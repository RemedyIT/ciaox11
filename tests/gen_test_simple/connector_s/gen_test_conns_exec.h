// -*- C++ -*-
/**
 * @file    gen_test_conns_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   connnector header
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_GEN_TEST_CONNS_EXEC_H_CFBFABGB_INCLUDED__
#define __RIDL_GEN_TEST_CONNS_EXEC_H_CFBFABGB_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : gen_test_conns_impl.h[Header]

#pragma once

#include "gen_test_connsEC.h"

#include /**/ "gen_test_conns_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : gen_test_conns_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : gen_test_conns_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : gen_test_conns_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : gen_test_conns_impl.h[user_global_decl]

/// Namespace for implementation of Hello::MyBaseEvent component
namespace Hello_MyBaseEvent_Impl
{
  /// Forward declarations
  class MyBaseEvent_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_namespace_decl]


  /// Executor implementation class for supplier_foo_uses facet
  class supplier_foo_uses_exec_i final
    : public IDL::traits<::Hello::CCM_MyFoo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    supplier_foo_uses_exec_i (
      IDL::traits<Hello::CCM_MyBaseEvent_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[ctor]

    /// Destructor
    ~supplier_foo_uses_exec_i () override;

    /** @name Operations from ::Hello::CCM_MyFoo */
    //@{

    int32_t
    hello (
        int32_t answer) override;
    //@}

    /** @name Attributes from ::Hello::CCM_MyFoo */
    //@{
    int16_t interface_attrib () override;
    void interface_attrib (int16_t interface_attrib) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Hello::CCM_MyBaseEvent_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Hello::CCM_MyFoo */
    //@{
    /// Class member storing value of interface_attrib attribute
    int16_t interface_attrib_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_members]
    bool hello_invoked_ {};
    bool set_interface_attrib_invoked_ {};
    bool get_interface_attrib_invoked_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : MyBaseEvent_exec_i
  class MyBaseEvent_exec_i final
    : public virtual IDL::traits<::Hello::CCM_MyBaseEvent>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]
    /// Constructor
    MyBaseEvent_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]
    /// Destructor
    ~MyBaseEvent_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the supplier_foo_uses facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::Hello::CCM_MyFoo>::ref_type get_supplier_foo_uses () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Hello::CCM_MyBaseEvent_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits<::Hello::CCM_MyFoo>::ref_type supplier_foo_uses_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_members]
    bool ccm_activate_invoked_ {};
    bool configuration_complete_invoked_ {};
    bool ccm_passivate_invoked_ {};
    bool ccm_remove_invoked_ {};
    bool set_session_context_invoked_ {};
    bool get_supplier_foo_uses_invoked_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]
    // Your code here
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
extern "C" GEN_TEST_CONNS_EXEC_Export  void
create_Hello_MyBaseEvent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : gen_test_conns_impl.h[Footer]

#endif /* __RIDL_GEN_TEST_CONNS_EXEC_H_CFBFABGB_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
