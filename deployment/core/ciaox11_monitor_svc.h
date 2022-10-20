/**
 * @file   ciaox11_monitor_svc.h
 * @author Martin Corino
 *
 * @brief Public interface for an AXCIOMA deadline monitor service.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CIAOX11_EXF_MONITOR_SVC_H
#define CIAOX11_EXF_MONITOR_SVC_H

#include "ace/Service_Object.h"
#include "exf/deployment/core/ciaox11_monitor.h"

namespace CIAOX11
{
  namespace ExF
  {
    /**
     * @class DeadlineMonitorSvc
     *
     * @brief A class to dynamically load a DeadlineMonitor implementation.
     *
     */
    class CIAOX11_EXF_CORE_Export DeadlineMonitorSvc
      : public ACE_Service_Object
    {
    public:
      /// The destructor
      virtual ~DeadlineMonitorSvc ();

      /**
       * Create and return the reference to a monitor instance.
       * This method cannot throw any exception, but it can return a nil
       * reference to indicate an error condition.
       */
      virtual std::shared_ptr<DeadlineMonitor> create_monitor (const Components::ConfigValues&) = 0;
    };


  } /* ExF */
} /* CIAOX11 */

#endif /* CIAOX11_EXF_MONITOR_SVC_H */
