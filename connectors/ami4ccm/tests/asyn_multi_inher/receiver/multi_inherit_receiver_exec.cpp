// -*- C++ -*-
/**
 * @file    multi_inherit_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   receiver of ami4ccm test with multiple inheritance
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : multi_inherit_receiver_impl.cpp[Header]

#include "multi_inherit_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl[user_global_impl]

namespace InterMulti_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl[user_namespace_impl]
  uint16_t nr_of_received {};
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_one_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_one_exec_i[ctor]
  do_my_one_exec_i::do_my_one_exec_i (
    IDL::traits<InterMulti::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_one_exec_i[ctor]

  do_my_one_exec_i::~do_my_one_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_one_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_one_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_one_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_one_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_one_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_one_exec_i[user_private_ops]


  /** Operations and attributes from do_my_one */

  int32_t
  do_my_one_exec_i::foo (
      const std::string& in_str,
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_one_exec_i::foo[_in_str_cmd_answer]
    CIAOX11_TEST_INFO << "Receiver: one_foo, in_str =" << in_str
                      << " cmd = " << cmd << std::endl;
    if (cmd != 1)
    {
      CIAOX11_TEST_ERROR << "ERROR: Receiver ONE::foo origin not 1, but "
                         << cmd << std::endl;
    }
    else
    {
      ++nr_of_received;
    }
    answer = "answer foo one";
    return cmd;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_one_exec_i::foo[_in_str_cmd_answer]
  }
  /**
   * Facet Executor Implementation Class : do_my_two_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_two_exec_i[ctor]
  do_my_two_exec_i::do_my_two_exec_i (
    IDL::traits<InterMulti::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_two_exec_i[ctor]

  do_my_two_exec_i::~do_my_two_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_two_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_two_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_two_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_two_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_two_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_two_exec_i[user_private_ops]


  /** Operations and attributes from do_my_two */

  void
  do_my_two_exec_i::bar (
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_two_exec_i::bar[_cmd_answer]
    CIAOX11_TEST_INFO << "Receiver: two_bar, cmd = " << cmd << std::endl;
   if (cmd != 2)
   {
     CIAOX11_TEST_ERROR << "ERROR Receiver: TWO::bar,origin not 2, but "
                        << cmd << std::endl;
   }
   else
   {
     ++nr_of_received;
   }
   answer = "answer bar two";
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_two_exec_i::bar[_cmd_answer]
  }
  /**
   * Facet Executor Implementation Class : do_my_three_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_three_exec_i[ctor]
  do_my_three_exec_i::do_my_three_exec_i (
    IDL::traits<InterMulti::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_three_exec_i[ctor]

  do_my_three_exec_i::~do_my_three_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_three_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_three_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_three_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_three_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_three_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_three_exec_i[user_private_ops]


  /** Operations and attributes from do_my_three */

  void
  do_my_three_exec_i::plus (
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_three_exec_i::plus[_cmd_answer]
    CIAOX11_TEST_INFO << "Receiver: three_plus, cmd = "
                      << cmd << std::endl;
    ++nr_of_received;
    answer = "answer plus three";
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_three_exec_i::plus[_cmd_answer]
  }

  int32_t
  do_my_three_exec_i::foo (
      const std::string& in_str,
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_three_exec_i::foo[_in_str_cmd_answer]
    CIAOX11_TEST_INFO << "Receiver: three_foo, in_str = " << in_str
                      << " cmd = " << cmd << std::endl;
    if (cmd != 3)
    {
      CIAOX11_TEST_ERROR << "ERROR: Receiver THREE::foo, origin not 3, but "
                         << cmd << std::endl;
    }
    else
    {
      ++nr_of_received;
    }
    answer = "answer foo three";
    return 3;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_three_exec_i::foo[_in_str_cmd_answer]
  }

  void
  do_my_three_exec_i::bar (
      int32_t cmd,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::do_my_three_exec_i::bar[_cmd_answer]
    CIAOX11_TEST_INFO << "Receiver: three_bar, cmd = " << cmd << std::endl;
    if (cmd != 3)
    {
      CIAOX11_TEST_ERROR << "ERROR: Receiver Three::bar, origin not 3, but "
                         << cmd << std::endl;
    }
    else
    {
      ++nr_of_received;
    }
    answer = "answer bar three";
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::do_my_three_exec_i::bar[_cmd_answer]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[ccm_remove]
    if (nr_of_received != 7)
    {
      CIAOX11_TEST_ERROR << "ERROR: not received the expected number of"
                         << "correct calls Expected: 7, Received: "
                         <<  nr_of_received << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK: Receiver received the expected "
                        << "number of correct calls. Expected: 7, Received:"
                        << nr_of_received << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::InterMulti::CCM_One >::ref_type
  Receiver_exec_i::get_do_my_one ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[get_do_my_one]
  if (!this->do_my_one_)
  {
    this->do_my_one_ = CORBA::make_reference <do_my_one_exec_i> (this->context_);
  }
  return this->do_my_one_;
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[get_do_my_one]
  }

  IDL::traits< ::InterMulti::CCM_Two >::ref_type
  Receiver_exec_i::get_do_my_two ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[get_do_my_two]
  if (!this->do_my_two_)
  {
    this->do_my_two_ = CORBA::make_reference <do_my_two_exec_i> (this->context_);
  }
  return this->do_my_two_;
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[get_do_my_two]
  }

  IDL::traits< ::InterMulti::CCM_Three >::ref_type
  Receiver_exec_i::get_do_my_three ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[get_do_my_three]
  if (!this->do_my_three_)
  {
    this->do_my_three_ = CORBA::make_reference <do_my_three_exec_i> (this->context_);
  }
  return this->do_my_three_;
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[get_do_my_three]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<InterMulti::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl[user_namespace_end_impl]

} // namespace InterMulti_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Receiver_Impl[factory]
extern "C" void
create_InterMulti_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <InterMulti_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : multi_inherit_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
