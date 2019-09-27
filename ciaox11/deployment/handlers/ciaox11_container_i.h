/**
 * @file    ciaox11_container_i.h
 * @author  Johnny Willemsen, Martin Corino
 *
 * @brief   Header file for CIAOX11 container implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef CIAOX11_CONTAINER_I_H
#define CIAOX11_CONTAINER_I_H

#pragma once

#include <map>

#include "ccm/ccm_serviceregistryC.h"
#include "ccm/ccm_executorlocatorC.h"

#include "ciaox11/deployment/handlers/ciaox11_deployment_handler_export.h"

namespace CIAOX11
{
  class CIAO_Deployment_Handler_Export Container
  {
  public:
    Container (std::string name,
               IDL::traits<CORBA::ORB>::ref_type orb);

    virtual ~Container ();

    virtual void fini ();

    IDL::traits<CIAOX11::Service_Registry>::ref_type
    the_service_registry () { return this->service_registry_; }

    std::string
    the_name() { return this->name_; }

    /// @copydoc CIAOX11::Container::install_component
    bool
    install_component (
        const std::string& name,
        IDL::traits<CIAOX11::ExecutorLocator>::ref_type component);

    /// @copydoc CIAOX11::Container::get_component
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type
    get_component (
        const std::string& name);

    /// @copydoc CIAOX11::Container::uninstall_component
    virtual bool uninstall_component (const std::string& name);

    /// @copydoc CIAOX11::Container::activate_component
    virtual bool activate_component (const std::string& name);

    /// @copydoc CIAOX11::Container::passivate_component
    virtual bool passivate_component (const std::string& name);

    /// @copydoc CIAOX11::Container::configured_component
    virtual bool configured_component (const std::string& name);

  private:
    /// Name of this container
    std::string name_;

    /// Reference to the ORB
    IDL::traits<CORBA::ORB>::ref_type orb_;

    /// Map storing for the executor locator for each component
    typedef std::map<std::string, IDL::traits<CIAOX11::ExecutorLocator>::ref_type> ExecutorLocatorMap;
    ExecutorLocatorMap executor_locator_map_;

    /// Service registry for this container
    IDL::traits<CIAOX11::Service_Registry>::ref_type service_registry_;

    Container () = delete;
    Container (const Container&) = delete;
    Container (Container&&) = delete;
    Container& operator= (const Container&) = delete;
    Container& operator= (Container&&) = delete;
  };
}

#endif /* CIAOX11_CONTAINER_I_H */
