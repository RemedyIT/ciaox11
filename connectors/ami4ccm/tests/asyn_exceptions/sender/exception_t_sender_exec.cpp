// -*- C++ -*-
/**
 * @file    exception_t_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   Sender component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : exception_t_sender_impl.cpp[Header]

#include "exception_t_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl[user_global_impl]

namespace ExceptionT_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl[user_namespace_impl]
  std::atomic_int nr_of_excep_received {};
  std::atomic_int nr_of_asyn_excep_received {};
  std::atomic_int nr_of_asyn_general_excep_received {};
  std::atomic_int nr_of_syn_received {};
  std::atomic_int nr_of_syn_excep_received {};
  std::atomic_int nr_of_syn_general_excep_received {};

  void HandleException (
      int32_t id,
      const std::string& error_string,
      const std::string& test,
      const std::string& func)
  {
    CIAOX11_TEST_INFO << "Sender:\t->HandleException id:  "
                      << id << " error_string: " << error_string
                      << "func: " << func << std::endl;
    if (id != 42)
    {
      CIAOX11_TEST_ERROR << "ERROR exception " << func
                        << ":\tReceived unexpected ID <"
                        << id << "> received" << std::endl;
      return;
    }
    if (test != "thrown by receiver")
    {
      CIAOX11_TEST_ERROR <<"ERROR exception  " << func
                         << ":\tReceived unexpected string <"
                         <<  error_string << "> in except handler." << std::endl;
      return;
    }
    CIAOX11_TEST_INFO <<  "Sender: Caught correct exception <" << id <<
                      "> <" << error_string << "> for "
                      << func << std::endl;
    ++nr_of_excep_received;
  }

  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
       IDL::traits<ExceptionT::CCM_Sender_Context>::ref_type context)
  {
    this->context_ = IDL::traits<ExceptionT::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                      << std::endl;
   IDL::traits< ::ExceptionT::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
        context_->get_connection_sendc_run_my_foo();

   if (!my_foo_ami_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
      IDL::traits< ExceptionT::AMI4CCM_MyFooReplyHandler>::ref_type cb =
         CORBA::make_reference< AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

    //Invoke Asynchronous calls to test exception handling
    //for this test, all functions of
    //receiver always sent back a exception
    my_foo_ami_->sendc_hello (cb);
    my_foo_ami_->sendc_get_rw_attrib(cb);
    my_foo_ami_->sendc_get_rw_attrib_g(cb);
    my_foo_ami_->sendc_get_rw_attrib_s(cb);
    my_foo_ami_->sendc_get_rw_attrib_g_s(cb);
    my_foo_ami_->sendc_get_ro_attrib(cb);
    my_foo_ami_->sendc_get_ro_attrib_r(cb);
    my_foo_ami_->sendc_foo (cb, 0);
    my_foo_ami_->sendc_set_rw_attrib(cb, 0);
    my_foo_ami_->sendc_set_rw_attrib_g(cb, 0);
    my_foo_ami_->sendc_set_rw_attrib_s(cb, 0);
    my_foo_ami_->sendc_set_rw_attrib_g_s(cb, 0);

    CIAOX11_TEST_INFO << "Sender (ASYNCH) :\tInvoked Asynchronous calls" << std::endl;
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<ExceptionT::CCM_Sender_Context>::ref_type context)
  {
    this->context_ = IDL::traits<ExceptionT::CCM_Sender_Context>::narrow (std::move(context));
  }
  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;
    IDL::traits<ExceptionT::MyFoo>::ref_type my_foo_ =
        this->context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
    }

    //run synch calls
    try
    {
      my_foo_->foo (1);
      ++nr_of_syn_received;
    }
    catch (const ExceptionT::InternalError&)
    {
      CIAOX11_TEST_ERROR <<  "ERROR: synch_foo_generator::foo: "
                         <<   "Unexpected exception." << std::endl;
    }
    try
    {
      my_foo_->foo (0);
    }
    catch (const ExceptionT::InternalError& ex)
    {
      // unexpected exception
      CIAOX11_TEST_INFO << "ERROR Syn method <foo> caught unexpected exception -> "
                        << ex.what() << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_syn_general_excep_received;
      CIAOX11_TEST_INFO << "Syn method <foo> caught correct exception -> "
                        << ex.what() << std::endl;
    }
    try
    {
      int32_t answer {};
      my_foo_->hello (answer);
    }
    catch (const ExceptionT::InternalError& ex)
    {
      //expected exception
      HandleException (ex.id (), ex.error_string (), ex.test (),
                          "hello (syn)");
      ++nr_of_syn_excep_received;
    }
    try
    {
      my_foo_->rw_attrib ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      // unexpected exception
      CIAOX11_TEST_INFO << "ERROR Syn method <get_rw_attrib> caught unexpected exception -> "
                  << ex.what() << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_syn_general_excep_received;
      CIAOX11_TEST_INFO << "Syn method <get_rw_attrib> caught correct exception -> "
                  << ex.what() << std::endl;
    }

    try
    {
      my_foo_->rw_attrib (0);
    }
    catch (const ExceptionT::InternalError& ex)
    {
      // unexpected exception
      CIAOX11_TEST_INFO << "ERROR Syn method <set_rw_attrib> caught unexpected exception -> "
                  << ex.what() << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_syn_general_excep_received;
      CIAOX11_TEST_INFO << "Syn method <set_rw_attrib> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    try
    {
      my_foo_->rw_attrib_g ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      //expected exception
      HandleException (ex.id (), ex.error_string (), ex.test (),
                      "get_rw_attrib_g (syn)");
      ++nr_of_syn_excep_received;
    }
    try
    {
       my_foo_->rw_attrib_g (0);
    }
    catch (const ExceptionT::InternalError& ex)
    {
      // unexpected exception
      CIAOX11_TEST_INFO << "ERROR Syn method <set_rw_attrib> caught unexpected exception -> "
                  << ex.what() << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_syn_general_excep_received;
      CIAOX11_TEST_INFO << "Syn method <set_rw_attrib> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    try
    {
      my_foo_->rw_attrib_s ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      // unexpected exception
      CIAOX11_TEST_INFO << "ERROR Syn method <get_rw_attrib_s> caught unexpected exception -> "
                  << ex.what() << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_syn_general_excep_received;
      CIAOX11_TEST_INFO << "Syn method <get_rw_attrib_s> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    try
    {
      my_foo_->rw_attrib_s (0);
    }
    catch (const ExceptionT::InternalError& ex)
    {
      //expected exception
      HandleException (ex.id (), ex.error_string (), ex.test (),
                      "set_rw_attrib_s (syn)");
      ++nr_of_syn_excep_received;
    }
    try
    {
      my_foo_->rw_attrib_g_s ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      //expected exception
      HandleException (ex.id (), ex.error_string (), ex.test (),
                      "get_rw_attrib_g_s (syn)");
      ++nr_of_syn_excep_received;
    }
    try
    {
       my_foo_->rw_attrib_g_s (0);
    }
    catch (const ExceptionT::InternalError& ex)
    {
      //expected exception
      HandleException (ex.id (), ex.error_string (), ex.test (),
                      "set_rw_attrib_g_s (syn)");
      ++nr_of_syn_excep_received;
    }
    try
    {
       my_foo_->ro_attrib ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      // unexpected exception
      CIAOX11_TEST_INFO << "ERROR Syn method <ro_attrib> caught unexpected exception -> "
                  << ex.what() << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_syn_general_excep_received;
      CIAOX11_TEST_INFO << "Syn method <ro_attrib> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    try
    {
      my_foo_->ro_attrib_r ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      HandleException (ex.id (), ex.error_string (), ex.test (),
                      "ro_attrib_r (syn)");
      ++nr_of_syn_excep_received;
    }
    return 0;
  }

  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[ccm_remove]
    if ((nr_of_asyn_excep_received != 6) ||
        (nr_of_asyn_general_excep_received != 6))
    {
      CIAOX11_TEST_ERROR << "ERROR: not received the expected number of "
                         << "exceptions or general exceptions for asynchronous calls "
                         << "Expected: 6 and 6  Received: "
                         << nr_of_asyn_excep_received << " and "
                         << nr_of_asyn_general_excep_received << std::endl;
    }
    if ((nr_of_syn_received != 1)||
        (nr_of_syn_excep_received != 6) ||
        (nr_of_syn_general_excep_received != 6))
    {
      CIAOX11_TEST_ERROR << "ERROR: not received the expected number of "
                         << "answers, exceptions or general exceptions for synchronous calls "
                         << "Expected: 1,6 and 6  Received: " << nr_of_syn_received
                         << "," << nr_of_syn_excep_received << " and "
                         << nr_of_syn_general_excep_received << std::endl;
    }
    if (nr_of_excep_received != 12)
    {
      CIAOX11_TEST_ERROR << "ERROR: Didn't received the expected number of "
                        <<  "correct ExceptionT::InternalError exceptions for "
                        <<  "(a)synchronous calls" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<ExceptionT::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo (
    int32_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
    X11_UNUSED_ARG (ami_return_val);
    // never should come here in this test.
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::foo: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "Callback method <foo> caught the wrong exception -> ERROR"
                        << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_asyn_general_excep_received;
      CIAOX11_TEST_INFO << "Callback method <foo> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
    X11_UNUSED_ARG (answer);
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::hello: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      ++nr_of_asyn_excep_received;
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      HandleException (ex.id(), ex.error_string(), ex.test(), "HELLO (asyn)");
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - unexpected exception caught: "
                         << e << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_g_s (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g_s]
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::get_rw_attrib_g_s: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g_s]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_g_s_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g_s_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      ++nr_of_asyn_excep_received;
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      HandleException (ex.id(), ex.error_string(), ex.test(), "get_rw_attrib_g_s (asyn)");
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - get_rw_attrib_g_s (asyn) unexpected exception caught: "
                         << e << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g_s_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_g_s ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g_s]
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::set_rw_attrib_g_s: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g_s]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_g_s_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g_s_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      ++nr_of_asyn_excep_received;
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      HandleException (ex.id(), ex.error_string(), ex.test(), "set_rw_attrib_g_s (asyn)");
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - set_rw_attrib_g_s (asyn) unexpected exception caught: "
                         << e << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g_s_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::get_rw_attrib: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "Callback method <get_rw_attrib> caught the wrong exception -> ERROR"
                   << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_asyn_general_excep_received;
      CIAOX11_TEST_INFO << "Callback method <get_rw_attrib> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::set_rw_attrib: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "Callback method <set_rw_attrib> caught the wrong exception -> ERROR"
                   << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_asyn_general_excep_received;
      CIAOX11_TEST_INFO << "Callback method <set_rw_attrib> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_g (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g]
    X11_UNUSED_ARG(ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::get_rw_attrib_g: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_g_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      ++nr_of_asyn_excep_received;
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      HandleException (ex.id(), ex.error_string(), ex.test(), "get_rw_attrib_g (asyn)");
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - get_rw_attrib_g (asyn) unexpected exception caught: "
                         << e << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_g_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_g ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g]
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::set_rw_attrib_g_s: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_g_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "Callback method <set_rw_attrib_g> caught the wrong exception -> ERROR"
                   << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_asyn_general_excep_received;
      CIAOX11_TEST_INFO << "Callback method <set_rw_attrib_g> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_g_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_s (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_s]
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::get_rw_attrib_s: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_s]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_s_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_s_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "Callback method <get_rw_attrib_s> caught the wrong exception -> ERROR"
                   << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_asyn_general_excep_received;
      CIAOX11_TEST_INFO << "Callback method <get_rw_attrib_s> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_s_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_s ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_s]
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::set_rw_attrib_s: "
                       <<  "Unexpected return." << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_s]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_s_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_s_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      ++nr_of_asyn_excep_received;
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      HandleException (ex.id(), ex.error_string(), ex.test(), "set_rw_attrib_s (asyn)");
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - set_rw_attrib_s (asyn)unexpected exception caught: "
                         << e << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_s_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_r (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_r]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::get_ro_attrib_r: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_r]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_r_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_r_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError& ex)
    {
      ++nr_of_asyn_excep_received;
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      HandleException (ex.id(), ex.error_string(), ex.test(), "get_ro_attrib_r (asyn)");
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - get_ro_attrib_r (asyn)unexpected exception caught: "
                         << e << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_r_excep]
  }


  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MyFoo_callback_exec_i::get_ro_attrib: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const ExceptionT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "Callback method <get_ro_attrib> caught the wrong exception -> ERROR"
                   << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      ++nr_of_asyn_general_excep_received;
      CIAOX11_TEST_INFO << "Callback method <get_ro_attrib> caught correct exception -> "
                  << ex.what() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
  }



  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl[user_namespace_end_impl]

} // namespace ExceptionT_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Sender_Impl[factory]
extern "C" void
create_ExceptionT_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <ExceptionT_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : exception_t_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
