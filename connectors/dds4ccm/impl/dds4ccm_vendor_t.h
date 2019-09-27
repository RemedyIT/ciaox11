// -*- C++ -*-
/**
 * @file    dds4ccm_vendor_t.h
 * @author  Marcel Smit/Martin Corino
 *
 * @brief   Definitions for vendor specific implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_VENDOR_T_H_
#define DDS4CCM_VENDOR_T_H_

#include "dds4ccm/idl/ccm_ddsC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {

    namespace VendorUtils
    {
      /* Provides for creation of vendor extended listeners.
       */
      template <typename EVT_STRATEGY>
      IDL::traits< ::DDS::PublisherListener >::ref_type
      create_publisher_listener (
        const EVT_STRATEGY &evs);

      template <typename EVT_STRATEGY>
      ::DDS::StatusKind
      get_publisher_listener_mask (
        IDL::traits< CCM_DDS::ConnectorStatusListener >::ref_type error_listener);
    }
  }
}

#include "dds4ccm/impl/dds4ccm_vendor_t.cpp"

#endif /* DDS4CCM_VENDOR_T_H_ */
