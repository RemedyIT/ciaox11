// -*- C++ -*-
/**
 * @file    dds4ccm_subscriber_listener_t.h
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   SubscriberListener for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_SUBSCRIBERLISTENER_T_H_
#define DDS4CCM_SUBSCRIBERLISTENER_T_H_

#include "dds4ccm/idl/dds4ccm_connector_status_listenerC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename EVT_STRATEGY>
    class SubscriberListener_T final
      : public IDL::traits< ::DDS::SubscriberListener >::base_type
    {
    public:
      /// Constructor
      explicit SubscriberListener_T (
        const EVT_STRATEGY &evs);

      /// Destructor
      virtual ~SubscriberListener_T () = default;

      virtual void
      on_requested_incompatible_qos (
        IDL::traits< ::DDS::DataReader >::ref_type reader,
        const ::DDS::RequestedIncompatibleQosStatus & status) override;

      virtual void
      on_liveliness_changed (
        IDL::traits< ::DDS::DataReader >::ref_type reader,
        const ::DDS::LivelinessChangedStatus& status) override;

      virtual void
      on_sample_rejected (
        IDL::traits< ::DDS::DataReader >::ref_type reader,
        const ::DDS::SampleRejectedStatus& status) override;

      virtual void
      on_subscription_matched (
        IDL::traits< ::DDS::DataReader >::ref_type reader,
        const ::DDS::SubscriptionMatchedStatus& status) override;

      virtual void
      on_data_on_readers (
        IDL::traits< ::DDS::Subscriber >::ref_type subscriber) override;

      virtual void
      on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader >::ref_type ,
        const ::DDS::RequestedDeadlineMissedStatus & ) override;

      virtual void
      on_data_available (
        IDL::traits< ::DDS::DataReader >::ref_type ) override;

      virtual void
      on_sample_lost (
        IDL::traits< ::DDS::DataReader >::ref_type ,
        const ::DDS::SampleLostStatus & ) override;

      static ::DDS::StatusMask get_mask (
        IDL::traits< CCM_DDS::ConnectorStatusListener >::ref_type csl);

    private:

      void
      on_unexpected_status (
        IDL::traits< ::DDS::Entity >::ref_type entity,
        ::DDS::StatusKind status_kind);

      EVT_STRATEGY evs_;

      SubscriberListener_T() = delete;
      SubscriberListener_T(const SubscriberListener_T&) = delete;
      SubscriberListener_T(SubscriberListener_T&&) = delete;
      SubscriberListener_T& operator=(const SubscriberListener_T&) = delete;
      SubscriberListener_T& operator=(SubscriberListener_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_subscriber_listener_t.cpp"

#endif /* DDS4CCM_SUBSCRIBERLISTENER_T_H_ */
