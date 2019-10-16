// -*- C++ -*-
/**
 * @file    attr_only_comp_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : attr_only_comp_impl.cpp[Header]

#include "attr_only_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[user_global_impl]

namespace AttrComp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : AttrComp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[ctor]
  AttrComp_exec_i::AttrComp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[ctor]

  AttrComp_exec_i::~AttrComp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[user_private_ops]

  /** Session component operations */
  void AttrComp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[configuration_complete]
  }

  void AttrComp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "AttrOnlyComp ACTIVATE" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[ccm_activate]
  }

  void AttrComp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[ccm_passivate]
  }

  void AttrComp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[ccm_remove]
  }


  ::Foo::Bar
  AttrComp_exec_i::TestBar ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i::TestBar[getter]
    return this->TestBar_;
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i::TestBar[getter]
  }

  void
  AttrComp_exec_i::TestBar (
      const ::Foo::Bar& TestBar)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i::TestBar[setter]
    this->TestBar_ = TestBar;
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i::TestBar[setter]
  }

  /// Operations from Components::SessionComponent
  void
  AttrComp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[set_session_context]
    this->context_ = IDL::traits< CCM_AttrComp_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[user_namespace_end_impl]

} // namespace AttrComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[factory]
extern "C" void
create_AttrComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <AttrComp_Impl::AttrComp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : attr_only_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
