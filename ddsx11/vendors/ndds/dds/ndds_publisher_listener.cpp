// -*- C++ -*-
/**
 * @file    ndds_publisher_listener.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/ndds_publisher_listener.h"

#include "dds/dds_proxy_entity_manager.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    NDDS_PublisherListener_proxy::NDDS_PublisherListener_proxy (
        IDL::traits< ::DDS::PublisherListener>::ref_type p)
      : DDS_PublisherListener_proxy (std::move(p))
    {
      DDSX11_LOG_TRACE ("NDDS_PublisherListener_proxy::NDDS_PublisherListener_proxy");
    }

    NDDS_PublisherListener_proxy::~NDDS_PublisherListener_proxy ()
    {
      DDSX11_LOG_TRACE ("NDDS_PublisherListener_proxy::~NDDS_PublisherListener_proxy");
    }

    void
    NDDS_PublisherListener_proxy::on_reliable_reader_activity_changed (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::ReliableReaderActivityChangedStatus & status)
    {
      DDSX11_LOG_TRACE ("NDDS_PublisherListener_proxy::on_reliable_reader_activity_changed");

      IDL::traits< ::DDS::DataWriter>::ref_type dw =
        DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
      if (dw)
      {
        this->impl_->on_reliable_reader_activity_changed (std::move(dw),
          ::DDSX11::traits< ::DDS::ReliableReaderActivityChangedStatus>::retn (status));
      }
    }

    void
    NDDS_PublisherListener_proxy::on_reliable_writer_cache_changed (
      DDS_Native::DDS::DataWriter* the_writer,
      const DDS_Native::DDS::ReliableWriterCacheChangedStatus & status)
    {
      DDSX11_LOG_TRACE ("NDDS_PublisherListener_proxy::on_reliable_writer_cache_changed");

      IDL::traits< ::DDS::DataWriter>::ref_type dw =
        DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
      if (dw)
      {
        this->impl_->on_reliable_writer_cache_changed (std::move(dw),
          ::DDSX11::traits< ::DDS::ReliableWriterCacheChangedStatus>::retn (status));
      }
    }
  }
}
