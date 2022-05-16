// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   exec sender  compomnent
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
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
  // Your code here
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
    CIAOX11_TEST_INFO << "Sender_exec_i:ccm_activate." << std::endl;
    CIAOX11_TEST_INFO << "Sender_exec_i: get_connection_sendc_run_my_foo "
                         << std::endl;
    IDL::traits< ::Hello::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
          this->context_->get_connection_sendc_run_my_foo();

    if (!my_foo_ami_)
    {
      CIAOX11_TEST_INFO << "ERROR Sender: get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
    }
    IDL::traits< ::Hello::AMI4CCM_MyFooReplyHandler>::ref_type cb =
      CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

    if(!cb)
    {
      CIAOX11_TEST_INFO << "ERROR Sender: CCM_AMI4CCM_MyFooReplyHandler "
                        << "ref is null" << std::endl;
    }

    CIAOX11_TEST_INFO << "Sender: get_connection_run_my_foo " << std::endl;
    IDL::traits<Hello::MyFoo>::ref_type my_foo_ =
               this->context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "ERROR Sender: get_connection_run_my_foo "
                       << "returns null" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
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
    CIAOX11_TEST_INFO << "Sender_exec_i::set_session_context." << std::endl;
    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
    // Your code here
    CIAOX11_TEST_INFO << "AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello"
                      << " answer: " << answer << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_INFO << "AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
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
