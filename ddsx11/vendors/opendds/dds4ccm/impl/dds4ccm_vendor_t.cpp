// -*- C++ -*-
/**
 * @file    dds4ccm_vendor_t.cpp
 * @author  Johnny Willemsen
 *
 * @brief   OpenDDS specific implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_publisher_listener_t.h"

#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    namespace VendorUtils
    {
      template <typename EVT_STRATEGY>
      IDL::traits<::DDS::PublisherListener>::ref_type
      create_publisher_listener (const EVT_STRATEGY &evs)
      {
        return CORBA::make_reference<CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>> (evs);
      }

      template <typename EVT_STRATEGY>
      ::DDS::StatusKind
      get_publisher_listener_mask (
        IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type error_listener)
      {
        return CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::get_mask (error_listener);
      }
    }
  }
}
