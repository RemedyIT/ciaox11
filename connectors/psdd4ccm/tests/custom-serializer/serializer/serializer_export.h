// -*- C++ -*-
/**
 * @file    serializer_export.h
 * @author  Martin Corino
 *
 * @brief   Custom serializer export header.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __SERIALIZER_EXPORT_INCLUDED__
#define __SERIALIZER_EXPORT_INCLUDED__

#include /**/ "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (SERIALIZER_HAS_DLL)
#  define SERIALIZER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && SERIALIZER_HAS_DLL */

#if !defined (SERIALIZER_HAS_DLL)
#  define SERIALIZER_HAS_DLL 1
#endif /* ! SERIALIZER_HAS_DLL */

#if defined (SERIALIZER_HAS_DLL) && (SERIALIZER_HAS_DLL == 1)
#  if defined (SERIALIZER_BUILD_DLL)
#    define SERIALIZER_Export ACE_Proper_Export_Flag
#    define SERIALIZER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define SERIALIZER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* SERIALIZER_BUILD_DLL */
#    define SERIALIZER_Export ACE_Proper_Import_Flag
#    define SERIALIZER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define SERIALIZER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* SERIALIZER_BUILD_DLL */
#else /* SERIALIZER_HAS_DLL == 1 */
#  define SERIALIZER_Export
#  define SERIALIZER_SINGLETON_DECLARATION(T)
#  define SERIALIZER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* SERIALIZER_HAS_DLL == 1 */

#endif /* __SERIALIZER_EXPORT_INCLUDED__ */
