/**
 * @file    dds4ccm_log.cpp
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM for X11 log module.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
#if !defined(X11_NLOGGING)
    namespace dds4ccm_logger
    {
      DDS4CCM_Log_Module* DDS4CCM_Log_Module::getInstance()
      {
        static DDS4CCM_Log_Module instance_;

        return &instance_;
      }

      DDS4CCM_Test_Log_Module* DDS4CCM_Test_Log_Module::getInstance()
      {
        static DDS4CCM_Test_Log_Module instance_;

        return &instance_;
      }

      DDS4CCM_Log_Module::DDS4CCM_Log_Module ()
        : x11_logger::Log_Module ("DDS4CCMX11")
      {
      }

      DDS4CCM_Log_Module::~DDS4CCM_Log_Module ()
      {
      }

      /**
       * Log_Module, specific for the test framework.
       */
      DDS4CCM_Test_Log_Module::DDS4CCM_Test_Log_Module ()
        : x11_logger::Log_Module ("DDS4CCM_TEST",
                                  x11_logger::X11_LogMask::LP_ALL,
                                  x11_logger::X11_Verbose::V_PRIO|
                                  x11_logger::X11_Verbose::V_TIME)
      {
      }

      DDS4CCM_Test_Log_Module::~DDS4CCM_Test_Log_Module ()
      {
      }
    }; /* dds4ccm_logger */
  } /* DDS4CCM */
#endif /* !defined(X11_NLOGGING) */
}; /* CIAOX11 */
