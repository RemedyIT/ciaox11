// -*- C++ -*-
/**
 * @file    dds4ccm_base_connector_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM Base connector.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"

#include "dds4ccm/impl/dds4ccm_conf.h"

#include "dds4ccm/impl/dds4ccm_dp_manager.h"
#include "dds4ccm/impl/dds4ccm_base_connector_t.h"

#include "dds/dds_vendor_adapter.h"
#include "dds/dds_domain_participant_factory.h"
#include "dds/dds_make_reference.h"
#include "dds4ccm_publisher_listener_t.h"
#include "dds4ccm_subscriber_listener_t.h"
#include "dds4ccm_topic_listener_t.h"

template <typename CCM_TYPE>
DDS_Base_Connector_T<CCM_TYPE>::DDS_Base_Connector_T ()
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::DDS_Base_Connector_T");

  const char * domain = std::getenv ("DDS4CCM_DEFAULT_DOMAIN_ID");

  if (domain)
  {
    this->domain_id_ = std::atoi (domain);
  }

  DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T<CCM_TYPE>::DDS_Base_Connector_T - "
    << "Domain ID set to <" << this->domain_id_ << ">.");

  if (!this->participant_factory_)
  {
    this->participant_factory_ = DDS::traits<DDS::DomainParticipantFactory>::get_instance ();
  }
}

template <typename CCM_TYPE>
DDS_Base_Connector_T<CCM_TYPE>::~DDS_Base_Connector_T ()
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::~DDS_Base_Connector_T");

  DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::~DDS_Base_Connector_T - "
    << "Connector has been destructed.");

  if (DPMANAGER->close())
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::~DDS_Base_Connector_T - "
      << "Closed the domain participant manager, DDS interaction "
      << "has been shutdown completely");
  }
  else
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::~DDS_Base_Connector_T - "
      << "Didn't shutdown the domain participant manager, DDS interaction "
      << "still active.");
  }
}

template <typename CCM_TYPE>
::DDS::DomainId_t
DDS_Base_Connector_T<CCM_TYPE>::domain_id ()
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::domain_id");

  return this->domain_id_;
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::domain_id (
  ::DDS::DomainId_t domain_id)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::domain_id");

  if (this->configuration_completed ())
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T<CCM_TYPE>::domain_id - "
      "Error: Not allowed to set the domain_id after configuration_complete. "
      "Throwing a CCM_DDS::NonChangeable exception.");
    throw CCM_DDS::NonChangeable ();
  }
  else
  {
    this->domain_id_ = domain_id;
  }
}

template <typename CCM_TYPE>
std::string
DDS_Base_Connector_T<CCM_TYPE>::qos_profile ()
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::qos_profile");

  return this->qos_profile_;
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::qos_profile (const std::string &qos_profile)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::qos_profile");

  if (this->configuration_completed ())
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T<CCM_TYPE>::qos_profile - "
      "Error: Not allowed to set the qos_profile after configuration_complete. "
      "Throwing a CCM_DDS::NonChangeable exception.");
    throw CCM_DDS::NonChangeable ();
  }
  else
  {
    this->qos_profile_ = qos_profile;
  }
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::set_session_context (
  IDL::traits<Components::SessionContext>::ref_type ctx)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::set_session_context");

  this->context_ = CCM_TYPE::context_type::_traits_type::narrow (std::move(ctx));
}

template <typename CCM_TYPE>
bool
DDS_Base_Connector_T<CCM_TYPE>::configuration_completed () const
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::configuration_completed");
  return this->configuration_completed_;
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::configuration_completed (
  bool configuration_completed)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::configuration_completed");
  this->configuration_completed_ = configuration_completed;
}

template <typename CCM_TYPE>
typename IDL::traits<typename CCM_TYPE::context_type>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::context ()
{
  return this->context_;
}

/**
  * Initialization
 **/
