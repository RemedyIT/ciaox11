/**
 * @file deployment_interceptors.h
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Deployment interceptors for CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CIAOX11_DEPLOYMENT_INTERCEPTORS_H
#define CIAOX11_DEPLOYMENT_INTERCEPTORS_H

#pragma once

#include "dancex11/core/dancex11_deploymentinterceptors_base_impl.h"
#include "orbsvcs/naming_server/CosNamingC.h"
#include "ciaox11_deployment_interceptors_export.h"

namespace CIAOX11
{
  class CIAOX11_Deployment_Interceptors_Export StoreReferences_i final
    : public DAnCEX11::DeploymentInterceptor_Base
  {
  public:
    /// Constructor
    StoreReferences_i ();

    /// Destructor
    virtual ~StoreReferences_i ();

    virtual void post_install (const ::Deployment::DeploymentPlan & plan,
                          uint32_t index,
                          const ::CORBA::Any & reference,
                          const ::CORBA::Any & exception_thrown) override;

    virtual void post_remove (const Deployment::DeploymentPlan & plan,
                          uint32_t instanceRef,
                          const CORBA::Any & exception_thrown) override;

    virtual void configure(const Deployment::Properties&) override;

  private:
    IDL::traits<CORBA::ORB>::ref_type orb_;
    IDL::traits<CosNaming::NamingContext>::ref_type ctx_;
  };

  class ReferenceLookup_i final
    : public DAnCEX11::DeploymentInterceptor_Base
  {
  public:
    /// Constructor
    ReferenceLookup_i ();

    /// Destructor
    virtual ~ReferenceLookup_i ();

    virtual
      void pre_connect (::Deployment::DeploymentPlan & plan,
                        uint32_t connection_index,
                       CORBA::Any & provided_reference) override;

  private:
    IDL::traits<CORBA::ORB>::ref_type orb_;
  };
}

extern "C"
{
  void
  CIAOX11_Deployment_Interceptors_Export create_CIAOX11_StoreReferences (
    IDL::traits<DAnCEX11::DeploymentInterceptor>::ref_type& interceptor);

  void
  CIAOX11_Deployment_Interceptors_Export create_CIAOX11_ReferenceLookup (
    IDL::traits<DAnCEX11::DeploymentInterceptor>::ref_type& interceptor);
}

#endif /* CIAOX11_DEPLOYMENT_INTERCEPTORS_H */
