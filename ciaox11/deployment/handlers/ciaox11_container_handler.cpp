/**
 * @file    ciaox11_container_handler.cpp
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Installation handler implementation for containers
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11_container_handler.h"
#include "ciaox11/logger/log.h"
#include "ciaox11/deployment/handlers/ciaox11_state.h"
#include "ciaox11/deployment/handlers/ciaox11_handler_common.h"
#include "dancex11/core/dancex11_deployment_state.h"
#include "dancex11/core/dancex11_utility.h"

namespace CIAOX11
{
  void
  Container_Handler::add_container (
      const std::string& id,
      std::shared_ptr<CIAOX11::Container> container)
  {
    DEPLOYMENT_STATE->add_container (id, container);
  }

  void
  Container_Handler::remove_container (
      const std::string &id)
  {
    DEPLOYMENT_STATE->remove_container (id);
  }

  std::shared_ptr<CIAOX11::Container>
  Container_Handler::fetch_container (
      const std::string& id)
  {
    return DEPLOYMENT_STATE->fetch_container (id);
  }

  void
  Container_Handler::close ()
  {
    try
    {
      // For the time being, we are going to go ahead and remove
      // the default container
      Deployment::DeploymentPlan plan;
      Deployment::InstanceDeploymentDescription idd;
      plan.instance ().push_back (idd);

      CORBA::Any any;
      this->remove_instance (plan, 0, any);
    }
    catch (...)
    { //swallow
    }

    DEPLOYMENT_STATE->close ();

    this->orb_ = nullptr;
  }

  CORBA::StringSeq
  Container_Handler::dependencies ()
  {
    CORBA::StringSeq retval;
    return retval;
  }

  std::string
  Container_Handler::instance_type ()
  {
    return DAnCEX11::CCM_CONTAINER;
  }

  void
  Container_Handler::install_instance (const Deployment::DeploymentPlan &plan,
                                         uint32_t instanceRef,
                                         CORBA::Any& instance_reference)
  {
    const ::Deployment::InstanceDeploymentDescription &idd (plan.instance()[instanceRef]);

    std::string name = plan.instance ()[instanceRef].name ();

    CIAOX11_LOG_DEBUG ("Container_Handler::install_instance - " <<
                       "Starting installation for <" << name << ">");

    // create unique set of deployment properties of instance
    DAnCEX11::Utility::PROPERTY_MAP props;
    if (idd.implementationRef() < plan.implementation ().size ())
    {
      const ::Deployment::MonolithicDeploymentDescription &mdd (plan.implementation()[idd.implementationRef()]);
      DAnCEX11::Utility::build_property_map (props, mdd.execParameter ());
    }
    DAnCEX11::Utility::build_property_map (props, idd.configProperty ());

    // check for explicitly declared container id
    std::string container_id;
    if (DAnCEX11::Utility::get_property_value (CIAOX11::CONTAINER_ID, props, container_id))
    {
      name = container_id;
    }

    try
    {
      std::shared_ptr<CIAOX11::Container> container_ref =
        std::make_shared <CIAOX11::Container> (name, this->orb_);

      CIAOX11_LOG_DEBUG ("Container_Handler::install_instance - " <<
                        "Successfully created container <" << name << ">");

      this->add_container (name, container_ref);

      CIAOX11_LOG_DEBUG ("Container_Handler::install_instance - " <<
                        "Successfully added container to our state <" << name << ">");

      instance_reference <<= name;

      CIAOX11_LOG_DEBUG ("Container_Handler::install_instance - " <<
                        "Successfully streamed container id into any <" << name << ">");
    }
    catch (const std::bad_alloc&)
    {
      CIAOX11_LOG_ERROR ("Container_Handler::install_instance - " <<
                        "Error creating container <" << name << ">");
      throw ::Deployment::StartError (name, "Unable to create container\n");
    }
  }

  void
  Container_Handler::activate_instance (const ::Deployment::DeploymentPlan & ,
                                     uint32_t ,
                                     const ::CORBA::Any &)
  {
    // no activation needed.
  }

  void
  Container_Handler::passivate_instance (const ::Deployment::DeploymentPlan & ,
                                      uint32_t ,
                                      const ::CORBA::Any &)
  {
    // no passivation needed.
  }

  void
  Container_Handler::provide_endpoint_reference (const ::Deployment::DeploymentPlan &,
                                                   uint32_t,
                                                   CORBA::Any&)
  {
    CIAOX11_LOG_ERROR ("Container_Handler::provide_endpoint_reference - " <<
                       "Unable to provide any endpoints for a container");
    throw CORBA::NO_IMPLEMENT ();
  }

  void
  Container_Handler::remove_instance (
    const ::Deployment::DeploymentPlan & plan,
    uint32_t instanceRef,
    const ::CORBA::Any &)
  {
    std::string const name = plan.instance ()[instanceRef].name ();

    CIAOX11_LOG_DEBUG ("Container_Handler::remove_instance - " <<
                       "Starting remove for <" << name << ">");

    std::shared_ptr<CIAOX11::Container> cont =
        this->fetch_container (name);

    if (!cont)
    {
      CIAOX11_LOG_ERROR ("Container_Handler::remove_instance - " <<
                         "Found no container with id <" << name << ">");
      throw ::Deployment::StopError (name,
                                     "No container with ID");
    }

    CIAOX11_LOG_DEBUG ("Container_Handler::remove_instance - " <<
                       "Finalizing <" << name << ">");

    // Instructing container to cleanup its state
    cont->fini ();

    CIAOX11_LOG_DEBUG ("Container_Handler::remove_instance - " <<
                       "Removing container from our state <" << name << ">");

    this->remove_container (name);

    CIAOX11_LOG_DEBUG ("Container_Handler::remove_instance - " <<
                       "Removed <" << name << ">");
  }

  void
  Container_Handler::connect_instance (const ::Deployment::DeploymentPlan &,
                                         uint32_t,
                                         const ::CORBA::Any &)
  {
    CIAOX11_LOG_ERROR ("Container_Handler::disconnect_instance - " <<
                       "Unable to connect for a container");
    throw CORBA::NO_IMPLEMENT ();
  }


  void
  Container_Handler::disconnect_instance (const ::Deployment::DeploymentPlan &,
                                            uint32_t)
  {
    CIAOX11_LOG_ERROR ("Container_Handler::disconnect_instance - " <<
                       "Unable to disconnect for a container");
    throw CORBA::NO_IMPLEMENT ();
  }

  void
  Container_Handler::instance_configured (const ::Deployment::DeploymentPlan &,
                                            uint32_t)
  {
    // nothing to be done
  }

  void
  Container_Handler::configure (const ::Deployment::Properties &props)
  {
    CIAOX11_LOG_DEBUG ("Container_Handler::configure - " <<
                       "Configuring with <" << props.size () << "> properties");

    this->orb_ = DAnCEX11::State::instance ()->orb ();

    if (!this->orb_)
    {
      CIAOX11_LOG_ERROR ("Container_Handler::configure - Unable to locate ORB");
      throw ::Deployment::StartError ("CIAO Container Handler ",
                                      "Unable to locate ORB");
    }

    // For the time being, we are going to go ahead and construct a container.
    Deployment::DeploymentPlan plan;
    Deployment::InstanceDeploymentDescription idd;
    idd.configProperty (props); // copy install properties as default container instance properties
    plan.instance ().push_back (idd);

    ::CORBA::Any any;
    this->install_instance (plan, 0, any);
  }
}

extern "C"
{
  void
  create_CIAOX11_Container_Handler (
    IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type& handler)
  {
    handler = CORBA::make_reference <CIAOX11::Container_Handler> ();
  }
}
