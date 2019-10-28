// -*- C++ -*-
/**
 * @file    dds_export.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_EXPORT_H_
#define DDSX11_IMPL_EXPORT_H_

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (DDSX11_IMPL_HAS_DLL)
#  define DDSX11_IMPL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && DDSX11_IMPL_HAS_DLL */

#if !defined (DDSX11_IMPL_HAS_DLL)
#  define DDSX11_IMPL_HAS_DLL 1
#endif /* ! DDSX11_IMPL_HAS_DLL */

#if defined (DDSX11_IMPL_HAS_DLL) && (DDSX11_IMPL_HAS_DLL == 1)
#  if defined (DDSX11_IMPL_BUILD_DLL)
#    define DDSX11_IMPL_Export ACE_Proper_Export_Flag
#    define DDSX11_IMPL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define DDSX11_IMPL_NDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* DDSX11_IMPL_BUILD_DLL */
#    define DDSX11_IMPL_Export ACE_Proper_Import_Flag
#    define DDSX11_IMPL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define DDSX11_IMPL_NDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* DDSX11_IMPL_BUILD_DLL */
#else /* DDSX11_IMPL_HAS_DLL == 1 */
#  define DDSX11_IMPL_Export
#  define DDSX11_IMPL_SINGLETON_DECLARATION(T)
#  define DDSX11_IMPL_NDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* DDSX11_IMPL_HAS_DLL == 1 */

#endif /* DDSX11_IMPL_EXPORT_H_ */

// End of auto generated file.
