/**
 * @file    ddsx11_log.h
 * @author  Marcel Smit
 *
 * @brief   DDSX11 logger stream implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_LOG_H_
#define DDSX11_LOG_H_

#include "tao/x11/logger/log_base.h"
#include "logger/ddsx11_logger_export.h"

namespace DDSX11
{
#define dds_proxy_trace      x11_logger::trace ()
#define dds_proxy_debug      x11_logger::debug ()
#define dds_proxy_info       x11_logger::info ()
#define dds_proxy_warning    x11_logger::warning ()
#define dds_proxy_error      x11_logger::error ()
#define dds_proxy_critical   x11_logger::critical ()
#define dds_proxy_panic      x11_logger::panic ()

#define dds_proxy_trace_w    x11_logger::trace_w ()
#define dds_proxy_debug_w    x11_logger::debug_w ()
#define dds_proxy_info_w     x11_logger::info_w ()
#define dds_proxy_warning_w  x11_logger::warning_w ()
#define dds_proxy_error_w    x11_logger::error_w ()
#define dds_proxy_critical_w x11_logger::critical_w ()
#define dds_proxy_panic_w    x11_logger::panic_w ()

#if !defined(X11_NLOGGING)
  namespace ddsx11_logger
  {
    class DDSX11_Logger_Export DDSX11_Log_Module
      : public x11_logger::Log_Module
    {
    public:
      virtual ~DDSX11_Log_Module ();

      static DDSX11_Log_Module* getInstance ();

      typedef x11_logger::Log_Type_T<DDSX11_Log_Module> log_type;

    private:
      DDSX11_Log_Module ();
    };
  } // namespace ddsx11_logger
#endif
} // namespace DDSX11

#if defined(X11_NLOGGING)

# define DDSX11_IMPL_LOGGER x11_logger::NULL_LogType

#else

# define DDSX11_IMPL_LOGGER \
    DDSX11::ddsx11_logger::DDSX11_Log_Module::log_type
#endif

using namespace DDSX11;

// CORE logging
#define DDSX11_LOG_TRACE(__stmt__) \
  X11_LOG_TRACE (DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_DEBUG(__stmt__) \
  X11_LOG_DEBUG(DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_INFO(__stmt__) \
  X11_LOG_INFO(DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_WARNING( __stmt__) \
  X11_LOG_WARNING(DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_ERROR(__stmt__) \
  X11_LOG_ERROR(DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_CRITICAL(__stmt__) \
  X11_LOG_CRITICAL(DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_PANIC(__stmt__) \
  X11_LOG_PANIC(DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_LOG_TRACE_W(__stmt__) \
   X11_LOG_TRACE_W (DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_DEBUG_W(__stmt__) \
  X11_LOG_DEBUG_W(DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_INFO_W(__stmt__) \
  X11_LOG_INFO (DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_WARNING_W( __stmt__) \
  X11_LOG_WARNING_W (DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_ERROR_W(__stmt__) \
  X11_LOG_ERROR_W (DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_CRITICAL_W(__stmt__) \
  X11_LOG_CRITICAL_W (DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_IMPL_LOG_PANIC_W(__stmt__) \
  X11_LOG_PANIC_W (DDSX11_IMPL_LOGGER, __stmt__)

#define DDSX11_CALL_TRACE(__call__) \
  X11_CALL_TRACE(DDSX11_LOGGER, __call__)

#define DDSX11_CALL_TRACE_W(__call__) \
  X11_CALL_TRACE_W(DDSX11_LOGGER, __call__)

#endif /* DDSX11_LOG_H_ */
