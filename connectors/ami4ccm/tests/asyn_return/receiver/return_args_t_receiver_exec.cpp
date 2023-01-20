// -*- C++ -*-
/**
 * @file    return_args_t_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   receiver of ami4ccm test with several return types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : return_args_t_receiver_impl.cpp[Header]

#include "return_args_t_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl[user_global_impl]

namespace InterReturnT_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i[ctor]
  do_my_foo_exec_i::do_my_foo_exec_i (
    IDL::traits<InterReturnT::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i[ctor]

  do_my_foo_exec_i::~do_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from do_my_foo */

  void
  do_my_foo_exec_i::ret_void (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_void[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer = "This is my answer from ret_void";
    l_cmd = 1;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_void[_in_str_answer_l_cmd]
  }

  int32_t
  do_my_foo_exec_i::ret_long (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_long[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer ="This is my answer from ret_long";
    l_cmd = 2;
    return 200;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_long[_in_str_answer_l_cmd]
  }

  double
  do_my_foo_exec_i::ret_double (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_double[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer = "This is my answer from ret_double";
    l_cmd = 3;
    return 3.14;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_double[_in_str_answer_l_cmd]
  }

  ::InterReturnT::TestStruct
  do_my_foo_exec_i::ret_struct (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_struct[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer = "This is my answer from ret_struct";
    l_cmd = 4;
    InterReturnT::TestStruct test_struct = {};
    test_struct.key ("aaa");
    test_struct.x (10);
    return test_struct;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_struct[_in_str_answer_l_cmd]
  }

  ::InterReturnT::TestArray
  do_my_foo_exec_i::ret_array (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_array[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer = "This is my answer from ret_array";
    l_cmd = 5;
    InterReturnT::TestArray test_array;
    for ( uint16_t i = 0; i < 5; i ++)
    {
      test_array[i].key ("bbb");
      for (uint16_t y = 0; y < 5; y ++)
      {
        test_array[i].x_array()[y] = i * 100 + y ;
      }
     }
     return test_array;

    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_array[_in_str_answer_l_cmd]
  }

  ::InterReturnT::TestSeq
  do_my_foo_exec_i::ret_seq (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_seq[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    X11_UNUSED_ARG(answer);
    l_cmd = 6;
    InterReturnT::test ttt;
    ttt.x_test(12);
    ttt.x_teststr ("ccc");
    InterReturnT::TestSeq seq {};
    seq.push_back(ttt);
    ttt.x_teststr ("ddd");
    seq.push_back(ttt);
    return seq;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_seq[_in_str_answer_l_cmd]
  }

  ::InterReturnT::X_Union
  do_my_foo_exec_i::ret_union (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_union[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer = "This is my answer from ret_union";
    l_cmd = 7;
    ::InterReturnT::X_Union x_uni;
    x_uni.x_long(11);
    return x_uni;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_union[_in_str_answer_l_cmd]
  }

  ::InterReturnT::test_enum
  do_my_foo_exec_i::ret_enum (
      const std::string& in_str,
      std::string& answer,
      int32_t& l_cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_enum[_in_str_answer_l_cmd]
    X11_UNUSED_ARG(in_str);
    answer = "This is my answer from ret_enum";
    l_cmd = 8;
    InterReturnT::test_enum test_enum;
    test_enum = InterReturnT::test_enum::TWO;
    return test_enum;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::do_my_foo_exec_i::ret_enum[_in_str_answer_l_cmd]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::InterReturnT::CCM_MyFoo>::ref_type
  Receiver_exec_i::get_do_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  if (!this->do_my_foo_)
  {
    this->do_my_foo_ = CORBA::make_reference <do_my_foo_exec_i> (this->context_);
  }
  return this->do_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<InterReturnT::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl[user_namespace_end_impl]

} // namespace InterReturnT_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Receiver_Impl[factory]
extern "C" void
create_InterReturnT_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterReturnT_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : return_args_t_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
