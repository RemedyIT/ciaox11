// -*- C++ -*-
/*
 * @file    analyzer_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_ANALYZER_EXEC_H_JBDHIFFH_INCLUDED__
#define __RIDL_ANALYZER_EXEC_H_JBDHIFFH_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : analyzer_impl.h[Header]

#pragma once

#include "analyzerEC.h"

#include /**/ "exftest_analyzer_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : analyzer_impl.h[user_includes]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : analyzer_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : analyzer_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : analyzer_impl.h[user_global_decl]

/// Namespace for implementation of App::Analyzer component
namespace App_Analyzer_Impl
{
  /// Forward declarations
  class Analyzer_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Analyzer_exec_i
  class Analyzer_exec_i final
    : public virtual IDL::traits< ::App::CCM_Analyzer>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[ctor]
    /// Constructor
    Analyzer_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[ctor]
    /// Destructor
    ~Analyzer_exec_i () override;

    /** @name Component port operations. */
    //@{

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::App::CCM_Analyzer_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_ana_;
    IDL::traits<CCM_TT::TT_Handler>::ref_type th_ana_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Analyzer_exec_i(const Analyzer_exec_i&) = delete;
    Analyzer_exec_i(Analyzer_exec_i&&) = delete;
    Analyzer_exec_i& operator=(const Analyzer_exec_i&) = delete;
    Analyzer_exec_i& operator=(Analyzer_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[user_namespace_end_decl]

} // namespace App_Analyzer_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[factory]
extern "C" EXFTEST_ANALYZER_EXEC_Export  void
create_App_Analyzer_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : analyzer_impl.h[Footer]

#endif /* __RIDL_ANALYZER_EXEC_H_JBDHIFFH_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
