/**
 * @file    ciaox11_container.h
 * @author  Martin Corino
 *
 * @brief   Base class for CIAOX11 container implementation(s).
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_CONTAINER_BASE_H
#define CIAOX11_CONTAINER_BASE_H

#pragma once

#include "ccm/ccm_serviceregistryC.h"
#include "ccm/ccm_executorlocatorC.h"

#include "ciaox11/core/service_registry.h"

#include "ciaox11/core/ciaox11_core_export.h"

namespace CIAOX11
{
  class CIAOX11_CORE_Export Container
  {
  public:
    Container (std::string name);

    virtual ~Container ();

    IDL::traits<CIAOX11::Service_Registry>::ref_type
    the_service_registry () { return this->service_registry_; }

    std::string
    the_name() { return this->name_; }

    /// Install component instance.
    virtual bool
    install_component (
        const std::string& name,
        IDL::traits<CIAOX11::ExecutorLocator>::ref_type component) = 0;

    /// Get component instance.
    virtual IDL::traits<CIAOX11::ExecutorLocator>::ref_type
    get_component (
        const std::string& name) = 0;

    /// Uninstall component instance.
    virtual bool
    uninstall_component (const std::string& name) = 0;

    /// Activate component instance.
    virtual bool
    activate_component (const std::string& name) = 0;

    /// Passivate component instance.
    virtual bool
    passivate_component (const std::string& name) = 0;

    /// Configured component instance.
    virtual bool
    configured_component (const std::string& name) = 0;

  protected:
    /// Name of this container
    std::string name_;

    /// Service registry for this container
    IDL::traits<CIAOX11::Service_Registry>::ref_type service_registry_;

    Container () = delete;
    Container (const Container&) = delete;
    Container (Container&&) = delete;
    Container& operator= (const Container&) = delete;
    Container& operator= (Container&&) = delete;
  };
}

#endif /* CIAOX11_CONTAINER_BASE_H */
