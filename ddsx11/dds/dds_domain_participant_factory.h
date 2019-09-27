// -*- C++ -*-
/**
 * @file    dds_domain_participant_factory.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_IMPL_DOMAIN_PARTICIPANT_FACTORY_H_
#define DDSX11_IMPL_DOMAIN_PARTICIPANT_FACTORY_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class DomainParticipantFactory;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_DomainParticipantFactory_proxy
    : public virtual IDL::traits< ::DDS::DomainParticipantFactory>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::DomainParticipantFactory>
  {
  public:
    /// Constructor
    DDS_DomainParticipantFactory_proxy (DDS_Native::DDS::DomainParticipantFactory * dpf);

    /// Destructor
    virtual ~DDS_DomainParticipantFactory_proxy () = default;

    virtual IDL::traits< ::DDS::DomainParticipant >::ref_type
    create_participant (
      ::DDS::DomainId_t domain_id,
      const ::DDS::DomainParticipantQos & qos,
      IDL::traits< ::DDS::DomainParticipantListener >::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    virtual ::DDS::ReturnCode_t
    delete_participant (
      IDL::traits< ::DDS::DomainParticipant >::ref_type a_participant) override;

    virtual IDL::traits< ::DDS::DomainParticipant >::ref_type
    lookup_participant (
      ::DDS::DomainId_t domain_id) override;

    virtual ::DDS::ReturnCode_t
    set_default_participant_qos (
      const ::DDS::DomainParticipantQos & qos) override;

    virtual ::DDS::ReturnCode_t
    get_default_participant_qos (
      ::DDS::DomainParticipantQos & qos) override;

    virtual ::DDS::ReturnCode_t
    set_qos (
      const ::DDS::DomainParticipantFactoryQos & qos) override;

    virtual ::DDS::ReturnCode_t
    get_qos (
      ::DDS::DomainParticipantFactoryQos & qos) override;

  private:
    DDS_DomainParticipantFactory_proxy() = delete;
    DDS_DomainParticipantFactory_proxy(const DDS_DomainParticipantFactory_proxy&) = delete;
    DDS_DomainParticipantFactory_proxy(DDS_DomainParticipantFactory_proxy&&) = delete;
    DDS_DomainParticipantFactory_proxy& operator=(const DDS_DomainParticipantFactory_proxy&) = delete;
    DDS_DomainParticipantFactory_proxy& operator=(DDS_DomainParticipantFactory_proxy&&) = delete;
  };
}

#endif /* DDSX11_IMPL_DOMAIN_PARTICIPANT_FACTORY_H_ */
