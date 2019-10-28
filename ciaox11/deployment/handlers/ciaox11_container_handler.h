/**
 * @file    ciaox11_container_handler.h
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Installation handler implementation for containers.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_CONTAINER_HANDLER_H
#define CIAOX11_CONTAINER_HANDLER_H

#pragma once

#include "dancex11/core/dancex11_deploymenthandlersC.h"
#include "dancex11/core/dancex11_utility.h"
#include "ciaox11_deployment_handler_export.h"
#include "tao/x11/portable_server/POAC.h"
#include "ciaox11/deployment/handlers/ciaox11_container_i.h"
#include "ciaox11/deployment/handlers/ciaox11_deployment_handler_export.h"

namespace CIAOX11
{
  class CIAO_Deployment_Handler_Export Container_Handler
    : public IDL::traits<DAnCEX11::InstanceDeploymentHandler>::base_type
  {
  public:
    // Constructor
    Container_Handler () = default;

    // Destructor
    virtual ~Container_Handler () = default;

    virtual
      std::string instance_type () override;

    virtual
      ::CORBA::StringSeq dependencies () override;

    virtual
      void install_instance (const ::Deployment::DeploymentPlan & plan,
                             uint32_t instanceRef,
                             CORBA::Any& instance_reference) override;

    virtual
      void activate_instance (const ::Deployment::DeploymentPlan & ,
                              uint32_t ,
                              const ::CORBA::Any &) override;
    virtual
      void passivate_instance (const ::Deployment::DeploymentPlan & ,
                               uint32_t ,
                               const ::CORBA::Any &) override;

    virtual
      void remove_instance (const ::Deployment::DeploymentPlan & plan,
                            uint32_t instanceRef,
                            const ::CORBA::Any & instance_reference) override;

    virtual
      void provide_endpoint_reference (const ::Deployment::DeploymentPlan & plan,
                                       uint32_t connectionRef,
                                       CORBA::Any& endpoint_reference) override;
    virtual
      void connect_instance (const ::Deployment::DeploymentPlan & plan,
                             uint32_t connectionRef,
                             const ::CORBA::Any & provided_reference) override;

    virtual
      void disconnect_instance (const ::Deployment::DeploymentPlan & plan,
                                uint32_t connectionRef) override;

    virtual
      void instance_configured (const ::Deployment::DeploymentPlan & plan,
                                uint32_t instanceRef) override;

    virtual
      void configure(const Deployment::Properties&) override;

    virtual void close () override;

  protected:

    void
    add_container (
        const std::string& id,
        std::shared_ptr<CIAOX11::Container> container);

    void
    remove_container (
        const std::string &id);

    std::shared_ptr<CIAOX11::Container>
    fetch_container (
        const std::string& id);

    IDL::traits<CORBA::ORB>::ref_type orb_;
    IDL::traits<PortableServer::POA>::ref_type poa_;
  };
}

extern "C"
{
  void
  CIAO_Deployment_Handler_Export create_CIAOX11_Container_Handler (
    IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type& handler);
}

#endif /* CIAOX11_CONTAINER_HANDLER_H */
