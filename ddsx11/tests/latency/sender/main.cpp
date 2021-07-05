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
#include "ace/High_Res_Timer.h"
#include "ace/Get_Opt.h"
#include "ace/Manual_Event.h"
#include "ace/OS_NS_string.h"
#include <iostream>
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <cmath>

static std::string const qos_profile { "latencydatalibrary#LatencyDataProfile" };

class TestExecutor; // forward

// Ticker EventHandler
class TickerHandler final
  : public ACE_Event_Handler
{
public:
  TickerHandler (
      TestExecutor* executor,
      bool startup)
    : executor_ (executor)
    , startup_ (startup)
  {
    // make this event handler reference counted
    this->reference_counting_policy ().value
      (ACE_Event_Handler::Reference_Counting_Policy::ENABLED);
  }

  virtual ~TickerHandler () = default;

  int handle_timeout (const ACE_Time_Value&,
                      const void*) override;

private:
  TickerHandler(const TickerHandler&) = delete;
  TickerHandler(TickerHandler&&) = delete;
  TickerHandler& operator=(const TickerHandler&) = delete;
  TickerHandler& operator=(TickerHandler&&) = delete;

  TestExecutor* executor_;
  bool startup_;
};

class LatencyDataListener final :
  public DDS::traits<Test::LatencyData>::datareaderlistener_type
{
public:
  LatencyDataListener(TestExecutor* executor, bool read_one)
    : executor_ (executor)
    , read_one_ (read_one)
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
  bool read_one_ {};
};

class TestExecutor
{
public:
  TestExecutor () {}
  ~TestExecutor () { cleanup (); }

  bool initialize (int argc, char*argv[]);

  void cleanup ();

  void tick ();
  void check_status ();

  void read (Test::LatencyData & instance, uint64_t receive_time);

  void run ();

private:

  void usage ();
  bool parse_args (int argc, char * argv[]);
  void calc_results (void);
  void reset_results (void);
  void init_values (void);
  void calculate_clock_overhead (void);
  void record_time (uint64_t receive_time);
  void start_publishing ();
  void start ();

  bool finished_ {};

  uint32_t rate_{100};
  uint32_t samples_{10000};
  uint32_t sample_size_{1024};
  uint32_t iterations_{10};
  ::DDS::DomainId_t domain_id_ {};
  bool read_one_ {false};

  bool already_publishing_ {};

  uint32_t iteration_nr_ {};
  std::atomic<bool> matched_ {};
  uint64_t tv_total_ {};
  uint64_t tv_max_ {};
  uint64_t tv_min_ {};
  uint16_t count_ {};
  uint16_t number_of_msg_ {};
  std::atomic<bool> received_ {};
  int32_t seq_num_ {};
  double sigma_duration_squared_ {};
  uint64_t start_time_ {};
  uint64_t start_time_test_ {};
  uint64_t end_time_test_ {};

  struct IterationResult
  {
    double tv_avg_ {};
    double sigma_duration_squared_;
    uint64_t tv_max_ {};
    uint64_t tv_min_ {};
    double per50_;
    double per90_;
    double per99_;
    double per9999_;
  };

  std::unique_ptr<uint64_t[]> duration_times_ {};
  std::unique_ptr<IterationResult[]> iteration_results_;
  int32_t _clock_overhead_ {};

  long timer_id_;

  DDS::traits<Test::LatencyData>::domainparticipantfactory_ref_type dpf_ {};
  DDS::traits<Test::LatencyData>::domainparticipant_ref_type domain_participant_ {};

  // publisher entities
  DDS::traits<Test::LatencyData>::topic_ref_type latency_topic_ {};
  DDS::traits<Test::LatencyData>::publisher_ref_type latency_publisher_ {};
  DDS::traits<Test::LatencyData>::datawriter_ref_type latency_dw_ {};
  DDS::traits<Test::LatencyData>::typed_datawriter_ref_type latency_writer_ {};
  Test::LatencyData latency_sample_ {};

