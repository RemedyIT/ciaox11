/**
 * @file    ami4ccm.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief Implementation file AMI4CCM ExceptionHolder
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ami4ccm.h"
#include "tao/x11/orb_constants.h"
#include "ciaox11/logger/log.h"

CCM_AMI::ExceptionHolder_i::ExceptionHolder_i (
    IDL::traits< ::Messaging::ExceptionHolder>::ref_type holder)
    : holder_ (std::move(holder))
{
}

void
CCM_AMI::ExceptionHolder_i::raise_exception ()
{
  if (holder_)
    {
      holder_->raise_exception ();
    }
  else
    {
      throw ::CORBA::UNKNOWN (CORBA::OMGVMCID, ::CORBA::COMPLETED_YES);
    }
}

IDL::traits<PortableServer::POA>::ref_type
CCM_AMI::get_ami_POA (IDL::traits<Components::SessionContext>::ref_type context)
{
  // Get the orb
  IDL::traits<CORBA::Object>::ref_type objvar =
    context->the_service_registry ()->resolve_service (CIAOX11::SVCID_ORB);

  if (!objvar)
  {
    CIAOX11_LOG_ERROR ("CCM_AMI::get_ami_POA: failed to resolve ORB service reference");
  }

  IDL::traits<CORBA::ORB>::ref_type orb = IDL::traits<CORBA::ORB>::narrow (std::move(objvar));

  if (!orb)
  {
    CIAOX11_LOG_ERROR ("CCM_AMI::get_ami_POA: " << "failed to narrow ORB service reference");
  }

  // Get rootpoa
  objvar = orb->resolve_initial_references ("RootPOA");

  if (!objvar)
  {
    CIAOX11_LOG_ERROR ("CCM_AMI::get_ami_POA: " << "resolve_initial_references failed to retrieve <RootPOA>");
  }

  IDL::traits<PortableServer::POA>::ref_type root_poa = IDL::traits<PortableServer::POA>::narrow (std::move(objvar));

  if (!root_poa)
  {
    CIAOX11_LOG_ERROR ("CCM_AMI::get_ami_POA: " << "failed to narrow <RootPOA>");
  }

  IDL::traits<PortableServer::POAManager>::ref_type poaman = root_poa->the_POAManager ();

  // Creation of the AMIPOA as child of the RootPoa.
  IDL::traits<PortableServer::POA>::ref_type ami_poa;
  try
  {
    CORBA::PolicyList policies;
    ami_poa = root_poa->create_POA(CCM_AMI::AMIPOA_ID, std::move(poaman), policies);
  }
  catch (const PortableServer::POA::AdapterAlreadyExists&)
  {
    // AMIPOA already exists, so find it.
    ami_poa = root_poa->find_POA (CCM_AMI::AMIPOA_ID, true);
    if (!ami_poa)
    {
      CIAOX11_LOG_ERROR ("CCM_AMI::get_ami_POA: unable to find AMIPOA.");
      throw ::CORBA::INTERNAL ();
    }
  }

  return ami_poa;
}
