// -*- C++ -*-
/**
 * @file    hello_sender_comp_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   Implementation sender component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_comp_impl.cpp[Header]

#include "hello_sender_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_global_impl]

namespace Hello_Sender_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_namespace_impl]
  //============================================================
  // Worker thread for asynchronous invocations for MyFoo_obj
  //============================================================
  void
  asynch_foo_generator::set_context(
     IDL::traits<Hello::CCM_Sender_comp_Context>::ref_type context)
  {
    this->context_ = IDL::traits<Hello::CCM_Sender_comp_Context>::narrow (std::move(context));
  }


  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender: get_connection_sendc_run_my_foo "
                      << std::endl;

    IDL::traits< ::Hello::AMI4CCM_MyFoo_obj>::ref_type my_foo_ami_  =
       this->context_->get_connection_sendc_run_my_foo();

    if (!my_foo_ami_)
    {
      CIAOX11_TEST_INFO << "Sender: get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    IDL::traits< ::Hello::AMI4CCM_MyFoo_objReplyHandler>::ref_type cb =
         CORBA::make_reference<AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i> ();
    // run asynch call's
    for (int i = 0; i < 5; ++i)
    {
      CIAOX11_TEST_INFO << "Sender (ASYNCH): Invoke 5 Asynchronous calls"<< std::endl;
      my_foo_ami_->sendc_foo (cb,"Do something asynchronous");
      my_foo_ami_->sendc_hello (cb);
      my_foo_ami_->sendc_get_rw_attrib(cb);
      my_foo_ami_->sendc_set_rw_attrib(cb, 15);
      my_foo_ami_->sendc_get_ro_attrib(cb);
      CIAOX11_TEST_INFO << "Sender (ASYNCH): Invoked 5 Asynchronous calls\n"<< std::endl;
    }

    CIAOX11_TEST_INFO << "Sender (ASYNCH) :Invoke Asynchronous calls to test except handling." << std::endl;
    my_foo_ami_->sendc_foo (cb, "");
    my_foo_ami_->sendc_set_rw_attrib(cb, 0);

    CIAOX11_TEST_INFO << "Sender (ASYNCH) : Invoked 2 Asynchronous calls\n" << std::endl;
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo_obj
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<Hello::CCM_Sender_comp_Context>::ref_type context)
  {
    this->context_ = IDL::traits<Hello::CCM_Sender_comp_Context>::narrow (std::move(context));
  }
  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender: get_connection_run_my_foo " << std::endl;
    IDL::traits<Hello::MyFoo_obj>::ref_type my_foo_ =
        this->context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "Sender: get_connection_run_my_foo "
                        << "returns null" << std::endl;
    }
    std::string out_str {};
    //run synch call
    for (int i = 0; i < 2; ++i)
    {
      try
      {
        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoke synchronous call (foo)" << std::endl;
        int32_t result = my_foo_->foo ("Do something synchronous",
                                        out_str);
        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoked synchronous call (foo)"
                          << " result <" << result << "> answer <" << out_str  << ">" <<  std::endl;

        int32_t answer {};
        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoke synchronous call (hello)" << std::endl;
        my_foo_->hello (answer);
        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoked synchronous"
                          << " call (hello) result <" <<  answer  << ">" << std::endl;

        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoke synchronous call "
                          << "(rw_attrib())" << std::endl;
        int16_t rw_attrib = my_foo_->rw_attrib ();
        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoked synchronous call"
                          << " (rw_attrib()) return :" << rw_attrib << std::endl;

        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoke synchronous call"
                          << " (rw_attrib(15))" << std::endl;
        my_foo_->rw_attrib (15);
        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoked synchronous call "
                          << " (rw_attrib(15))" << std::endl;

        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoke synchronous call"
                          << " (ro_attrib())" << std::endl;
        int16_t ro_attrib = my_foo_->ro_attrib ();
        CIAOX11_TEST_INFO << "Sender (SYNCH): Invoked synchronous call "
                          << "(ro_attrib) return " << ro_attrib << std::endl;
      }
      catch (const Hello::InternalError& ex)
      {
        CIAOX11_TEST_ERROR << "Sender (SYNCH) : ERROR: "
                           << "Unexpected Exception caught :"
                           << " <" << ex.id () << "> <" << ex.error_string () << ">." << std::endl;
        return 1;
      }
    }
    return 0;
  }
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
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
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
    this->context_ = IDL::traits<Hello::CCM_Sender_comp_Context>::narrow (std::move(ctx));
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
    CIAOX11_TEST_INFO << "Sender: MyFoo_obj AMI Callback from foo:"
                      << " result <"<< ami_return_val << "> answer <" << answer
                      << ">" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[foo]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::foo_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[foo_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const Hello::InternalError& ex)
    {
      CIAOX11_TEST_INFO << "Sender: MyFoo_obj Expected exception AMI Callback "
                        << "from foo: id <" << ex.id () << "> error_string <"
                        << ex.error_string () << ">" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[foo_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello]
    CIAOX11_TEST_INFO << "Sender: MyFoo_obj AMI Callback from hello:"
                         " answer <" << answer << ">" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello_excep]
    try
    {
       excep_holder->raise_exception ();
    }
    catch (const Hello::InternalError& ex)
    {
      CIAOX11_TEST_INFO << "Sender:\tMyFoo Exception AMI Callback from hello:"
                        << " id " << ex.id ()<< "> error_string <" << ex.error_string ()
                        <<  ">" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[hello_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib]
    CIAOX11_TEST_INFO << "Sender: MyFoo_obj AMI Callback from get_rw_attrib:"
                      << " result <" << ami_return_val << ">" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_rw_attrib_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib_excep]
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib]
    CIAOX11_TEST_INFO << "Sender: MyFoo_obj AMI Callback from "
                      << "set_rw_attrib." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::set_rw_attrib_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib_excep]
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_ro_attrib]
    CIAOX11_TEST_INFO << "Sender: MyFoo_obj AMI Callback from "
                      << "get_ro_attrib: result <" << ami_return_val  << ">"<< std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_ro_attrib]
  }

  void
  AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i::get_ro_attrib_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[get_ro_attrib_excep]
    excep_holder->raise_exception ();
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
  component = CORBA::make_reference <Hello_Sender_comp_Impl::Sender_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
