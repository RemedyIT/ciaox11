// -*- C++ -*-
/**
 * @file    bar_provider_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : bar_provider_impl.cpp[Header]

#include "bar_provider_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[user_global_impl]

namespace Example_BarProvider_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_bar_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[ctor]
  do_my_bar_exec_i::do_my_bar_exec_i (
    IDL::traits<::Example::CCM_BarProvider_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[ctor]

  do_my_bar_exec_i::~do_my_bar_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i[user_private_ops]


  /** Operations and attributes from do_my_bar */

  void
  do_my_bar_exec_i::do_something_else (
      std::string& an_argument)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::do_my_bar_exec_i::do_something_else[_an_argument]
    CIAOX11_TEST_INFO << "Bar received [" << an_argument << "]" << std::endl;
    an_argument = "Bar says thank you for sending me: "+an_argument;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::do_my_bar_exec_i::do_something_else[_an_argument]
  }

  /**
   * Component Executor Implementation Class : BarProvider_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[ctor]
  BarProvider_exec_i::BarProvider_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[ctor]

  BarProvider_exec_i::~BarProvider_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[user_private_ops]

  /** Session component operations */
  void BarProvider_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[configuration_complete]
  }

  void BarProvider_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[ccm_activate]
  }

  void BarProvider_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[ccm_passivate]
  }

  void BarProvider_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[ccm_remove]
  }

  IDL::traits<::Example::CCM_Bar>::ref_type
  BarProvider_exec_i::get_do_my_bar ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[get_do_my_bar]
    if (!this->do_my_bar_)
    {
      this->do_my_bar_ = CORBA::make_reference <do_my_bar_exec_i> (this->context_);
    }
    return this->do_my_bar_;
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[get_do_my_bar]
  }

  /// Operations from Components::SessionComponent
  void
  BarProvider_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl::BarProvider_exec_i[set_session_context]
    this->context_ = IDL::traits<::Example::CCM_BarProvider_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl::BarProvider_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[user_namespace_end_impl]

} // namespace Example_BarProvider_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BarProvider_Impl[factory]
extern "C" void
create_Example_BarProvider_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Example_BarProvider_Impl::BarProvider_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Example_BarProvider_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : bar_provider_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
