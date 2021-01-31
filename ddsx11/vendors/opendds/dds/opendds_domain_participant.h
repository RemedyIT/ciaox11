// -*- C++ -*-
/**
 * @file    opendds_domain_participant.h
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_OpenDDS_DOMAIN_PARTICIPANT_H_
#define DDSX11_IMPL_OpenDDS_DOMAIN_PARTICIPANT_H_

#include "dds/dds_domain_participant.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    class DDSX11_IMPL_Export OpenDDS_DomainParticipant_proxy final
      : public virtual DDSX11::DDS_DomainParticipant_proxy
    {
    public:
      OpenDDS_DomainParticipant_proxy (
        DDS_Native::DDS::DomainParticipant *dp);

      virtual ~OpenDDS_DomainParticipant_proxy () = default;

      /**
       * @name  create_publisher_with_profile
       * @brief OpenDDS extensions. Create OpenDDS specific entities, using
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

      ::DDS::ReturnCode_t delete_topic (
        IDL::traits< ::DDS::Topic>::ref_type a_topic) override;

    private:
      OpenDDS_DomainParticipant_proxy() = delete;
      OpenDDS_DomainParticipant_proxy(const OpenDDS_DomainParticipant_proxy&) = delete;
      OpenDDS_DomainParticipant_proxy(OpenDDS_DomainParticipant_proxy&&) = delete;
      OpenDDS_DomainParticipant_proxy& operator=(const OpenDDS_DomainParticipant_proxy&) = delete;
      OpenDDS_DomainParticipant_proxy& operator=(OpenDDS_DomainParticipant_proxy&&) = delete;
    };
  }
}

#endif /* DDSX11_IMPL_OpenDDS_DOMAIN_PARTICIPANT_H_ */
