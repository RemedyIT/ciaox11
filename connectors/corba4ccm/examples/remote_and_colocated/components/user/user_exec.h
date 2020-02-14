// -*- C++ -*-
/**
 * @file    user_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_USER_EXEC_H_JBHJDJHE_INCLUDED__
#define __RIDL_USER_EXEC_H_JBHJDJHE_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : user_impl.h[Header]

#pragma once

#include "userEC.h"

#include /**/ "user_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : user_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : user_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : user_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : user_impl.h[user_global_decl]

/// Namespace for implementation of Example::User component
namespace Example_User_Impl
{
  /// Forward declarations
  class User_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : User_exec_i
  class User_exec_i final
    : public virtual IDL::traits< ::Example::CCM_User>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[ctor]
    /// Constructor
    User_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[ctor]
    /// Destructor
    virtual ~User_exec_i ();

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute connection

    virtual
    std::string
    connection () override;

    virtual
    void
    connection (
        const std::string& connection) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Example::CCM_User_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of connection attribute
    std::string connection_;
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[user_members]
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    User_exec_i(const User_exec_i&) = delete;
    User_exec_i(User_exec_i&&) = delete;
    User_exec_i& operator=(const User_exec_i&) = delete;
    User_exec_i& operator=(User_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[user_namespace_end_decl]

} // namespace Example_User_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[factory]
extern "C" USER_EXEC_Export  void
create_Example_User_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : user_impl.h[Footer]

#endif /* __RIDL_USER_EXEC_H_JBHJDJHE_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
