/**
 * @file    corba4ccm.h
 * @author  Martin Corino
 *
 * @brief Header file CORBA4CCM base
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAO_CORBA4CCM_H
#define CIAO_CORBA4CCM_H

#include /**/ "ace/pre.h"

#include "connectors/corba4ccm/corba4ccm/corba4ccmC.h"
#include "tao/x11/object.h"
#include "tao/x11/portable_server/portableserver.h"
#include "ccm/session/ccm_sessioncontextC.h"

namespace CCM_CORBA
{
  /// Helper method for CORBA4CCM facets to retrieve the CORBA4CCM POA
  CORBA4CCM_STUB_Export
  IDL::traits<PortableServer::POA>::ref_type
  get_corba4ccm_POA (IDL::traits<Components::SessionContext>::ref_type);

  /// Activate a CORBA servant for the component
  CORBA4CCM_STUB_Export
  void
  activate_corba4ccm_component (
    IDL::traits<PortableServer::POA>::ref_type poa,
    const std::string& instance_id);

  /// Deactivate the CORBA servant for the component
  CORBA4CCM_STUB_Export
  void
  deactivate_corba4ccm_component (
    IDL::traits<PortableServer::POA>::ref_type poa,
    const std::string& instance_id);

  /// Activate a CORBA facet servant
  CORBA4CCM_STUB_Export
  void
  activate_corba4ccm_facet (
    IDL::traits<PortableServer::POA>::ref_type poa,
    CORBA::servant_reference<PortableServer::Servant> servant,
    const std::string& instance_id,
    const std::string& facet_name);

  /// Deactivate a CORBA facet servant
  CORBA4CCM_STUB_Export
  void
  deactivate_corba4ccm_facet (
    IDL::traits<PortableServer::POA>::ref_type poa,
    const std::string& instance_id,
    const std::string& facet_name);

  /// Get a CORBA facet servant reference
  CORBA4CCM_STUB_Export
  CORBA::servant_reference<PortableServer::Servant>
  get_corba4ccm_facet (
    IDL::traits<PortableServer::POA>::ref_type poa,
    const std::string& instance_id,
    const std::string& facet_name);
}

#include /**/ "ace/post.h"
#endif /* CIAO_CORBA4CCM_H */
