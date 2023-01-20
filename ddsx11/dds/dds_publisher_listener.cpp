// -*- C++ -*-
/**
 * @file    dds_publisher_listener.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds_publisher_listener.h"
#include "dds_publisher.h"
#include "dds_data_writer_t.h"
#include "dds_domain_participant.h"

#include "logger/ddsx11_log.h"
#include "dds_proxy_entity_manager.h"

namespace DDSX11
{
  DDS_PublisherListener_proxy::DDS_PublisherListener_proxy (
    IDL::traits<::DDS::PublisherListener>::ref_type p)
    : impl_ (std::move (p))
  {
    DDSX11_LOG_TRACE ("DDS_PublisherListener_proxy::DDS_PublisherListener_proxy");
  }

  DDS_PublisherListener_proxy::~DDS_PublisherListener_proxy ()
  {
    DDSX11_LOG_TRACE ("DDS_PublisherListener_proxy::~DDS_PublisherListener_proxy");
  }

  void
  DDS_PublisherListener_proxy::on_offered_deadline_missed (
    DDS_Native::DDS::DataWriter* the_writer,
    const DDS_Native::DDS::OfferedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_PublisherListener_proxy::on_offered_deadline_missed");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_offered_deadline_missed (std::move(dw),
        ::DDSX11::traits< ::DDS::OfferedDeadlineMissedStatus>::retn (status));
    }
  }

  void
  DDS_PublisherListener_proxy::on_offered_incompatible_qos (
    DDS_Native::DDS::DataWriter* the_writer,
    const DDS_Native::DDS::OfferedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_PublisherListener_proxy::on_offered_incompatible_qos");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_offered_incompatible_qos (std::move(dw),
        ::DDSX11::traits< ::DDS::OfferedIncompatibleQosStatus>::retn (status));
    }
  }

  void
  DDS_PublisherListener_proxy::on_liveliness_lost (
    DDS_Native::DDS::DataWriter* the_writer,
    const DDS_Native::DDS::LivelinessLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_PublisherListener_proxy::on_liveliness_lost");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_liveliness_lost (std::move(dw),
        ::DDSX11::traits< ::DDS::LivelinessLostStatus>::retn (status));
    }
  }

  void
  DDS_PublisherListener_proxy::on_publication_matched (
    DDS_Native::DDS::DataWriter* the_writer,
    const DDS_Native::DDS::PublicationMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_PublisherListener_proxy::on_publication_matched");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_publication_matched (std::move(dw),
        ::DDSX11::traits< ::DDS::PublicationMatchedStatus>::retn (status));
    }
  }

  IDL::traits<::DDS::PublisherListener>::ref_type
  DDS_PublisherListener_proxy::get_publisher_listener ()
  {
    return this->impl_;
  }
}
