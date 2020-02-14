// -*- C++ -*-
/**
 * @file    dds4ccm_ndds_publisher_listener_t.cpp
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   NDDS specific PublisherListener for DDS4CCM4CIAOX11,
 *          overriding the generic publisherlistener, extending
 *          it with NDDS specific methods.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_utils.h"

namespace CIAOX11
{
  namespace NDDS4CCM
  {
    template <typename EVT_STRATEGY>
    NDDSPublisherListener_T<EVT_STRATEGY>::NDDSPublisherListener_T (
        const EVT_STRATEGY &evs)
      : PublisherListener_T<EVT_STRATEGY> (evs)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::NDDSPublisherListener_T<EVT_STRATEGY>::NDDSPublisherListener");
    }

    template <typename EVT_STRATEGY>
    void
    NDDSPublisherListener_T<EVT_STRATEGY>::on_reliable_writer_cache_changed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
      const ::DDS::ReliableWriterCacheChangedStatus & status)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::NDDSPublisherListener_T<EVT_STRATEGY>::on_reliable_writer_cache_changed");

      DDS4CCM_LOG_DEBUG ("NDDSPublisherListener_T<EVT_STRATEGY>::on_reliable_writer_cache_changed - "
        << IDL::traits< ::DDS::ReliableWriterCacheChangedStatus >::write (status));

      this->on_unexpected_status (std::move(the_Writer), ::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS);
    }

    template <typename EVT_STRATEGY>
    void
    NDDSPublisherListener_T<EVT_STRATEGY>::on_reliable_reader_activity_changed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
      const ::DDS::ReliableReaderActivityChangedStatus & status)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::NDDSPublisherListener_T<EVT_STRATEGY>::on_reliable_reader_activity_changed");

      DDS4CCM_LOG_DEBUG ("NDDSPublisherListener_T<EVT_STRATEGY>::on_reliable_reader_activity_changed - "
        << IDL::traits< ::DDS::ReliableReaderActivityChangedStatus >::write (status));

      this->on_unexpected_status (std::move(the_Writer), ::DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS);
    }

    template <typename EVT_STRATEGY>
    ::DDS::StatusKind
    NDDSPublisherListener_T<EVT_STRATEGY>::get_mask (
      IDL::traits< CCM_DDS::ConnectorStatusListener>::ref_type error_listener)
    {
      ::DDS::StatusMask mask {};

      if (error_listener)
        {
          mask = PublisherListener_T<EVT_STRATEGY>::get_mask (error_listener) |
                ::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS |
                ::DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS;
        }
      DDS4CCM_LOG_DEBUG ("NDDSPublisherListener_T<EVT_STRATEGY>::get_mask - "
        << "Mask becomes <"
        << IDL::traits< ::DDS::StatusMask >::write<status_mask_formatter> (mask)
        << ">");
      return mask;
    }
  }
}
