/**
 * @file    ciaox11_exf_connection_handler.h
 * @author  Martin Corino
 *
 * @brief ExF connection handling logic for components.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_EXF_CONNECTION_HANDLER_H
#define CIAOX11_EXF_CONNECTION_HANDLER_H

#include "ciaox11/deployment/handlers/ciaox11_connection_handler.h"

namespace CIAOX11
{
  namespace ExF
  {
    class Connection_Handler
      : public CIAOX11::Connection_Handler
    {
    protected:

      virtual
      void connect_local_port (const ::Deployment::DeploymentPlan & plan,
                               const ::Deployment::PlanConnectionDescription &conn,
                               uint32_t endpointRef,
                               const ::Deployment::PlanSubcomponentPortEndpoint &receptacle_endpoint,
                               const CORBA::Any & provided_reference);
    };
  }
}

#endif /* CIAOX11_EXF_CONNECTION_HANDLER_H */
