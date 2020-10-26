// -*- C++ -*-
/**
 * @file    dds4ccm_port_status_listener_t.cpp
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   Implementation of the DDS4CCM connector
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
    PortStatusListener_T<EVT_STRATEGY>::PortStatusListener_T (
        const EVT_STRATEGY& evs)
      : evs_ (evs)
    {
      DDS4CCM_LOG_TRACE ("PortStatusListener_T<EVT_STRATEGY>::PortStatusListener_T");
    }

    template <typename EVT_STRATEGY>
    void
    PortStatusListener_T<EVT_STRATEGY>::on_requested_deadline_missed (
     IDL::traits< ::DDS::DataReader>::ref_type the_reader,
     const ::DDS::RequestedDeadlineMissedStatus & status)
    {
      DDS4CCM_LOG_TRACE ("PortStatusListener_T<EVT_STRATEGY>::on_requested_deadline_missed");

      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::on_requested_deadline_missed - "
        << IDL::traits< ::DDS::RequestedDeadlineMissedStatus>::write (status));

      this->evs_.handle_requested_deadline_missed_event (std::move(the_reader), status);
    }

    template <typename EVT_STRATEGY>
    void
    PortStatusListener_T<EVT_STRATEGY>::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus & status)
    {
      DDS4CCM_LOG_TRACE ("PortStatusListener_T<EVT_STRATEGY>::on_sample_lost");

      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::on_sample_lost - "
        << IDL::traits< ::DDS::SampleLostStatus>::write (status));

      this->evs_.handle_sample_lost_event (std::move(the_reader), status);
    }

    template <typename EVT_STRATEGY>
    void
    PortStatusListener_T<EVT_STRATEGY>::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type ,
      const ::DDS::RequestedIncompatibleQosStatus & )
    {
      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::on_requested_incompatible_qos - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    void
    PortStatusListener_T<EVT_STRATEGY>::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type ,
      const ::DDS::SampleRejectedStatus & )
    {
      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::on_sample_rejected - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    void
    PortStatusListener_T<EVT_STRATEGY>::on_liveliness_changed (
      IDL::traits< ::DDS::DataReader>::ref_type ,
      const ::DDS::LivelinessChangedStatus & )
    {
      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::on_liveliness_changed - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    void
    PortStatusListener_T<EVT_STRATEGY>::on_data_available (
      IDL::traits< ::DDS::DataReader>::ref_type )
    {
      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::on_data_available - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    void
    PortStatusListener_T<EVT_STRATEGY>::on_subscription_matched (
      IDL::traits< ::DDS::DataReader>::ref_type ,
      const ::DDS::SubscriptionMatchedStatus & )
    {
      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::on_subscription_matched - "
        << "Unexpected callback occurred.");
    }

    template <typename EVT_STRATEGY>
    ::DDS::StatusMask
    PortStatusListener_T<EVT_STRATEGY>::get_mask (
      IDL::traits< CCM_DDS::PortStatusListener>::ref_type psl)
    {
      DDS4CCM_LOG_TRACE ("PortStatusListener_T<EVT_STRATEGY>::get_mask");

      ::DDS::StatusMask mask { ::DDS::STATUS_MASK_NONE };
      if (psl)
      {
        mask = ::DDS::REQUESTED_DEADLINE_MISSED_STATUS |
               ::DDS::SAMPLE_LOST_STATUS;
      }

      DDS4CCM_LOG_DEBUG ("PortStatusListener_T<EVT_STRATEGY>::get_mask - "
        << "Mask becomes <"
        << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask)
        << ">.");
      return mask;
    }
  }
}
