// -*- C++ -*-
/**
 * @file    dds_publisher.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_PUBLISHER_H_
#define DDSX11_IMPL_PUBLISHER_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class Publisher;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_Publisher_proxy
    : public virtual IDL::traits< ::DDS::Publisher>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::Publisher>
  {
  public:
    /// Constructor
    explicit DDS_Publisher_proxy (DDS_Native::DDS::Publisher * p);

    /// Destructor
    virtual ~DDS_Publisher_proxy () = default;

    IDL::traits< ::DDS::DataWriter>::ref_type
    create_datawriter (
      IDL::traits< ::DDS::Topic>::ref_type a_topic,
      const ::DDS::DataWriterQos & qos,
      IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    ::DDS::ReturnCode_t
    delete_datawriter (
      IDL::traits< ::DDS::DataWriter>::ref_type a_datawriter) override;

    IDL::traits< ::DDS::DataWriter>::ref_type
    lookup_datawriter (
      const std::string &impl_name) override;

    ::DDS::ReturnCode_t
    delete_contained_entities () override;

    ::DDS::ReturnCode_t
    set_qos (
      const ::DDS::PublisherQos & qos) override;

    ::DDS::ReturnCode_t
    get_qos (
      ::DDS::PublisherQos & qos) override;

    ::DDS::ReturnCode_t
    set_listener (
      IDL::traits< ::DDS::PublisherListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    IDL::traits< ::DDS::PublisherListener>::ref_type
    get_listener () override;

    ::DDS::ReturnCode_t
    suspend_publications () override;

    ::DDS::ReturnCode_t
    resume_publications () override;

    ::DDS::ReturnCode_t
    begin_coherent_changes () override;

    ::DDS::ReturnCode_t
    end_coherent_changes () override;

    ::DDS::ReturnCode_t
    wait_for_acknowledgments (
      const ::DDS::Duration_t & max_wait) override;

    IDL::traits< ::DDS::DomainParticipant>::ref_type
    get_participant () override;

    ::DDS::ReturnCode_t
    set_default_datawriter_qos (
      const ::DDS::DataWriterQos & qos) override;

    ::DDS::ReturnCode_t
    get_default_datawriter_qos (
      ::DDS::DataWriterQos & qos) override;

    ::DDS::ReturnCode_t
    copy_from_topic_qos (
      ::DDS::DataWriterQos & a_dataimpl_qos,
      const ::DDS::TopicQos & a_impl_qos) override;

    ::DDS::ReturnCode_t
    enable () override;

    IDL::traits< ::DDS::StatusCondition>::ref_type
    get_statuscondition () override;

    ::DDS::StatusMask
    get_status_changes () override;

    ::DDS::InstanceHandle_t
    get_instance_handle () override;

  private:
    DDS_Publisher_proxy() = delete;
    DDS_Publisher_proxy(const DDS_Publisher_proxy&) = delete;
    DDS_Publisher_proxy(DDS_Publisher_proxy&&) = delete;
    DDS_Publisher_proxy& operator=(const DDS_Publisher_proxy&) = delete;
    DDS_Publisher_proxy& operator=(DDS_Publisher_proxy&&) = delete;
  };

  using publisher_trait = entity_traits< ::DDS::Publisher, DDS_Publisher_proxy, DDS_Native::DDS::Publisher>;
}

#endif /* DDSX11_IMPL_PUBLISHER_H_ */
