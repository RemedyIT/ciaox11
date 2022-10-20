// -*- C++ -*-
/**
 * @file    ciaox11_timed_trigger_exf_svnt.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 Timed Trigger connector servant using execution framework and timer queue
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "ciaox11_timed_trigger_exf_svnt.h"

#include "ciaox11_timed_trigger_exf_exec.h"
#include "exf/deployment/core/ciaox11_schedule.h"

// generated from ccmx11/templates/svnt/src/component.erb
namespace CIAOX11_TT_TimedTrigger_Impl
{

  TimedTrigger_ExecutorLocator::TimedTrigger_ExecutorLocator (
      IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger>::ref_type component_executor,
      IDL::traits< TimedTrigger_Context>::ref_type component_context) :
        component_executor_ (std::move (component_executor)),
        component_context_ (std::move (component_context))
  {
  }

  bool
  TimedTrigger_ExecutorLocator::connect (
      const ::Components::FeatureName& name,
      IDL::traits<CORBA::Object>::ref_type connection,
      const std::string& conn_name,
      const ::Components::ConfigValues& config)
  {
    X11_UNUSED_ARG(config);
    // generated from ccmx11/templates/svnt/src/component_connect.erb
    X11_UNUSED_ARG(name);
    X11_UNUSED_ARG(connection);
    X11_UNUSED_ARG(conn_name);
    return false;
  }

  bool
  TimedTrigger_ExecutorLocator::disconnect (
      const ::Components::FeatureName& name,
      const std::string& conn_name)
  {
    X11_UNUSED_ARG(name);
    X11_UNUSED_ARG(conn_name);
    return false;
  }

  void
  TimedTrigger_ExecutorLocator::configure (
      ::Components::ConfigValues& config)
  {
    // mark connector as having no scheduling lane itself
    bool flag { true };
    CORBA::Any val;
    val <<= flag;
    config.push_back (
      Components::ConfigValue (CIAOX11::ExF::NO_SCHEDULING_LANE, val));
  }

  IDL::traits<CORBA::Object>::ref_type
  TimedTrigger_ExecutorLocator::obtain_executor ()
  {
    return this->component_executor_;
  }

  IDL::traits<CORBA::Object>::ref_type
  TimedTrigger_ExecutorLocator::obtain_facet_executor (
                          const ::Components::FeatureName& name,
                          ::Components::ConfigValues& config)
  {
    if (name == "tt_scheduler")
    {
      IDL::traits< ::CCM_TT::CCM_TT_Scheduler>::ref_type tt_sched =
        this->component_executor_->get_tt_scheduler ();
      if (tt_sched)
      {
        IDL::traits< ::CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i>::ref_type tt_sched_i =
          IDL::traits< ::CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i>::narrow (tt_sched);
        tt_sched_i->set_config (config);
      }
      return tt_sched;
    }
    // no match
    throw CIAOX11::InvalidName (name);
  }

  TimedTrigger_Context::TimedTrigger_Context (
      IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
      std::string ins_name) :
        service_registry_ (std::move (svcreg)),
        instance_id_ (std::move (ins_name))
  {
  }

  TimedTrigger_Context::~TimedTrigger_Context ()
  {
  }

  IDL::traits< ::CIAOX11::Service_Registry>::ref_type
  TimedTrigger_Context::the_service_registry ()
  {
    return this->service_registry_;
  }

  std::string
  TimedTrigger_Context::instance_id ()
  {
    return this->instance_id_;
  }

  extern "C" void
  create_CIAOX11_TT_TimedTrigger_Servant (
    IDL::traits<Components::EnterpriseComponent>::ref_type p,
    IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
    const std::string& ins_name,
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type& executor_locator)
  {
    IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger>::ref_type component_executor =
      IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger>::narrow (p);

    if (component_executor)
    {
      // Create the context for this component, passing in it's ServiceRegistry
      IDL::traits< CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_Context>::ref_type context =
        CORBA::make_reference <CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_Context> (svcreg, ins_name);

      // Set the created context onto the user component executor
      component_executor->set_session_context (context);

      // Create the executor locator which holds the references
      // to all created entities
      executor_locator =
        CORBA::make_reference <CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_ExecutorLocator> (
          component_executor,
          context);
    }
  }
} /* CIAOX11_TT_TimedTrigger_Impl */

// -*- END -*-
