// -*- C++ -*-
/**
 * @file    conn_test_connr_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   connnector source
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : conn_test_connr_impl.cpp[Header]

#include "conn_test_connr_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_includes]
#include <thread>
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
   * Component Executor Implementation Class : MyBaseEvent_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]
  MyBaseEvent_exec_i::MyBaseEvent_exec_i ()
    : consumer_port_attrib_ { 2 }
    , conn_attrib_ { 1 }

  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]

  MyBaseEvent_exec_i::~MyBaseEvent_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[dtor]
    this->configuration_complete_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i R configuration_complete was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i R configuration_complete was NOT invoked" << std::endl;
    this->ccm_activate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i R ccm_activate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i R ccm_activate was NOT invoked" << std::endl;
    this->ccm_passivate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i R ccm_passivate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i R ccm_passivate was NOT invoked" << std::endl;
    this->ccm_remove_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i R ccm_remove was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i R ccm_remove was NOT invoked" << std::endl;
    this->set_session_context_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i R set_session_context was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i R set_session_context was NOT invoked" << std::endl;
    this->conn_attrib_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i R conn_attrib was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i R conn_attrib was NOT invoked" << std::endl;
    this->consumer_port_attrib_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~MyBaseEvent_exec_i R consumer_port_attrib was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~MyBaseEvent_exec_i R consumer_port_attrib was NOT invoked" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]
  void MyBaseEvent_exec_i::send_something ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (2));
    IDL::traits<Hello::MyFoo>::ref_type my_foo =
               this->context_->get_connection_consumer_foo_prov ();
    if (!my_foo)
      {
        CIAOX11_TEST_ERROR << "ERROR: MyBaseEvent_exec_i::send_something: "
          << "get_connection_consumer_foo_prov returns null."
          << std::endl;
        return;
      }

    int32_t hello = my_foo->hello(11);
    if (hello != 11)
      {
        CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: Hello returned an unexpected "
          << "value: expected <11> - got <" << hello << ">."
          << std::endl;
      }

    CIAOX11_TEST_INFO << "ConnectorR:\tInvoked synchronous call hello" << std::endl;

    my_foo->interface_attrib (115);
    CIAOX11_TEST_INFO <<  "ConnectorR:\tInvoked synchronous call interface_attrib (115) " << std::endl;

    int16_t interface_attrib = my_foo->interface_attrib ();
    CIAOX11_TEST_INFO << "ConnectorR:\tInvoked synchronous call "
                        << "(GET_RW_ATTRIB) answer <" << interface_attrib << ">" << std::endl;

    if (interface_attrib != 115)
      {
        CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: interface_attrib returned an unexpected "
          << "value: expected <115> - got <" << interface_attrib << ">."
          << std::endl;
      }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]

  /** Session component operations */
  void MyBaseEvent_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[configuration_complete]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::configuration_complete ConnectorR." << std::endl;
    this->configuration_complete_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[configuration_complete]
  }

  void MyBaseEvent_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::ccm_activate ConnectorR." << std::endl;
    this->ccm_activate_invoked_ = true;
    this->send_something();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
  }

  void MyBaseEvent_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::ccm_passivate ConnectorR." << std::endl;
    this->ccm_passivate_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
  }

  void MyBaseEvent_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::ccm_remove ConnectorR." << std::endl;
    this->ccm_remove_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
  }


  int16_t
  MyBaseEvent_exec_i::consumer_port_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[getter]
    return this->consumer_port_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[getter]
  }

  void
  MyBaseEvent_exec_i::consumer_port_attrib (
      int16_t consumer_port_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[setter]
    this->consumer_port_attrib_invoked_ = true;
    if (consumer_port_attrib != 4321)
    {
        CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: consumer_port_attrib received an "
          << "unexpected value: expected <4321> - got <" << consumer_port_attrib << ">."
          << std::endl;
    }
    this->consumer_port_attrib_ = consumer_port_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[setter]
  }

  ::Hello::long_seq
  MyBaseEvent_exec_i::consumer_port_seq_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_seq_attrib[getter]
    return this->consumer_port_seq_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_seq_attrib[getter]
  }

  void
  MyBaseEvent_exec_i::consumer_port_seq_attrib (
      const ::Hello::long_seq& consumer_port_seq_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_seq_attrib[setter]
    this->consumer_port_seq_attrib_ = consumer_port_seq_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_seq_attrib[setter]
  }

  int16_t
  MyBaseEvent_exec_i::conn_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[getter]
    return this->conn_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[getter]
  }

  void
  MyBaseEvent_exec_i::conn_attrib (
      int16_t conn_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[setter]
    this->conn_attrib_invoked_ = true;
    if (conn_attrib != 4321)
    {
      CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: conn_attrib received an "
          << "unexpected value: expected <4321> - got <" << conn_attrib << ">."
          << std::endl;
    }
    this->conn_attrib_ = conn_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[setter]
  }

  /// Operations from Components::SessionComponent
  void
  MyBaseEvent_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[set_session_context]
    CIAOX11_TEST_INFO << "OK: MyBaseEvent_exec_i::set_session_context." << std::endl;
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
//@@{__RIDL_REGEN_MARKER__} - BEGIN : conn_test_connr_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
