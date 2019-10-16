// -*- C++ -*-
/**
 * @file    corba4ccm_exceptions_component_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Testing the INV_OBJREF exception
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : corba4ccm_exceptions_component_impl.cpp[Header]

#include "corba4ccm_exceptions_component_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[user_global_impl]

namespace Foo_CORBA4CCM_exception_component_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : CORBA4CCM_exception_component_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ctor]
  CORBA4CCM_exception_component_exec_i::CORBA4CCM_exception_component_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ctor]

  CORBA4CCM_exception_component_exec_i::~CORBA4CCM_exception_component_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[user_private_ops]

  /** Session component operations */
  void CORBA4CCM_exception_component_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[configuration_complete]
  }

  void CORBA4CCM_exception_component_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ccm_activate]
    try
    {
      IDL::traits< Hello >::ref_type foo =
        this->context_->get_connection_foo_hello ();
      foo->say_hello ();
      CIAOX11_TEST_ERROR << "ERROR: CORBA4CCM_exception_component_exec_i::ccm_activate - "
        << "No exception caught." << std::endl;
    }
    catch (CORBA::INV_OBJREF const &ex)
    {
      CIAOX11_TEST_DEBUG << "OK: CORBA4CCM_exception_component_exec_i::ccm_activate - "
        << "Expected exception caught: " << ex << std::endl;
    }
    catch (...)
    {
      CIAOX11_TEST_ERROR << "ERROR: CORBA4CCM_exception_component_exec_i::ccm_activate - "
        << "unexpected exception caught." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ccm_activate]
  }

  void CORBA4CCM_exception_component_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ccm_passivate]
  }

  void CORBA4CCM_exception_component_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  CORBA4CCM_exception_component_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Foo::CCM_CORBA4CCM_exception_component_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[user_namespace_end_impl]

} // namespace Foo_CORBA4CCM_exception_component_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_CORBA4CCM_exception_component_Impl[factory]
extern "C" void
create_Foo_CORBA4CCM_exception_component_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Foo_CORBA4CCM_exception_component_Impl::CORBA4CCM_exception_component_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Foo_CORBA4CCM_exception_component_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : corba4ccm_exceptions_component_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
