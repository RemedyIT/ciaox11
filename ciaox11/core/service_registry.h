/**
 * @file    service_registry.h
 * @author  Johnny Willemsen
 *
 * @brief Header file for CIAOX11 service registry implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_SERVICE_REGISTRY_H
#define CIAOX11_SERVICE_REGISTRY_H

#pragma once

#include "ccm/ccm_serviceregistryC.h"
#include "ciaox11/core/ciaox11_core_export.h"

#include <map>

namespace CIAOX11
{
  /// Service registry administration. Each service is registered
  /// with a unique name
  class CIAOX11_CORE_Export Service_Registry_i final :
    public IDL::traits <CIAOX11::Service_Registry>::base_type
  {
  public:
    Service_Registry_i () = default;
    ~Service_Registry_i () override = default;

    /// @copydoc CIAOX11::Service_Registry::install_service
    void
    install_service (
      const std::string& service_id,
      IDL::traits<CORBA::Object>::ref_type objref) override;

    /// @copydoc CIAOX11::Service_Registry::uninstall_service
    IDL::traits<CORBA::Object>::ref_type
    uninstall_service (const std::string& service_id) override;

    /// @copydoc CIAOX11::Service_Registry::resolve_service
    IDL::traits<CORBA::Object>::ref_type
    resolve_service (const std::string& service_id) override;

  private:
    /// Administration of installed service
    using Services = std::map<std::string, IDL::traits<CORBA::Object>::ref_type>;
    Services services_;

    Service_Registry_i (const Service_Registry_i&) = delete;
    Service_Registry_i (Service_Registry_i&&) = delete;
    Service_Registry_i& operator= (const Service_Registry_i&) = delete;
    Service_Registry_i& operator= (Service_Registry_i&&) = delete;
  };
}

#endif /* CIAOX11_SERVICE_REGISTRY_H */
