// -*- C++ -*-
/**
 * @file    out_args_t_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   sender of ami4ccm test with out arguments
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : out_args_t_sender_impl.cpp[Header]

#include "out_args_t_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl[user_global_impl]

namespace InterOutArgsT_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl[user_namespace_impl]
  std::atomic_int nr_of_received_ {};

  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
         IDL::traits<InterOutArgsT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterOutArgsT::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                      << std::endl;

    IDL::traits< ::InterOutArgsT::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
          this->ciao_context_->get_connection_sendc_run_my_foo();

    if (!my_foo_ami_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo ok"
                      << std::endl;

    IDL::traits< ::InterOutArgsT::AMI4CCM_MyFooReplyHandler>::ref_type cb =
             CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

    CIAOX11_TEST_INFO << "Sender:\t->invoking async calls"
                      << std::endl;

    //Invoke Asynchronous calls to test
    my_foo_ami_->sendc_var_outs ( cb,"Send me a double and a long.");
    my_foo_ami_->sendc_var_div_outs (cb);
    my_foo_ami_->sendc_var_div2_outs (cb);
    my_foo_ami_->sendc_enum_out (cb);

    CIAOX11_TEST_INFO << "Sender:\t->finishing async generator"
                      << std::endl;

    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<InterOutArgsT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterOutArgsT::CCM_Sender_Context>::narrow (std::move(context));

  }
  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;
    IDL::traits<InterOutArgsT::MyFoo>::ref_type my_foo_ =
        this->ciao_context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo ok; invoking sync calls"
                      << std::endl;
    //run some synch calls
    InterOutArgsT::TestTopic test_topic {};
    InterOutArgsT::TopicString topic_str {};
    InterOutArgsT::TopicArray topic_arr {};
    double d_cmd {};
    int32_t l_cmd {};
    std::string out_str {};
    try
    {
      my_foo_->var_outs ("Do something synchronous",
                          out_str,d_cmd , l_cmd);
      if ( (d_cmd == 3.14 ) && (l_cmd == 100))
      {
        ++nr_of_received_;
      }
    }
    catch (const InterOutArgsT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "ERROR: synch_foo_generator::var_outs: "
                         << "Unexpected exception." << std::endl;
    }
    try
    {
      my_foo_->var_div_outs(test_topic,topic_str,topic_arr);
      if ((test_topic.key() == "aaa") &&
          (test_topic.x() == 10))
      {
        ++nr_of_received_;
      }
      else
      {
        CIAOX11_TEST_ERROR << "ERROR: synch_foo_generator::var_div_outs: "
                           << "Unexpected data returned." << std::endl;
      }
    }
    catch (const InterOutArgsT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "ERROR: synch_foo_generator::var_div_outs: "
                         << "Unexpected exception." << std::endl;
    }

    CIAOX11_TEST_INFO << "Sender:\t->finishing sync generator"
                      << std::endl;

    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[ccm_remove]
    if (nr_of_received_.load() == 6)
    {
      CIAOX11_TEST_INFO <<"OK: Sender received the expected number of"
                        <<     " callbacks for syn- and "
                        <<     "asynchronous calls" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR <<"ERROR: Sender not received the expected number"
                         << " of callbacks and returns  for syn- and "
                         <<     "asynchronous calls. Expected: 6,"
                         <<   " Received: "
                         <<  nr_of_received_.load() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<InterOutArgsT::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_outs (
    const std::string& answer,
    double d_cmd,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_outs]
    X11_UNUSED_ARG (answer);
    if (d_cmd != 3.14)
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::var_outs: "
                         << "received the wrong double, expected 3.14,"
                         << " received " << d_cmd << std::endl;
    }
    else if (l_cmd !=100)
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::var_outs: "
                         << "received the wrong long, expected 100,"
                         << " received " << l_cmd << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_outs]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_outs_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_outs_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_outs_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div_outs (
    const ::InterOutArgsT::TestTopic& test_topic,
    const ::InterOutArgsT::TopicString& topic_str,
    const ::InterOutArgsT::TopicArray& topic_arr)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_outs]
    // Your code here
    bool error = false;
    if ((test_topic.key() != "aaa") || (test_topic.x() != 10))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_exec_i::var_div_outs: "
                         << "received the wrong struct, "
                         << "expected key 'aaa', x = 10,"
                         << " received key '" <<  test_topic.key()<< "' , x = "
                         << test_topic.x() << std::endl;
      error = true;
    }
    if (( topic_str.key() != "bbb") ||
        ( topic_str.x_str() != "ccc"))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_exec_i::var_div_outs: "
                         << "received the wrong struct, "
                         << "expected key 'bbb', x = 'ccc',"
                         << " received key '" << topic_str.key() << "' , x = "
                         << topic_str.x_str() << std::endl;
      error = true;
    }
    if (( topic_arr.key() != "ddd") ||
        (topic_arr.x_array()[1] != 100))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_exec_i::var_div_outs: "
                         << "received the wrong struct, "
                         << "expected key 'ddd', second elem 100 ,"
                         << " received key '" << topic_arr.key() << "', second elem "
                         << topic_arr.x_array()[1] << std::endl;
      error = true;
    }
    if (error == false)
    {
      ++nr_of_received_;
    }

    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_outs]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div_outs_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_outs_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div_outs_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div2_outs (
    const ::InterOutArgsT::X_Union& x_uni,
    const ::InterOutArgsT::test_seq& seq)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_outs]
    // Your code here
    bool error = false;

    if (x_uni.x_long() != 11)
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_exec_i::var_div2_outs: "
                         << "received the wrong union, "
                         << "expected x_long = 11, received x_long = "
                         << x_uni.x_long() << std::endl;
      error = true;
    }
    if (( seq[0].x_teststr() != "fff") ||
        (seq[0].x_test() != 12))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_exec_i::var_div2_outs: "
                         << "received the wrong sequence, "
                         << "expected key 'fff', x = 12,"
                         << " received key '" << seq[0].x_teststr() << "' , x = "
                         <<  seq[0].x_test() << std::endl;
      error = true;
    }
    if (error == false)
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_outs]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::var_div2_outs_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_outs_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[var_div2_outs_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::enum_out (
    ::InterOutArgsT::test_enum out_test)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_out]
    // Your code here
    if (out_test != InterOutArgsT::test_enum::ONE)

     {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::enum_out: "
                         << "received the wrong value, expected ONE,received "
                         << (int) out_test << std::endl;
     }
   else
     {
       ++nr_of_received_;
     }
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_out]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::enum_out_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_out_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[enum_out_excep]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl[user_namespace_end_impl]

} // namespace InterOutArgsT_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Sender_Impl[factory]
extern "C" void
create_InterOutArgsT_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterOutArgsT_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : out_args_t_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
