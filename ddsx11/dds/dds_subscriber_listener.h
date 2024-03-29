// -*- C++ -*-
/**
 * @file    dds_subscriber_listener.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_SUBSCRIBER_LISTENER_H_
#define DDSX11_IMPL_SUBSCRIBER_LISTENER_H_

#include "dds/dds_common.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_listener_guard_t.h"
#include "dds/dds_proxy_traits_t.h"

namespace DDSX11
{
  class DDS_SubscriberListener_proxy final
    : public DDS_Native::DDS::SubscriberListener
  {
  public:
    /// Constructor
    explicit DDS_SubscriberListener_proxy (
      IDL::traits<::DDS::SubscriberListener>::ref_type s);

    /// Destructor
    ~DDS_SubscriberListener_proxy () override;

    void
    on_requested_deadline_missed (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::RequestedDeadlineMissedStatus & status) override;

    void
    on_requested_incompatible_qos (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::RequestedIncompatibleQosStatus & status) override;

    void
    on_sample_rejected (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::SampleRejectedStatus & status) override;

    void
    on_liveliness_changed (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::LivelinessChangedStatus & status) override;

    void
    on_data_available (
      DDS_Native::DDS::DataReader* the_reader) override;

    void
    on_subscription_matched (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::SubscriptionMatchedStatus & status) override;

    void
    on_sample_lost (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::SampleLostStatus & status) override;

    void
    on_data_on_readers (
      DDS_Native::DDS::Subscriber* the_subscriber) override;

    IDL::traits<::DDS::SubscriberListener>::ref_type
    get_subscriber_listener ();

  private:
    IDL::traits<::DDS::SubscriberListener>::ref_type impl_;

    DDS_SubscriberListener_proxy() = delete;
    DDS_SubscriberListener_proxy(const DDS_SubscriberListener_proxy&) = delete;
    DDS_SubscriberListener_proxy(DDS_SubscriberListener_proxy&&) = delete;
    DDS_SubscriberListener_proxy& operator=(const DDS_SubscriberListener_proxy&) = delete;
    DDS_SubscriberListener_proxy& operator=(DDS_SubscriberListener_proxy&&) = delete;
  };

  using SubscriberListener_Guard = DDSX11_Listener_Guard_T<DDS_Native::DDS::SubscriberListener>;

  using native_subscriberlistener_trait =
    native_entity_traits< ::DDS::SubscriberListener, DDS_SubscriberListener_proxy, DDS_Native::DDS::SubscriberListener>;
}

#endif /* DDSX11_IMPL_SUBSCRIBER_LISTENER_H_ */

