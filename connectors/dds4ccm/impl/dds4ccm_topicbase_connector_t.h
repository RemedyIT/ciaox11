// -*- C++ -*-
/**
 * @file    dds4ccm_topicbase_connector_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_TOPICBASE_CONNECTOR_H
#define DDS4CCM_TOPICBASE_CONNECTOR_H

#include "dds4ccm/impl/dds4ccm_base_connector_t.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_TopicBase_Connector_T
  : public virtual DDS_Base_Connector_T<CCM_TYPE>
{
public:
  DDS_TopicBase_Connector_T () = default;
  virtual ~DDS_TopicBase_Connector_T () = default;

  /**
   * @name attributes of DDS4CCM TopicBase
   * Attributes of DDS4CCM TopicBase
   */
  //@{
  virtual void
  topic_name (
    const std::string &topic_name) override;

  virtual std::string
  topic_name () override;

  virtual void
  type_name (
    const std::string &type_name) override;

  virtual std::string
  type_name () override;
  //@}

  /**
   * @name life cycle methods
   * Life cycle methods, specific for this class.
   */
  //@{
  virtual void configuration_complete () override;
  virtual void ccm_activate () override;
  virtual void ccm_passivate () override;
  virtual void ccm_remove () override;
  //@}

  /**
   * @name type registration
   * Overriden from the base connector
   * For users to register/unregister their type.
   */
  //@{
  virtual void
  register_type (
    IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    const std::string &typesupport_name) override;

  virtual void
  unregister_type (
    IDL::traits< ::DDS::DomainParticipant >::ref_type participant,
    const std::string &typesupport_name) override;
  //@}

protected:
  /**
   * @name late bind
   * Setter/Getter which indicate late binding of topics
   *
   */
    //@{
  bool
  late_binding ();

  void
  late_binding (
    bool late_binding);
  //@}

  /// Actual determination whether a topic is late binded.
  bool
  late_binded (
    const std::string &topic_name);

  /// Determines whether to stop DDS in case of a topic reset.
  bool
  stop_dds (
    const std::string &topic_name);

  /**
   * @name DDS entity getters
   *
   * Getters for the DDS entities. Will init the
   * entities if not already initialized.
   */
  IDL::traits< ::DDS::DomainParticipant >::ref_type domain_participant ();
  IDL::traits< ::DDS::Topic >::ref_type topic ();
  IDL::traits< ::DDS::Publisher >::ref_type publisher ();
  IDL::traits< ::DDS::Subscriber >::ref_type subscriber ();

  typedef DDS_Base_Connector_T<CCM_TYPE> BaseConnector;

  IDL::traits< ::DDS::Publisher >::ref_type publisher_;
  IDL::traits< ::DDS::Subscriber >::ref_type subscriber_;

private:
  std::string topic_name_;
  std::string type_name_;

  IDL::traits< ::DDS::DomainParticipant >::ref_type domain_participant_;

  IDL::traits< ::DDS::Topic >::ref_type topic_;
  IDL::traits< ::DDS::TopicListener >::ref_type topic_listener_;

  IDL::traits< ::DDS::PublisherListener >::ref_type publisher_listener_;

  IDL::traits< ::DDS::SubscriberListener >::ref_type subscriber_listener_;


  /// Indicates whether a topic is late binded.
  bool late_binding_ { false };

  DDS_TopicBase_Connector_T(const DDS_TopicBase_Connector_T&) = delete;
  DDS_TopicBase_Connector_T(DDS_TopicBase_Connector_T&&) = delete;
  DDS_TopicBase_Connector_T& operator=(const DDS_TopicBase_Connector_T&) = delete;
  DDS_TopicBase_Connector_T& operator=(DDS_TopicBase_Connector_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_topicbase_connector_t.cpp"

#endif /* DDS4CCM_TOPICBASE_CONNECTOR_H */
