/**
 * @file   ciaox11_schedule.cpp
 * @author Martin Corino
 *
 * @brief Public interfaces for the AXCIOMA execution framework.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/core/ciaox11_schedule.h"

#include "ace/Dynamic_Service.h"
#include "exf/deployment/core/ciaox11_scheduler_svc.h"
#include "exf/deployment/logger/log.h"

namespace CIAOX11
{
  namespace ExF
  {

    Executor::~Executor () {}

    SchedulingLane::~SchedulingLane () {}

    Scheduler::~Scheduler () {}

    const std::string Scheduler::ServiceName { "CIAOX11_ExF_Scheduler_Svc" };

    Scheduler::ref_type Scheduler::create_instance (
        const Components::ConfigValues& cfg)
    {
      SchedulerSvc *dms {};
      try
      {
        CIAOX11_EXF_LOG_DEBUG ( "ExF::Scheduler::create_instance - " \
              "Resolving scheduler service <"
              << Scheduler::ServiceName << ">");
        dms =
          ACE_Dynamic_Service<SchedulerSvc>::instance (Scheduler::ServiceName.c_str ());
      }
      catch (...)
      {
        CIAOX11_EXF_LOG_ERROR ("ExF::Scheduler::create_instance - " \
                 "Unknown exception caught while resolving the "
              << "scheduler service <" << Scheduler::ServiceName << ">");
      }

      std::shared_ptr<Scheduler> dm = {};
      if (dms)
      {
        CIAOX11_EXF_LOG_DEBUG ( "ExF::Scheduler::create_instance - " \
              "Creating scheduler");

        dm = dms->create_scheduler (cfg);
        if (dm)
        {
          CIAOX11_EXF_LOG_DEBUG ( "ExF::Scheduler::create_instance - " \
                "Created scheduler instance");
        }
        else
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Scheduler::create_instance - " \
                   "Scheduler service <" << Scheduler::ServiceName
                   << "> failed to create scheduler.");
        }
      }
      else
      {
        CIAOX11_EXF_LOG_ERROR ("ExF::Scheduler::create_instance - " \
                 "No Scheduler service <" << Scheduler::ServiceName
                 << "> loaded.");
      }

      return dm;
    }

  }
}
