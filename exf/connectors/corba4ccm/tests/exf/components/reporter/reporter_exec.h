// -*- C++ -*-
/*
 * @file    reporter_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_REPORTER_EXEC_H_DFCIDCJA_INCLUDED__
#define __RIDL_REPORTER_EXEC_H_DFCIDCJA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : reporter_impl.h[Header]

#pragma once

#include "reporterEC.h"

#include /**/ "exftest_reporter_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : reporter_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : reporter_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : reporter_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : reporter_impl.h[user_global_decl]

/// Namespace for implementation of App::Reporter component
namespace App_Reporter_Impl
{
  /// Forward declarations
  class Reporter_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[user_namespace_decl]


  /// Executor implementation class for do_presenter facet
  class do_presenter_exec_i final
    : public IDL::traits< ::API::CCM_Presenter>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_presenter_exec_i (
        IDL::traits< ::App::CCM_Reporter_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[ctor]

    /// Destructor
    ~do_presenter_exec_i () override;

    /** @name Operations from ::API::CCM_Presenter */
    //@{

    void
    present_info (
        const std::string& info) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::App::CCM_Reporter_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Reporter_exec_i
  class Reporter_exec_i final
    : public virtual IDL::traits< ::App::CCM_Reporter>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[ctor]
    /// Constructor
    Reporter_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[ctor]
    /// Destructor
    ~Reporter_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_presenter facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::API::CCM_Presenter>::ref_type get_do_presenter () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::App::CCM_Reporter_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::API::CCM_Presenter>::ref_type do_presenter_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Reporter_exec_i(const Reporter_exec_i&) = delete;
    Reporter_exec_i(Reporter_exec_i&&) = delete;
    Reporter_exec_i& operator=(const Reporter_exec_i&) = delete;
    Reporter_exec_i& operator=(Reporter_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[user_namespace_end_decl]

} // namespace App_Reporter_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[factory]
extern "C" EXFTEST_REPORTER_EXEC_Export  void
create_App_Reporter_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : reporter_impl.h[Footer]

#endif /* __RIDL_REPORTER_EXEC_H_DFCIDCJA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
