// -*- C++ -*-
/**
 * @file    out_args_t_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   receiver of ami4ccm test with out arguments
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : out_args_t_receiver_impl.cpp[Header]

#include "out_args_t_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl[user_global_impl]

namespace InterOutArgsT_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[ctor]
  do_my_foo_exec_i::do_my_foo_exec_i (
    IDL::traits<InterOutArgsT::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[ctor]

  do_my_foo_exec_i::~do_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from do_my_foo */

  void
  do_my_foo_exec_i::var_outs (
      const std::string& in_str,
      std::string& answer,
      double& d_cmd,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::var_outs[_in_str_answer_d_cmd_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer = "This is my answer from var_outs";
    d_cmd = 3.14;
    l_cmd = 100;

    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::var_outs[_in_str_answer_d_cmd_l_cmd]
  }

  void
  do_my_foo_exec_i::var_div_outs (
      ::InterOutArgsT::TestTopic& test_topic,
      ::InterOutArgsT::TopicString& topic_str,
      ::InterOutArgsT::TopicArray& topic_arr)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::var_div_outs[_test_topic_topic_str_topic_arr]

    test_topic.key () ="aaa";
    test_topic.x () = 10;

    topic_str.key() = "bbb";
    topic_str.x_str() = "ccc";

    topic_arr.key() = "ddd";
    for (uint16_t i = 0; i < 5; i ++)
    {
      topic_arr.x_array()[i] = i * 100;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::var_div_outs[_test_topic_topic_str_topic_arr]
  }

  void
  do_my_foo_exec_i::var_div2_outs (
      ::InterOutArgsT::X_Union& x_uni,
      ::InterOutArgsT::test_seq& seq)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::var_div2_outs[_x_uni_seq]
    x_uni.x_long(11);

    InterOutArgsT::test ttt;
    ttt.x_test () = 12;
    ttt.x_teststr () = "fff" ;
    seq.resize(2);
    seq[0]= ttt;
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::var_div2_outs[_x_uni_seq]
  }

  void
  do_my_foo_exec_i::enum_out (
      ::InterOutArgsT::test_enum& out_test)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::enum_out[_out_test]
    out_test = ::InterOutArgsT::test_enum::ONE;
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::do_my_foo_exec_i::enum_out[_out_test]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::InterOutArgsT::CCM_MyFoo>::ref_type
  Receiver_exec_i::get_do_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  if (!this->do_my_foo_)
  {
    this->do_my_foo_ = CORBA::make_reference <do_my_foo_exec_i> (this->context_);
  }
  return this->do_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<InterOutArgsT::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl[user_namespace_end_impl]

} // namespace InterOutArgsT_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterOutArgsT_Receiver_Impl[factory]
extern "C" void
create_InterOutArgsT_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterOutArgsT_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterOutArgsT_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : out_args_t_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
