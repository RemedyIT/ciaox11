/**
 * @file    hello_sender_comp_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   generated implementation file sender component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_comp_impl.cpp[Header]

#include "hello_sender_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_global_impl]

namespace Hello_Sender_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[ctor]
  Sender_comp_exec_i::Sender_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[ctor]

  Sender_comp_exec_i::~Sender_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[configuration_complete]
  }

  void Sender_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[ccm_activate]
  }

  void Sender_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[ccm_passivate]
  }

  void Sender_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<::Hello::CCM_Sender_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::~AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    X11_UNUSED_ARG (answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[foo]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[foo_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[foo_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello]
    // Your code here
    X11_UNUSED_ARG (answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::set_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_ro_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_ro_attrib]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_ro_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_ro_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_ro_attrib_excep]
  }



  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_namespace_end_impl]

} // namespace Hello_Sender_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[factory]
extern "C" void
create_Hello_Sender_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference < Hello_Sender_comp_Impl::Sender_comp_exec_i > ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_comp_impl.cpp[Footer]
// Your footer (code) here
