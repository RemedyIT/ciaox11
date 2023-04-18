// -*- C++ -*-
/**
 * @file    dds4ccm_ndds_publisher_listener_t.h
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   NDDS specific PublisherListener for DDS4CCM4CIAOX11,
 *          overriding the generic publisherlistener, extending
 *          it with NDDS specific methods.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_NDDS_PUBLISHERLISTENER_T_H_
#define DDS4CCM_NDDS_PUBLISHERLISTENER_T_H_

#include "dds4ccm/impl/dds4ccm_publisher_listener_t.h"

namespace CIAOX11
{
  namespace NDDS4CCM
  {
    template <typename EVT_STRATEGY>
    class NDDSPublisherListener_T final
      : public virtual DDS4CCM::PublisherListener_T<EVT_STRATEGY>
    {
    public:
      explicit NDDSPublisherListener_T (const EVT_STRATEGY &evs);

      ~NDDSPublisherListener_T () override = default;

      void
      on_reliable_writer_cache_changed (
        IDL::traits<::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::ReliableWriterCacheChangedStatus & status) override;

      void
      on_reliable_reader_activity_changed (
        IDL::traits<::DDS::DataWriter>::ref_type the_Writer,
        const ::DDS::ReliableReaderActivityChangedStatus & status) override;

      static ::DDS::StatusKind
      get_mask (
        IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type error_listener);
    };
  }
}

#include "dds4ccm/impl/dds4ccm_ndds_publisher_listener_t.cpp"

#endif /* DDS4CCM_NDDS_PUBLISHERLISTENER_H_ */
