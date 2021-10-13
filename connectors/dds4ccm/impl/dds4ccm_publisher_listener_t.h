// -*- C++ -*-
/**
 * @file    dds4ccm_publisher_listener_t.h
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   PublisherListener_T for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_PUBLISHERLISTENER_T_H_
#define DDS4CCM_PUBLISHERLISTENER_T_H_

#include "dds4ccm/idl/dds4ccm_connector_status_listenerC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename EVT_STRATEGY>
    class PublisherListener_T
      : public IDL::traits< ::DDS::PublisherListener>::base_type
    {
    public:
      /// Constructor
      explicit PublisherListener_T (const EVT_STRATEGY &evs);

      /// Destructor
      ~PublisherListener_T () override = default;

      using uses_context_switch = typename EVT_STRATEGY::uses_context_switch;
      static constexpr const char* context_switch_type = EVT_STRATEGY::context_switch_type;

      void
      on_offered_deadline_missed (
        IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
        const ::DDS::OfferedDeadlineMissedStatus & status) override;

      void
      on_liveliness_lost (
        IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
        const ::DDS::LivelinessLostStatus & status) override;

      void
      on_offered_incompatible_qos (
        IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
        const ::DDS::OfferedIncompatibleQosStatus & status) override;

      void
      on_publication_matched (
        IDL::traits< ::DDS::DataWriter>::ref_type the_Writer,
        const ::DDS::PublicationMatchedStatus & status) override;

      /// Helper method to determine which DDS mask we have to use
      static ::DDS::StatusMask get_mask (
        IDL::traits< CCM_DDS::ConnectorStatusListener>::ref_type error_listener);

    protected:
      virtual void
      on_unexpected_status (
        IDL::traits< ::DDS::Entity>::ref_type entity,
        ::DDS::StatusKind status_kind);

    private:
      EVT_STRATEGY evs_;

      PublisherListener_T() = delete;
      PublisherListener_T(const PublisherListener_T&) = delete;
      PublisherListener_T(PublisherListener_T&&) = delete;
      PublisherListener_T& operator=(const PublisherListener_T&) = delete;
      PublisherListener_T& operator=(PublisherListener_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_publisher_listener_t.cpp"

#endif /* DDS4CCM_PUBLISHERLISTENER_T_H_ */