template <typename CCM_TYPE>
IDL::traits<::DDS::DomainParticipant>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::init_domain ()
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T<CCM_TYPE>::init_domain");

  DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_domain - "
    << "Start configuring default domain <" << this->domain_id_
    << ">.");
  IDL::traits<::DDS::DomainParticipant>::ref_type participant;

  IDL::traits<::DDS::DomainParticipant>::ref_type dds_dp =
    DPMANAGER->get_participant (this->domain_id_, this->qos_profile_);

  if (!dds_dp)
  {
    if (this->qos_profile_.empty ())
    {
      DDS::DomainParticipantQos qos;
      ::DDS::ReturnCode_t const retcode =
        this->participant_factory_->get_default_participant_qos (qos);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_domain - "
          << "Error: Unable to retrieve default_participant_qos: <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");
        throw CCM_DDS::InternalError (retcode, 0);
      }

      // Create a participant with the default qos profile and domain ID.
      participant =
        this->participant_factory_->create_participant (
          this->domain_id_,
          qos,
          nullptr,
          ::DDS::STATUS_MASK_NONE);
    }
    else
    {
      participant =
        this->participant_factory_->create_participant_with_profile (
          this->domain_id_,
          this->qos_profile_,
          nullptr,
          ::DDS::STATUS_MASK_NONE);
    }

    if (!participant)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_domain - "
        << "Error: DDS returned a nullptr as participant. Unable to continue.");
      throw CCM_DDS::InternalError (DDS::RETCODE_ERROR, 0);
    }

    ::DDS::ReturnCode_t const retcode = participant->enable ();
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_domain - "
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CCM_DDS::InternalError (retcode, 0);
    }

    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_domain - "
      << "Created and enabled domainparticipant "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant)
      << " domain <" << this->domain_id_ << "> - qos_profile <"
      << this->qos_profile_<< ">.");

    if (!DPMANAGER->register_participant (
      this->domain_id_, this->qos_profile_, participant))
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_domain - "
        << "Error: Unable to register DomainParticipant for domain <"
        << this->domain_id_ << ">.");
      throw CCM_DDS::InternalError (DDS::RETCODE_ERROR, 0);
    }
  }
  else
  {
    // Re-use the domain_participant for this QOS profile and domain ID
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_domain - "
      << "Re-using domainparticipant " << dds_dp << " - domain <"
      << this->domain_id_ << "> - qos_profile <"
      << this->qos_profile_ << ">.");

    participant = dds_dp;
  }

  return participant;
}

template <typename CCM_TYPE>
IDL::traits<::DDS::Topic>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::init_topic (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant,
  const std::string &topic_name,
  const std::string &type_name)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::init_topic");

  DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_topic - "
    << "Finding existing topic name <" << topic_name << "> for profile <"
    << this->qos_profile_ << "> in participant "
    << IDL::traits<DDS::Entity>::write<entity_formatter> (participant));

  IDL::traits<::DDS::Topic>::ref_type topic;

  ::DDS::Duration_t timeout { 0, 0 };
  IDL::traits<::DDS::Topic>::ref_type dds_tp =
    participant->find_topic (topic_name, timeout);

  if (dds_tp)
  {
    // Re-use topic.
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_topic - "
      << "Re-using topic <" << topic_name << "> for profile <"
      << this->qos_profile_ << ">.");

    topic = dds_tp;
  }
  else
  {
    if (!this->qos_profile_.empty ())
    {
      topic = participant->create_topic_with_profile (
          topic_name,
          type_name,
          this->qos_profile_,
          nullptr,
          ::DDS::STATUS_MASK_NONE);
    }
    else
    {
      ::DDS::TopicQos tqos;
      ::DDS::ReturnCode_t const retcode =
        participant->get_default_topic_qos (tqos);

      if (retcode != DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_topic - "
          << "Error: Unable to retrieve default_topic_qos: <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");
        throw CCM_DDS::InternalError (retcode, 0);
      }

      topic = participant->create_topic (
                      topic_name,
                      type_name,
                      tqos,
                      nullptr,
                      ::DDS::STATUS_MASK_NONE);
    }
  }
  if (topic)
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_topic - "
      << "Created a topic <"
      << IDL::traits<::DDS::Entity>::write<entity_formatter> (topic)
      << ">: name <" << topic_name << "> type <" << type_name
      << "> for profile <" << this->qos_profile_
      << ">.");
  }
  else
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_topic - "
      << "Error: unable to create a topic <" << topic_name
      << "> for profile <" << this->qos_profile_ << ">.");
    throw CCM_DDS::InternalError (DDS::RETCODE_ERROR, 0);
  }
  return topic;
}

