/**
 * @file    ndds_typedefs.h
 * @author  Marcel Smit
 *
 * @brief   'Conversion' from RTI NDDS-naming conventions to
 *          naming convertions visible to the user.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_TYPEDEF_H_
#define DDSX11_IMPL_NDDS_TYPEDEF_H_

#include "ndds_cpp.h"
#include <cstdint>

#define DDSX11_HAS_VENDOR_TYPEDEFS

namespace DDS_Native
{
    namespace DDS
    {
      typedef ::DDS_Long Long;
      typedef ::DDS_LongDouble LongDouble;

      typedef uint32_t long_4[4];

      typedef ::DDS_Long sequence_size_type;

      typedef ::DDS_BuiltinTopicKey_t BuiltinTopicKey_t;
      typedef ::DDS_Duration_t Duration_t;
      typedef ::DDS_Time_t Time_t;

      typedef ::DDS_OctetSeq OctetSeq;
      typedef ::DDS_StringSeq StringSeq;

      typedef ::DDS_InstanceHandle_t InstanceHandle_t;
      typedef ::DDS_InstanceHandleSeq InstanceHandleSeq;

      typedef ::DDS_ReturnCode_t ReturnCode_t;

      typedef ::DDSListener Listener;
      typedef ::DDSEntity Entity;
      typedef ::DDSTopicDescription TopicDescription;
      typedef ::DDSTopicDescription* TopicDescription_var;
      typedef ::DDSTopic Topic;
      typedef ::DDSTopic* Topic_var;
      typedef ::DDSContentFilteredTopic ContentFilteredTopic;
      typedef ::DDSContentFilteredTopic_var ContentFilteredTopic_var;
      typedef ::DDSMultiTopic MultiTopic;
      typedef ::DDSDataWriter DataWriter;
      typedef ::DDSDataWriter* DataWriter_var;
      typedef ::DDSDataReader DataReader;
      typedef ::DDSDataReader* DataReader_var;
      typedef ::DDSSubscriber Subscriber;
      typedef ::DDSSubscriber* Subscriber_var;
      typedef ::DDSPublisher Publisher;
      typedef ::DDSPublisher* Publisher_var;
      typedef ::DDSDomainParticipant DomainParticipant;
      typedef ::DDSDomainParticipant* DomainParticipant_var;
      typedef ::DDSDomainParticipantFactory DomainParticipantFactory;
      typedef ::DDSDomainParticipantFactory* DomainParticipantFactory_var;
      typedef ::DDSDataReaderSeq DataReaderSeq;
      typedef ::DDSTopicListener TopicListener;
      typedef ::DDSDataWriterListener DataWriterListener;
      typedef ::DDSPublisherListener PublisherListener;
      typedef ::DDSDataReaderListener DataReaderListener;
      typedef ::DDSSubscriberListener SubscriberListener;
      typedef ::DDSDomainParticipantListener DomainParticipantListener;
      typedef ::DDSDomainParticipantListener_var DomainParticipantListener_var;
      typedef ::DDSCondition Condition;
      typedef ::DDSQueryCondition QueryCondition;
      typedef ::DDSQueryCondition* QueryCondition_var;
      typedef ::DDSReadCondition ReadCondition;
      typedef ::DDSReadCondition* ReadCondition_var;
      typedef ::DDSConditionSeq ConditionSeq;
      typedef ::DDSWaitSet WaitSet;
      typedef ::DDSGuardCondition GuardCondition;
      typedef ::DDSStatusCondition StatusCondition;
      typedef ::DDSStatusCondition* StatusCondition_var;

      typedef ::DDS_UserDataQosPolicy UserDataQosPolicy;
      typedef ::DDS_TopicDataQosPolicy TopicDataQosPolicy;
      typedef ::DDS_GroupDataQosPolicy GroupDataQosPolicy;
      typedef ::DDS_TransportPriorityQosPolicy TransportPriorityQosPolicy;
      typedef ::DDS_LifespanQosPolicy LifespanQosPolicy;
      typedef ::DDS_DurabilityQosPolicy DurabilityQosPolicy;
      typedef ::DDS_PresentationQosPolicy PresentationQosPolicy;
      typedef ::DDS_DeadlineQosPolicy DeadlineQosPolicy;
      typedef ::DDS_LatencyBudgetQosPolicy LatencyBudgetQosPolicy;
      typedef ::DDS_OwnershipQosPolicy OwnershipQosPolicy;
      typedef ::DDS_OwnershipStrengthQosPolicy OwnershipStrengthQosPolicy;
      typedef ::DDS_LivelinessQosPolicy LivelinessQosPolicy;
      typedef ::DDS_TimeBasedFilterQosPolicy TimeBasedFilterQosPolicy;
      typedef ::DDS_PartitionQosPolicy PartitionQosPolicy;
      typedef ::DDS_ReliabilityQosPolicy ReliabilityQosPolicy;
      typedef ::DDS_DestinationOrderQosPolicy DestinationOrderQosPolicy;
      typedef ::DDS_HistoryQosPolicy HistoryQosPolicy;
      typedef ::DDS_ResourceLimitsQosPolicy ResourceLimitsQosPolicy;
      typedef ::DDS_EntityFactoryQosPolicy EntityFactoryQosPolicy;
      typedef ::DDS_WriterDataLifecycleQosPolicy WriterDataLifecycleQosPolicy;
      typedef ::DDS_DataReaderResourceLimitsQosPolicy DataReaderResourceLimitsQosPolicy;
      typedef ::DDS_DataWriterResourceLimitsQosPolicy DataWriterResourceLimitsQosPolicy;
      typedef ::DDS_ReaderDataLifecycleQosPolicy ReaderDataLifecycleQosPolicy;
      typedef ::DDS_DurabilityServiceQosPolicy DurabilityServiceQosPolicy;
      typedef ::DDS_DomainParticipantFactoryQos DomainParticipantFactoryQos;
      typedef ::DDS_DomainParticipantQos DomainParticipantQos;
      typedef ::DDS_TopicQos TopicQos;
      typedef ::DDS_DataWriterQos DataWriterQos;
      typedef ::DDS_PublisherQos PublisherQos;
      typedef ::DDS_DataReaderQos DataReaderQos;
      typedef ::DDS_SubscriberQos SubscriberQos;
      typedef ::DDS_ParticipantBuiltinTopicData ParticipantBuiltinTopicData;
      typedef ::DDS_TopicBuiltinTopicData TopicBuiltinTopicData;
      typedef ::DDS_PublicationBuiltinTopicData PublicationBuiltinTopicData;
      typedef ::DDS_SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData;
      typedef ::DDS_SampleInfo SampleInfo;
      typedef ::DDS_SampleInfoSeq SampleInfoSeq;

      typedef ::DDS_InconsistentTopicStatus InconsistentTopicStatus;
      typedef ::DDS_SampleLostStatus SampleLostStatus;
      typedef ::DDS_SampleRejectedStatusKind SampleRejectedStatusKind;
      typedef ::DDS_SampleRejectedStatus SampleRejectedStatus;
      typedef ::DDS_LivelinessLostStatus LivelinessLostStatus;
      typedef ::DDS_LivelinessChangedStatus LivelinessChangedStatus;
      typedef ::DDS_OfferedDeadlineMissedStatus OfferedDeadlineMissedStatus;
      typedef ::DDS_RequestedDeadlineMissedStatus RequestedDeadlineMissedStatus;
      typedef ::DDS_QosPolicyCount QosPolicyCount;
      typedef ::DDS_QosPolicyCountSeq QosPolicyCountSeq;
      typedef ::DDS_OfferedIncompatibleQosStatus OfferedIncompatibleQosStatus;
      typedef ::DDS_RequestedIncompatibleQosStatus RequestedIncompatibleQosStatus;
      typedef ::DDS_PublicationMatchedStatus PublicationMatchedStatus;
      typedef ::DDS_SubscriptionMatchedStatus SubscriptionMatchedStatus;
      typedef ::DDS_ReliableReaderActivityChangedStatus ReliableReaderActivityChangedStatus;
      typedef ::DDS_ReliableWriterCacheEventCount ReliableWriterCacheEventCount;
      typedef ::DDS_ReliableWriterCacheChangedStatus ReliableWriterCacheChangedStatus;
      typedef ::DDS_TypeConsistencyKind TypeConsistencyKind;
      typedef ::DDS_TypeConsistencyEnforcementQosPolicy TypeConsistencyEnforcementQosPolicy;

      typedef ::DDS_DurabilityQosPolicyKind DurabilityQosPolicyKind;
      typedef ::DDS_PresentationQosPolicyAccessScopeKind PresentationQosPolicyAccessScopeKind;
      typedef ::DDS_OwnershipQosPolicyKind OwnershipQosPolicyKind;
      typedef ::DDS_LivelinessQosPolicyKind LivelinessQosPolicyKind;
      typedef ::DDS_ReliabilityQosPolicyKind ReliabilityQosPolicyKind;
      typedef ::DDS_DestinationOrderQosPolicyKind DestinationOrderQosPolicyKind;
      typedef ::DDS_DestinationOrderQosPolicyScopeKind DestinationOrderQosPolicyScopeKind;
      typedef ::DDS_DataWriterResourceLimitsInstanceReplacementKind DataWriterResourceLimitsInstanceReplacementKind;
      typedef ::DDS_HistoryQosPolicyKind HistoryQosPolicyKind;
      typedef ::DDS_RefilterQosPolicyKind RefilterQosPolicyKind;
  } // namespace DDS
} // namespace DDS_Native

#endif /* DDSX11_IMPL_NDDS_TYPEDEF_H_ */

