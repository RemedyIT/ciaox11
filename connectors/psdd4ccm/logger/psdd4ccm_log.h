/**
 * @file    psdd4ccm_log.h
 * @author  Martin Corino
 *
 * @brief   PSDD4CCM X11 logger stream implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_LOGGER_LOG_H
#define PSDD4CCM_LOGGER_LOG_H

#include "tao/x11/logger/log_base.h"
#include "psdd4ccm/logger/psdd4ccm_logger_export.h"

namespace CIAOX11
{
  namespace PSDD4CCM
  {
#define psdd4ccm_trace      x11_logger::trace ()
#define psdd4ccm_debug      x11_logger::debug ()
#define psdd4ccm_info       x11_logger::info ()
#define psdd4ccm_warning    x11_logger::warning ()
#define psdd4ccm_error      x11_logger::error ()
#define psdd4ccm_critical   x11_logger::critical ()
#define psdd4ccm_panic      x11_logger::panic ()

#define psdd4ccm_trace_w    x11_logger::trace_w ()
#define psdd4ccm_debug_w    x11_logger::debug_w ()
#define psdd4ccm_info_w     x11_logger::info_w ()
#define psdd4ccm_warning_w  x11_logger::warning_w ()
#define psdd4ccm_error_w    x11_logger::error_w ()
#define psdd4ccm_critical_w x11_logger::critical_w ()
#define psdd4ccm_panic_w    x11_logger::panic_w ()

#if !defined(X11_NLOGGING)
    namespace psdd4ccm_logger
    {
      class PSDD4CCM_Logger_Export PSDD4CCM_Log_Module
        : public x11_logger::Log_Module
      {
      public:
        virtual ~PSDD4CCM_Log_Module () = default;

        static PSDD4CCM_Log_Module* getInstance ();

        typedef x11_logger::Log_Type_T<PSDD4CCM_Log_Module> log_type;

      private:
        PSDD4CCM_Log_Module ();
      };

      /**
       * Log_Module, specific for the test framework.
       */
      class PSDD4CCM_Logger_Export PSDD4CCM_Test_Log_Module
        : public x11_logger::Log_Module
      {
      public:
        virtual ~PSDD4CCM_Test_Log_Module () = default;

        typedef x11_logger::Log_Type_T<PSDD4CCM_Test_Log_Module> log_type;

        static PSDD4CCM_Test_Log_Module* getInstance();

      private:
        PSDD4CCM_Test_Log_Module ();
      };

    } // namespace psdd4ccm_logger
#endif
  } // namespace PSDD4CCM
} // namespace CIAOX11

#if defined(X11_NLOGGING)

#define PSDD4CCM_LOGGER x11_logger::NULL_LogType

#else

# define PSDD4CCM_LOGGER \
    CIAOX11::PSDD4CCM::psdd4ccm_logger::PSDD4CCM_Log_Module::log_type

#endif /* !X11_NLOGGING */

using namespace CIAOX11::PSDD4CCM;

// CORE logging
#define PSDD4CCM_LOG_TRACE(__stmt__) \
  X11_LOG_TRACE (PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_DEBUG(__stmt__) \
  X11_LOG_DEBUG(PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_INFO(__stmt__) \
  X11_LOG_INFO(PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_WARNING( __stmt__) \
  X11_LOG_WARNING(PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_ERROR(__stmt__) \
  X11_LOG_ERROR(PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_CRITICAL(__stmt__) \
  X11_LOG_CRITICAL(PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_PANIC(__stmt__) \
  X11_LOG_PANIC(PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_TRACE_W(__stmt__) \
   X11_LOG_TRACE_W (PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_DEBUG_W(__stmt__) \
  X11_LOG_DEBUG_W(PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_INFO_W(__stmt__) \
  X11_LOG_INFO (PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_WARNING_W( __stmt__) \
  X11_LOG_WARNING_W (PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_ERROR_W(__stmt__) \
  X11_LOG_ERROR_W (PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_CRITICAL_W(__stmt__) \
  X11_LOG_CRITICAL_W (PSDD4CCM_LOGGER, __stmt__)

#define PSDD4CCM_LOG_PANIC_W(__stmt__) \
  X11_LOG_PANIC_W (PSDD4CCM_LOGGER, __stmt__)

#define DD4CCM_CALL_TRACE(__call__) \
  X11_CALL_TRACE(DD4CCM_LOGGER, __call__)

#define DD4CCM_CALL_TRACE_W(__call__) \
  X11_CALL_TRACE_W(DD4CCM_LOGGER, __call__)

#endif /* PSDD4CCM_LOGGER_LOG_H */
