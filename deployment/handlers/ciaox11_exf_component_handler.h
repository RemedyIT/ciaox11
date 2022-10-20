/**
 * @file   ciaox11_exf_component_handler.h
 * @author Martin Corino
 *
 * @brief Installation handler implementation for Components.
 *        Supports the Execution Framework.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef CIAOX11_EXF_COMPONENT_HANDLER_H
#define CIAOX11_EXF_COMPONENT_HANDLER_H

#pragma once

#include "ciaox11/deployment/handlers/ciaox11_component_handler.h"
#include "exf/deployment/core/ciaox11_schedule.h"

#include <map>
#include <string>

#include "exf/deployment/handlers/ciaox11_exf_connection_handler.h"
#include "exf/deployment/handlers/ciaox11_exf_handler_export.h"

namespace CIAOX11
{
  namespace ExF
  {

    class CIAOX11_EXF_HANDLER_Export Component_Handler
      : public CIAOX11::Component_Handler
    {
    public:
      /// Constructor
      Component_Handler (std::unique_ptr<CIAOX11::Connection_Handler>&& ch)
        : CIAOX11::Component_Handler (std::move (ch)) {}

      /// Destructor
      virtual ~Component_Handler ();

      void install_instance (const ::Deployment::DeploymentPlan & plan,
                             uint32_t instanceRef,
                             CORBA::Any& instance_reference) override;

      void remove_instance (const ::Deployment::DeploymentPlan & plan,
                            uint32_t instanceRef,
                            const ::CORBA::Any & instance_reference) override;

    private:
      void close_scheduling_lane (std::shared_ptr<CIAOX11::Container>,
                                  const std::string&);
    };
  }
}

extern "C"
{
  void
  CIAOX11_EXF_HANDLER_Export create_CIAOX11_EXF_Component_Handler (
      IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type&);
}

#endif /* CIAOX11_EXF_COMPONENT_HANDLER_H */
