/**
 * ****  Code generated by the RIDL Compiler ****
 * RIDL has been developed by:
 *        Remedy IT Expertise BV
 *        The Netherlands
 *        https://www.remedy.nl
 */

#include "messagePS_svnt.h"

// generated from exf4psdd/templates/svnt/src/exf/psdd/exf/psdd/pre_extra_include
#include "exf/deployment/core/ciaox11_schedule.h"

// generated from ccmx11/templates/svnt/src/exf/psdd/component
namespace Test_Msg_PSDD_Event_Impl
{

  PSDD_Event_ExecutorLocator::PSDD_Event_ExecutorLocator (
      IDL::traits< ::Test::Msg::CCM_PSDD_Event>::ref_type component_executor,
      IDL::traits<PSDD_Event_Context>::ref_type component_context) :
        component_executor_ (std::move (component_executor)),
        component_context_ (std::move (component_context))
  {
  }

  bool
  PSDD_Event_ExecutorLocator::connect (
      const ::Components::FeatureName& name,
      IDL::traits<CORBA::Object>::ref_type connection,
      const std::string& conn_name,
      const ::Components::ConfigValues& config)
  {
    X11_UNUSED_ARG(config);
    // generated from exf4psdd/templates/svnt/src/exf/psdd/component_connect
    X11_UNUSED_ARG(conn_name);
    return this->component_context_->set_connection (name,
                                                     std::move(connection),
                                                     config);
  }

  bool
  PSDD_Event_ExecutorLocator::disconnect (
      const ::Components::FeatureName& name,
      const std::string& conn_name)
  {
    X11_UNUSED_ARG(conn_name);
    return this->component_context_->reset_connection (name);
  }

  void
  PSDD_Event_ExecutorLocator::configure (
      ::Components::ConfigValues& config)
  {
    this->set_configuration (config);
    // generated from exf4psdd/templates/svnt/src/exf/psdd/component_configure
    // Mark connector as having no scheduling lane itself
    bool flag { true };
    CORBA::Any val;
    val <<= flag;
    config.push_back (Components::ConfigValue (CIAOX11::ExF::NO_SCHEDULING_LANE, val));
  }

  void
  PSDD_Event_ExecutorLocator::set_configuration (const Components::ConfigValues& descr)
  {
    Components::NameList name_list;
    for (const auto& config_value : descr)
    {
      Components::FeatureName const & descr_name = config_value.name ();
      CORBA::Any const & descr_value = config_value.value ();

      if (descr_name == "topic_name")
      {
        std::string _extract_val{};
        if (!(descr_value >>= _extract_val))
        {
          // Unable to extract value from Any
          name_list.push_back (descr_name);
        }
        else
        {
          this->component_executor_->topic_name (_extract_val);
        }
      }
      else if (descr_name == "type_name")
      {
        // Received value for a readonly attribute which is
        // a configuration error
        name_list.push_back (descr_name);
      }
      else if (descr_name == "publish")
      {
        bool _extract_val{};
        if (!(descr_value >>= _extract_val))
        {
          // Unable to extract value from Any
          name_list.push_back (descr_name);
        }
        else
        {
          this->component_executor_->publish (_extract_val);
        }
      }
      else if (descr_name == "subscribe")
      {
        bool _extract_val{};
        if (!(descr_value >>= _extract_val))
        {
          // Unable to extract value from Any
          name_list.push_back (descr_name);
        }
        else
        {
          this->component_executor_->subscribe (_extract_val);
        }
      }
    }
    if (!name_list.empty ())
    {
      throw CIAOX11::ConfigurationError (name_list);
    }
  }

  IDL::traits<CORBA::Object>::ref_type
  PSDD_Event_ExecutorLocator::obtain_executor ()
  {
    return this->component_executor_;
  }


  // generated from ccmx11/templates/svnt/src/exf/psdd/component_obtain_facet_executor
  IDL::traits<CORBA::Object>::ref_type
  PSDD_Event_ExecutorLocator::obtain_facet_executor (
    const ::Components::FeatureName& name,
    ::Components::ConfigValues& /*config*/)
  {
    if (name == "supplier_data")
    {
      return this->component_executor_->get_supplier_data ();
    }
    if (name == "consumer_data")
    {
      return this->component_executor_->get_consumer_data ();
    }
    if (name == "consumer_data_subscriber")
    {
      return this->component_executor_->get_consumer_data_subscriber ();
    }
    // no match
    throw CIAOX11::InvalidName (name);
  }

  PSDD_Event_Context::PSDD_Event_Context (
      IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
      std::string ins_name) :
        service_registry_ (std::move (svcreg)),
        instance_id_ (std::move (ins_name))
  {
  }

  IDL::traits< ::CIAOX11::Service_Registry>::ref_type
  PSDD_Event_Context::the_service_registry ()
  {
    return this->service_registry_;
  }

  IDL::traits<Test::Msg::Listener>::ref_type
  PSDD_Event_Context::get_connection_consumer_data_listener ()
  {
    return this->consumer_data_listener_;
  }
  // generated from exf4psdd/templates/svnt/src/exf/psdd/connector_context_extra_receptacles
  ::Components::ConfigValues
  PSDD_Event_Context::consumer_data_listener_configuration ()
  {
    return this->consumer_data_listener_config_;
  }


  // generated from exf4psdd/templates/svnt/src/exf/psdd/context_set_connection
  bool
  PSDD_Event_Context::set_connection (
    const std::string& name,
    IDL::traits<CORBA::Object>::ref_type connection,
    const ::Components::ConfigValues& config)
  {
    if (name == "consumer_data_listener")
    {
      this->consumer_data_listener_ = IDL::traits<Test::Msg::Listener>::narrow (std::move(connection));
      // copy all (applicable) configuration values for this connection
      this->consumer_data_listener_config_ = config;
    }
    else
    {
      return false;
    }
    return true;
  }


  // generated from exf4psdd/templates/svnt/src/exf/psdd/context_reset_connection
  bool
  PSDD_Event_Context::reset_connection (
    const std::string& name)
  {
    if (name == "consumer_data_listener")
    {
      this->consumer_data_listener_ = nullptr;
      // Clear configuration values for this connection
      this->consumer_data_listener_config_.clear ();
    }
    else
    {
      return false;
    }
    return true;
  }

  std::string
  PSDD_Event_Context::instance_id ()
  {
    return this->instance_id_;
  }
} /* Test_Msg_PSDD_Event_Impl */

extern "C" void
create_Test_Msg_PSDD_Event_Servant (
  IDL::traits<Components::EnterpriseComponent>::ref_type p,
  IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
  const std::string& ins_name,
  IDL::traits<CIAOX11::ExecutorLocator>::ref_type& executor_locator)
{
  IDL::traits< ::Test::Msg::CCM_PSDD_Event>::ref_type component_executor =
    IDL::traits< ::Test::Msg::CCM_PSDD_Event>::narrow (std::move(p));

  if (component_executor)
  {
    // Create the context for this component, passing in it's ServiceRegistry
    IDL::traits<Test_Msg_PSDD_Event_Impl::PSDD_Event_Context>::ref_type context =
      CORBA::make_reference<Test_Msg_PSDD_Event_Impl::PSDD_Event_Context> (std::move(svcreg), ins_name);

    // Set the new context onto the user component executor
    component_executor->set_session_context (context);

    // Create the executor locator which holds the references
    // to all created entities
    executor_locator =
      CORBA::make_reference <Test_Msg_PSDD_Event_Impl::PSDD_Event_ExecutorLocator> (
        std::move (component_executor),
        std::move (context));
  }
}

// -*- END -*-
