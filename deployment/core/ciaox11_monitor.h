/**
 * @file   ciaox11_monitor.h
 * @author Martin Corino
 *
 * @brief Public interface for the Axcioma deadline monitor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CIAOX11_EXF_MONITOR_H
#define CIAOX11_EXF_MONITOR_H

#include "exf/deployment/core/ciaox11_task.h"

namespace CIAOX11
{
  namespace ExF
  {
    // uint32_t value; size of deadline timer queue
    const std::string DEADLINE_MONITOR_QUEUE_SIZE = "nl.remedy.it.Axcioma.ExF.Monitor.Queue.Size";
    // uint32_t value; resolution of deadline timer queue
    const std::string DEADLINE_MONITOR_QUEUE_RESOLUTION = "nl.remedy.it.Axcioma.ExF.Monitor.Queue.Resolution";
    // uint32_t value; preallocation of deadline timer queue
    const std::string DEADLINE_MONITOR_QUEUE_PREALLOC = "nl.remedy.it.Axcioma.ExF.Monitor.Queue.PreAlloc";

    /**
     * @class DeadlineMonitor
     *
     * @brief A class implementing deadline monitoring for scheduled
     *        executor tasks.
     *
     */
    class CIAOX11_EXF_CORE_Export DeadlineMonitor
    {
    public:
      typedef std::shared_ptr<DeadlineMonitor>  ref_type;

      DeadlineMonitor () = default;
      virtual ~DeadlineMonitor ();

      /**
       * Start monitoring the deadline set for the executor task.
       * Only called for executors with deadline types != DLT_NONE.
       */
      virtual void start_monitoring (ExF::ExecutionTask::ref_type task) = 0;

      /**
       * Stop monitoring the deadline set for the executor task.
       * Called after an executor has finished executing.
       */
      virtual void stop_monitoring (const ExF::ExecutionTask::ref_type& task) = 0;

      /**
       * Create a scheduler instance.
       */
      static ref_type create_instance (const Components::ConfigValues&);

      static const std::string ServiceName;
    };

  } /* ExF */
} /* CIAOX11 */

#endif /* CIAOX11_EXF_MONITOR_H */
