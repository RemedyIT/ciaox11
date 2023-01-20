// -*- C++ -*-
/**
 * @file    foo_provider_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_FOO_PROVIDER_EXEC_H_HEAFDICA_INCLUDED__
#define __RIDL_FOO_PROVIDER_EXEC_H_HEAFDICA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_provider_impl.h[Header]

#pragma once

#include "foo_providerEC.h"

#include /**/ "foo_provider_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_provider_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : foo_provider_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_provider_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : foo_provider_impl.h[user_global_decl]

/// Namespace for implementation of Example::FooProvider component
namespace Example_FooProvider_Impl
{
  /// Forward declarations
  class FooProvider_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[user_namespace_decl]


  /// Executor implementation class for do_my_foo facet
  class do_my_foo_exec_i final
    : public IDL::traits<::Example::CCM_Foo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_foo_exec_i (
        IDL::traits<::Example::CCM_FooProvider_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[ctor]

    /// Destructor
    ~do_my_foo_exec_i () override;

    /** @name Operations from ::Example::CCM_Foo */
    //@{

    void
    do_something (
        const std::string& an_argument) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Example::CCM_FooProvider_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : FooProvider_exec_i
  class FooProvider_exec_i final
    : public virtual IDL::traits<::Example::CCM_FooProvider>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[ctor]
    /// Constructor
    FooProvider_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[ctor]
    /// Destructor
    ~FooProvider_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_my_foo facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::Example::CCM_Foo>::ref_type get_do_my_foo () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Example::CCM_FooProvider_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits<::Example::CCM_Foo>::ref_type do_my_foo_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    FooProvider_exec_i(const FooProvider_exec_i&) = delete;
    FooProvider_exec_i(FooProvider_exec_i&&) = delete;
    FooProvider_exec_i& operator=(const FooProvider_exec_i&) = delete;
    FooProvider_exec_i& operator=(FooProvider_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[user_namespace_end_decl]

} // namespace Example_FooProvider_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[factory]
extern "C" FOO_PROVIDER_EXEC_Export  void
create_Example_FooProvider_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_provider_impl.h[Footer]

#endif /* __RIDL_FOO_PROVIDER_EXEC_H_HEAFDICA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
