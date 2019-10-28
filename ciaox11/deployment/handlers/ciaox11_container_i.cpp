/**
 * @file    ciaox11_container_i.cpp
 * @author  Johnny Willemsen, Martin Corino
 *
 * @brief Implementation file for CIAOX11 container implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ccm/ccm_objectC.h"
#include "ccm/session/ccm_sessioncomponentC.h"
#include "ciaox11/logger/log.h"
#include "ciaox11/deployment/handlers/ciaox11_container_i.h"
#include "ciaox11/core/service_registry.h"

namespace CIAOX11
{
  Container::Container (
    std::string name,
    IDL::traits<CORBA::ORB>::ref_type orb)
    : name_ (std::move (name)),
      orb_ (std::move (orb))
  {
    if (!this->orb_)
    {
      // this should never happen
      CIAOX11_LOG_ERROR ("Container::Container - " <<
                         "Missing orb for container <" << this->name_ << ">");
    }

    this->service_registry_ = CORBA::make_reference<CIAOX11::Service_Registry_i> ();

    // Install our ORB into the service registry, this
    // can be used for retrieval of the POA, Reactor, or
    // anything else that is CORBA related
    this->service_registry_->install_service (CIAOX11::SVCID_ORB, this->orb_);
  }

  Container::~Container ()
  {
  }

  void
  Container::fini ()
  {
    if (this->service_registry_)
    {
      // Uninstall the ORB from the service registry
      this->service_registry_->uninstall_service (CIAOX11::SVCID_ORB);
      this->service_registry_ = nullptr;
    }

    this->orb_ = nullptr;
  }

  bool
  Container::install_component (
      const std::string& name,
      IDL::traits<CIAOX11::ExecutorLocator>::ref_type component)
  {

    CIAOX11_LOG_DEBUG ("Container::install_component - " <<
                       "Installing component <" << name << ">");

    if (!component)
    {
      CIAOX11_LOG_ERROR ("Container::install_component - " <<
                         "Invalid executor locator for <" << name << ">");
      return false;
    }

    /// Insert the executor locator into the map
    std::pair<ExecutorLocatorMap::iterator,bool> ret =
      this->executor_locator_map_.insert (ExecutorLocatorMap::value_type(name, component));
    if (!ret.second)
    {
      CIAOX11_LOG_ERROR ("Container::install_component - " <<
                         "Registration of executor locator failed");
      return false;
    }

    CIAOX11_LOG_DEBUG ("Container::install_component - " <<
                       "Installed component <" << name << ">");
    return true;
  }

  IDL::traits<CIAOX11::ExecutorLocator>::ref_type
  Container::get_component (
      const std::string& name)
  {
    CIAOX11_LOG_DEBUG ("Container::get_component - " <<
                       "Get component <" << name << ">");

    ExecutorLocatorMap::iterator i = this->executor_locator_map_.find (name);
    if (i != this->executor_locator_map_.end ())
    {
      CIAOX11_LOG_DEBUG ("Container::get_component - " <<
                         "Found component <" << name << ">");
    }
    else
    {
      CIAOX11_LOG_ERROR ("Container::get_component - " <<
                         "Unable to find component <" << name << ">");
      return {};
    }
    return i->second;
  }

  bool
  Container::uninstall_component (
    const std::string& name)
  {
    CIAOX11_LOG_DEBUG ("Container::uninstall_component - " <<
                       "Uninstall component <" << name << ">");

    ExecutorLocatorMap::iterator i = this->executor_locator_map_.find (name);
    if (i != this->executor_locator_map_.end ())
    {
      // Try to narrow the found ref_type to a session component so that
      // ccm_remove can be invoked.
      IDL::traits<CORBA::Object>::ref_type executor = i->second->obtain_executor ();
      IDL::traits<Components::SessionComponent>::ref_type session_executor =
        IDL::traits<Components::SessionComponent>::narrow (executor);

      if (session_executor)
      {
        session_executor->ccm_remove ();
      }

      // Remove the executor locator from the map
      (void) this->executor_locator_map_.erase (i);

      return true;
    }

    CIAOX11_LOG_ERROR ("Container::get_component - " <<
                       "Unable to find component <" << name << ">");
    return false;
  }

  bool
  Container::activate_component (
    const std::string& name)
  {
    CIAOX11_LOG_DEBUG ("Container::activate_component - " <<
                       "Activate component <" << name << ">");

    IDL::traits<CIAOX11::ExecutorLocator>::ref_type comp = this->get_component (name);
    if (comp)
    {
      IDL::traits<CORBA::Object>::ref_type executor = comp->obtain_executor ();
      IDL::traits<Components::SessionComponent>::ref_type session_executor =
            IDL::traits<Components::SessionComponent>::narrow (executor);

      if (session_executor)
      {
        session_executor->ccm_activate ();
        return true;
      }

      CIAOX11_LOG_ERROR ("Container::activate_component - " <<
                         "Unable to retrieve component executor reference for <" + name + ">");
    }
    return false;
  }

  bool
  Container::passivate_component (const std::string& name)
  {
    CIAOX11_LOG_DEBUG ("Container::passivate_component - " <<
                       "Passivate component <" << name << ">");

    IDL::traits<CIAOX11::ExecutorLocator>::ref_type comp = this->get_component (name);
    if (comp)
    {
      IDL::traits<CORBA::Object>::ref_type executor = comp->obtain_executor ();
      IDL::traits<Components::SessionComponent>::ref_type session_executor =
            IDL::traits<Components::SessionComponent>::narrow (executor);

      if (session_executor)
      {
        session_executor->ccm_passivate ();
        return true;
      }
      else
      {
        CIAOX11_LOG_ERROR ("Container::passivate_component - " <<
                           "Unable to retrieve component executor reference for <" + name + ">");
      }
    }
    return false;
  }

  bool
  Container::configured_component (const std::string& name)
  {
    CIAOX11_LOG_DEBUG ("Container::configured_component - " <<
                       "Configure component <" << name << ">");

    IDL::traits<CIAOX11::ExecutorLocator>::ref_type comp = this->get_component (name);
    if (comp)
    {
      IDL::traits<CORBA::Object>::ref_type executor = comp->obtain_executor ();
      IDL::traits<Components::SessionComponent>::ref_type session_executor =
            IDL::traits<Components::SessionComponent>::narrow (executor);

      if (session_executor)
      {
        session_executor->configuration_complete ();
        return true;
      }
      else
      {
        CIAOX11_LOG_ERROR ("Container::configured_component - " <<
                           "Unable to retrieve component executor reference for <" + name + ">");
      }
    }
    return false;
  }
}
