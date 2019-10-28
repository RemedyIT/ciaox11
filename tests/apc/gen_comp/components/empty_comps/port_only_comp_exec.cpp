// -*- C++ -*-
/**
 * @file    port_only_comp_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : port_only_comp_impl.cpp[Header]

#include "port_only_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[user_global_impl]

namespace PortComp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : run_my_bar_foo_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[ctor]
  run_my_bar_foo_prov_exec_i::run_my_bar_foo_prov_exec_i (
    IDL::traits< CCM_PortComp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[ctor]

  run_my_bar_foo_prov_exec_i::~run_my_bar_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]


  /** Operations and attributes from run_my_bar_foo_prov */

  void
  run_my_bar_foo_prov_exec_i::hello (
      int32_t& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i::hello[_answer]
    X11_UNUSED_ARG(answer);
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i::hello[_answer]
  }

  /**
   * Component Executor Implementation Class : PortComp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[ctor]
  PortComp_exec_i::PortComp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[ctor]

  PortComp_exec_i::~PortComp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[user_private_ops]

  /** Session component operations */
  void PortComp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[configuration_complete]
  }

  void PortComp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "PortOnlyComp ACTIVATE" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[ccm_activate]
  }

  void PortComp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[ccm_passivate]
  }

  void PortComp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[ccm_remove]
  }

  IDL::traits< ::Foo::CCM_MyFoo >::ref_type
  PortComp_exec_i::get_run_my_bar_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[get_run_my_bar_foo_prov]
    if (!this->run_my_bar_foo_prov_)
    {
      this->run_my_bar_foo_prov_ = CORBA::make_reference <run_my_bar_foo_prov_exec_i> (this->context_);
    }
    return this->run_my_bar_foo_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[get_run_my_bar_foo_prov]
  }

  /// Operations from Components::SessionComponent
  void
  PortComp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[set_session_context]
    this->context_ = IDL::traits< CCM_PortComp_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[user_namespace_end_impl]

} // namespace PortComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[factory]
extern "C" void
create_PortComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <PortComp_Impl::PortComp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : port_only_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
