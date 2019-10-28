// -*- C++ -*-
/**
 * @file    uses_s_m_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   sender of ami4ccm test with combination of uses multiple and simplex
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : uses_s_m_sender_impl.cpp[Header]

#include "uses_s_m_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <atomic>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[user_global_impl]

namespace UsesSM_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[user_namespace_impl]
  bool asynch = false;
  std::atomic_int nr_of_received_ {};
  std::atomic_int nr_of_sent_ {};

  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
         IDL::traits<UsesSM::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<UsesSM::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));

    //multiple
    ::UsesSM::CCM_Sender::sendc_m_run_my_oneConnections m_run_my_one_seq_ =
              ciao_context_->get_connections_sendc_m_run_my_one();

    if (m_run_my_one_seq_.size() != 3)
    {
      CIAOX11_TEST_ERROR
             << "ERROR: SENDER.- get_connections_m_run_my_one "
             << "didn't return <3> connections, but <"
             << m_run_my_one_seq_.size() << ">."<< std::endl;
      return 1;
    }
    //simplex
    IDL::traits< ::UsesSM::AMI4CCM_Two>::ref_type my_two_ami_  =
           this->ciao_context_->get_connection_sendc_s_run_my_two();

    if (!my_two_ami_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }

    int32_t i {};
    // Invoke Asynchronous calls to test, send one message foo per one connection
    // and send one message bar to all connections
    for(::UsesSM::CCM_Sender::sendc_m_run_my_oneConnection my_one_ami_ : m_run_my_one_seq_)
    {
      IDL::traits< ::UsesSM::AMI4CCM_OneReplyHandler>::ref_type cb_one =
        CORBA::make_reference< AMI4CCM_OneReplyHandler_m_run_my_one_i> ();

      std::string test;
      switch (i)
      {
        case 0:
          test = "Asynch. foo call one";
          break;
        case 1:
          test = "Asynch. foo call two";
          break;
        case 2:
          test = "Asynch. foo call three";
          break;
        default:
          break;
      }
      ++nr_of_sent_;
      my_one_ami_.objref()->sendc_foo (cb_one, test, i);

      CIAOX11_TEST_INFO << "Sender (ASYNCH) : send " << test << std::endl;
      // There is more than 1 message sent, without receiving callbacks,
      // so it is asynchronous
      if (nr_of_sent_.load() > 1)
      {
        asynch = true;
      }

      CIAOX11_TEST_INFO << "Sender (ASYNCH) : send asynch call bar " << i <<std::endl;
      IDL::traits< ::UsesSM::AMI4CCM_TwoReplyHandler>::ref_type cb_two =
        CORBA::make_reference< AMI4CCM_TwoReplyHandler_s_run_my_two_i> ();
      my_two_ami_->sendc_bar ( cb_two, i);
      i++;

    }
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<UsesSM::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<UsesSM::CCM_Sender_Context>::narrow (std::move(context));

  }
  int synch_foo_generator::svc ()
  {

    ::UsesSM::CCM_Sender::m_run_my_oneConnections m_run_my_one_seq_ =
         ciao_context_->get_connections_m_run_my_one();

    if (m_run_my_one_seq_.size() != 3)
    {
      CIAOX11_TEST_ERROR
           << "ERROR: SENDER.- get_connections_m_run_my__one "
           << ">didn't return <3> connections, but <"
           << m_run_my_one_seq_.size() << ">."<< std::endl;
      return 1;
    }
    // Invoke synchronous calls to test, send one message per one connection
    uint32_t i = 0;
    for(::UsesSM::CCM_Sender::m_run_my_oneConnection my_one_ami_ : m_run_my_one_seq_)
    {
      std::string test;
      switch (i)
      {
        case 0:
          test = "Synch. call 0.";
          break;
        case 1:
          test = "Synch. call 1";
          break;
        case 2:
          test = "Synch. call 2";
          break;
        default:
        break;
      }
      CIAOX11_TEST_DEBUG << "Sender (SYNCH) : send " << test << std::endl;

      std::string answer;
      uint32_t result = my_one_ami_.objref()->foo( test, i, answer);
      if (result != i)
      {
        CIAOX11_TEST_ERROR
                   << "ERROR Sender (SYNCH) : CLASS One foo !" << std::endl;
      }
      else
      {
         ++nr_of_received_;
         CIAOX11_TEST_DEBUG << "Sender (SYNCH) : received answer = "
                            << answer << std::endl;
      }
      i++;
    }
    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[ccm_remove]
    if (asynch == false)
    {
      CIAOX11_TEST_ERROR << "ERROR: Uses multiple test not asynchronous!" << std::endl;
    }
    if (nr_of_received_.load() != 9)
    {
      CIAOX11_TEST_ERROR << "ERROR: Did not get all callbacks from multiple ports."
                         << " Received = " << nr_of_received_.load() << " of 9"
                         << std::endl;
    }
    else
    {
      CIAOX11_TEST_DEBUG << "OK: All messages received back by Sender" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<UsesSM::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_OneReplyHandler_m_run_my_one_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[ctor]
  AMI4CCM_OneReplyHandler_m_run_my_one_i::AMI4CCM_OneReplyHandler_m_run_my_one_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[ctor]

  AMI4CCM_OneReplyHandler_m_run_my_one_i::~AMI4CCM_OneReplyHandler_m_run_my_one_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_private_ops]

  void
  AMI4CCM_OneReplyHandler_m_run_my_one_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[foo]
    // Your code here
    X11_UNUSED_ARG (ami_return_val);
    CIAOX11_TEST_DEBUG << "Sender: Get asynchronous callback from foo,"
                       << " answer = " << answer << std::endl;
     ++nr_of_received_;
     --nr_of_sent_;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[foo]
  }

  void
  AMI4CCM_OneReplyHandler_m_run_my_one_i::foo_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[foo_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[foo_excep]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_TwoReplyHandler_s_run_my_two_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[ctor]
  AMI4CCM_TwoReplyHandler_s_run_my_two_i::AMI4CCM_TwoReplyHandler_s_run_my_two_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[ctor]

  AMI4CCM_TwoReplyHandler_s_run_my_two_i::~AMI4CCM_TwoReplyHandler_s_run_my_two_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_private_ops]

  void
  AMI4CCM_TwoReplyHandler_s_run_my_two_i::bar (
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[bar]
    // Your code here
    CIAOX11_TEST_DEBUG << "Sender: Get asynchronous callback from bar,"
                       << " answer =" << answer << std::endl;
    ++nr_of_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[bar]
  }

  void
  AMI4CCM_TwoReplyHandler_s_run_my_two_i::bar_excep (
    IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[bar_excep]
    // Your code here
    excep_holder->raise_exception ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[bar_excep]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[user_namespace_end_impl]

} // namespace UsesSM_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[factory]
extern "C" void
create_UsesSM_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UsesSM_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
