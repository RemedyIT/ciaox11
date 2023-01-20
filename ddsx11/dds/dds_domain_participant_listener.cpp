// -*- C++ -*-
/**
 * @file    dds_domain_participant_listener.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_domain_participant_listener.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_type_support.h"
#include "dds/dds_vendor_adapter.h"
#include "dds/dds_proxy_entity_manager.h"
#include "dds/dds_topic.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  DDS_DomainParticipantListener_proxy::DDS_DomainParticipantListener_proxy (
    IDL::traits<::DDS::DomainParticipantListener>::ref_type p)
    : impl_ (std::move (p))
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::DDS_DomainParticipantListener_proxy");
  }

  DDS_DomainParticipantListener_proxy::~DDS_DomainParticipantListener_proxy ()
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::~DDS_DomainParticipantListener_proxy");
  }

  void
  DDS_DomainParticipantListener_proxy::on_inconsistent_topic (
    DDS_Native::DDS::Topic * tp,
    const DDS_Native::DDS::InconsistentTopicStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_inconsistent_topic");

    IDL::traits<::DDS::Topic>::ref_type topic =
      TAOX11_CORBA::make_reference<DDS_Topic_proxy> (tp);

    this->impl_->on_inconsistent_topic (std::move(topic),
      ::DDSX11::traits< ::DDS::InconsistentTopicStatus>::retn (status));
  }

  void
  DDS_DomainParticipantListener_proxy::on_requested_deadline_missed (
    DDS_Native::DDS::DataReader *the_reader,
    const DDS_Native::DDS::RequestedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_requested_deadline_missed");

    IDL::traits<::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_requested_deadline_missed (std::move(dr),
        ::DDSX11::traits< ::DDS::RequestedDeadlineMissedStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_requested_incompatible_qos (
    DDS_Native::DDS::DataReader *the_reader,
    const DDS_Native::DDS::RequestedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_requested_incompatible_qos");

    IDL::traits<::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_requested_incompatible_qos (std::move(dr),
        ::DDSX11::traits< ::DDS::RequestedIncompatibleQosStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_sample_rejected (
    DDS_Native::DDS::DataReader *the_reader,
    const DDS_Native::DDS::SampleRejectedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_sample_rejected");

    IDL::traits<::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_sample_rejected (std::move(dr),
        ::DDSX11::traits< ::DDS::SampleRejectedStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_liveliness_changed (
    DDS_Native::DDS::DataReader *the_reader,
    const DDS_Native::DDS::LivelinessChangedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_liveliness_changed");

    IDL::traits<::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_liveliness_changed (std::move(dr),
        ::DDSX11::traits< ::DDS::LivelinessChangedStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_data_available (
    DDS_Native::DDS::DataReader *the_reader)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_data_available");

    IDL::traits<::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_data_available (std::move(dr));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_subscription_matched (
    DDS_Native::DDS::DataReader *the_reader,
    const DDS_Native::DDS::SubscriptionMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_subscription_matched");

    IDL::traits<::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_subscription_matched (std::move(dr),
        ::DDSX11::traits< ::DDS::SubscriptionMatchedStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_sample_lost (
    DDS_Native::DDS::DataReader *the_reader,
    const DDS_Native::DDS::SampleLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_sample_lost");

    IDL::traits<::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (the_reader);
    if (dr)
    {
      this->impl_->on_sample_lost (std::move(dr),
        ::DDSX11::traits< ::DDS::SampleLostStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_offered_deadline_missed (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::OfferedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_offered_deadline_missed");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_offered_deadline_missed (std::move(dw),
        ::DDSX11::traits< ::DDS::OfferedDeadlineMissedStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_offered_incompatible_qos (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::OfferedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_offered_incompatible_qos");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_offered_incompatible_qos (std::move(dw),
        ::DDSX11::traits< ::DDS::OfferedIncompatibleQosStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_liveliness_lost (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::LivelinessLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_liveliness_lost");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_liveliness_lost (std::move(dw),
        ::DDSX11::traits< ::DDS::LivelinessLostStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_publication_matched (
    DDS_Native::DDS::DataWriter *the_writer,
    const DDS_Native::DDS::PublicationMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_publication_matched");

    IDL::traits<::DDS::DataWriter>::ref_type dw =
      DDS_ProxyEntityManager::get_datawriter_proxy (the_writer);
    if (dw)
    {
      this->impl_->on_publication_matched (std::move(dw),
        ::DDSX11::traits< ::DDS::PublicationMatchedStatus>::retn (status));
    }
  }

  void
  DDS_DomainParticipantListener_proxy::on_data_on_readers (
    DDS_Native::DDS::Subscriber* subscriber)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantListener_proxy::on_data_on_readers");

    IDL::traits<::DDS::Subscriber>::ref_type sub =
      DDS_ProxyEntityManager::get_subscriber_proxy (subscriber);
    if (sub)
    {
      this->impl_->on_data_on_readers (std::move(sub));
    }
  }

  IDL::traits<::DDS::DomainParticipantListener>::ref_type
  DDS_DomainParticipantListener_proxy::get_domainparticipantlistener ()
  {
    return this->impl_;
  }
}

