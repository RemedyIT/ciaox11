// -*- C++ -*-
/**
 * @file    return_args_t_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   sender of ami4ccm test with several return types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : return_args_t_sender_impl.cpp[Header]

#include "return_args_t_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[user_global_impl]

namespace InterReturnT_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[user_namespace_impl]
  std::atomic_int nr_of_received_ {};

  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
         IDL::traits<InterReturnT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterReturnT::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                      << std::endl;

    IDL::traits< ::InterReturnT::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
          this->ciao_context_->get_connection_sendc_run_my_foo();

    if (!my_foo_ami_)
    {
      CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }

    try
    {
      IDL::traits< ::InterReturnT::AMI4CCM_MyFooReplyHandler>::ref_type cb =
        CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> ();

      //Invoke Asynchronous calls to test
      my_foo_ami_->sendc_ret_void (cb, "Send me a void." );
      my_foo_ami_->sendc_ret_long (cb,"Send me a long.");
      my_foo_ami_->sendc_ret_double (cb,"Send me a double.");
      my_foo_ami_->sendc_ret_struct (cb, "Send me a struct.");
      my_foo_ami_->sendc_ret_array (cb,"Send me an array.");
      my_foo_ami_->sendc_ret_seq (cb,"Send me a sequence.");
      my_foo_ami_->sendc_ret_union (cb,"Send me a union.");
      my_foo_ami_->sendc_ret_enum (cb,"Send me a enum value.");
    }
    catch (const CORBA::Exception& ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: Sender asynch_foo_generator(): Unexpected exception." << ex << std::endl;
    }
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<InterReturnT::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterReturnT::CCM_Sender_Context>::narrow (std::move(context));

  }
  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;
    IDL::traits<InterReturnT::MyFoo>::ref_type my_foo_ =
        this->ciao_context_->get_connection_run_my_foo();
    if (!my_foo_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }
    //run some synch calls
    InterReturnT::TestStruct test_topic {};
    int32_t l_cmd {};
    std::string out_str {};
    try
    {
      double ret =
           my_foo_->ret_double ("Send me synch double",out_str, l_cmd);
       if ( (ret == 3.14 ) && (l_cmd == 3))
       {
         ++nr_of_received_;
       }
    }
    catch (const InterReturnT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "ERROR: synch_foo_generator::ret_double: "
                            "Unexpected exception." << std::endl;
    }
    try
    {
      InterReturnT::TestArray arr =
           my_foo_->ret_array ("Send me synch array",out_str, l_cmd);
      if ((l_cmd != 5) || (arr[1].x_array()[2] != 102))
      {
        CIAOX11_TEST_ERROR << "ERROR MyFoo synchronous ret_array: "
                               "received the wrong long or array, expected 5 "
                               "and 102, received " << l_cmd << " and "
                               << arr[1].x_array()[2]<< std::endl;
      }
      else
      {
        ++nr_of_received_;
      }
    }
    catch (const InterReturnT::InternalError&)
    {
      CIAOX11_TEST_ERROR << "ERROR: synch_foo_generator::ret_array: "
                            "Unexpected exception."<< std::endl;
    }

    InterReturnT::TestStruct struct_return_val =
            my_foo_->ret_struct ("Send me synch struct",out_str, l_cmd);
    if (l_cmd != 4)
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_struct: "
                            "received the wrong long, expected 4,"
                            " received " << l_cmd<< std::endl;
    }
    else if ((struct_return_val.key() != "aaa") ||
             (struct_return_val.x() != 10))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_struct: "
                            "received the struct return, expected 'aaa' "
                            "and 10, received " << struct_return_val.key() << " and "
                            <<struct_return_val.x()<< std::endl;
    }
    else
    {
      ++nr_of_received_;
    }

    const InterReturnT::TestSeq seq_return_val =
          my_foo_->ret_seq ("Send me synch struct",out_str, l_cmd);
    if ((l_cmd != 6)|| (seq_return_val.size() == 0))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_seq: "
                         << "received the wrong long, expected 6,"
                         <<" received " << l_cmd<< std::endl;
    }
    else
    {
      ++nr_of_received_;
    }

    InterReturnT::X_Union union_return_val =
          my_foo_->ret_union ("Send me synch union",out_str, l_cmd);

    if ((l_cmd != 7) || (union_return_val.x_long() != 11))
    {
       CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_union: "
                          << "received the wrong long or union, expected 7"
                          << " and 11, received " << l_cmd << " and "
                          << union_return_val.x_long() << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }

    InterReturnT::test_enum enum_return_val =
        my_foo_->ret_enum ("Send me synch enum",out_str, l_cmd);

    if ((l_cmd != 8) || (enum_return_val != InterReturnT::test_enum::TWO))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_enum: "
                         << "received the wrong long or enum value, expected 8"
                         << " and TWO, received " << l_cmd << " and "
                         << (int) enum_return_val << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }

    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[ccm_remove]
    if (nr_of_received_.load() == 14)
    {
      CIAOX11_TEST_INFO << "OK: Sender received the expected number of"
                        << " callbacks for syn- and "
                        << "asynchronous calls" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR: Sender not received the expected number"
                         << " of callbacks and returns  for syn- and "
                         << "asynchronous calls. Expected: 14,"
                         << " Received: "
                         <<  nr_of_received_.load() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<InterReturnT::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_void (
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_void]
    // Your code here
    X11_UNUSED_ARG (answer);
    if (l_cmd != 1)
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_void: "
                         << "received the wrong long, expected 1,"
                         << " received " << l_cmd << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_void]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_void_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_void_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_void_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_long (
    int32_t ami_return_val,
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_long]
    // Your code here
    X11_UNUSED_ARG (answer);
    if ((l_cmd != 2) || (ami_return_val != 200))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_long: "
                         << "received the wrong longs, expected 2 and 200,"
                         << " received " << l_cmd << " and "
                         << ami_return_val << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_long]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_long_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_long_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_long_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_double (
    double ami_return_val,
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_double]
    // Your code here
    X11_UNUSED_ARG (answer);
    if ((l_cmd != 3) || (ami_return_val != 3.14))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_double: "
                         << "received the wrong returns, expected 3 "
                         << "and 3.14,received " << l_cmd << " and "
                         << ami_return_val << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_double]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_double_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_double_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_double_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_struct (
    const ::InterReturnT::TestStruct& ami_return_val,
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_struct]
    // Your code here
    X11_UNUSED_ARG (answer);
    if (l_cmd != 4)
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_struct: "
                         << "received the wrong long, expected 4,"
                         << " received " << l_cmd << std::endl;
    }
    else if ((ami_return_val.key() != "aaa") ||
             (ami_return_val.x() != 10))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_struct: "
                         << "received the struct return, expected 'aaa' "
                         << "and 10, received " << ami_return_val.key() << "and "
                         << ami_return_val.x() << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_struct]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_struct_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_struct_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_struct_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_array (
    const ::InterReturnT::TestArray& ami_return_val,
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_array]
    // Your code here
    X11_UNUSED_ARG (answer);
    if ((l_cmd != 5) || (ami_return_val[1].x_array()[2] != 102))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_array: "
                         << "received the wrong long or array, expected 5 "
                         << "and 102,received " << l_cmd << " and "
                         << ami_return_val[1].x_array()[2] << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_array]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_array_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_array_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_array_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_seq (
    const ::InterReturnT::TestSeq& ami_return_val,
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_seq]
    // Your code here
    X11_UNUSED_ARG (answer);
    if (l_cmd != 6)
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_seq: "
                         << "received the wrong long, expected 6,"
                         << " received " << l_cmd << std::endl;
    }
    else if ((ami_return_val[0].x_teststr () != "ccc") ||
             (ami_return_val[1].x_test () != 12))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_seq: "
                         << "didn't receive the expected sequence,"
                         << " received " << ami_return_val[0].x_teststr() <<" and "
                         <<     ami_return_val[1].x_test () << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_seq]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_seq_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_seq_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_seq_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_union (
    const ::InterReturnT::X_Union& ami_return_val,
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_union]
    // Your code here
    X11_UNUSED_ARG (answer);
    if ((l_cmd != 7) || (ami_return_val.x_long() != 11))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_union: "
                         << "received the wrong long or union, expected 7"
                         << " and 11, received " << l_cmd << " and "
                         << ami_return_val.x_long() << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_union]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_union_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_union_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_union_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_enum (
    ::InterReturnT::test_enum ami_return_val,
    const std::string& answer,
    int32_t l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_enum]
    // Your code here
    X11_UNUSED_ARG (answer);
    if ((l_cmd != 8) || (ami_return_val != InterReturnT::test_enum::TWO))
    {
      CIAOX11_TEST_ERROR << "ERROR MyFoo_callback_exec_i::ret_enum: "
                         << "received the wrong long or enum value, expected 8"
                         << " and TWO, received " << l_cmd << " and "
                         << (int) ami_return_val << std::endl;
    }
    else
    {
      ++nr_of_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_enum]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::ret_enum_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_enum_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ret_enum_excep]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[user_namespace_end_impl]

} // namespace InterReturnT_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[factory]
extern "C" void
create_InterReturnT_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterReturnT_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : return_args_t_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
