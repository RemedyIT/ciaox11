// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   Sender component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_global_impl]

namespace Hello_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
    : ojee_ { 2 }
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[dtor]
    this->configuration_complete_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Sender_exec_i configuration_complete was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Sender_exec_i configuration_complete was NOT invoked" << std::endl;
    this->ccm_activate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Sender_exec_i ccm_activate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Sender_exec_i ccm_activate was NOT invoked" << std::endl;
    this->ccm_passivate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Sender_exec_i ccm_passivate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Sender_exec_i ccm_passivate was NOT invoked" << std::endl;
    this->ccm_remove_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Sender_exec_i ccm_remove was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Sender_exec_i ccm_remove was NOT invoked" << std::endl;
    this->set_session_context_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Sender_exec_i set_session_context was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Sender_exec_i set_session_context was NOT invoked" << std::endl;
    this->ojee_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Sender_exec_i ojee was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Sender_exec_i ojee was NOT invoked" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
    CIAOX11_TEST_INFO << "OK: Sender_exec_i::configuration_complete" << std::endl;
    this->configuration_complete_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "OK: Sender_exec_i::ccm_activate." << std::endl;
    this->ccm_activate_invoked_ = true;

    CIAOX11_TEST_INFO <<  "Sender:\tStarting tests..." << std::endl;

    IDL::traits<Hello::MyFoo>::ref_type my_foo =
      this->context_->get_connection_sender_write_port_foo_uses();
    if (!my_foo)
      {
        CIAOX11_TEST_INFO << "Sender:\t->get_connection_sender_write_port_foo_uses "
          << "returns null" << std::endl;
        return;
      }
    int32_t const hello = my_foo->hello (10);
    if (hello != 10)
      {
        CIAOX11_TEST_ERROR << "Sender:\tERROR: Hello returned an unexpected "
          << "value: expected <10> - got <" << hello << ">."
          << std::endl;
      }
    my_foo->interface_attrib (15);

    int16_t interface_attrib = my_foo->interface_attrib ();
    CIAOX11_TEST_INFO << "Sender:\tInvoked synchronous call "
      << "answer <" << interface_attrib << ">" << std::endl;
    if (interface_attrib != 15)
      {
        CIAOX11_TEST_ERROR << "Sender:\tERROR: interface_attrib returned an unexpected "
          << "value: expected <15> - got <" << interface_attrib << ">."
          << std::endl;
      }
    CIAOX11_TEST_INFO <<  "Sender:\tFinished tests." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "OK: Sender_exec_i::ccm_passivate." << std::endl;
    this->ccm_passivate_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "OK: Sender_exec_i::ccm_remove." << std::endl;
    this->ccm_remove_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
  }


  int16_t
  Sender_exec_i::ojee ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::ojee[getter]
    return this->ojee_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::ojee[getter]
  }

  void
  Sender_exec_i::ojee (
      int16_t ojee)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::ojee[setter]
    this->ojee_invoked_ = true;
    if (ojee != 1234)
    {
      CIAOX11_TEST_ERROR << "ERROR: Sender_exec_i::ojee - "
        << "unexpected value: expected <1234> - got <" << ojee << ">."
        << std::endl;
    }
    this->ojee_ = ojee;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::ojee[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[set_session_context]
    CIAOX11_TEST_INFO << "OK: Sender_exec_i::set_session_context." << std::endl;
    this->set_session_context_invoked_ = true;

    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_impl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
