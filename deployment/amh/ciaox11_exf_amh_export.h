// -*- C++ -*-
/**
 * @file    ciaox11_exf_amh_export.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CIAOX11_EXF_AMH_EXPORT_H
#define CIAOX11_EXF_AMH_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (CIAOX11_EXF_AMH_HAS_DLL)
#  define CIAOX11_EXF_AMH_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && CIAOX11_EXF_AMH_HAS_DLL */

#if !defined (CIAOX11_EXF_AMH_HAS_DLL)
#  define CIAOX11_EXF_AMH_HAS_DLL 1
#endif /* ! CIAOX11_EXF_AMH_HAS_DLL */

#if defined (CIAOX11_EXF_AMH_HAS_DLL) && (CIAOX11_EXF_AMH_HAS_DLL == 1)
#  if defined (CIAOX11_EXF_AMH_BUILD_DLL)
#    define CIAOX11_EXF_AMH_Export ACE_Proper_Export_Flag
#    define CIAOX11_EXF_AMH_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define CIAOX11_EXF_AMH_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* CIAOX11_EXF_AMH_BUILD_DLL */
#    define CIAOX11_EXF_AMH_Export ACE_Proper_Import_Flag
#    define CIAOX11_EXF_AMH_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define CIAOX11_EXF_AMH_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* CIAOX11_EXF_AMH_BUILD_DLL */
#else /* CIAOX11_EXF_AMH_HAS_DLL == 1 */
#  define CIAOX11_EXF_AMH_Export
#  define CIAOX11_EXF_AMH_SINGLETON_DECLARATION(T)
#  define CIAOX11_EXF_AMH_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* CIAOX11_EXF_AMH_HAS_DLL == 1 */

// Set CIAOX11_EXF_AMH_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (CIAOX11_EXF_AMH_NTRACE)
#  if (ACE_NTRACE == 1)
#    define CIAOX11_EXF_AMH_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define CIAOX11_EXF_AMH_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !CIAOX11_EXF_AMH_NTRACE */

#if (CIAOX11_EXF_AMH_NTRACE == 1)
#  define CIAOX11_EXF_AMH_TRACE(X)
#else /* (CIAOX11_EXF_AMH_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define CIAOX11_EXF_AMH_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (CIAOX11_EXF_AMH_NTRACE == 1) */

#endif /* CIAOX11_EXF_AMH_EXPORT_H */

// End of auto generated file.
