/**
 * @file    ddsx11_log.cpp
 * @author  Marcel Smit
 *
 * @brief   DDSX11 for X11 log module.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "logger/ddsx11_log.h"

namespace DDSX11
{
#if !defined(X11_NLOGGING)
  namespace ddsx11_logger
  {
    DDSX11_Log_Module* DDSX11_Log_Module::getInstance()
    {
      static DDSX11_Log_Module instance_;

      return &instance_;
    }

    DDSX11_Log_Module::DDSX11_Log_Module ()
      : x11_logger::Log_Module ("DDSX11")
    {
    }

    DDSX11_Log_Module::~DDSX11_Log_Module ()
    {
    }
  }; /* ddsx11_logger */
} /* DDSX11 */
#endif /* !defined(X11_NLOGGING) */
