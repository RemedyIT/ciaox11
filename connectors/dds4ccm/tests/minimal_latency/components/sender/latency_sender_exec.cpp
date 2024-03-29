// -*- C++ -*-
/**
 * @file    latency_sender_exec.cpp
 * @author  Martin Corino
 *
 * @brief   Sender component implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : latency_sender_impl.cpp[Header]

#include "latency_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "ace/High_Res_Timer.h"
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_global_impl]
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_global_impl]

namespace Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_impl]
  class TT_Callback final : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit
    TT_Callback (
        IDL::traits<Sender_exec_i>::ref_type component_executor,
        bool activate)
      : component_executor_ (std::move (component_executor))
      , activate_ (activate)
    {
    }

    void
    on_trigger (IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
                const ::CCM_TT::TT_Duration &time, uint32_t round) override;

    void
    shutdown ();

  private:
    IDL::traits<Sender_exec_i>::ref_type component_executor_;
    bool const activate_;
  };

  void
  TT_Callback::on_trigger (IDL::traits<::CCM_TT::TT_Timer>::ref_type /*timer*/,
                           const ::CCM_TT::TT_Duration& /*time*/,
                           uint32_t /*round*/)
  {
    if (this->component_executor_)
    {
      if (this->activate_)
        this->component_executor_->check_status ();
      else
        this->component_executor_->tick ();
    }
  }

  void
  TT_Callback::shutdown ()
  {
    this->component_executor_.reset ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_recv_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_data_listener_exec_i[ctor]
  info_recv_data_listener_exec_i::info_recv_data_listener_exec_i (
    IDL::traits<::Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<::Test::CCM_Sender>::ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move (component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_data_listener_exec_i[ctor]

  info_recv_data_listener_exec_i::~info_recv_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_data_listener_exec_i[user_public_ops]
  void
  info_recv_data_listener_exec_i::shutdown ()
  {
    this->component_executor_.reset ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_recv_data_listener */

  void
  info_recv_data_listener_exec_i::on_one_data (
      const ::Test::LatencyData& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_data_listener_exec_i::on_one_data[_datum_info]
    //DDS4CCM_TEST_DEBUG << "info_recv_data_listener_exec_i::on_one_data : " << std::endl <<
    //                      " datum:" << datum << std::endl <<
    //                      " info:" << DDS::dds_write(info) << std::endl;

    if (info.instance_status() == ::CCM_DDS::InstanceStatus::INSTANCE_CREATED
        || info.instance_status() == ::CCM_DDS::InstanceStatus::INSTANCE_UPDATED)
    {
      uint64_t  receive_time = 0;
      ACE_High_Res_Timer::gettimeofday_hr ().to_usec (receive_time);
      if (this->component_executor_)
      {
        IDL::traits<Sender_exec_i>::narrow(this->component_executor_)->read(const_cast<Test::LatencyData&> (datum), receive_time);
      }
      else
      {
        DDS4CCM_TEST_WARNING << "info_recv_data_listener_exec_i::on_one_data - "
                             << "WARNING: failed to lock component executor" << std::endl;
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_recv_data_listener_exec_i::on_many_data (
      const ::Test::LatencyDataSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_recv_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_status_exec_i[ctor]
  info_recv_status_exec_i::info_recv_status_exec_i (
    IDL::traits<::Test::CCM_Sender_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_status_exec_i[ctor]

  info_recv_status_exec_i::~info_recv_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_status_exec_i[user_private_ops]


  /** Operations and attributes from info_recv_status */

  void
  info_recv_status_exec_i::on_requested_deadline_missed (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_recv_status_exec_i::on_sample_lost (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<::Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<::Test::CCM_Sender>::ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move (component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i[user_public_ops]
  void
  connector_status_exec_i::shutdown ()
  {
    this->component_executor_.reset ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits<::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits<::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits<::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits<::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // started_ flag.
    if (!this->started_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 1))
      {
        if (this->component_executor_)
        {
          this->started_ = true;
          IDL::traits<Sender_exec_i>::narrow (this->component_executor_)->start_publishing ();
        }
        return;
      }
    }
    if (this->component_executor_)
    {
      IDL::traits<Sender_exec_i>::narrow (this->component_executor_)->inc_unexpected_count ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
    : rate_(100)
    , samples_ (10000)
    , iterations_ (10)
    , uses_context_switch_ (true)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::check_status ()
  {
    IDL::traits<::DDS::DataWriter>::ref_type writer_dds_entity =
      this->context_->get_connection_info_write_dds_entity ();
    if (writer_dds_entity)
    {
      ::DDS::PublicationMatchedStatus status {};
      ::DDS::ReturnCode_t const retcode = writer_dds_entity->get_publication_matched_status (status);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_TEST_ERROR <<"Sender_exec_i::check_status - "
          << "Error: Unable to get_publication_matched_status: <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched current_count: "
                         << status.current_count() << std::endl;

        if (status.current_count() == 1)
        {
          DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched received" << std::endl;
          this->start_publishing();
        }
      }
    }
  }

  void
  Sender_exec_i::start_publishing ()
  {
    if (!this->already_publishing_)
    {
      this->already_publishing_ = true;

      this->tm_activate_->cancel();

      this->start ();
    }
  }

  void
  Sender_exec_i::tick ()
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
          this->tm_->cancel ();
          this->calc_results ();
          ACE_High_Res_Timer::gettimeofday_hr ().to_usec (this->end_time_test_);
          // signal that we are finished
          std::ofstream ostrm("FINISHED", std::ios::binary);
          ostrm << 1;
          ostrm.close();
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
        try
        {
          this->test_topic_.seq_num (this->number_of_msg_);

          // Keep last sent seq_num, to control if message is sent back.
          this->seq_num_ = this->number_of_msg_;
          this->received_ = false;
          ACE_High_Res_Timer::gettimeofday_hr ().to_usec (this->start_time_);
          this->writer_->write_one (this->test_topic_, ::DDS::HANDLE_NIL);
        }
        catch (const CCM_DDS::InternalError&)
        {
          DDS4CCM_TEST_ERROR << "ERROR: Internal Error "
              "while writing sample with sequence_number "
              << this->test_topic_.seq_num () << std::endl;
        }
        ++this->number_of_msg_;
      }
    }
  }

  void
  Sender_exec_i::read (Test::LatencyData & an_instance, uint64_t receive_time)
  {
    if (an_instance.seq_num () == this->seq_num_)
      {
        this->record_time (receive_time);
        this->received_ = true;
      }
  }

  void
  Sender_exec_i::inc_unexpected_count ()
  {
    ++this->unexpected_count_;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_private_ops]

  void
  Sender_exec_i::reset_results()
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
  Sender_exec_i::calc_results ()
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
        if (this->uses_context_switch_)
          DDS4CCM_TEST_INFO << std::endl <<
                               "YES, we're using a threadswitch (" << this->context_switch_type_ << ") between DDS and CCM" <<
                               std::endl;
        else
          DDS4CCM_TEST_INFO << std::endl <<
                               "NO, we're not using a threadswitch between DDS and CCM" <<
                               std::endl;
        DDS4CCM_TEST_INFO <<
         "Collecting statistics on " << this->count_ << " samples of a single long value" << std::endl <<
         "at a rate of 1 sample per " << this->rate_ << "usec." << std::endl <<
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
        DDS4CCM_TEST_INFO <<
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


          DDS4CCM_TEST_INFO <<
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
       DDS4CCM_TEST_INFO << "SUMMARY SENDER latency time:\n "
                             "No samples received back." << std::endl;
     }
  }

  void
  Sender_exec_i::record_time (uint64_t receive_time)
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
      DDS4CCM_TEST_ERROR << "Sender_exec_i::record_time : received exceed sample number (" <<
                            this->count_ << "<>" << this->samples_ << "; " << this->number_of_msg_ << ")" << std::endl;
    }
  }

  void
  Sender_exec_i::calculate_clock_overhead ()
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
  Sender_exec_i::init_values ()
  {
    this->duration_times_.reset (new uint64_t[this->samples_]);
    this->iteration_results_.reset (new IterationResult[this->iterations_]);

    // make instances of Topic
    this->test_topic_.seq_num (0);
    calculate_clock_overhead ();
  }

  void
  Sender_exec_i::start ()
  {
    try
    {
      if (this->tmh_)
      {
        IDL::traits<TT_Callback>::narrow(this->tmh_)->shutdown ();
      }
      this->tmh_ = IDL::traits<CCM_TT::TT_Handler>::make_reference<TT_Callback> (
          IDL::traits<Sender_exec_i>::narrow (this->_lock()), false);
      this->tm_ = tt_s->schedule_repeated_trigger (
                    this->tmh_,
                    CCM_TT::TT_Duration (this->rate_ / 1000000, (this->rate_ % 1000000) * 1000),
                    CCM_TT::TT_Duration (this->rate_ / 1000000, (this->rate_ % 1000000) * 1000),
                    0);
    }
    catch_dds4ccm_test_ex(ex, "Sender_exec_i::start")
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_activate]
    try
    {
      this->writer_ = this->context_->get_connection_info_write_data ();
      IDL::traits<::CCM_DDS::DataListenerControl>::ref_type dlc =
          this->context_->get_connection_info_recv_data_control ();
      dlc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);

      this->init_values();

      this->tt_s = this->context_->get_connection_tt_scheduler ();
      this->tmh_ = IDL::traits<CCM_TT::TT_Handler>::make_reference<TT_Callback> (
          IDL::traits<Sender_exec_i>::narrow (this->_lock()), true);
      this->tm_activate_ = this->tt_s->schedule_repeated_trigger (
                                this->tmh_,
                                CCM_TT::TT_Duration (0, 100000000),
                                CCM_TT::TT_Duration (0, 100000000),
                                0);
    }
    catch_dds4ccm_test_ex(ex, "Sender_exec_i::ccm_activate")
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (this->tmh_)
    {
      IDL::traits<TT_Callback>::narrow(this->tmh_)->shutdown ();
    }
    if (!this->tm_)
    {
       DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                             "Test did not start, because no DDS::PUBLICATION_MATCHED_STATUS was received."
                          << std::endl;
    }
    else
    {
      if (!this->tm_->is_canceled())
      {
        this->tm_->cancel();
      }
      if (this->info_recv_data_listener_)
      {
        IDL::traits<info_recv_data_listener_exec_i>::narrow(this->info_recv_data_listener_)->shutdown();
      }
      if (this->connector_status_)
      {
        IDL::traits<connector_status_exec_i>::narrow(this->connector_status_)->shutdown();
      }
      if (this->tm_->rounds() < 1)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                              "Timer of tests didn't tick." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_passivate - "
                             "Timer ticked " << this->tm_->rounds() << " times." << std::endl;
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_remove]
    if (this->count_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR SENDER: No run has taken place."
          << std::endl;
    }
    else if (this->count_ < this->samples_)
    {
      DDS4CCM_TEST_INFO << "SUMMARY SENDER : " << (this->iteration_nr_+1) << " of " << this->iterations_ << " iterations completed." << std::endl <<
                           " Number of messages sent in last iteration: " << this->number_of_msg_ << "; received: " << this->count_ << std::endl;
    }
    DDS4CCM_TEST_INFO << "\tNumber of unexpected events : " << (int32_t)this->unexpected_count_ << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits<::Test::LatencyDataConnector::CCM_Listener>::ref_type
  Sender_exec_i::get_info_recv_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[get_info_recv_data_listener]
    if (!this->info_recv_data_listener_)
    {
      this->info_recv_data_listener_ =
          IDL::traits<::Test::LatencyDataConnector::CCM_Listener>::make_reference <info_recv_data_listener_exec_i> (
              this->context_,
              IDL::traits<Test::CCM_Sender>::narrow (this->_lock()));
    }
    return this->info_recv_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[get_info_recv_data_listener]
  }

  IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type
  Sender_exec_i::get_info_recv_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[get_info_recv_status]
    if (!this->info_recv_status_)
    {
      this->info_recv_status_ =
          IDL::traits<::CCM_DDS::CCM_PortStatusListener>::make_reference <info_recv_status_exec_i> (
              this->context_);
    }
    return this->info_recv_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[get_info_recv_status]
  }

  IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[get_connector_status]
    if (!this->connector_status_)
    {
      this->connector_status_ =
          IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::make_reference <connector_status_exec_i> (
              this->context_,
              IDL::traits<Test::CCM_Sender>::narrow (this->_lock()));
    }
    return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[get_connector_status]
  }


  uint32_t
  Sender_exec_i::rate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::rate[getter]
    return this->rate_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::rate[getter]
  }

  void
  Sender_exec_i::rate (
      uint32_t rate)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::rate[setter]
    this->rate_ = rate;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::rate[setter]
  }

  uint32_t
  Sender_exec_i::samples ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::samples[getter]
    return this->samples_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::samples[getter]
  }

  void
  Sender_exec_i::samples (
      uint32_t samples)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::samples[setter]
    this->samples_ = samples;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::samples[setter]
  }

  uint32_t
  Sender_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::iterations[getter]
  }

  void
  Sender_exec_i::iterations (
      uint32_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::iterations[setter]
  }

  bool
  Sender_exec_i::uses_context_switch ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::uses_context_switch[getter]
    return this->uses_context_switch_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::uses_context_switch[getter]
  }

  void
  Sender_exec_i::uses_context_switch (
      bool uses_context_switch)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::uses_context_switch[setter]
    this->uses_context_switch_ = uses_context_switch;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::uses_context_switch[setter]
  }

  std::string
  Sender_exec_i::context_switch_type ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::context_switch_type[getter]
    return this->context_switch_type_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::context_switch_type[getter]
  }

  void
  Sender_exec_i::context_switch_type (
      const std::string& context_switch_type)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::context_switch_type[setter]
    this->context_switch_type_ = context_switch_type;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::context_switch_type[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<::Test::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_end_impl]

} // namespace Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[factory]
extern "C" void
create_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = IDL::traits<::Test::CCM_Sender>::make_reference < Test_Sender_Impl::Sender_exec_i > ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : latency_sender_impl.cpp[Footer]
// Your footer (code) here
