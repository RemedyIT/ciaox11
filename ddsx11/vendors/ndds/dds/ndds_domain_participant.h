// -*- C++ -*-
/**
 * @file    ndds_domain_participant.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_DOMAIN_PARTICIPANT_H_
#define DDSX11_IMPL_NDDS_DOMAIN_PARTICIPANT_H_

#include "dds/dds_domain_participant.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    class DDSX11_IMPL_Export NDDS_DomainParticipant_proxy final
      : public virtual DDSX11::DDS_DomainParticipant_proxy
    {
    public:
      explicit NDDS_DomainParticipant_proxy (DDS_Native::DDS::DomainParticipant *dp);

      ~NDDS_DomainParticipant_proxy () override = default;

      /**
       * @name  create_publisher_with_profile
       * @brief NDDS extensions. Create NDDS specific entities, using
       *        the QOS profile string
       */
      //@{
      IDL::traits< ::DDS::Publisher>::ref_type
      create_publisher_with_profile (
        const std::string &qos_profile,
        IDL::traits< ::DDS::PublisherListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;

      IDL::traits< ::DDS::Subscriber>::ref_type
      create_subscriber_with_profile(
        const std::string &qos_profile,
        IDL::traits< ::DDS::SubscriberListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;

      IDL::traits< ::DDS::Topic>::ref_type
      create_topic_with_profile (
        const std::string &topic_name,
        const std::string &type_name,
        const std::string &qos_profile,
        IDL::traits< ::DDS::TopicListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;
      //@}

    private:
      NDDS_DomainParticipant_proxy() = delete;
      NDDS_DomainParticipant_proxy(const NDDS_DomainParticipant_proxy&) = delete;
      NDDS_DomainParticipant_proxy(NDDS_DomainParticipant_proxy&&) = delete;
      NDDS_DomainParticipant_proxy& operator=(const NDDS_DomainParticipant_proxy&) = delete;
      NDDS_DomainParticipant_proxy& operator=(NDDS_DomainParticipant_proxy&&) = delete;
    };
  }
}

#endif /* DDSX11_IMPL_NDDS_DOMAIN_PARTICIPANT_H_ */
