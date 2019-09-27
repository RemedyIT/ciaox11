// -*- C++ -*-
/**
 * @file    receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component header
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef __RIDL_RECEIVER_EXEC_H_EEJFAJFG_INCLUDED__
#define __RIDL_RECEIVER_EXEC_H_EEJFAJFG_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : receiver_impl.h[Header]

#pragma once

#include "receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : receiver_impl.h[user_includes]
#include <mutex>
//@@{__RIDL_REGEN_MARKER__} - END : receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : receiver_impl.h[user_global_decl]
//@@{__RIDL_REGEN_MARKER__} - END : receiver_impl.h[user_global_decl]

/// Namespace for implementation of Interceptor::Interceptor_Receiver component
namespace Interceptor_Interceptor_Receiver_Impl
{
  /// Forward declarations
  class Interceptor_Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for prov_my_foo facet
  class prov_my_foo_exec_i final
    : public IDL::traits< ::Interceptor::CCM_Foo>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    prov_my_foo_exec_i (
        IDL::traits< Interceptor::CCM_Interceptor_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[ctor]

    /// Destructor
    virtual ~prov_my_foo_exec_i ();

    /** @name Operations from ::Interceptor::CCM_Foo */
    //@{

    virtual
    uint16_t
    do_foo (
        uint16_t input,
        uint16_t& output) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_public_ops]
    static uint16_t   _do_foo_count;
    static std::mutex _lock;
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Interceptor::CCM_Interceptor_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_members]
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Interceptor_Receiver_exec_i
  class Interceptor_Receiver_exec_i final
    : public virtual IDL::traits< ::Interceptor::CCM_Interceptor_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ctor]
    /// Constructor
    Interceptor_Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Interceptor_Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the prov_my_foo facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::Interceptor::CCM_Foo >::ref_type get_prov_my_foo () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Interceptor::CCM_Interceptor_Receiver_Context >::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::Interceptor::CCM_Foo >::ref_type prov_my_foo_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Interceptor_Receiver_exec_i(const Interceptor_Receiver_exec_i&) = delete;
    Interceptor_Receiver_exec_i(Interceptor_Receiver_exec_i&&) = delete;
    Interceptor_Receiver_exec_i& operator=(const Interceptor_Receiver_exec_i&) = delete;
    Interceptor_Receiver_exec_i& operator=(Interceptor_Receiver_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[user_namespace_end_decl]

} // namespace Interceptor_Interceptor_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_Interceptor_Interceptor_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : receiver_impl.h[Footer]

#endif /* __RIDL_RECEIVER_EXEC_H_EEJFAJFG_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
