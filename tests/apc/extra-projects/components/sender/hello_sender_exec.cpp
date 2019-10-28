// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include "tao/x11/anytypecode/any.h"
#include "tao/x11/anytypecode/typecode.h"
#include "tao/x11/anytypecode/typecode_constants.h"
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
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
  void Sender_exec_i::test_any ()
  {
     CORBA::Any tA;
     int32_t l= 10;
     tA<<=l;
     IDL::traits<CORBA::TypeCode>::ref_type tc = tA.type();

     if (tc->kind() != CORBA::TCKind::tk_long)
     {
       CIAOX11_TEST_ERROR << "ERROR  Sender  1 component Unexpected TCKind in value."<< std::endl;
     }
     else
     {
       CIAOX11_TEST_INFO << "Sender 1 component TCKind "<< tc->kind() << std::endl;
     }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
   this->test_any();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Hello::CCM_Sender_Context >::narrow (std::move(ctx));
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
