// -*- C++ -*-
/**
 * @file    dds4ccm_subscriber_listener_t.cpp
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   SubscriberListener for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_utils.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename EVT_STRATEGY>
    SubscriberListener_T<EVT_STRATEGY>::SubscriberListener_T (
      const EVT_STRATEGY &evs)
      : evs_ (evs)
    {
      DDS4CCM_LOG_TRACE("SubscriberListener_T<EVT_STRATEGY>::SubscriberListener");
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_requested_incompatible_qos (
      IDL::traits<::DDS::DataReader>::ref_type reader,
      const ::DDS::RequestedIncompatibleQosStatus & status)
    {
      DDS4CCM_LOG_TRACE("SubscriberListener_T<EVT_STRATEGY>::on_requested_incompatible_qos");

      DDS4CCM_LOG_DEBUG ("SubscriberListener_T<EVT_STRATEGY>::on_requested_incompatible_qos - "
        << IDL::traits<::DDS::RequestedIncompatibleQosStatus>::write (status));

      for (const ::DDS::QosPolicyCount& pol : status.policies ())
      {
        DDS4CCM_LOG_DEBUG ("\t\t"
          << IDL::traits<::DDS::QosPolicyCount>::write (pol));
      }

      this->evs_.handle_requested_incompatible_qos_event (std::move(reader), status);
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_unexpected_status (
      IDL::traits<::DDS::Entity>::ref_type entity,
      ::DDS::StatusKind status_kind)
    {
      DDS4CCM_LOG_TRACE("SubscriberListener_T<EVT_STRATEGY>::on_unexpected_status");

      this->evs_.handle_unexpected_status_event (std::move(entity), status_kind);
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_liveliness_changed (
      IDL::traits<::DDS::DataReader>::ref_type reader,
      const ::DDS::LivelinessChangedStatus& status)
    {
      DDS4CCM_LOG_TRACE("SubscriberListener_T<EVT_STRATEGY>::on_liveliness_changed");

      DDS4CCM_LOG_DEBUG ("SubscriberListener_T<EVT_STRATEGY>::on_liveliness_changed - "
        << IDL::traits<::DDS::LivelinessChangedStatus>::write (status));

      this->on_unexpected_status (std::move(reader), ::DDS::LIVELINESS_CHANGED_STATUS);
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_sample_rejected (
      IDL::traits<::DDS::DataReader>::ref_type reader,
      const ::DDS::SampleRejectedStatus & status)
    {
      DDS4CCM_LOG_TRACE("SubscriberListener_T<EVT_STRATEGY>::on_sample_rejected");

      DDS4CCM_LOG_DEBUG ("SubscriberListener_T<EVT_STRATEGY>::on_sample_rejected - "
        << IDL::traits<::DDS::SampleRejectedStatus>::write (status));

      this->evs_.handle_sample_rejected_event (std::move(reader), status);
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_subscription_matched (
      IDL::traits<::DDS::DataReader>::ref_type reader,
      const ::DDS::SubscriptionMatchedStatus & status)
    {
      DDS4CCM_LOG_TRACE("SubscriberListener_T<EVT_STRATEGY>::on_subscription_matched");

      DDS4CCM_LOG_DEBUG ("SubscriberListener_T<EVT_STRATEGY>::on_subscription_matched - "
        << IDL::traits<::DDS::SubscriptionMatchedStatus>::write (status));

      this->on_unexpected_status (std::move(reader), ::DDS::SUBSCRIPTION_MATCHED_STATUS);
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_data_on_readers (
      IDL::traits<::DDS::Subscriber>::ref_type)
    {
      DDS4CCM_LOG_TRACE("SubscriberListener_T<EVT_STRATEGY>::on_data_on_readers");
      //do nothing by design
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_requested_deadline_missed (
      IDL::traits<::DDS::DataReader>::ref_type,
      const ::DDS::RequestedDeadlineMissedStatus &)
    {
      DDS4CCM_LOG_ERROR ("SubscriberListener_T<EVT_STRATEGY>::on_requested_deadline_missed - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_data_available (
      IDL::traits<::DDS::DataReader>::ref_type)
    {
      DDS4CCM_LOG_ERROR ("SubscriberListener_T<EVT_STRATEGY>::on_data_available - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    void
    SubscriberListener_T<EVT_STRATEGY>::on_sample_lost (
      IDL::traits<::DDS::DataReader>::ref_type,
      const ::DDS::SampleLostStatus &)
    {
      DDS4CCM_LOG_ERROR ("SubscriberListener_T<EVT_STRATEGY>::on_sample_lost - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    ::DDS::StatusMask
    SubscriberListener_T<EVT_STRATEGY>::get_mask (
      IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type csl)
    {
      ::DDS::StatusMask mask { ::DDS::STATUS_MASK_NONE };

      if (csl)
      {
        mask = ::DDS::REQUESTED_INCOMPATIBLE_QOS_STATUS |
               ::DDS::SAMPLE_REJECTED_STATUS |
               ::DDS::LIVELINESS_CHANGED_STATUS |
               ::DDS::SUBSCRIPTION_MATCHED_STATUS;
      }

      DDS4CCM_LOG_DEBUG ("SubscriberListener_T<EVT_STRATEGY>::get_mask - "
        << "Mask becomes <"
        << IDL::traits<::DDS::StatusMask>::write<status_mask_formatter> (mask)
        << ">.");
    return mask;
    }
  }
}

