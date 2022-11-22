/**
 * @file   ciaox11_exf_monitor_svc_i.h
 * @author Martin Corino
 *
 * @brief AXCIOMA deadline monitor implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_MONITOR_SVC_IMPL_H
#define CIAOX11_EXF_MONITOR_SVC_IMPL_H

#pragma once

#include "exf/deployment/core/ciaox11_monitor_svc.h"
#include "exf/deployment/monitor/ciaox11_exf_monitor_export.h"

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class CIAOX11_EXF_MONITOR_Export DeadlineMonitorSvc
        : public ExF::DeadlineMonitorSvc
      {
      public:
        /// The destructor
        ~DeadlineMonitorSvc () override = default;

        std::shared_ptr<ExF::DeadlineMonitor> create_monitor (
          const Components::ConfigValues&) override;

        static int Initializer ();
      };

      static int CIAOX11_Requires_EXF_DeadlineMonitor_Svc_Initializer =
          DeadlineMonitorSvc::Initializer ();

      ACE_STATIC_SVC_DECLARE (DeadlineMonitorSvc)
      ACE_FACTORY_DECLARE (CIAOX11_EXF_MONITOR, DeadlineMonitorSvc)
    }
  }
}

#endif /* CIAOX11_EXF_MONITOR_SVC_IMPL_H */
