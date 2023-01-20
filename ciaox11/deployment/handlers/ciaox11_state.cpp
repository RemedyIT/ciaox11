/**
 * @file    ciaox11_state.cpp
 * @author Johnny Willemsen, Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11_state.h"
#include "ciaox11/logger/log.h"

namespace CIAOX11
{
  Deployment_State* Deployment_State::getInstance ()
  {
    static Deployment_State instance_;

    return std::addressof(instance_);
  }

  void
  Deployment_State::close ()
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    this->containers_.clear ();
    this->instance_container_.clear ();
  }

  void
  Deployment_State::add_container (
      const std::string& id,
      Components::ConfigValues&& config,
      std::shared_ptr<CIAOX11::Container> container)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    if (this->containers_.find (id) != this->containers_.end ())
    {
      CIAOX11_LOG_ERROR ("Deployment_State::add_container - " <<
                         "attempting to add duplicate container reference");
    }

    this->containers_.insert (CONTAINERS_PAIR (id, container));

    this->container_config_.insert (CONFIG_PAIR (id, std::move (config)));
  }

  void
  Deployment_State::remove_container (const std::string& id)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    this->containers_.erase (id);

    this->container_config_.erase (id);
  }

  std::shared_ptr<CIAOX11::Container>
  Deployment_State::fetch_container (const std::string& id)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    CONTAINERS::iterator pos = this->containers_.find (id);

    if (pos == this->containers_.end ())
    {
      return nullptr;
    }

    return pos->second;
  }

  void
  Deployment_State::fetch_container_configuration (
      const std::string& id,
      Components::ConfigValues& config)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    INSTANCE_CONFIG::iterator cfgit =
      this->container_config_.find (id);

    if (cfgit != this->container_config_.end ())
    {
      config = cfgit->second;
    }
  }

  void
  Deployment_State::register_component (
      const std::string& id,
      Components::ConfigValues&& config,
      const std::string& cont_id)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    this->instance_container_.insert (INSTANCE_PAIR (id, cont_id));

    this->instance_config_.insert (CONFIG_PAIR (id, std::move (config)));
  }

  void
  Deployment_State::unregister_component (const std::string& id)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    this->instance_container_.erase (id);

    this->instance_config_.erase (id);
  }

  void
  Deployment_State::fetch_component_configuration (
      const std::string& id,
      Components::ConfigValues& config)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    INSTANCE_CONFIG::iterator cfgit = this->instance_config_.find (id);

    if (cfgit != this->instance_config_.end ())
    {
      config = cfgit->second;
    }
  }

  std::shared_ptr<CIAOX11::Container>
  Deployment_State::fetch_component_container (const std::string& id)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    INSTANCE_CONTAINER::const_iterator cont =
      this->instance_container_.find (id);

    if (cont == this->instance_container_.end ())
    {
      CIAOX11_LOG_DEBUG ("Deployment_State::fetch_component_container - " <<
                         "Unknown component instance <"
                         << id << ">");

      return {};
    }

    CONTAINERS::iterator pos = this->containers_.find (cont->second);

    if (pos == this->containers_.end ())
    {
      // This should never happen
      CIAOX11_LOG_ERROR ("Deployment_State::fetch_component_container - " <<
                         "Warning: Unknown component container <"
                         << cont->second << ">");
      return {};
    }

    return pos->second;
  }

  IDL::traits<CIAOX11::ExecutorLocator>::ref_type
  Deployment_State::fetch_component (const std::string& id)
  {
    std::shared_ptr<CIAOX11::Container> container =
        this->fetch_component_container (id);

    if (container)
    {
      return container->get_component (id);
    }

    return {};
  }

  std::string
  Deployment_State::component_container_id (const std::string& id)
  {
    std::lock_guard<std::mutex> lock (this->state_mutex_);

    INSTANCE_CONTAINER::const_iterator cont =
      this->instance_container_.find (id);

    if (cont != this->instance_container_.end ())
    {
      return cont->second;
    }

    CIAOX11_LOG_DEBUG ("Deployment_State::component_container_id - "
                       "Unknown component instance <"
                       << id << ">");
    return {};
  }
}
