/**
 * @file   ciaox11_exf_scheduler_svc_i.cpp
 * @author Martin Corino
 *
 * @brief AXCIOMA execution scheduler implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "exf/deployment/scheduler/ciaox11_exf_scheduler_svc_i.h"

#include "ace/Service_Config.h"
#include "exf/deployment/logger/log.h"
#include "exf/deployment/scheduler/ciaox11_exf_scheduler_i.h"

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      ACE_STATIC_SVC_DEFINE (SchedulerSvc,
                             ACE_TEXT ("CIAOX11_ExF_Scheduler_Svc"),
                             ACE_SVC_OBJ_T,
                             &ACE_SVC_NAME (SchedulerSvc),
                             ACE_Service_Type::DELETE_THIS
                              | ACE_Service_Type::DELETE_OBJ,
                             0)
      ACE_FACTORY_DEFINE (CIAOX11_EXF_SCHEDULER, SchedulerSvc)

      std::shared_ptr<ExF::Scheduler> SchedulerSvc::create_scheduler (
          const Components::ConfigValues& cfg)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::SchedulerSvc::create_scheduler - ");

        try
        {
          return std::make_shared<ExF::Impl::Scheduler> (cfg);
        }
        catch (const std::bad_alloc&)
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::SchedulerSvc::create_scheduler - " <<
                                 "no memory");
        }
        return {};
      }

      int SchedulerSvc::Initializer ()
      {
        if (ACE_Service_Config::process_directive (ace_svc_desc_SchedulerSvc) == 0)
        {
          return 0;
        }
        return 1;
      }
    }
  }
}
