// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   header sender compomnent
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[user_global_impl]

namespace UsesMulti_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[user_namespace_impl]
  //============================================================
  // Worker thread for synchronous invocations for One
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<UsesMulti::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<UsesMulti::CCM_Sender_Context>::narrow (std::move(context));
  }

  int synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));

    CIAOX11_TEST_INFO << "Sender:\tsynch_foo_generator started" <<  std::endl;

    ::UsesMulti::CCM_Sender::m_run_my_oneConnections m_run_my_one_seq_ =
         ciao_context_->get_connections_m_run_my_one();

    if (m_run_my_one_seq_.size() != 2)
    {
      CIAOX11_TEST_ERROR
           << "ERROR: SENDER - get_connections_m_run_my_one - "
           << "didn't return <2> connections, but <"
           << m_run_my_one_seq_.size() << ">."<< std::endl;
    }

   for(::UsesMulti::CCM_Sender::m_run_my_oneConnection run_my_foo_ : m_run_my_one_seq_)
   {
     int32_t cmd_ = 100;
     std::string hello_;

     int32_t answer_ = run_my_foo_.objref()->foo( "Hi,", cmd_, hello_);

     CIAOX11_TEST_INFO << "Sender:\tInvoked synchronous call foo, returns :"
                       << hello_ <<  std::endl;

     if ((hello_ != "Hi, hello you") || (answer_ != 400))
     {
       CIAOX11_TEST_ERROR << "Sender:\tError invoking synchronous call foo, "
                         << "returns : <" << hello_ <<  "> and <"
                         << answer_ << ">." << std::endl;
       return 1;
     }

     answer_ = run_my_foo_.objref()->foo( "Hey,", cmd_, hello_);

     CIAOX11_TEST_INFO << "Sender:\tInvoked synchronous call foo, returns :"
                       << hello_ <<  std::endl;

     if ((hello_ != "Hey, hello you") || (answer_ != 400))
     {
       CIAOX11_TEST_ERROR << "Sender:\tError invoking synchronous call foo, "
                         << "returns : <" << hello_ <<  "> and <"
                         << answer_ << ">." << std::endl;
       return 1;
     }
   }
   CIAOX11_TEST_INFO << "Sender (SYNCH) :\tInvoked "
                     << " 2 synchronous call for each connection"
                     << std::endl;

   return 0;
   }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
    {
    }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[configuration_complete]
    CIAOX11_TEST_INFO << "Sender_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[ccm_activate]
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "Sender_exec_i::ccm_remove." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[set_session_context]
    CIAOX11_TEST_INFO << "Sender_exec_i::set_session_context." << std::endl;
    this->context_ = IDL::traits<UsesMulti::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[user_namespace_end_impl]

} // namespace UsesMulti_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[factory]
extern "C" void
create_UsesMulti_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UsesMulti_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
