/**
 * @file   log_server.cpp
 * @author Johnny Willemsen
 *
 * @brief  A simple server daemon that prints log records received over DDS.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ace/Log_Msg.h"
#include "ace/Get_Opt.h"
#include "log_record_dds_typesupport.h"
#include "tests/testlib/ddsx11_testlog.h"

#include <string>
#include <iostream>
#include <thread>

// @todo add listener, cleanup all dds entities one by one
struct Options
{
  std::string topic_;
  DDS::DomainId_t domain_ {};
  std::string qosprofile_;
};

Options program_options;

bool parse_args (int argc, ACE_TCHAR **argv)
{
  ACE_Get_Opt opts (argc, argv, ACE_TEXT ("t:d:q:"), 1, 0,
                    ACE_Get_Opt::RETURN_IN_ORDER);
  opts.long_option (ACE_TEXT ("topic"), 't', ACE_Get_Opt::ARG_REQUIRED);
  opts.long_option (ACE_TEXT ("domain"), 'd', ACE_Get_Opt::ARG_REQUIRED);
  opts.long_option (ACE_TEXT ("qosprofile"), 'q', ACE_Get_Opt::ARG_REQUIRED);

  int c = 0;

  while ((c = opts ()) != -1)
    {
      switch (c)
        {
        case 't':
          program_options.topic_ = opts.opt_arg ();
          break;

        case 'd':
          program_options.domain_ = std::atoi (opts.opt_arg ());
          break;

        case 'q':
          program_options.qosprofile_ = opts.opt_arg ();
          break;

        default:
          DDSX11_TEST_ERROR << "Unknown option for log_server " << opts.last_option () << std::endl;

          return false;
        }
    }
  return true;
}

class Log_RecordListener final :
  public DDS::traits<DnCX11::Log_Record>::datareaderlistener_type
{
public:
  void
  on_requested_deadline_missed (
    DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader,
    const DDS::RequestedDeadlineMissedStatus& status) override;

  void
  on_requested_incompatible_qos (
    DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader,
    const DDS::RequestedIncompatibleQosStatus& status) override;

  void
  on_sample_rejected (
    DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader,
    const DDS::SampleRejectedStatus& status) override;

  void
  on_liveliness_changed (
    DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader,
    const DDS::LivelinessChangedStatus& status) override;

  void
  on_subscription_matched (
      DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader,
      const DDS::SubscriptionMatchedStatus& status) override;

  void
  on_sample_lost (
      DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader,
      const DDS::SampleLostStatus& status) override;

  void
  on_data_available (
    DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader) override;
};

int
ACE_TMAIN (int argc, ACE_TCHAR **argv)
{
  if (!parse_args (argc, argv))
    {
      DDSX11_TEST_ERROR << "Unable to parse command line options" << std::endl;
      return 1;
    }

  DDS::traits<DnCX11::Log_Record>::domainparticipantfactory_ref_type dpf_ =
      DDS::traits<DDS::DomainParticipantFactory>::get_instance ();
  DDS::traits<DnCX11::Log_Record>::domainparticipant_ref_type participant_;
  DDS::traits<DnCX11::Log_Record>::topic_ref_type topic_;
  DDS::traits<DnCX11::Log_Record>::subscriber_ref_type subscriber_;
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type datareader_;
  DDS::traits<DnCX11::Log_Record>::typed_datareader_ref_type log_record_reader_;

  try
    {
      if (program_options.qosprofile_.empty ())
        {
          participant_ = dpf_->
            create_participant (
              program_options.domain_,
              DDS::PARTICIPANT_QOS_DEFAULT,
              nullptr,
              DDS::STATUS_MASK_NONE);
        }
      else
        {
          participant_ = dpf_->
            create_participant_with_profile (
              program_options.domain_,
              program_options.qosprofile_,
              nullptr,
              DDS::STATUS_MASK_NONE);
        }

      if (!participant_)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to create participant" << std::endl;
          return 1;
        }

      DDS::ReturnCode_t retval =
        DDS::traits<DnCX11::Log_Record>::register_type(
          participant_,
          DDS::traits<DnCX11::Log_Record>::get_type_name ());

      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to register type" << std::endl;
          throw 1;
        }

      DDS::TopicQos tqos;
      retval = participant_->get_default_topic_qos (tqos);

      if (retval != DDS::RETCODE_OK)
      {
          DDSX11_TEST_ERROR << "log_server - Failed to register type <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
          throw 1;
      }

      topic_ = participant_->create_topic (
        program_options.topic_,
        DDS::traits<DnCX11::Log_Record>::get_type_name (),
        tqos,
        nullptr,
        DDS::STATUS_MASK_NONE);

      if (!topic_)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to create topic" << std::endl;
          throw 1;
        }

      DDS::SubscriberQos subqos;
      retval = participant_->get_default_subscriber_qos (subqos);
      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to retrieve default subscriber QoS <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
          throw 1;
        }

      subscriber_ =
        participant_->create_subscriber (
          subqos,
          nullptr,
          DDS::STATUS_MASK_NONE);

      if (!subscriber_)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to create subscriber" << std::endl;
          throw 1;
        }

      DDS::DataReaderQos readerqos;
      retval = subscriber_->get_default_datareader_qos (readerqos);
      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to retrieve default datareader QoS <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
          throw 1;
        }

      DDS::traits<DnCX11::Log_Record>::datareaderlistener_ref_type listener =
        DDS::make_reference<Log_RecordListener>();
      datareader_ =
        subscriber_->create_datareader (
          topic_,
          readerqos,
          listener,
          DDS::DATA_AVAILABLE_STATUS);

      if (!datareader_)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to create the datareader" << std::endl;
          throw 1;
        }

      log_record_reader_ =
        DDS::traits<DnCX11::Log_Record>::narrow (datareader_);

      if (!log_record_reader_)
        {
          DDSX11_TEST_ERROR << "log_server - Failed to narrow the typed datareader" << std::endl;
          throw 1;
        }

      for (;;)
        {
          std::this_thread::sleep_for (std::chrono::seconds (1));
        }
    }
  catch (...)
    {
    }

  if (datareader_)
    {
      DDS::ReturnCode_t const retval =
        subscriber_->delete_datareader (datareader_);

      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Unable to delete datareader <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
        }

      datareader_ = nullptr;
      log_record_reader_ = nullptr;
    }

  if (subscriber_)
    {
      DDS::ReturnCode_t const retval =
        participant_->delete_subscriber (subscriber_);

      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Unable to delete subscriber <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
        }
      subscriber_ = nullptr;
    }

  if (topic_)
    {
      DDS::ReturnCode_t const retval =
        participant_->delete_topic (topic_);

      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Unable to delete topic <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
        }
      topic_ = nullptr;
    }

  if (participant_)
    {
      DDS::ReturnCode_t const retval =
        dpf_->delete_participant (participant_);

      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Unable to delete participant <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
        }
      participant_ = nullptr;
    }

  if (dpf_)
    {
      DDS::ReturnCode_t const retval =
        dpf_->finalize_instance ();

      if (retval != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "log_server - Unable to finalize participant factory <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
            << ">." << std::endl;
        }
      dpf_ = nullptr;
    }

  return 0;
}

void
Log_RecordListener::on_requested_deadline_missed (
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type ,
  const DDS::RequestedDeadlineMissedStatus& )
{
  DDSX11_TEST_DEBUG << "Log_RecordListener::on_requested_deadline_missed received" << std::endl;
}

void
Log_RecordListener::on_requested_incompatible_qos (
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type ,
  const DDS::RequestedIncompatibleQosStatus& )
{
  DDSX11_TEST_DEBUG << "Log_RecordListener::on_requested_incompatible_qos received" << std::endl;
}

void
Log_RecordListener::on_sample_rejected (
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type ,
  const DDS::SampleRejectedStatus& )
{
  DDSX11_TEST_DEBUG << "Log_RecordListener::on_sample_rejected received" << std::endl;
}

void
Log_RecordListener::on_liveliness_changed (
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type ,
  const DDS::LivelinessChangedStatus& )
{
  DDSX11_TEST_DEBUG << "Log_RecordListener::on_liveliness_changed received" << std::endl;
}

void
Log_RecordListener::on_subscription_matched (
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type ,
  const DDS::SubscriptionMatchedStatus& )
{
  DDSX11_TEST_DEBUG << "Log_RecordListener::on_subscription_matched received" << std::endl;
}

void
Log_RecordListener::on_sample_lost (
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type ,
  const DDS::SampleLostStatus& )
{
  DDSX11_TEST_DEBUG << "Log_RecordListener::on_sample_lost received" << std::endl;
}

void
Log_RecordListener::on_data_available (
  DDS::traits<DnCX11::Log_Record>::datareader_ref_type the_reader)
{
  DDSX11_TEST_DEBUG << "Log_RecordListener::on_data_available received" << std::endl;

  DDS::traits<DnCX11::Log_Record>::typed_datareader_ref_type rd =
    DDS::traits<DnCX11::Log_Record>::narrow (the_reader);

  DnCX11::Log_Record log_record;
  DDS::SampleInfo info;
  for(;;)
  {
    DDS::ReturnCode_t const retval = rd->take_next_sample(log_record, info);
    if (retval == DDS::RETCODE_NO_DATA)
    {
      /* No more samples */
      break;
    }
    else if (retval != DDS::RETCODE_OK)
    {
      DDSX11_TEST_DEBUG << "Unable to take data from datareader, error <"
        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
        << ">" << std::endl;
      break;
    }
    else if (info.valid_data ())
    {
      DDSX11_TEST_DEBUG << "Received: " << log_record << std::endl;
    }
  }
}

