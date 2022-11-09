/**
 * @file   ciaox11_timer_queue_i.h
 * @author Marijke Hengstmengel
 *
 * @brief AXCIOMA timer-queue implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CIAOX11_TIMER_QUEUE_IMPL_H
#define CIAOX11_TIMER_QUEUE_IMPL_H


#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include /**/ "tt4ccm_exf_conn_export.h"
#include "ciaox11_timed_triggerEC.h"
#include "exf/deployment/core/ciaox11_schedule.h"

#include "ace/Timer_Wheel_T.h"
#include "ace/Synch_Traits.h"
#if defined(ACE_WIN32) || \
    (defined (_POSIX_MONOTONIC_CLOCK) && !defined (ACE_LACKS_MONOTONIC_TIME)) || \
    defined (ACE_HAS_CLOCK_GETTIME_MONOTONIC)
# include "ace/Monotonic_Time_Policy.h"
# define EXF_TIME_POLICY  ACE_Monotonic_Time_Policy
#else
# include "ace/Time_Policy.h"
# define EXF_TIME_POLICY  ACE_System_Time_Policy
#endif
#include "ace/Task.h"
#include "ace/Auto_Event.h"

#include <atomic>
#include <memory>

namespace CIAOX11_TT_TimedTrigger_Impl
{
  //forward declaration
  class TimerMonitor;

  class TTC_Task_Timer_Upcall;

  //  Timer object implementation
  class tt_timer_i final
      : public IDL::traits< CCM_TT::TT_Timer>::base_type
  {
  public:
    typedef std::shared_ptr< tt_timer_i> ref_s_type;

    tt_timer_i (
        TimerMonitor& monitor,
        IDL::traits<CCM_TT::TT_Handler>::ref_type tt_handler,
        uint32_t max_rounds,
        const ACE_Time_Value& start_time,
        bool recurring,
        IDL::traits<CIAOX11::ExF::SchedulingLane>::ref_type scheduling_lane,
        CIAOX11::ExF::Deadline exf_deadline,
        CIAOX11::ExF::Priority exf_priority)
      : monitor_ (monitor)
      , tt_handler_ (std::move(tt_handler))
      , max_rounds_ (max_rounds)
      , start_time_ (start_time)
      , recurring_ (recurring)
      , scheduling_lane_(std::move(scheduling_lane))
      , exf_deadline_ (exf_deadline)
      , exf_priority_ (exf_priority)
    {
      this->set_id_ ();
    }

    ~tt_timer_i () override;

    void on_timer (const CCM_TT::TT_Duration& delta_time) noexcept;

    void cancel () override;

    bool is_canceled () override;

    uint32_t rounds () override;

    std::string id () override;

    ACE_Time_Value start_time ()const
    { return this->start_time_; }

    bool is_recurring () const
    {return this->recurring_;}

    IDL::traits<CCM_TT::TT_Handler>::ref_type tt_handler()
    {return this->tt_handler_;}

    CIAOX11::ExF::Deadline exf_deadline()
    {return this->exf_deadline_;}

    CIAOX11::ExF::Priority exf_priority()
    {return this->exf_priority_;}

  private:
    tt_timer_i (const tt_timer_i&) = delete;
    tt_timer_i (tt_timer_i&&) = delete;
    tt_timer_i& operator= (const tt_timer_i&) = delete;
    tt_timer_i& operator= (tt_timer_i&&) = delete;

    void set_id_ ();

    TimerMonitor& monitor_;
    IDL::traits<CCM_TT::TT_Handler>::ref_type tt_handler_;
    uint32_t const max_rounds_;
    std::atomic<uint32_t> rounds_ {0};
    std::atomic_bool finished_ {false};
    std::atomic_bool cancelled_ {false};
    ACE_Time_Value start_time_;
    bool recurring_ {false};
    IDL::traits<CIAOX11::ExF::SchedulingLane>::ref_type scheduling_lane_ {};
    CIAOX11::ExF::Deadline exf_deadline_ {};
    CIAOX11::ExF::Priority exf_priority_ {};
    std::string id_ {};
  };

