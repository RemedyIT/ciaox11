// -*- C++ -*-
/**
 * @file    corba4ccm_exceptions_component_exec.h
 * @author  Marcel Smit
 *
 * @brief   Testing the INV_OBJREF exception
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_CORBA4CCM_EXCEPTIONS_COMPONENT_EXEC_H_HCBBIAEA_INCLUDED__
#define __RIDL_CORBA4CCM_EXCEPTIONS_COMPONENT_EXEC_H_HCBBIAEA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : corba4ccm_exceptions_component_impl.h[Header]

#pragma once

#include "corba4ccm_exceptions_componentEC.h"

#include /**/ "corba4ccm_exceptions_component_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : corba4ccm_exceptions_component_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : corba4ccm_exceptions_component_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : corba4ccm_exceptions_component_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : corba4ccm_exceptions_component_impl.h[user_global_decl]

/// Namespace for implementation of Foo::CORBA4CCM_exception_component component
namespace Foo_CORBA4CCM_exception_component_Impl
{
  /// Forward declarations
  class CORBA4CCM_exception_component_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : CORBA4CCM_exception_component_exec_i
  class CORBA4CCM_exception_component_exec_i final
    : public virtual IDL::traits<::Foo::CCM_CORBA4CCM_exception_component>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ctor]
  /// Constructor
  CORBA4CCM_exception_component_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ctor]
    /// Destructor
    ~CORBA4CCM_exception_component_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Foo::CCM_CORBA4CCM_exception_component_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    CORBA4CCM_exception_component_exec_i(const CORBA4CCM_exception_component_exec_i&) = delete;
    CORBA4CCM_exception_component_exec_i(CORBA4CCM_exception_component_exec_i&&) = delete;
    CORBA4CCM_exception_component_exec_i& operator=(const CORBA4CCM_exception_component_exec_i&) = delete;
    CORBA4CCM_exception_component_exec_i& operator=(CORBA4CCM_exception_component_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[user_namespace_end_decl]

} // namespace Foo_CORBA4CCM_exception_component_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[factory]
extern "C" CORBA4CCM_EXCEPTIONS_COMPONENT_EXEC_Export  void
create_Foo_CORBA4CCM_exception_component_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : corba4ccm_exceptions_component_impl.h[Footer]

#endif /* __RIDL_CORBA4CCM_EXCEPTIONS_COMPONENT_EXEC_H_HCBBIAEA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
