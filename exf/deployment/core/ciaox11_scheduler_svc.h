/**
 * @file   ciaox11_scheduler_svc.h
 * @author Martin Corino
 *
 * @brief Public interface for an AXCIOMA scheduler service.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_SCHEDULER_SVC_H
#define CIAOX11_EXF_SCHEDULER_SVC_H

#include "ace/Service_Object.h"
#include "exf/deployment/core/ciaox11_schedule.h"

namespace CIAOX11
{
  namespace ExF
  {

    /**
     * @class SchedulerSvc
     *
     * @brief A class to dynamically load a Scheduler implementation.
     *
     */
    class CIAOX11_EXF_CORE_Export SchedulerSvc
      : public ACE_Service_Object
    {
    public:
      /// The destructor
      ~SchedulerSvc () override;

      /**
       * Create and return the reference to a monitor instance.
       * This method cannot throw any exception, but it can return a nil
       * reference to indicate an error condition.
       */
      virtual std::shared_ptr<Scheduler> create_scheduler (
          const Components::ConfigValues& cfg) = 0;
    };


  } /* ExF */
} /* CIAOX11 */

#endif /* CIAOX11_EXF_SCHEDULER_SVC_H */
