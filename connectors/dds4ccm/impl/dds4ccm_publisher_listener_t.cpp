// -*- C++ -*-
/**
 * @file    dds4ccm_publisher_listener_t.cpp
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   PublisherListener for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_utils.h"
#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename EVT_STRATEGY>
    PublisherListener_T<EVT_STRATEGY>::PublisherListener_T (
      const EVT_STRATEGY &evs)
      : evs_ (evs)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::PublisherListener");
    }

    template <typename EVT_STRATEGY>
    void
    PublisherListener_T<EVT_STRATEGY>::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type entity,
      ::DDS::StatusKind status_kind)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::on_unexpected_status");
      DDS4CCM_LOG_INFO("CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::on_unexpected_status" <<
          IDL::traits< ::DDS::StatusKind>::write<status_kind_formatter> (status_kind));

      this->evs_.handle_unexpected_status_event (std::move(entity), status_kind);
    }

    template <typename EVT_STRATEGY>
    void
    PublisherListener_T<EVT_STRATEGY>::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
      const ::DDS::OfferedDeadlineMissedStatus & status)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::on_offered_deadline_missed");

      DDS4CCM_LOG_INFO ("PublisherListener_T<EVT_STRATEGY>::on_offered_deadline_missed: "
        << IDL::traits< ::DDS::OfferedDeadlineMissedStatus>::write (status));

      this->evs_.handle_offered_deadline_missed_event (std::move(the_Writer), status);
    }

    template <typename EVT_STRATEGY>
    void
    PublisherListener_T<EVT_STRATEGY>::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
      const ::DDS::OfferedIncompatibleQosStatus & status)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::on_offered_incompatible_qos");

      DDS4CCM_LOG_INFO ("PublisherListener_T<EVT_STRATEGY>::on_offered_incompatible_qos - "
        << IDL::traits< ::DDS::OfferedIncompatibleQosStatus>::write (status));

      for (const ::DDS::QosPolicyCount& pol : status.policies ())
      {
        DDS4CCM_LOG_DEBUG ("\t\t" << IDL::traits< ::DDS::QosPolicyCount>::write (pol));
      }

      this->evs_.handle_offered_incompatible_qos_event (std::move(the_Writer), status);
    }

    template <typename EVT_STRATEGY>
    void
    PublisherListener_T<EVT_STRATEGY>::on_liveliness_lost (
      IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
      const ::DDS::LivelinessLostStatus & status)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::on_liveliness_lost");

      DDS4CCM_LOG_INFO ("PublisherListener_T<EVT_STRATEGY>::on_liveliness_lost - "
        << IDL::traits< ::DDS::LivelinessLostStatus>::write (status));

      this->on_unexpected_status (std::move(the_Writer), ::DDS::LIVELINESS_LOST_STATUS);
    }

    template <typename EVT_STRATEGY>
    void
    PublisherListener_T<EVT_STRATEGY>::on_publication_matched (
      IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
      const ::DDS::PublicationMatchedStatus & status)
    {
      DDS4CCM_LOG_TRACE("CIAOX11::DDS4CCM::PublisherListener_T<EVT_STRATEGY>::on_publication_matched");

      DDS4CCM_LOG_INFO ("PublisherListener_T<EVT_STRATEGY>::on_publication_matched - "
        << IDL::traits< ::DDS::PublicationMatchedStatus>::write (status));

      this->on_unexpected_status (std::move(the_Writer), ::DDS::PUBLICATION_MATCHED_STATUS);
    }

    template <typename EVT_STRATEGY>
    ::DDS::StatusMask
    PublisherListener_T<EVT_STRATEGY>::get_mask (
      IDL::traits< CCM_DDS::ConnectorStatusListener>::ref_type error_listener)
    {
      ::DDS::StatusMask mask { ::DDS::STATUS_MASK_NONE };

      if (error_listener)
      {
        mask = ::DDS::OFFERED_DEADLINE_MISSED_STATUS |
               ::DDS::OFFERED_INCOMPATIBLE_QOS_STATUS |
               ::DDS::LIVELINESS_LOST_STATUS |
               ::DDS::PUBLICATION_MATCHED_STATUS;
      }

      DDS4CCM_LOG_DEBUG ("PublisherListener_T<EVT_STRATEGY>::get_mask - "
        << "Mask becomes <"
        << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask)
        << ">.");
      return mask;
    }
  }
}
