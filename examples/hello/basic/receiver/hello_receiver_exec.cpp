// -*- C++ -*-
/**
 * @file    hello_receiver_exec.cpp
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_receiver_impl.cpp[Header]

#include "hello_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_includes]
// Your headers here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_global_impl]

namespace Hello_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i[ctor]
  do_my_foo_exec_i::do_my_foo_exec_i (
    IDL::traits<Hello::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i[ctor]

  do_my_foo_exec_i::~do_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from do_my_foo */

  int32_t
  do_my_foo_exec_i::foo (
      const std::string& in_str,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::foo[_in_str_answer]
    if (in_str.empty ())
    {
      throw Hello::InternalError (42, "Hello world");
    }

    answer = "This is my answer: Hi";
    return 0;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::foo[_in_str_answer]
  }

  void
  do_my_foo_exec_i::hello (
      int32_t& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::hello[_answer]
    answer = 5;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::hello[_answer]
  }

  int16_t
  do_my_foo_exec_i::rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::rw_attrib[getter]
    if (this->get_rw_)
    {
      this->get_rw_ = false;
      throw Hello::InternalError  (42, "Hello world");
    }
    else
    {
      this->get_rw_ = true;
    }
    return 0;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::rw_attrib[getter]
  }

  void
  do_my_foo_exec_i::rw_attrib (
      int16_t rw_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::rw_attrib[setter]
    if (rw_attrib == 0)
    {
      throw Hello::InternalError (42, "Hello world");
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::rw_attrib[setter]
  }

  int16_t
  do_my_foo_exec_i::ro_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::ro_attrib[getter]
    if (this->get_ro_)
    {
      this->get_ro_ = false;
      throw Hello::InternalError (42, "Hello world");
    }
    else
    {
      this->get_ro_ = true;
    }
    return 0;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::ro_attrib[getter]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::Hello::CCM_MyFoo>::ref_type
  Receiver_exec_i::get_do_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  if (!this->do_my_foo_)
  {
    this->do_my_foo_ = CORBA::make_reference <do_my_foo_exec_i> (this->context_);
  }
  return this->do_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<Hello::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_namespace_end_impl]

} // namespace Hello_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[factory]
extern "C" void
create_Hello_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
