// -*- C++ -*-
/**
 * @file    fa_rg_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the query condition test which
 *          tests two different queries.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : fa_rg_receiver_impl.cpp[Header]

#include "fa_rg_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[user_includes]
#include "dds4ccm/tests/filters/common/read_get/receiver/filters_common_receiver_rg_runner_t.h"
#include "dds4ccm/tests/common/common_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[user_global_impl]

// During the first run only sample 7 and 8 are to be received by the getter.
// During the second run, the samples between 4 and 14 (thus 5,6,7,8,9,10,11,12,
// and 13) are to be received by the getter.
// The rest of the samples are filtered out and are not available in DDS!! That
// means that NO samples of a previous run are to be read during the current run;
// these samples are either filtered out or read.
constexpr uint16_t expected_number_of_samples_on_getter_during_run_1 ()
{
  return 2 * keys ();
}

constexpr uint16_t expected_number_of_samples_on_getter_during_run_2 ()
{
  return 9 * keys ();
}

// Nothing is read during the third run so these samples are still in DDS during
// the fourth run. The filter which was set during the third run, applies to the
// samples read during the third run (the samples are filtered in and not read)
// during the third run.
// Thus all samples greater than four and less than 15 are read (5,6,7,8,9,10,11,
// 12,13, and 14).
// All samples are filtered in during the fourth run but *without* the ones
// of the last key. This is because there's a checker which checks whether the
// last sample is available in DDS. Since this reads all the samples of the last
// key, the getter will not receive these.
constexpr uint16_t number_of_unread_sample_getter_during_run_3 ()
{
  return 10 * keys ();
}

// No samples are read during the fourth run (they are all filtered out)
constexpr uint16_t number_of_read_sample_getter_during_run_4 ()
{
  return keys () * iterations ();
}


// During the first run all samples except 6,7,8, and 9 are to be received by the reader
// During the second run, just 1,2, and 3 and 15 are to be received by the reader + all
// samples from the first run again. Since all samples are kept in DDS, the reader reads
// all samples again with the original filter parameters applied.
// Plus one for KEY_6
constexpr uint16_t expected_number_of_samples_on_reader_during_run_1 ()
{
  return (iterations () - 4) * keys () + 1;
}
// KEY_6 is filtered out
constexpr uint16_t expected_number_of_samples_on_reader_during_run_2 ()
{
  return (4 * keys ()) + expected_number_of_samples_on_reader_during_run_1 () - 1;
}

// During the third run only the last sample of each key will be received
// // Plus one for KEY_6
constexpr uint16_t expected_number_of_samples_on_reader_during_run_3 ()
{
  return 2 * keys () + 1;
}

// No samples during the fourth run (filtered out). Filtered in samples from
// the third (3 per key) run should be counted
constexpr uint16_t expected_number_of_samples_on_reader_during_run_4 ()
{
  return expected_number_of_samples_on_reader_during_run_2 () + (3 * keys ()) + 4;
}


// Now calculate the total number of samples that is expected on the receiver
constexpr uint16_t expected_number_of_samples_on_getter ()
{
  return expected_number_of_samples_on_getter_during_run_1 () +
    expected_number_of_samples_on_getter_during_run_2 () +
    number_of_unread_sample_getter_during_run_3 () +
    number_of_read_sample_getter_during_run_4 ();
}

// Also KEY_6 will be received (1 during run 1, none during run 2 and
// one during run 3 and therefor 4 during run 4 )
constexpr uint16_t expected_number_of_samples_on_reader ()
{
  return expected_number_of_samples_on_reader_during_run_1 () +
    expected_number_of_samples_on_reader_during_run_2 () +
    expected_number_of_samples_on_reader_during_run_3 () +
    expected_number_of_samples_on_reader_during_run_4 ();
}

//@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[user_global_impl]

namespace FA_Read_Get_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
  :  public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::FA_Read_Get_Test::CCM_Receiver>::weak_ref_type component_executor)
                 : component_executor_(component_executor)
    {}

    virtual
    void
    on_trigger (
                IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
                const ::CCM_TT::TT_Duration& time,
                uint32_t round) override;

  private:
    IDL::traits< ::FA_Read_Get_Test::CCM_Receiver>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
           IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
           const ::CCM_TT::TT_Duration& time,
           uint32_t round)
  {
    X11_UNUSED_ARG(time);
    X11_UNUSED_ARG(round);
    X11_UNUSED_ARG(timer);
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : get_port_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[ctor]
  get_port_status_exec_i::get_port_status_exec_i (
    IDL::traits<FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[ctor]

  get_port_status_exec_i::~get_port_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_private_ops]


  /** Operations and attributes from get_port_status */

  void
  get_port_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_requested_deadline_missed get - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  get_port_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_sample_lost get - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : listen_port_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[ctor]
  listen_port_data_listener_exec_i::listen_port_data_listener_exec_i (
    IDL::traits<FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[ctor]

  listen_port_data_listener_exec_i::~listen_port_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from listen_port_data_listener */

  void
  listen_port_data_listener_exec_i::on_one_data (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  listen_port_data_listener_exec_i::on_many_data (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : listen_port_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[ctor]
  listen_port_status_exec_i::listen_port_status_exec_i (
    IDL::traits<FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[ctor]

  listen_port_status_exec_i::~listen_port_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_private_ops]


  /** Operations and attributes from listen_port_status */

  void
  listen_port_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_requested_deadline_missed listen - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  listen_port_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_sample_lost listen - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : start_reading_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[ctor]
  start_reading_exec_i::start_reading_exec_i (
    IDL::traits<FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context,
    IDL::traits<FA_Read_Get_Test::CCM_Receiver>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[ctor]

  start_reading_exec_i::~start_reading_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_private_ops]


  /** Operations and attributes from start_reading */

  void
  start_reading_exec_i::start_read ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i::start_read[void]
    DDS4CCM_TEST_DEBUG << "start_reading_exec_i::start_read " << std::endl;

    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->run ();
    else
    {
      DDS4CCM_TEST_ERROR << "start_reading_exec_i::start_read - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i::start_read[void]
  }

  void
  start_reading_exec_i::start_new_run (
      uint16_t run)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i::start_new_run[_run]
    X11_UNUSED_ARG(run);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i::start_new_run[_run]
  }

  void
  start_reading_exec_i::set_reader_properties (
      uint16_t nr_keys,
      uint16_t nr_iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i::set_reader_properties[_nr_keys_nr_iterations]
    X11_UNUSED_ARG(nr_keys);
    X11_UNUSED_ARG(nr_iterations);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i::set_reader_properties[_nr_keys_nr_iterations]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  void
  Receiver_exec_i::tick ()
  {
    if (!this->last_get)
    {
      this->last_get = DDS4CCM_TEST_UTILS::check_last (
              this->context_->get_connection_get_port_data (), keys () + 1, 1);
    }
    if (!this->last_listen)
    {
      this->last_listen = DDS4CCM_TEST_UTILS::check_last (
            this->context_->get_connection_listen_port_data (), keys () + 1, 1);
    }
    if (this->last_get && this->last_listen)
    {
      this->tm_->cancel();
      this->notify ();
    }
  }

  void
  Receiver_exec_i::notify ()
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::notify " << std::endl;
    //reset last_get and last_listen for the next start_write run
    this->last_get = false;
    this->last_listen = false;
    uint32_t read_before_run_getter = this->received_4_getter_;
    uint32_t read_before_run_reader = this->received_4_reader_;

    ReadGetReceiverRunner_T<FA_Read_Get_Test::CCM_Receiver_Context, false> runner (
      this->context_, this->run_);
    this->run_ = runner.run ();
    runner.get_received (this->received_4_getter_, this->received_4_reader_);

    uint16_t run_to_check = this->run_ - 1;
    uint32_t read_during_run_getter = this->received_4_getter_ - read_before_run_getter;
    uint32_t read_during_run_reader = this->received_4_reader_ - read_before_run_reader;

    switch (run_to_check)
    {
      case 1:
        if (read_during_run_getter != expected_number_of_samples_on_getter_during_run_1 ())
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::notify - "
            << "Unexpected number of samples read on Getter during run <"
            << run_to_check << ">: expected <"
            << expected_number_of_samples_on_getter_during_run_1 ()
            << "> - read <" << read_during_run_getter << ">."
            << std::endl;
        }
        if (read_during_run_reader != expected_number_of_samples_on_reader_during_run_1 ())
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::notify - "
            << "Unexpected number of samples read on Reader during run <"
            << run_to_check << ">: expected <"
            << expected_number_of_samples_on_reader_during_run_1 ()
            << "> - read <" << read_during_run_reader << ">."
            << std::endl;
        }
        break;
      case 2:
        if (read_during_run_getter != expected_number_of_samples_on_getter_during_run_2 ())
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::notify - "
            << "Unexpected number of samples read on Getter during run <"
            << run_to_check << ">: expected <"
            << expected_number_of_samples_on_getter_during_run_2 ()
            << "> - read <" << read_during_run_getter << ">."
            << std::endl;
        }
        if (read_during_run_reader != expected_number_of_samples_on_reader_during_run_2 ())
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::notify - "
            << "Unexpected number of samples read on Reader during run <"
            << run_to_check << ">: expected <"
            << expected_number_of_samples_on_reader_during_run_2 ()
            << "> - read <" << read_during_run_reader << ">."
            << std::endl;
        }
        break;
      case 3:
        if (read_during_run_reader != expected_number_of_samples_on_reader_during_run_3 ())
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::notify - "
            << "Unexpected number of samples read on Reader during run <"
            << run_to_check << ">: expected <"
            << expected_number_of_samples_on_reader_during_run_3 ()
            << "> - read <" << read_during_run_reader << ">."
            << std::endl;
        }
        break;
      case 4:
        {
          uint32_t expected_on_getter =
              number_of_unread_sample_getter_during_run_3 () +
            number_of_read_sample_getter_during_run_4 ();
          if (read_during_run_getter != expected_on_getter)
          {
            DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::notify - "
              << "Unexpected number of samples read on Getter during run <"
              << run_to_check << ">: expected <"
              << expected_on_getter
              << "> - read <" << read_during_run_getter << ">."
              << std::endl;
          }
          if (read_during_run_reader != expected_number_of_samples_on_reader_during_run_4 ())
          {
            DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::notify - "
              << "Unexpected number of samples read on Reader during run <"
              << run_to_check << ">: expected <"
              << expected_number_of_samples_on_reader_during_run_4 ()
              << "> - read <" << read_during_run_reader << ">."
              << std::endl;
          }
        }
        break;
      default:
        break;
    }
  }

  void
  Receiver_exec_i::run ()
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::run " << std::endl;
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    this->tm_ = tt_s->schedule_repeated_trigger (
                          CORBA::make_reference<TT_Callback> (IDL::traits< FA_Read_Get_Test::CCM_Receiver>::narrow (this->_lock())),
                          CCM_TT::TT_Duration (1, 0),
                          CCM_TT::TT_Duration (1, 0),
                          0);


  }
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate " << std::endl;
    IDL::traits< ::CommonTestConnector::Getter >::ref_type getter =
      this->context_->get_connection_get_port_fresh_data ();
    getter->time_out (DDS::Duration_t (2, 0));

    ReadGetReceiverRunner_T<FA_Read_Get_Test::CCM_Receiver_Context, false> runner (this->context_);
    runner.pre_start_checks ();
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->tm_ && !this->tm_->is_canceled())
    {
      this->tm_->cancel ();
    }

    bool error = false;

    if (this->received_4_getter_ != expected_number_of_samples_on_getter ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of samples received for the Getter: "
        << "expected <" << expected_number_of_samples_on_getter ()
        << "> - got <" << this->received_4_getter_ << ">." << std::endl;
      error = true;
    }

    if (this->received_4_reader_ != expected_number_of_samples_on_reader ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of samples received for the Reader: "
        << "expected <" << expected_number_of_samples_on_reader ()
        << "> - got <" << this->received_4_reader_ << ">." << std::endl;
      error = true;
    }
    if (!error)
    {
      DDS4CCM_TEST_DEBUG << "OK: Receiver_exec_i::ccm_passivate - "
        << "Received the expected number of samples."
        << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_get_port_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_get_port_status]
  if (!this->get_port_status_)
  {
    this->get_port_status_ = CORBA::make_reference <get_port_status_exec_i> (this->context_);
  }
  return this->get_port_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_get_port_status]
  }

  IDL::traits< ::CommonTestConnector::CCM_Listener >::ref_type
  Receiver_exec_i::get_listen_port_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_data_listener]
  if (!this->listen_port_data_listener_)
  {
    this->listen_port_data_listener_ = CORBA::make_reference <listen_port_data_listener_exec_i> (this->context_);
  }
  return this->listen_port_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_listen_port_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_status]
  if (!this->listen_port_status_)
  {
    this->listen_port_status_ = CORBA::make_reference <listen_port_status_exec_i> (this->context_);
  }
  return this->listen_port_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_status]
  }

  IDL::traits< CCM_ReaderStarter >::ref_type
  Receiver_exec_i::get_start_reading ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_start_reading]
  if (!this->start_reading_)
  {
    this->start_reading_ =
      CORBA::make_reference <start_reading_exec_i> (
        this->context_, IDL::traits<FA_Read_Get_Test::CCM_Receiver>::narrow (this->_lock()));
  }
  return this->start_reading_;
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[get_start_reading]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<FA_Read_Get_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace FA_Read_Get_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[factory]
extern "C" void
create_FA_Read_Get_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : fa_rg_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
