/**
 * @file    service_registry.cpp
 * @author  Johnny Willemsen
 *
 * @brief Implementation file for CIAOX11 service registry implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11/core/service_registry.h"
#include "ccm/ccm_ccmexceptionC.h"
#include "ciaox11/logger/log.h"

namespace CIAOX11
{
  void
  Service_Registry_i::install_service (
    const std::string& service_id,
    IDL::traits<CORBA::Object>::ref_type objref)
  {
    CIAOX11_LOG_DEBUG ("Service_Registry_i::install_service - Install service <" << service_id << ">");

    bool error {};
    if (service_id.empty ())
      {
        CIAOX11_LOG_ERROR ("Service_Registry_i::install_service - service id is empty");
        error = true;
      }
    if (!objref)
      {
        CIAOX11_LOG_ERROR ("Service_Registry_i::install_service - service object reference is nil");
        error = true;
      }
    if (this->services_.find(service_id) != this->services_.end())
      {
        CIAOX11_LOG_ERROR ("Service_Registry_i::install_service - service with name <" << service_id << "> is already registered");
        error = true;
      }

    if (error)
      {
        throw Components::CCMException (Components::CCMExceptionReason::SERVICE_INSTALLATION_ERROR);
      }

    std::pair<Services::iterator, bool> ret = this->services_.insert ({service_id, objref});
    if (!ret.second)
      {
        CIAOX11_LOG_ERROR ("Service_Registry_i::install_component - Registration of service <" << service_id << "> failed");

        throw Components::CCMException (Components::CCMExceptionReason::SERVICE_INSTALLATION_ERROR);
      }
  }

  IDL::traits<CORBA::Object>::ref_type
  Service_Registry_i::uninstall_service (
    const std::string& service_id)
  {
    CIAOX11_LOG_DEBUG ("Service_Registry_i::uninstall_service - Uninstall service <" << service_id << ">");

    IDL::traits<CORBA::Object>::ref_type obj;
    Services::size_type nr_removed {};
    Services::iterator i = this->services_.find (service_id);
    if (i != this->services_.end ())
      {
        obj = i->second;
        nr_removed = this->services_.erase (service_id);
      }

    if (obj && nr_removed == 1)
      {
        CIAOX11_LOG_DEBUG ("Service_Registry_i::uninstall_service - service <" << service_id << "> uninstalled");
      }
    else
      {
        CIAOX11_LOG_ERROR ("Service_Registry_i::uninstall_service - problem uninstalling service <" << service_id << ">");

        throw Components::CCMException (Components::CCMExceptionReason::SERVICE_INSTALLATION_ERROR);
      }

    return obj;
  }

  IDL::traits<CORBA::Object>::ref_type
  Service_Registry_i::resolve_service (
      const std::string& service_id)
  {
    CIAOX11_LOG_DEBUG ("Service_Registry_i::resolve_service - Resolve service <" << service_id << ">");

    IDL::traits<CORBA::Object>::ref_type service;

    // Search for the asked services
    Services::iterator it = this->services_.find (service_id);
    if (it != this->services_.end ())
      {
        service = it->second;
      }

    if (!service)
      {
        CIAOX11_LOG_INFO ("Service_Registry_i::resolve_service - service <" << service_id << "> not found");

        throw Components::CCMException (Components::CCMExceptionReason::OBJECT_NOT_FOUND);
      }

    return service;
  }
}
