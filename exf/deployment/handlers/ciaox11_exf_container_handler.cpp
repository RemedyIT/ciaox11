/**
 * @file   ciaox11_exf_container_handler.cpp
 * @author Martin Corino
 *
 * @brief Installation handler implementation for ExF containers
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/handlers/ciaox11_exf_container_handler.h"

#include "ciaox11/deployment/handlers/ciaox11_handler_common.h"
#include "ciaox11/logger/log.h"
#include "dancex11/core/dancex11_utility.h"
#include "exf/deployment/core/ciaox11_schedule.h"
#include "exf/deployment/handlers/ciaox11_exf_container.h"

namespace CIAOX11
{
  namespace ExF
  {
    void
    Container_Handler::close ()
    {
      this->CIAOX11::Container_Handler::close ();
    }

    void
    Container_Handler::install_instance (const Deployment::DeploymentPlan &plan,
                                         uint32_t instanceRef,
                                         CORBA::Any& instance_reference)
    {
      const ::Deployment::InstanceDeploymentDescription &idd (plan.instance()[instanceRef]);

      std::string name = plan.instance ()[instanceRef].name ();

      CIAOX11_LOG_DEBUG ("ExF::Container_Handler::install_instance - " <<
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

      // check if we need to instantiate an ExF scheduler/container
      bool create_scheduler = true;
      bool tmp;
      if (DAnCEX11::Utility::get_property_value (ExF::CREATE_EXECUTION_SCHEDULER, props, tmp))
      {
        create_scheduler = tmp;
      }

      std::shared_ptr<CIAOX11::Container> container_ref;
      if (create_scheduler)
      {
        CIAOX11_LOG_DEBUG ("ExF::Container_Handler::install_instance - " <<
                           "creating execution scheduler");

        // copy unique deployment properties
        Components::ConfigValues cfgval;
        Deployment_Common::collect_config_values (props, cfgval);
        ExF::Scheduler::ref_type sched = ExF::Scheduler::create_instance (cfgval);
        if (sched)
        {
          CIAOX11_LOG_DEBUG ("ExF::Container_Handler::install_instance - " <<
                             "creating ExF container " << name);

          try
          {
            container_ref =
              std::make_shared <CIAOX11::ExF::Container> (name, this->orb_, sched);
          }
          catch (const std::bad_alloc&)
          {
            CIAOX11_LOG_ERROR ("ExF::Container_Handler::install_instance - " <<
                               "no memory when creating ExF container");
          }
        }
        else
        {
          CIAOX11_LOG_ERROR ("ExF::Container_Handler::install_instance - " <<
                             "Unable to create scheduler for container <" << name << ">");
          throw ::Deployment::StartError (name, "Unable to create execution scheduler");
        }
      }
      else
      {
        CIAOX11_LOG_DEBUG ("ExF::Container_Handler::install_instance - " <<
                           "creating regular container " << name);

        try
        {
          // create a regular container without scheduler
          container_ref =
            std::make_shared <CIAOX11::Container_i> (name, this->orb_);
        }
        catch (const std::bad_alloc&)
        {
          CIAOX11_LOG_ERROR ("ExF::Container_Handler::install_instance - " <<
                             "no memory when creating regular container");
        }
      }

      if (container_ref)
      {
        // collect unique configuration values for container
        Components::ConfigValues container_config;
        Deployment_Common::collect_config_values (props,
                                                  container_config);

        CIAOX11_LOG_DEBUG ("ExF::Container_Handler::install_instance - " <<
                           "Successfully created container <" << name << ">");

        this->add_container (name, std::move (container_config), container_ref);

        CIAOX11_LOG_DEBUG ("ExF::Container_Handler::install_instance - " <<
                           "Successfully added container to our state <" << name << ">");

        instance_reference <<= name;

        CIAOX11_LOG_DEBUG ("ExF::Container_Handler::install_instance - " <<
                           "Successfully streamed container id into any <" << name << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("ExF::Container_Handler::install_instance - " <<
                           "Error creating container <" << name << ">");
        throw ::Deployment::StartError (name, "Unable to create container");
      }
    }
  }
}

extern "C"
{
  void
  create_CIAOX11_EXF_Container_Handler (
      IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type& handler)
  {
    handler = CORBA::make_reference <CIAOX11::ExF::Container_Handler> ();
  }
}
