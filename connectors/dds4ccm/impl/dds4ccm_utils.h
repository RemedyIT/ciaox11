// -*- C++ -*-
/**
 * @file    dds4ccm_utils.h
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM4CIAOX11 utilities
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_UTILS_H_
#define DDS4CCM_UTILS_H_

#include "dds4ccm/impl/dds4ccm_impl_export.h"
#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/idl/ccm_ddsC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    enum DDS4CCM_LISTENER_READ_TAKE
    {
      /// Listener does a DDS read
      DDS4CCM_READ,
      /// Listener does a DDS take
      DDS4CCM_TAKE
    };
  } /* DDS4CCM */
} /* CIAOX11 */

#define catch_dds4ccm_listener_ex(ex, L) \
  catch (const CORBA::Exception &ex) \
  { \
    DDS4CCM_LOG_ERROR (L << " - " \
      << "ERROR: Caught unexpected CORBA exception: " << ex); \
  } \
  catch (const std::exception &ex) \
  { \
    DDS4CCM_LOG_ERROR (L << " - " \
      << "ERROR: Caught unexpected std exception: " << ex.what ()); \
  } \
  catch (...) \
  { \
    DDS4CCM_LOG_ERROR (L << " - " \
      << "ERROR: Caught unexpected exception"); \
  }

#define catch_dds4ccm_lifecycle_ex(ex, L) \
  catch (const CCM_DDS::InternalError &ex) \
  { \
    DDS4CCM_LOG_ERROR (L << " - " \
      << "ERROR caught unexpected CCM_DDS::InternalError exception: " \
      << ex); \
    throw CORBA::INTERNAL (); \
  } \
  catch (const CORBA::Exception &ex) \
  { \
    DDS4CCM_LOG_ERROR (L << " - " \
      << "ERROR caught unexpected CORBA exception: " \
      << ex); \
    throw; \
  } \
  catch (const std::exception &ex) \
  { \
    DDS4CCM_LOG_ERROR (L << " - " \
      << "ERROR caught unexpected std exception: " \
      << ex.what ()); \
    throw; \
  } \
  catch (...) \
  { \
    DDS4CCM_LOG_ERROR (L << " - " \
      << "ERROR caught unexpected exception"); \
    throw CORBA::INTERNAL (); \
  }

#endif /* DDS4CCM_UTILS_H_ */
