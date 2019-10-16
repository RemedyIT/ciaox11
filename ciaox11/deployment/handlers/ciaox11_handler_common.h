/**
 * @file    ciaox11_handler_common.h
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Operations common to all CIAOX11 handlers
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_HANDLER_COMMON_H
#define CIAOX11_HANDLER_COMMON_H

#include <map>
#include <string>

#include "ccm/ccm_configC.h"
#include "dancex11/deployment/deployment_deploymentplanC.h"
#include "dancex11/core/dancex11_utility.h"
#include "dancex11/core/dancex11_propertiesC.h"
#include "ciaox11/deployment/handlers/ciaox11_state.h"
#include "tao/x11/portable_server/portableserver_functions.h"

#include "ciaox11/deployment/handlers/ciaox11_deployment_handler_export.h"

namespace CIAOX11
{
  /// CIAOX11 specific deployment properties
  const std::string COMPONENT_HOME = "nl.remedy.it.CIAOX11.ComponentHomeId";
  const std::string CONTAINER_ID = "nl.remedy.it.CIAOX11.ContainerId";

  class CIAO_Deployment_Handler_Export Deployment_Common final
  {
  public:
    // Temporary hack until Martin's artifact installation work can
    // be implemented.
    static std::string get_implementation (const std::string& name,
                                           const ::Deployment::MonolithicDeploymentDescription &mdd,
                                           const ::Deployment::DeploymentPlan &plan);

    static void collect_config_values (const DAnCEX11::Utility::PROPERTY_MAP &props,
                                       ::Components::ConfigValues & values);

    static bool find_config_value (const ::Components::ConfigValues & values,
                                   const std::string& name,
                                   CORBA::Any& value);

    static IDL::traits<Components::CCMObject>::ref_type
    get_ccm_object (const std::string& name);

    struct Instance_Info
    {
      std::string name;
      DAnCEX11::Utility::PROPERTY_MAP pmap;
    };

    typedef std::map <std::string, Instance_Info> INSTANCES;

  private:
    // Helper methods for get_ccm_object.
    // Find the given poa in the given rootpoa
    static IDL::traits<PortableServer::POA>::ref_type
    find_poa (IDL::traits<PortableServer::POA>::ref_type root,
      const std::string &name);

    // Try to find the given servant id in the given poa.
    static IDL::traits<CORBA::Object>::ref_type
    find_ccm_object (IDL::traits<PortableServer::POA>::ref_type poa,
      const PortableServer::ObjectId& component_servant_id);
  };
}

#endif
