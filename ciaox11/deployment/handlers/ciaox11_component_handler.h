/**
 * @file    ciaox11_component_handler.h
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Installation handler implementation for Components
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_COMPONENT_HANDLER_H
#define CIAOX11_COMPONENT_HANDLER_H

#pragma once

#include "ciaox11/deployment/handlers/ciaox11_handler_common.h"
#include "dancex11/core/dancex11_deploymenthandlersC.h"
#include "ccm/ccm_executorlocatorC.h"
#include "ciaox11/deployment/handlers/ciaox11_container_i.h"
#include "ciaox11/deployment/handlers/ciaox11_connection_handler.h"
#include "ciaox11_deployment_handler_export.h"

namespace CIAOX11
{
  class CIAOX11_Deployment_Handler_Export Component_Handler
    : public IDL::traits<DAnCEX11::InstanceDeploymentHandler>::base_type
  {
  public:
    /// Constructor
    Component_Handler (std::unique_ptr<Connection_Handler>&& ch)
      : connection_handler_ (std::move (ch)) {}

    /// Destructor
    ~Component_Handler () override = default;

    CORBA::StringSeq dependencies () override;

    std::string instance_type () override;

    void install_instance (const ::Deployment::DeploymentPlan & plan,
                            uint32_t instanceRef,
                            CORBA::Any& instance_reference) override;

    void remove_instance (const ::Deployment::DeploymentPlan & plan,
                          uint32_t instanceRef,
                          const ::CORBA::Any & instance_reference) override;

    void activate_instance (const ::Deployment::DeploymentPlan & ,
                            uint32_t ,
                            const ::CORBA::Any &) override;

    void passivate_instance (const ::Deployment::DeploymentPlan & ,
                              uint32_t ,
                              const ::CORBA::Any &) override;

    void provide_endpoint_reference (const ::Deployment::DeploymentPlan & plan,
                                      uint32_t connectionRef,
                                      CORBA::Any& endpoint_reference) override;

    void connect_instance (const ::Deployment::DeploymentPlan & plan,
                            uint32_t connectionRef,
                            const ::CORBA::Any & provided_reference) override;

    void disconnect_instance (const ::Deployment::DeploymentPlan & plan,
                              uint32_t connectionRef) override;

    void instance_configured (const ::Deployment::DeploymentPlan & plan,
                              uint32_t instanceRef) override;

    void configure(const Deployment::Properties&) override;

    void close () override;

  protected:
    std::unique_ptr<Connection_Handler> connection_handler_;

    void prepare_install (const ::Deployment::DeploymentPlan& plan,
                          const ::Deployment::MonolithicDeploymentDescription &mdd,
                          const Deployment_Common::Instance_Info& info,
                          std::string& exec_art,
                          std::string& exec_entry,
                          std::string& svnt_art,
                          std::string& svnt_entry,
                          uint32_t open_mode,
                          std::string& cont_id);

    IDL::traits<CIAOX11::ExecutorLocator>::ref_type
    create_component (const Deployment_Common::Instance_Info& info,
                      const std::string& exec_art,
                      const std::string& exec_entry,
                      const std::string& svnt_art,
                      const std::string& svnt_entry,
                      uint32_t open_mode,
                      std::shared_ptr<CIAOX11::Container> container);

    std::shared_ptr<CIAOX11::Container>
    fetch_container (const std::string& id);

    void
    register_component (
        const std::string& id,
        Components::ConfigValues&& config,
        const std::string& container_id);

    std::shared_ptr<CIAOX11::Container>
    fetch_component_container (
        const std::string& id);

    void
    unregister_component (
        const std::string& id);
  };
}

extern "C"
{
  void
  CIAOX11_Deployment_Handler_Export create_CIAOX11_Component_Handler (
    IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type& handler);
}

#endif /* CIAOX11_COMPONENT_HANDLER_H */
