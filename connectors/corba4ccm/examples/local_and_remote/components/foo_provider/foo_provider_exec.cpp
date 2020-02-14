// -*- C++ -*-
/**
 * @file    foo_provider_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_provider_impl.cpp[Header]

#include "foo_provider_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[user_global_impl]

namespace Example_FooProvider_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[ctor]
  do_my_foo_exec_i::do_my_foo_exec_i (
    IDL::traits< ::Example::CCM_FooProvider_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[ctor]

  do_my_foo_exec_i::~do_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from do_my_foo */

  void
  do_my_foo_exec_i::do_something (
      const std::string& an_argument)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::do_my_foo_exec_i::do_something[_an_argument]
    CIAOX11_TEST_INFO << "Foo received [" << an_argument << "]" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::do_my_foo_exec_i::do_something[_an_argument]
  }

  /**
   * Component Executor Implementation Class : FooProvider_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[ctor]
  FooProvider_exec_i::FooProvider_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[ctor]

  FooProvider_exec_i::~FooProvider_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[user_private_ops]

  /** Session component operations */
  void FooProvider_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[configuration_complete]
  }

  void FooProvider_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[ccm_activate]
  }

  void FooProvider_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[ccm_passivate]
  }

  void FooProvider_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[ccm_remove]
  }

  IDL::traits< ::Example::CCM_Foo>::ref_type
  FooProvider_exec_i::get_do_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[get_do_my_foo]
    if (!this->do_my_foo_)
    {
      this->do_my_foo_ = CORBA::make_reference <do_my_foo_exec_i> (this->context_);
    }
    return this->do_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[get_do_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  FooProvider_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl::FooProvider_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Example::CCM_FooProvider_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl::FooProvider_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[user_namespace_end_impl]

} // namespace Example_FooProvider_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_FooProvider_Impl[factory]
extern "C" void
create_Example_FooProvider_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Example_FooProvider_Impl::FooProvider_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Example_FooProvider_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_provider_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
