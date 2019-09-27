// -*- C++ -*-
/**
 * @file    dds_data_reader_listener.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "dds_data_reader_listener.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

#include "dds/dds_proxy_entity_manager.h"

namespace DDSX11
{
  DDS_DataReaderListener_proxy::DDS_DataReaderListener_proxy (
    IDL::traits< ::DDS::DataReaderListener >::ref_type p)
    : impl_ (std::move (p))
  {
  }

  IDL::traits< ::DDS::DataReader>::ref_type
  DDS_DataReaderListener_proxy::get_datareader (
    DDS_Native::DDS::DataReader* the_reader)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::get_datareader");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->dr_.lock ();
    if (!dr)
    {
      // Weak pointer was not set. It could be that it has been removed from the
      // internal map in the DDS_ProxyEntityManager. If so, the return value of
      // this method will be a nullptr; otherwise it will be a valid proxy to
      // the given native datareader.
      this->dr_ =
        DDS_ProxyEntityManager::get_datareader_proxy (the_reader).weak_reference ();
      dr = this->dr_.lock ();
    }
    return dr;
  }

  void
  DDS_DataReaderListener_proxy::on_requested_deadline_missed (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::RequestedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::on_requested_deadline_missed");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->get_datareader (the_reader);
    if (dr)
    {
      this->impl_->on_requested_deadline_missed (std::move(dr),
        ::DDSX11::traits< ::DDS::RequestedDeadlineMissedStatus >::retn (status));
    }
  }

  void
  DDS_DataReaderListener_proxy::on_requested_incompatible_qos (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::RequestedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::on_requested_incompatible_qos");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->get_datareader (the_reader);
    if (dr)
    {
      this->impl_->on_requested_incompatible_qos (std::move(dr),
        ::DDSX11::traits< ::DDS::RequestedIncompatibleQosStatus >::retn (status));
    }
  }

  void
  DDS_DataReaderListener_proxy::on_sample_rejected (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::SampleRejectedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::on_sample_rejected");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->get_datareader (the_reader);
    if (dr)
    {
      this->impl_->on_sample_rejected (std::move(dr),
        ::DDSX11::traits< ::DDS::SampleRejectedStatus >::retn (status));
    }
  }

  void
  DDS_DataReaderListener_proxy::on_liveliness_changed (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::LivelinessChangedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::on_liveliness_changed");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->get_datareader (the_reader);
    if (dr)
    {
      this->impl_->on_liveliness_changed (std::move(dr),
        ::DDSX11::traits< ::DDS::LivelinessChangedStatus >::retn (status));
    }
  }

  void
  DDS_DataReaderListener_proxy::on_data_available(
    DDS_Native::DDS::DataReader *the_reader)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::on_data_available");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->get_datareader (the_reader);
    if (dr)
    {
      this->impl_->on_data_available (std::move(dr));
    }
  }

  void
  DDS_DataReaderListener_proxy::on_subscription_matched (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::SubscriptionMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::on_subscription_matched");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->get_datareader (the_reader);
    if (dr)
    {
      this->impl_->on_subscription_matched (std::move(dr),
        ::DDSX11::traits< ::DDS::SubscriptionMatchedStatus >::retn (status));
    }
  }

  void
  DDS_DataReaderListener_proxy::on_sample_lost (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::SampleLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DataReaderListener_proxy::on_sample_lost");

    IDL::traits< ::DDS::DataReader>::ref_type dr = this->get_datareader (the_reader);
    if (dr)
    {
      this->impl_->on_sample_lost (std::move(dr),
        ::DDSX11::traits< ::DDS::SampleLostStatus >::retn (status));
    }
  }

  IDL::traits< ::DDS::DataReaderListener >::ref_type
  DDS_DataReaderListener_proxy::get_datareaderlistener ()
  {
    return this->impl_;
  }
}
