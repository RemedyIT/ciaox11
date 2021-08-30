// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   sender for test with missing connection
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl[user_global_impl]

namespace HelloT_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl[user_namespace_impl]
  std::atomic_int nr_of_asyn_received {};
  std::atomic_int nr_of_asyn_called {};
  std::atomic_int nr_of_syn_failed {};
  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
         IDL::traits<HelloT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<HelloT::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                      << std::endl;

    IDL::traits< ::HelloT::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
          this->ciao_context_->get_connection_sendc_run_my_foo();

    if (!my_foo_ami_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    IDL::traits< ::HelloT::AMI4CCM_MyFooReplyHandler>::ref_type cb =
             CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

    //Invoke Asynchronous calls
    try
    {
      my_foo_ami_->sendc_hello (cb);
      // This shouldn't happen, because an exception is expected
      ++nr_of_asyn_called;
    }
    catch (const CORBA::INV_OBJREF& ex)
    {
      if (ex.completed () != CORBA::COMPLETED_NO)
      {
        CIAOX11_TEST_ERROR
                  << "ERROR: Caught unexpected completed status exception for sendc_hello:"
                  << ex << std::endl;
      }
      else
      {
        CIAOX11_TEST_INFO << "OK Caught expected exception for sendc_hello:"
                          << ex << std::endl;
      }
    // expected exception
    }
    catch (const std::exception &ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: Caught unexpected exception for sendc_hello:"
                         << ex.what() << std::endl;
    }
    try
    {
      my_foo_ami_->sendc_get_rw_attrib(cb);
      // This shouldn't happen, because an exception is expected
      ++nr_of_asyn_called;
    }
    catch (const CORBA::INV_OBJREF& ex)
    {
      if (ex.completed () != CORBA::COMPLETED_NO)
      {
        CIAOX11_TEST_ERROR
                 << "ERROR: Caught unexpected completed status exception forsendc_get_rw_attrib:"
                 << ex << std::endl;
      }
      else
      {
        CIAOX11_TEST_INFO << "OK Caught expected exception for sendc_get_rw_attrib:"
                          << ex << std::endl;
      }
    // expected exception
    }
    catch (const std::exception &ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: Caught unexpected exception for sendc_get_rw_attrib:" << ex.what() << std::endl;
    }
    try
    {
      my_foo_ami_->sendc_get_ro_attrib(cb);
      // This shouldn't happen, because an exception is expected
      ++nr_of_asyn_called;
    }
    catch (const CORBA::INV_OBJREF& ex)
    {
      if (ex.completed () != CORBA::COMPLETED_NO)
      {
        CIAOX11_TEST_ERROR
                 << "ERROR: Caught unexpected completed status exception for sendc_get_ro_attrib:"
                 << ex << std::endl;
      }
      else
      {
        CIAOX11_TEST_INFO << "OK Caught expected exception for sendc_get_ro_attrib:"
                          << ex << std::endl;
      }
    // expected exception
    }
    catch (const std::exception &ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: Caught unexpected exception for sendc_get_ro_attrib:"
                         << ex.what() << std::endl;
    }
    try
    {
      my_foo_ami_->sendc_set_rw_attrib(cb, 0);
      // This shouldn't happen, because an exception is expected
      ++nr_of_asyn_called;
    }
    catch (const CORBA::INV_OBJREF& ex)
    {
      if (ex.completed () != CORBA::COMPLETED_NO)
      {
        CIAOX11_TEST_ERROR
                 << "ERROR: Caught unexpected completed status exception for sendc_set_rw_attrib:"
                 << ex << std::endl;
      }
      else
      {
        CIAOX11_TEST_INFO << "OK Caught expected exception for sendc_set_rw_attrib:"
                          << ex << std::endl;
      }
    // expected exception
    }
    catch (const std::exception &ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: Caught unexpected exception for sendc_set_rw_attrib:"
                         << ex.what() << std::endl;
    }
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<HelloT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<HelloT::CCM_Sender_Context>::narrow (std::move(context));
  }

  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;
    IDL::traits<HelloT::MyFoo>::ref_type my_foo_ =
        this->ciao_context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }

    //run some synch calls
    std::string out_str;
    try
    {
      my_foo_->hello (out_str);
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "Exception on sync call" << std::endl;
       ++nr_of_syn_failed;
    }
    try
    {
       my_foo_->rw_attrib ();
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "Exception on sync call" << std::endl;
      ++nr_of_syn_failed;
    }
    try
    {
      my_foo_->rw_attrib (0);
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "Exception on sync call" << std::endl;
      ++nr_of_syn_failed;
    }
    try
    {
      my_foo_->ro_attrib ();
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "Exception on sync call" << std::endl;
      ++nr_of_syn_failed;
    }
    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[ccm_remove]
    if (nr_of_asyn_received > 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: received unexpected asynchronous responses." << std::endl;
    }
    if (nr_of_asyn_called > 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpectedly succeeded calling asynchronously." << std::endl;
    }
    if (nr_of_syn_failed > 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected failures calling synchronously." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<HelloT::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
    // Your code here
    X11_UNUSED_ARG (answer);
    // never should come here in this test.
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::hello: "
                       << "Unexpected callback." << std::endl;
    ++nr_of_asyn_received;

    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::hello_excep: "
                       << "Unexpected exception." << std::endl;

    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::get_rw_attrib: "
                       << "Unexpected callback." << std::endl;

    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::get_rw_attrib_excep: "
                       << "Unexpected exception." << std::endl;

    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::set_rw_attrib: "
                       << "Unexpected callback." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::set_rw_attrib_excep: "
                       << "Unexpected exception." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::get_ro_attrib: "
                       << "Unexpected callback." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
    // Your code here
    X11_UNUSED_ARG (excep_holder);
    CIAOX11_TEST_ERROR << "ERROR: MyFoo_callback_exec_i::get_ro_attrib_excep: "
                       << "Unexpected exception." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
  }



  //@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl[user_namespace_end_impl]

} // namespace HelloT_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : HelloT_Sender_Impl[factory]
extern "C" void
create_HelloT_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <HelloT_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : HelloT_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
