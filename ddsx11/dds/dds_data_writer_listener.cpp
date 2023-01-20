// -*- C++ -*-
/**
 * @file    dds_data_writer_listener.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_data_writer_listener.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

#include "dds_proxy_entity_manager.h"

namespace DDSX11
{
  DDS_DataWriterListener_proxy::DDS_DataWriterListener_proxy (
    IDL::traits<::DDS::DataWriterListener>::ref_type s)
    : impl_ (std::move (s))
  {
    DDSX11_LOG_TRACE ("DDS_DataWriterListener_proxy::DDS_DataWriterListener_proxy");
  }

  DDS_DataWriterListener_proxy::~DDS_DataWriterListener_proxy ()
  {
    DDSX11_LOG_TRACE ("DDS_DataWriterListener_proxy::~DDS_DataWriterListener_proxy");
  }

  IDL::traits<::DDS::DataWriter>::ref_type
  DDS_DataWriterListener_proxy::get_datawriter (
    DDS_Native::DDS::DataWriter *the_writer)
  {
    DDSX11_LOG_TRACE ("DDS_DataWriterListener_proxy::get_datawriter");

    IDL::traits<::DDS::DataWriter>::ref_type dw = this->dw_.lock ();
    if (!dw)
    {
      // Weak pointer was not set. It could be that it has been removed from the
      // internal map in the DDS_ProxyEntityManager. If so, the return value of
      // this method will be a nullptr; otherwise it will be a valid proxy to
      // the given native datawriter.
      this->dw_ =
        DDS_ProxyEntityManager::get_datawriter_proxy (the_writer).weak_reference ();
      dw = this->dw_.lock ();
    }
    return dw;
  }

  void
  DDS_DataWriterListener_proxy::on_offered_deadline_missed (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::OfferedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataWriterListener_proxy::on_offered_deadline_missed");

    IDL::traits<::DDS::DataWriter>::ref_type dw = this->get_datawriter (the_writer);
    if (dw)
    {
      this->impl_->on_offered_deadline_missed (std::move(dw),
        ::DDSX11::traits< ::DDS::OfferedDeadlineMissedStatus>::retn (status));
    }
  }

  void
  DDS_DataWriterListener_proxy::on_offered_incompatible_qos (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::OfferedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataWriterListener_proxy::on_offered_incompatible_qos");

    IDL::traits<::DDS::DataWriter>::ref_type dw = this->get_datawriter (the_writer);
    if (dw)
    {
      this->impl_->on_offered_incompatible_qos (std::move(dw),
        ::DDSX11::traits< ::DDS::OfferedIncompatibleQosStatus>::retn (status));
    }
  }

  void
  DDS_DataWriterListener_proxy::on_liveliness_lost (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::LivelinessLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataWriterListener_proxy::on_liveliness_lost");

    IDL::traits<::DDS::DataWriter>::ref_type dw = this->get_datawriter (the_writer);
    if (dw)
    {
      this->impl_->on_liveliness_lost (std::move(dw),
        ::DDSX11::traits< ::DDS::LivelinessLostStatus>::retn (status));
    }
  }

  void
  DDS_DataWriterListener_proxy::on_publication_matched (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::PublicationMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataWriterListener_proxy::on_publication_matched");

    IDL::traits<::DDS::DataWriter>::ref_type dw = this->get_datawriter (the_writer);
    if (dw)
    {
      this->impl_->on_publication_matched (std::move(dw),
        ::DDSX11::traits< ::DDS::PublicationMatchedStatus>::retn (status));
    }
  }

  IDL::traits<::DDS::DataWriterListener>::ref_type
  DDS_DataWriterListener_proxy::get_datawriterlistener ()
  {
    return this->impl_;
  }
}

