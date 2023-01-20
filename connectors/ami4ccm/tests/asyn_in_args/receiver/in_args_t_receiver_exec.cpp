// -*- C++ -*-
/**
 * @file   in_args_t_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   receiver compomnent
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : in_args_t_receiver_impl.cpp[Header]

#include "in_args_t_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl[user_global_impl]

namespace InterInArgsT_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl[user_namespace_impl]
  uint16_t nr_of_received {};
  uint16_t update_val = InterInArgsT::update_val;
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[ctor]
  do_my_foo_exec_i::do_my_foo_exec_i (
    IDL::traits<InterInArgsT::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[ctor]

  do_my_foo_exec_i::~do_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from do_my_foo */

  int32_t
  do_my_foo_exec_i::foo (
      const std::string& in_str,
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::foo[_in_str_cmd_answer]
    if (in_str.empty())
    {
      InterInArgsT::InternalError ex (cmd + update_val,
                                     "foo thrown by receiver");
      throw ex;
    }
    else
    {
      answer = "This is my answer : Hi";
      ++nr_of_received;
      return (cmd + update_val);
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::foo[_in_str_cmd_answer]
  }

  void
  do_my_foo_exec_i::var_ins (
      const std::string& in_str,
      std::string& answer,
      double cmd)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::var_ins[_in_str_answer_cmd]
    X11_UNUSED_ARG (in_str);
    if ( cmd != 1.6)
    {
      CIAOX11_TEST_ERROR << "MyFoo_exec_i::var_ins: "
                         << "received the wrong double, expected 1.6,"
                         << " received " << cmd << std::endl;
    }
    else
    {
      ++nr_of_received;
    }
    answer = "double was " + std::to_string(cmd);
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::var_ins[_in_str_answer_cmd]
  }

  void
  do_my_foo_exec_i::var_div_ins (
      const ::InterInArgsT::TestTopic& test_topic,
      const ::InterInArgsT::TopicString& topic_str,
      const ::InterInArgsT::TestArray& topic_arr,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::var_div_ins[_test_topic_topic_str_topic_arr_answer]
    bool error = false;
    if ((test_topic.key() != "aaa") || (test_topic.x() != 10))
    {
      CIAOX11_TEST_ERROR << "MyFoo_exec_i::var_div_ins: "
                         << "received the wrong struct, "
                         << "expected key 'aaa', x = 10,"
                         << " received key '" << test_topic.key()
                         <<"' , x = " << test_topic.x() << std::endl;
       error = true;
    }
    if ((topic_str.key() != "bbb") ||
        (topic_str.x_str() != "ccc"))
    {
      CIAOX11_TEST_ERROR << "MyFoo_exec_i::var_div_ins: "
                         << "received the wrong struct, "
                         << "expected key 'bbb', x = 'ccc',"
                         << " received key '" <<  topic_str.key()
                         <<"' , x = " << topic_str.x_str()<< std::endl;
       error = true;
     }
     if ((topic_arr[0].key() != "ddd")  ||
         (topic_arr[1].x_array()[2] != 102))
     {
       CIAOX11_TEST_ERROR << "MyFoo_exec_i::var_div_ins: "
                          << "received the wrong struct, "
                          << "expected key 'ddd', elem 102"
                          << " received key '" << topic_arr[0].key()
                          << "', elem " << topic_arr[1].x_array()[2] << std::endl;
        error = true;
     }
     answer = "This is my answer from var_div_ins";
     if(error == false)
     {
       ++nr_of_received;
     }
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::var_div_ins[_test_topic_topic_str_topic_arr_answer]
  }

  void
  do_my_foo_exec_i::var_div2_ins (
      const ::InterInArgsT::X_Union& topic_union,
      const ::InterInArgsT::test_seq& seq,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::var_div2_ins[_topic_union_seq_answer]
    bool error = false;
    if (topic_union.x_long() != 11)
    {
      CIAOX11_TEST_ERROR << "MyFoo_exec_i::var_div2_ins: "
                         << "received the wrong union, "
                         << "expected x = 11,"
                         << " received x = " << topic_union.x_long() << std::endl;
       error = true;
     }
     if ((seq[0].x_teststr() != "fff")||
         ( seq[0].x_test() != 12))
     {
       CIAOX11_TEST_ERROR << "MyFoo_exec_i::var_div2_ins: "
                          << "received the wrong struct, "
                          << "expected key 'fff', x = 10,"
                          << " received key '" << seq[0].x_teststr()
                          << "' , x = " << seq[0].x_test() << std::endl;
       error = true;
     }
     answer = "This is my answer from var_div2_ins";
     if(error == false)
     {
       ++nr_of_received;
     }
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::var_div2_ins[_topic_union_seq_answer]
  }

  void
  do_my_foo_exec_i::enum_in (
      std::string& answer,
      ::InterInArgsT::test_enum in_test)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::enum_in[_answer_in_test]
    if ( in_test != InterInArgsT::test_enum::ONE)
    {
      CIAOX11_TEST_ERROR << "MyFoo_exec_i::enum_in: "
                         << "received the wrong enum value, expected ONE,"
                         << " received " <<  (int) in_test << std::endl;
    }
    else
    {
       ++nr_of_received;
    }
    answer = "This is my answer from enum_in";
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::do_my_foo_exec_i::enum_in[_answer_in_test]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[ccm_remove]
    if (nr_of_received == 6)
    {
      CIAOX11_TEST_DEBUG << "OK: Receiver received all expected data"
                         << " from syn- and asynchronous calls" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR: Receiver didn't receive all"
                         << " expected data  (" << nr_of_received << " of 6)"
                         << " from syn- and asynchronous calls"
                         << std::endl;
    }

    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::InterInArgsT::CCM_MyFoo>::ref_type
  Receiver_exec_i::get_do_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  if (!this->do_my_foo_)
  {
    this->do_my_foo_ = CORBA::make_reference <do_my_foo_exec_i> (this->context_);
  }
  return this->do_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<InterInArgsT::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl[user_namespace_end_impl]

} // namespace InterInArgsT_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInArgsT_Receiver_Impl[factory]
extern "C" void
create_InterInArgsT_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterInArgsT_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterInArgsT_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : in_args_t_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
