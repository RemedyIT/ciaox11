// -*- C++ -*-
/**
 * @file    multi_inherit_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   sender of ami4ccm test with multiple inheritance
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : multi_inherit_sender_impl.cpp[Header]

#include "multi_inherit_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[user_global_impl]

namespace InterMulti_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[user_namespace_impl]
  std::atomic_int nr_of_received_ {};

  //============================================================
  // Worker thread for asynchronous invocations for One
  //============================================================
  asynch_one_generator::asynch_one_generator()
  {
  }

  void
  asynch_one_generator::set_context(
         IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterMulti::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_one_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    try
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_one "
                        << std::endl;

      IDL::traits<::InterMulti::AMI4CCM_One>::ref_type my_one_ami_  =
            this->ciao_context_->get_connection_sendc_run_my_one();

      if (!my_one_ami_)
      {
        CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_sendc_run_my_one "
                           << "returns null" << std::endl;
        return 1;
      }
      IDL::traits<::InterMulti::AMI4CCM_OneReplyHandler>::ref_type cb =
               CORBA::make_reference<AMI4CCM_OneReplyHandler_run_my_one_i> ();
      //Invoke Asynchronous calls to test
      my_one_ami_->sendc_foo ( cb, "Hi from asynch call ONE::foo", 1);
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_ERROR << "Sender::asynch_one_generator: caught unexepected exception [" <<
                            ex.what () << "]" << std::endl;
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "Sender::asynch_one_generator: caught unexepected C++ exception" <<
                            std::endl;
    }

    return 0;
  }
  //============================================================
   // Worker thread for asynchronous invocations for Two
   //============================================================
   asynch_two_generator::asynch_two_generator()
   {
   }

   void
   asynch_two_generator::set_context(
          IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context)
   {
     this->ciao_context_ = IDL::traits<InterMulti::CCM_Sender_Context>::narrow (std::move(context));
   }

   int asynch_two_generator::svc()
   {
     std::this_thread::sleep_for (std::chrono::seconds (3));
     try
     {
       CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_two "
                         << std::endl;

       IDL::traits<::InterMulti::AMI4CCM_Two>::ref_type my_two_ami_  =
             this->ciao_context_->get_connection_sendc_run_my_two();

       if (!my_two_ami_)
       {
         CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_sendc_run_my_two "
                           << "returns null" << std::endl;
         return 1;
       }
       IDL::traits<::InterMulti::AMI4CCM_TwoReplyHandler>::ref_type cb =
                CORBA::make_reference<AMI4CCM_TwoReplyHandler_run_my_two_i> ();

       //Invoke Asynchronous calls to test
       my_two_ami_->sendc_bar ( cb, 2);
     }
     catch (const std::exception& ex)
     {
       CIAOX11_TEST_ERROR << "Sender::asynch_two_generator: caught unexepected exception [" <<
                             ex.what () << "]" << std::endl;
     }
     catch (...)
     {
       CIAOX11_TEST_ERROR << "Sender::asynch_two_generator: caught unexepected C++ exception" <<
                             std::endl;
     }

     return 0;
   }
   //============================================================
    // Worker thread for asynchronous invocations for Three
    //============================================================
    asynch_three_generator::asynch_three_generator()
    {
    }

    void
    asynch_three_generator::set_context(
           IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context)
    {
      this->ciao_context_ = IDL::traits<InterMulti::CCM_Sender_Context>::narrow (std::move(context));
    }

    int asynch_three_generator::svc()
    {
      std::this_thread::sleep_for (std::chrono::seconds (3));
      try
      {
        CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_three "
                          << std::endl;

        IDL::traits<::InterMulti::AMI4CCM_Three>::ref_type my_three_ami_  =
              this->ciao_context_->get_connection_sendc_run_my_three();

        if (!my_three_ami_)
        {
          CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_sendc_run_my_three "
                            << "returns null" << std::endl;
          return 1;
        }
        IDL::traits<::InterMulti::AMI4CCM_ThreeReplyHandler>::ref_type cb =
                 CORBA::make_reference<AMI4CCM_ThreeReplyHandler_run_my_three_i> ();

        //Invoke Asynchronous calls to test
        my_three_ami_->sendc_plus(cb, 3);
        // derived from CLASS ONE
        my_three_ami_->sendc_foo (cb,"hoi", 3);
        // derived fron CLASS TWO
        my_three_ami_->sendc_bar (cb, 3);
      }
      catch (const std::exception& ex)
      {
        CIAOX11_TEST_ERROR << "Sender::asynch_three_generator: caught unexepected exception [" <<
                              ex.what () << "]" << std::endl;
      }
      catch (...)
      {
        CIAOX11_TEST_ERROR << "Sender::asynch_three_generator: caught unexepected C++ exception" <<
                              std::endl;
      }

      return 0;
    }

  //============================================================
  // Worker thread for synchronous invocations for One
  //============================================================
  synch_one_generator::synch_one_generator ()
  {
  }
  void
  synch_one_generator::set_context(
     IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterMulti::CCM_Sender_Context>::narrow (std::move(context));

  }
  int synch_one_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    try
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_one " << std::endl;
      IDL::traits<InterMulti::One>::ref_type my_one_ =
          this->ciao_context_->get_connection_run_my_one();

      if (!my_one_)
      {
        CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_run_my_one "
                          << "returns null" << std::endl;
        return 1;
      }

      //run some synch calls
      std::string answer {};
      int32_t result = my_one_->foo (
                              "Synchronous call foo from class One",
                              1,
                              answer);
      if (result != 1)
      {
        CIAOX11_TEST_ERROR << "ERROR Sender (SYNCH) : CLASS One foo !" << std::endl;
      }
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_ERROR << "Sender::synch_one_generator: caught unexepected exception [" <<
                            ex.what () << "]" << std::endl;
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "Sender::synch_one_generator: caught unexepected C++ exception" <<
                            std::endl;
    }

    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for Three
  //============================================================
  synch_three_generator::synch_three_generator ()
  {
  }
  void
  synch_three_generator::set_context(
     IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<InterMulti::CCM_Sender_Context>::narrow (std::move(context));

  }
  int synch_three_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    try
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_three " << std::endl;
      IDL::traits<InterMulti::One>::ref_type my_three_ =
          this->ciao_context_->get_connection_run_my_three();

      if (!my_three_)
      {
        CIAOX11_TEST_ERROR << "ERROR: Sender:\t->get_connection_run_my_three "
                          << "returns null" << std::endl;
        return 1;
      }

      //run some synch calls
      std::string answer {};
      int32_t result = my_three_->foo (
                              "Synchronous call foo from class Three"
                              " derived from class ONE",
                              3,
                              answer);
      if (result != 3)
      {
        CIAOX11_TEST_ERROR << "ERROR Sender (SYNCH) : CLASS Three foo !" << std::endl;
      }
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_ERROR << "Sender::synch_three_generator: caught unexepected exception [" <<
                            ex.what () << "]" << std::endl;
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "Sender::synch_three_generator: caught unexepected C++ exception" <<
                            std::endl;
    }

    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_one_gen_.set_context(this->context_);
    this->synch_one_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_one_gen_.set_context(this->context_);
    this->asynch_one_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_two_gen_.set_context(this->context_);
    this->asynch_two_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->synch_three_gen_.set_context(this->context_);
    this->synch_three_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_three_gen_.set_context(this->context_);
    this->asynch_three_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[ccm_remove]
    if (nr_of_received_.load() != 5)
    {
      CIAOX11_TEST_ERROR << "ERROR: Did not get all callbacks for derived classes."
                         << " Received = " << nr_of_received_.load() << " of 5"
                         << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK: All messages received back by Sender" << std::endl;
      }

    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<InterMulti::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_OneReplyHandler_run_my_one_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[ctor]
  AMI4CCM_OneReplyHandler_run_my_one_i::AMI4CCM_OneReplyHandler_run_my_one_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[ctor]

  AMI4CCM_OneReplyHandler_run_my_one_i::~AMI4CCM_OneReplyHandler_run_my_one_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_private_ops]

  void
  AMI4CCM_OneReplyHandler_run_my_one_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_INFO << "OK: Get asynchronous callback from ONE::foo,"
                     << " answer = " << answer << std::endl;
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[foo]
  }

  void AMI4CCM_OneReplyHandler_run_my_one_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[foo_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[foo_excep]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_TwoReplyHandler_run_my_two_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[ctor]
  AMI4CCM_TwoReplyHandler_run_my_two_i::AMI4CCM_TwoReplyHandler_run_my_two_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[ctor]

  AMI4CCM_TwoReplyHandler_run_my_two_i::~AMI4CCM_TwoReplyHandler_run_my_two_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_private_ops]

  void
  AMI4CCM_TwoReplyHandler_run_my_two_i::bar (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[bar]
    // Your code here
    CIAOX11_TEST_INFO << "OK: Get asynchronous callback from TWO::bar,"
                     << " answer = " << answer << std::endl;
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[bar]
  }

  void AMI4CCM_TwoReplyHandler_run_my_two_i::bar_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[bar_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[bar_excep]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_ThreeReplyHandler_run_my_three_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[ctor]
  AMI4CCM_ThreeReplyHandler_run_my_three_i::AMI4CCM_ThreeReplyHandler_run_my_three_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[ctor]

  AMI4CCM_ThreeReplyHandler_run_my_three_i::~AMI4CCM_ThreeReplyHandler_run_my_three_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_private_ops]

  void
  AMI4CCM_ThreeReplyHandler_run_my_three_i::plus (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[plus]
    // Your code here
    CIAOX11_TEST_INFO << "OK: Get asynchronous callback from THREE::plus,"
                     << " answer = " << answer << std::endl;
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[plus]
  }

  void AMI4CCM_ThreeReplyHandler_run_my_three_i::plus_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[plus_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[plus_excep]
  }

  void
  AMI4CCM_ThreeReplyHandler_run_my_three_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_INFO << "OK: Get asynchronous callback from THREE::foo,"
                     << " answer = " << answer << std::endl;
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[foo]
  }

  void AMI4CCM_ThreeReplyHandler_run_my_three_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[foo_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[foo_excep]
  }

  void
  AMI4CCM_ThreeReplyHandler_run_my_three_i::bar (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[bar]
    // Your code here
    CIAOX11_TEST_INFO << "OK: Get asynchronous callback from THREE::bar,"
                     << " answer = " << answer << std::endl;
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[bar]
  }

  void AMI4CCM_ThreeReplyHandler_run_my_three_i::bar_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[bar_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[bar_excep]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[user_namespace_end_impl]

} // namespace InterMulti_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[factory]
extern "C" void
create_InterMulti_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterMulti_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : multi_inherit_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