  // subscriber entities
  DDS::traits<Test::LatencyData>::topic_ref_type latency_echo_topic_ {};
  DDS::traits<Test::LatencyData>::subscriber_ref_type latency_echo_subscriber_ {};
  IDL::traits<DDS::DataReader>::ref_type latency_echo_reader_ {};
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
      DDSX11_TEST_ERROR << "sender: failed to initialize" << std::endl;
      return 1;
    }
  }
  catch (const std::exception& e)
  {
    DDSX11_TEST_ERROR << "sender: exception caught: " << e.what ()
                      << std::endl;
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
    DDSX11_TEST_ERROR << "sender: Failed to register type: "
                      << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                      << std::endl;
    return false;
  }

  this->latency_topic_ =
      this->domain_participant_->create_topic_with_profile (
          "LatencyData", DDS::traits<Test::LatencyData>::get_type_name (), qos_profile, nullptr, DDS::STATUS_MASK_NONE);

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
      DDSX11_TEST_ERROR << "sender: Failed to create latency writer"
                        << std::endl;
      return false;
    }
  }
  else
  {
    DDSX11_TEST_ERROR << "sender: Failed to create latency publisher and topic"
                      << std::endl;
    return false;
  }

  this->latency_echo_topic_ =
      this->domain_participant_->create_topic_with_profile (
          "LatencyDataEcho", DDS::traits<Test::LatencyData>::get_type_name (), qos_profile, nullptr, DDS::STATUS_MASK_NONE);

  this->latency_echo_subscriber_ =
    this->domain_participant_->create_subscriber (DDS::SUBSCRIBER_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);

  if (this->latency_echo_topic_ && this->latency_echo_subscriber_)
  {
    this->latency_echo_listener_ =
      DDS::make_reference<LatencyDataListener> (this, this->read_one_);
    if (this->latency_echo_listener_)
    {
      this->latency_echo_reader_ =
          this->latency_echo_subscriber_->create_datareader_with_profile (
              this->latency_echo_topic_, qos_profile, this->latency_echo_listener_, DDS::DATA_AVAILABLE_STATUS);

      if (!this->latency_echo_reader_)
      {
        DDSX11_TEST_ERROR << "sender: Error in creating datareader!" << std::endl;
        return false;
      }
    }
    else
    {
      DDSX11_TEST_ERROR << "sender: No listener created!" << std::endl;
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
    "sender " << std::endl <<
    "\tOptions:" << std::endl <<
    "\t--rate RATE          timer frequency in microseconds (default 100)" << std::endl <<
    "\t--samples COUNT      number of samples to send each iteration (default 10000)" << std::endl <<
    "\t--samplesize SIZE    size of samples sent (default 1024) in bytes" << std::endl <<
    "\t--iterations COUNT   number of iterations to run (default 10)" << std::endl <<
    "\t--domain DOMAINID    DDS domain ID (default $DDS4CCM_DEFAULT_DOMAIN_ID)" << std::endl <<
    "\t--readall            read all available samples on data_available" << std::endl <<
    "\t--readone            read a single sample at a time on data_available (default :readall)" << std::endl <<
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

  get_opts.long_option (ACE_TEXT("rate"), ACE_Get_Opt::ARG_REQUIRED);
  get_opts.long_option (ACE_TEXT("samples"), ACE_Get_Opt::ARG_REQUIRED);
  get_opts.long_option (ACE_TEXT("samplesize"), ACE_Get_Opt::ARG_REQUIRED);
  get_opts.long_option (ACE_TEXT("iterations"), ACE_Get_Opt::ARG_REQUIRED);
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
                          ACE_TEXT("rate")) == 0)
      {
        this->rate_ = std::atoi (get_opts.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opts.long_option (),
                               ACE_TEXT("samples")) == 0)
      {
        this->samples_ = std::atoi (get_opts.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opts.long_option (),
                               ACE_TEXT("samplesize")) == 0)
      {
        this->sample_size_ = std::atoi (get_opts.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opts.long_option (),
                               ACE_TEXT("iterations")) == 0)
      {
        this->iterations_ = std::atoi (get_opts.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opts.long_option (),
                               ACE_TEXT("domain")) == 0)
      {
        this->domain_id_ = std::atoi (get_opts.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opts.long_option (),
                               ACE_TEXT("readall")) == 0)
      {
        this->read_one_ = false;
      }
      else if (ACE_OS::strcmp (get_opts.long_option (),
                               ACE_TEXT("readone")) == 0)
      {
        this->read_one_ = true;
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
      DDSX11_TEST_ERROR << "sender: Failed to delete datawriter from publisher: "
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->latency_publisher_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_publisher (this->latency_publisher_);
    this->latency_publisher_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "sender: Failed to delete publisher from domain participant"
                        << std::endl;
    }
  }
  if (this->latency_topic_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_topic (this->latency_topic_);
    this->latency_topic_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "sender: Failed to delete topic from domain participant"
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }

  if (this->latency_echo_reader_)
  {
    DDS::ReturnCode_t retcode = this->latency_echo_subscriber_->delete_datareader (this->latency_echo_reader_);
    this->latency_echo_reader_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "sender: Failed to delete datareader from subscriber."
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->latency_echo_subscriber_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_subscriber (this->latency_echo_subscriber_);
    this->latency_echo_subscriber_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "sender: Failed to delete subscriber from domain participant." << std::endl
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->latency_echo_topic_)
  {
    DDS::ReturnCode_t retcode = this->domain_participant_->delete_topic (this->latency_echo_topic_);
    this->latency_echo_topic_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "sender: Failed to delete topic from domain participant"
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }

  if (this->domain_participant_)
  {
    DDS::ReturnCode_t retcode = this->dpf_->delete_participant(this->domain_participant_);
    this->domain_participant_ = nullptr;
    if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "sender: Failed to delete domain participant from domain participant factory: "
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
  if (this->dpf_)
  {
    DDS::ReturnCode_t retcode = this->dpf_->finalize_instance ();
    this->dpf_ = nullptr;
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "sender: Failed to finalize the domain participant factory: "
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
    }
  }
}

