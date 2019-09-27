// -*- C++ -*-
/**
 * @file    conn_test_conns_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   connnector source
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : conn_test_conns_impl.cpp[Header]

#include "conn_test_conns_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
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
   this->hello_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~supplier_foo_uses_exec_i hello was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~supplier_foo_uses_exec_i hello was NOT invoked" << std::endl;
    this->get_interface_attrib_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~supplier_foo_uses_exec_i getter interface_attrib was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~supplier_foo_uses_exec_i getter interface_attrib was NOT invoked" << std::endl;
    this->set_interface_attrib_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~supplier_foo_uses_exec_i setter interface_attrib was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~supplier_foo_uses_exec_i setter interface_attrib was NOT invoked" << std::endl;
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
    CIAOX11_TEST_INFO << "OK: ConnectorS: supplier_foo_uses_exec_i::hello answer: " << answer << std::endl;
    this->hello_invoked_ = true;
    return answer;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::hello[_answer]
  }

  int16_t
  supplier_foo_uses_exec_i::interface_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::interface_attrib[getter]
    this->get_interface_attrib_invoked_ = true;
    return this->interface_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::interface_attrib[getter]
  }

  void
  supplier_foo_uses_exec_i::interface_attrib (
      int16_t interface_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::supplier_foo_uses_exec_i::interface_attrib[setter]
    this->set_interface_attrib_invoked_ = true;
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
    this->configuration_complete_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i S configuration_complete was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i S configuration_complete was NOT invoked" << std::endl;
    this->ccm_activate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i S ccm_activate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i S ccm_activate was NOT invoked" << std::endl;
    this->ccm_passivate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i S ccm_passivate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i S ccm_passivate was NOT invoked" << std::endl;
    this->ccm_remove_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i S ccm_remove was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i S ccm_remove was NOT invoked" << std::endl;
    this->set_session_context_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i S set_session_context was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i S set_session_context was NOT invoked" << std::endl;
    this->get_supplier_foo_uses_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i S get_supplier_foo_uses was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i S get_supplier_foo_uses was NOT invoked" << std::endl;
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
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::configuration_complete ConnectorS." << std::endl;
    this->configuration_complete_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[configuration_complete]
  }

  void MyBaseEvent_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::ccm_activate ConnectorS." << std::endl;
    this->ccm_activate_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
  }

  void MyBaseEvent_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::ccm_passivate ConnectorS." << std::endl;
    this->ccm_passivate_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
  }

  void MyBaseEvent_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::ccm_remove ConnectorS." << std::endl;
    this->ccm_remove_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
  }

  IDL::traits< ::Hello::CCM_MyFoo >::ref_type
  MyBaseEvent_exec_i::get_supplier_foo_uses ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[get_supplier_foo_uses]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::get_supplier_foo_uses  ConnectorS" << std::endl;
    this->get_supplier_foo_uses_invoked_ = true;
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
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::set_session_context  ConnectorS." << std::endl;
    this->set_session_context_invoked_ = true;

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
//@@{__RIDL_REGEN_MARKER__} - BEGIN : conn_test_conns_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
