/**
 * ****  Code generated by the RIDL Compiler ****
 * RIDL has been developed by:
 *        Remedy IT Expertise BV
 *        The Netherlands
 *        https://www.remedy.nl
 */

#include "hello_sender_svnt.h"


// generated from ccmx11/templates/svnt/src/component
namespace Hello_Sender_Impl
{

  Sender_ExecutorLocator::Sender_ExecutorLocator (
      IDL::traits< ::Hello::CCM_Sender>::ref_type component_executor,
      IDL::traits<Sender_Context>::ref_type component_context) :
        component_executor_ (std::move (component_executor)),
        component_context_ (std::move (component_context))
  {
  }

  bool
  Sender_ExecutorLocator::connect (
      const ::Components::FeatureName& name,
      IDL::traits<CORBA::Object>::ref_type connection,
      const std::string& conn_name,
      const ::Components::ConfigValues& config)
  {
    X11_UNUSED_ARG(config);
    // generated from ccmx11/templates/svnt/src/component_connect
    X11_UNUSED_ARG(conn_name);
    return this->component_context_->set_connection (name, std::move(connection));
  }

  bool
  Sender_ExecutorLocator::disconnect (
      const ::Components::FeatureName& name,
      const std::string& conn_name)
  {
    X11_UNUSED_ARG(conn_name);
    return this->component_context_->reset_connection (name);
  }

  void
  Sender_ExecutorLocator::configure (
      ::Components::ConfigValues& config)
  {
    X11_UNUSED_ARG (config);
  }

  IDL::traits<CORBA::Object>::ref_type
  Sender_ExecutorLocator::obtain_executor ()
  {
    return this->component_executor_;
  }


  // generated from ccmx11/templates/svnt/src/component_obtain_facet_executor
  IDL::traits<CORBA::Object>::ref_type
  Sender_ExecutorLocator::obtain_facet_executor (
    const ::Components::FeatureName& name,
    ::Components::ConfigValues& /*config*/)
  {
    // no match
    throw CIAOX11::InvalidName (name);
  }

  Sender_Context::Sender_Context (
      IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
      std::string ins_name) :
        service_registry_ (std::move (svcreg)),
        instance_id_ (std::move (ins_name))
  {
  }

  IDL::traits< ::CIAOX11::Service_Registry>::ref_type
  Sender_Context::the_service_registry ()
  {
    return this->service_registry_;
  }

  IDL::traits<Hello::B>::ref_type
  Sender_Context::get_connection_run_my_B ()
  {
    return this->run_my_B_;
  }


  // generated from ccmx11/templates/svnt/src/context_set_connection
  bool
  Sender_Context::set_connection (
    const std::string& name,
    IDL::traits<CORBA::Object>::ref_type connection)
  {
    if (name == "run_my_B")
    {
      this->run_my_B_ = IDL::traits<Hello::B>::narrow (std::move(connection));
    }
    else
    {
      return false;
    }
    return true;
  }


  // generated from ccmx11/templates/svnt/src/context_reset_connection
  bool
  Sender_Context::reset_connection (
    const std::string& name)
  {
    if (name == "run_my_B")
    {
      this->run_my_B_ = nullptr;
    }
    else
    {
      return false;
    }
    return true;
  }

  std::string
  Sender_Context::instance_id ()
  {
    return this->instance_id_;
  }
} /* Hello_Sender_Impl */

extern "C" void
create_Hello_Sender_Servant (
  IDL::traits<Components::EnterpriseComponent>::ref_type p,
  IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
  const std::string& ins_name,
  IDL::traits<CIAOX11::ExecutorLocator>::ref_type& executor_locator)
{
  IDL::traits< ::Hello::CCM_Sender>::ref_type component_executor =
    IDL::traits< ::Hello::CCM_Sender>::narrow (std::move(p));

  if (component_executor)
  {
    // Create the context for this component, passing in it's ServiceRegistry
    IDL::traits<Hello_Sender_Impl::Sender_Context>::ref_type context =
      CORBA::make_reference<Hello_Sender_Impl::Sender_Context> (std::move(svcreg), ins_name);

    // Set the new context onto the user component executor
    component_executor->set_session_context (context);

    // Create the executor locator which holds the references
    // to all created entities
    executor_locator =
      CORBA::make_reference <Hello_Sender_Impl::Sender_ExecutorLocator> (
        std::move (component_executor),
        std::move (context));
  }
}

// -*- END -*-