void
TestExecutor::check_status ()
{
  if (this->latency_dw_)
  {
    ::DDS::PublicationMatchedStatus status {};
    ::DDS::ReturnCode_t const retcode = this->latency_dw_->get_publication_matched_status (status);

    if (retcode != ::DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR <<"Sender_exec_i::check_status - "
        << "Error: Unable to get_publication_matched_status: <"
        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">." << std::endl;
      this->finished_ = true;
    }
    else
    {
      DDSX11_TEST_DEBUG << "Sender_exec_i::check_status publication_matched current_count: "
                       << status.current_count() << std::endl;

      if (status.current_count() == 1)
      {
        DDSX11_TEST_DEBUG << "Sender_exec_i::check_status publication_matched received" << std::endl;
        this->start_publishing();
      }
    }
  }
}

void
TestExecutor::run ()
{
  DDSX11_TEST_INFO << "Sender: starting test" << std::endl;

  ACE_Manual_Event test_event (0, USYNC_PROCESS, "TEST_MANUAL_EVENT");

  this->init_values();

  ACE_Event_Handler_var evh =
      ACE::make_event_handler<TickerHandler> (this, true);

  this->timer_id_ = ACE_Reactor::instance ()->schedule_timer(
      evh.handler(),
      nullptr,
      ACE_Time_Value (1, 0),
      ACE_Time_Value (1, 0));

  this->finished_ = false;
  while (!this->finished_)
  {
    if (ACE_Reactor::instance ()->work_pending(ACE_Time_Value(0, 1000*100)))
    {
      ACE_Reactor::instance ()->handle_events ();
    }
  }

  // signal receiver that we finished
  test_event.signal();

  DDSX11_TEST_INFO << "Sender: finished test" << std::endl;
}

void
TestExecutor::start_publishing ()
{
  if (!this->already_publishing_)
  {
    this->already_publishing_ = true;

    ACE_Reactor::instance ()->cancel_timer(this->timer_id_);

    this->start ();
  }
}

