/**
 * @file   ciaox11_exf_scheduler_svc_i.h
 * @author Martin Corino
 *
 * @brief AXCIOMA execution scheduler implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_SCHEDULER_SVC_IMPL_H
#define CIAOX11_EXF_SCHEDULER_SVC_IMPL_H

#pragma once

#include "exf/deployment/core/ciaox11_scheduler_svc.h"
#include "exf/deployment/scheduler/ciaox11_exf_scheduler_export.h"

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class CIAOX11_EXF_SCHEDULER_Export SchedulerSvc
        : public ExF::SchedulerSvc
      {
      public:
        /// The destructor
        ~SchedulerSvc () override = default;

        std::shared_ptr<ExF::Scheduler> create_scheduler (
            const Components::ConfigValues& cfg) override;

        static int Initializer ();
      };

      static int CIAOX11_Requires_EXF_Scheduler_Svc_Initializer =
          SchedulerSvc::Initializer ();

      ACE_STATIC_SVC_DECLARE (SchedulerSvc)
      ACE_FACTORY_DECLARE (CIAOX11_EXF_SCHEDULER, SchedulerSvc)
    }
  }
}

#endif /* CIAOX11_EXF_SCHEDULER_SVC_IMPL_H */
