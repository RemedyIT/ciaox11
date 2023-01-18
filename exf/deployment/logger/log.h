/**
 * @file    log.h
 * @author  Martin Corino
 *
 * @brief   CIAOX11 ExF logger stream implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_EXF_LOGGER_LOG_H
#define CIAOX11_EXF_LOGGER_LOG_H

#include "tao/x11/logger/log_base.h"

#include "exf/deployment/logger/ciaox11_exf_logger_export.h"

namespace CIAOX11
{

#define ciaox11_exf_trace      x11_logger::trace ()
#define ciaox11_exf_debug      x11_logger::debug ()
#define ciaox11_exf_info       x11_logger::info ()
#define ciaox11_exf_warning    x11_logger::warning ()
#define ciaox11_exf_error      x11_logger::error ()
#define ciaox11_exf_critical   x11_logger::critical ()
#define ciaox11_exf_panic      x11_logger::panic ()

#define ciaox11_exf_trace_w    x11_logger::trace_w ()
#define ciaox11_exf_debug_w    x11_logger::debug_w ()
#define ciaox11_exf_info_w     x11_logger::info_w ()
#define ciaox11_exf_warning_w  x11_logger::warning_w ()
#define ciaox11_exf_error_w    x11_logger::error_w ()
#define ciaox11_exf_critical_w x11_logger::critical_w ()
#define ciaox11_exf_panic_w    x11_logger::panic_w ()

#if !defined(X11_NLOGGING)

  namespace ciaox11_exf_logger
  {
    class CIAOX11_EXF_Logger_Export CIAOX11_EXF_Log_Msg
      : public x11_logger::Log_Module
    {
    public:
      CIAOX11_EXF_Log_Msg();
       ~CIAOX11_EXF_Log_Msg() override;

      static CIAOX11_EXF_Log_Msg* getInstance();

      typedef x11_logger::Log_Type_T<CIAOX11_EXF_Log_Msg> log_type;
    };
  } // namespace ciaox11_exf_logger

#endif /* !X11_NLOGGING */
} // namespace CIAOX11

#if defined(X11_NLOGGING)

#define TAOX11_LOGGER   x11_logger::NULL_LogType

#else

#define CIAOX11_EXF_LOGGER \
  CIAOX11::ciaox11_exf_logger::CIAOX11_EXF_Log_Msg::log_type

#endif /* !X11_NLOGGING */

using namespace CIAOX11;

#define CIAOX11_EXF_LOG_TRACE(__stmt__) \
  X11_LOG_TRACE (CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_DEBUG(__stmt__) \
  X11_LOG_DEBUG(CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_INFO(__stmt__) \
  X11_LOG_INFO(CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_WARNING( __stmt__) \
  X11_LOG_WARNING(CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_ERROR(__stmt__) \
  X11_LOG_ERROR(CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_CRITICAL(__stmt__) \
  X11_LOG_CRITICAL(CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_PANIC(__stmt__) \
  X11_LOG_PANIC(CIAOX11_EXF_LOGGER, __stmt__)

// CORE logging
#define CIAOX11_EXF_LOG_TRACE_W(__stmt__) \
   X11_LOG_TRACE_W (CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_DEBUG_W(__stmt__) \
  X11_LOG_DEBUG_W(CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_INFO_W(__stmt__) \
  X11_LOG_INFO (CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_WARNING_W( __stmt__) \
  X11_LOG_WARNING_W (CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_ERROR_W(__stmt__) \
  X11_LOG_ERROR_W (CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_CRITICAL_W(__stmt__) \
  X11_LOG_CRITICAL_W (CIAOX11_EXF_LOGGER, __stmt__)

#define CIAOX11_EXF_LOG_PANIC_W(__stmt__) \
  X11_LOG_PANIC_W (CIAOX11_EXF_LOGGER, __stmt__)

#endif /* CIAOX11_EXF_LOGGER_LOG_H */
