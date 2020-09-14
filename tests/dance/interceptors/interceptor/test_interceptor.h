/**
 * @file    test_interceptor.h
 * @author  Marcel Smit
 *
 * @brief   Testing interceptors
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef TEST_INTERCEPTORS_H
#define TEST_INTERCEPTORS_H

#include "dancex11/core/dancex11_deploymentinterceptors_base_impl.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "test_interceptor_export.h"
#include "../base/generated_code/interceptorC.h"

#include <vector>

namespace DAnCEX11
{
  class Test_Interceptor_Export Test_Interceptor final
    : public DAnCEX11::DeploymentInterceptor_Base
  {
  public:
    Test_Interceptor ();

    virtual ~Test_Interceptor ();

    void
    configure (const Deployment::Properties &config) override;

    void
    preprocess_plan (Deployment::DeploymentPlan &plan) override;

    void
    pre_install (Deployment::DeploymentPlan &plan,
      uint32_t instanceRef) override;

    void
    post_install (const Deployment::DeploymentPlan &plan,
      uint32_t index,
      const CORBA::Any &reference,
      const CORBA::Any &exception_thrown) override;

    void
    post_endpoint_reference (const Deployment::DeploymentPlan &plan,
      uint32_t connectionRef,
      const CORBA::Any &endpoint_reference,
      const CORBA::Any &exception_thrown) override;

    void
    pre_connect (Deployment::DeploymentPlan &plan,
      uint32_t connection_index,
      CORBA::Any &provided_reference) override;

    void
    post_connect (const Deployment::DeploymentPlan &plan,
      uint32_t connectionRef,
      const CORBA::Any &exceptionThrown) override;

    void
    pre_disconnect (Deployment::DeploymentPlan &plan,
      uint32_t connection_index) override;

    void
    post_disconnect (const Deployment::DeploymentPlan &plan,
      uint32_t connectionRef,
      const CORBA::Any &exceptionThrown) override;

    void
    post_configured (const Deployment::DeploymentPlan &plan,
      uint32_t instanceRef,
      const CORBA::Any &exception_thrown) override;

    void
    post_activate (const Deployment::DeploymentPlan &plan,
      uint32_t instanceRef,
      const CORBA::Any &exception_thrown) override;

    void
    post_passivate (const Deployment::DeploymentPlan &plan,
      uint32_t instanceRef,
      const CORBA::Any &exception_thrown) override;

    void
    post_remove (const Deployment::DeploymentPlan &plan,
      uint32_t instanceRef,
      const CORBA::Any &exception_thrown) override;

    void
    unexpected_event (const Deployment::DeploymentPlan &plan,
      uint32_t instanceRef,
      const CORBA::Any &exception_thrown,
      const std::string&error) override;

  private:
    uint32_t preprocess_plan_ {};
    uint32_t pre_install_invoked_ {};
    uint32_t post_install_invoked_ {};
    uint32_t post_endpoint_reference_invoked_ {};
    uint32_t pre_connect_invoked_ {};
    uint32_t post_connect_invoked_ {};
    uint32_t pre_disconnect_invoked_ {};
    uint32_t post_disconnect_invoked_ {};
    uint32_t post_configured_invoked_ {};
    uint32_t post_activate_invoked_ {};
    uint32_t post_passivate_invoked_ {};
    uint32_t post_remove_invoked_ {};
    uint32_t configure_invoked_ {};
    std::string node_ {};

    typedef std::vector<IDL::traits< ::Interceptor::Foo>::ref_type> FooList;
    FooList foo_list_ {};

    void
    check_instances (const Deployment::DeploymentPlan &plan,
      const std::string &method);

    void
    check_connections (const Deployment::DeploymentPlan &plan,
      const std::string &method);

    void
    check_reference (const CORBA::Any &ref,
      const std::string &method);

    void
    test_references ();
  };
}

extern "C"
{
  void
  Test_Interceptor_Export create_test_interceptor (
    IDL::traits<DAnCEX11::DeploymentInterceptor>::ref_type& interceptor);
}

#endif /* TEST_INTERCEPTORS_H */
