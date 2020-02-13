// -*- C++ -*-
/**
 * @file    conn_test_connr_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   connnector header
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_CONN_TEST_CONNR_EXEC_H_BCJJAEGJ_INCLUDED__
#define __RIDL_CONN_TEST_CONNR_EXEC_H_BCJJAEGJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : conn_test_connr_impl.h[Header]

#pragma once

#include "conn_test_connrEC.h"

#include /**/ "conn_test_connr_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : conn_test_connr_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : conn_test_connr_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : conn_test_connr_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : conn_test_connr_impl.h[user_global_decl]

/// Namespace for implementation of Hello::MyBaseEvent component
namespace Hello_MyBaseEvent_Impl
{
  /// Forward declarations
  class MyBaseEvent_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : MyBaseEvent_exec_i
  class MyBaseEvent_exec_i final
    : public virtual IDL::traits< ::Hello::CCM_MyBaseEvent>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]
    /// Constructor
    MyBaseEvent_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]
    /// Destructor
    virtual ~MyBaseEvent_exec_i ();

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute consumer_port_attrib

    virtual
    int16_t
    consumer_port_attrib () override;

    virtual
    void
    consumer_port_attrib (
        int16_t consumer_port_attrib) override;

    /// Attribute consumer_port_seq_attrib

    virtual
    ::Hello::long_seq
    consumer_port_seq_attrib () override;

    virtual
    void
    consumer_port_seq_attrib (
        const ::Hello::long_seq& consumer_port_seq_attrib) override;

    /// Attribute conn_attrib

    virtual
    int16_t
    conn_attrib () override;

    virtual
    void
    conn_attrib (
        int16_t conn_attrib) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Hello::CCM_MyBaseEvent_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of consumer_port_attrib attribute
    int16_t consumer_port_attrib_ {};
    /// Class member storing value of consumer_port_seq_attrib attribute
    ::Hello::long_seq consumer_port_seq_attrib_;
    /// Class member storing value of conn_attrib attribute
    int16_t conn_attrib_ {};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_members]
    bool ccm_activate_invoked_ {};
    bool configuration_complete_invoked_ {};
    bool ccm_passivate_invoked_ {};
    bool ccm_remove_invoked_ {};
    bool set_session_context_invoked_ {};
    bool conn_attrib_invoked_ {};
    bool consumer_port_attrib_invoked_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]
    void send_something ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    MyBaseEvent_exec_i(const MyBaseEvent_exec_i&) = delete;
    MyBaseEvent_exec_i(MyBaseEvent_exec_i&&) = delete;
    MyBaseEvent_exec_i& operator=(const MyBaseEvent_exec_i&) = delete;
    MyBaseEvent_exec_i& operator=(MyBaseEvent_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_namespace_end_decl]

} // namespace Hello_MyBaseEvent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[factory]
extern "C" CONN_TEST_CONNR_EXEC_Export  void
create_Hello_MyBaseEvent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : conn_test_connr_impl.h[Footer]

#endif /* __RIDL_CONN_TEST_CONNR_EXEC_H_BCJJAEGJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