void
TestExecutor::tick ()
{
  if (this->number_of_msg_ == 0)
  {
    ACE_High_Res_Timer::gettimeofday_hr ().to_usec (this->start_time_test_);
  }
  // First message sent always, next messages only as previous sent message
  // is received back.
  if (this->number_of_msg_ == 0 || this->received_)
  {
    // All messages send, stop timer.
    if (this->samples_ != 0 && this->number_of_msg_ >= this->samples_)
    {
      // iterate max (iterations_+1) times; ignoring the first iteration
      if (this->iteration_nr_ >= this->iterations_)
      {
        ACE_Reactor::instance ()->cancel_timer(this->timer_id_);
        this->calc_results ();
        ACE_High_Res_Timer::gettimeofday_hr ().to_usec (this->end_time_test_);
        this->finished_ = true;
      }
      else
      {
        this->calc_results ();
        this->reset_results ();
        ++this->iteration_nr_;
      }
    }
    else
    {
      this->latency_sample_.seq_num (this->number_of_msg_);

      // Keep last sent seq_num, to control if message is sent back.
      this->seq_num_ = this->number_of_msg_;
      this->received_ = false;
      ACE_High_Res_Timer::gettimeofday_hr ().to_usec (this->start_time_);
      DDS::ReturnCode_t retcode = this->latency_writer_->write (this->latency_sample_, ::DDS::HANDLE_NIL);
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR <<"TestExecutor::tick - "
          << "Error: Unable to write sample: <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">." << std::endl;
        this->finished_ = true;
      }
      else
        ++this->number_of_msg_;
    }
  }
}

void
TestExecutor::read (Test::LatencyData & an_instance, uint64_t receive_time)
{
  if (an_instance.seq_num () == this->seq_num_)
    {
      this->record_time (receive_time);
      this->received_ = true;
    }
}

void
TestExecutor::reset_results()
{
  this->count_ = 0;

  this->duration_times_.reset (new uint64_t[this->samples_]);

  this->tv_total_ = 0L;
  this->tv_max_ = 0L;
  this->tv_min_ = 0L;
  this->number_of_msg_ = 0;
  this->received_ = false;
  this->seq_num_ = 0;
  this->sigma_duration_squared_ = 0;
}