  class TimerMonitor final
   : private ACE_Task_Base
  {
  public:
    typedef std::shared_ptr<TimerMonitor>  ref_type;

    struct TT_QEntry
    {
      IDL::traits<tt_timer_i>::ref_type tt_timer_ {};

      TT_QEntry () {}
      TT_QEntry (std::nullptr_t) {}
      TT_QEntry (IDL::traits< tt_timer_i>::ref_type tmr)
      { this->tt_timer_ = std::move(tmr); }
      TT_QEntry (const TT_QEntry& ttqe)
      { this->tt_timer_ = ttqe.tt_timer_; }
      TT_QEntry (TT_QEntry&& ttqe)
      { this->tt_timer_ = std::move (ttqe.tt_timer_); }

      bool operator ==(const TT_QEntry& ttqe)
      { return (this->tt_timer_.operator ->()) == (ttqe.tt_timer_.operator ->()); }

      void operator =(const TT_QEntry& ttqe)
      { this->tt_timer_ = ttqe.tt_timer_; }
      void operator =(TT_QEntry&& ttqe)
      { this->tt_timer_ = std::move (ttqe.tt_timer_); }
    };

    TimerMonitor ();
    ~TimerMonitor () override;

    /**
     * Start monitoring
     */
    IDL::traits< ::CCM_TT::TT_Timer>::ref_type
    start_monitoring (IDL::traits< ::CCM_TT::TT_Handler>::ref_type trigger_handler,
                      const ACE_Time_Value& delay,
                      const ACE_Time_Value& interval,
                      uint32_t max_rounds,
                      IDL::traits< CIAOX11::ExF::SchedulingLane>::ref_type scheduling_lane,
                      CIAOX11::ExF::Priority exf_priority ,
                      CIAOX11::ExF::Deadline exf_deadline);

    /**
     * Stop monitoring.
     */
    bool stop_monitoring (const TT_QEntry&);

    /**
     * Create a monitor instance.
     */
    static ref_type create_instance ();

    void deactivate ()
    { this->deactivated_ = true; }

    bool deactivated () const
    { return this->deactivated_; }

  private:
    class TTC_Task_Timer_Upcall final
    {
    public:
      // = Initialization and termination methods.
      /// Constructor.
      TTC_Task_Timer_Upcall () = default;

      typedef ACE_Timer_Queue_T<TT_QEntry,
                                TTC_Task_Timer_Upcall,
                                ACE_SYNCH_RECURSIVE_MUTEX,
                                EXF_TIME_POLICY> TimerQueue;
      /// Destructor.
      ~TTC_Task_Timer_Upcall () = default;

      /// This method is called when a timer is registered.
      int registration (TimerQueue & /*timer_queue*/,
                        TimerMonitor::TT_QEntry /*timer*/,
                        const void * /*arg*/);

      /// This method is called before the timer expires.
      int preinvoke (TimerQueue & /*timer_queue*/,
                     TT_QEntry /*timer*/,
                     const void * /*arg*/,
                     int /*recurring_timer*/,
                     const ACE_Time_Value & /*cur_time*/,
                     const void *& /*upcall_act*/);

      /// This method is called when the timer expires.
      int timeout (TimerQueue & /*timer_queue*/,
                   TT_QEntry /*timer*/,
                   const void * /*arg*/,
                   int /*recurring_timer*/,
                   const ACE_Time_Value & /*cur_time*/);

      /// This method is called after the timer expires.
      int postinvoke (TimerQueue & /*timer_queue*/,
                      TT_QEntry /*timer*/,
                      const void * /*arg*/,
                      int /*recurring_timer*/,
                      const ACE_Time_Value & /*cur_time*/,
                      const void * /*upcall_act*/);

      /// This method is called when a handler is cancelled
      int cancel_type (TimerQueue & /*timer_queue*/,
                       TT_QEntry /*timer*/,
                       int /*dont_call*/,
                       int & /*requires_reference_counting*/);

      /// This method is called when a timer is cancelled
      int cancel_timer (TimerQueue & /*timer_queue*/,
                        TT_QEntry /*timer*/,
                        int /*dont_call*/,
                        int /*requires_reference_counting*/);

      /// This method is called when the timer queue is destroyed and
      /// the timer is still contained in it
      int deletion (TimerQueue &timer_queue,
                    TT_QEntry timer,
                    const void * /*arg*/);

      int wait_for_event (const ACE_Time_Value& timeout);

      void shutdown ();

    private:
      TTC_Task_Timer_Upcall (const TTC_Task_Timer_Upcall&) = delete;
      TTC_Task_Timer_Upcall (TTC_Task_Timer_Upcall&&) = delete;
      TTC_Task_Timer_Upcall& operator= (const TTC_Task_Timer_Upcall&) = delete;
      TTC_Task_Timer_Upcall& operator= (TTC_Task_Timer_Upcall&&) = delete;

      ACE_Auto_Event_T<EXF_TIME_POLICY> timer_;
    };

    int svc () override;
  private:
    TimerMonitor (const TimerMonitor&) = delete;
    TimerMonitor (TimerMonitor&&) = delete;
    TimerMonitor& operator= (const TimerMonitor&) = delete;
    TimerMonitor& operator= (TimerMonitor&&) = delete;

    typedef ACE_Timer_Wheel_T<TT_QEntry,
                              TTC_Task_Timer_Upcall,
                              ACE_SYNCH_RECURSIVE_MUTEX,
                              EXF_TIME_POLICY> TimerQueue;

    std::unique_ptr<TimerQueue> timer_q_ {};
    TTC_Task_Timer_Upcall tm_upcall_;
    bool activated_ {};
    bool shutdown_ {};
    bool deactivated_ {};
  };
}

#endif /* CIAOX11_TIMER_QUEUE_IMPL_H */
