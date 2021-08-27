// -*- C++ -*-
/**
 * @file    opendds_domain_participant_factory.h
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_OpenDDS_DOMAIN_PARTICIPANT_FACTORY_H_
#define DDSX11_IMPL_OpenDDS_DOMAIN_PARTICIPANT_FACTORY_H_

#include "dds/dds_domain_participant_factory.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    class DDSX11_IMPL_Export OpenDDS_DomainParticipantFactory_proxy final
      : public virtual DDSX11::DDS_DomainParticipantFactory_proxy
    {
    public:
      explicit OpenDDS_DomainParticipantFactory_proxy (DDS_Native::DDS::DomainParticipantFactory * dpf);

      ~OpenDDS_DomainParticipantFactory_proxy () override = default;

      /**
       * @name  create_participant_with_profile
       * @brief OpenDDS extension. Creates a domain participant, using
       *        the QOS profile string
       */
      IDL::traits< ::DDS::DomainParticipant>::ref_type
      create_participant_with_profile (
        ::DDS::DomainId_t domain_id,
        const std::string &qos_profile,
        IDL::traits< ::DDS::DomainParticipantListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;

      ::DDS::ReturnCode_t finalize_instance () override;

      /**
       * @name  set_default_participant_qos_with_profile
       * @brief OpenDDS extension.
       */
      ::DDS::ReturnCode_t
      set_default_participant_qos_with_profile (const std::string &qos_profile) override;

    private:
      OpenDDS_DomainParticipantFactory_proxy() = delete;
      OpenDDS_DomainParticipantFactory_proxy(const OpenDDS_DomainParticipantFactory_proxy&) = delete;
      OpenDDS_DomainParticipantFactory_proxy(OpenDDS_DomainParticipantFactory_proxy&&) = delete;
      OpenDDS_DomainParticipantFactory_proxy& operator=(const OpenDDS_DomainParticipantFactory_proxy&) = delete;
      OpenDDS_DomainParticipantFactory_proxy& operator=(OpenDDS_DomainParticipantFactory_proxy&&) = delete;
    };
  }
}

#endif /* DDSX11_IMPL_OpenDDS_DOMAIN_PARTICIPANT_FACTORY_H_ */
