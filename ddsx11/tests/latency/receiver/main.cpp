/**
 * @file   main.cpp
 * @author Martin Corino <mcorino@remedy.nl>
 *
 * @brief  Minimal latency DDS test using the IDL to C++11
 *         language mapping
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "latency_data_dds_typesupport.h"
#include "tests/testlib/ddsx11_testlog.h"
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "ace/Get_Opt.h"
#include "ace/High_Res_Timer.h"
#include "ace/Manual_Event.h"
#include "ace/OS_NS_string.h"
#include <iostream>
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <cmath>

static std::string const qos_profile { "latencydatalibrary#LatencyDataProfile" };

class TestExecutor; // forward

class LatencyDataListener final :
  public DDS::traits<Test::LatencyData>::datareaderlistener_type
{
public:
  LatencyDataListener(TestExecutor* executor)
    : executor_ (executor)
  {}

  void
  on_requested_deadline_missed (
    DDS::traits<Test::LatencyData>::datareader_ref_type the_reader,
    const DDS::RequestedDeadlineMissedStatus& status) override;

  void
  on_requested_incompatible_qos (
    DDS::traits<Test::LatencyData>::datareader_ref_type the_reader,
    const DDS::RequestedIncompatibleQosStatus& status) override;

  void
  on_sample_rejected (
    DDS::traits<Test::LatencyData>::datareader_ref_type the_reader,
    const DDS::SampleRejectedStatus& status) override;

  void
  on_liveliness_changed (
    DDS::traits<Test::LatencyData>::datareader_ref_type the_reader,
    const DDS::LivelinessChangedStatus& status) override;

  void
  on_subscription_matched (
      DDS::traits<Test::LatencyData>::datareader_ref_type the_reader,
      const DDS::SubscriptionMatchedStatus& status) override;

  void
  on_sample_lost (
      DDS::traits<Test::LatencyData>::datareader_ref_type the_reader,
      const DDS::SampleLostStatus& status) override;

  void
  on_data_available (
    DDS::traits<Test::LatencyData>::datareader_ref_type the_reader) override;

private:
  TestExecutor* executor_;
};

class TestExecutor
{
public:
  TestExecutor () {}
  ~TestExecutor () { cleanup (); }

  bool initialize (int argc, char*argv[]);

  void cleanup ();

  void read (Test::LatencyData & instance);

  void run ();

private:
  void usage ();
  bool parse_args (int argc, char * argv[]);

  ::DDS::DomainId_t domain_id_ {};

  DDS::traits<Test::LatencyData>::domainparticipantfactory_ref_type dpf_ {};
  DDS::traits<Test::LatencyData>::domainparticipant_ref_type domain_participant_ {};

  // publisher entities
  DDS::traits<Test::LatencyData>::topic_ref_type latency_topic_ {};
  DDS::traits<Test::LatencyData>::publisher_ref_type latency_publisher_ {};
  DDS::traits<Test::LatencyData>::datawriter_ref_type latency_dw_ {};
  DDS::traits<Test::LatencyData>::typed_datawriter_ref_type latency_writer_ {};

  // subscriber entities
  DDS::traits<Test::LatencyData>::topic_ref_type latency_echo_topic_ {};
  DDS::traits<Test::LatencyData>::subscriber_ref_type latency_echo_subscriber_ {};
  CORBA::object_traits<DDS::DataReader>::ref_type latency_echo_reader_ {};
  DDS::traits<Test::LatencyData>::datareaderlistener_ref_type latency_echo_listener_ {};
};


int main (int argc, char *argv[])
{
  try
  {
    TestExecutor tester;

    if (tester.initialize (argc, argv))
    {
      tester.run ();

      tester.cleanup ();
    }
    else
    {
      DDSX11_TEST_ERROR << "receiver: failed to initialize" << std::endl;
      return 1;
    }
  }
  catch (const std::exception& e)
  {
    DDSX11_TEST_ERROR << "receiver: exception caught: " << e << std::endl;
    return 1;
  }

  return 0;
}


bool
TestExecutor::initialize (int argc, char* argv[])
{
  const char * domain = std::getenv ("DDS4CCM_DEFAULT_DOMAIN_ID");
  if (domain)
  {
    this->domain_id_ = std::atoi (domain);
  }

  if (!parse_args(argc, argv))
  {
    return false;
  }

  this->dpf_=
    DDS::traits<DDS::DomainParticipantFactory>::get_instance ();

  this->domain_participant_ =
    this->dpf_->create_participant_with_profile (
        this->domain_id_, qos_profile, nullptr, DDS::STATUS_MASK_NONE);

  DDS::ReturnCode_t retcode = DDS::traits<Test::LatencyData>::register_type (
      this->domain_participant_, DDS::traits<Test::LatencyData>::get_type_name ());
  if (retcode != DDS::RETCODE_OK)
  {
    DDSX11_TEST_ERROR << "receiver: Failed to register type: "
                      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                      << std::endl;
    return false;
  }

  this->latency_topic_ =
      this->domain_participant_->create_topic_with_profile (
          "LatencyDataEcho", DDS::traits<Test::LatencyData>::get_type_name (), qos_profile, nullptr, DDS::STATUS_MASK_NONE);

  this->latency_publisher_ =
    this->domain_participant_->create_publisher_with_profile (
        qos_profile, nullptr, DDS::STATUS_MASK_NONE);

  if (this->latency_publisher_ && this->latency_topic_)
  {
    this->latency_dw_ =
      this->latency_publisher_->create_datawriter_with_profile (
          this->latency_topic_, qos_profile, nullptr, DDS::STATUS_MASK_NONE);

    this->latency_writer_ =
      DDS::traits<Test::LatencyData>::narrow (this->latency_dw_);

    if (!this->latency_writer_)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to create latency writer"
                        << std::endl;
      return false;
    }
  }
  else
  {
    DDSX11_TEST_ERROR << "receiver: Failed to create latency publisher and topic"
                      << std::endl;
    return false;
  }


  this->latency_echo_topic_ =
      this->domain_participant_->create_topic_with_profile (
          "LatencyData", DDS::traits<Test::LatencyData>::get_type_name (), qos_profile, nullptr, DDS::STATUS_MASK_NONE);

  this->latency_echo_subscriber_ =
    this->domain_participant_->create_subscriber (DDS::SUBSCRIBER_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);

  if (this->latency_echo_topic_ && this->latency_echo_subscriber_)
  {
    this->latency_echo_listener_ =
      DDS::make_reference<LatencyDataListener> (this);
    if (this->latency_echo_listener_)
    {
      this->latency_echo_reader_ =
          this->latency_echo_subscriber_->create_datareader_with_profile (
              this->latency_echo_topic_, qos_profile, this->latency_echo_listener_, DDS::DATA_AVAILABLE_STATUS);

      if (!this->latency_echo_reader_)
      {
        DDSX11_TEST_ERROR << "receiver: Error in creating datareader!" << std::endl;
        return false;
      }
    }
    else
    {
      DDSX11_TEST_ERROR << "receiver: No listener created!" << std::endl;
      return false;
    }
  }

  return true;
}

void
TestExecutor::usage ()
{
  //X11_FUZZ: disable check_cout_cerr
  std::cerr << std::endl <<
    "receiver " << std::endl <<
    "\tOptions:" << std::endl <<
    "\t--domain DOMAINID    DDS domain ID (default $DDS4CCM_DEFAULT_DOMAIN_ID)" << std::endl <<
    "\t-h|--help            print this help message" << std::endl << std::endl;
  //X11_FUZZ: enable check_cout_cerr
}

bool
TestExecutor::parse_args (int argc, char * argv[])
{
  ACE_Get_Opt get_opts (argc,
                        argv,
                        ACE_TEXT("h"),
                        1,
                        0,
                        ACE_Get_Opt::RETURN_IN_ORDER);

  get_opts.long_option (ACE_TEXT("domain"), ACE_Get_Opt::ARG_REQUIRED);
  get_opts.long_option (ACE_TEXT("help"), ACE_Get_Opt::NO_ARG);

  int c {};
  while ( (c = get_opts ()) != -1)
  {
    switch (c)
    {
    //X11_FUZZ: disable check_cout_cerr
    case 'h':
      this->usage ();
      ACE_OS::exit (0);
      break;
    //X11_FUZZ: enable check_cout_cerr

    case 0:
      if (ACE_OS::strcmp (get_opts.long_option (),
                               ACE_TEXT("domain")) == 0)
      {
        this->domain_id_ = std::atoi (get_opts.opt_arg ());
      }
      else
      {
        DDSX11_TEST_WARNING << "TestExecutor::parse_args - "
                               "Ignoring unknown long option: " <<
                               get_opts.long_option () << std::endl;
      }
      break;

    default:
      DDSX11_TEST_WARNING << "TestExecutor::parse_args - ignoring incorrect option: " <<
                             (get_opts.opt_arg () ? get_opts.opt_arg () : "") << std::endl;
    }
  }

  return true;
}

void
TestExecutor::cleanup ()
{
  if (this->latency_writer_)
  {
    DDS::ReturnCode_t retcode = this->latency_publisher_->delete_datawriter (this->latency_writer_);
    this->latency_writer_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to delete datawriter from publisher: "
                        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->latency_publisher_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_publisher (this->latency_publisher_);
    this->latency_publisher_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to delete publisher from domain participant"
                        << std::endl;
    }
  }
  if (this->latency_topic_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_topic (this->latency_topic_);
    this->latency_topic_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to delete topic from domain participant"
                        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }

  if (this->latency_echo_reader_)
  {
    DDS::ReturnCode_t retcode = this->latency_echo_subscriber_->delete_datareader (this->latency_echo_reader_);
    this->latency_echo_reader_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to delete datareader from subscriber."
                        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->latency_echo_subscriber_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_subscriber (this->latency_echo_subscriber_);
    this->latency_echo_subscriber_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to delete subscriber from domain participant." << std::endl
                        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->latency_echo_topic_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_topic (this->latency_echo_topic_);
    this->latency_echo_topic_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to delete topic from domain participant"
                        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }

  if (this->domain_participant_)
  {
    DDS::ReturnCode_t retcode = this->dpf_->delete_participant(this->domain_participant_);
    this->domain_participant_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to delete domain participant from domain participant factory: "
                        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->dpf_)
  {
    DDS::ReturnCode_t retcode = this->dpf_->finalize_instance ();
    this->dpf_ = nullptr;
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Failed to finalize the domain participant factory: "
                        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
}

void
TestExecutor::run ()
{
  DDSX11_TEST_INFO << "Receiver: starting test" << std::endl;

  ACE_Manual_Event test_event (0, USYNC_PROCESS, "TEST_MANUAL_EVENT");

  test_event.wait();

  DDSX11_TEST_INFO << "Receiver: finished test" << std::endl;
}

void
TestExecutor::read (Test::LatencyData & an_instance)
{
  this->latency_writer_->write(an_instance, ::DDS::HANDLE_NIL);
}

void
LatencyDataListener::on_requested_deadline_missed (
  DDS::traits<Test::LatencyData>::datareader_ref_type ,
  const DDS::RequestedDeadlineMissedStatus& )
{
  DDSX11_TEST_DEBUG << "LatencyDataListener::on_requested_deadline_missed received"
                    << std::endl;
}

void
LatencyDataListener::on_requested_incompatible_qos (
  DDS::traits<Test::LatencyData>::datareader_ref_type ,
  const DDS::RequestedIncompatibleQosStatus& )
{
  DDSX11_TEST_DEBUG << "LatencyDataListener::on_requested_incompatible_qos received"
                    << std::endl;
}

void
LatencyDataListener::on_sample_rejected (
  DDS::traits<Test::LatencyData>::datareader_ref_type ,
  const DDS::SampleRejectedStatus& )
{
  DDSX11_TEST_DEBUG << "LatencyDataListener::on_sample_rejected received"
                    << std::endl;
}

void
LatencyDataListener::on_liveliness_changed (
  DDS::traits<Test::LatencyData>::datareader_ref_type ,
  const DDS::LivelinessChangedStatus& )
{
  DDSX11_TEST_DEBUG << "LatencyDataListener::on_liveliness_changed received"
                    << std::endl;
}

void
LatencyDataListener::on_subscription_matched (
  DDS::traits<Test::LatencyData>::datareader_ref_type ,
  const DDS::SubscriptionMatchedStatus& )
{
  DDSX11_TEST_DEBUG << "LatencyDataListener::on_subscription_matched received"
                    << std::endl;
}

void
LatencyDataListener::on_sample_lost (
  DDS::traits<Test::LatencyData>::datareader_ref_type ,
  const DDS::SampleLostStatus& )
{
  DDSX11_TEST_DEBUG << "LatencyDataListener::on_sample_lost received"
                    << std::endl;
}

void
LatencyDataListener::on_data_available (
  DDS::traits<Test::LatencyData>::datareader_ref_type the_reader)
{
  //DDSX11_TEST_DEBUG << "LatencyDataListener::on_data_available" << std::endl;
  DDS::traits<Test::LatencyData>::typed_datareader_ref_type rd =
    DDS::traits<Test::LatencyData>::narrow (the_reader);

  Test::LatencyData datum;
  DDS::SampleInfo info;
  DDS::ReturnCode_t const retcode = rd->take_next_sample(datum, info);
  if (retcode == DDS::RETCODE_NO_DATA)
  {
    DDSX11_TEST_ERROR << "LatencyDataListener::on_data_available: No data available!"
                      << std::endl;
  }
  else if (retcode != DDS::RETCODE_OK)
  {
    DDSX11_TEST_ERROR << "LatencyDataListener::on_data_available: Unable to take data from data reader, error "
                      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                      << std::endl;
  }
  else if (info.valid_data ())
  {
    if ( (info.instance_state () == ::DDS::ALIVE_INSTANCE_STATE &&
            info.view_state () == ::DDS::NEW_VIEW_STATE)
        || ((info.instance_state () == ::DDS::ALIVE_INSTANCE_STATE &&
                info.view_state () == ::DDS::NOT_NEW_VIEW_STATE) ||
             info.instance_state () == ::DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE))
    {
      this->executor_->read(const_cast<Test::LatencyData&> (datum));
    }
  }
}
