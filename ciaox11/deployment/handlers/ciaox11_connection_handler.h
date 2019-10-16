/**
 * @file    ciaox11_connection_handler.h
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Common connection handling logic for components.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_CONNECTION_HANDLER_H
#define CIAOX11_CONNECTION_HANDLER_H

#include "dancex11/deployment/deployment_deploymentplanC.h"
#include "ccm/ccm_executorlocatorC.h"
#include "ciaox11_deployment_handler_export.h"

namespace CIAOX11
{
  class CIAO_Deployment_Handler_Export Connection_Handler
  {
  public:
    virtual ~Connection_Handler () = default;

    void
    provide_endpoint_reference (const ::Deployment::DeploymentPlan & plan,
                                uint32_t connectionRef,
                                CORBA::Any& endpoint_reference);

    void connect_instance (const ::Deployment::DeploymentPlan & plan,
                           uint32_t c_id,
                           const ::CORBA::Any & provided_reference);

    void disconnect_instance (const ::Deployment::DeploymentPlan & plan,
                              uint32_t c_id);

  protected:

    virtual
    void connect_local_port (const ::Deployment::DeploymentPlan & plan,
                             const ::Deployment::PlanConnectionDescription &conn,
                             uint32_t endpointRef,
                             const ::Deployment::PlanSubcomponentPortEndpoint &receptacle_endpoint,
                             const ::CORBA::Any & provided_reference);

    void disconnect_local_port (const ::Deployment::DeploymentPlan & plan,
                                const ::Deployment::PlanConnectionDescription &conn,
                                uint32_t endpointRef,
                                const ::Deployment::PlanSubcomponentPortEndpoint &receptacle_endpoint);

    void connect_non_local_receptacle (const ::Deployment::DeploymentPlan & plan,
                                       const ::Deployment::PlanConnectionDescription &conn,
                                       const ::Deployment::PlanSubcomponentPortEndpoint &endpoint,
                                       const ::CORBA::Any & provided_reference);

    void connect_non_local_facet (const ::Deployment::DeploymentPlan & plan,
                                  const ::Deployment::PlanConnectionDescription &conn,
                                  const ::Deployment::PlanSubcomponentPortEndpoint &endpoint,
                                  const ::CORBA::Any & provided_reference);

    void disconnect_non_local (const ::Deployment::DeploymentPlan & plan,
                               const ::Deployment::PlanConnectionDescription &conn,
                               const ::Deployment::PlanSubcomponentPortEndpoint &endpoint,
                               const std::string& port_name);
    bool is_local_connection (const Deployment::DeploymentPlan & plan,
                              const ::Deployment::PlanConnectionDescription &conn);

#if defined (CIAOX11_PRE_ESTABLISH_CONNECTIONS)
    void validate_connection (const std::string& conn,
                              IDL::traits<CORBA::Object>::ref_type obj);
#endif

    uint32_t retrieve_endpoint (const ::Deployment::PlanConnectionDescription &conn);

    static IDL::traits<CIAOX11::ExecutorLocator>::ref_type
    fetch_component (const std::string& id);

    static void
    fetch_component_configuration (
        const std::string& id,
        Components::ConfigValues& config);
  };
}

#endif /* CIAOX11_CONNECTION_HANDLER_H */
