// -*- C++ -*-
/**
 * @file    dds4ccm_state_connector_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM State connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::~DDS_State_Connector_T ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::~DDS_State_Connector_T");
}

/**
  * @name DDS_Update
  * DDS_Update operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Observable_type *
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::observable ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::observable");

  if (!this->observable_)
  {
    this->observable_ = std::make_unique<Observable_type> (this->_this ());
  }
  return this->observable_.get ();
}


template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::observable_traits::data_type>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_observable_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_observable_data");

  return this->observable ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::CCM_DataWriter>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_observable_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_observable_dds_entity");

  return this->observable ()->get_dds_entity ();
}
//@}


/**
  * @name DDS_Read
  * DDS_Read operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::PassiveObserver_type *
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::passive_observer ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::passive_observer");

  if (!this->passive_observer_)
  {
    this->passive_observer_ = std::make_unique<PassiveObserver_type> (this->_this ());
  }
  return this->passive_observer_.get ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::passive_observer_traits::data_type>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_passive_observer_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_passive_observer_data");

  return this->passive_observer ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::CCM_DataReader>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_passive_observer_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_passive_observer_dds_entity");

  return this->passive_observer ()->get_dds_entity ();
}


template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_passive_observer_filter_config ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_passive_observer_filter_config");

  return this->passive_observer ()->get_filter_config ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
::CCM_DDS::QueryFilter
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::passive_observer_filter ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::passive_observer_filter");

  return this->passive_observer ()->filter ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::passive_observer_filter (
  const ::CCM_DDS::QueryFilter &filter)
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::passive_observer_filter");

  this->passive_observer ()->filter (filter);
}
//@}


/**
  * @name DDS_Get
  * DDS_Get operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::PullObserver_type *
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_observer ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::pull_observer");

  if (!this->pull_observer_)
  {
    this->pull_observer_ = std::make_unique<PullObserver_type> (this->_this ());
  }
  return this->pull_observer_.get ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::pull_observer_traits::fresh_data_type>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_observer_fresh_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_observer_fresh_data");

  return this->pull_observer ()->get_fresh_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::pull_observer_traits::data_type>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_observer_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_observer_data");

  return this->pull_observer ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_observer_filter_config ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_observer_filter_config");

  return this->pull_observer ()->get_filter_config ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::CCM_DataReader>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_observer_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_pull_observer_dds_entity");

  return this->pull_observer ()->get_dds_entity ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
CCM_DDS::QueryFilter
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_observer_filter ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::pull_observer_filter");

  return this->pull_observer ()->filter ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_observer_filter (
  const CCM_DDS::QueryFilter &filter)
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::pull_observer_filter");

  this->pull_observer ()->filter (filter);
}
//@}


/**
  * @name DDS_Listen
  * DDS_Listen operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::PushObserver_type *
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_observer ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_observer");

  if (!this->push_observer_)
  {
    this->push_observer_ = std::make_unique<PushObserver_type> (this->_this ());
  }
  return this->push_observer_.get ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::push_observer_traits::data_type>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_observer_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_observer_data");

  return this->push_observer ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_DataListenerControl>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_observer_data_control ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_observer_data_control");

  return this->push_observer ()->get_data_control ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::CCM_DataReader>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_observer_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_observer_dds_entity");

  return this->push_observer ()->get_dds_entity ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_observer_filter_config ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_observer_filter_config");

  return this->push_observer ()->get_filter_config ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
CCM_DDS::QueryFilter
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_observer_filter ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_observer_filter");

  return this->push_observer ()->filter ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_observer_filter (
  const CCM_DDS::QueryFilter &filter)
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_observer_filter");

  this->push_observer ()->filter (filter);
}
//@}


/**
  * @name DDS_StateListen
  * DDS_StateListen operations
  */
//@{
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::PushStateObserver_type *
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_state_observer ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_state_observer");

  if (!this->push_state_observer_)
  {
    this->push_state_observer_ = std::make_unique<PushStateObserver_type> (this->_this ());
  }
  return this->push_state_observer_.get ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::push_state_observer_traits::data_type>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_state_observer_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_state_observer_data");

  return this->push_state_observer ()->get_data ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_StateListenerControl>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_state_observer_data_control ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_state_observer_data_control");

  return this->push_state_observer ()->get_data_control ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<::DDS::CCM_DataReader>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_state_observer_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_state_observer_dds_entity");

  return this->push_state_observer ()->get_dds_entity ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_push_state_observer_filter_config ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_push_state_observer_filter_config");

  return this->push_state_observer ()->get_filter_config ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
::CCM_DDS::QueryFilter
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_state_observer_filter ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_state_observer_filter");

  return this->push_state_observer ()->filter ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::push_state_observer_filter (
  const ::CCM_DDS::QueryFilter & filter)
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::push_state_observer_filter");

  this->push_state_observer ()->filter (filter);
}
//@}


