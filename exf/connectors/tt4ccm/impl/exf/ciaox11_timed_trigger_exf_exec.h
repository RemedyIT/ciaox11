/**
 * @file    ciaox11_timed_trigger_exf_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 Timed Trigger connector executors using execution framework and timer queue
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_CIAOX11_TIMED_TRIGGER_EXF_EXEC_H_DFBCCACH_INCLUDED__
#define __RIDL_CIAOX11_TIMED_TRIGGER_EXF_EXEC_H_DFBCCACH_INCLUDED__

#include "ciaox11_timed_triggerEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "tt4ccm_exf_conn_export.h"


#include "ciaox11_timer_queue_i.h"

/// Namespace for implementation of CIAOX11_TT::TimedTrigger component
namespace CIAOX11_TT_TimedTrigger_Impl
{
  /// Forward declarations
  class TimedTrigger_exec_i;

  /// Executor implementation class for tt_scheduler facet
  class tt_scheduler_exec_i final
    : public IDL::traits<::CCM_TT::CCM_TT_Scheduler>::base_type
  {
  public:

    /// Constructor
    /// @param[in] context Component context
    tt_scheduler_exec_i (
        IDL::traits<::CIAOX11_TT::CCM_TimedTrigger_Context>::ref_type context,
        TimerMonitor::ref_type monitor);

    /// Destructor
    ~tt_scheduler_exec_i () override;

    /** @name Operations from ::CCM_TT::CCM_TT_Scheduler */
    //@{

    IDL::traits<::CCM_TT::TT_Timer>::ref_type
    schedule_trigger (
        IDL::traits<::CCM_TT::TT_Handler>::ref_type trigger_handler,
        const ::CCM_TT::TT_Duration& trigger_delay) override;

    IDL::traits<::CCM_TT::TT_Timer>::ref_type
    schedule_repeated_trigger (
        IDL::traits<::CCM_TT::TT_Handler>::ref_type trigger_handler,
        const ::CCM_TT::TT_Duration& start_delay,
        const ::CCM_TT::TT_Duration& interval,
        uint32_t max_rounds) override;
    //@}

    /** @name User defined public operations. */
    //@{
    void deactivate ()
    { this->monitor_->deactivate (); }

    void set_config (
         const ::Components::ConfigValues& config);
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::CIAOX11_TT::CCM_TimedTrigger_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    TimerMonitor::ref_type monitor_;
    // generated from ccmx11/exf4cc/comp_exec/hdr/corba/exf/component_extra_private.erb
    IDL::traits<CIAOX11::ExF::SchedulingLane>::ref_type scheduling_lane_ {};

    /// Member variables for ExF configuration
    CIAOX11::ExF::Deadline get_exf_tts_deadline_ {};
    CIAOX11::ExF::Priority get_exf_tts_priority_ {};
    //@}
  };

  /// Component Executor Implementation Class : TimedTrigger_exec_i
  class TimedTrigger_exec_i final
    : public virtual IDL::traits<::CIAOX11_TT::CCM_TimedTrigger>::base_type
  {
  public:
    /// Constructor
    TimedTrigger_exec_i ();
    /// Destructor
    ~TimedTrigger_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the tt_scheduler facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_TT::CCM_TT_Scheduler>::ref_type get_tt_scheduler () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}


  private:
    /// Context for component instance.
    IDL::traits<::CIAOX11_TT::CCM_TimedTrigger_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    typedef std::vector<IDL::traits<::CCM_TT::CCM_TT_Scheduler>::ref_type> tt_sched_list_t;
    tt_sched_list_t tt_schedulers_;
    //@}

    /** @name User defined members. */
    //@{
    TimerMonitor::ref_type monitor_;
    //@}


  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    TimedTrigger_exec_i(const TimedTrigger_exec_i&) = delete;
    TimedTrigger_exec_i(TimedTrigger_exec_i&&) = delete;
    TimedTrigger_exec_i& operator=(const TimedTrigger_exec_i&) = delete;
    TimedTrigger_exec_i& operator=(TimedTrigger_exec_i&&) = delete;
    //@}
  };


  extern "C" TT4CCM_EXF_CONN_Export  void
  create_CIAOX11_TT_TimedTrigger_Impl (
    IDL::traits<Components::EnterpriseComponent>::ref_type& component);
} // namespace CIAOX11_TT_TimedTrigger_Impl

#endif /* __RIDL_CIAOX11_TIMED_TRIGGER_EXF_EXEC_H_DFBCCACH_INCLUDED__ */
