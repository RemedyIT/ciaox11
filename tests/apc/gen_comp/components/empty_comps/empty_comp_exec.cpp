// -*- C++ -*-
/**
 * @file    empty_comp_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : empty_comp_impl.cpp[Header]

#include "empty_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[user_global_impl]

namespace EmptyComp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : EmptyComp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[ctor]
  EmptyComp_exec_i::EmptyComp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[ctor]

  EmptyComp_exec_i::~EmptyComp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[user_private_ops]

  /** Session component operations */
  void EmptyComp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[configuration_complete]
  }

  void EmptyComp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "EmptyComp ACTIVATE" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[ccm_activate]
  }

  void EmptyComp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[ccm_passivate]
  }

  void EmptyComp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  EmptyComp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_EmptyComp_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[user_namespace_end_impl]

} // namespace EmptyComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[factory]
extern "C" void
create_EmptyComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <EmptyComp_Impl::EmptyComp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : empty_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
