// -*- C++ -*-
/**
 * @file    starter_component_exec.cpp
 * @author  Johnny Willemsen
 *
 * @brief   generated source file sender component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : starter_component_impl.cpp[Header]

#include "starter_component_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_includes]
// Your includes here
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
    IDL::traits< ::Hello::CCM_Receiver_Context>::ref_type context)
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

  std::string
  do_my_foo_exec_i::foo (
      const std::string& in_str,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::foo[_in_str_answer]
    X11_UNUSED_ARG(in_str);
    X11_UNUSED_ARG(answer);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::foo[_in_str_answer]
  }

  int16_t
  do_my_foo_exec_i::foo_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::foo_attrib[getter]
    return this->foo_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::foo_attrib[getter]
  }

  void
  do_my_foo_exec_i::foo_attrib (
      int16_t foo_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::foo_attrib[setter]
    this->foo_attrib_ = foo_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::foo_attrib[setter]
  }

  int16_t
  do_my_foo_exec_i::foo_excep ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::foo_excep[getter]
    return this->foo_excep_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::foo_excep[getter]
  }

  void
  do_my_foo_exec_i::foo_excep (
      int16_t foo_excep)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_foo_exec_i::foo_excep[setter]
    this->foo_excep_ = foo_excep;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_foo_exec_i::foo_excep[setter]
  }
  /**
   * Facet Executor Implementation Class : do_foo_bar_bar_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[ctor]
  do_foo_bar_bar_exec_i::do_foo_bar_bar_exec_i (
    IDL::traits< ::Hello::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[ctor]

  do_foo_bar_bar_exec_i::~do_foo_bar_bar_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i[user_private_ops]


  /** Operations and attributes from do_foo_bar_bar */

  std::string
  do_foo_bar_bar_exec_i::bar (
      const std::string& in_str,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::bar[_in_str_answer]
    X11_UNUSED_ARG(in_str);
    X11_UNUSED_ARG(answer);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::bar[_in_str_answer]
  }

  int16_t
  do_foo_bar_bar_exec_i::bar_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::bar_attrib[getter]
    return this->bar_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::bar_attrib[getter]
  }

  void
  do_foo_bar_bar_exec_i::bar_attrib (
      int16_t bar_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::bar_attrib[setter]
    this->bar_attrib_ = bar_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::bar_attrib[setter]
  }

  int16_t
  do_foo_bar_bar_exec_i::ro_bar_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::ro_bar_attrib[getter]
    return this->ro_bar_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_foo_bar_bar_exec_i::ro_bar_attrib[getter]
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

  IDL::traits< ::Hello::CCM_MyFoo>::ref_type
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

  IDL::traits< ::Hello::CCM_MyBar>::ref_type
  Receiver_exec_i::get_do_foo_bar_bar ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[get_do_foo_bar_bar]
    if (!this->do_foo_bar_bar_)
    {
      this->do_foo_bar_bar_ = CORBA::make_reference <do_foo_bar_bar_exec_i> (this->context_);
    }
    return this->do_foo_bar_bar_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[get_do_foo_bar_bar]
  }


  uint16_t
  Receiver_exec_i::just_an_attribute ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i::just_an_attribute[getter]
    return this->just_an_attribute_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i::just_an_attribute[getter]
  }

  void
  Receiver_exec_i::just_an_attribute (
      uint16_t just_an_attribute)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i::just_an_attribute[setter]
    this->just_an_attribute_ = just_an_attribute;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i::just_an_attribute[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Hello::CCM_Receiver_Context >::narrow (std::move(ctx));
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
//@@{__RIDL_REGEN_MARKER__} - BEGIN : starter_component_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
