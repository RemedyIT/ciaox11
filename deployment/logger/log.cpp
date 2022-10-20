/**
 * @file    log.cpp
 * @author  Martin Corino
 *
 * @brief   CIAOX11 ExF logger stream implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "exf/deployment/logger/log.h"

namespace CIAOX11
{
#if !defined(X11_NLOGGING)

  namespace ciaox11_exf_logger
  {
    CIAOX11_EXF_Log_Msg* CIAOX11_EXF_Log_Msg::getInstance()
    {
      static CIAOX11_EXF_Log_Msg instance_;

      return std::addressof(instance_);
    }

    CIAOX11_EXF_Log_Msg::CIAOX11_EXF_Log_Msg()
      : x11_logger::Log_Module ("CIAOX11_EXF")
    {
    }

    CIAOX11_EXF_Log_Msg::~CIAOX11_EXF_Log_Msg()
    {
    }

  } // namespace ciaox11_logger

#endif
} // namespace CIAOX11
