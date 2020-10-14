/**
 * @file    log.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 logger stream implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11/logger/log.h"

namespace CIAOX11
{
#if !defined(X11_NLOGGING)

  namespace ciaox11_logger
  {
    CIAOX11_Log_Msg* CIAOX11_Log_Msg::getInstance()
    {
      static CIAOX11_Log_Msg instance_;

      return std::addressof(instance_);
    }

    CIAOX11_Test_Log_Msg* CIAOX11_Test_Log_Msg::getInstance()
    {
      static CIAOX11_Test_Log_Msg instance_;

      return std::addressof(instance_);
    }

    CIAOX11_Log_Msg::CIAOX11_Log_Msg()
      : x11_logger::Log_Module ("CIAOX11")
    {
    }

    CIAOX11_Log_Msg::~CIAOX11_Log_Msg()
    {
    }

    CIAOX11_Test_Log_Msg::CIAOX11_Test_Log_Msg()
      : x11_logger::Log_Module ("CIAOX11_TEST",
                                x11_logger::X11_LogMask::LP_ALL,
                                x11_logger::X11_Verbose::V_PRIO|
                                x11_logger::X11_Verbose::V_TIME)
    {
    }

    CIAOX11_Test_Log_Msg::~CIAOX11_Test_Log_Msg()
    {
    }

  } // namespace ciaox11_logger

#endif
} // namespace CIAOX11_NAMESPACE
