// -*- C++ -*-
/**
 * @file    foo_exec.h
 * @author  Martin Corino
 *
 * @brief   DAnCEX11 ORB advanced_resources test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_FOO_EXEC_H_BCHJJJGJ_INCLUDED__
#define __RIDL_FOO_EXEC_H_BCHJJJGJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_impl.h[Header]

#pragma once

#include "fooEC.h"

#include /**/ "foo_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : foo_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : foo_impl.h[user_global_decl]

/// Namespace for implementation of Foo component
namespace Foo_Impl
{
  /// Forward declarations
  class Foo_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Foo_exec_i
  class Foo_exec_i final
    : public virtual IDL::traits<CCM_Foo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ctor]
    /// Constructor
    Foo_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ctor]
    /// Destructor
    ~Foo_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<CCM_Foo_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_members]
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_private_ops]
    void test_orb_advanced_resources ();
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Foo_exec_i(const Foo_exec_i&) = delete;
    Foo_exec_i(Foo_exec_i&&) = delete;
    Foo_exec_i& operator=(const Foo_exec_i&) = delete;
    Foo_exec_i& operator=(Foo_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_end_decl]

} // namespace Foo_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[factory]
extern "C" FOO_EXEC_Export  void
create_Foo_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[Footer]

#endif /* __RIDL_FOO_EXEC_H_BCHJJJGJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
