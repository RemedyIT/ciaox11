// -*- C++ -*-
/**
 * @file    ciaox11_exf_core_export.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_CORE_EXPORT_H
#define CIAOX11_EXF_CORE_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (CIAOX11_EXF_CORE_HAS_DLL)
#  define CIAOX11_EXF_CORE_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && CIAOX11_EXF_CORE_HAS_DLL */

#if !defined (CIAOX11_EXF_CORE_HAS_DLL)
#  define CIAOX11_EXF_CORE_HAS_DLL 1
#endif /* ! CIAOX11_EXF_CORE_HAS_DLL */

#if defined (CIAOX11_EXF_CORE_HAS_DLL) && (CIAOX11_EXF_CORE_HAS_DLL == 1)
#  if defined (CIAOX11_EXF_CORE_BUILD_DLL)
#    define CIAOX11_EXF_CORE_Export ACE_Proper_Export_Flag
#    define CIAOX11_EXF_CORE_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define CIAOX11_EXF_CORE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* CIAOX11_EXF_CORE_BUILD_DLL */
#    define CIAOX11_EXF_CORE_Export ACE_Proper_Import_Flag
#    define CIAOX11_EXF_CORE_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define CIAOX11_EXF_CORE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* CIAOX11_EXF_CORE_BUILD_DLL */
#else /* CIAOX11_EXF_CORE_HAS_DLL == 1 */
#  define CIAOX11_EXF_CORE_Export
#  define CIAOX11_EXF_CORE_SINGLETON_DECLARATION(T)
#  define CIAOX11_EXF_CORE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* CIAOX11_EXF_CORE_HAS_DLL == 1 */

// Set CIAOX11_EXF_CORE_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (CIAOX11_EXF_CORE_NTRACE)
#  if (ACE_NTRACE == 1)
#    define CIAOX11_EXF_CORE_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define CIAOX11_EXF_CORE_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !CIAOX11_EXF_CORE_NTRACE */

#if (CIAOX11_EXF_CORE_NTRACE == 1)
#  define CIAOX11_EXF_CORE_TRACE(X)
#else /* (CIAOX11_EXF_CORE_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define CIAOX11_EXF_CORE_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (CIAOX11_EXF_CORE_NTRACE == 1) */

#endif /* CIAOX11_EXF_CORE_EXPORT_H */

// End of auto generated file.
