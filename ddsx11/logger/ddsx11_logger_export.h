/**
 * @file    ddsx11_logger_export.h
 * @author  Unknown
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_LOGGER_EXPORT_H
#define DDSX11_LOGGER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (DDSX11_LOGGER_HAS_DLL)
#  define DDSX11_LOGGER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && DDSX11_LOGGER_HAS_DLL */

#if !defined (DDSX11_LOGGER_HAS_DLL)
#  define DDSX11_LOGGER_HAS_DLL 1
#endif /* ! DDSX11_LOGGER_HAS_DLL */

#if defined (DDSX11_LOGGER_HAS_DLL) && (DDSX11_LOGGER_HAS_DLL == 1)
#  if defined (DDSX11_LOGGER_BUILD_DLL)
#    define DDSX11_Logger_Export ACE_Proper_Export_Flag
#    define DDSX11_LOGGER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define DDSX11_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* DDSX11_LOGGER_BUILD_DLL */
#    define DDSX11_Logger_Export ACE_Proper_Import_Flag
#    define DDSX11_LOGGER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define DDSX11_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* DDSX11_LOGGER_BUILD_DLL */
#else /* DDSX11_LOGGER_HAS_DLL == 1 */
#  define DDSX11_Logger_Export
#  define DDSX11_LOGGER_SINGLETON_DECLARATION(T)
#  define DDSX11_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* DDSX11_LOGGER_HAS_DLL == 1 */

// Set DDSX11_LOGGER_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (DDSX11_LOGGER_NTRACE)
#  if (ACE_NTRACE == 1)
#    define DDSX11_LOGGER_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define DDSX11_LOGGER_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !DDSX11_LOGGER_NTRACE */

#if (DDSX11_LOGGER_NTRACE == 0)
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define DDSX11_LOGGER_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (DDSX11_LOGGER_NTRACE == 1) */

#endif /* DDSX11_LOGGER_EXPORT_H */

// End of auto generated file.