template <typename CCM_TYPE>
IDL::traits<::DDS::Publisher>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::init_publisher (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::init_publisher");

  ::DDS::ReturnCode_t retcode;
  IDL::traits<::DDS::Publisher>::ref_type publisher;

  if (!this->qos_profile_.empty ())
  {
    publisher = participant->create_publisher_with_profile (
        this->qos_profile_,
        nullptr,
        ::DDS::STATUS_MASK_NONE);
  }
  else
  {
    DDS::PublisherQos pqos;
    retcode = participant->get_default_publisher_qos (pqos);

    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_publisher - "
        << "Error: Unable to retrieve get_default_publisher_qos: <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CCM_DDS::InternalError (retcode, 0);
    }

    publisher = participant->create_publisher (
                    pqos,
                    nullptr,
                    ::DDS::STATUS_MASK_NONE);
  }

  if (publisher)
  {
    retcode = publisher->enable ();
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_publisher - "
        << "Error whilst enabling the Publisher: <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CCM_DDS::InternalError (retcode, 0);
    }

    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_publisher - "
      << "Created and enabled publisher "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (publisher)
      << " using participant "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant));
  }
  else
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_publisher - "
      "Error: DDS returned a nil publisher.");
    throw CCM_DDS::InternalError (DDS::RETCODE_ERROR, 0);
  }
  return publisher;
}

template <typename CCM_TYPE>
IDL::traits<::DDS::Subscriber>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::init_subscriber (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::init_subscriber");

  ::DDS::ReturnCode_t retcode;
  IDL::traits<::DDS::Subscriber>::ref_type subscriber;

  if (!this->qos_profile_.empty ())
  {
    subscriber = participant->create_subscriber_with_profile (
        this->qos_profile_,
        nullptr,
        ::DDS::STATUS_MASK_NONE);
  }
  else
  {
    DDS::SubscriberQos sqos;
    retcode = participant->get_default_subscriber_qos (sqos);

    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_subscriber - "
        << "Error: Unable to retrieve get_default_subscriber_qos: <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CCM_DDS::InternalError (retcode, 0);
    }

    subscriber = participant->create_subscriber (sqos, nullptr, ::DDS::STATUS_MASK_NONE);
  }

  if (subscriber)
  {
    retcode = subscriber->enable ();
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_subscriber - "
        << "Error whilst enabling the Subscriber: <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CCM_DDS::InternalError (retcode, 0);
    }

    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::init_subscriber - "
      << "Created and enabled subscriber "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (subscriber)
      << " using participant "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant));
  }
  else
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::init_subscriber - "
      "Error: DDS returned a nil subscriber.");
    throw CCM_DDS::InternalError (DDS::RETCODE_ERROR, 0);
  }
  return subscriber;
}

/**
  * Activation
  */
template <typename CCM_TYPE>
IDL::traits<::DDS::TopicListener>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::activate_topic (
  IDL::traits<::DDS::Topic>::ref_type topic)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::activate_topic");

  IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type error_listener =
    this->context_->get_connection_error_listener ();

  IDL::traits<::DDS::TopicListener>::ref_type topic_listener;

  using event_strategy_type = typename CCM_TYPE::error_event_strategy_type;
  using topic_listener_type = CIAOX11::DDS4CCM::TopicListener_T<event_strategy_type>;

  // Even if error_listener is nil, it is possible for some vendors
  // that mask isn't DDS::STATUS_MASK_NONE.
  ::DDS::StatusMask const mask =
      topic_listener_type::get_mask (error_listener);

  if (mask != ::DDS::STATUS_MASK_NONE)
  {
    topic_listener =
      DDS::make_reference<topic_listener_type>(
        event_strategy_type (this->context_));

    ::DDS::ReturnCode_t const retcode = topic->set_listener (
      topic_listener, mask);

    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::activate_topic - "
        << "Error while setting the listener on the topic - <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CORBA::INTERNAL ();
    }
  }

  return topic_listener;
}

