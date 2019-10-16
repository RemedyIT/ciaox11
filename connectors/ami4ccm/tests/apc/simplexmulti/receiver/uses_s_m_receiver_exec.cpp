// -*- C++ -*-
/**
 * @file    uses_s_m_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   receiver of ami4ccm test with combination of uses multiple and simplex
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : uses_s_m_receiver_impl.cpp[Header]

#include "uses_s_m_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[user_global_impl]

namespace UsesSM_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_one_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[ctor]
  do_my_one_exec_i::do_my_one_exec_i (
    IDL::traits<UsesSM::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[ctor]

  do_my_one_exec_i::~do_my_one_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[user_private_ops]


  /** Operations and attributes from do_my_one */

  int32_t
  do_my_one_exec_i::foo (
      const std::string& in_str,
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i::foo[_in_str_cmd_answer]
    // sleep to make it possible to test asynchronous behavior.
    std::this_thread::sleep_for (std::chrono::seconds (2));
    ++this->nr_of_one_received_;
    answer = in_str;
    return cmd;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i::foo[_in_str_cmd_answer]
  }
  /**
   * Facet Executor Implementation Class : do_my_two_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[ctor]
  do_my_two_exec_i::do_my_two_exec_i (
    IDL::traits<UsesSM::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[ctor]

  do_my_two_exec_i::~do_my_two_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[user_private_ops]


  /** Operations and attributes from do_my_two */

  void
  do_my_two_exec_i::bar (
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i::bar[_cmd_answer]
    X11_UNUSED_ARG(cmd);
    ++this->nr_of_two_received_;
    answer = "answer TWO::bar";
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i::bar[_cmd_answer]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "Receiver_exec_i::ccm_passivate  " << std::endl;
    uint32_t nr_received_one {};
    uint32_t nr_received_two {};
    auto rec_one = IDL::traits<do_my_one_exec_i>::narrow (this->do_my_one_);
    if (rec_one)
    {
      nr_received_one = rec_one->get_nr_received ();
    }
    auto rec_two = IDL::traits<do_my_two_exec_i>::narrow (this->do_my_two_);
    if (rec_two)
    {
      nr_received_two = rec_two->get_nr_received ();
    }
    //this receiver instance received my_one foo, or this is a receiver instance
    //that received my_two bar . This is arranged in the deployment plan .
    if (((nr_received_one == 2) &&
         (nr_received_two == 0)) ||
        ((nr_received_two  == 3) &&
         (nr_received_one == 0)))
    {
      if (nr_received_one == 2)
      {
        CIAOX11_TEST_INFO << "OK: Receiver received the expected "
                          << "number (2) of correct calls for foo "
                          << std::endl;
      }
      else
      {
        CIAOX11_TEST_INFO << "OK: Receiver received the expected "
                          << "number (3) of correct calls for bar "
                          << std::endl;
      }
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR: Receiver didn't receive the expected "
                         << "number of correct calls."
                         << "Expected 2 calls for foo but received " <<  nr_received_one
                         << "or Expected 3 calls for bar but received "
                         << nr_received_two << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[ccm_remove]
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::UsesSM::CCM_One >::ref_type
  Receiver_exec_i::get_do_my_one ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[get_do_my_one]
    if (!this->do_my_one_)
    {
      this->do_my_one_ = CORBA::make_reference <do_my_one_exec_i> (this->context_);
    }
    return this->do_my_one_;
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[get_do_my_one]
  }

  IDL::traits< ::UsesSM::CCM_Two >::ref_type
  Receiver_exec_i::get_do_my_two ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[get_do_my_two]
    if (!this->do_my_two_)
    {
      this->do_my_two_ = CORBA::make_reference <do_my_two_exec_i> (this->context_);
    }
    return this->do_my_two_;
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[get_do_my_two]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<UsesSM::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[user_namespace_end_impl]

} // namespace UsesSM_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[factory]
extern "C" void
create_UsesSM_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UsesSM_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
