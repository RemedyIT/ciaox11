/**
 * @file    opendds_typedefs.h
 * @author  Johnny Willemsen
 *
 * @brief   'Conversion' OpenDDS naming conventions to
 *          naming conversions visible to the user.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_OPENDDS_TYPEDEF_H_
#define DDSX11_IMPL_OPENDDS_TYPEDEF_H_

#include "dds/DdsDcpsC.h"

#include /**/ "tao/Versioned_Namespace.h"
#include "tao/x11/tao_corba.h"

#include /**/ "dds/Versioned_Namespace.h"
#include "dds/DCPS/WaitSet.h"

#define DDSX11_HAS_VENDOR_TYPEDEFS

// At the moment OpenDDS has been compiled using minimum
// build in topics we also disable this in DDSX11
#if defined DDS_HAS_MINIMUM_BIT
# define DDSX11_HAS_MINIMUM_BIT
#endif /* DDS_HAS_MINIMUM_BIT */

namespace DDS_Native
{
    namespace DDS
    {
      typedef TAO_VERSIONED_NAMESPACE_NAME::CORBA::Long Long;
      typedef TAO_VERSIONED_NAMESPACE_NAME::CORBA::ULong ULong;
      typedef TAO_VERSIONED_NAMESPACE_NAME::CORBA::LongDouble LongDouble;

      typedef TAO_VERSIONED_NAMESPACE_NAME::CORBA::Octet OctetArray16[16];

      typedef TAO_VERSIONED_NAMESPACE_NAME::CORBA::ULong sequence_size_type;

      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::BuiltinTopicKey_t BuiltinTopicKey_t;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Duration_t Duration_t;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Time_t Time_t;

      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::OctetSeq OctetSeq;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::StringSeq StringSeq;

      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::InstanceHandle_t InstanceHandle_t;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::InstanceHandleSeq InstanceHandleSeq;

      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ReturnCode_t ReturnCode_t;

      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Listener Listener;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Entity Entity;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Entity_var Entity_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TopicDescription TopicDescription;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TopicDescription_var TopicDescription_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Topic Topic;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Topic_var Topic_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ContentFilteredTopic ContentFilteredTopic;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ContentFilteredTopic_var ContentFilteredTopic_var;
#ifndef OPENDDS_NO_MULTI_TOPIC
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::MultiTopic MultiTopic;
#endif /* OPENDDS_NO_MULTI_TOPIC */
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataWriter DataWriter;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataWriter_var DataWriter_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataReader DataReader;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataReader_var DataReader_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Subscriber Subscriber;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Subscriber_var Subscriber_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Publisher Publisher;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Publisher_var Publisher_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipant DomainParticipant;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipant_var DomainParticipant_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipantFactory DomainParticipantFactory;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipantFactory_var DomainParticipantFactory_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataReaderSeq DataReaderSeq;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TopicListener TopicListener;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TopicListener_var TopicListener_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataWriterListener DataWriterListener;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataWriterListener_var DataWriterListener_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PublisherListener PublisherListener;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PublisherListener_var PublisherListener_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataReaderListener DataReaderListener;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataReaderListener_var DataReaderListener_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SubscriberListener SubscriberListener;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SubscriberListener_var SubscriberListener_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipantListener DomainParticipantListener;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipantListener_var DomainParticipantListener_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::Condition Condition;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::QueryCondition QueryCondition;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::QueryCondition_var QueryCondition_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ReadCondition ReadCondition;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ReadCondition_var ReadCondition_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ConditionSeq ConditionSeq;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::WaitSet WaitSet;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::WaitSet_var WaitSet_var;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::StatusCondition StatusCondition;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::StatusCondition_var StatusCondition_var;

      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::UserDataQosPolicy UserDataQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TopicDataQosPolicy TopicDataQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::GroupDataQosPolicy GroupDataQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TransportPriorityQosPolicy TransportPriorityQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::LifespanQosPolicy LifespanQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DurabilityQosPolicy DurabilityQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PresentationQosPolicy PresentationQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DeadlineQosPolicy DeadlineQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::LatencyBudgetQosPolicy LatencyBudgetQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::OwnershipQosPolicy OwnershipQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::OwnershipStrengthQosPolicy OwnershipStrengthQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::LivelinessQosPolicy LivelinessQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TimeBasedFilterQosPolicy TimeBasedFilterQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PartitionQosPolicy PartitionQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ReliabilityQosPolicy ReliabilityQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DestinationOrderQosPolicy DestinationOrderQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::HistoryQosPolicy HistoryQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ResourceLimitsQosPolicy ResourceLimitsQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::EntityFactoryQosPolicy EntityFactoryQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::WriterDataLifecycleQosPolicy WriterDataLifecycleQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ReaderDataLifecycleQosPolicy ReaderDataLifecycleQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DurabilityServiceQosPolicy DurabilityServiceQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipantFactoryQos DomainParticipantFactoryQos;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DomainParticipantQos DomainParticipantQos;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TopicQos TopicQos;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataWriterQos DataWriterQos;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PublisherQos PublisherQos;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataReaderQos DataReaderQos;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SubscriberQos SubscriberQos;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ParticipantBuiltinTopicData ParticipantBuiltinTopicData;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TopicBuiltinTopicData TopicBuiltinTopicData;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PublicationBuiltinTopicData PublicationBuiltinTopicData;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SampleInfo SampleInfo;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SampleInfoSeq SampleInfoSeq;

      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::InconsistentTopicStatus InconsistentTopicStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SampleLostStatus SampleLostStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SampleRejectedStatusKind SampleRejectedStatusKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SampleRejectedStatus SampleRejectedStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::LivelinessLostStatus LivelinessLostStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::LivelinessChangedStatus LivelinessChangedStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::OfferedDeadlineMissedStatus OfferedDeadlineMissedStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::RequestedDeadlineMissedStatus RequestedDeadlineMissedStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::QosPolicyCount QosPolicyCount;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::QosPolicyCountSeq QosPolicyCountSeq;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::OfferedIncompatibleQosStatus OfferedIncompatibleQosStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::RequestedIncompatibleQosStatus RequestedIncompatibleQosStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PublicationMatchedStatus PublicationMatchedStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::SubscriptionMatchedStatus SubscriptionMatchedStatus;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DurabilityQosPolicyKind DurabilityQosPolicyKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::PresentationQosPolicyAccessScopeKind PresentationQosPolicyAccessScopeKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::OwnershipQosPolicyKind OwnershipQosPolicyKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::LivelinessQosPolicyKind LivelinessQosPolicyKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::ReliabilityQosPolicyKind ReliabilityQosPolicyKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DestinationOrderQosPolicyKind DestinationOrderQosPolicyKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::HistoryQosPolicyKind HistoryQosPolicyKind;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataRepresentationIdSeq DataRepresentationIdSeq;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::DataRepresentationQosPolicy DataRepresentationQosPolicy;
      typedef OPENDDS_VERSIONED_NAMESPACE_NAME::DDS::TypeConsistencyEnforcementQosPolicy TypeConsistencyEnforcementQosPolicy;
    } // namespace DDS
} // namespace DDS_Native


#endif /* DDSX11_IMPL_OPENDDS_TYPEDEF_H_ */

