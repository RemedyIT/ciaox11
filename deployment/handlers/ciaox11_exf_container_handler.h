/**
 * @file   ciaox11_exf_container_handler.h
 * @author Martin Corino
 *
 * @brief Installation handler implementation for ExF containers
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef CIAOX11_EXF_CONTAINER_HANDLER_H
#define CIAOX11_EXF_CONTAINER_HANDLER_H

#pragma once

#include "ciaox11/deployment/handlers/ciaox11_container_handler.h"

#include "exf/deployment/handlers/ciaox11_exf_handler_export.h"

namespace CIAOX11
{
  namespace ExF
  {
    class CIAOX11_EXF_HANDLER_Export Container_Handler
      : public CIAOX11::Container_Handler
    {
    public:
      // Constructor
      Container_Handler () = default;

      // Destructor
      virtual ~Container_Handler ();

      void install_instance (const ::Deployment::DeploymentPlan & plan,
                             uint32_t instanceRef,
                             CORBA::Any& instance_reference) override;

      void close () override;
    };
  }
}

extern "C"
{
  void
  CIAOX11_EXF_HANDLER_Export create_CIAOX11_EXF_Container_Handler (
      IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type&);
}

#endif /* CIAOX11_EXF_CONTAINER_HANDLER_H */
