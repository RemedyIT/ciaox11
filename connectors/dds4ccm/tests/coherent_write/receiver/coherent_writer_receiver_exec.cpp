// -*- C++ -*-
/**
 * @file    coherent_writer_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : coherent_writer_receiver_impl.cpp[Header]

#include "coherent_writer_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[user_includes]
#include "dds4ccm/tests/common/common_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[user_global_impl]

namespace CoherentWriter_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits< ::CoherentWriter::CCM_Receiver>::weak_ref_type component_executor)
    : component_executor_(component_executor)
    {}

    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits< ::CoherentWriter::CCM_Receiver>::weak_ref_type component_executor_;
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
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<CoherentWriter::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : start_reading_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[ctor]
  start_reading_exec_i::start_reading_exec_i (
    IDL::traits<CoherentWriter::CCM_Receiver_Context>::ref_type context,
    IDL::traits<CoherentWriter::CCM_Receiver>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[ctor]

  start_reading_exec_i::~start_reading_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_private_ops]


  /** Operations and attributes from start_reading */

  void
  start_reading_exec_i::start_read ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i::start_read[void]
    // Your code here.
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i::start_read[void]
  }

  void
  start_reading_exec_i::start_new_run (
      uint16_t run)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i::start_new_run[_run]
    auto cex = IDL::traits< Receiver_exec_i >::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->start_read (run);
    }
    else
    {
      DDS4CCM_TEST_ERROR << "start_reading_exec_i::start_new_run - "
        << "ERROR: failed to lock component executor." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i::start_new_run[_run]
  }

  void
  start_reading_exec_i::set_reader_properties (
      uint16_t nr_keys,
      uint16_t nr_iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i::set_reader_properties[_nr_keys_nr_iterations]
    X11_UNUSED_ARG(nr_keys);

    auto cex = IDL::traits< Receiver_exec_i >::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->iterations (nr_iterations);
    }
    else
    {
      DDS4CCM_TEST_ERROR << "start_reading_exec_i::set_reader_properties - "
        << "ERROR: failed to lock component executor." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i::set_reader_properties[_nr_keys_nr_iterations]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_public_ops]
  void Receiver_exec_i::start_read (uint16_t run)
  {
    this->run_ = run;
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    this->tm_ = tt_s->schedule_repeated_trigger (
                       CORBA::make_reference<TT_Callback> (IDL::traits< CoherentWriter::CCM_Receiver>::narrow (this->_lock())),
                       CCM_TT::TT_Duration (1, 0),
                       CCM_TT::TT_Duration (1, 0),
                       0);
   }

  void Receiver_exec_i::tick ()
  {
    // Use get_many for every even number. In that case, don't check whether
    // the last sample has arrived since the samples are read by then (the
    // getter only reads unread samples).
    if (DDS4CCM_TEST_UTILS::check_last (
      this->context_->get_connection_info_get_data (), 2, this->run_))
    {
        this->tm_->cancel();
        if (this->run_ % 2 == 1)
          this->read_all ();
        else
          this->get_all ();
    }
  }

  void Receiver_exec_i::iterations (int32_t iterations)
  {
    this->iterations_ = iterations;
  }

  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_private_ops]
  void
  Receiver_exec_i::check_iters (std::string const &test,
    CommonTestMessageSeq const &msgs)
  {
    bool error {false};
    for (CommonTestMessage const &msg : msgs)
    {
      if (msg.iteration () > this->last_iter_)
      {
        if (msg.iteration () != ++this->last_iter_)
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_iters - "
            << test << " - expected iteration <" << this->last_iter_
            << "> - received <" << msg << ">." << std::endl;
          error = true;
        }
      }
    }
    if (!error)
    {
      if (this->run_ < this->nr_runs () + 1)
      {
        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::check_iters - "
          << "No errors found in read. Continue next run." << std::endl;
        try
        {
          IDL::traits< WriterStarter>::ref_type restarter =
            this->context_->get_connection_writer_start ();
          restarter->start_write ();
        }
        catch_dds4ccm_test_ex(ex, "Receiver_exec_i::check_iters")
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::check_iters - "
          << "Finished: wait for shutdown" << std::endl;
      }
    }
    else
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::check_iters - "
        << "Errors found in read. No need to advance to the next run. "
        << "Waiting for shutdown." << std::endl;
    }
  }


  void Receiver_exec_i::get_all ()
  {
    try
    {
      IDL::traits<CommonTestConnector::Getter>::ref_type getter =
        this->context_->get_connection_info_get_fresh_data ();

      CommonTestMessageSeq messages;
      ::CCM_DDS::ReadInfo readinfo;
      bool result = true;
      while (result)
      {
        CommonTestMessage msg;
        result = getter->get_one (msg, readinfo);
        if (result)
        {
          messages.push_back (msg);
        }
      }
      this->check_iters ("GET", messages);
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::get_all")
  }

  void Receiver_exec_i::read_all ()
  {
    try
    {
      IDL::traits<CommonTestConnector::Reader>::ref_type reader =
        this->context_->get_connection_info_get_data ();

      CommonTestMessageSeq coherentwrite_info_seq;
      ::CCM_DDS::ReadInfoSeq readinfo_seq;
      reader->read_one_all (CommonTestMessage ("KEY_1", 1),
        coherentwrite_info_seq, readinfo_seq, DDS::HANDLE_NIL);

      this->check_iters ("READ", coherentwrite_info_seq);
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::read_all")
  }

  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits<CommonTestConnector::Getter>::ref_type getter =
      this->context_->get_connection_info_get_fresh_data ();

    getter->time_out (DDS::Duration_t (2, 0));
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  }

  IDL::traits< CCM_ReaderStarter>::ref_type
  Receiver_exec_i::get_start_reading ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[get_start_reading]
  if (!this->start_reading_)
  {
    this->start_reading_ =
      CORBA::make_reference <start_reading_exec_i>
        (this->context_, IDL::traits<CoherentWriter::CCM_Receiver>::narrow (this->_lock()));
  }
  return this->start_reading_;
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[get_start_reading]
  }


  uint16_t
  Receiver_exec_i::nr_runs ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i::nr_runs[getter]
    return this->nr_runs_;
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i::nr_runs[getter]
  }

  void
  Receiver_exec_i::nr_runs (
      uint16_t nr_runs)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i::nr_runs[setter]
    this->nr_runs_ = nr_runs;
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i::nr_runs[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<CoherentWriter::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[user_namespace_end_impl]

} // namespace CoherentWriter_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[factory]
extern "C" void
create_CoherentWriter_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <CoherentWriter_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : coherent_writer_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
