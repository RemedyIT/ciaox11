// -*- C++ -*-
/**
 * @file    gen_test_conns_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   connnector source
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : gen_test_conns_impl.cpp[Header]

#include "gen_test_conns_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_global_impl]

namespace Hello_MyBaseEvent_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : supplier_foo_uses_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[ctor]
  supplier_foo_uses_exec_i::supplier_foo_uses_exec_i (
    IDL::traits<Hello::CCM_MyBaseEvent_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[ctor]

  supplier_foo_uses_exec_i::~supplier_foo_uses_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i[user_private_ops]


  /** Operations and attributes from supplier_foo_uses */

  int32_t
  supplier_foo_uses_exec_i::hello (
      int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::hello[_answer]
    return answer;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::hello[_answer]
  }

  int16_t
  supplier_foo_uses_exec_i::interface_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::interface_attrib[getter]
    return this->interface_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::interface_attrib[getter]
  }

  void
  supplier_foo_uses_exec_i::interface_attrib (
      int16_t interface_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::interface_attrib[setter]
    this->interface_attrib_ = interface_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::interface_attrib[setter]
  }

  /**
   * Component Executor Implementation Class : MyBaseEvent_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]
  MyBaseEvent_exec_i::MyBaseEvent_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]

  MyBaseEvent_exec_i::~MyBaseEvent_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]

  /** Session component operations */
  void MyBaseEvent_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[configuration_complete]
  }

  void MyBaseEvent_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
  }

  void MyBaseEvent_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
  }

  void MyBaseEvent_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
  }

  IDL::traits< ::Hello::CCM_MyFoo >::ref_type
  MyBaseEvent_exec_i::get_supplier_foo_uses ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[get_supplier_foo_uses]
  if (!this->supplier_foo_uses_)
  {
    this->supplier_foo_uses_ = CORBA::make_reference <supplier_foo_uses_exec_i> (this->context_);
  }
  return this->supplier_foo_uses_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[get_supplier_foo_uses]
  }

  /// Operations from Components::SessionComponent
  void
  MyBaseEvent_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[set_session_context]
    this->context_ = IDL::traits<Hello::CCM_MyBaseEvent_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_namespace_end_impl]

} // namespace Hello_MyBaseEvent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[factory]
extern "C" void
create_Hello_MyBaseEvent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : gen_test_conns_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
