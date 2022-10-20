/**
 * @file   ciaox11_monitor.cpp
 * @author Martin Corino
 *
 * @brief Public interface for the Axcioma deadline monitor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "exf/deployment/core/ciaox11_monitor.h"

#include "ace/Dynamic_Service.h"
#include "exf/deployment/core/ciaox11_monitor_svc.h"
#include "exf/deployment/logger/log.h"

namespace CIAOX11
{
  namespace ExF
  {
    ExecutionTask::~ExecutionTask () {}

    DeadlineMonitor::~DeadlineMonitor () {}

    const std::string DeadlineMonitor::ServiceName { "CIAOX11_ExF_DeadlineMonitor_Svc" };

    class NullMonitor : public DeadlineMonitor
    {
    public:
      NullMonitor () = default;

      void start_monitoring (ExF::ExecutionTask::ref_type /*task*/) override {}

      void stop_monitoring (const ExF::ExecutionTask::ref_type& /*task*/) override {}
    };

    DeadlineMonitor::ref_type DeadlineMonitor::create_instance (const Components::ConfigValues& cfg)
    {
      DeadlineMonitorSvc *dms {};
      try
      {
        CIAOX11_EXF_LOG_DEBUG ( "ExF::DeadlineMonitor::create_instance - " \
              "Resolving monitor service <"
              << DeadlineMonitor::ServiceName << ">");
        dms =
          ACE_Dynamic_Service<DeadlineMonitorSvc>::instance (DeadlineMonitor::ServiceName.c_str ());
      }
      catch (...)
      {
        CIAOX11_EXF_LOG_ERROR ("ExF::DeadlineMonitor::create_instance - " \
                 "Unknown exception caught while resolving the "
              << "monitor service <" << DeadlineMonitor::ServiceName << ">");
      }

      std::shared_ptr<DeadlineMonitor> dm = {};
      if (dms)
      {
        dm = dms->create_monitor (cfg);
        if (!dm)
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::DeadlineMonitor::create_instance - " \
                   "Monitor service <" << DeadlineMonitor::ServiceName
                   << "> failed to create deadline monitor. Fallback to NU" "LL monitor."); // string split to shut up fuzz
        }
      }
      else
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::DeadlineMonitor::create_instance - " \
                 "No monitor service <" << DeadlineMonitor::ServiceName
                 << "> loaded.");
      }

      if (!dm)
      {
        try
        {
          dm = std::make_shared<NullMonitor> ();
        }
        catch (const std::bad_alloc&)
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::DeadlineMonitor::create_instance - " \
                   "Monitor service <" << DeadlineMonitor::ServiceName
                   << "> failed to create fallback monitor. Caught std::bad_alloc.");
        }
      }
      return dm;
    }

  } /* ExF */
} /* CIAOX11 */
