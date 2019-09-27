// -*- C++ -*-
/**
 * @file    test_interceptor_export.h
 * @author  Marcel Smit
 *
 * @brief   Generated
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef TEST_INTERCEPTOR_EXPORT_H
#define TEST_INTERCEPTOR_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (TEST_INTERCEPTOR_HAS_DLL)
#  define TEST_INTERCEPTOR_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && TEST_INTERCEPTOR_HAS_DLL */

#if !defined (TEST_INTERCEPTOR_HAS_DLL)
#  define TEST_INTERCEPTOR_HAS_DLL 1
#endif /* ! TEST_INTERCEPTOR_HAS_DLL */

#if defined (TEST_INTERCEPTOR_HAS_DLL) && (TEST_INTERCEPTOR_HAS_DLL == 1)
#  if defined (TEST_INTERCEPTOR_BUILD_DLL)
#    define Test_Interceptor_Export ACE_Proper_Export_Flag
#    define TEST_INTERCEPTOR_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define TEST_INTERCEPTOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* TEST_INTERCEPTOR_BUILD_DLL */
#    define Test_Interceptor_Export ACE_Proper_Import_Flag
#    define TEST_INTERCEPTOR_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define TEST_INTERCEPTOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* TEST_INTERCEPTOR_BUILD_DLL */
#else /* TEST_INTERCEPTOR_HAS_DLL == 1 */
#  define Test_Interceptor_Export
#  define TEST_INTERCEPTOR_SINGLETON_DECLARATION(T)
#  define TEST_INTERCEPTOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* TEST_INTERCEPTOR_HAS_DLL == 1 */

#endif /* TEST_INTERCEPTOR_EXPORT_H */

// End of auto generated file.
