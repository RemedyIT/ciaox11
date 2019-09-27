// -*- C++ -*-
/**
 * @file    in_args_t_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   sender compomnent
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : in_args_t_sender_impl.cpp[Header]

#include "in_args_t_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl[user_global_impl]

namespace InterInArgsT_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl[user_namespace_impl]
  std::atomic_int nr_of_received_ {};
  int16_t nr_of_excep_received = 0;
  uint16_t update_val = InterInArgsT::update_val;
  uint16_t cmd_synch_ok = 1;
  uint16_t cmd_synch_nok = 2;
  uint16_t cmd_asynch_ok = 3;
  uint16_t cmd_asynch_nok = 4;

  void HandleException (
          int32_t id,
          int32_t expect_id,
          const std::string error_string,
          const std::string func)
  {
    if (id == expect_id)
    {
      CIAOX11_TEST_DEBUG << "Sender: Caught correct exception <" << id
                         << "," << error_string << "> for " << func
                         << std::endl;
      ++nr_of_excep_received;
    }
    else
    {
      CIAOX11_TEST_ERROR <<"ERROR Sender: wrong exception received for "
                         << func << std::endl;
    }
  }

  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
         IDL::traits<InterInArgsT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterInArgsT::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                      << std::endl;

    IDL::traits< ::InterInArgsT::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
          this->ciao_context_->get_connection_sendc_run_my_foo();

    if (!my_foo_ami_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    IDL::traits< ::InterInArgsT::AMI4CCM_MyFooReplyHandler>::ref_type cb =
             CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

    my_foo_ami_->sendc_foo (cb,"Hi",cmd_asynch_ok);
    //this should invoke a exception
    my_foo_ami_->sendc_foo (cb, "", cmd_asynch_nok);
    my_foo_ami_->sendc_var_ins (cb, "Here a double for you.", 1.6);

    InterInArgsT::TestTopic test_topic;
    test_topic.key() = "aaa";
    test_topic.x() = 10;
    InterInArgsT::TopicString topic_str;
    topic_str.key() = "bbb";
    topic_str.x_str() = "ccc";
    InterInArgsT::TestArray topic_arr;

    for ( uint32_t i = 0; i < 5; i ++)
    {
      topic_arr[i].key() ="ddd";
      for (uint32_t y = 0; y < 5; y ++)
      {
        topic_arr[i].x_array()[y] = i * 100 + y ;
      }
    }
    my_foo_ami_->sendc_var_div_ins (cb, test_topic,topic_str,topic_arr);

    InterInArgsT::X_Union topic_union;
    topic_union.x_long(11);
    InterInArgsT::test ttt;
    ttt.x_test () = 12;
    ttt.x_teststr () = "fff" ;
    InterInArgsT::test_seq seq;
    seq.resize(2);
    seq[0] = ttt;

    my_foo_ami_->sendc_var_div2_ins (cb, topic_union, seq);
    InterInArgsT::test_enum in_test;
    in_test = ::InterInArgsT::test_enum::ONE;
    my_foo_ami_->sendc_enum_in(cb, in_test);
    CIAOX11_TEST_INFO << "Sender (ASYNCH) :\tInvoked Asynchronous calls" << std::endl;
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<InterInArgsT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterInArgsT::CCM_Sender_Context>::narrow (std::move(context));

  }
  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;
    IDL::traits<InterInArgsT::MyFoo>::ref_type my_foo_ =
        this->ciao_context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    std::string out_str;
    try {
      int32_t result = my_foo_->foo ("Do something synchronous",
                                      cmd_synch_ok ,
                                      out_str);
      if (result == (update_val + cmd_synch_ok))
      {
        ++nr_of_received_;
      }
    }
    catch (const InterInArgsT::InternalError&)
    {
       CIAOX11_TEST_ERROR << "ERROR: synch_foo_generator::foo: "
                          << "Unexpected exception." << std::endl;
    }
    try
    {
      my_foo_->foo ("",cmd_synch_nok, out_str);
    }
    catch (const InterInArgsT::InternalError& ex)
    {
      HandleException (ex.id(), (update_val + cmd_synch_nok),ex.error_string(),
                       "synch foo");
    }

    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);

    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[ccm_remove]
    if (nr_of_excep_received != 2)
    {
      CIAOX11_TEST_ERROR <<"ERROR: not received the expected number of"
                         <<" exceptions Expected: 2, Received: "
                         <<  nr_of_excep_received << std::endl;
    }
    if (nr_of_received_.load() != 6)
    {
      CIAOX11_TEST_ERROR <<"ERROR: Sender not received the expected number"
                         << " of callbacks and returns  for syn- and "
                         <<     "asynchronous calls. Expected: 6,"
                         <<   " Received: "
                         <<  nr_of_received_.load() << std::endl;
    }
    if ((nr_of_received_.load() == 6) && (nr_of_excep_received == 2))
    {
      CIAOX11_TEST_INFO <<"OK: Sender received the expected number of"
                        <<     " callbacks and exceptions for syn- and "
                        <<     "asynchronous calls" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<InterInArgsT::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
    X11_UNUSED_ARG (answer);
    // Your code here
    if ( ami_return_val == ( cmd_asynch_ok + update_val ))
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
    try
    {
      excep_holder->raise_exception ();
    }
    catch (const InterInArgsT::InternalError& ex)
    {
      InterInArgsT_Sender_Impl::HandleException (ex.id(),
                      (cmd_asynch_nok + update_val),
                       ex.error_string(), "asynch foo");
    }
    catch (const CORBA::Exception& ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: Caught unexpected exception:" << ex << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_ins (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_ins]
    // Your code here
    X11_UNUSED_ARG (answer);
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_ins]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_ins_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_ins_excep]
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_ins_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div_ins (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_ins]
    // Your code here
    X11_UNUSED_ARG (answer);
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_ins]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div_ins_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_ins_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_ins_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div2_ins (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_ins]
    // Your code here
    ++nr_of_received_;
    X11_UNUSED_ARG (answer);
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_ins]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div2_ins_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_ins_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_ins_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::enum_in (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_in]
    // Your code here
    X11_UNUSED_ARG (answer);
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_in]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::enum_in_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_in_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_in_excep]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl[user_namespace_end_impl]

} // namespace InterInArgsT_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Sender_Impl[factory]
extern "C" void
create_InterInArgsT_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterInArgsT_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : in_args_t_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
