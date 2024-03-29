// -*- C++ -*-
/**
 * @file    dds4ccm_topic_listener_t.h
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   TopicListener for DDS4CCM CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_TOPICLISTENER_T_H_
#define DDS4CCM_TOPICLISTENER_T_H_

#include "dds4ccm/idl/dds4ccm_connector_status_listenerC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename EVT_STRATEGY>
    class TopicListener_T
      : public virtual IDL::traits<::DDS::TopicListener>::base_type
    {
    public:
      explicit TopicListener_T (const EVT_STRATEGY &evs);
      ~TopicListener_T () override = default;

      using uses_context_switch = typename EVT_STRATEGY::uses_context_switch;
      static constexpr const char* context_switch_type = EVT_STRATEGY::context_switch_type;

      void
      on_inconsistent_topic (
        IDL::traits<::DDS::Topic>::ref_type the_topic,
        const ::DDS::InconsistentTopicStatus & status) override;

      /// Helper method to determine which DDS mask we have to use
      static ::DDS::StatusMask get_mask (
        IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type error_listener);

    private:
      EVT_STRATEGY evs_;

      TopicListener_T() = delete;
      TopicListener_T(const TopicListener_T&) = delete;
      TopicListener_T(TopicListener_T&&) = delete;
      TopicListener_T& operator=(const TopicListener_T&) = delete;
      TopicListener_T& operator=(TopicListener_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_topic_listener_t.cpp"

#endif /* DDS4CCM_TOPICLISTENER_T_H_ */
