/**
 * @file    dds_entities_types.h
 * @author  Johnny Willemsen
 *
 * @brief   Basic DDSX11 traits for all DDS defined interfaces
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_ENTITIES_TRAITS_H_
#define DDSX11_IMPL_ENTITIES_TRAITS_H_

#include "idl/dds_dcpsC.h"

namespace DDSX11
{
  struct dds_entities_types
  {
    typedef IDL::traits< ::DDS::Listener>::ref_type listener_ref_type;
    typedef IDL::traits< ::DDS::Listener>::weak_ref_type listener_weak_ref_type;
    typedef IDL::traits< ::DDS::Listener>::base_type listener_type;
    typedef IDL::traits< ::DDS::TopicListener>::ref_type topiclistener_ref_type;
    typedef IDL::traits< ::DDS::TopicListener>::weak_ref_type topiclistener_weak_ref_type;
    typedef IDL::traits< ::DDS::TopicListener>::base_type topiclistener_type;
    typedef IDL::traits< ::DDS::DataWriterListener>::ref_type datawriterlistener_ref_type;
    typedef IDL::traits< ::DDS::DataWriterListener>::weak_ref_type datawriterlistener_weak_ref_type;
    typedef IDL::traits< ::DDS::DataWriterListener>::base_type datawriterlistener_type;
    typedef IDL::traits< ::DDS::PublisherListener>::ref_type publisherlistener_ref_type;
    typedef IDL::traits< ::DDS::PublisherListener>::weak_ref_type publisherlistener_weak_ref_type;
    typedef IDL::traits< ::DDS::PublisherListener>::base_type publisherlistener_type;
    typedef IDL::traits< ::DDS::DataReaderListener>::ref_type datareaderlistener_ref_type;
    typedef IDL::traits< ::DDS::DataReaderListener>::weak_ref_type datareaderlistener_weak_ref_type;
    typedef IDL::traits< ::DDS::DataReaderListener>::base_type datareaderlistener_type;
    typedef IDL::traits< ::DDS::SubscriberListener>::ref_type subscriberlistener_ref_type;
    typedef IDL::traits< ::DDS::SubscriberListener>::weak_ref_type subscriberlistener_weak_ref_type;
    typedef IDL::traits< ::DDS::SubscriberListener>::base_type subscriberlistener_type;
    typedef IDL::traits< ::DDS::DomainParticipantListener>::ref_type domainparticipantlistener_ref_type;
    typedef IDL::traits< ::DDS::DomainParticipantListener>::weak_ref_type domainparticipantlistener_weak_ref_type;
    typedef IDL::traits< ::DDS::DomainParticipantListener>::base_type domainparticipantlistener_type;
    typedef IDL::traits< ::DDS::Condition>::ref_type condition_ref_type;
    typedef IDL::traits< ::DDS::Condition>::weak_ref_type condition_weak_ref_type;
    typedef IDL::traits< ::DDS::Condition>::base_type condition_type;
    typedef IDL::traits< ::DDS::WaitSet>::ref_type waitset_ref_type;
    typedef IDL::traits< ::DDS::WaitSet>::weak_ref_type waitset_weak_ref_type;
    typedef IDL::traits< ::DDS::WaitSet>::base_type waitset_type;
    typedef IDL::traits< ::DDS::GuardCondition>::ref_type guardcondition_ref_type;
    typedef IDL::traits< ::DDS::GuardCondition>::weak_ref_type guardcondition_weak_ref_type;
    typedef IDL::traits< ::DDS::GuardCondition>::base_type guardcondition_type;
    typedef IDL::traits< ::DDS::StatusCondition>::ref_type statuscondition_ref_type;
    typedef IDL::traits< ::DDS::StatusCondition>::weak_ref_type statuscondition_weak_ref_type;
    typedef IDL::traits< ::DDS::StatusCondition>::base_type statuscondition_type;
    typedef IDL::traits< ::DDS::ReadCondition>::ref_type readcondition_ref_type;
    typedef IDL::traits< ::DDS::ReadCondition>::weak_ref_type readcondition_weak_ref_type;
    typedef IDL::traits< ::DDS::ReadCondition>::base_type readcondition_type;
    typedef IDL::traits< ::DDS::QueryCondition>::ref_type querycondition_ref_type;
    typedef IDL::traits< ::DDS::QueryCondition>::weak_ref_type querycondition_weak_ref_type;
    typedef IDL::traits< ::DDS::QueryCondition>::base_type querycondition_type;
    typedef IDL::traits< ::DDS::Entity>::ref_type entity_ref_type;
    typedef IDL::traits< ::DDS::Entity>::weak_ref_type entity_weak_ref_type;
    typedef IDL::traits< ::DDS::Entity>::base_type entity_type;
    typedef IDL::traits< ::DDS::DomainParticipant>::ref_type domainparticipant_ref_type;
    typedef IDL::traits< ::DDS::DomainParticipant>::weak_ref_type domainparticipant_weak_ref_type;
    typedef IDL::traits< ::DDS::DomainParticipant>::base_type domainparticipant_type;
    typedef IDL::traits< ::DDS::DomainParticipantFactory>::ref_type domainparticipantfactory_ref_type;
    typedef IDL::traits< ::DDS::DomainParticipantFactory>::weak_ref_type domainparticipantfactory_weak_ref_type;
    typedef IDL::traits< ::DDS::DomainParticipantFactory>::base_type domainparticipantfactory_type;
    typedef IDL::traits< ::DDS::TypeSupport>::ref_type typesupport_ref_type;
    typedef IDL::traits< ::DDS::TypeSupport>::weak_ref_type typesupport_weak_ref_type;
    typedef IDL::traits< ::DDS::TypeSupport>::base_type typesupport_type;
    typedef IDL::traits< ::DDS::TopicDescription>::ref_type topicdescription_ref_type;
    typedef IDL::traits< ::DDS::TopicDescription>::weak_ref_type topicdescription_weak_ref_type;
    typedef IDL::traits< ::DDS::TopicDescription>::base_type topicdescription_type;
    typedef IDL::traits< ::DDS::Topic>::ref_type topic_ref_type;
    typedef IDL::traits< ::DDS::Topic>::weak_ref_type topic_weak_ref_type;
    typedef IDL::traits< ::DDS::Topic>::base_type topic_type;
    typedef IDL::traits< ::DDS::ContentFilteredTopic>::ref_type contentfilteredtopic_ref_type;
    typedef IDL::traits< ::DDS::ContentFilteredTopic>::weak_ref_type contentfilteredtopic_weak_ref_type;
    typedef IDL::traits< ::DDS::ContentFilteredTopic>::base_type contentfilteredtopic_type;
    typedef IDL::traits< ::DDS::MultiTopic>::ref_type multitopic_ref_type;
    typedef IDL::traits< ::DDS::MultiTopic>::weak_ref_type multitopic_weak_ref_type;
    typedef IDL::traits< ::DDS::MultiTopic>::base_type multitopic_type;
    typedef IDL::traits< ::DDS::Publisher>::ref_type publisher_ref_type;
    typedef IDL::traits< ::DDS::Publisher>::weak_ref_type publisher_weak_ref_type;
    typedef IDL::traits< ::DDS::Publisher>::base_type publisher_type;
    typedef IDL::traits< ::DDS::Subscriber>::ref_type subscriber_ref_type;
    typedef IDL::traits< ::DDS::Subscriber>::weak_ref_type subscriber_weak_ref_type;
    typedef IDL::traits< ::DDS::Subscriber>::base_type subscriber_type;
    typedef IDL::traits< ::DDS::DataReader>::ref_type datareader_ref_type;
    typedef IDL::traits< ::DDS::DataReader>::weak_ref_type datareader_weak_ref_type;
    typedef IDL::traits< ::DDS::DataReader>::base_type datareader_type;
    typedef IDL::traits< ::DDS::DataWriter>::ref_type datawriter_ref_type;
    typedef IDL::traits< ::DDS::DataWriter>::weak_ref_type datawriter_weak_ref_type;
    typedef IDL::traits< ::DDS::DataWriter>::base_type datawriter_type;
  };
} // namespace DDSX11

#endif /* DDSX11_IMPL_ENTITIES_TRAITS_H_ */
