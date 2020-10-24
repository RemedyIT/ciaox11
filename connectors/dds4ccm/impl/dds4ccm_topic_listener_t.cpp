// -*- C++ -*-
/**
 * @file    dds4ccm_topic_listener_t.cpp
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   TopicListener for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename EVT_STRATEGY>
    TopicListener_T<EVT_STRATEGY>::TopicListener_T (
      const EVT_STRATEGY &evs)
      : evs_ (evs)
    {
      DDS4CCM_LOG_TRACE("TopicListener_T::TopicListener_T");
    }

    template <typename EVT_STRATEGY>
    void
    TopicListener_T<EVT_STRATEGY>::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus & status)
    {
      DDS4CCM_LOG_TRACE("TopicListener_T::on_inconsistent_topic");

      DDS4CCM_LOG_DEBUG ("TopicListener_T::on_inconsistent_topic - "
        << IDL::traits< ::DDS::InconsistentTopicStatus>::write (status));

      this->evs_.handle_inconsistent_topic_event (
          the_topic, status);
    }

    template <typename EVT_STRATEGY>
    ::DDS::StatusMask
     TopicListener_T<EVT_STRATEGY>::get_mask (
      IDL::traits< CCM_DDS::ConnectorStatusListener>::ref_type error_listener)
    {
      DDS4CCM_LOG_TRACE("TopicListener_T::get_mask");

      ::DDS::StatusMask mask { ::DDS::STATUS_MASK_NONE };

      if (error_listener)
      {
        mask = ::DDS::INCONSISTENT_TOPIC_STATUS;
      }

      DDS4CCM_LOG_DEBUG ("TopicListener_T::get_mask - "
        << "Mask becomes <"
        << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask)
        << ">.");
      return mask;
    }
  }
}

