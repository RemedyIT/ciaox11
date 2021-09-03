/**
 * @file    ciaox11_timed_trigger_exec.cpp
 * @author  Martin Corino
 *
 * @brief   CIAOX11 Timed Trigger connector executors
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : ciaox11_timed_trigger_impl.cpp[Header]

#include "ciaox11_timed_trigger_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[user_includes]
#include "ciaox11/logger/log.h"
#include "ace/Truncate.h"
#include "ace/Abstract_Timer_Queue.h"
#include "ace/Timer_Queue_Iterator.h"
#include "ace/Reactor.h"

#include <atomic>
#include <sstream>
//@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[user_global_impl]

namespace CIAOX11_TT_TimedTrigger_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : tt_scheduler_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[ctor]
  tt_scheduler_exec_i::tt_scheduler_exec_i (
    IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger_Context>::ref_type context)
    : context_ (std::move (context))
  {
    CIAOX11_LOG_DEBUG ("tt_scheduler_exec_i::tt_scheduler_exec_i using orb reactor.");
    // resolve ORB service object
    this->orb_ = IDL::traits<CORBA::ORB>::narrow (
                    this->context_->the_service_registry ()->resolve_service(CIAOX11::SVCID_ORB));
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[ctor]

  tt_scheduler_exec_i::~tt_scheduler_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_public_ops]
  bool
  tt_scheduler_exec_i::schedule_timer (
      ACE_Event_Handler* tevh,
      const ACE_Time_Value& delay,
      const ACE_Time_Value& interval) noexcept
  {
    try
    {
      long const timer_id = this->orb_->reactor ()->schedule_timer (tevh, 0, delay, interval);
      if (timer_id != -1)
      {
        return true;
      }

      CIAOX11_LOG_ERROR ("tt_scheduler_exec_i::schedule_timer - " <<
                         "failed to schedule timer");
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("tt_scheduler_exec_i::schedule_timer - " <<
                         "caught unexpected C++ exception");
    }
    return false;
  }

  bool
  tt_scheduler_exec_i::cancel_timer (ACE_Event_Handler* tevh) noexcept
  {
    try
    {
      int const rc = this->orb_->reactor ()->cancel_timer (tevh);
      if (rc < 0)
      {
        CIAOX11_LOG_WARNING ("tt_scheduler_exec_i::cancel_timer - " <<
                           "failed to cancel timer [" << std::hex << tevh << "]");
      }
      else
      {
        if (rc == 0)
        {
          CIAOX11_LOG_INFO ("tt_scheduler_exec_i::cancel_timer - " <<
                            "unable to find timer [" << std::hex << tevh <<
                            "]; assumed canceled");
        }

        return true;
      }
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("tt_scheduler_exec_i::cancel_timer - " <<
                         "caught unexpected C++ exception cancelling timer [" <<
                         std::hex << tevh << "]");
    }
    return false;
  }


  ACE_Time_Value
  tt_scheduler_exec_i::get_timeofday () noexcept
  {
    return this->orb_->reactor ()->timer_queue ()->gettimeofday ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i[user_private_ops]


  /** Operations and attributes from tt_scheduler */

  IDL::traits< ::CCM_TT::TT_Timer>::ref_type
  tt_scheduler_exec_i::schedule_trigger (
      IDL::traits< ::CCM_TT::TT_Handler>::ref_type trigger_handler,
      const ::CCM_TT::TT_Duration& trigger_delay)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i::schedule_trigger[_trigger_handler_trigger_delay]
    CIAOX11_CALL_TRACE ("tt_scheduler_exec_i::schedule_trigger");

    // schedule as trigger with zero interval and max 1 rounds
    return this->schedule_repeated_trigger (
        trigger_handler,
        trigger_delay,
        CCM_TT::TT_Duration (),
        1);
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i::schedule_trigger[_trigger_handler_trigger_delay]
  }

  IDL::traits< ::CCM_TT::TT_Timer>::ref_type
  tt_scheduler_exec_i::schedule_repeated_trigger (
      IDL::traits< ::CCM_TT::TT_Handler>::ref_type trigger_handler,
      const ::CCM_TT::TT_Duration& start_delay,
      const ::CCM_TT::TT_Duration& interval,
      uint32_t max_rounds)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i::schedule_repeated_trigger[_trigger_handler_start_delay_interval_max_rounds]
    CIAOX11_CALL_TRACE ("tt_scheduler_exec_i::schedule_repeated_trigger");

    // create timer object
    bool const recurring = (interval.sec() > 0 || interval.nanosec () > 0);
    IDL::traits< tt_timer_i>::ref_type timer =
        CORBA::make_reference< tt_timer_i> (
            IDL::traits<tt_scheduler_exec_i>::narrow (this->_this ()),
            trigger_handler,
            (recurring ? max_rounds : 1),
            recurring);

    // create ACE event handler wrapper
    ACE_Event_Handler_var evh =
        ACE::make_event_handler<tt_event_handler> (timer,
                                                   this->get_timeofday ());

    // schedule timer
    timespec_t const ts_delay {
      ACE_Utils::truncate_cast<time_t> (start_delay.sec ()),
      ACE_Utils::truncate_cast<long> (start_delay.nanosec ())
    };
    timespec_t const ts_interval {
      ACE_Utils::truncate_cast<time_t> (interval.sec ()),
      ACE_Utils::truncate_cast<long> (interval.nanosec ())
    };

    if (this->schedule_timer (evh.handler (),
                              ACE_Time_Value(ts_delay),
                              ACE_Time_Value (ts_interval)))
    {
      CIAOX11_LOG_DEBUG ("tt_scheduler_exec_i::schedule_repeated_trigger" <<
                         " - timer[" << timer->id () << "] scheduled");

      return timer;
    }

    CIAOX11_LOG_ERROR ("tt_scheduler_exec_i::schedule_repeated_trigger" <<
                       " - failed to schedule timer");

    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::tt_scheduler_exec_i::schedule_repeated_trigger[_trigger_handler_start_delay_interval_max_rounds]
  }

  /**
   * Component Executor Implementation Class : TimedTrigger_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ctor]
  TimedTrigger_exec_i::TimedTrigger_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ctor]

  TimedTrigger_exec_i::~TimedTrigger_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[dtor]
  }


  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[user_private_ops]



  /** Session component operations */
  void TimedTrigger_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[configuration_complete]
  }

  void TimedTrigger_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ccm_activate]
  }

  void TimedTrigger_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ccm_passivate]
    if (this->tt_scheduler_)
    {
      IDL::traits<tt_scheduler_exec_i>::narrow (this->tt_scheduler_)->deactivate ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ccm_passivate]
  }

  void TimedTrigger_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[ccm_remove]
  }


  IDL::traits< ::CCM_TT::CCM_TT_Scheduler>::ref_type
  TimedTrigger_exec_i::get_tt_scheduler ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[get_tt_scheduler]
    if (!this->tt_scheduler_)
    {
      this->tt_scheduler_ = CORBA::make_reference <tt_scheduler_exec_i> (this->context_);
    }
    return this->tt_scheduler_;
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[get_tt_scheduler]
  }


  /// Operations from Components::SessionComponent
  void
  TimedTrigger_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[set_session_context]
    this->context_ = IDL::traits< ::CIAOX11_TT::CCM_TimedTrigger_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl::TimedTrigger_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[user_namespace_end_impl]
  void
  tt_timer_i::set_ev_handler (ACE_Event_Handler* evh)
  {
    this->ev_handler_.store (evh);
    std::ostringstream os;
    os << std::hex << evh;
    this->id_ = os.str ();
  }

  void
  tt_timer_i::on_timer (const CCM_TT::TT_Duration& delta_time) noexcept
  {
    CIAOX11_CALL_TRACE ("tt_timer_i::on_timer");

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
          if (this->scheduler_->deactivated ())
          {
            CIAOX11_LOG_DEBUG ("tt_timer_i::on_timer" <<
                               " - timer[" << this->id_ <<
                               "] ignoring timer because of scheduler deactivation");
            return;
          }

          // in case of a non-recurring timer there is no possibility of (or need for)
          // cancellation after this point so reset the handler reference
          if (!this->recurring_)
          {
            this->ev_handler_.store (nullptr);
          }

          this->rounds_.store (new_round); // update iteration count
          // execute trigger callback
          this->tt_handler_->on_trigger (this->_this (), delta_time, new_round);
          // if this is a recurring timer (interval > 0) and we reached max (if any) now
          //  -> cancel the timer
          if (this->recurring_ && this->max_rounds_ > 0 && new_round == this->max_rounds_)
          {
            CIAOX11_LOG_INFO ("tt_timer_i::on_timer" <<
                              " - timer[" << this->id_ <<
                              "] cancelling for maximum nr of rounds reached : " << this->max_rounds_);
            this->cancel ();
          }
        }
      }
    }
    catch (const ::CORBA::Exception &ex)
    {
      CIAOX11_LOG_ERROR ("tt_timer_i::on_timer" <<
                         " - timer[" << this->id_ <<
                         "] caught CORBA exception : " << ex);
    }
    catch (const std::exception& ex)
    {
      CIAOX11_LOG_ERROR ("tt_timer_i::on_timer" <<
                         " - timer[" << this->id_ <<
                         "] caught exception : " << ex);
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("tt_timer_i::on_timer" <<
                         " - timer[" << this->id_ <<
                         "] caught unexpected C++ exception");
    }
  }

  void
  tt_timer_i::cancel ()
  {
    CIAOX11_CALL_TRACE ("tt_timer_i::cancel");

    ACE_Event_Handler* evh = this->ev_handler_.exchange (nullptr);
    if (evh)
    {
      this->finished_.store (true); // prevent any waiting trigger to execute

      CIAOX11_LOG_DEBUG ("tt_timer_i::cancel" <<
                        " - timer[" << this->id_ << "]");

      if (this->scheduler_->cancel_timer (evh))
      {
        CIAOX11_LOG_DEBUG ("tt_timer_i::cancel" <<
                          " - timer[" << this->id_ << "] cancelled");
      }
    }
  }

  bool
  tt_timer_i::is_canceled ()
  {
    return this->ev_handler_.load () == nullptr;
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

  int
  tt_event_handler::handle_timeout (
      const ACE_Time_Value& curtime,
      const void*)
  {
    timespec_t const ts = (timespec)(curtime - this->start_time_);
    this->ccm_timer_->on_timer (
        CCM_TT::TT_Duration (ACE_Utils::truncate_cast<uint32_t> (ts.tv_sec),
                             ACE_Utils::truncate_cast<uint32_t> (ts.tv_nsec)));
    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[user_namespace_end_impl]

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CIAOX11_TT_TimedTrigger_Impl[factory]
  extern "C" void
  create_CIAOX11_TT_TimedTrigger_Impl (
    IDL::traits<Components::EnterpriseComponent>::ref_type& component)
  {
    component = CORBA::make_reference <TimedTrigger_exec_i> ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CIAOX11_TT_TimedTrigger_Impl[factory]

} // namespace CIAOX11_TT_TimedTrigger_Impl
//@@{__RIDL_REGEN_MARKER__} - BEGIN : ciaox11_timed_trigger_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
