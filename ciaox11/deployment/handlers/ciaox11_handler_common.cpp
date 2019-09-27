/**
 * @file    ciaox11_handler_common.cpp
 * @author Johnny Willemsen, Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "ciaox11_handler_common.h"

#include "dancex11/deployment/deployment_planerrorC.h"
#include "dancex11/core/dancex11_deployment_state.h"
#include "dancex11/deployment/deployment_starterrorC.h"
#include "ciaox11/logger/log.h"

namespace CIAOX11
{
  std::string
  Deployment_Common::get_implementation (const std::string& name,
                                         const ::Deployment::MonolithicDeploymentDescription &mdd,
                                         const ::Deployment::DeploymentPlan &plan)
  {
    for (uint32_t artix : mdd.artifactRef ())
    {
      ::Deployment::ArtifactDeploymentDescription const &artifact = plan.artifact ()[artix];
      if (artifact.name () == name)
      {
        if (artifact.location ().size () >= 1 &&
            artifact.location ()[0].size () != 0)
        {
          return artifact.location ()[0];
        }
        else
        {
          CIAOX11_LOG_ERROR ("Deployment_Common::get_implementation - "
            "No validation location for artifact <" << name << ">");
          throw ::Deployment::PlanError (name,
                                         "No valid location field\n");
        }
      }
    }

    CIAOX11_LOG_INFO ("Deployment_Common::get_implementation - "
      "No artifact found for <" << name << ">");

    // return the name itself to use as implementation artifact
    return name;
  }

  void
  Deployment_Common::collect_config_values (const DAnCEX11::Utility::PROPERTY_MAP &props,
                                            ::Components::ConfigValues & values)
  {
    values.resize (props.size ());
    uint32_t n = 0;
    for (DAnCEX11::Utility::PROPERTY_MAP::const_iterator i = props.begin ();
         i != props.end ();
         ++i)
    {
      values[n++] = Components::ConfigValue (i->first, i->second);
    }
  }

  bool Deployment_Common::find_config_value (const ::Components::ConfigValues & values,
                                             const std::string& name,
                                             CORBA::Any& value)
  {
    for (const ::Components::ConfigValue& cfgval : values)
    {
      if (cfgval.name () == name)
      {
        value = cfgval.value ();
        return true;
      }
    }
    return false;
  }

  IDL::traits<Components::CCMObject>::ref_type
  Deployment_Common::get_ccm_object (const std::string& name)
  {
    IDL::traits<CORBA::ORB>::ref_type orb =
      DAnCEX11::State::instance ()->orb ();

    if (!orb)
    {
      CIAOX11_LOG_ERROR ("Deployment_Common::get_ccm_object - "
        << "Unable to retieve ORB.");
      throw Deployment::StartError (name,
        "Deployment_Common::get_ccm_object - Unable to retrieve ORB");
    }
    // Get rootpoa in order to get the correct poa
    IDL::traits<CORBA::Object>::ref_type poa_obj =
      orb->resolve_initial_references ("RootPOA");

    if (!poa_obj)
    {
      CIAOX11_LOG_ERROR ("Deployment_Common::get_ccm_object - "
        << "(\"RootPOA\") returned null reference.");
      throw Deployment::StartError (name,
        "Deployment_Common::get_ccm_object - Unable to retrieve RootPOA");
    }

    IDL::traits<PortableServer::POA>::ref_type root_poa =
      IDL::traits<PortableServer::POA>::narrow (poa_obj);

    IDL::traits<CORBA::Object>::ref_type obj;
    PortableServer::ObjectId component_servant_id =
      PortableServer::string_to_ObjectId (name);

    // First check whether ccm object is available in the CORBA4CCM POA
    IDL::traits<PortableServer::POA>::ref_type corba_poa =
      Deployment_Common::find_poa (root_poa, "CORBA4CCM_POA");
    if (corba_poa)
    {
      obj = Deployment_Common::find_ccm_object (corba_poa, component_servant_id);
    }
    if (!obj)
    {
      // CCM Object not found in the CORBA4CCM POA or the CORBA4CCM POA was not
      // available. It could be registred in the AMI POA. Check this.
      IDL::traits<PortableServer::POA>::ref_type ami_poa =
        Deployment_Common::find_poa (root_poa, "AMIPOA");
      if (ami_poa)
      {
        obj = Deployment_Common::find_ccm_object (ami_poa, component_servant_id);
      }
    }

    return IDL::traits<Components::CCMObject>::narrow (obj);
  }

  IDL::traits<PortableServer::POA>::ref_type
  Deployment_Common::find_poa (IDL::traits<PortableServer::POA>::ref_type root,
    const std::string &name)
  {
    IDL::traits<PortableServer::POA>::ref_type poa {};
    try
    {
      poa = root->find_POA (name, true);
    }
    catch (const PortableServer::POA::AdapterNonExistent&)
    {
    }
    return poa;
  }

  IDL::traits<CORBA::Object>::ref_type
  Deployment_Common::find_ccm_object (IDL::traits<PortableServer::POA>::ref_type poa,
    const PortableServer::ObjectId& component_servant_id)
  {
    IDL::traits<CORBA::Object>::ref_type obj {};
    try
    {
      CORBA::servant_reference<PortableServer::Servant> svnt_ref =
        poa->id_to_servant(component_servant_id);
      obj = poa->servant_to_reference (svnt_ref);
    }
    catch (const PortableServer::POA::ObjectNotActive& )
    {
      CIAOX11_LOG_DEBUG ("Deployment_Common::get_ccm_object - "
        << "CCM Object not active in the <" << poa->the_name ()
        << ">.");
    }
    return obj;
  }
}
