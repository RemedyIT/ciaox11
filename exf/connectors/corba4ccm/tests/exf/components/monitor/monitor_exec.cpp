// -*- C++ -*-
/*
 * @file    monitor_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : monitor_impl.cpp[Header]

#include "monitor_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <thread>
#include <iomanip>
//@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[user_global_impl]

namespace App_Monitor_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[user_namespace_impl]
  void
  TT_Monitor::on_trigger (
      IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    CIAOX11_TEST_TRACE << "TT_Monitor::on_trigger - timer[" << timer->id ()
                       << "] @ " << time.sec () << "."
                       << std::right << std::setfill('0') << std::setw(9)
                       << time.nanosec ()
                       << " #" << round
                       << " : " << this->location_ << std::endl;

    if (this->passivated_)
      return;

    // observe environment for 50 - 250 milliseconds
    std::this_thread::sleep_for (
        std::chrono::milliseconds (this->uniform_dist_(this->dre_)));

    // report environment change
    ::Data::Environment data {
      this->location_,
      std::time(0),
      37.5, 967.3, 60.23
    };

    try
    {
      this->context_->get_connection_my_recorder ()->submit_environment_data (data);

      this->msg_count_++;

      // schedule next trigger
      IDL::traits<CCM_TT::TT_Scheduler>::ref_type ts_mon = this->context_->get_connection_tt_monitor ();
      ts_mon->schedule_trigger (
          IDL::traits<::CCM_TT::TT_Handler>::narrow (this->_lock ()),
          CCM_TT::TT_Duration (0, 100000000));  // 100ms
    }
    catch (const CORBA::TRANSIENT&)
    {
      // ignore in non-active state when not using ExF
      if (this->passivated_ == false)
      {
        // for now always ignore
        // CIAOX11_TEST_ERROR << "App::Monitor(" << this->location_ << "): caught exception [" << ex.what () << "]" << std::endl;
      }
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_ERROR << "App::Monitor(" << this->location_ << "): caught exception [" << ex.what () << "]" << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Monitor_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[ctor]
  Monitor_exec_i::Monitor_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[ctor]

  Monitor_exec_i::~Monitor_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[user_private_ops]

  /** Session component operations */
  void Monitor_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[configuration_complete]
  }

  void Monitor_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[ccm_activate]
    this->tt_mon_ = CORBA::make_reference<TT_Monitor> (this->location_, this->context_);
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type ts_mon = this->context_->get_connection_tt_monitor ();
    ts_mon->schedule_trigger (
        this->tt_mon_,
        CCM_TT::TT_Duration (0, 1000000));  // 1ms

    CIAOX11_TEST_INFO << "App::Monitor(" << this->location_ << "): activated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[ccm_activate]
  }

  void Monitor_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[ccm_passivate]
    this->tt_mon_->passivate ();
    CIAOX11_TEST_INFO << "App::Monitor(" << this->location_ << "): passivated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[ccm_passivate]
  }

  void Monitor_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "App::Monitor(" << this->location_ << "): " << this->tt_mon_->message_count () << " messages sent" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[ccm_remove]
  }


  std::string
  Monitor_exec_i::location ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i::location[getter]
    return this->location_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i::location[getter]
  }

  void
  Monitor_exec_i::location (
      const std::string& location)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i::location[setter]
    this->location_ = location;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i::location[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Monitor_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[set_session_context]
    this->context_ = IDL::traits<::App::CCM_Monitor_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[user_namespace_end_impl]

} // namespace App_Monitor_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[factory]
extern "C" void
create_App_Monitor_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <App_Monitor_Impl::Monitor_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : monitor_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
