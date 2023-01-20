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
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_global_impl]

namespace Hello_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_impl]
  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
    IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(context));
  }

  int
  synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));

    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo_uses " << std::endl;

    IDL::traits<Hello::MyFoo>::ref_type my_foo =
      this->ciao_context_->get_connection_run_my_foo_uses();

    if (!my_foo)
    {
      CIAOX11_TEST_ERROR << "ERROR Sender:\t->get_connection_run_my_foo_uses "
                        << "returns null" << std::endl;
      return 1;
    }

    try
    {
      int32_t answer;
      for (uint16_t i = 0; i < 3; ++i)
      {
        my_foo->hello (answer);
        CIAOX11_TEST_INFO << "Sender:\tsynch hello " << answer << std::endl;
      }
    }
    catch (const Hello::InternalError& )
    {
      CIAOX11_TEST_INFO << "Sender:\tsynch hello get expected exception."
        << std::endl;
    }
    return 0;
  }
  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
    IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo_arr "
      << std::endl;

    IDL::traits<::Hello::AMI4CCM_MyFoo>::ref_type my_foo_ami  =
      this->ciao_context_->get_connection_sendc_run_my_foo_arr ();

    if (!my_foo_ami)
    {
      CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    IDL::traits<::Hello::AMI4CCM_MyFooReplyHandler>::ref_type cb =
      CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i> ();

    my_foo_ami->sendc_hello (cb);
    my_foo_ami->sendc_hello (cb);

    CIAOX11_TEST_INFO << "Sender (ASYNCH) :\tInvoked Asynchronous calls" << std::endl;
    return 0;
  }
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
    CIAOX11_TEST_INFO << "Sender ACTIVATE" << std::endl;
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
     this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    this->synch_foo_gen_.wait();
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
    this->context_ = IDL::traits<::Hello::CCM_Sender_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    X11_UNUSED_ARG (answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[foo]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[foo_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[foo_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[hello]
    // Your code here
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::hello "
                      << " answer: " << answer <<std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[hello]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[hello_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[hello_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_rw_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::get_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[set_rw_attrib]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[set_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::set_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[set_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_ro_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_ro_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i::get_ro_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_ro_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_i[get_ro_attrib_excep]
  }


  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    X11_UNUSED_ARG (answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[foo]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[foo_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[foo_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[hello]
    // Your code here
    X11_UNUSED_ARG (answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[hello]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[hello_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[hello_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_rw_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::get_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[set_rw_attrib]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[set_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::set_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[set_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_ro_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_ro_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i::get_ro_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_ro_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_arr_2_i[get_ro_attrib_excep]
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
