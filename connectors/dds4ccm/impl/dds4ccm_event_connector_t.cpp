// -*- C++ -*-
/**
 * @file    dds4ccm_event_connector_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM Event connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::~DDS_Event_Connector_T ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::~DDS_Event_Connector_T");
}

/**
  * @name DDS_Write
  * DDS_Write operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Supplier_type *
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::supplier ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::supplier");

  if (!this->supplier_)
  {
    this->supplier_ = std::make_unique<Supplier_type> (this->_this ());
  }
  return this->supplier_.get ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::supplier_traits::data_type>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_supplier_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_supplier_data");

  return this->supplier ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::supplier_traits::dds_entity_type>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_supplier_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_supplier_dds_entity");

  return this->supplier ()->get_dds_entity ();
}
//@}

/**
  * @name DDS_Get
  * DDS_Get operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::PullConsumer_type *
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_consumer ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::pull_consumer");

  if (!this->pull_consumer_)
  {
    this->pull_consumer_ = std::make_unique<PullConsumer_type> (this->_this ());
  }
  return this->pull_consumer_.get ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::pull_consumer_traits::fresh_data_type>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_consumer_fresh_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_consumer_fresh_data");

  return this->pull_consumer ()->get_fresh_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::pull_consumer_traits::data_type>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_consumer_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_consumer_data");

  return this->pull_consumer ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_consumer_filter_config ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_consumer_filter_config");

  return this->pull_consumer ()->get_filter_config ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::CCM_DataReader>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_consumer_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_consumer_dds_entity");

  return this->pull_consumer ()->get_dds_entity ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
CCM_DDS::QueryFilter
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_consumer_filter ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::pull_consumer_filter");

  return this->pull_consumer ()->filter ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_consumer_filter (
  const CCM_DDS::QueryFilter &filter)
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::pull_consumer_filter");

  this->pull_consumer ()->filter (filter);
}
//@}

/**
  * @name DDS_Listen
  * DDS_Listen operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::PushConsumer_type *
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_consumer ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_consumer");

  if (!this->push_consumer_)
  {
    this->push_consumer_ = std::make_unique<PushConsumer_type> (this->_this ());
  }
  return this->push_consumer_.get ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::push_consumer_traits::data_type>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_consumer_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_consumer_data");

  return this->push_consumer ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_DataListenerControl>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_consumer_data_control ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_consumer_data_control");

  return this->push_consumer ()->get_data_control ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::CCM_DataReader>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_consumer_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_consumer_dds_entity");

  return this->push_consumer ()->get_dds_entity ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_consumer_filter_config ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_consumer_filter_config");

  return this->push_consumer ()->get_filter_config ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
CCM_DDS::QueryFilter
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_consumer_filter ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_consumer_filter");

  return this->push_consumer ()->filter ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_consumer_filter (
  const CCM_DDS::QueryFilter &filter)
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_consumer_filter");

  this->push_consumer ()->filter (filter);
}
//@}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::do_configuration_complete ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::do_configuration_complete");

  typename IDL::traits<typename CCM_TYPE::push_consumer_traits::data_listener_type>::ref_type
    push_consumer_data_listener =
      this->context ()->get_connection_push_consumer_data_listener ();
  IDL::traits< CCM_DDS::PortStatusListener>::ref_type push_consumer_psl =
    this->context ()->get_connection_push_consumer_status ();
  IDL::traits< CCM_DDS::PortStatusListener>::ref_type pull_consumer_psl =
    this->context ()->get_connection_pull_consumer_status ();

  // Listeners can be connected (deploymentplan) without having
  // to connect a basic port. We need the basic ports when listeners
  // are configured (connected). Create them here.
  if (push_consumer_data_listener || push_consumer_psl)
  {
    this->push_consumer ();
  }
  if (pull_consumer_psl)
  {
    this->pull_consumer ();
  }

  TopicBaseConnector::configuration_complete ();

  // Configure the basic ports which are connected.
  // Use the getters (topic, publisher etc) since these
  // will create the entities when they don't exist
  if (this->push_consumer_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_Event_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - Invoking configuration_complete on the push consumer port.");
    this->push_consumer_->configuration_complete (
      this->topic (),
      this->subscriber (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_Event_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - No need to create push consumer port.");
  }

  if (this->supplier_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_Event_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - Invoking configuration_complete on the supplier consumer port.");
    this->supplier_->configuration_complete(
      this->topic (),
      this->publisher (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_Event_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - No need to create supplier port.");
  }

  if (this->pull_consumer_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_Event_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - Invoking configuration_complete on the pull consumer port.");
    this->pull_consumer_->configuration_complete (
      this->topic (),
      this->subscriber (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_Event_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - No need to create pull consumer port.");
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::do_ccm_activate ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::do_ccm_activate");

  TopicBaseConnector::ccm_activate ();

  // Activate the basic ports which are connected.
  // No need to explicitly activate the Writer basic port.
  if (this->push_consumer_)
  {
    using event_strategy_type = typename CCM_TYPE::push_consumer_traits::event_strategy_type;

    this->push_consumer_->activate (
      event_strategy_type (this->context ()),
      this->context ()->get_connection_push_consumer_data_listener (),
      this->context ()->get_connection_push_consumer_status ());
  }

  if (this->pull_consumer_)
  {
    using event_strategy_type = typename CCM_TYPE::pull_consumer_traits::event_strategy_type;

    this->pull_consumer_->activate (
      event_strategy_type (this->context ()),
      this->context ()->get_connection_pull_consumer_status ());
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_passivate ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ccm_passivate");

  // No need to explicitly passivate the Writer basic port.
  try
  {
    // It could be that no topic name was set or that the topic name was
    // reset in this connector.
    if (!TopicBaseConnector::topic_name ().empty ())
    {
      // Remove the basic ports which are connected.
      // Using the members directly since the getters will create
      // one is it doesn't exist.
      if (this->push_consumer_)
      {
        this->push_consumer_->passivate ();
      }

      if (this->pull_consumer_)
      {
        this->pull_consumer_->passivate ();
      }

      TopicBaseConnector::ccm_passivate ();
    }
  }
  catch_dds4ccm_lifecycle_ex(ex, "DDS_Event_Connector_T::ccm_passivate")
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::do_ccm_remove ()
{
  DDS4CCM_LOG_TRACE ("DDS_Event_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::do_ccm_remove");

  try
  {
    // It could be that no topic name was set or that the topic name was
    // reset in this connector.
    if (!TopicBaseConnector::topic_name ().empty ())
    {
      // Remove the basic ports which are connected.
      // Using the members directly since the getters will create
      // one is it doesn't exist.
      if (this->push_consumer_ && this->subscriber_)
      {
        this->push_consumer_->remove (this->subscriber_);
      }

      if (this->supplier_ && this->publisher_)
      {
        this->supplier_->remove (this->publisher_);
      }

      if (this->pull_consumer_ && this->subscriber_)
      {
        this->pull_consumer_->remove (this->subscriber_);
      }

      TopicBaseConnector::ccm_remove ();
    }
  }
  catch_dds4ccm_lifecycle_ex(ex, "DDS_Event_Connector_T::do_ccm_remove")
}
