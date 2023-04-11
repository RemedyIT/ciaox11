/**
 * @file   ciaox11_timer_queue_i.cpp
 * @author Marijke Hengstmengel
 *
 * @brief AXCIOMA timer queue implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11_timer_queue_i.h"

#include "ciaox11/logger/log.h"

// X11_FUZZ: disable check_new_delete

namespace CIAOX11_TT_TimedTrigger_Impl
{
  class TimedTrigger_Executor final
    : public ExF::Executor
  {
  public:
    TimedTrigger_Executor (
         std::string event_id,
         IDL::traits<tt_timer_i>::ref_type timer,
         const ::CCM_TT::TT_Duration& delta_time,
         uint32_t round)
       : CIAOX11::ExF::Executor (std::move(timer->exf_settings())),
         event_id_ (std::move (event_id))
       , timer_(std::move (timer))
       , delta_time_(std::move (delta_time))
       , round_(std::move (round))
    {
    }

    void
    execute () noexcept(true) override
    {
    }

    void
    finish () noexcept(true) override
    {
      CIAOX11_LOG_INFO ("TimedTrigger_Executor::finish");

      try
      {
        this->timer_->tt_handler()->on_trigger(this->timer_, this->delta_time_, this->round_);
      }
      catch (const CORBA::Exception& ex)
      {
        CIAOX11_LOG_ERROR ("TimedTrigger_Executor::finish caught exception: " << ex.what());
      }
      catch (...)
      {
        CIAOX11_LOG_ERROR ("TimedTrigger_Executor::finish caught C++ exception.");
      }
    }

    void
    cancel (CIAOX11::ExF::CancellationType ctyp) noexcept(true) override
    {
      CIAOX11_LOG_INFO ("TimedTrigger_Executor::cancel received " <<
                        (ctyp == CIAOX11::ExF::CancellationType::CT_SHUTDOWN ?
                            "CT_SHUTDOWN" : "CT_TIMEOUT") <<
                        " for timer " << this->timer_->id ()  <<
                        " for round " << this->round_);
    }

    const std::string& event_id () const noexcept(true) override
    { return event_id_; }

  private:
    TimedTrigger_Executor () = delete;
    TimedTrigger_Executor (const TimedTrigger_Executor&) = delete;
    TimedTrigger_Executor (TimedTrigger_Executor&&) = delete;
    TimedTrigger_Executor& operator= (const TimedTrigger_Executor&) = delete;
    TimedTrigger_Executor& operator= (TimedTrigger_Executor&&) = delete;

    std::string const event_id_;
    IDL::traits< tt_timer_i>::ref_type timer_;
    ::CCM_TT::TT_Duration const delta_time_;
    uint32_t const round_;
  };

  tt_timer_i::~tt_timer_i ()
  {
    CIAOX11_LOG_INFO ("tt_timer_i::~tt_timer_i[" << this->id () << "]");
  }

  void
  tt_timer_i::set_id_ ()
  {
    std::ostringstream os;
    os << std::hex << this;
    this->id_ = os.str ();
  }

  void
  tt_timer_i::on_timer (const CCM_TT::TT_Duration& delta_time) noexcept
  {
    CIAOX11_LOG_INFO ("tt_timer_i::on_timer[" << this->id () << "]");

    try
    {
      // unless we're already finished
      if (!this->finished_.load ())
      {
        // atomically get last iteration count
        uint32_t const last_round = this->rounds_.load ();
        uint32_t const new_round = last_round + 1; // next iteration to be
        // if it looks like this is going to be the last round
        // attempt to set the finish flag
        bool not_finished = true;
        if (this->max_rounds_ > 0 && new_round == this->max_rounds_)
        {
          // if we managed to be first to set the finish flag (meaning the old
          // value was still 'false') we're not finished yet
          not_finished = !this->finished_.exchange (true);
        }

        if (not_finished)
        {
          // check check if schdeuler still active; if not we do *not* fire anymore
          if (this->monitor_.deactivated ())
          {
            CIAOX11_LOG_INFO ("tt_timer_i::on_timer" <<
                               " - timer[" << this->id () <<
                               "] ignoring timer because of scheduler deactivation");
            return;
          }

          // in case of a non-recurring timer there is no possibility of (or need for)
          // timer cancellation after this point so mark the timer cancelled
          if (!this->recurring_)
          {
            this->cancelled_.store (true);
          }

          this->rounds_.store (new_round); // update iteration count

          try
          {
            // Push the on_trigger into the EXF, i.o calling direct the on_trigger
            CIAOX11::ExF::Executor::ref_type exec =
                    std::make_unique<TimedTrigger_Executor> (
                        "on_trigger",
                        IDL::traits<tt_timer_i>::narrow (this->_lock ()),
                        delta_time,
                        new_round);

            this->scheduling_lane_->submit (std::move (exec));
          }
          catch (const std::bad_alloc&)
          {
            CIAOX11_LOG_ERROR ("tt_timer_i::on_timer" <<
                               " - timer[" << this->id () <<
                               "] no memory");
            return;
          }

          // if we reached max (if any) now -> cancel the timer
          // unless it was a non-recurring trigger, in that case the queue
          // has cancelled itself.
          if (this->recurring_ && this->max_rounds_ > 0 && new_round == this->max_rounds_)
          {
            CIAOX11_LOG_INFO ("tt_timer_i::on_timer" <<
                              " - timer[" << this->id () <<
                              "] cancelling for maximum nr of rounds reached : " << this->max_rounds_);
            this->cancel ();
          }
        }
      }
    }
    catch (const std::exception& ex)
    {
      CIAOX11_LOG_ERROR ("tt_timer_i::on_timer" <<
                         " - timer[" << this->id () <<
                         "] caught exception : " << ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("tt_timer_i::on_timer" <<
                         " - timer[" << this->id () <<
                         "] caught unexpected C++ exception");
    }
  }

  void
  tt_timer_i::cancel ()
  {
    bool const cancelled = this->cancelled_.exchange (true);
    if (cancelled)
      return; // already cancelled/cancelling

    IDL::traits< tt_timer_i>::ref_type tmref = IDL::traits<tt_timer_i>::narrow (this->_lock ());
    TimerMonitor::TT_QEntry ttqe (std::move(tmref));
    if (this->monitor_.stop_monitoring (ttqe))
    {
      CIAOX11_LOG_DEBUG ("tt_timer_i::cancel" <<
                         " - timer[" << this->id () << "] cancelled");
    }
  }

  bool
  tt_timer_i::is_canceled ()
  {
    return this->cancelled_.load ();
  }

  uint32_t
  tt_timer_i::rounds ()
  {
    return this->rounds_;
  }

  std::string
  tt_timer_i::id ()
  {
    return this->id_;
  }

  /// This method is called when a timer is registered.
  int
  TimerMonitor::TTC_Task_Timer_Upcall::registration (
      TimerQueue & /*timer_queue*/,
      TimerMonitor::TT_QEntry /*timer*/,
      const void * /*arg*/)
  {
    CIAOX11_LOG_INFO ("TTC_Task_Timer_Upcall::registration ");
    // wakeup timer thread
    this->timer_.signal ();
    return 0;
  }

  /// This method is called before the timer expires.
  int
  TimerMonitor::TTC_Task_Timer_Upcall::preinvoke (
      TimerQueue & /*timer_queue*/,
      TimerMonitor::TT_QEntry /*timer*/,
      const void * /*arg*/,
      int /*recurring_timer*/,
      const ACE_Time_Value & /*cur_time*/,
      const void *& /*upcall_act*/)
  {
    return 0;
  }

  /// This method is called when the timer expires.
  int
  TimerMonitor::TTC_Task_Timer_Upcall::timeout (
      TimerQueue & /*timer_queue*/,
      TimerMonitor::TT_QEntry timer,
      const void * /*arg*/,
      int /*recurring_timer*/,
      const ACE_Time_Value & cur_time)
  {
    ACE_TCHAR tss[27];
    CIAOX11_LOG_INFO ("TTC_Task_Timer_Upcall::timeout - "
                     "timer[" <<
                       timer.tt_timer_->id () <<
                      "] expired @ " <<
                      ACE_TEXT_ALWAYS_CHAR (
                          ACE::timestamp (
                              cur_time,
                              tss,
                              sizeof(tss) / sizeof(ACE_TCHAR),
                              true)));
    // submit task execution
    timespec_t const ts = (timespec)((cur_time) - timer.tt_timer_->start_time ());
    timer.tt_timer_->on_timer (CCM_TT::TT_Duration (ACE_Utils::truncate_cast<uint32_t> (ts.tv_sec),
                                                    ACE_Utils::truncate_cast<uint32_t> (ts.tv_nsec)));
    return 0;
  }

  /// This method is called after the timer expires.
  int
  TimerMonitor::TTC_Task_Timer_Upcall::postinvoke (
      TimerQueue & /*timer_queue*/,
      TimerMonitor::TT_QEntry /* timer */,
      const void * /*arg*/,
      int /* recurring_timer */,
      const ACE_Time_Value & /*cur_time*/,
      const void * /*upcall_act*/)
  {
    return 0;
  }

  /// This method is called when a handler is cancelled
  int
  TimerMonitor::TTC_Task_Timer_Upcall::cancel_type (
      TimerQueue & /*timer_queue*/,
      TimerMonitor::TT_QEntry /*timer*/,
      int /*dont_call*/,
      int & /*requires_reference_counting*/)
  {
    return 0;
  }

  /// This method is called when a timer is cancelled
  int
  TimerMonitor::TTC_Task_Timer_Upcall::cancel_timer (
      TimerQueue & /*timer_queue*/,
      TimerMonitor::TT_QEntry timer,
      int /*dont_call*/,
      int /*requires_reference_counting*/)
  {
    CIAOX11_LOG_INFO ("TTC_Task_Timer_Upcall::cancel_timer - "
                           "timer[" << timer.tt_timer_->id () << "]");
    return 0;
  }

  /// This method is called when the timer queue is destroyed and
  /// the timer is still contained in it
  int
  TimerMonitor::TTC_Task_Timer_Upcall::deletion (
      TimerQueue &timer_queue,
      TimerMonitor::TT_QEntry timer,
      const void * /*arg*/)
  {
    int requires_reference_counting = 0;

    this->cancel_type (timer_queue,
                       timer,
                       0,
                       requires_reference_counting);

    this->cancel_timer (timer_queue,
                        timer,
                        0,
                        requires_reference_counting);
    return 0;
  }

  int
  TimerMonitor::TTC_Task_Timer_Upcall::wait_for_event (
      const ACE_Time_Value& timeout)
  {
    ACE_Time_Value_T<EXF_TIME_POLICY> wait_time (timeout);

    return this->timer_.wait (std::addressof(wait_time), 0);
  }

  void
  TimerMonitor::TTC_Task_Timer_Upcall::shutdown ()
  {
    this->timer_.signal ();
  }

  TimerMonitor::TimerMonitor ()
  {
    CIAOX11_LOG_TRACE ("TimerMonitor::TimerMonitor");

    // defaults
    constexpr u_int spoke_count = ACE_DEFAULT_TIMER_WHEEL_SIZE;
    constexpr u_int resolution = ACE_DEFAULT_TIMER_WHEEL_RESOLUTION;
    constexpr size_t prealloc = 15;

    // create timer queue
    this->timer_q_ = std::make_unique<TimerQueue> (spoke_count,
                                                   resolution,
                                                   prealloc,
                                                   &this->tm_upcall_);

    CIAOX11_LOG_INFO ("TimerMonitor::TimerMonitor - "
                       "activating timer monitor thread");

    if (this->activate (THR_NEW_LWP | THR_JOINABLE) != 0)
    {
      CIAOX11_LOG_PANIC ("TimerMonitor::TimerMonitor - "
                         "failed to start timer monitor queue");
    }
    else
    {
      this->activated_ = true;
    }

    CIAOX11_LOG_TRACE ("TimerMonitor::TimerMonitor - finished");
  }

  TimerMonitor::~TimerMonitor ()
  {
    CIAOX11_LOG_TRACE ("TimerMonitor::~TimerMonitor");

    if (this->timer_q_)
    {
      if (this->activated_)
      {
        this->shutdown_ = true;
        this->tm_upcall_.shutdown ();

        this->wait ();
      }
    }

    CIAOX11_LOG_INFO ("TimerMonitor::~TimerMonitor - finished");
  }

  IDL::traits<::CCM_TT::TT_Timer>::ref_type
  TimerMonitor::start_monitoring (
      IDL::traits<::CCM_TT::TT_Handler>::ref_type trigger_handler,
      const ACE_Time_Value& delay,
      const ACE_Time_Value& interval,
      uint32_t max_rounds,
      IDL::traits<CIAOX11::ExF::SchedulingLane>::ref_type scheduling_lane,
      CIAOX11::ExF::Settings exf_settings)
  {
    CIAOX11_LOG_TRACE ("TimerMonitor::start_monitoring.");

    bool recurring_ = true;
    // If no interval time is set, we are not dealing with
    // a repeating timer, so set recurring to false.
    // This is needed for cancelling the timer later on.
    // (also for non-recurring timers max_count will be forced to 1)
    if (ACE_Time_Value::zero == interval)
    {
      recurring_ = false;
    }

    ACE_TCHAR ts[27];
    ACE_Time_Value const future_time =
        ACE_Time_Value_T<EXF_TIME_POLICY> (delay).to_absolute_time ();

    CIAOX11_LOG_INFO ("TimerMonitor::start_monitoring -"
                      " trigger_start " <<
                              ACE_TEXT_ALWAYS_CHAR (
                                ACE::timestamp (
                                  future_time,
                                  ts,
                                  sizeof(ts) / sizeof(ACE_TCHAR),
                                  true)) <<
                      " interval <" <<
                              interval.msec() << "> msec.");

    if (this->activated_)
    {
      // get current time according time policy
      ACE_Time_Value const start_time_ = this->timer_q_->gettimeofday_static ();

      CIAOX11_LOG_INFO ("TimerMonitor::start_monitoring -"
                                  " start_time " <<
                                  ACE_TEXT_ALWAYS_CHAR (
                                     ACE::timestamp (
                                       start_time_,
                                       ts,
                                       sizeof(ts) / sizeof(ACE_TCHAR),
                                       true)));
      // create timer object
      IDL::traits< tt_timer_i>::ref_type timer =
          CORBA::make_reference< tt_timer_i> (
              *this,
              std::move(trigger_handler),
              (recurring_ ? max_rounds : 1),
              start_time_,
              recurring_,
              std::move(scheduling_lane),
              std::move(exf_settings));

      TT_QEntry qe (timer);
      if (this->timer_q_->schedule (qe, 0, future_time,interval ) != -1)
      {
        CIAOX11_LOG_INFO ("TimerMonitor::start_monitoring - "
                          "timer[" << timer->id () << "] scheduled");
        return timer;
      }
      else
      {
        CIAOX11_LOG_ERROR ("TimerMonitor::start_monitoring - "
                           "failed to schedule timer[" <<
                           timer->id () << "]");
      }
    }
    else
    {
      CIAOX11_LOG_PANIC ("TimerMonitor::start_monitoring - "
                         "monitor not activated");
    }
    return {};
  }

  bool TimerMonitor::stop_monitoring (
      const TT_QEntry& ttqe)
  {
    CIAOX11_LOG_INFO ("TimerMonitor::stop_monitoring - "
                       "activated=" << this->activated_ <<
                       " timer[" << const_cast<TT_QEntry&> (ttqe).tt_timer_->id () << "]");

    if (this->activated_)
    {
      if (this->timer_q_->cancel (ttqe) > 0)
      {
        return true;
      }
      CIAOX11_LOG_INFO ("TimerMonitor::stop_monitoring - "
                        "failed to cancel timer[" <<
                        const_cast<TT_QEntry&> (ttqe).tt_timer_->id () << "]");
    }
    else
    {
      CIAOX11_LOG_PANIC ("TimerMonitor::stop_monitoring - "
                         "timer monitor not activated");
    }
    return false;
  }

  int TimerMonitor::svc ()
  {
    CIAOX11_LOG_TRACE ("TimerMonitor::svc");

    while (!this->shutdown_)
    {
      ACE_TCHAR ts[27];
      ACE_Time_Value max_wait { 60 };

      ACE_Time_Value* this_wait =
          this->timer_q_->calculate_timeout (std::addressof(max_wait));

      if (this_wait && (*this_wait != ACE_Time_Value::zero))
      {
        CIAOX11_LOG_INFO ("TimerMonitor::svc - "
                          "waiting for timer events for <" <<
                          this_wait->msec() << "> msec.");

        this->tm_upcall_.wait_for_event (*this_wait);
      }

      CIAOX11_LOG_INFO ("TimerMonitor::svc - " <<
                         "checking for timer expirations @ " <<
                         ACE_TEXT_ALWAYS_CHAR (
                             ACE::timestamp (
                                 (this->timer_q_->gettimeofday () + this->timer_q_->timer_skew ()),
                                 ts,
                                 sizeof(ts) / sizeof(ACE_TCHAR),
                                 true)));

      int const n = this->timer_q_->expire ();

      CIAOX11_LOG_INFO ("TimerMonitor::svc - "
                         << n << " timers expired");
    }

    CIAOX11_LOG_INFO ("TimerMonitor::svc - finished");

    return 0;
  }

  TimerMonitor::ref_type
  TimerMonitor::create_instance ()
  {
    ref_type tm = ref_type (new TimerMonitor ());
    return tm;
  }

}