void
TestExecutor::calc_results (void)
{
  if (this->iteration_nr_ == 0)
    return; // ignore first iteration

  // Sort all duration times.
  std::qsort(this->duration_times_.get (),
             this->count_,
             sizeof(uint64_t),
             [](const void *long1, const void *long2)
             {
               return (int)(*(uint64_t*)long1 - *(uint64_t*)long2);
             });

  // Show latency_50_percentile, latency_90_percentile,
  // latency_99_percentile and latency_99.99_percentile.
  // For example duration_times[per50] is the median i.e. 50% of the
  // samples have a latency time <= duration_times[per50]
  int const per50 = this->count_ / 2;
  int const per90 = (int)(this->count_ * 0.90);
  int const per99 = (int)(this->count_ * 0.990);
  int const per9999 = (int)(this->count_ * 0.9999);

  double const avg = (double)(this->tv_total_ / this->count_);
  // Calculate standard deviation.
  double const roundtrip_time_std  = std::sqrt(
      (this->sigma_duration_squared_ / (double)this->count_) -
      (avg * avg));

  uint32_t iteration_ix = this->iteration_nr_-1;

  this->iteration_results_[iteration_ix].tv_avg_ = avg;
  this->iteration_results_[iteration_ix].sigma_duration_squared_ = this->sigma_duration_squared_;
  this->iteration_results_[iteration_ix].tv_min_ = this->tv_min_;
  this->iteration_results_[iteration_ix].tv_max_ = this->tv_max_;
  this->iteration_results_[iteration_ix].per50_ = (double)this->duration_times_[per50-1];
  this->iteration_results_[iteration_ix].per90_ = (double)this->duration_times_[per90-1];
  this->iteration_results_[iteration_ix].per99_ = (double)this->duration_times_[per99-1];
  this->iteration_results_[iteration_ix].per9999_ = (double)this->duration_times_[per9999-1];

  // Show values as float, in order to be comparable with RTI performance test.
  if (this->count_ > 0)
  {
    if (iteration_ix == 0)
    {
      DDSX11_TEST_INFO << std::endl <<
                           "NO, we're not using a threadswitch between DDS and DDSX11" <<
                           std::endl;
      DDSX11_TEST_INFO <<
          "Collecting statistics on " << this->count_ << " samples per message (size " << this->sample_size_ << " bytes)" << std::endl <<
          "at a rate of 1 sample per " << this->rate_ << "usec. (" << (this->read_one_ ? "readone" : "readall") << ")" << std::endl <<
       "This is the roundtrip time, *not* the one-way-latency" << std::endl <<
       " stdev us ave us   min us   50%% us  90%% us  99%% us  99.99%%  max us" << std::endl <<
       " --------+--------+--------+--------+--------+--------+--------+--------" << std::endl <<
        std::setw(9) << std::fixed << std::setprecision(1) << roundtrip_time_std <<
        std::setw(9) << std::fixed << std::setprecision(1) << avg <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->tv_min_ <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per50-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per90-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per99-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per9999-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->tv_max_ << std::endl;
    }
    else
    {
      DDSX11_TEST_INFO <<
        std::setw(9) << std::fixed << std::setprecision(1) << roundtrip_time_std <<
        std::setw(9) << std::fixed << std::setprecision(1) << avg <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->tv_min_ <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per50-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per90-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per99-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->duration_times_[per9999-1] <<
        std::setw(9) << std::fixed << std::setprecision(1) << (double)this->tv_max_ << std::endl;

      if (this->iterations_ > 1 && this->iteration_nr_ >= this->iterations_)
      {
        double total_avg {}, total_sigma {};
        double avg_per50 {}, avg_per90 {}, avg_per99 {}, avg_per9999 {};
        for (uint32_t n=0; n<this->iterations_ ;++n)
        {
          total_avg += this->iteration_results_[n].tv_avg_;
          total_sigma += this->iteration_results_[n].sigma_duration_squared_;
          avg_per50 += this->iteration_results_[n].per50_;
          avg_per90 += this->iteration_results_[n].per90_;
          avg_per99 += this->iteration_results_[n].per99_;
          avg_per9999 += this->iteration_results_[n].per9999_;
        }
        total_avg /= this->iterations_;
        avg_per50 /= this->iterations_;
        avg_per90 /= this->iterations_;
        avg_per99 /= this->iterations_;
        avg_per9999 /= this->iterations_;
        double const avg_roundtrip_time_std  = ::sqrt(
            (total_sigma / (double)(this->samples_ * this->iterations_)) -
            (total_avg * total_avg));

        // Sort all minimum duration times.
        std::qsort(this->iteration_results_.get (),
                   this->iterations_,
                   sizeof(IterationResult),
                   [](const void *result1, const void *result2)
                   {
                     const IterationResult* r1 = (const IterationResult*)result1;
                     const IterationResult* r2 = (const IterationResult*)result2;
                     return (r1->tv_min_ < r2->tv_min_ ? -1 : (r1->tv_min_ > r2->tv_min_ ? 1 : 0));
                   });
        uint64_t tv_min_total = this->iteration_results_[0].tv_min_;

        // Sort all maximum duration times (in reverse order).
        std::qsort(this->iteration_results_.get (),
                   this->iterations_,
                   sizeof(IterationResult),
                   [](const void *result1, const void *result2)
                   {
                     const IterationResult* r1 = (const IterationResult*)result1;
                     const IterationResult* r2 = (const IterationResult*)result2;
                     return (r2->tv_max_ < r1->tv_max_ ? -1 : (r2->tv_max_ > r1->tv_max_ ? 1 : 0));
                   });
        uint64_t tv_max_total = this->iteration_results_[0].tv_max_;


        DDSX11_TEST_INFO <<
         " --------+--------+--------+--------+--------+--------+--------+--------" << std::endl <<
          std::setw(9) << std::fixed << std::setprecision(1) << avg_roundtrip_time_std <<
          std::setw(9) << std::fixed << std::setprecision(1) << total_avg <<
          std::setw(9) << std::fixed << std::setprecision(1) << (double)tv_min_total <<
          std::setw(9) << std::fixed << std::setprecision(1) << (double)avg_per50 <<
          std::setw(9) << std::fixed << std::setprecision(1) << (double)avg_per90 <<
          std::setw(9) << std::fixed << std::setprecision(1) << (double)avg_per99 <<
          std::setw(9) << std::fixed << std::setprecision(1) << (double)avg_per9999 <<
          std::setw(9) << std::fixed << std::setprecision(1) << (double)tv_max_total << std::endl;
      }
    }
   }
   else
   {
     DDSX11_TEST_INFO << "SUMMARY SENDER latency time:\n "
                           "No samples received back." << std::endl;
   }
}

