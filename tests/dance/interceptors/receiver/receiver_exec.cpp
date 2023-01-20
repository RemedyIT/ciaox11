// -*- C++ -*-
/**
 * @file    receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component header
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : receiver_impl.cpp[Header]

#include "receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[user_global_impl]
//@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[user_global_impl]

namespace Interceptor_Interceptor_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[user_namespace_impl]
  uint16_t   prov_my_foo_exec_i::_do_foo_count {};
  std::mutex prov_my_foo_exec_i::_lock;
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : prov_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[ctor]
  prov_my_foo_exec_i::prov_my_foo_exec_i (
    IDL::traits<Interceptor::CCM_Interceptor_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[ctor]

  prov_my_foo_exec_i::~prov_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from prov_my_foo */

  uint16_t
  prov_my_foo_exec_i::do_foo (
      uint16_t input,
      uint16_t& output)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i::do_foo[_input_output]
    std::lock_guard<std::mutex> lk(prov_my_foo_exec_i::_lock);
    ++prov_my_foo_exec_i::_do_foo_count;
    output = ++input;
    return output+1;
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::prov_my_foo_exec_i::do_foo[_input_output]
  }

  /**
   * Component Executor Implementation Class : Interceptor_Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ctor]
  Interceptor_Receiver_exec_i::Interceptor_Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ctor]

  Interceptor_Receiver_exec_i::~Interceptor_Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Interceptor_Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[configuration_complete]
  }

  void Interceptor_Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ccm_activate]
  }

  void Interceptor_Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ccm_passivate]
  }

  void Interceptor_Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ccm_remove]
    if (prov_my_foo_exec_i::_do_foo_count != 8)
    {
      CIAOX11_TEST_ERROR << "Interceptor_Receiver_exec_i::ccm_remove - "
        "ERROR: Interceptor did not run. " << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::Interceptor::CCM_Foo>::ref_type
  Interceptor_Receiver_exec_i::get_prov_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[get_prov_my_foo]
  if (!this->prov_my_foo_)
  {
    this->prov_my_foo_ = CORBA::make_reference <prov_my_foo_exec_i> (this->context_);
  }
  return this->prov_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[get_prov_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  Interceptor_Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<Interceptor::CCM_Interceptor_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[user_namespace_end_impl]

} // namespace Interceptor_Interceptor_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Interceptor_Interceptor_Receiver_Impl[factory]
extern "C" void
create_Interceptor_Interceptor_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Interceptor_Interceptor_Receiver_Impl::Interceptor_Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Interceptor_Interceptor_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
