/**
 * @file    dds4ccm_log.h
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM X11 logger stream implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_LOGGER_LOG_H
#define DDS4CCM_LOGGER_LOG_H

#include "tao/x11/logger/log_base.h"
#include "dds4ccm/logger/dds4ccm_logger_export.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
#define dds4ccm_trace      x11_logger::trace ()
#define dds4ccm_debug      x11_logger::debug ()
#define dds4ccm_info       x11_logger::info ()
#define dds4ccm_warning    x11_logger::warning ()
#define dds4ccm_error      x11_logger::error ()
#define dds4ccm_critical   x11_logger::critical ()
#define dds4ccm_panic      x11_logger::panic ()

#define dds4ccm_trace_w    x11_logger::trace_w ()
#define dds4ccm_debug_w    x11_logger::debug_w ()
#define dds4ccm_info_w     x11_logger::info_w ()
#define dds4ccm_warning_w  x11_logger::warning_w ()
#define dds4ccm_error_w    x11_logger::error_w ()
#define dds4ccm_critical_w x11_logger::critical_w ()
#define dds4ccm_panic_w    x11_logger::panic_w ()

#if !defined(X11_NLOGGING)
    namespace dds4ccm_logger
    {
      class DDS4CCM_Logger_Export DDS4CCM_Log_Module
        : public x11_logger::Log_Module
      {
      public:
        ~DDS4CCM_Log_Module () override;

        static DDS4CCM_Log_Module* getInstance ();

        typedef x11_logger::Log_Type_T<DDS4CCM_Log_Module> log_type;

      private:
        DDS4CCM_Log_Module ();
      };

      /**
       * Log_Module, specific for the test framework.
       */
      class DDS4CCM_Logger_Export DDS4CCM_Test_Log_Module
        : public x11_logger::Log_Module
      {
      public:
        ~DDS4CCM_Test_Log_Module () override;

        typedef x11_logger::Log_Type_T<DDS4CCM_Test_Log_Module> log_type;

        static DDS4CCM_Test_Log_Module* getInstance();

      private:
        DDS4CCM_Test_Log_Module ();
      };

    } // namespace dds4ccm_logger
#endif
  } // namespace DDS4CCM
} // namespace CIAOX11

#if defined(X11_NLOGGING)

#define DDS4CCM_LOGGER x11_logger::NULL_LogType

#else

# define DDS4CCM_LOGGER \
    CIAOX11::DDS4CCM::dds4ccm_logger::DDS4CCM_Log_Module::log_type

#endif /* !X11_NLOGGING */

using namespace CIAOX11::DDS4CCM;

// CORE logging
#define DDS4CCM_LOG_TRACE(__stmt__) \
  X11_LOG_TRACE (DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_DEBUG(__stmt__) \
  X11_LOG_DEBUG(DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_INFO(__stmt__) \
  X11_LOG_INFO(DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_WARNING( __stmt__) \
  X11_LOG_WARNING(DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_ERROR(__stmt__) \
  X11_LOG_ERROR(DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_CRITICAL(__stmt__) \
  X11_LOG_CRITICAL(DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_PANIC(__stmt__) \
  X11_LOG_PANIC(DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_TRACE_W(__stmt__) \
   X11_LOG_TRACE_W (DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_DEBUG_W(__stmt__) \
  X11_LOG_DEBUG_W(DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_INFO_W(__stmt__) \
  X11_LOG_INFO (DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_WARNING_W( __stmt__) \
  X11_LOG_WARNING_W (DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_ERROR_W(__stmt__) \
  X11_LOG_ERROR_W (DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_CRITICAL_W(__stmt__) \
  X11_LOG_CRITICAL_W (DDS4CCM_LOGGER, __stmt__)

#define DDS4CCM_LOG_PANIC_W(__stmt__) \
  X11_LOG_PANIC_W (DDS4CCM_LOGGER, __stmt__)

#define DD4CCM_CALL_TRACE(__call__) \
  X11_CALL_TRACE(DD4CCM_LOGGER, __call__)

#define DD4CCM_CALL_TRACE_W(__call__) \
  X11_CALL_TRACE_W(DD4CCM_LOGGER, __call__)

#endif /* DDS4CCM_LOGGER_LOG_H */
