// -*- C++ -*-
/**
 * @file    dds_domain_participant.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DOMAIN_PARTICIPANT_H_
#define DDSX11_IMPL_DOMAIN_PARTICIPANT_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class DomainParticipant;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_DomainParticipant_proxy
    : public virtual IDL::traits<::DDS::DomainParticipant>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::DomainParticipant>
  {
  public:
    /// Constructor
    explicit DDS_DomainParticipant_proxy (DDS_Native::DDS::DomainParticipant * dp);

    /// Destructor
    ~DDS_DomainParticipant_proxy () override = default;

    IDL::traits<::DDS::Publisher>::ref_type
    create_publisher (
      const ::DDS::PublisherQos & qos,
      IDL::traits<::DDS::PublisherListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    ::DDS::ReturnCode_t
    delete_publisher (
      IDL::traits<::DDS::Publisher>::ref_type p) override;

    IDL::traits<::DDS::Subscriber>::ref_type
    create_subscriber (
      const ::DDS::SubscriberQos & qos,
      IDL::traits<::DDS::SubscriberListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    ::DDS::ReturnCode_t
    delete_subscriber (
      IDL::traits<::DDS::Subscriber>::ref_type s) override;

    IDL::traits<::DDS::Subscriber>::ref_type
    get_builtin_subscriber () override;

    IDL::traits<::DDS::Topic>::ref_type
    create_topic (
      const std::string &impl_name,
      const std::string &type_name,
      const ::DDS::TopicQos &qos,
      IDL::traits<::DDS::TopicListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    ::DDS::ReturnCode_t
    delete_topic (
      IDL::traits<::DDS::Topic>::ref_type a_topic) override;

    IDL::traits<::DDS::Topic>::ref_type
    find_topic (
      const std::string &impl_name,
      const ::DDS::Duration_t & timeout) override;

    IDL::traits<::DDS::TopicDescription>::ref_type
    lookup_topicdescription (
      const std::string &name) override;

    IDL::traits<::DDS::ContentFilteredTopic>::ref_type
    create_contentfilteredtopic (
      const std::string &name,
      IDL::traits<::DDS::Topic>::ref_type related_topic,
      const std::string &filter_expression,
      const ::DDS::StringSeq & expression_parameters) override;

    ::DDS::ReturnCode_t
    delete_contentfilteredtopic (
      IDL::traits<::DDS::ContentFilteredTopic>::ref_type a_contentfilteredtopic) override;

    IDL::traits<::DDS::MultiTopic>::ref_type
    create_multitopic (
      const std::string &name,
      const std::string &type_name,
      const std::string &subscription_expression,
      const ::DDS::StringSeq & expression_parameters) override;

    ::DDS::ReturnCode_t
    delete_multitopic (
      IDL::traits<::DDS::MultiTopic>::ref_type a_multitopic) override;

    ::DDS::ReturnCode_t
    delete_contained_entities () override;

    ::DDS::ReturnCode_t
    set_qos (
      const ::DDS::DomainParticipantQos & qos) override;

    ::DDS::ReturnCode_t
    get_qos (
      ::DDS::DomainParticipantQos & qos) override;

    ::DDS::ReturnCode_t
    set_listener (
      IDL::traits<::DDS::DomainParticipantListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    IDL::traits<::DDS::DomainParticipantListener>::ref_type
    get_listener () override;

    ::DDS::ReturnCode_t
    ignore_participant (
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::ReturnCode_t
    ignore_topic (
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::ReturnCode_t
    ignore_publication (
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::ReturnCode_t
    ignore_subscription (
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::DomainId_t
    get_domain_id () override;

    ::DDS::ReturnCode_t
    assert_liveliness () override;

    ::DDS::ReturnCode_t
    set_default_publisher_qos (
      const ::DDS::PublisherQos & qos) override;

    ::DDS::ReturnCode_t
    get_default_publisher_qos (
      ::DDS::PublisherQos & qos) override;

    ::DDS::ReturnCode_t
    set_default_subscriber_qos (
      const ::DDS::SubscriberQos & qos) override;

    ::DDS::ReturnCode_t
    get_default_subscriber_qos (
      ::DDS::SubscriberQos & qos) override;

    ::DDS::ReturnCode_t
    set_default_topic_qos (
      const ::DDS::TopicQos & qos) override;

    ::DDS::ReturnCode_t
    get_default_topic_qos (
      ::DDS::TopicQos & qos) override;

    ::DDS::ReturnCode_t
    get_discovered_participants (
      ::DDS::InstanceHandleSeq & impl_handles) override;

    ::DDS::ReturnCode_t
    get_discovered_participant_data (
      ::DDS::ParticipantBuiltinTopicData & impl_data,
      const ::DDS::InstanceHandle_t& impl_handle) override;

    ::DDS::ReturnCode_t
    get_discovered_topics (
      ::DDS::InstanceHandleSeq & impl_handles) override;

    ::DDS::ReturnCode_t
    get_discovered_topic_data (
      ::DDS::TopicBuiltinTopicData & impl_data,
      const ::DDS::InstanceHandle_t& impl_handle) override;

    bool
    contains_entity (
      const ::DDS::InstanceHandle_t& a_handle) override;

    ::DDS::ReturnCode_t
    get_current_time (
      ::DDS::Time_t & current_time) override;

    ::DDS::ReturnCode_t
    enable () override;

    IDL::traits<::DDS::StatusCondition>::ref_type
    get_statuscondition () override;

    ::DDS::StatusMask
    get_status_changes () override;

    ::DDS::InstanceHandle_t
    get_instance_handle () override;

  private:
    DDS_DomainParticipant_proxy() = delete;
    DDS_DomainParticipant_proxy(const DDS_DomainParticipant_proxy&) = delete;
    DDS_DomainParticipant_proxy(DDS_DomainParticipant_proxy&&) = delete;
    DDS_DomainParticipant_proxy& operator=(const DDS_DomainParticipant_proxy&) = delete;
    DDS_DomainParticipant_proxy& operator=(DDS_DomainParticipant_proxy&&) = delete;

    /// Each DomainParticipant has a single built-in subscriber which
    /// can be retrieved by the user but this doesn't need to be deleted
    /// by the user, it is deleted automatically when the domain participant
    /// is deleted
    IDL::traits<::DDS::Subscriber>::ref_type builtin_subscriber_ {};
  };

  using domain_participant_trait = entity_traits< ::DDS::DomainParticipant, DDS_DomainParticipant_proxy, DDS_Native::DDS::DomainParticipant>;
}

#endif /* DDSX11_IMPL_DOMAIN_PARTICIPANT_H_ */
