/**
 * @file    ciaox11_component_handler.cpp
 * @author Johnny Willemsen, Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "ciaox11/deployment/handlers/ciaox11_component_handler.h"
#include "dancex11/deployment/deployment_deploymentplanC.h"
#include "ccm/ccm_objectC.h"
#include "ccm/ccm_enterprisecomponentC.h"
#include "ciaox11/deployment/handlers/ciaox11_state.h"
#include "ciaox11/logger/log.h"
#include "dancex11/core/dancex11_dynamic_loader.h"
#include "tao/x11/portable_server/portableserver.h"
//#include "ace/OS_NS_dlfcn.h"

namespace CIAOX11
{
  std::shared_ptr<CIAOX11::Container>
  Component_Handler::fetch_container (const std::string& id)
  {
    return DEPLOYMENT_STATE->fetch_container (id);
  }

  void
  Component_Handler::register_component (
      const std::string& id,
      Components::ConfigValues&& config,
      const std::string& container_id)
  {
    DEPLOYMENT_STATE->register_component (
        id,
        std::move (config),
        container_id);
  }

  std::shared_ptr<CIAOX11::Container>
  Component_Handler::fetch_component_container (
      const std::string& id)
  {
    return DEPLOYMENT_STATE->fetch_component_container (id);
  }

  void
  Component_Handler::unregister_component (
      const std::string& id)
  {
    DEPLOYMENT_STATE->unregister_component (id);
  }

  void
  Component_Handler::close ()
  {
  }

  CORBA::StringSeq
  Component_Handler::dependencies ()
  {
    CORBA::StringSeq retval;
    retval.push_back (DAnCEX11::CCM_CONTAINER);
    return retval;
  }

  std::string
  Component_Handler::instance_type ()
  {
    return DAnCEX11::CCM_COMPONENT;
  }


  void
  Component_Handler::prepare_install (
      const ::Deployment::DeploymentPlan& plan,
      const ::Deployment::MonolithicDeploymentDescription &mdd,
      const Deployment_Common::Instance_Info& info,
      std::string& exec_art,
      std::string& exec_entry,
      std::string& svnt_art,
      std::string& svnt_entry,
      uint32_t open_mode,
      std::string& cont_id)
  {
    std::string tmp, error_string;

    DAnCEX11::Utility::PROPERTY_MAP::const_iterator i = info.pmap.find (DAnCEX11::COMPONENT_SVNT_FACTORY);
    if (i != info.pmap.end ())
    {
      if (i->second >>= svnt_entry)
      {
        CIAOX11_LOG_DEBUG ("Component_Handler::prepare_install - " <<
                           "Found servant entry point <" << info.name << ">:<" << svnt_entry << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                           "Unable to extract servant entrypoint for <" << info.name << ">");
        error_string += "Unable to extract servant entrypoint\n";
      }
    }
    else
    {
      CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                         "No servant entry point found <" << info.name << ">");
      error_string += "No servant entrypoint identified\n";
    }

    i = info.pmap.find (DAnCEX11::DANCE_PLUGIN_OPENMODE);
    if (i != info.pmap.end ())
    {
      if (i->second >>= open_mode)
      {
        CIAOX11_LOG_DEBUG ("Component_Handler::prepare_install - " <<
                           "Found open mode <" << info.name << ">:<" << open_mode << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                           "Unable to extract open mode for <" << info.name << ">");
      }
    }

    i = info.pmap.find (DAnCEX11::COMPONENT_SVNT_ARTIFACT);
    if (i != info.pmap.end ())
    {
      if (i->second >>= tmp)
      {
        svnt_art = Deployment_Common::get_implementation (tmp, mdd, plan);
        CIAOX11_LOG_DEBUG ("Component_Handler::prepare_install - " <<
                           "Found servant artifact <" << info.name << ">:"\
                           "<" << tmp << ":=" << svnt_art << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                           "Unable to extract servant artifact for <" << info.name << ">");
        error_string += "Unable to extract servant artifact\n";
      }
    }
    else
    {
      CIAOX11_LOG_INFO ("Component_Handler::prepare_install - " <<
                        "No servant artifact found <" << info.name << ">");
    }

    i = info.pmap.find (DAnCEX11::COMPONENT_ARTIFACT);
    if (i != info.pmap.end ())
    {
      if (i->second >>= tmp)
      {
        exec_art = Deployment_Common::get_implementation (tmp, mdd, plan);
        CIAOX11_LOG_DEBUG ("Component_Handler::prepare_install - " <<
                           "Found executor artifact <" << info.name << ">:"\
                           "<" << tmp << ":=" << exec_art << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                           "Unable to extract executor artifact for <" << info.name << ">");
        error_string += "Unable to extract executor artifact\n";
      }
    }
    else
    {
      CIAOX11_LOG_INFO ("Component_Handler::prepare_install - " <<
                        "No executor artifact found <" << info.name << ">");
    }

    i = info.pmap.find (DAnCEX11::COMPONENT_FACTORY);
    if (i != info.pmap.end ())
    {
      if (i->second >>= exec_entry)
      {
        CIAOX11_LOG_DEBUG ("Component_Handler::prepare_install - " <<
                           "Found executor entry point <" << info.name << ">:<" << exec_entry << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                           "Unable to extract executor entrypoint for <" << info.name << ">");
        error_string += "Unable to extract executor entrypoint\n";
      }
    }
    else
    {
      CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                         "No executor entry point found <" << info.name << ">");
      error_string += "No executory entrypoint identified\n";
    }

    i = info.pmap.find (CIAOX11::CONTAINER_ID);
    if (i != info.pmap.end ())
    {
      if (i->second >>= cont_id)
      {
        CIAOX11_LOG_DEBUG ("Component_Handler::install_instance - " <<
                           "Found container <" << info.name << ">:<" << cont_id << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                           "Unable to extract container id for <" << info.name << ">");
        error_string += "Unable to extract container id\n";
      }
    }
    else
    {
      CIAOX11_LOG_DEBUG ("Component_Handler::install_instance - " <<
                         "Found no container using default <" << info.name << ">:<" << cont_id << ">");
    }

    if (exec_entry == svnt_entry)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::prepare_install - " <<
                         "Executor and servant entrypoints are equal for <" <<
                         info.name << "> : " << exec_entry);
      error_string += "Executor and servant entrypoints are equal\n";
    }

    if (!error_string.empty ())
    {
      throw Deployment::PlanError (info.name, error_string);
    }

    if (svnt_art.empty ())
    {
      CIAOX11_LOG_INFO ("Component_Handler::install_instance - " <<
                        "Empty servant artifact for <" << info.name << "> "\
                        "using executor artifact <" << exec_art << ">");
      svnt_art = exec_art;
    }
    else if (exec_art.empty ())
    {
      exec_art = svnt_art;
      CIAOX11_LOG_INFO ("Component_Handler::install_instance - " <<
                        "Empty executor artifact for <" << info.name << "> "\
                        "using servant artifact <" << svnt_art << ">");
    }
  }

  IDL::traits<CIAOX11::ExecutorLocator>::ref_type
  Component_Handler::create_component (
      const Deployment_Common::Instance_Info& info,
      const std::string& exec_art,
      const std::string& exec_entry,
      const std::string& svnt_art,
      const std::string& svnt_entry,
      uint32_t open_mode,
      std::shared_ptr<CIAOX11::Container> container)
  {
    std::string error_string;

    DANCEX11_LOG_DEBUG ("Component_Handler::create_component - " \
                        "Loading component executor factory for <" << info.name << "> "\
                        "<" << exec_entry << "@" << exec_art << ">");

    DAnCEX11::DL_Module exec_mod (exec_art, open_mode);
    auto exec_factory =
        exec_mod.resolve<void, IDL::traits<Components::EnterpriseComponent>::ref_type&> (error_string, exec_entry);
    if (!exec_factory)
    {
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - " \
                          "Failed loading component executor factory for <" << info.name << "> "\
                          ":" << error_string);

      throw Deployment::StartError (info.name, error_string);
    }

    DANCEX11_LOG_DEBUG ("Component_Handler::create_component - " \
                        "Loading component servant factory for <" << info.name << "> "\
                        "<" << svnt_entry << "@" << svnt_art << ">");

    DAnCEX11::DL_Module svnt_mod (svnt_art, open_mode);
    auto svnt_factory = svnt_mod.resolve<void,
                                         IDL::traits<Components::EnterpriseComponent>::ref_type,
                                         IDL::traits<CIAOX11::Service_Registry>::ref_type,
                                         const std::string&,
                                         IDL::traits<CIAOX11::ExecutorLocator>::ref_type&> (error_string, svnt_entry);
    if (!svnt_factory)
    {
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - " \
                          "Failed loading component servant factory for <" << info.name << "> "\
                          ":" << error_string);

      throw Deployment::StartError (info.name, error_string);
    }

    DANCEX11_LOG_DEBUG ("Component_Handler::create_component - " \
                        "Creating component executor for <" << info.name << ">");

    IDL::traits<Components::EnterpriseComponent>::ref_type component_executor;
    try
    {
      exec_factory (component_executor);
    }
    catch (const CORBA::Exception& ex)
    {
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - " \
                          "Caught exception from component factory <" << ex << ">");
      throw Deployment::StartError (info.name, "Component executor factory threw exception");
    }
    catch (...)
    {
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - "\
                          "Caught unknown exception from component factory");
      throw Deployment::StartError (info.name, "Component executor factory threw exception");
    }

    if (!component_executor)
    {
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - "\
                          "Component executor factory failed");

      throw Deployment::StartError (info.name, "Component executor factory failed");
    }

    DANCEX11_LOG_DEBUG ("Component_Handler::create_component - "\
                        "Creating component executor locator for <" << info.name << ">");

    IDL::traits<CIAOX11::ExecutorLocator>::ref_type executor_locator;

    try
    {
      svnt_factory (component_executor,
                    container->the_service_registry (),
                    info.name,
                    executor_locator);
    }
    catch (const CORBA::Exception& ex)
    {
      std::ostringstream err {"Executor locator factory threw exception <"};
      err << ex << ">";
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - "\
                          << err.str ());
      throw Deployment::StartError (info.name, err.str ());
    }
    catch (const std::exception& ex)
    {
      std::ostringstream err {"Executor locator factory threw std exception <"};
      err << ex.what () << ">";
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - "\
                          << err.str ());
      throw Deployment::StartError (info.name, err.str ());
    }
    catch (...)
    {
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - "\
                          "Caught unknown exception from executor locator factory for <" << info.name << ">");

      throw Deployment::StartError (info.name, "Executor locator factory threw unknown exception");
    }

    if (!executor_locator)
    {
      DANCEX11_LOG_ERROR ("Component_Handler::create_component - "\
                          "Executor locator factory failed for <" << info.name << ">");

      throw Deployment::StartError (info.name, "Executor locator factory failed");
    }

    DANCEX11_LOG_DEBUG ("Component_Handler::create_component - "\
                        "Component <" << info.name << "> successfully created");

    return executor_locator;
  }

  void
  Component_Handler::install_instance (const Deployment::DeploymentPlan &plan,
                                         uint32_t instanceRef,
                                         CORBA::Any& instance_reference)
  {
    CIAOX11_CALL_TRACE ("Component_Handler_i::install_instance");

    const ::Deployment::InstanceDeploymentDescription &idd (plan.instance()[instanceRef]);
    const ::Deployment::MonolithicDeploymentDescription &mdd (plan.implementation()[idd.implementationRef()]);

    Deployment_Common::Instance_Info info;
    info.name = idd.name ();

    CIAOX11_LOG_DEBUG ("Component_Handler::install_instance - " <<
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
      DANCEX11_LOG_ERROR ("Component_Handler::install_instance - " <<
                         "Container not found <" << info.name << ">:<" << cont_id << ">");
      throw ::Deployment::PlanError (info.name, "Invalid container\n");
    }

    IDL::traits<CIAOX11::ExecutorLocator>::ref_type executor_locator =
        this->create_component (info, exec_art, exec_entry, svnt_art, svnt_entry, open_mode, container);

    IDL::traits<Components::CCMObject>::ref_type comp_ref;
    try
    {
      // collect unique configuration values for component
      Components::ConfigValues exec_config;
      Deployment_Common::collect_config_values (info.pmap,
                                                exec_config);

      // configure component (and optionally collect additional/updated values)
      executor_locator->configure (exec_config);

      // install component in container
      if (!container->install_component (idd.name (), executor_locator))
      {
        throw ::Deployment::StartError (idd.name (),
                                        "Failed to install component");
      }

      this->register_component (
          idd.name (),
          std::move (exec_config),
          cont_id);

      CIAOX11_LOG_DEBUG ("Component_Handler::install_instance - " <<
                         "installed component <" << idd.name () << ">:<" << cont_id << ">");

    }
    catch (const ::Deployment::StartError &)
    {
      throw;
    }
    catch (const ::CORBA::Exception &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Component_Handler_i::install_instance - " <<
                         "Caught CORBA exception <" << idd.name () << ">:<" << err.str () << ">");
      throw ::Deployment::StartError (idd.name (), err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::install_instance - " <<
                         "Caught C++ std::exception <" << idd.name () << ">:<" <<
                         ex.what () << ">");
      throw ::Deployment::StartError (idd.name (),
                                      ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::install_instance - " <<
                         "Caught unknown C++ exception <" << idd.name () << ">");
      throw ::Deployment::StartError (idd.name (),
                                      "Unknown C++ exception\n");
    }

    comp_ref = Deployment_Common::get_ccm_object (info.name);
    instance_reference <<= comp_ref;
  }

  void
  Component_Handler::activate_instance (const Deployment::DeploymentPlan &plan,
                                     uint32_t instanceRef,
                                     const CORBA::Any &)
  {
    std::string const name = plan.instance ()[instanceRef].name ();

    CIAOX11_LOG_DEBUG ("Component_Handler::activate_instance - " <<
                       "Starting activate for <" << name << ">");

    std::shared_ptr<CIAOX11::Container> cont =
      this->fetch_component_container (name);

    if (!cont)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::activate_instance - " <<
                         "Container not found for <" << name << ">");
      throw ::Deployment::StartError (
          name,
          "Unable to activate due to nil container reference");
    }

    try
    {
      if (!cont->activate_component (name))
      {
        throw ::Deployment::StartError (name,
                                        "Failed to activate component");
      }
    }
    catch (const ::Deployment::StartError &)
    {
      throw;
    }
    catch (const CORBA::Exception &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Component_Handler_i::activate_instance - " <<
                         "Caught CORBA exception <" << name << ">:<" << err.str () << ">");
      throw ::Deployment::StartError (name, err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::activate_instance - " <<
                         "Caught C++ std::exception <" << name << ">:<" <<
                         ex.what () << ">");
      throw ::Deployment::StartError (name,
                                      ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::activate_instance - " <<
                         "Caught unknown C++ exception <" << name << ">");
      throw ::Deployment::StartError (
          name,
          "Unknown C++ exception during activation");
    }
  }

  void
  Component_Handler::passivate_instance (const Deployment::DeploymentPlan &plan,
                                           uint32_t instanceRef,
                                           const CORBA::Any &)
  {
    std::string const name = plan.instance ()[instanceRef].name ();

    CIAOX11_LOG_DEBUG ("Component_Handler::passivate_instance - " <<
                       "Starting passivate for <" << name << ">");

    std::shared_ptr<CIAOX11::Container> cont =
      this->fetch_component_container (name);

    if (!cont)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::passivate_instance - " <<
                         "Container not found for <" << name << ">");
      throw ::Deployment::StopError (name,
                                     "Unable to activate due to nil container reference");
    }

    try
    {
      if (!cont->passivate_component (name))
      {
        throw ::Deployment::StopError (name,
                                        "Failed to passivate component");
      }
    }
    catch (const ::Deployment::StartError &)
    {
      throw;
    }
    catch (const CORBA::Exception &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Component_Handler_i::passivate_instance - " <<
                         "Caught CORBA exception <" << name << ">:<" << err.str () << ">");
      throw ::Deployment::StopError (name, err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::passivate_instance - " <<
                         "Caught C++ std::exception <" << name << ">:<" <<
                         ex.what () << ">");
      throw ::Deployment::StopError (name,
                                      ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::passivate_instance - " <<
                         "Caught unknown C++ exception <" << name << ">");
      throw ::Deployment::StopError (name,
                                      "Unknown C++ exception during passivation");
    }
  }

  void
  Component_Handler::remove_instance (const Deployment::DeploymentPlan & plan,
                                        uint32_t instanceRef,
                                        const CORBA::Any &)
  {
    std::string const name = plan.instance ()[instanceRef].name ();

    CIAOX11_LOG_DEBUG ("Component_Handler::remove_instance - " <<
                       "Starting remove for <" << name << ">");

    std::shared_ptr<CIAOX11::Container> cont =
      this->fetch_component_container (name);

    if (!cont)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::remove_instance - " <<
                         "Container not found for <" << name << ">");
      throw ::Deployment::StopError (name,
                                     "Unable to remove due to nil container reference");
    }

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
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Component_Handler_i::remove_instance - " <<
                         "Caught CORBA exception <" << name << ">:<" << err.str () << ">");
      throw ::Deployment::StopError (name, err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::remove_instance - " <<
                         "Caught C++ std::exception <" << name << ">:<" <<
                         ex.what () << ">");
      throw ::Deployment::StopError (name,
                                      ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::remove_instance - " <<
                         "Caught unknown C++ exception <" << name << ">");
      throw ::Deployment::StopError (name,
                                      "Unknown C++ exception during remove");
    }

    this->unregister_component (name);

    CIAOX11_LOG_DEBUG ("Component_Handler::remove_instance - " <<
                       "Finished remove for <" << name << ">");
  }

  void
  Component_Handler::provide_endpoint_reference (const Deployment::DeploymentPlan & plan,
                                                   uint32_t connectionRef,
                                                   CORBA::Any& endpoint_reference)
  {
    this->connection_handler_->provide_endpoint_reference (plan,
                                                         connectionRef,
                                                         endpoint_reference);
  }

  void
  Component_Handler::connect_instance (const Deployment::DeploymentPlan & plan,
                                         uint32_t connectionRef,
                                         const CORBA::Any & provided_reference)
  {
    this->connection_handler_->connect_instance (plan,
                                               connectionRef,
                                               provided_reference);
  }

  void
  Component_Handler::disconnect_instance (const Deployment::DeploymentPlan & plan,
                                            uint32_t connectionRef)
  {
    this->connection_handler_->disconnect_instance (plan,
                                                  connectionRef);

  }

  void
  Component_Handler::instance_configured (const Deployment::DeploymentPlan & plan,
                                            uint32_t instanceRef)
  {
    std::string const name = plan.instance ()[instanceRef].name ();

    CIAOX11_LOG_DEBUG ("Component_Handler::instance_configured - " <<
                       "Starting configured_component for <" << name << ">");

    std::shared_ptr<CIAOX11::Container> cont =
      this->fetch_component_container (name);

    if (!cont)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::instance_configured - " <<
                         "Container not found for <" << name << ">");
      throw ::Deployment::StartError (name,
                                     "Unable to activate due to nil container reference");
    }

    try
    {
      if (!cont->configured_component (name))
      {
        throw ::Deployment::StartError (name,
                                        "Failed to set component configured");
      }
    }
    catch (const ::Deployment::StartError &)
    {
      throw;
    }
    catch (const CORBA::Exception &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Component_Handler_i::instance_configured - " <<
                         "Caught CORBA exception <" << name << ">:<" << err.str () << ">");
      throw ::Deployment::StartError (name, err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::instance_configured - " <<
                         "Caught C++ std::exception <" << name << ">:<" <<
                         ex.what () << ">");
      throw ::Deployment::StartError (name,
                                      ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::instance_configured - " <<
                         "Caught unknown C++ exception <" << name << ">");
      throw ::Deployment::StartError (name,
                                      "Unknown C++ exception during instance configured");
    }
  }

  void
  Component_Handler::configure (const ::Deployment::Properties & )
  {
  }
}

extern "C"
{
  void
  create_CIAOX11_Component_Handler (
    IDL::traits<DAnCEX11::InstanceDeploymentHandler>::ref_type& handler)
  {
    try
    {
      handler = CORBA::make_reference<CIAOX11::Component_Handler> (
          std::make_unique<CIAOX11::Connection_Handler> ());
    }
    catch (const std::bad_alloc&)
    {
      CIAOX11_LOG_ERROR ("create_CIAOX11_Component_Handler - " <<
                         "no memory");
    }
  }
}