void
TestExecutor::record_time (uint64_t receive_time)
{
  if (this->count_ < this->samples_)
  {
    uint64_t interval = receive_time - this->start_time_;
    uint64_t duration = interval - this->_clock_overhead_;
    this->duration_times_[this->count_] = duration;
    ++this->count_;
    this->sigma_duration_squared_ += (double)duration * (double)duration;
    this->tv_total_ += duration;
    if (duration > this->tv_max_ || this->tv_max_ == 0L)
    {
      this->tv_max_ = duration;
    }
    if (duration < this->tv_min_ || this->tv_min_ == 0L)
    {
      this->tv_min_ = duration;
    }
  }
  else
  {
    DDSX11_TEST_ERROR << "Sender::record_time : received exceed sample number (" <<
                          this->count_ << "<>" << this->samples_ << "; " << this->number_of_msg_ << ")" << std::endl;
  }
}

void
TestExecutor::calculate_clock_overhead (void)
{
  int num_of_loops_clock = 320;
  uint64_t begin_time = 0;
  uint64_t clock_roundtrip_time = 0;
  ACE_High_Res_Timer::gettimeofday_hr ().to_usec (begin_time);
  for (int i = 0; i < num_of_loops_clock; ++i)
    {
      ACE_High_Res_Timer::gettimeofday_hr ().to_usec (clock_roundtrip_time);
    }
  uint64_t total_time =  clock_roundtrip_time - begin_time;
  this->_clock_overhead_ = (long)(total_time / num_of_loops_clock);
}

void
TestExecutor::init_values (void)
{
  this->duration_times_.reset (new uint64_t[this->samples_]);
  this->iteration_results_.reset (new IterationResult[this->iterations_]);

  // make instances of Topic
  this->latency_sample_.seq_num (0);
  this->latency_sample_.data ().resize (this->sample_size_);
  calculate_clock_overhead ();
}

void
TestExecutor::start ()
{
  ACE_Event_Handler_var evh =
      ACE::make_event_handler<TickerHandler> (this, false);

  this->timer_id_ = ACE_Reactor::instance ()->schedule_timer(
      evh.handler(),
      nullptr,
      ACE_Time_Value (this->rate_ / 1000000, this->rate_ % 1000000),
      ACE_Time_Value (this->rate_ / 1000000, this->rate_ % 1000000));
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

  if (rd)
  {
    if (this->read_one_)
    {
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
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
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
          uint64_t  receive_time = 0;
          ACE_High_Res_Timer::gettimeofday_hr ().to_usec (receive_time);
          this->executor_->read(const_cast<Test::LatencyData&> (datum), receive_time);
        }
      }
    }
    else
    {
      ::DDS::SampleInfoSeq sample_info;
      Test::LatencyDataSeq dataseq;
      DDS::ReturnCode_t const retcode = rd->take(dataseq,
                                                 sample_info,
                                                 ::DDS::LENGTH_UNLIMITED,
                                                 ::DDS::NOT_READ_SAMPLE_STATE,
                                                 ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
                                                 ::DDS::ANY_INSTANCE_STATE);
      if (retcode == DDS::RETCODE_NO_DATA)
      {
        DDSX11_TEST_ERROR << "LatencyDataListener::on_data_available: No data available!"
                          << std::endl;
      }
      else if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "LatencyDataListener::on_data_available: Unable to take data from data reader, error "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
      }
      else
      {
        Test::LatencyDataSeq::size_type topic_idx {};
        for (DDS::SampleInfo info : sample_info)
        {
          if (info.valid_data ())
          {
            if ( (info.instance_state () == ::DDS::ALIVE_INSTANCE_STATE &&
                    info.view_state () == ::DDS::NEW_VIEW_STATE)
                || ((info.instance_state () == ::DDS::ALIVE_INSTANCE_STATE &&
                        info.view_state () == ::DDS::NOT_NEW_VIEW_STATE) ||
                     info.instance_state () == ::DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE))
            {
              uint64_t  receive_time = 0;
              ACE_High_Res_Timer::gettimeofday_hr ().to_usec (receive_time);
              this->executor_->read(const_cast<Test::LatencyData&> (dataseq[topic_idx]), receive_time);
            }
          }
        }
      }
    }
  }
  else
  {
    DDSX11_TEST_ERROR << "LatencyDataListener::on_data_available: no data reader"
                      << std::endl;
  }
}


int
TickerHandler::handle_timeout (
    const ACE_Time_Value&,
    const void*)
{
  if (this->executor_)
  {
    if (this->startup_)
      this->executor_->check_status ();
    else
      this->executor_->tick ();
  }
  return 0;
}
