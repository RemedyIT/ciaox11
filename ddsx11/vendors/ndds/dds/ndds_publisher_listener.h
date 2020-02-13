// -*- C++ -*-
/**
 * @file    ndds_publisher_listener.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_PUBLISHER_LISTENER_H_
#define DDSX11_IMPL_NDDS_PUBLISHER_LISTENER_H_

#include "dds/dds_publisher_listener.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    class DDSX11_IMPL_Export NDDS_PublisherListener_proxy
      : public virtual DDSX11::DDS_PublisherListener_proxy
    {
    public:
      NDDS_PublisherListener_proxy (
        IDL::traits< ::DDS::PublisherListener>::ref_type p);

      virtual ~NDDS_PublisherListener_proxy () = default;

      /**
       * NDDS specific callback methods.
       */
      //@{
      virtual void
      on_reliable_reader_activity_changed (
        DDS_Native::DDS::DataWriter *the_writer,
        const DDS_Native::DDS::ReliableReaderActivityChangedStatus & status) override;

      virtual void
      on_reliable_writer_cache_changed (
        DDS_Native::DDS::DataWriter *the_writer,
        const DDS_Native::DDS::ReliableWriterCacheChangedStatus & status) override;
      //@}
    };
  }
}

#endif /* DDSX11_IMPL_NDDS_DATA_WRITER_LISTENER_H_ */