template <typename CCM_TYPE>
IDL::traits<::DDS::PublisherListener>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::activate_publisher (
  IDL::traits<::DDS::Publisher>::ref_type publisher)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::activate_publisher");

  IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type error_listener =
    this->context_->get_connection_error_listener ();

  IDL::traits<::DDS::PublisherListener>::ref_type publisher_listener;

  using event_strategy_type = typename CCM_TYPE::error_event_strategy_type ;

  // Even if error_listener is nil, it is possible for some vendors
  // that mask isn't DDS::STATUS_MASK_NONE.
  ::DDS::StatusMask const mask =
    CIAOX11::DDS4CCM::VendorUtils::get_publisher_listener_mask<event_strategy_type> (
        error_listener);

  if (mask != ::DDS::STATUS_MASK_NONE)
  {
    publisher_listener = CIAOX11::DDS4CCM::VendorUtils::create_publisher_listener<event_strategy_type> (
      event_strategy_type (this->context_));

    ::DDS::ReturnCode_t const retcode =
      publisher->set_listener (publisher_listener, mask);

    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::activate_publisher - "
        << "Error while setting the listener on the publisher - <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CORBA::INTERNAL ();
    }
  }
  return publisher_listener;
}

template <typename CCM_TYPE>
IDL::traits<::DDS::SubscriberListener>::ref_type
DDS_Base_Connector_T<CCM_TYPE>::activate_subscriber (
  IDL::traits<::DDS::Subscriber>::ref_type subscriber)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::activate_subscriber");

  IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type error_listener =
    this->context_->get_connection_error_listener ();

  IDL::traits<::DDS::SubscriberListener>::ref_type subscriber_listener;

  using event_strategy_type = typename CCM_TYPE::error_event_strategy_type;
  using subscriber_listener_type = CIAOX11::DDS4CCM::SubscriberListener_T<event_strategy_type>;

  // Even if error_listener is nil, it is possible for some vendors
  // that mask isn't DDS::STATUS_MASK_NONE.
  ::DDS::StatusMask const mask =
      subscriber_listener_type::get_mask (error_listener);

  if (mask != ::DDS::STATUS_MASK_NONE)
  {
    subscriber_listener =
      DDS::make_reference<subscriber_listener_type>
        (event_strategy_type (this->context_));

    ::DDS::ReturnCode_t const retcode =
      subscriber->set_listener (subscriber_listener, mask);

    if (retcode != DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::activate_subscriber - "
          << "Error while setting the listener on the subscriber - <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");
        throw CORBA::INTERNAL ();
      }
  }
  return subscriber_listener;
}

/**
  * Passivation
 **/
template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::passivate_topic (
  IDL::traits<::DDS::Topic>::ref_type topic,
  IDL::traits<::DDS::TopicListener>::ref_type topic_listener)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::passivate_topic");

  if (topic_listener)
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::passivate_topic - "
      << "Setting the listener on the topic to nil.");

    ::DDS::ReturnCode_t const retcode = topic->set_listener (nullptr, 0);
    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::passivate_topic - "
        << "Error while setting the listener on the topic - <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CORBA::INTERNAL ();
    }
  }
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::passivate_publisher (
  IDL::traits<::DDS::Publisher>::ref_type publisher,
  IDL::traits<::DDS::PublisherListener>::ref_type publisher_listener)

{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::passivate_publisher");

  if (publisher_listener)
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::passivate_publisher - "
      << "Setting the listener on the publisher to nil.");

    ::DDS::ReturnCode_t const retcode = publisher->set_listener (nullptr, 0);

    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::passivate_publisher - "
        << "Error while setting the listener on the publisher - <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CORBA::INTERNAL ();
    }
  }
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::passivate_subscriber (
  IDL::traits<::DDS::Subscriber>::ref_type subscriber,
  IDL::traits<::DDS::SubscriberListener>::ref_type subscriber_listener)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::passivate_subscriber");

  if (subscriber_listener)
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::passivate_subscriber - "
      << "Setting the listener on the subscriber to nil.");

    ::DDS::ReturnCode_t const retcode =
      subscriber->set_listener (nullptr, 0);

    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::passivate_subscriber - "
        << "Error while setting the listener on the subscriber - <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CORBA::INTERNAL ();
    }
  }
}

