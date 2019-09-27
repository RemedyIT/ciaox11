// -*- C++ -*-
/**
 * @file    dds_domain_participant_listener.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_IMPL_DOMAIN_PARTICIPANT_LISTENER_H_
#define DDSX11_IMPL_DOMAIN_PARTICIPANT_LISTENER_H_

#include "dds/dds_common.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_listener_guard_t.h"

namespace DDSX11
{
  class DDS_DomainParticipantListener_proxy final
    : public DDS_Native::DDS::DomainParticipantListener
  {
  public:
    /// Constructor
    DDS_DomainParticipantListener_proxy (
      IDL::traits< ::DDS::DomainParticipantListener >::ref_type p);

    /// Destructor
    virtual ~DDS_DomainParticipantListener_proxy () = default;

    virtual void
    on_inconsistent_topic (
      DDS_Native::DDS::Topic*,
      const DDS_Native::DDS::InconsistentTopicStatus & ) override;

    virtual void
    on_requested_deadline_missed (
      DDS_Native::DDS::DataReader *,
      const DDS_Native::DDS::RequestedDeadlineMissedStatus & ) override;

    virtual void
    on_requested_incompatible_qos (
      DDS_Native::DDS::DataReader *,
      const DDS_Native::DDS::RequestedIncompatibleQosStatus & ) override;

    virtual void
    on_sample_rejected (
      DDS_Native::DDS::DataReader*,
      const DDS_Native::DDS::SampleRejectedStatus & ) override;

    virtual void
    on_liveliness_changed (
      DDS_Native::DDS::DataReader *,
      const DDS_Native::DDS::LivelinessChangedStatus & ) override;

    virtual void
    on_data_available (
      DDS_Native::DDS::DataReader* ) override;

    virtual void
    on_subscription_matched (
      DDS_Native::DDS::DataReader *,
      const DDS_Native::DDS::SubscriptionMatchedStatus & ) override;

    virtual void
    on_sample_lost (
      DDS_Native::DDS::DataReader *,
      const DDS_Native::DDS::SampleLostStatus & ) override;

    virtual void
    on_offered_deadline_missed (
      DDS_Native::DDS::DataWriter *,
      const DDS_Native::DDS::OfferedDeadlineMissedStatus & ) override;

    virtual void
    on_offered_incompatible_qos (
      DDS_Native::DDS::DataWriter *,
      const DDS_Native::DDS::OfferedIncompatibleQosStatus & ) override;

    virtual void
    on_liveliness_lost (
      DDS_Native::DDS::DataWriter *,
      const DDS_Native::DDS::LivelinessLostStatus & ) override;

    virtual void
    on_publication_matched (
      DDS_Native::DDS::DataWriter *,
      const DDS_Native::DDS::PublicationMatchedStatus & ) override;

    virtual void
    on_data_on_readers (
      DDS_Native::DDS::Subscriber* ) override;

    IDL::traits< ::DDS::DomainParticipantListener >::ref_type
    get_domainparticipantlistener ();

  private:
    IDL::traits< ::DDS::DomainParticipantListener >::ref_type impl_;

    DDS_DomainParticipantListener_proxy() = delete;
    DDS_DomainParticipantListener_proxy(const DDS_DomainParticipantListener_proxy&) = delete;
    DDS_DomainParticipantListener_proxy(DDS_DomainParticipantListener_proxy&&) = delete;
    DDS_DomainParticipantListener_proxy& operator=(const DDS_DomainParticipantListener_proxy&) = delete;
    DDS_DomainParticipantListener_proxy& operator=(DDS_DomainParticipantListener_proxy&&) = delete;
  };

  typedef DDSX11_Listener_Guard_T<
    DDS_Native::DDS::DomainParticipantListener,
    ::DDS::DomainParticipantListener> DomainParticipantListener_Guard;
}

#endif /* DDSX11_IMPL_DOMAIN_PARTICIPANT_LISTENER_H_ */
