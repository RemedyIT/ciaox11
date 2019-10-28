// -*- C++ -*-
// -*- C++ -*-
/**
 * @file    no_reply_h_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   sender ami4ccm test with no replyhandler
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : no_reply_h_sender_impl.cpp[Header]

#include "no_reply_h_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl[user_global_impl]

namespace NoReplyH_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl[user_namespace_impl]

  std::atomic_int  nr_received_back {};
  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
         IDL::traits<NoReplyH::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<NoReplyH::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                      << std::endl;

    IDL::traits< ::NoReplyH::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
          this->ciao_context_->get_connection_sendc_run_my_foo();

    if (!my_foo_ami_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    IDL::traits< ::NoReplyH::AMI4CCM_MyFooReplyHandler>::ref_type cb =
             CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

    //Invoke Asynchronous calls
    //test with  replyhandler.
    my_foo_ami_->sendc_foo ( cb, "Do something asynchronous");

    //test without replyhandlers.
    my_foo_ami_->sendc_foo ( nullptr,
                            "Do something asynchronous with no replyhandler");
    my_foo_ami_->sendc_hello ( nullptr);
    my_foo_ami_->sendc_get_rw_attrib ( nullptr);
    my_foo_ami_->sendc_set_rw_attrib ( nullptr, 15);
    my_foo_ami_->sendc_get_ro_attrib ( nullptr);

    //Invoke Asynchronous calls to test exception handling
    //without replyhandlers.
    my_foo_ami_->sendc_foo ( nullptr, "");
    my_foo_ami_->sendc_set_rw_attrib ( nullptr, 0);
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<NoReplyH::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<NoReplyH::CCM_Sender_Context>::narrow (std::move(context));

  }
  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;
    IDL::traits<NoReplyH::MyFoo>::ref_type my_foo_ =
        this->ciao_context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }

    //run some synch calls
    try
    {
      int16_t rw_attrib = my_foo_->rw_attrib ();
      CIAOX11_TEST_INFO <<  "OK: SYNCH rw_attrib() returns " << rw_attrib << std::endl;
    }
    catch (const NoReplyH::InternalError& )
    {
      CIAOX11_TEST_ERROR << "ERROR: SYNCH rw_attrib(): Unexpected return." << std::endl;
    }
    try
    {
      int16_t ro_attrib = my_foo_->ro_attrib ();
      CIAOX11_TEST_INFO << "OK: SYNCH ro_attrib() returns " << ro_attrib << std::endl;
    }
    catch (const NoReplyH::InternalError& )
    {
      CIAOX11_TEST_ERROR << "ERROR: SYNCH ro_attrib(): Unexpected return." << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: SYNCH ro_attrib(): Unexpected exception." << ex << std::endl;
    }
    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[ccm_remove]
    if(nr_received_back.load () != 1)
    {
      CIAOX11_TEST_ERROR << "ERROR: Sender doesn't received the expected "
                         << "number of callbacks"
                         << "Expected: 1, Received: " << nr_received_back.load ()
                         << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK: Sender received the expected number of "
                       << "callbacks: " <<  nr_received_back.load()
                       << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<NoReplyH::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
     ++nr_received_back;
    CIAOX11_TEST_INFO << "OK: ASYNCH foo() returns answer: " << answer << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
    X11_UNUSED_ARG (excep_holder);
    // Your code here
    // never should come here in this test.
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::foo_excep: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
    // Your code here
    X11_UNUSED_ARG (answer);
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::hello: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::hello_excep: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::get_rw_attrib: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::get_rw_attrib_excep: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::set_rw_attrib: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::set_rw_attrib_excep: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::get_ro_attrib: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR <<  "ERROR: MI4CCM_MyFooReplyHandler_i::get_ro_attrib_excep: "
                       <<  "Unexpected return." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
  }



  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl[user_namespace_end_impl]

} // namespace NoReplyH_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : NoReplyH_Sender_Impl[factory]
extern "C" void
create_NoReplyH_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <NoReplyH_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : NoReplyH_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : no_reply_h_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
