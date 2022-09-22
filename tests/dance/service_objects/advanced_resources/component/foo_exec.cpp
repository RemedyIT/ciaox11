// -*- C++ -*-
/**
 * @file    foo_exec.cpp
 * @author  Martin Corino
 *
 * @brief   DAnCEX11 ORB advanced_resources test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_impl.cpp[Header]

#include "foo_exec.h"

#include "ciaox11/testlib/ciaox11_testlog.h"
#include "dancex11/core/dancex11_deployment_state.h"
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_global_impl]
void do_test_orb_advanced_resources (const std::string&);
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_global_impl]

namespace Foo_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Foo_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ctor]
  Foo_exec_i::Foo_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ctor]

  Foo_exec_i::~Foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_private_ops]
  void Foo_exec_i::test_orb_advanced_resources ()
  {
    CIAOX11_TEST_INFO << "Testing for ORB Advanced_Resource_Factory" << std::endl;

    // Installing a service with a null object reference should fail
    try
    {
      IDL::traits<CORBA::ORB>::ref_type orb = DAnCEX11::State::instance ()->orb ();

      if (orb)
      {
        do_test_orb_advanced_resources (orb->id ());
      }
      else
      {
        CIAOX11_TEST_ERROR << "ERROR: Cannot retrieve DnCX11 deployment ORB" << std::endl;
      }
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_ERROR << "ERROR: Exception caught: " << ex << std::endl;
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "ERROR: Unknown exception caught"<< std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_private_ops]

  /** Session component operations */
  void Foo_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[configuration_complete]
  }

  void Foo_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_activate]
    test_orb_advanced_resources ();
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_activate]
  }

  void Foo_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_passivate]
  }

  void Foo_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Foo_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_Foo_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_end_impl]

} // namespace Foo_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[factory]
extern "C" void
create_Foo_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Foo_Impl::Foo_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
