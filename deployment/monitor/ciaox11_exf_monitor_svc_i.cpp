/**
 * @file   ciaox11_exf_monitor_svc_i.cpp
 * @author Martin Corino
 *
 * @brief AXCIOMA deadline monitor implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "exf/deployment/monitor/ciaox11_exf_monitor_svc_i.h"

#include "ace/Service_Config.h"
#include "exf/deployment/logger/log.h"
#include "exf/deployment/monitor/ciaox11_exf_monitor_i.h"

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {

      ACE_STATIC_SVC_DEFINE (DeadlineMonitorSvc,
                             ACE_TEXT ("CIAOX11_ExF_DeadlineMonitor_Svc"),
                             ACE_SVC_OBJ_T,
                             &ACE_SVC_NAME (DeadlineMonitorSvc),
                             ACE_Service_Type::DELETE_THIS
                              | ACE_Service_Type::DELETE_OBJ,
                             0)
      ACE_FACTORY_DEFINE (CIAOX11_EXF_MONITOR, DeadlineMonitorSvc)

      std::shared_ptr<ExF::DeadlineMonitor> DeadlineMonitorSvc::create_monitor (
          const Components::ConfigValues& cfg)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DeadlineMonitorSvc::create_monitor");

        try
        {
          return std::make_shared<ExF::Impl::DeadlineMonitor> (cfg);
        }
        catch (const std::bad_alloc&)
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::DeadlineMonitorSvc::create_monitor - " <<
                                 "no memory");
        }
        return {};
      }

      int DeadlineMonitorSvc::Initializer ()
      {
        if (ACE_Service_Config::process_directive (ace_svc_desc_DeadlineMonitorSvc) == 0)
        {
          return 0;
        }
        return 1;
      }
    }
  }
}
