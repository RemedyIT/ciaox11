/**
 * @file    ciaox11_timed_trigger_exf_exec.cpp
* @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 Timed Trigger connector executors using execution framework and timer queue
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11_timed_trigger_exf_exec.h"

#include "exf/deployment/core/ciaox11_exf_util.h"
#include "exf/deployment/core/ciaox11_schedule.h"

#include "ciaox11/logger/log.h"

namespace CIAOX11_TT_TimedTrigger_Impl
{
   /**
   * Facet Executor Implementation Class : tt_scheduler_exec_i
   */

   tt_scheduler_exec_i::tt_scheduler_exec_i (
    IDL::traits<::CIAOX11_TT::CCM_TimedTrigger_Context>::ref_type context,
    TimerMonitor::ref_type monitor)
    : context_ (std::move (context)),
      monitor_ (std::move (monitor))
  {
    CIAOX11_LOG_DEBUG ("tt_scheduler_exec_i::tt_scheduler_exec_i using exf framework.");
  }

  tt_scheduler_exec_i::~tt_scheduler_exec_i ()
  {
  }

  /** Operations and attributes from tt_scheduler */

  IDL::traits<::CCM_TT::TT_Timer>::ref_type
  tt_scheduler_exec_i::schedule_trigger (
      IDL::traits<::CCM_TT::TT_Handler>::ref_type trigger_handler,
      const ::CCM_TT::TT_Duration& trigger_delay)
  {
    // schedule as trigger with zero interval and max 1 rounds
    return this->schedule_repeated_trigger (
        trigger_handler,
        trigger_delay,
        CCM_TT::TT_Duration (),
        1);
  }

  IDL::traits<::CCM_TT::TT_Timer>::ref_type
  tt_scheduler_exec_i::schedule_repeated_trigger (
      IDL::traits<::CCM_TT::TT_Handler>::ref_type trigger_handler,
      const ::CCM_TT::TT_Duration& start_delay,
      const ::CCM_TT::TT_Duration& interval,
      uint32_t max_rounds)
  {
    // schedule timer
    timespec_t const ts_delay {
      ACE_Utils::truncate_cast<time_t> (start_delay.sec ()),
      ACE_Utils::truncate_cast<long> (start_delay.nanosec ())
    };

    timespec_t const ts_interval {
      ACE_Utils::truncate_cast<time_t> (interval.sec ()),
      ACE_Utils::truncate_cast<long> (interval.nanosec ())
    };

    try
    {
      return this->monitor_->start_monitoring(trigger_handler,
                                              ACE_Time_Value (ts_delay),
                                              ACE_Time_Value (ts_interval),
                                              max_rounds,
                                              this->scheduling_lane_,
                                              this->get_exf_tts_settings_);
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("tt_scheduler_exec_i::schedule_repeated_trigger - " <<
                         "caught unexpected C++ exception");
    }

    return {};
  }

   void tt_scheduler_exec_i::set_config (
       const ::Components::ConfigValues& config)
   {
     // check for scheduling lane
     for (const Components::ConfigValue& cval : config)
     {
       if (cval.name () == CIAOX11::ExF::SCHEDULING_LANE_REF)
       {
         IDL::traits<CORBA::Object>::ref_type objref {};
         if (!(cval.value () >>= objref))
         {
           throw std::runtime_error ("failed to  extract " +
                                     CIAOX11::ExF::SCHEDULING_LANE_REF +
                                     " for timer connector");
         }
         this->scheduling_lane_ =
             IDL::traits<CIAOX11::ExF::SchedulingLane>::narrow (objref);
       }
     }

     if (this->scheduling_lane_)
     {
       // get scheduling settings
       CIAOX11::ExF::Settings def_settings {};
       if (CIAOX11::ExF::Util::get_exf_defaults (config, def_settings))
       {
         this->get_exf_tts_settings_ = def_settings;
        }

       // check for scheduling properties
       CIAOX11::ExF::Util::get_exf_settings (config, "handle_trigger", this->get_exf_tts_settings_);
     }
   }


  /**
   * Component Executor Implementation Class : TimedTrigger_exec_i
   */
  TimedTrigger_exec_i::TimedTrigger_exec_i ()
  {
  }

  TimedTrigger_exec_i::~TimedTrigger_exec_i ()
  {
  }

  /** Session component operations */
  void TimedTrigger_exec_i::configuration_complete ()
  {
  }

  void TimedTrigger_exec_i::ccm_activate ()
  {
  }

  void TimedTrigger_exec_i::ccm_passivate ()
  {
    this->monitor_->deactivate ();
   }

  void TimedTrigger_exec_i::ccm_remove ()
  {
  }


  IDL::traits<::CCM_TT::CCM_TT_Scheduler>::ref_type
  TimedTrigger_exec_i::get_tt_scheduler ()
  {
    if (!this->monitor_)
    {
      this->monitor_ = TimerMonitor::create_instance ();
    }
    if (this->monitor_)
    {
      this->tt_schedulers_.push_back (CORBA::make_reference <tt_scheduler_exec_i> (
                                         this->context_,
                                         this->monitor_));
       return this->tt_schedulers_.back ();
    }
    else
    {
      CIAOX11_LOG_ERROR ("TimedTrigger_exec_i::get_tt_scheduler - " <<
                         "Unable to create monitor. ");
    }
    return {};
  }

  /// Operations from Components::SessionComponent
  void
  TimedTrigger_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    this->context_ = IDL::traits<::CIAOX11_TT::CCM_TimedTrigger_Context >::narrow (std::move(ctx));
  }

  extern "C" void
  create_CIAOX11_TT_TimedTrigger_Impl (
    IDL::traits<Components::EnterpriseComponent>::ref_type& component)
  {
    component = CORBA::make_reference <TimedTrigger_exec_i> ();
  }

} // namespace CIAOX11_TT_TimedTrigger_Impl