template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::do_configuration_complete ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::do_configuration_complete");

  typename IDL::traits<typename CCM_TYPE::push_observer_traits::data_listener_type>::ref_type
    push_observer_data_listener =
      this->context ()->get_connection_push_observer_data_listener ();
  IDL::traits< CCM_DDS::PortStatusListener>::ref_type push_observer_psl =
    this->context ()->get_connection_push_observer_status ();

  typename IDL::traits<typename CCM_TYPE::push_state_observer_traits::data_listener_type>::ref_type
    push_state_observer_data_listener =
      this->context ()->get_connection_push_state_observer_data_listener ();
  IDL::traits< CCM_DDS::PortStatusListener>::ref_type push_state_observer_psl =
    this->context ()->get_connection_push_state_observer_status ();

  IDL::traits< CCM_DDS::PortStatusListener>::ref_type pull_observer_psl =
    this->context ()->get_connection_pull_observer_status ();

  IDL::traits< CCM_DDS::PortStatusListener>::ref_type passive_observer_psl =
    this->context ()->get_connection_passive_observer_status ();

  // Listeners can be connected (deploymentplan) without having
  // to connect a basic port. We need the basic ports when listeners
  // are configured (connected). Create them here.
  if (passive_observer_psl)
  {
    this->passive_observer ();
  }
  if (pull_observer_psl)
  {
    this->pull_observer ();
  }
  if (push_observer_data_listener || push_observer_psl)
  {
    this->push_observer ();
  }
  if (push_state_observer_data_listener || push_state_observer_psl)
  {
    this->push_state_observer ();
  }

  TopicBaseConnector::configuration_complete ();

  // Configure the basic ports which are connected.

  // Use the getters (topic, publisher etc) since these
  // will create the entities when they don't exist

  // Updater
  if (this->observable_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - Invoking configuration_complete on the observable port.");
    this->observable_->configuration_complete(
      this->topic (),
      this->publisher (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - No need to create observable port.");
  }

  // Reader
  if (this->passive_observer_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - Invoking configuration_complete on the passive observer port.");
    this->passive_observer_->configuration_complete (
      this->topic (),
      this->subscriber (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - No need to create passive observer port.");
  }

  // Getter
  if (this->pull_observer_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - Invoking configuration_complete on the pull observer port.");
    this->pull_observer_->configuration_complete (
      this->topic (),
      this->subscriber (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - No need to create pull observer port.");
  }

  // Data Listener
  if (this->push_observer_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - Invoking configuration_complete on the push observer port.");
    this->push_observer_->configuration_complete (
      this->topic (),
      this->subscriber (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - No need to create push observer port.");
  }

  // State Listener
  if (this->push_state_observer_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - "
      "Invoking configuration_complete on the push state observer port.");
    this->push_state_observer_->configuration_complete (
      this->topic (),
      this->subscriber (),
      this->qos_profile ());
  }
  else
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_State_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::do_configuration_complete - "
      "No need to create push state observer port.");
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::do_ccm_activate ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::do_ccm_activate");

  TopicBaseConnector::ccm_activate ();

  // Activate the basic ports which are connected.
  // No need to explicitly activate the Updater basic port.

  if (this->passive_observer_)
  {
    using event_strategy_type = typename CCM_TYPE::passive_observer_traits::event_strategy_type;

    this->passive_observer_->activate (
      event_strategy_type (this->context ()),
      this->context ()->get_connection_passive_observer_status ());
  }

  if (this->pull_observer_)
  {
    using event_strategy_type = typename CCM_TYPE::pull_observer_traits::event_strategy_type;

    this->pull_observer_->activate (
      event_strategy_type (this->context ()),
      this->context ()->get_connection_pull_observer_status ());
  }

  if (this->push_observer_)
  {
    using event_strategy_type = typename CCM_TYPE::push_observer_traits::event_strategy_type;

    this->push_observer_->activate (
      event_strategy_type (this->context ()),
      this->context ()->get_connection_push_observer_data_listener (),
      this->context ()->get_connection_push_observer_status ());
  }

  if (this->push_state_observer_)
  {
    using event_strategy_type = typename CCM_TYPE::push_state_observer_traits::event_strategy_type;

    this->push_state_observer_->activate (
      event_strategy_type (this->context ()),
      this->context ()->get_connection_push_state_observer_data_listener (),
      this->context ()->get_connection_push_state_observer_status ());
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_passivate ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ccm_passivate");

  // No need to explicitly passivate the Updater basic port.

  try
  {
    // It could be that no topic name was set or that the topic name was
    // reset in this connector.
    if (!TopicBaseConnector::topic_name ().empty ())
    {
      // Remove the basic ports which are connected.
      // Using the members directly since the getters will create
      // one is it doesn't exist.
      if (this->passive_observer_)
      {
        this->passive_observer_->passivate ();
      }

      if (this->pull_observer_)
      {
        this->pull_observer_->passivate ();
      }

      if (this->push_observer_)
      {
        this->push_observer_->passivate ();
      }

      if (this->push_state_observer_)
      {
        this->push_state_observer_->passivate ();
      }

      TopicBaseConnector::ccm_passivate ();
    }
  }
  catch_dds4ccm_lifecycle_ex(ex, "DDS_State_Connector_T::ccm_passivate")
}


template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_State_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::do_ccm_remove ()
{
  DDS4CCM_LOG_TRACE ("DDS_State_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::do_ccm_remove");

  try
  {
    // It could be that no topic name was set or that the topic name was
    // reset in this connector.
    if (!TopicBaseConnector::topic_name ().empty ())
    {
      // Remove the basic ports which are connected.
      // Using the members directly since the getters will create
      // one is it doesn't exist.
      if (this->observable_ && this->publisher_)
      {
        this->observable_->remove (this->publisher_);
      }
      if (this->passive_observer_ && this->subscriber_)
      {
        this->passive_observer_->remove (this->subscriber_);
      }

      if (this->pull_observer_ && this->subscriber_)
      {
        this->pull_observer_->remove (this->subscriber_);
      }

      if (this->push_observer_ && this->subscriber_)
      {
        this->push_observer_->remove (this->subscriber_);
      }

      if (this->push_state_observer_ && this->subscriber_)
      {
        this->push_state_observer_->remove (this->subscriber_);
      }

      TopicBaseConnector::ccm_remove ();
    }
  }
  catch_dds4ccm_lifecycle_ex(ex, "DDS_State_Connector_T::do_ccm_remove")
}

