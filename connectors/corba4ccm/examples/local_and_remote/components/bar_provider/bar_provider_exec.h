// -*- C++ -*-
/**
 * @file    bar_provider_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_BAR_PROVIDER_EXEC_H_BGIIEIHC_INCLUDED__
#define __RIDL_BAR_PROVIDER_EXEC_H_BGIIEIHC_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : bar_provider_impl.h[Header]

#pragma once

#include "bar_providerEC.h"

#include /**/ "bar_provider_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : bar_provider_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : bar_provider_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : bar_provider_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : bar_provider_impl.h[user_global_decl]

/// Namespace for implementation of Example::BarProvider component
namespace Example_BarProvider_Impl
{
  /// Forward declarations
  class BarProvider_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[user_namespace_decl]


  /// Executor implementation class for do_my_bar facet
  class do_my_bar_exec_i final
    : public IDL::traits< ::Example::CCM_Bar>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_bar_exec_i (
        IDL::traits< ::Example::CCM_BarProvider_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[ctor]

    /// Destructor
    virtual ~do_my_bar_exec_i ();

    /** @name Operations from ::Example::CCM_Bar */
    //@{

    virtual
    void
    do_something_else (
        std::string& an_argument) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Example::CCM_BarProvider_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : BarProvider_exec_i
  class BarProvider_exec_i final
    : public virtual IDL::traits< ::Example::CCM_BarProvider>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[ctor]
    /// Constructor
    BarProvider_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[ctor]
    /// Destructor
    virtual ~BarProvider_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_my_bar facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::Example::CCM_Bar >::ref_type get_do_my_bar () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    virtual void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    virtual void configuration_complete () override;

    /// Component state change method to activated state
    virtual void ccm_activate () override;

    /// Component state change method to passivated state
    virtual void ccm_passivate () override;

    /// Component state change method to removed state
    virtual void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Example::CCM_BarProvider_Context >::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::Example::CCM_Bar >::ref_type do_my_bar_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    BarProvider_exec_i(const BarProvider_exec_i&) = delete;
    BarProvider_exec_i(BarProvider_exec_i&&) = delete;
    BarProvider_exec_i& operator=(const BarProvider_exec_i&) = delete;
    BarProvider_exec_i& operator=(BarProvider_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[user_namespace_end_decl]

} // namespace Example_BarProvider_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[factory]
extern "C" BAR_PROVIDER_EXEC_Export  void
create_Example_BarProvider_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : bar_provider_impl.h[Footer]

#endif /* __RIDL_BAR_PROVIDER_EXEC_H_BGIIEIHC_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
