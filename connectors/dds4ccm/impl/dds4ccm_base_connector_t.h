// -*- C++ -*-
/**
 * @file    dds4ccm_base_connector_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM Base connector.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_BASE_CONNECTOR_T_H_
#define DDS4CCM_BASE_CONNECTOR_T_H_

#include "dds4ccm/logger/dds4ccm_log.h"

#include "dds4ccm_sample_info.h"

template <typename CCM_TYPE>
class DDS_Base_Connector_T
  : public virtual CCM_TYPE::base_type
{
public:
  DDS_Base_Connector_T ();
  virtual ~DDS_Base_Connector_T ();

  /**
   * @name domain_id
   * Accessors for domain_id
   */
  //@{
  virtual ::DDS::DomainId_t
  domain_id () override;

  virtual void
  domain_id (
    ::DDS::DomainId_t domain_id) override;
  //@}

  /**
   * @name qos_profile
   * Accessors for qos_profile
   */
  //@{
  virtual std::string
  qos_profile () override;

  virtual void
  qos_profile (
    const std::string &qos_profile) override;
  //@}

  /**
   * Sets the context of the connector.
   * The context is used to make connections to the user component,
   * like the interfaces to the data listeners.
   */
  virtual void
  set_session_context (
    IDL::traits<Components::SessionContext >::ref_type ctx) override;

private:
  DDS_Base_Connector_T(const DDS_Base_Connector_T&) = delete;
  DDS_Base_Connector_T(DDS_Base_Connector_T&&) = delete;
  DDS_Base_Connector_T& operator=(const DDS_Base_Connector_T&) = delete;
  DDS_Base_Connector_T& operator=(DDS_Base_Connector_T&&) = delete;

protected:

  /**
   * Initialization of a connector.
   *
   * When one wants to use his own DDS::DomainParticipant, DDS::Topic,
   * DDS::Subscriber and/or DDS::Publisher, these helper methods allows
   * to create these, independent of the DDS vendor.
   *
   * These methods will create the DDS4CCM Entities (and therefor the DDS
   * entities in DDS itself), like DomainParticipant, Topic, Subscriber and Publisher
   *
   */
  //@{
  IDL::traits< ::DDS::DomainParticipant >::ref_type
  init_domain ();

  virtual void
  register_type (IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    const std::string &typesupport_name) = 0;

  IDL::traits< ::DDS::Topic >::ref_type
  init_topic (IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    const std::string &topic_name,
    const std::string &type_name);

  IDL::traits< ::DDS::Publisher >::ref_type
  init_publisher (IDL::traits< ::DDS::DomainParticipant >::ref_type participant);

  IDL::traits< ::DDS::Subscriber >::ref_type
  init_subscriber (IDL::traits< ::DDS::DomainParticipant >::ref_type participant);
  //@}

  /**
   * Activation of a connector.
   *
   * Helper methods to create the DDS listeners and attach them to the DDS Entities.
   * This will activate the DDS Entities.
   *
   */
  //@{
  IDL::traits< ::DDS::TopicListener >::ref_type
  activate_topic (IDL::traits< ::DDS::Topic >::ref_type topic);

  IDL::traits< ::DDS::PublisherListener >::ref_type
  activate_publisher (IDL::traits< ::DDS::Publisher >::ref_type publisher);

  IDL::traits< ::DDS::SubscriberListener >::ref_type
  activate_subscriber (IDL::traits< ::DDS::Subscriber >::ref_type subscriber);
  //@}

  /**
   * Passivation of a connector.
   *
   * Helper methods to detach the DDS listeners from the DDS Entities.
   * This will passivate the DDS Entities.
   *
   */
  //@{
  void
  passivate_topic (IDL::traits< ::DDS::Topic >::ref_type topic,
    IDL::traits< ::DDS::TopicListener >::ref_type topic_listener);

  void
  passivate_publisher (IDL::traits< ::DDS::Publisher >::ref_type publisher,
    IDL::traits< ::DDS::PublisherListener >::ref_type publisher_listener);
  void
  passivate_subscriber (IDL::traits< ::DDS::Subscriber >::ref_type subscriber,
    IDL::traits< ::DDS::SubscriberListener >::ref_type subscriber_listener);
  //@}

   /**
   * Removal of a connector.
   *
   * Helper methods to remove the DDS Entities from memory.
   */
  //@{
  void
  remove_topic (IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    IDL::traits< ::DDS::Topic >::ref_type topic);

  void
  remove_publisher (IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    IDL::traits< ::DDS::Publisher >::ref_type publisher);

  void
  remove_subscriber (IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    IDL::traits< ::DDS::Subscriber >::ref_type subscriber);

  void
  remove_domain (IDL::traits< ::DDS::DomainParticipant >::ref_type participant);

  virtual
  void
  unregister_type (IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    const std::string &typesupport_name) = 0;
  //@}

  /**
   * Protected getters and setters
   */
  /// Get configuration_completed
  bool
  configuration_completed ();

  /// Set configuration_completed
  void
  configuration_completed (bool configuration_completed);

  /// Get the context of this connector.
  typename IDL::traits< typename CCM_TYPE::context_type >::ref_type
  context ();

private:
  /**
   * @name attributes of DDS4CCM base
   * Attributes of DDS4CCM Base
   */
  //@{
  ::DDS::DomainId_t domain_id_ {};
  std::string       qos_profile_ {};
  //@}

  /**
   * Indicates whether configuration_complete has been invoked. Once invoked,
   * changing a connector attribute is not allowed anymore. If the user still
   * wants to set an attribute, a NonChangeable exception is thrown.
    */
  bool configuration_completed_ { false };

  /**
   * Context of the connector. Used to make connections to the user component
   * like the interfaces to the data listeners.
   */
  typename IDL::traits< typename CCM_TYPE::context_type >::ref_type context_;

  /**
   * DomainParticipantFactory. Administration of Domain Participants
   */
  IDL::traits< ::DDS::DomainParticipantFactory >::ref_type participant_factory_;
};

#include "dds4ccm/impl/dds4ccm_base_connector_t.cpp"

#endif /* DDS4CCM_BASE_CONNECTOR_T_H_ */
