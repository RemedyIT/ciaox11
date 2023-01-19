// -*- C++ -*-
/*
 * @file    monitor_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_MONITOR_EXEC_H_CBFCGIGE_INCLUDED__
#define __RIDL_MONITOR_EXEC_H_CBFCGIGE_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : monitor_impl.h[Header]

#pragma once

#include "monitorEC.h"

#include /**/ "exftest_monitor_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : monitor_impl.h[user_includes]
#include <random>
#include <ctime>
//@@{__RIDL_REGEN_MARKER__} - END : monitor_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : monitor_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : monitor_impl.h[user_global_decl]

/// Namespace for implementation of App::Monitor component
namespace App_Monitor_Impl
{
  /// Forward declarations
  class Monitor_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[user_namespace_decl]
  //============================================================
  // Monitor trigger callback
  //============================================================
  class TT_Monitor final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Monitor (std::string loc, IDL::traits< ::App::CCM_Monitor_Context>::ref_type context)
      : location_ (std::move(loc)),
        context_ (std::move(context)),
        dre_ (std::random_device ()()),
        uniform_dist_ (50, 250)
    {
    }

    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

    uint32_t message_count () const
    { return this->msg_count_; }

    void passivate ()
    { this->passivated_ = true; }

  private:
    std::string location_;
    bool passivated_ {};
    IDL::traits< ::App::CCM_Monitor_Context>::ref_type context_;
    std::default_random_engine dre_;
    std::uniform_int_distribution<int> uniform_dist_;
    uint32_t msg_count_ {};
  };
  //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Monitor_exec_i
  class Monitor_exec_i final
    : public virtual IDL::traits<::App::CCM_Monitor>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[ctor]
    /// Constructor
    Monitor_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[ctor]
    /// Destructor
    ~Monitor_exec_i () override;

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute location
    std::string location () override;
    void location (const std::string& location) override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::App::CCM_Monitor_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of location attribute
    std::string location_{};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[user_members]
    IDL::traits<TT_Monitor>::ref_type tt_mon_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl::Monitor_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl::Monitor_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Monitor_exec_i(const Monitor_exec_i&) = delete;
    Monitor_exec_i(Monitor_exec_i&&) = delete;
    Monitor_exec_i& operator=(const Monitor_exec_i&) = delete;
    Monitor_exec_i& operator=(Monitor_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[user_namespace_end_decl]

} // namespace App_Monitor_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Monitor_Impl[factory]
extern "C" EXFTEST_MONITOR_EXEC_Export  void
create_App_Monitor_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : App_Monitor_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : monitor_impl.h[Footer]

#endif /* __RIDL_MONITOR_EXEC_H_CBFCGIGE_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
