/**
 * @file    ciaox11_state.h
 * @author Johnny Willemsen, Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_STATE_H
#define CIAOX11_STATE_H

#include <map>
#include <string>
#include <mutex>

#include "ciaox11/core/ciaox11_container.h"

#include "ciaox11/deployment/handlers/ciaox11_deployment_state_export.h"

namespace CIAOX11
{
  /**
   * @class Deployment_State
   * @brief Singleton collecting state for the instance handlers.
   *
   */
  class CIAOX11_Deployment_State_Export Deployment_State final
  {
  public:
    void close ();

    void
    add_container (
        const std::string& id,
        Components::ConfigValues&& config,
        std::shared_ptr<CIAOX11::Container> container);

    void
    remove_container (
        const std::string &id);

    std::shared_ptr<CIAOX11::Container>
    fetch_container (
        const std::string& id);

    void
    fetch_container_configuration (
        const std::string& id,
        Components::ConfigValues& config);

    void
    register_component (
        const std::string& id,
        Components::ConfigValues&& config,
        const std::string& container_id);

    void
    unregister_component (
        const std::string& id);

    std::string
    component_container_id (
        const std::string& id);

    std::shared_ptr<CIAOX11::Container>
    fetch_component_container (
        const std::string& id);

    IDL::traits<CIAOX11::ExecutorLocator>::ref_type
    fetch_component (
        const std::string& id);

    void
    fetch_component_configuration (
        const std::string& id,
        Components::ConfigValues& config);

    static Deployment_State* getInstance ();

  private:
    std::mutex state_mutex_;

    /// Container administration
    using CONTAINERS_PAIR = std::pair <std::string, std::shared_ptr<CIAOX11::Container>>;
    using CONTAINERS = std::map <std::string, std::shared_ptr<CIAOX11::Container>>;

    CONTAINERS containers_;

    /// Administration which components are instantiated in which container
    using INSTANCE_CONTAINER = std::map <std::string, std::string>;

    /// maps instance ids to containers.
    INSTANCE_CONTAINER instance_container_;

    /// Administers configuration of instances
    using INSTANCE_CONFIG = std::map <std::string, Components::ConfigValues>;

    /// maps container ids to configuration.
    INSTANCE_CONFIG container_config_;

    /// maps instance ids to configuration.
    INSTANCE_CONFIG instance_config_;
  };

#define DEPLOYMENT_STATE \
  Deployment_State::getInstance ()

}

#endif
