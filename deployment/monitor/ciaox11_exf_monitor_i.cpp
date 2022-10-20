/**
 * @file   ciaox11_exf_monitor_i.cpp
 * @author Martin Corino
 *
 * @brief AXCIOMA deadline monitor implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "exf/deployment/monitor/ciaox11_exf_monitor_i.h"

#include "ace/ACE.h"
#include "ace/Auto_Event.h"
#include "exf/deployment/logger/log.h"

// X11_FUZZ: disable check_new_delete

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class ExF_Task_Timer_Upcall
      {
      public:
        // = Initialization and termination methods.
        /// Constructor.
        ExF_Task_Timer_Upcall (void) = default;

        typedef ACE_Timer_Queue_T<ExF::ExecutionTask::ref_type,
                                  ExF_Task_Timer_Upcall,
                                  ACE_SYNCH_RECURSIVE_MUTEX,
                                  EXF_TIME_POLICY> TimerQueue;
        /// Destructor.
        ~ExF_Task_Timer_Upcall (void) = default;

        /// This method is called when a timer is registered.
        int registration (TimerQueue & /* timer_queue */,
                          ExF::ExecutionTask::ref_type task,
                          const void * /* arg */)
        {
          ACE_TCHAR ts[27];
          CIAOX11_EXF_LOG_INFO ("ExF::Impl::ExF_Task_Timer_Upcall::registration - "
                            "deadline registered for " <<
                            task->instance_id () << "::" << task->event_id () <<
                            " @ " <<
                            ACE_TEXT_ALWAYS_CHAR (
                                ACE::timestamp (
                                    task->deadline ().deadline_time_,
                                    ts,
                                    sizeof(ts) / sizeof(ACE_TCHAR),
                                    true)));
          // wakeup timer thread
          this->timer_.signal ();

          return 0;
        }

        /// This method is called before the timer expires.
        int preinvoke (TimerQueue &/*timer_queue*/,
                       ExF::ExecutionTask::ref_type /*task*/,
                       const void * /* arg */,
                       int /* recurring_timer */,
                       const ACE_Time_Value & /* cur_time */,
                       const void *& /* upcall_act */)
        {
          return 0;
        }

        /// This method is called when the timer expires.
        int timeout (TimerQueue &timer_queue,
                     ExF::ExecutionTask::ref_type task,
                     const void * /*arg*/,
                     int /*recurring_timer*/,
                     const ACE_Time_Value &cur_time)
        {
          ACE_TCHAR ts[27];
          CIAOX11_EXF_LOG_INFO ("ExF::Impl::ExF_Task_Timer_Upcall::timeout - "
                            "deadline expired for " <<
                            task->instance_id () << "::" << task->event_id () <<
                            " @ " <<
                            ACE_TEXT_ALWAYS_CHAR (
                                ACE::timestamp (
                                    cur_time,
                                    ts,
                                    sizeof(ts) / sizeof(ACE_TCHAR),
                                    true)));
          // signal task expiration
          task->expire ();
          // cancel the timer for this task
          timer_queue.cancel (task);

          return 0;
        }

        /// This method is called after the timer expires.
        int postinvoke (TimerQueue &/*timer_queue*/,
                        ExF::ExecutionTask::ref_type /*task*/,
                        const void * /* arg */,
                        int /* recurring_timer */,
                        const ACE_Time_Value & /* cur_time */,
                        const void * /* upcall_act */)
        {
          return 0;
        }

        /// This method is called when a handler is cancelled
        int cancel_type (TimerQueue & /* timer_queue */,
                         ExF::ExecutionTask::ref_type /* task */,
                         int /* dont_call */,
                         int & /* requires_reference_counting */)
        {
          return 0;
        }

        /// This method is called when a timer is cancelled
        int cancel_timer (TimerQueue & /* timer_queue */,
                          ExF::ExecutionTask::ref_type /* task */,
                          int /* dont_call */,
                          int /* requires_reference_counting */)
        {
          return 0;
        }

        /// This method is called when the timer queue is destroyed and
        /// the timer is still contained in it
        int deletion (TimerQueue &timer_queue,
                      ExF::ExecutionTask::ref_type task,
                      const void * /* arg */)
        {
          int requires_reference_counting = 0;

          this->cancel_type (timer_queue,
                             task,
                             0,
                             requires_reference_counting);

          this->cancel_timer (timer_queue,
                              task,
                              0,
                              requires_reference_counting);
          return 0;
        }

        static ExF_Task_Timer_Upcall instance_;

        int wait_for_event (const ACE_Time_Value& timeout)
        {
          ACE_Time_Value_T<EXF_TIME_POLICY> wait_time (timeout); // relative max. waiting time
          return this->timer_.wait (std::addressof(wait_time), 0);
        }

        void shutdown ()
        {
          this->timer_.signal ();
        }

      private:
        ACE_Auto_Event_T<EXF_TIME_POLICY> timer_;

        ExF_Task_Timer_Upcall (const ExF_Task_Timer_Upcall&) = delete;
        ExF_Task_Timer_Upcall (ExF_Task_Timer_Upcall&&) = delete;
        ExF_Task_Timer_Upcall& operator= (const ExF_Task_Timer_Upcall&) = delete;
        ExF_Task_Timer_Upcall& operator= (ExF_Task_Timer_Upcall&&) = delete;
      };

      ExF_Task_Timer_Upcall ExF_Task_Timer_Upcall::instance_ {};

      DeadlineMonitor::DeadlineMonitor (const Components::ConfigValues& cfg)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::DeadlineMonitor");

        // defaults
        u_int spoke_count = ACE_DEFAULT_TIMER_WHEEL_SIZE;
        u_int resolution = ACE_DEFAULT_TIMER_WHEEL_RESOLUTION;
        size_t prealloc = 15;

        // get config
        for (const Components::ConfigValue& cval : cfg)
        {
          uint32_t size {};

          if (cval.name () == ExF::DEADLINE_MONITOR_QUEUE_SIZE)
          {
            if (this->get_size (cval, size))
            {
              spoke_count = (u_int)size;
            }
          }
          else if (cval.name () == ExF::DEADLINE_MONITOR_QUEUE_RESOLUTION)
          {
            if (this->get_size (cval, size))
            {
              resolution = (u_int)size;
            }
          }
          else if (cval.name () == ExF::DEADLINE_MONITOR_QUEUE_PREALLOC)
          {
            if (this->get_size (cval, size))
            {
              prealloc = size;
            }
          }
        }

        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::DeadlineMonitor - "
                           "creating timer queue :"
                              " spoke_count=" << spoke_count <<
                              " resolution=" << resolution <<
                              " prealloc=" << prealloc);

        // create timer queue
        ACE_NEW_NORETURN(this->timer_q_,
                         TimerQueue (spoke_count,
                                     resolution,
                                     prealloc,
                                     &ExF_Task_Timer_Upcall::instance_));
        if (this->timer_q_)
        {
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::DeadlineMonitor - "
                             "activating deadline monitor thread");

          if (this->activate (THR_NEW_LWP | THR_JOINABLE) != 0)
          {
            CIAOX11_EXF_LOG_PANIC ("ExF::Impl::DeadlineMonitor::DeadlineMonitor - "
                               "failed to start deadline monitor queue");
          }
          else
          {
            this->activated_ = true;
          }
        }
        else
        {
          CIAOX11_EXF_LOG_PANIC ("ExF::Impl::DeadlineMonitor::DeadlineMonitor - "
                             "failed to allocate timer queue");
        }

        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::DeadlineMonitor - finished");
      }

      DeadlineMonitor::~DeadlineMonitor ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::~DeadlineMonitor");

        if (this->timer_q_)
        {
          if (this->activated_)
          {
            this->shutdown_ = true;
            this->timer_q_->upcall_functor ().shutdown ();

            this->wait ();
          }

          delete this->timer_q_;
          this->timer_q_ = nullptr;
        }

        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::~DeadlineMonitor - finished");
      }

      void DeadlineMonitor::start_monitoring (
          ExF::ExecutionTask::ref_type task)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::start_monitoring - "
                           "activated=" << this->activated_);

        if (this->activated_)
        {
          if (this->timer_q_->schedule (task, 0, task->deadline ().deadline_time_) == -1)
          {
            ACE_TCHAR ts[27];
            CIAOX11_EXF_LOG_ERROR ("ExF::Impl::DeadlineMonitor::start_monitoring - "
                               "failed to schedule deadline time for" <<
                               task->instance_id () << "::" << task->event_id () <<
                               " @ " <<
                               ACE_TEXT_ALWAYS_CHAR (
                                   ACE::timestamp (
                                       task->deadline ().deadline_time_,
                                       ts,
                                       sizeof(ts) / sizeof(ACE_TCHAR),
                                       true)));
          }
        }
        else
        {
          CIAOX11_EXF_LOG_PANIC ("ExF::Impl::DeadlineMonitor::start_monitoring - "
                             "deadline monitor not activated");
        }
      }

      void DeadlineMonitor::stop_monitoring (
          const ExF::ExecutionTask::ref_type& task)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::stop_monitoring - "
                           "activated=" << this->activated_);

        if (this->activated_)
        {
          if (this->timer_q_->cancel (task) < 1)
          {
            ACE_TCHAR ts[27];
            CIAOX11_EXF_LOG_INFO ("ExF::Impl::DeadlineMonitor::stop_monitoring - "
                              "no deadline timer canceled for" <<
                              task->instance_id () << "::" << task->event_id () <<
                              " @ " <<
                              ACE_TEXT_ALWAYS_CHAR (
                                  ACE::timestamp (
                                      task->deadline ().deadline_time_,
                                      ts,
                                      sizeof(ts) / sizeof(ACE_TCHAR),
                                      true)));
          }
        }
        else
        {
          CIAOX11_EXF_LOG_PANIC ("ExF::Impl::DeadlineMonitor::stop_monitoring - "
                             "deadline monitor not activated");
        }
      }

      int DeadlineMonitor::svc ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::svc");

        while (!this->shutdown_)
        {
          ACE_TCHAR ts[27];
          ACE_Time_Value max_wait { 60 };

          ACE_Time_Value this_wait =
              *this->timer_q_->calculate_timeout (std::addressof(max_wait));

          if (this_wait != ACE_Time_Value::zero)
          {
            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::svc - "
                              "waiting for timer events for " <<
                              ACE_TEXT_ALWAYS_CHAR (
                                  ACE::timestamp (
                                      this_wait,
                                      ts,
                                      sizeof(ts) / sizeof(ACE_TCHAR),
                                      true)));

            ExF_Task_Timer_Upcall::instance_.wait_for_event (this_wait);
          }

          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::svc - " <<
                             "checking for dealine expirations @ " <<
                             ACE_TEXT_ALWAYS_CHAR (
                                 ACE::timestamp (
                                     (this->timer_q_->gettimeofday () + this->timer_q_->timer_skew ()),
                                     ts,
                                     sizeof(ts) / sizeof(ACE_TCHAR),
                                     true)));

          int n = this->timer_q_->expire ();

          CIAOX11_EXF_LOG_INFO ("ExF::Impl::DeadlineMonitor::svc - "
                             << n << " deadlines expired");
        }

        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::svc - finished");

        return 0;
      }

      bool DeadlineMonitor::get_size (
          const Components::ConfigValue& cval,
          uint32_t& size)
      {
        uint32_t val;
        if (!(cval.value () >>= val))
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::DeadlineMonitor::get_size - "
                             "failed to extract value for "
                             << cval.name ());
          return false;
        }
        else
        {
          size = val;
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitor::get_size - "
                             << cval.name () << " size = " << size);
        }
        return true;
      }

    }
  }
}
