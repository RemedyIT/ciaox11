/**
 * @file    log.h
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 logger stream implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_LOGGER_LOG_H
#define CIAOX11_LOGGER_LOG_H

#include "tao/x11/logger/log_base.h"
#include "ciaox11/logger/ciaox11_logger_export.h"

namespace CIAOX11
{

#define ciaox11_trace      x11_logger::trace ()
#define ciaox11_debug      x11_logger::debug ()
#define ciaox11_info       x11_logger::info ()
#define ciaox11_warning    x11_logger::warning ()
#define ciaox11_error      x11_logger::error ()
#define ciaox11_critical   x11_logger::critical ()
#define ciaox11_panic      x11_logger::panic ()

#define ciaox11_trace_w    x11_logger::trace_w ()
#define ciaox11_debug_w    x11_logger::debug_w ()
#define ciaox11_info_w     x11_logger::info_w ()
#define ciaox11_warning_w  x11_logger::warning_w ()
#define ciaox11_error_w    x11_logger::error_w ()
#define ciaox11_critical_w x11_logger::critical_w ()
#define ciaox11_panic_w    x11_logger::panic_w ()

#if !defined(X11_NLOGGING)

  namespace ciaox11_logger
  {
    class CIAOX11_Logger_Export CIAOX11_Log_Msg
      : public x11_logger::Log_Module
    {
    public:
      ~CIAOX11_Log_Msg() override = default;

      static CIAOX11_Log_Msg* getInstance();

      using log_type = x11_logger::Log_Type_T<CIAOX11_Log_Msg>;

    private:
      CIAOX11_Log_Msg();
    };


    class CIAOX11_Logger_Export CIAOX11_Test_Log_Msg
      : public x11_logger::Log_Module
    {
    public:
      ~CIAOX11_Test_Log_Msg () override = default;

      using log_type = x11_logger::Log_Type_T<CIAOX11_Test_Log_Msg>;

      static CIAOX11_Test_Log_Msg* getInstance();

    private:
      CIAOX11_Test_Log_Msg ();
    };
  } // namespace ciaox11_logger

#endif /* !X11_NLOGGING */
} // namespace CIAOX11_NAMESPACE

#if defined(X11_NLOGGING)

#define CIAOX11_LOGGER   x11_logger::NULL_LogType

#else

#define CIAOX11_LOGGER \
  CIAOX11::ciaox11_logger::CIAOX11_Log_Msg::log_type

#endif /* !X11_NLOGGING */

using namespace CIAOX11;

// CORE logging
#define CIAOX11_LOG_TRACE(__stmt__) \
 X11_LOG_TRACE (CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_DEBUG(__stmt__) \
  X11_LOG_DEBUG(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_INFO(__stmt__) \
  X11_LOG_INFO(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_WARNING( __stmt__) \
  X11_LOG_WARNING(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_ERROR(__stmt__) \
  X11_LOG_ERROR(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_CRITICAL(__stmt__) \
  X11_LOG_CRITICAL(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_PANIC(__stmt__) \
  X11_LOG_PANIC(CIAOX11_LOGGER, __stmt__)

// CORE logging
#define CIAOX11_LOG_TRACE_W(__stmt__) \
   X11_LOG_TRACE_W (CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_DEBUG_W(__stmt__) \
  X11_LOG_DEBUG_W(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_INFO_W(__stmt__) \
  X11_LOG_INFO(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_WARNING_W( __stmt__) \
  X11_LOG_WARNING_W(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_ERROR_W(__stmt__) \
  X11_LOG_ERROR_W(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_CRITICAL_W(__stmt__) \
  X11_LOG_CRITICAL_W(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_LOG_PANIC_W(__stmt__) \
  X11_LOG_PANIC_W(CIAOX11_LOGGER, __stmt__)

#define CIAOX11_CALL_TRACE(__call__) \
  X11_CALL_TRACE(CIAOX11_LOGGER, __call__)

#define CIAOX11_CALL_TRACE_W(__call__) \
  X11_CALL_TRACE_W(CIAOX11_LOGGER, __call__)

#endif /* CIAOX11_LOGGER_LOG_H */
