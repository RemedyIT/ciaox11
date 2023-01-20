// -*- C++ -*-
/**
 * @file    dds4ccm_topicbase_connector_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds/dds_domain_participant.h"

#include <memory>

/**
 * Helper methods for the determination of late binded topics.
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
bool
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::late_binding ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::late_binding");
  return this->late_binding_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::late_binding (bool late_binding)
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::late_binding");
  this->late_binding_ |= late_binding;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
bool
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::stop_dds (
  const std::string &topic_name)
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::stop_dds");

  if (!this->topic_name_.empty ())
  {
    DDS4CCM_LOG_DEBUG ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::stop_dds - "
      << "Checking topic_name change from <" << this->topic_name_ << "> to <" << topic_name << ">");

    // topic name already set
    // do not stop DDS when topic names are equal
    return this->topic_name_ != topic_name;
  }
  return false;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
bool
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::late_binded (
  const std::string &topic_name)
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::late_binded");

  if (!topic_name.empty () && this->topic_name_.empty () && this->late_binding_)
  {
    DDS4CCM_LOG_DEBUG ("DDS_TopicBase_Connector_T::late_binded - "
      << "Topic <" << topic_name << "> is late binded.");
    DDS_TopicBase_Connector_T::topic_name (topic_name);
    return true;
  }
  else if (!this->configuration_completed ())
  {
    DDS_TopicBase_Connector_T::topic_name (topic_name);
  }

  this->late_binding (topic_name.empty ());

  DDS4CCM_LOG_DEBUG ("DDS_TopicBase_Connector_T::late_binded - "
    << "Topic <" << topic_name << "> is not late binded.");
  return false;
}

/**
 * DDS entity getters
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::DomainParticipant>::ref_type
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::domain_participant ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::domain_participant");

  if (!this->domain_participant_)
  {
    this->domain_participant_ = this->init_domain ();
  }
  return this->domain_participant_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::Topic>::ref_type
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::topic ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::topic");

  if (!this->topic_)
  {
    this->register_type (this->domain_participant (), this->type_name ());

    this->topic_ = this->init_topic (
      this->domain_participant (), this->topic_name (), this->type_name ());

  }
  return this->topic_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::Publisher>::ref_type
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::publisher ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::publisher");

  if (!this->publisher_)
  {
    this->publisher_ = this->init_publisher (this->domain_participant ());
  }
  return this->publisher_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::Subscriber>::ref_type
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscriber ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::subscriber");

  if (!this->subscriber_)
  {
    this->subscriber_ = this->init_subscriber (this->domain_participant ());
  }
  return this->subscriber_;
}

/**
 * Life cycle methods
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_complete ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::configuration_complete");

  this->configuration_completed (true);

  if (this->context ()->get_connection_error_listener ())
  {
    /// The connector status listener uses both a subscriber and a publisher
    /// Create both here.
    this->subscriber ();
    this->publisher ();
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_activate ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ccm_activate");

  this->topic_listener_ = this->activate_topic (this->topic_);

  // Activate the basic ports which are connected.
  if (this->subscriber_)
  {
    this->subscriber_listener_ = this->activate_subscriber (this->subscriber_);
  }
  if (this->publisher_)
  {
    this->publisher_listener_ = this->activate_publisher (this->publisher_);
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_passivate ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ccm_passivate");

  if (this->topic_)
  {
    // Prevent passivating a non-existing topic
    this->passivate_topic (this->topic_, this->topic_listener_);
  }

  // Passivate the basic ports which are connected.
  if (this->subscriber_)
  {
    this->passivate_subscriber (this->subscriber_, this->subscriber_listener_);
  }

  if (this->publisher_)
  {
    this->passivate_publisher (this->publisher_, this->publisher_listener_);
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_remove ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ccm_remove");

  if (this->topic_)
  {
    this->remove_topic (this->domain_participant (), this->topic_);
    this->topic_ = nullptr;

    this->unregister_type (this->domain_participant (), this->type_name ());
  }

  // Remove the basic ports which are connected.
  if (this->subscriber_)
  {
    this->remove_subscriber (this->domain_participant (), this->subscriber_);
    this->subscriber_ = nullptr;
  }
  if (this->publisher_)
  {
    this->remove_publisher (this->domain_participant (), this->publisher_);
    this->publisher_= nullptr;
  }
  if (this->domain_participant_)
  {
    this->remove_domain (this->domain_participant_);
    this->domain_participant_ = nullptr;
  }
}

/**
  * Type registration
 **/
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::register_type (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant,
  const std::string &typesupport_name)
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::register_type");

  DDS4CCM_LOG_DEBUG ("DDS_TopicBase_Connector_T::register_type - "
    "About to register type <" << typesupport_name << ">.");

  ::DDS::ReturnCode_t const retcode =
    ::DDS::traits<TOPIC_TYPE>::register_type (participant, typesupport_name);
  if (retcode != ::DDS::RETCODE_OK)
  {
    DDS4CCM_LOG_ERROR ("DDS_TopicBase_Connector_T::register_type - "
      << "Error registering type <" << typesupport_name << "> to participant <"
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant)
      << "with error code <"
      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
      << "> in DDS.");
    throw CCM_DDS::InternalError (retcode, 0);
  }
}

/**
  * Unregister type
 **/
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::unregister_type (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant,
  const std::string &typesupport_name)
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::unregister_type");

  ::DDS::ReturnCode_t const retcode =
    ::DDS::traits<TOPIC_TYPE>::unregister_type (participant, typesupport_name);
  if (retcode != ::DDS::RETCODE_OK)
  {
    DDS4CCM_LOG_ERROR ("DDS_TopicBase_Connector_T::unregister_type - "
      << "Error unregistering type <" << typesupport_name << "> from participant <"
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant)
      << "with error code <"
      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
      << "> in DDS.");
    throw CCM_DDS::InternalError (DDS::RETCODE_ERROR, 0);
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
std::string
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::topic_name ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::topic_name");

  return this->topic_name_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::topic_name (
  const std::string &topic_name)
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::topic_name");

  this->topic_name_ = topic_name;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
std::string
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::type_name ()
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::type_name");

  // When the user has not set a type_name we default to the DDS
  // vendor defined default type_name
  if (this->type_name_.empty ())
  {
    this->type_name_ = DDS::traits<TOPIC_TYPE>::get_type_name ();
  }

  return this->type_name_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::type_name (
  const std::string &type_name)
{
  DDS4CCM_LOG_TRACE ("DDS_TopicBase_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::type_name");

  this->type_name_ = type_name;
}
