/**
 * @file    tt_test_exec.cpp
 * @author  Marijke Hengstmengel
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
    explicit TT_Callback (std::string desc, uint32_t max_calls = 0)
      : desc_ (std::move(desc)), max_calls_ (max_calls) {}

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

   IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s_1 = this->context_->get_connection_tt_scheduler_one ();
   this->tm_1 = tt_s_1->schedule_repeated_trigger (
        CORBA::make_reference<TT_Callback> ("tm_1 - repeated trigger: delay=1sec; interval=4000usec; autocancel after 10 iterations"),
        CCM_TT::TT_Duration (1, 0),
        CCM_TT::TT_Duration (0, 4000000),
        10);
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s_2 = this->context_->get_connection_tt_scheduler_two ();
    this->tm_2 = tt_s_2->schedule_repeated_trigger (
        CORBA::make_reference<TT_Callback> ("tm_2 - repeated trigger: delay=2sec; interval=3.001sec; manually cancelled at passivate"),
        CCM_TT::TT_Duration (2, 0),
        CCM_TT::TT_Duration (3, 1000000),
        0);
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s_3 = this->context_->get_connection_tt_scheduler_one ();
    this->tm_3 = tt_s_3->schedule_trigger (
        CORBA::make_reference<TT_Callback> ("tm_3 - trigger once: delay=4sec; autocancel after one triggger"),
        CCM_TT::TT_Duration (4, 0)
     // ,  CCM_TT::TT_Duration (0, 100000),0
        );
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s_4 = this->context_->get_connection_tt_scheduler_two ();
        this->tm_4 = tt_s_4->schedule_repeated_trigger (
            CORBA::make_reference<TT_Callback> ("tm_4 - repeated trigger: delay=2sec; interval=3.001sec; manually cancelled at passivate"),
            CCM_TT::TT_Duration (2, 0),
            CCM_TT::TT_Duration (3, 1000000),
            0);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_activate]
  }

  void TT_Tester_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "TT_Tester_exec_i::ccm_passivate - cancelling triggers" << std::endl;

    if (!this->tm_1->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_1 should have auto cancelled" << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK: tm_1 auto cancelled" << std::endl;
    }
    if (this->tm_1->rounds () != 10)
    {
      CIAOX11_TEST_ERROR << "tm_1 should have triggered 10 times, found " << this->tm_1->rounds () << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK: tm_1 have triggered 10 times" << std::endl;
    }
    if (this->tm_2->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_2 should not have been cancelled yet" << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK, tm_2 is not yet cancelled, triggered " << this->tm_2->rounds () <<
          " times, going to cancel now" << std::endl;

      tm_2->cancel ();
    }
    if (!this->tm_3->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_3 should have been cancelled yet" << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK, tm_3 is cancelled, triggered " << this->tm_3->rounds () <<
          " times." << std::endl;
    }
    if (this->tm_4->is_canceled ())
    {
      CIAOX11_TEST_ERROR << "tm_4 should not have been cancelled yet" << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK, tm_4 is not yet cancelled, triggered " << this->tm_4->rounds () <<
          " times, going to cancel now" << std::endl;

      tm_4->cancel ();
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
