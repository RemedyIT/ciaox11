// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_global_impl]

namespace Hello_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_impl]
  std::atomic_uint nr_of_received {};
  std::atomic_uint nr_of_excep_received = {};

  void HandleException (
      IDL::traits<::CCM_AMI::ExceptionHolder>::ref_type excep_holder,
      const std::string& func)
  {
    CIAOX11_TEST_INFO << "Sender:\t->HandleException "
                      << "func: " << func << std::endl;
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const Hello::InternalError& ex)
    {
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      if (ex.id() != 42)
      {
        CIAOX11_TEST_ERROR << "ERROR exception " << func
                           << ":\tReceived unexpected ID <"
                           << ex.id() << "> received" << std::endl;
      }
      if (ex.error_string() != "Hello world")
      {
        CIAOX11_TEST_ERROR <<"ERROR exception  " << func
                           << ":\tReceived unexpected error string <"
                           <<  ex.error_string() << "> in except handler." << std::endl;
      }
      ++nr_of_excep_received;
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - unexpected exception caught: "
                          << e << std::endl;
    }
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
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
      << std::endl;

    IDL::traits<::Hello::AMI4CCM_MyFoo>::ref_type my_foo_ami  =
      this->ciao_context_->get_connection_sendc_run_my_foo ();

    if (!my_foo_ami)
    {
      CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    IDL::traits<::Hello::AMI4CCM_MyFooReplyHandler>::ref_type cb =
      CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

    my_foo_ami->sendc_foo (cb,"Do something asynchronous");

    //next should throw an exception
    my_foo_ami->sendc_foo (cb,"");

    my_foo_ami->sendc_hello (cb);
    my_foo_ami->sendc_do_something(cb);
    my_foo_ami->sendc_get_rw_attrib(cb);
    my_foo_ami->sendc_set_rw_attrib(cb, 15);

    my_foo_ami->sendc_return_something(cb);
    my_foo_ami->sendc_bar(cb, "bar1", "bar2");

    //next should throw an exception
    my_foo_ami->sendc_set_rw_attrib(cb, 0);

    my_foo_ami->sendc_get_ro_attrib(cb);

    CIAOX11_TEST_INFO << "Sender (ASYNCH) :\tInvoked Asynchronous calls" << std::endl;
    return 0;
  }

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

    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;

    IDL::traits<Hello::MyFoo>::ref_type my_foo =
      this->ciao_context_->get_connection_run_my_foo();

    if (!my_foo)
    {
      CIAOX11_TEST_ERROR << "ERROR Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }

    try
    {
      int32_t answer;
      for (uint16_t i = 0; i < 5; ++i)
      {
        my_foo->hello (answer);
        CIAOX11_TEST_INFO << "Sender:\tsynch hello " << answer << std::endl;
      }
    }
    catch (const Hello::InternalError& )
    {
      CIAOX11_TEST_ERROR << "Sender:\tsynch hello get unexpected exception."
        << std::endl;
    }

    try
    {
      my_foo->rw_attrib (15);
      int16_t const ret  = my_foo->ro_attrib();
      CIAOX11_TEST_INFO << "Sender:\tsynch get_ro_attribo " << ret << std::endl;
    }
    catch (const Hello::InternalError& )
    {
      CIAOX11_TEST_ERROR << "Sender:\tsynch ro_attrib get unexpected exception "
                        << std::endl;
    }

    try
    {
      my_foo->rw_attrib (0);
      CIAOX11_TEST_ERROR << "Sender:\tsynch rw_attrib expected exception not caught"
                        << std::endl;
    }
    catch (const Hello::InternalError& )
    {
      CIAOX11_TEST_INFO << "Sender:\tsynch rw_attrib expected exception caught"
                        << std::endl;
    }
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
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
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
    bool received_all = true;
    // if a deadline in exf is expired, it is possible that not all expected callbacks are received
    if ((nr_of_excep_received == 0) || (nr_of_excep_received > 4))
    {
      CIAOX11_TEST_ERROR <<"ERROR: not received the expected number of"
                         <<" exceptions Expected more then 0 and less then 5. Received: "
                         <<  nr_of_excep_received << std::endl;
      received_all = false;
    }
    if ((nr_of_received == 0) || (nr_of_received > 16))
    {
      CIAOX11_TEST_ERROR <<"ERROR: Sender not received the expected number"
                         << " of callbacks and returns  for "
                         <<     "asynchronous calls. Expected more then 0 and less then 17."
                         <<   " Received: "
                         <<  nr_of_received << std::endl;
      received_all = false;
    }
    if (received_all)
    {
      CIAOX11_TEST_INFO <<"OK: Sender received the expected number of"
                        <<     " callbacks and exceptions for "
                        <<     "asynchronous calls" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[set_session_context]
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
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    X11_UNUSED_ARG (answer);
    CIAOX11_TEST_INFO << "Sender: Replyhandler foo received." << std::endl;
    ++nr_of_received;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
    // Your code here
    HandleException (excep_holder, "foo");
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
    // Your code here
    X11_UNUSED_ARG (answer);
    ++nr_of_received;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep "
                       << "shouldn't be called" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::do_something ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[do_something]
    ++nr_of_received;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[do_something]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::do_something_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[do_something_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::do_something_excep "
                       << "shouldn't be called" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[do_something_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::return_something (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[return_something]
    ++nr_of_received;
    CIAOX11_TEST_INFO << "Sender: Replyhandler return_something received " << ami_return_val << std::endl;
    if (ami_return_val != 5)
      {
        CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::return_something "
                            << "should have received 5, but received " << ami_return_val << std::endl;
      }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[return_something]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::return_something_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[return_something_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::return_something_excep "
                       << "shouldn't be called" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[return_something_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::bar (
    int32_t ami_return_val,
    const std::string& answer,
    const std::string& answer2)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[bar]
    ++nr_of_received;
    CIAOX11_TEST_INFO << "Sender: Replyhandler bar received return " << ami_return_val
                      << " answer <" << answer << "><" << answer2 << ">" << std::endl;
    if ((ami_return_val != 77) || (answer != "answer1") || (answer2 != "answer2"))
      {
        CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::bar "
                            << "received incorrect values" << ami_return_val
                            << " answer <" << answer << "><" << answer2 << ">" << std::endl;
      }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[bar]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::bar_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[bar_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::bar_excep "
                       << "shouldn't be called" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[bar_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib "
                      << " rw_attrib: " << ami_return_val <<std::endl;
    ++nr_of_received;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
    HandleException (excep_holder, "get_rw_attrib");
    CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_excep "
                       << "shouldn't be called" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib "
                      <<std::endl;
    ++nr_of_received;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
    HandleException (excep_holder, "set_rw_attribo");
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib "
                       << " ro_attrib: " << ami_return_val <<std::endl;
    ++nr_of_received;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
    HandleException (excep_holder, "get_ro_attrib");
    CIAOX11_TEST_ERROR << "Sender:\t>AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_excep "
                       << "shouldn't be called" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
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
