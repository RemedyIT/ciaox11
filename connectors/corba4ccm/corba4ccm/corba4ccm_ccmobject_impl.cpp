/**
 * @file    corba4ccm_ccmobject_impl.cpp
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "connectors/corba4ccm/corba4ccm/corba4ccm_ccmobject_impl.h"
#include "tao/x11/portable_server/portableserver_functions.h"
#include "ciaox11/logger/log.h"

namespace CCM_CORBA
{
  CCMObject_impl::CCMObject_impl (
    IDL::traits<PortableServer::POA>::ref_type poa,
    std::string component_name) :
      poa_ (std::move(poa)),
      component_name_ (std::move(component_name))
  {
  }

  void
  CCMObject_impl::provide_facet (
    const std::string& facet_name,
    CORBA::Any& facet_ref)
  {
    // Each facet is registered into the POA using an user
    // defined object id. This is build up as:
    // componentname_facetname
    // When we need to give a facet back, we just look for
    // this unique object id in the POA.

    // Create an unique object id consisting out of the
    // unique component id and the facet name
    std::string const object_id = this->component_name_ + "_" + facet_name;

    // Convert the unique stringified object id to a
    // real ObjectId
    PortableServer::ObjectId const servant_oid = PortableServer::string_to_ObjectId (object_id);

    IDL::traits<CORBA::Object>::ref_type retval;

    // Check if there is a reference for the ObjectId, if
    // there is one, we return it
    try
      {
        retval = this->poa_->id_to_reference (servant_oid);

        CIAOX11_LOG_DEBUG ("CCMObject_impl::provide_facet - Found facet <" << this->component_name_ << ":" << facet_name << ">");
      }
    catch (const CORBA::Exception& ex)
      {
        // Couldn't find the ObjectId, so we don't have
        // the needed facet servant in the POA registered
        CIAOX11_LOG_ERROR ("CCMObject_impl::provide_facet - Caught " << ex << " Error while finding facet <" << this->component_name_ << ":" << facet_name << "> : exception <" << ex << ">");
      }

    if (!retval)
    {
      // We haven't found a CORBA facet servant
      throw Components::InvalidName (object_id);
    }

    facet_ref <<= retval;
  }
}

