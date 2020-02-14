// -*- C++ -*-
/**
 * @file    dds_subscriber_listener.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_subscriber.h"
#include "dds/dds_domain_participant.h"
#include "dds/dds_subscriber_listener.h"
#include "dds/dds_vendor_adapter.h"
#include "dds/dds_proxy_entity_manager.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  DDS_SubscriberListener_proxy::DDS_SubscriberListener_proxy (
    IDL::traits< ::DDS::SubscriberListener>::ref_type p)
    : impl_ (std::move (p))
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::DDS_SubscriberListener_proxy");
  }

  void
  DDS_SubscriberListener_proxy::on_data_on_readers (
    DDS_Native::DDS::Subscriber* the_subscriber)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_data_on_readers");

    IDL::traits< ::DDS::Subscriber>::ref_type sub =
      DDS_ProxyEntityManager::get_subscriber_proxy (the_subscriber);
    if (sub)
    {
      this->impl_->on_data_on_readers (std::move(sub));
    }
  }

  void
  DDS_SubscriberListener_proxy::on_requested_deadline_missed (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::RequestedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_requested_deadline_missed");

    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_requested_deadline_missed (dr,
        ::DDSX11::traits< ::DDS::RequestedDeadlineMissedStatus >::retn (status));
    }
  }

  void
  DDS_SubscriberListener_proxy::on_requested_incompatible_qos (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::RequestedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_requested_incompatible_qos");

    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_requested_incompatible_qos (std::move(dr),
        ::DDSX11::traits< ::DDS::RequestedIncompatibleQosStatus >::retn (status));
    }
  }

  void
  DDS_SubscriberListener_proxy::on_sample_rejected (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::SampleRejectedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_sample_rejected");

    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_sample_rejected (std::move(dr),
        ::DDSX11::traits< ::DDS::SampleRejectedStatus >::retn (status));
    }
  }

  void
  DDS_SubscriberListener_proxy::on_liveliness_changed (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::LivelinessChangedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_liveliness_changed");

    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_liveliness_changed (std::move(dr),
        ::DDSX11::traits< ::DDS::LivelinessChangedStatus >::retn (status));
    }
  }

  void
  DDS_SubscriberListener_proxy::on_data_available (
    DDS_Native::DDS::DataReader* the_reader)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_data_available");

    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_data_available (std::move(dr));
    }
  }

  void
  DDS_SubscriberListener_proxy::on_subscription_matched (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::SubscriptionMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_subscription_matched");

    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_subscription_matched (std::move(dr),
        ::DDSX11::traits< ::DDS::SubscriptionMatchedStatus >::retn (status));
    }
  }

  void
  DDS_SubscriberListener_proxy::on_sample_lost (
    DDS_Native::DDS::DataReader* the_reader,
    const DDS_Native::DDS::SampleLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_SubscriberListener_proxy::on_sample_lost");

    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_sample_lost (std::move(dr),
        ::DDSX11::traits< ::DDS::SampleLostStatus >::retn (status));
    }
  }

  IDL::traits< ::DDS::SubscriberListener>::ref_type
  DDS_SubscriberListener_proxy::get_subscriber_listener ()
  {
    return this->impl_;
  }
}
