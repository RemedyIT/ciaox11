/**
 * @file    ciaox11_timed_trigger_exec.h
 * @author  Martin Corino
 *
 * @brief   CIAOX11 Timed Trigger connector executors
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_CIAOX11_TIMED_TRIGGER_EXEC_H_DFBCCACH_INCLUDED__
#define __RIDL_CIAOX11_TIMED_TRIGGER_EXEC_H_DFBCCACH_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : ciaox11_timed_trigger_impl.h[Header]

#include "ciaox11_timed_triggerEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "tt4ccm_conn_export.h"


//@@{__RIDL_REGEN_MARKER__} - BEGIN : ciaox11_timed_trigger_impl.h[user_includes]
#include "ace/Event_Handler.h"
#include <atomic>
//@@{__RIDL_REGEN_MARKER__} - END : ciaox11_timed_trigger_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ciaox11_timed_trigger_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : ciaox11_timed_trigger_impl.h[user_global_decl]

/// Namespace for implementation of CIAOX11_TT::TimedTrigger component
namespace CIAOX11_TT_TimedTrigger_Impl
{
  /// Forward declarations
  class TimedTrigger_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[user_namespace_decl]


  /// Executor implementation class for tt_scheduler facet
  class tt_scheduler_exec_i final
    : public IDL::traits< ::CCM_TT::CCM_TT_Scheduler>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    tt_scheduler_exec_i (
        IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[ctor]

    /// Destructor
    virtual ~tt_scheduler_exec_i ();

    /** @name Operations from ::CCM_TT::CCM_TT_Scheduler */
    //@{

    virtual
    IDL::traits< ::CCM_TT::TT_Timer>::ref_type
    schedule_trigger (
        IDL::traits< ::CCM_TT::TT_Handler>::ref_type trigger_handler,
        const ::CCM_TT::TT_Duration& trigger_delay) override;

    virtual
    IDL::traits< ::CCM_TT::TT_Timer>::ref_type
    schedule_repeated_trigger (
        IDL::traits< ::CCM_TT::TT_Handler>::ref_type trigger_handler,
        const ::CCM_TT::TT_Duration& start_delay,
        const ::CCM_TT::TT_Duration& interval,
        uint32_t max_rounds) override;

    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_public_ops]
    bool schedule_timer (ACE_Event_Handler* tevh,
                         const ACE_Time_Value& delay,
                         const ACE_Time_Value& interval) noexcept;

    bool cancel_timer (ACE_Event_Handler* tevh) noexcept;

    ACE_Time_Value get_timeofday () noexcept;

    void deactivate ()
    { this->deactivated_ = true; }

    bool deactivated ()
    { return this->deactivated_; }
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_members]
    IDL::traits<CORBA::ORB>::ref_type orb_;
    bool deactivated_ {false};
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : TimedTrigger_exec_i
  class TimedTrigger_exec_i final
    : public virtual IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ctor]
    /// Constructor
    TimedTrigger_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ctor]
    /// Destructor
    virtual ~TimedTrigger_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the tt_scheduler facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_TT::CCM_TT_Scheduler >::ref_type get_tt_scheduler () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    virtual void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    virtual void configuration_complete () override;

    /// Component state change method to activated state
    virtual void ccm_activate () override;

    /// Component state change method to passivated state
    virtual void ccm_passivate () override;

    /// Component state change method to removed state
    virtual void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger_Context >::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_TT::CCM_TT_Scheduler >::ref_type tt_scheduler_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[user_namespace_end_decl]

  // Timer implementation
  class tt_timer_i final
    : public IDL::traits< CCM_TT::TT_Timer>::base_type
  {
  public:
    tt_timer_i (
        IDL::traits<tt_scheduler_exec_i>::ref_type scheduler,
        IDL::traits<CCM_TT::TT_Handler>::ref_type tt_handler,
        uint32_t max_rounds,
        bool recurring)
      : scheduler_ (std::move (scheduler))
      , tt_handler_ (std::move (tt_handler))
      , max_rounds_ (max_rounds)
      , recurring_ (recurring)
    {
    }

    virtual ~tt_timer_i () = default;

    void on_timer (const CCM_TT::TT_Duration& delta_time) noexcept;

    virtual
    void cancel () override;

    virtual
    bool is_canceled () override;

    virtual
    uint32_t rounds () override;

    virtual
    std::string id () override;

  protected:
    friend class tt_event_handler;

    void set_ev_handler (ACE_Event_Handler* evh);

  private:
    tt_timer_i(const tt_timer_i&) = delete;
    tt_timer_i(tt_timer_i&&) = delete;
    tt_timer_i& operator=(const tt_timer_i&) = delete;
    tt_timer_i& operator=(tt_timer_i&&) = delete;

    IDL::traits<tt_scheduler_exec_i>::ref_type scheduler_;
    IDL::traits<CCM_TT::TT_Handler>::ref_type tt_handler_;
    uint32_t const max_rounds_ {};
    bool recurring_ {};
    std::atomic<uint32_t> rounds_ {0};
    std::atomic_bool finished_ {false};
    std::string id_ {};
    std::atomic<ACE_Event_Handler*> ev_handler_ {};
  };

  // EventHandler wrapper for TT_Timer
  class tt_event_handler final
    : public ACE_Event_Handler
  {
  public:
    tt_event_handler (
        IDL::traits<tt_timer_i>::ref_type ccm_timer,
        ACE_Time_Value start_time)
      : ccm_timer_ (std::move (ccm_timer))
      , start_time_ (std::move(start_time))
    {
      // make this event handler reference counted
      this->reference_counting_policy ().value
        (ACE_Event_Handler::Reference_Counting_Policy::ENABLED);
      // provide handler reference to timer for possible cancellation
      this->ccm_timer_->set_ev_handler (this);
    }

    virtual ~tt_event_handler () = default;

    virtual int handle_timeout (const ACE_Time_Value&,
                                const void*) override;

  private:
    tt_event_handler(const tt_event_handler&) = delete;
    tt_event_handler(tt_event_handler&&) = delete;
    tt_event_handler& operator=(const tt_event_handler&) = delete;
    tt_event_handler& operator=(tt_event_handler&&) = delete;

    IDL::traits<tt_timer_i>::ref_type ccm_timer_;
    ACE_Time_Value const start_time_;
  };

  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[user_namespace_end_decl]

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[factory]
  extern "C" TT4CCM_CONN_Export  void
  create_CIAOX11_TT_TimedTrigger_Impl (
    IDL::traits<Components::EnterpriseComponent>::ref_type& component);
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[factory]

} // namespace CIAOX11_TT_TimedTrigger_Impl
//@@{__RIDL_REGEN_MARKER__} - BEGIN : ciaox11_timed_trigger_impl.h[Footer]

#endif /* __RIDL_CIAOX11_TIMED_TRIGGER_EXEC_H_DFBCCACH_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
