/**
 * @file   ciaox11_exf_component_handler.cpp
 * @author Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "exf/deployment/handlers/ciaox11_exf_component_handler.h"

#include "ciaox11/logger/log.h"
#include "dancex11/deployment/deployment_deploymentplanC.h"
#include "dancex11/core/dancex11_dynamic_loader.h"
#include "exf/deployment/handlers/ciaox11_exf_container.h"

namespace CIAOX11
{
  namespace ExF
  {
    Component_Handler::~Component_Handler ()
    {
    }

    void
    Component_Handler::install_instance (const Deployment::DeploymentPlan &plan,
                                           uint32_t instanceRef,
                                           CORBA::Any& instance_reference)
    {
      const ::Deployment::InstanceDeploymentDescription &idd (plan.instance()[instanceRef]);
      const ::Deployment::MonolithicDeploymentDescription &mdd (plan.implementation()[idd.implementationRef()]);

      Deployment_Common::Instance_Info info;
      info.name = idd.name ();

      CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                         "Starting installation for <" << idd.name () << ">");

      DAnCEX11::Utility::build_property_map (info.pmap,
                                          mdd.execParameter ());
      DAnCEX11::Utility::build_property_map (info.pmap,
                                          idd.configProperty ());

      std::string exec_art, exec_entry, svnt_art, svnt_entry, cont_id, tmp, error_string;

      uint32_t open_mode = ACE_DEFAULT_SHLIB_MODE;

      this->prepare_install (plan, mdd, info, exec_art, exec_entry, svnt_art, svnt_entry, open_mode, cont_id);

      std::shared_ptr<CIAOX11::Container> container =
          this->fetch_container (cont_id);

      if (!container)
      {
        CIAOX11_LOG_ERROR ("ExF::Component_Handler::install_instance - " <<
                           "Container not found <" << info.name << ">:<" << cont_id << ">");
        throw ::Deployment::PlanError (info.name, "Invalid container\n");
      }

      IDL::traits<CIAOX11::ExecutorLocator>::ref_type executor_locator =
          this->create_component (info, exec_art, exec_entry, svnt_art, svnt_entry, open_mode, container);

      CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                         "executor locator created for <" << idd.name () << ">");

      IDL::traits<Components::CCMObject>::ref_type comp_ref;
      try
      {
        // collect unique configuration values for component
        Components::ConfigValues exec_config;
        Deployment_Common::collect_config_values (info.pmap,
                                                  exec_config);

        CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                           "configuring executor locator for <" << idd.name () << ">");

        // configure component (and optionally collect additional/updated values)
        executor_locator->configure (exec_config);

        CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                           "checking container type");

        // do we deploy into an ExF container or a regular container
        std::shared_ptr<ExF::Container> exf_container =
            std::dynamic_pointer_cast<ExF::Container> (container);
        if (exf_container)
        {
          CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                             "checking property " << ExF::NO_SCHEDULING_LANE);

          // check if component needs an execution SchedulingLane opened
          CORBA::Any val;
          bool no_lane_flag {}; // default false
          if (Deployment_Common::find_config_value (exec_config, ExF::NO_SCHEDULING_LANE, val))
          {
            if (!(val >>= no_lane_flag))
            {
              CIAOX11_LOG_ERROR ("ExF::Component_Handler::install_instance - " \
                                 "Cannot extract value of config value <"
                                 << ExF::NO_SCHEDULING_LANE << "> for <"
                                 << info.name << ">");
              throw ::Deployment::StartError (idd.name (),
                                              "Failed to detect scheduler setting.");
            }
          }

          if (!no_lane_flag)
          {
            CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                               "opening scheduling lane");

            // get the scheduler allocated to the container
            ExF::Scheduler::ref_type sched =
                exf_container->the_scheduler ();
            if (!sched)
            {
              CIAOX11_LOG_ERROR ("ExF::Component_Handler::install_instance - " \
                                 "Failed to allocate ExF::Scheduler for container <"
                                  << cont_id << "> for <"
                                  << info.name << ">");
              throw ::Deployment::StartError (idd.name (),
                                              "Failed to allocate ExF::Scheduler.");
            }

            // open a scheduling lane for the component instance
            IDL::traits<ExF::SchedulingLane>::ref_type lane {};
            if (ExF::SchedulerResult::SOK != sched->open_scheduling_lane (idd.name (), exec_config, lane))
            {
              CIAOX11_LOG_ERROR ("ExF::Component_Handler::install_instance - " \
                                 "Failed to open SchedulingLane for <"
                                  << info.name << ">");
              throw ::Deployment::StartError (idd.name (),
                                              "Failed to open SchedulingLane.");
            }

            CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                               "opened scheduling lane for " << idd.name ());

            // add the lane to the instances configuration values
            CORBA::Any lane_ref;
            lane_ref <<= lane;

            CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                               "inserted scheduling lane reference in Any");

            exec_config.push_back (
                Components::ConfigValue (ExF::SCHEDULING_LANE_REF, lane_ref));

            CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                               "stored scheduling lane reference");
          }
        }

        // install component in container
        if (!container->install_component (idd.name (), executor_locator))
        {
          throw ::Deployment::StartError (idd.name (),
                                          "Failed to install component");
        }

        // register the component and it's configuration values
        this->register_component (
            idd.name (),
            std::move (exec_config),
            cont_id);

        CIAOX11_LOG_DEBUG ("ExF::Component_Handler::install_instance - " <<
                           "installed component <" << idd.name () << ">:<" << cont_id << ">");

      }
      catch (const ::Deployment::StartError &)
      {
        throw;
      }
      catch (const ::CORBA::Exception &ex)
      {
        CIAOX11_LOG_ERROR ("ExF::Component_Handler::install_instance - " <<
                           "Caught CORBA exception <" << idd.name () << ">:<" << ex << ">");
        throw ::Deployment::StartError (idd.name (),
                                        ex.what ());
      }
      catch (const std::exception &ex)
      {
        CIAOX11_LOG_ERROR ("ExF::Component_Handler::install_instance - " <<
                           "Caught C++ std::exception <" << idd.name () << ">:<" <<
                           ex.what () << ">");
        throw ::Deployment::StartError (idd.name (),
                                        ex.what ());
      }
      catch (...)
      {
        CIAOX11_LOG_ERROR ("ExF::Component_Handler::install_instance - " <<
                           "Caught unknown C++ exception <" << idd.name () << ">");
        throw ::Deployment::StartError (idd.name (),
                                        "Unknown C++ exception\n");
      }

      comp_ref = Deployment_Common::get_ccm_object (info.name);
      instance_reference <<= comp_ref;
    }


    void
    Component_Handler::remove_instance (const Deployment::DeploymentPlan & plan,
                                          uint32_t instanceRef,
                                          const CORBA::Any &)
    {
      std::string const name = plan.instance ()[instanceRef].name ();

      CIAOX11_LOG_DEBUG ("ExF::Component_Handler::remove_instance - " <<
                         "Starting remove for <" << name << ">");

      std::shared_ptr<CIAOX11::Container> cont =
        this->fetch_component_container (name);

      if (!cont)
      {
        CIAOX11_LOG_ERROR ("ExF::Component_Handler::remove_instance - " <<
                           "Container not found for <" << name << ">");
        throw ::Deployment::StopError (name,
                                       "Unable to remove due to nil container reference");
      }

      try
      {
        try
        {
          if (!cont->uninstall_component (name))
          {
            throw ::Deployment::StopError (name,
                                           "Failed to uninstall component");
          }
        }
        catch (const ::Deployment::StopError &)
        {
          throw;
        }
        catch (const CORBA::Exception &ex)
        {
          CIAOX11_LOG_ERROR ("ExF::Component_Handler::remove_instance - " <<
                             "Caught CORBA exception <" << name << ">:<" << ex << ">");
          throw ::Deployment::StopError (name, ex.what ());
        }
        catch (const std::exception &ex)
        {
          CIAOX11_LOG_ERROR ("ExF::Component_Handler::remove_instance - " <<
                             "Caught C++ std::exception <" << name << ">:<" <<
                             ex.what () << ">");
          throw ::Deployment::StopError (name,
                                          ex.what ());
        }
        catch (...)
        {
          CIAOX11_LOG_ERROR ("ExF::Component_Handler::remove_instance - " <<
                             "Caught unknown C++ exception <" << name << ">");
          throw ::Deployment::StopError (name,
                                          "Unknown C++ exception during remove");
        }
      }
      catch (const ::Deployment::StopError &)
      {
        this->close_scheduling_lane (cont, name);

        this->unregister_component (name);

        throw;
      }

      this->close_scheduling_lane (cont, name);

      this->unregister_component (name);

      CIAOX11_LOG_DEBUG ("ExF::Component_Handler::remove_instance - " <<
                         "Finished remove for <" << name << ">");
    }

    void
    Component_Handler::close_scheduling_lane (
        std::shared_ptr<CIAOX11::Container> cont,
        const std::string& name)
    {
      // did we deploy into an ExF container or a regular container
      std::shared_ptr<ExF::Container> exf_container =
          std::dynamic_pointer_cast<ExF::Container> (cont);
      if (exf_container)
      {
        // get the scheduler allocated to the container
        std::shared_ptr<ExF::Scheduler> sched =
            exf_container->the_scheduler ();
        // close the scheduling lane for this component
        if (ExF::SchedulerResult::SOK != sched->close_scheduling_lane (name))
        {
          CIAOX11_LOG_INFO ("ExF::Component_Handler::close_scheduling_lane - " <<
                            "no SchedulingLane to close for <" << name << ">");
          // continue uninstalling
        }
        else
        {
          CIAOX11_LOG_DEBUG ("ExF::Component_Handler::close_scheduling_lane - " <<
                             "closed SchedulingLane for <" << name << ">");
        }
      }
    }

  }
}

extern "C"
{
  void
  create_CIAOX11_EXF_Component_Handler (
      IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type& handler)
  {
    try
    {
      handler = CORBA::make_reference<CIAOX11::ExF::Component_Handler> (
          std::make_unique<CIAOX11::ExF::Connection_Handler> ());
    }
    catch (const std::bad_alloc&)
    {}
  }
}
