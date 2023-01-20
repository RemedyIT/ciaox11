// -*- C++ -*-
/**
 * @file    psl_deadline_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the deadline missed callback on
 *          the Port Status Listener.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psl_deadline_sender_impl.cpp[Header]

#include "psl_deadline_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[user_global_impl]

namespace PSL_DeadlineTest_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
    public:
    explicit TT_Callback (IDL::traits<::PSL_DeadlineTest::CCM_Sender>::weak_ref_type component_executor)
                  : component_executor_(component_executor)
    {}

    void
    on_trigger (
        IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

    private:
      IDL::traits<::PSL_DeadlineTest::CCM_Sender>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
       IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
       const ::CCM_TT::TT_Duration& time,
       uint32_t round)
  {
    X11_UNUSED_ARG(time);
    X11_UNUSED_ARG(round);
    X11_UNUSED_ARG(timer);
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::tick ()
  {
    IDL::traits<::CommonTestConnector::Writer>::ref_type writer =
      this->context_->get_connection_writer_data ();

    try
    {
      for (uint16_t i = 0; i < 2; ++i)
      {
        writer->write_one (CommonTestMessage ("ONE", i), ::DDS::HANDLE_NIL);
      }
      for (uint16_t i = 0; i < 2; ++i)
      {
        writer->write_one (CommonTestMessage ("TWO", i), ::DDS::HANDLE_NIL);
      }
    }
    catch (const CCM_DDS::InternalError& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Internal Error while writing sample to DDS: "
        << ex << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_private_ops]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ccm_activate]
    // deadline period in QoS is set to two so the reader expects data every
    // two seconds. Setting the interval to somewhat more than two seconds,
    // the reader should (almost) always receive an on_requested_deadline_missed
    // callback from DDS.
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
            this->tm_ = tt_s->schedule_repeated_trigger (
                               CORBA::make_reference<TT_Callback> (IDL::traits< PSL_DeadlineTest::CCM_Sender>::narrow (this->_lock())),
                               CCM_TT::TT_Duration (2, 500000000),
                               CCM_TT::TT_Duration (2, 500000000),
                               0);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (!this->tm_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                            "Test did not start, because no DDS::PUBLICATION_MATCHED_STATUS was received "
                            "via info_out_connector_status_exec_i::on_unexpected_status ."  << std::endl;
    }
    else
    {
      if (!this->tm_->is_canceled())
      {
        this->tm_->cancel();
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
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<PSL_DeadlineTest::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[user_namespace_end_impl]

} // namespace PSL_DeadlineTest_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[factory]
extern "C" void
create_PSL_DeadlineTest_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <PSL_DeadlineTest_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
