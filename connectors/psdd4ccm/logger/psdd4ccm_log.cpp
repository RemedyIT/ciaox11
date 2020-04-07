/**
 * @file    psdd4ccm_log.cpp
 * @author  Martin Corino
 *
 * @brief   PSDD4CCM for X11 log module.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "psdd4ccm/logger/psdd4ccm_log.h"

namespace CIAOX11
{
  namespace PSDD4CCM
  {
#if !defined(X11_NLOGGING)
    namespace psdd4ccm_logger
    {
      PSDD4CCM_Log_Module* PSDD4CCM_Log_Module::getInstance()
      {
        static PSDD4CCM_Log_Module instance_;

        return &instance_;
      }

      PSDD4CCM_Test_Log_Module* PSDD4CCM_Test_Log_Module::getInstance()
      {
        static PSDD4CCM_Test_Log_Module instance_;

        return &instance_;
      }

      PSDD4CCM_Log_Module::PSDD4CCM_Log_Module ()
        : x11_logger::Log_Module ("PSDD4CCMX11")
      {
      }

      /**
       * Log_Module, specific for the test framework.
       */
      PSDD4CCM_Test_Log_Module::PSDD4CCM_Test_Log_Module ()
        : x11_logger::Log_Module ("PSDD4CCM_TEST",
                                  x11_logger::X11_LogMask::LP_ALL,
                                  x11_logger::X11_Verbose::V_PRIO|
                                  x11_logger::X11_Verbose::V_TIME)
      {
      }
    }; /* psdd4ccm_logger */
  } /* PSDD4CCM */
#endif /* !defined(X11_NLOGGING) */
}; /* CIAOX11 */