/**
  * Removal
  */
template <typename CCM_TYPE>
void DDS_Base_Connector_T<CCM_TYPE>::remove_topic (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant,
  IDL::traits<::DDS::Topic>::ref_type topic)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::remove_topic");

  std::string const topic_name = topic->get_name ();
  ::DDS::InstanceHandle_t const topic_handle = topic->get_instance_handle ();

  DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_topic - "
    << "Going to remove topic <" << topic_name << ">:<"
    << topic_handle
    << "> from participant "
    << IDL::traits<DDS::Entity>::write<entity_formatter> (participant));

  ::DDS::ReturnCode_t const retcode = participant->delete_topic (topic);

  if (retcode != DDS::RETCODE_OK)
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::remove_topic - Error removing topic <"
      << topic_handle
      << "> from participant "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant)
      << " - return code <"
      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
      << ">.");
    throw CCM_DDS::InternalError (retcode, 0);
  }
  else
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_topic - "
      << "Removed topic <" << topic_name << ">:<"
      << topic_handle
      << "> from participant "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant)
      << " - return code <"
      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
      << ">.");
  }
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::remove_publisher (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant,
  IDL::traits<::DDS::Publisher>::ref_type publisher)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::remove_publisher");

  DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_publisher - "
    << "Going to remove publisher "
    << IDL::traits<DDS::Entity>::write<entity_formatter> (publisher)
    << " from participant "
    << IDL::traits<DDS::Entity>::write<entity_formatter> (participant));

  ::DDS::ReturnCode_t const retcode = participant->delete_publisher (publisher);

  if (retcode != DDS::RETCODE_OK)
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::remove_publisher - "
      << "Unable to remove publisher: <"
      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
      << ">.");
    throw CORBA::INTERNAL ();
  }
  else
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_publisher - "
      << "Removed publisher");
  }
}

template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::remove_subscriber (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant,
  IDL::traits<::DDS::Subscriber>::ref_type subscriber)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::remove_subscriber");

  DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_subscriber - "
    << "Going to remove subscriber "
    << IDL::traits<DDS::Entity>::write<entity_formatter> (subscriber)
    << " from participant "
    << IDL::traits<DDS::Entity>::write<entity_formatter> (participant));

  ::DDS::ReturnCode_t const retcode = participant->delete_subscriber (subscriber);

  if (retcode != DDS::RETCODE_OK)
  {
    DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::remove_subscriber - "
      << "Unable to remove subscriber: <"
      << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
      << ">.");
    throw CORBA::INTERNAL ();
  }
  else
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_subscriber - "
      "Removed subscriber");
  }
}


template <typename CCM_TYPE>
void
DDS_Base_Connector_T<CCM_TYPE>::remove_domain (
  IDL::traits<::DDS::DomainParticipant>::ref_type participant)
{
  DDS4CCM_LOG_TRACE ("DDS_Base_Connector_T::remove_domain");

  DDS4CCM_LOG_INFO("DDS_Base_Connector_T::remove_domain with participant <"
                   << IDL::traits<DDS::Entity>::write<entity_formatter> (participant) << ">");

  if (DPMANAGER->unregister_participant (
    this->domain_id_, this->qos_profile_, participant))
  {
    DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_domain - "
      << "Going to remove participant <"
      << IDL::traits<DDS::Entity>::write<entity_formatter> (participant)
      << "> for domain <" << this->domain_id_ << "> with qos <"
      << this->qos_profile_ << ">.");

    ::DDS::ReturnCode_t const retcode = this->participant_factory_->delete_participant (participant);

    if (retcode != DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Base_Connector_T::remove_domain - "
        << "Error removing participant for domain <" << this->domain_id_
        << "> with qos <" << this->qos_profile_ << "> - return code <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw CCM_DDS::InternalError (retcode, 0);
    }
    else
    {
      DDS4CCM_LOG_DEBUG ("DDS_Base_Connector_T::remove_domain - "
        << "Removed participant for domain <" << this->domain_id_
        << "> with qos <" << this->qos_profile_ << "> - return code <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
    }
  }
}
