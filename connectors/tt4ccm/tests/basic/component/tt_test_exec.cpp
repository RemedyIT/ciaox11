/**
 * @file    tt_test_exec.cpp
 * @author  Martin Corino
 *
 * @brief   Timed Trigger connector test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : tt_test_impl.cpp[Header]

#include "tt_test_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <iomanip>
//@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[user_global_impl]

namespace Test_TT_Tester_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[user_namespace_impl]
  class TT_Callback final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (std::string desc, uint32_t max_calls = 0)
      : desc_ (desc), max_calls_ (max_calls) {}

    virtual
    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    std::string desc_;
    uint32_t max_calls_;
  };

  void
  TT_Callback::on_trigger (
      IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    CIAOX11_TEST_INFO << "TT_Callback::on_trigger - timer[" << timer->id ()
                      << "] @ " << time.sec () << "."
                      << std::right << std::setfill('0') << std::setw(9)
                      << time.nanosec ()
                      << " #" << round
                      << " : " << this->desc_ << std::endl;

    if (this->max_calls_ > 0 && round >= this->max_calls_)
    {
      CIAOX11_TEST_INFO << "TT_Callback::on_trigger - timer[" << timer->id ()
                        << "] cancelling after reaching max calls : "
                        << this->max_calls_ << std::endl;

      timer->cancel ();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : TT_Tester_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[ctor]
  TT_Tester_exec_i::TT_Tester_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[ctor]

  TT_Tester_exec_i::~TT_Tester_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[user_private_ops]

  /** Session component operations */
  void TT_Tester_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[configuration_complete]
  }

  void TT_Tester_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "TT_Tester_exec_i::ccm_activate - scheduling triggers" << std::endl;

    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    this->tm_1 = tt_s->schedule_repeated_trigger (
        CORBA::make_reference<TT_Callback> ("tm_1 - repeated trigger: delay=3sec; interval=50usec; autocancel after 20 iterations"),
        CCM_TT::TT_Duration (3, 0),
        CCM_TT::TT_Duration (0, 50000),
        20);

    this->tm_2 = tt_s->schedule_repeated_trigger (
        CORBA::make_reference<TT_Callback> ("tm_2 - repeated trigger: delay=3sec; interval=500msec; manually cancelled at passivate"),
        CCM_TT::TT_Duration (3, 0),
        CCM_TT::TT_Duration (0, 500000000),
        0);

    this->tm_3 = tt_s->schedule_repeated_trigger (
        CORBA::make_reference<TT_Callback> ("tm_3 - repeated trigger: delay=3sec; interval=60usec; manually cancel after 20 iterations", 20),
        CCM_TT::TT_Duration (3, 0),
        CCM_TT::TT_Duration (0, 60000),
        0);

    this->tm_4 = tt_s->schedule_trigger (
        CORBA::make_reference<TT_Callback> ("tm_4 - single trigger: delay=5sec"),
        CCM_TT::TT_Duration (5, 0));

    this->tm_5 = tt_s->schedule_repeated_trigger (
        CORBA::make_reference<TT_Callback> ("tm_5 - repeated trigger: delay=6sec; interval=1sec; open ended"),
        CCM_TT::TT_Duration (6, 0),
        CCM_TT::TT_Duration (1, 0),
        0);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_activate]
  }

  void TT_Tester_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "TT_Tester_exec_i::ccm_activate - cancelling triggers" << std::endl;

    if (!this->tm_1->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_1 should have auto cancelled" << std::endl;
    }
    if (this->tm_1->rounds () != 20)
    {
      CIAOX11_TEST_ERROR << "tm_1 should have triggered 20 times, found " << this->tm_1->rounds () << std::endl;
    }

    if (this->tm_2->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_2 should not have been cancelled yet" << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "cancelling tm_2" << std::endl;

      tm_2->cancel ();
    }

    if (!this->tm_3->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_3 should have been cancelled" << std::endl;
    }
    if (this->tm_3->rounds () != 20)
    {
      CIAOX11_TEST_ERROR << "tm_3 should have triggered 20 times, found " << this->tm_3->rounds () << std::endl;
    }

    if (!this->tm_4->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_4 should have been cancelled" << std::endl;
    }
    if (this->tm_4->rounds () != 1)
    {
      CIAOX11_TEST_ERROR << "tm_4 should have triggered 1 time, found " << this->tm_4->rounds () << std::endl;
    }

    if (this->tm_5->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_5 should not have been cancelled" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_passivate]
  }

  void TT_Tester_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  TT_Tester_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Test::CCM_TT_Tester_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[user_namespace_end_impl]

} // namespace Test_TT_Tester_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[factory]
extern "C" void
create_Test_TT_Tester_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Test_TT_Tester_Impl::TT_Tester_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : tt_test_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
