/**
 * @file   ciaox11_exf_monitor_i.h
 * @author Martin Corino
 *
 * @brief AXCIOMA deadline monitor implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_MONITOR_IMPL_H
#define CIAOX11_EXF_MONITOR_IMPL_H

#pragma once

#include "exf/deployment/core/ciaox11_monitor.h"
#include "exf/deployment/monitor/ciaox11_exf_monitor_export.h"

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

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class ExF_Task_Timer_Upcall;

      class CIAOX11_EXF_MONITOR_Export DeadlineMonitor
        : public ExF::DeadlineMonitor,
          private ACE_Task_Base
      {
      public:
        DeadlineMonitor (const Components::ConfigValues& cfg);
        ~DeadlineMonitor () override;

        /**
         * Start monitoring the deadline set for the executor task.
         * Only called for executors with deadline types != DLT_NONE.
         */
        void start_monitoring (ExF::ExecutionTask::ref_type task) override;

        /**
         * Stop monitoring the deadline set for the executor task.
         * Called after an executor has finished executing.
         */
        void stop_monitoring (const ExF::ExecutionTask::ref_type& task) override;

      private:
        bool get_size (const Components::ConfigValue&, uint32_t&);

        int svc () override;

        using TimerQueue = ACE_Timer_Wheel_T<ExF::ExecutionTask::ref_type,
                                  ExF_Task_Timer_Upcall,
                                  ACE_SYNCH_RECURSIVE_MUTEX,
                                  EXF_TIME_POLICY>;

        TimerQueue& timer_q () { return *this->timer_q_; }

        TimerQueue* timer_q_;
        bool activated_ {};
        bool shutdown_ {};
      };
    }
  }
}

#endif /* CIAOX11_EXF_MONITOR_IMPL_H */
