/**
 * @file    ciaox11_container_i.h
 * @author  Johnny Willemsen, Martin Corino
 *
 * @brief   Header file for CIAOX11 container implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_CONTAINER_I_H
#define CIAOX11_CONTAINER_I_H

#pragma once

#include <map>

#include "ciaox11/core/ciaox11_container.h"

#include "ciaox11/deployment/handlers/ciaox11_deployment_handler_export.h"

namespace CIAOX11
{
  class CIAOX11_Deployment_Handler_Export Container_i : public Container
  {
  public:
    Container_i (std::string name,
                 IDL::traits<CORBA::ORB>::ref_type orb);

    virtual ~Container_i ();

    virtual void fini ();

    /// @copydoc CIAOX11::Container::install_component
    bool
    install_component (
        const std::string& name,
        IDL::traits<CIAOX11::ExecutorLocator>::ref_type component) override;

    /// @copydoc CIAOX11::Container::get_component
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type
    get_component (const std::string& name) override;

    /// @copydoc CIAOX11::Container::uninstall_component
    bool uninstall_component (const std::string& name) override;

    /// @copydoc CIAOX11::Container::activate_component
    bool activate_component (const std::string& name) override;

    /// @copydoc CIAOX11::Container::passivate_component
    bool passivate_component (const std::string& name) override;

    /// @copydoc CIAOX11::Container::configured_component
    bool configured_component (const std::string& name) override;

  private:
    /// Reference to the ORB
    IDL::traits<CORBA::ORB>::ref_type orb_;

    /// Map storing for the executor locator for each component
    typedef std::map<std::string, IDL::traits<CIAOX11::ExecutorLocator>::ref_type> ExecutorLocatorMap;
    ExecutorLocatorMap executor_locator_map_;

    Container_i () = delete;
    Container_i (const Container&) = delete;
    Container_i (Container_i&&) = delete;
    Container_i& operator= (const Container_i&) = delete;
    Container_i& operator= (Container_i&&) = delete;
  };
}

#endif /* CIAOX11_CONTAINER_I_H */
