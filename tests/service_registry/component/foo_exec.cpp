// -*- C++ -*-
/**
 * @file    foo_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 attribute keywords test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_impl.cpp[Header]

#include "foo_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_global_impl]
// Your declarations here
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
  void Foo_exec_i::test_null_reference ()
  {
    // Installing a service with a null object reference should fail
    try
    {
      this->context_->the_service_registry ()->install_service ("Foo", nullptr);
    }
    catch (const Components::CCMException&ex)
    {
      if (ex.reason() != Components::CCMExceptionReason::SERVICE_INSTALLATION_ERROR)
      {
        CIAOX11_TEST_ERROR << "ERROR: Exception when using null object reference has wrong reason " << ex << std::endl;
      }
      return;
    }
    CIAOX11_TEST_ERROR << "ERROR: Using null object should have failed" << std::endl;
  }

  void Foo_exec_i::test_empty_service_id ()
  {
    // Installing a service with a null object reference should fail
    try
    {
      this->context_ ->the_service_registry ()->install_service ("", this->context_);
    }
    catch (const Components::CCMException&ex)
    {
      if (ex.reason() != Components::CCMExceptionReason::SERVICE_INSTALLATION_ERROR)
      {
        CIAOX11_TEST_ERROR << "ERROR: Exception when using an empty service id reference has wrong reason " << ex << std::endl;
      }
      return;
    }
    CIAOX11_TEST_ERROR << "ERROR: Using empty service id should have failed" << std::endl;
  }

  void Foo_exec_i::test_double_installation ()
  {
    // Installing a service twice should fail
    this->context_ ->the_service_registry ()->install_service ("MyService", this->context_);
    try
    {
      this->context_ ->the_service_registry ()->install_service ("MyService", this->context_);
    }
    catch (const Components::CCMException&ex)
    {
      if (ex.reason() != Components::CCMExceptionReason::SERVICE_INSTALLATION_ERROR)
      {
        CIAOX11_TEST_ERROR << "ERROR: Exception when installing the service twice has wrong reason " << ex << std::endl;
      }
      this->context_ ->the_service_registry ()->uninstall_service ("MyService");
      return;
    }
    CIAOX11_TEST_ERROR << "ERROR: Double installation should have failed" << std::endl;
  }

  void Foo_exec_i::test_invalid_uninstall ()
  {
    // Uninstalling a not registered service should fail
    try
    {
      this->context_ ->the_service_registry ()->uninstall_service ("NoService");
    }
    catch (const Components::CCMException&ex)
    {
      if (ex.reason() != Components::CCMExceptionReason::SERVICE_INSTALLATION_ERROR)
      {
        CIAOX11_TEST_ERROR << "ERROR: Exception when uninstalling unknown service has wrong reason " << ex << std::endl;
      }
      return;
    }
    CIAOX11_TEST_ERROR << "ERROR: Uninstall unknown service should have failed" << std::endl;
  }

  void Foo_exec_i::test_invalid_resolv ()
  {
    // Resolving a not registered service should fail
    try
    {
      this->context_ ->the_service_registry ()->resolve_service ("InvalidService");
    }
    catch (const Components::CCMException&ex)
    {
      if (ex.reason() != Components::CCMExceptionReason::OBJECT_NOT_FOUND)
      {
        CIAOX11_TEST_ERROR << "ERROR: Exception when resolving unknown service has wrong reason " << ex << std::endl;
      }
      return;
    }
    CIAOX11_TEST_ERROR << "ERROR: Resolving unknown service should have failed" << std::endl;
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
    test_null_reference ();
    test_empty_service_id ();
    test_double_installation ();
    test_invalid_uninstall ();
    test_invalid_resolv ();
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
