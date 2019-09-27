// -*- C++ -*-
/**
 * @file    hello_sender_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_HELLO_SENDER_EXEC_H_JEJEJEFD_INCLUDED__
#define __RIDL_HELLO_SENDER_EXEC_H_JEJEJEFD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.h[Header]

#pragma once

#include "hello_senderEC.h"

#include /**/ "hello_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[user_includes]
#include "ace/Task.h"
//@@{__RIDL_REGEN_MARKER__} - END : hello_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : hello_sender_impl.h[user_global_decl]

/// Namespace for implementation of Hello::Sender component
namespace Hello_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_decl]
  /// Worker thread for synchronous invocations
  class synch_foo_generator final : public ACE_Task_Base
  {
  public:
    synch_foo_generator () = default;
    void set_context(IDL::traits<Hello::CCM_Sender_Context>::ref_type context);
    virtual int svc () override;

  private:
    IDL::traits<Hello::CCM_Sender_Context>::ref_type ciao_context_;
  };
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for foo_port_s_foo_prov facet
  class foo_port_s_foo_prov_exec_i final
    : public IDL::traits< ::Hello::CCM_PortFooS>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    foo_port_s_foo_prov_exec_i (
        IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[ctor]

    /// Destructor
    virtual ~foo_port_s_foo_prov_exec_i ();

    /** @name Operations from ::Hello::CCM_PortFooS */
    //@{

    virtual
    int32_t
    hello (
        int32_t answer) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Hello::CCM_Sender_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::Hello::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ctor]
  /// Constructor
  Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    virtual ~Sender_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the foo_port_s_foo_prov facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::Hello::CCM_PortFooS >::ref_type get_foo_port_s_foo_prov () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute my_attribute

    virtual
    ::Hello::foo_seq
    my_attribute () override;

    virtual
    void
    my_attribute (
        const ::Hello::foo_seq& my_attribute) override;

    /// Attribute my_attrib2

    virtual
    ::Hello::foo_long
    my_attrib2 () override;

    virtual
    void
    my_attrib2 (
        ::Hello::foo_long my_attrib2) override;

    /// Attribute my_attrib3

    virtual
    ::Hello::bar_seq
    my_attrib3 () override;

    virtual
    void
    my_attrib3 (
        const ::Hello::bar_seq& my_attrib3) override;

    /// Attribute my_attrib4

    virtual
    ::Hello::foo_struct
    my_attrib4 () override;

    virtual
    void
    my_attrib4 (
        const ::Hello::foo_struct& my_attrib4) override;

    /// Attribute my_attrib5

    virtual
    int32_t
    my_attrib5 () override;

    virtual
    void
    my_attrib5 (
        int32_t my_attrib5) override;

    /// Attribute my_attrib6

    virtual
    ::Hello::out_seq
    my_attrib6 () override;

    virtual
    void
    my_attrib6 (
        const ::Hello::out_seq& my_attrib6) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Hello::CCM_Sender_Context >::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of my_attribute attribute
    ::Hello::foo_seq my_attribute_;
    /// Class member storing value of my_attrib2 attribute
    ::Hello::foo_long my_attrib2_ {};
    /// Class member storing value of my_attrib3 attribute
    ::Hello::bar_seq my_attrib3_;
    /// Class member storing value of my_attrib4 attribute
    ::Hello::foo_struct my_attrib4_;
    /// Class member storing value of my_attrib5 attribute
    int32_t my_attrib5_ {};
    /// Class member storing value of my_attrib6 attribute
    ::Hello::out_seq my_attrib6_;
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::Hello::CCM_PortFooS >::ref_type foo_port_s_foo_prov_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_members]
    synch_foo_generator synch_foo_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Sender_exec_i(const Sender_exec_i&) = delete;
    Sender_exec_i(Sender_exec_i&&) = delete;
    Sender_exec_i& operator=(const Sender_exec_i&) = delete;
    Sender_exec_i& operator=(Sender_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_decl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" HELLO_SENDER_EXEC_Export  void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[Footer]

#endif /* __RIDL_HELLO_SENDER_EXEC_H_JEJEJEFD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
