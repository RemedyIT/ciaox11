// -*- C++ -*-
/**
 * @file    hello_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   Receiver component exec
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_receiver_impl.cpp[Header]

#include "hello_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl[user_global_impl]

namespace UsesMulti_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_one_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::do_my_one_exec_i[ctor]
  do_my_one_exec_i::do_my_one_exec_i (
      IDL::traits<UsesMulti::CCM_Receiver_Context>::ref_type context,
    uint32_t &nr_of_messages)
    : context_ (std::move (context)),
      nr_of_messages_ (nr_of_messages)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::do_my_one_exec_i[ctor]

  do_my_one_exec_i::~do_my_one_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::do_my_one_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::do_my_one_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::do_my_one_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::do_my_one_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::do_my_one_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::do_my_one_exec_i[user_private_ops]


  /** Operations and attributes from do_my_one */

  int32_t
  do_my_one_exec_i::foo (
      const std::string& in_str,
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::do_my_one_exec_i::foo[_in_str_cmd_answer]
    ++nr_of_messages_;
    CIAOX11_TEST_INFO << "Receiver_exec_i::do_my_one_exec_i::foo cmd: " << cmd << std::endl;
    answer = in_str + " hello you";
    return cmd + 300;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::do_my_one_exec_i::foo[_in_str_cmd_answer]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
    {
    }
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[configuration_complete]
    CIAOX11_TEST_INFO << "Receiver_exec_i::configuration_complete." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "Receiver_exec_i::ccm_activate." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Each instance of the Reciever receives 2 asynchronous messages,
    // some instances also receive 1 synchronous call
    if  ((nr_of_messages_ !=  2) && (nr_of_messages_ !=  3))
    {
      CIAOX11_TEST_ERROR << "ERROR Receiver_exec_i::ccm_remove."
                         << "Didn't receive the expected nr_of messages."
                         << " Expected <2> or <3>. received <" << nr_of_messages_
                         << ">." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::UsesMulti::CCM_One >::ref_type
  Receiver_exec_i::get_do_my_one ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[get_do_my_one]
    CIAOX11_TEST_INFO << "Receiver_exec_i::get_do_my_one." << std::endl;
    if (!this->do_my_one_)
    {
      this->do_my_one_ =
        CORBA::make_reference <do_my_one_exec_i> (this->context_,
                                                  this->nr_of_messages_);
    }
    return this->do_my_one_;
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[get_do_my_one]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl::Receiver_exec_i[set_session_context]
    CIAOX11_TEST_INFO << "Receiver_exec_i::set_session_context." << std::endl;
    this->context_ = IDL::traits<UsesMulti::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl[user_namespace_end_impl]

} // namespace UsesMulti_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Receiver_Impl[factory]
extern "C" void
create_UsesMulti_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UsesMulti_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
