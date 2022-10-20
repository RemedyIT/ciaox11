/**
 * @file   ciaox11_task.h
 * @author Martin Corino
 *
 * @brief Internal task interface.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CIAOX11_EXF_DISPATCH_H
#define CIAOX11_EXF_DISPATCH_H

#include "exf/deployment/core/ciaox11_schedule.h"

namespace CIAOX11
{
  namespace ExF
  {

    /**
     * @class ExecutionTask
     *
     * @brief A class managing an executor submitted to
     *        a scheduling lane.
     *
     */
    class CIAOX11_EXF_CORE_Export ExecutionTask
    {
    public:
      typedef std::shared_ptr<ExecutionTask> ref_type;

      virtual ~ExecutionTask ();

      /**
       * Mark the executor as expired.
       * Cancels running operations for hard deadlines.
       * This method should never throw exceptions.
       */
      virtual void expire () noexcept(true) = 0;

      /**
       * Returns the id of component instance that dispatched this task.
       * This method should never throw an exception.
       */
      virtual const std::string& instance_id () const noexcept(true) = 0;

      /**
       * Returns the id of the event handled by this executor.
       * This method should never throw an exception.
       */
      virtual const std::string& event_id () const noexcept(true) = 0;

      /**
       * Returns task deadline with time value converted to absolute time.
       */
      virtual const ExF::Deadline& deadline () const noexcept(true) = 0;
    };

  } /* ExF */
} /* CIAOX11 */

#endif /* CIAOX11_EXF_DISPATCH_H */
