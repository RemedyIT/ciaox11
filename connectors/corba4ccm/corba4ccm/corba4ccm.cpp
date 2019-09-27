/**
 * @file    corba4ccm.cpp
 * @author  Martin Corino
 *
 * @brief Implementation file CORBA4CCM base
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "corba4ccm.h"
#include "tao/x11/orb.h"
#include "ciaox11/logger/log.h"
#include "ccm/ccm_serviceregistryC.h"
#include "tao/x11/portable_server/portableserver_functions.h"
#include "connectors/corba4ccm/corba4ccm/corba4ccm_ccmobject_impl.h"

IDL::traits<PortableServer::POA>::ref_type
CCM_CORBA::get_corba4ccm_POA (IDL::traits<Components::SessionContext>::ref_type context)
{
  // Get the orb
  IDL::traits< CORBA::Object>::ref_type objvar =
    context->the_service_registry()->resolve_service (CIAOX11::SVCID_ORB);
  if (!objvar)
  {
    CIAOX11_LOG_ERROR ("CCM_CORBA::get_corba4ccm_POA: failed to resolve ORB service reference");
  }

  IDL::traits<CORBA::ORB>::ref_type orb =
    IDL::traits<CORBA::ORB>::narrow (std::move(objvar));

  // Get rootpoa
  IDL::traits<CORBA::Object>::ref_type poa_obj =
    orb->resolve_initial_references ("RootPOA");

  if (!poa_obj)
  {
    CIAOX11_LOG_ERROR ("CCM_CORBA::get_corba4ccm_POA: resolve_initial_references (\"RootPOA\") returned null reference.");
  }

  IDL::traits<PortableServer::POA>::ref_type root_poa =
    IDL::traits<PortableServer::POA>::narrow (std::move(poa_obj));

  // Creation of the CORBA4CCMPOA as child of the RootPoa.
  IDL::traits<PortableServer::POA>::ref_type corba_poa;
  try
  {
    // Check if the CORBA4CCM_POA already exists
    corba_poa = root_poa->find_POA (CCM_CORBA::CORBA4CCM_POA_ID, true);
  }
  catch (const PortableServer::POA::AdapterNonExistent&)
  {
    // Ok, POA does not exist yet. We will try to create it.
  }

  if (!corba_poa)
  {
    IDL::traits<PortableServer::POAManager>::ref_type poaman =
      root_poa->the_POAManager ();

    // Create a child POA where we control the assignment of user id
    CORBA::PolicyList policies (1);
    policies[0] =
      root_poa->create_id_assignment_policy (
          PortableServer::IdAssignmentPolicyValue::USER_ID);

    // Creation of the CORBA4CCM_POA as child of the RootPoa.
    try
    {
      corba_poa = root_poa->create_POA(CCM_CORBA::CORBA4CCM_POA_ID, std::move(poaman), policies);
    }
    catch (const CORBA::Exception& ex)
    {
      CIAOX11_LOG_ERROR ("CCM_CORBA::get_corba4ccm_POA:"
                         " unable to create CORBA4CCM_POA [" << ex << "]");
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("CCM_CORBA::get_corba4ccm_POA:"
                         " unable to create CORBA4CCM_POA [exception caught]");
    }
    for (IDL::traits<CORBA::Policy>::ref_type _pol : policies)
    {
      _pol->destroy ();
    }
    if (!corba_poa)
    {
      throw ::CORBA::INTERNAL ();
    }
  }

  return corba_poa;
}

void
CCM_CORBA::deactivate_corba4ccm_component (
  IDL::traits<PortableServer::POA>::ref_type poa,
  const std::string& instance_id)
{
  if (poa)
  {
    // Deactivate the CORBA servant for the component
    PortableServer::ObjectId const component_servant_id =
      PortableServer::string_to_ObjectId (instance_id);
    poa->deactivate_object (component_servant_id);
  }
}

void
CCM_CORBA::activate_corba4ccm_component (
  IDL::traits<PortableServer::POA>::ref_type poa,
  const std::string& instance_id)
{
  if (poa)
  {
    // Create the CORBA component servant, this will handle the
    // request for the retrieval of the facet CORBA servants. These
    // are retrieved from the CORBA4CCM POA.
    // These facet CORBA servants are registered to the CORBA4CCM POA
    // before this servant is registered
    CORBA::servant_reference<PortableServer::Servant> component_servant =
      CORBA::make_reference <CCM_CORBA::CCMObject_impl> (poa, instance_id);

    // Activate the created CORBA component servant in the
    // POA
    PortableServer::ObjectId const component_servant_id =
      PortableServer::string_to_ObjectId (instance_id);

    poa->activate_object_with_id (component_servant_id, std::move(component_servant));
  }
}

void
CCM_CORBA::activate_corba4ccm_facet (
  IDL::traits<PortableServer::POA>::ref_type poa,
  CORBA::servant_reference<PortableServer::Servant> servant,
  const std::string& instance_id,
  const std::string& facet_name)
{
  if (poa)
  {
    // Create an unique object id consisting out of the
    // unique component id and the facet name
    PortableServer::ObjectId const object_id =
      PortableServer::string_to_ObjectId (instance_id + "_" + facet_name);

    // Activate the servant using the object id
    poa->activate_object_with_id (object_id, std::move(servant));
  }
}

void
CCM_CORBA::deactivate_corba4ccm_facet (
  IDL::traits<PortableServer::POA>::ref_type poa,
  const std::string& instance_id,
  const std::string& facet_name)
{
  if (poa)
  {
    // Unregister the CORBA facet servant for facet identified by object_id
    // from the POA. The object id is build out of the
    // unique component id and the facet name
    PortableServer::ObjectId const object_id =
      PortableServer::string_to_ObjectId (instance_id + "_" + facet_name);
    // Deactivate the CORBA facet servant using the user constructed object id
    poa->deactivate_object (object_id);
  }
}

CORBA::servant_reference<PortableServer::Servant>
CCM_CORBA::get_corba4ccm_facet (
  IDL::traits<PortableServer::POA>::ref_type poa,
  const std::string& instance_id,
  const std::string& facet_name)
{
  if (poa)
  {
    // Get the CORBA facet servant for facet identified by object_id
    // from the POA. The object id is build out of the
    // unique component id and the facet name
    PortableServer::ObjectId const object_id =
      PortableServer::string_to_ObjectId (instance_id + "_" + facet_name);
    // Find the CORBA facet servant using the user constructed object id
    return poa->id_to_servant (object_id);
  }
  return {};
}

