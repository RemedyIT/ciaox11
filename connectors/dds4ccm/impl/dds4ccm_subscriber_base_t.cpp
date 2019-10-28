// -*- C++ -*-
/**
 * @file    dds4ccm_subscriber_base_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"


template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::~DDS_Subscriber_Base_T ()
{
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::DDS_Subscriber_Base_T (
  IDL::traits< CORBA::Object >::ref_type component)
  : component_ (component.weak_reference ())
  , condition_manager_ (std::make_shared< CIAOX11::DDS4CCM::ConditionManager > ())
{
  // DDS_Subscriber_Base_T is the base for the Subscribing extended ports (DDS_Get,
  // DDS_Listen, DDS_Read). When one of these is connected, the basic DataReader
  // is always used; the getter uses is to 'get' data from DDS, this listener to
  // read or to take data from DDS. Therefor this basic port can be created upon
  // construction
  this->dds4ccm_reader_ = CORBA::make_reference<DDS4CCM_Reader_type> (this->component_);
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
IDL::traits<CIAOX11::DDS4CCM::CCM_DDS_ContentFilterSetting_i>::ref_type
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::create_cft_setting_impl ()
{
  if (!this->cft_setting_)
  {
    this->cft_setting_ = CORBA::make_reference<CIAOX11::DDS4CCM::CCM_DDS_ContentFilterSetting_i> ();
  }
  return this->cft_setting_;
}

/**
 * Life cycle methods
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_complete (
  IDL::traits< ::DDS::Topic >::ref_type topic,
  IDL::traits< ::DDS::Subscriber >::ref_type subscriber,
  const std::string &qos_profile)
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_complete");

  this->configuration_complete_ = true;

  if (!this->dds4ccm_reader_->get_dds_reader ())
  {
    // Subscriber, so might need to filter the data. When a
    // 'filter_config' (see ccm_dds.idl) connection is created, and
    // a filter is configured in the deployment plan, a contentfiltered
    // topic should be needed. This in addition to the given topic.
    IDL::traits< ::DDS::TopicDescription >::ref_type td (topic);
    if (this->cft_setting_)
    {
      if (!this->cft_setting_->filter ().expression ().empty ())
      {
        IDL::traits< ::DDS::ContentFilteredTopic >::ref_type cft =
          this->cft_setting_->create_contentfilteredtopic (topic, subscriber);
        if (!cft)
        {
          DDS4CCM_LOG_ERROR (
            "DDS_Subscriber_Base_T::configuration_complete: "
            "Error creating ContentFilteredTopic.");
          throw ::CORBA::INTERNAL ();
        }
        td = cft;
      }
    }

    IDL::traits< ::DDS::DataReader >::ref_type dr;
    if (!qos_profile.empty ())
    {
      // A QOS profile is set in the deployment plan; need to apply that.
      dr = subscriber->create_datareader_with_profile (
             td, qos_profile, nullptr, 0);
    }
    else
    {
      // To create a datareader, the qos should be passed. In order o pass a
      // valid qos we first retrieve it from DDS itself.
      ::DDS::DataReaderQos drqos;
      ::DDS::ReturnCode_t const retcode =
        subscriber->get_default_datareader_qos (drqos);

      if (retcode != DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR (
          "DDS_Subscriber_Base_T::configuration_complete - "
          "Error: Unable to retrieve get_default_datareader_qos: <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CCM_DDS::InternalError (retcode, 0);
      }
      // Create a datareader without a listener; this will be set
      // upon activation.
      dr = subscriber->create_datareader (
            td, drqos, nullptr, 0);
    }
    if (dr)
    {
      DDS4CCM_LOG_DEBUG (
        "DDS_Subscriber_Base_T::configuration_complete - "
        "Created DataReader <"
        << IDL::traits<DDS::Entity>::write<entity_formatter> (dr)
        << ">, using subscriber <"
        << IDL::traits<DDS::Entity>::write<entity_formatter> (subscriber)
        << ">.");
    }
    else
    {
      DDS4CCM_LOG_ERROR (
        "DDS_Subscriber_Base_T::configuration_complete - "
        "Error: DDS returned a nil datareader.");
      throw ::CORBA::INTERNAL ();
    }

    // The reader has been created. Now distribute it to the various
    // parts of the subscriber
    this->dds4ccm_reader_->set_dds_reader (dr, this->condition_manager_);
    // Could be that the CCM reader is a nullptr
    if (this->ccm_data_reader_)
    {
      this->ccm_data_reader_->set_dds_entity (dr);
    }
    this->condition_manager_->set_dds_entity (dr);
    this->condition_manager_->init_read_condition ();

    ::DDS::ReturnCode_t const retcode = dr->enable ();
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR (
        "DDS_Subscriber_Base_T::configuration_complete - "
        "Error: Unable to enable the datareader: <"
        << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
        << ">.");
      throw ::CORBA::INTERNAL ();
    }
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::activate (
    const typename CCM_TYPE::event_strategy_type &evs,
    IDL::traits< CCM_DDS::PortStatusListener >::ref_type status)
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::activate");

  typedef ::CIAOX11::DDS4CCM::PortStatusListener_T<typename CCM_TYPE::event_strategy_type>
    PortStatusListener_type;

  ::DDS::StatusMask const mask =
      PortStatusListener_type::get_mask (status);

  // Add the listener to the datareader (if needed)
  if (mask != 0)
  {
    if (!this->listener_)
    {
      this->listener_ =
        DDS::make_reference< PortStatusListener_type > (
          evs);
    }

    IDL::traits< ::DDS::DataReader >::ref_type dr = this->dds4ccm_reader_->get_dds_reader ();

    if (dr)
    {
      ::DDS::ReturnCode_t const retcode =
        dr->set_listener (this->listener_, mask);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR (
          "DDS_Subscriber_Base_T::activate - "
          "Error while setting the listener on the datareader - <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CORBA::INTERNAL ();
      }
    }
    else
    {
      DDS4CCM_LOG_ERROR (
        "DDS_Subscriber_Base_T::activate - "
        "Error while retrieving the DataReader");
      throw ::CORBA::INTERNAL ();
    }
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::passivate ()
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::passivate");

  this->condition_manager_->passivate ();

  // Remove the listeners
  IDL::traits< ::DDS::DataReader >::ref_type dr = this->dds4ccm_reader_->get_dds_reader ();
  if (dr && this->listener_)
  {
    DDS4CCM_LOG_DEBUG (
      "DDS_Subscriber_Base_T::passivate - "
      "Setting the listener on the reader to nil");

    ::DDS::ReturnCode_t const retcode =
      dr->set_listener (nullptr, 0);
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR (
        "DDS_Subscriber_Base_T::passivate - "
        "Error while setting the listener on the reader - <"
        << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
        << ">.");
      throw ::CORBA::INTERNAL ();
    }
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::remove (
  IDL::traits< ::DDS::Subscriber >::ref_type subscriber)
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::remove");

  // Need to empty the reader port since a topic can be re-bounded
  // to this connector
  if (this->ccm_data_reader_)
  {
    this->ccm_data_reader_->set_dds_entity (nullptr);
  }
  this->condition_manager_->set_dds_entity (nullptr);


  IDL::traits< ::DDS::DataReader >::ref_type dr =
    this->dds4ccm_reader_->get_dds_reader ();

  if (dr)
  {
    this->dds4ccm_reader_->set_dds_reader (nullptr, nullptr);

    DDS4CCM_LOG_DEBUG ("DDS_Subscriber_Base_T::remove - "
      << "Going to remove DataReader "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (dr)
      << " from subscriber "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (subscriber));

    ::DDS::ReturnCode_t const retcode =
      subscriber->delete_datareader (dr);

    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Subscriber_Base_T::remove - "
        << "Unable to remove DataReader: <"
        << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
        << ">.");
      throw ::CORBA::INTERNAL ();
    }
    else
    {
      DDS4CCM_LOG_DEBUG ("DDS_Subscriber_Base_T::remove - "
        "Deleted datareader.");
    }
  }
  // Delete the contentfiltered topic as last.
  if (this->cft_setting_)
  {
    this->cft_setting_->delete_contentfilteredtopic (subscriber);
  }
}

/**
 * Context methods.
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits< typename CCM_TYPE::data_type >::ref_type
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_data");

  return this->dds4ccm_reader_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits< typename CCM_TYPE::dds_entity_type >::ref_type
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_dds_entity");

  if (!this->ccm_data_reader_)
  {
    this->ccm_data_reader_ = CORBA::make_reference<CCM_DataReader_type> (this->component_);
  }
  return this->ccm_data_reader_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits< typename CCM_TYPE::filter_config_type >::ref_type
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_filter_config ()
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_filter_config");

  return this->create_cft_setting_impl ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
CCM_DDS::QueryFilter
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::filter ()
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::filter (get)");

  return this->create_cft_setting_impl ()->filter ();
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::filter (
  const ::CCM_DDS::QueryFilter & filter)
{
  DDS4CCM_LOG_TRACE ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::filter (set)");
  if (this->configuration_complete_)
  {
    DDS4CCM_LOG_ERROR ("DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::filter - "
      "Error: Not allowed to set the filter after configuration_complete. Throwing a "
      "CCM_DDS::NonChangeable exception.");
    throw CCM_DDS::NonChangeable ();
  }
  else
  {
    this->create_cft_setting_impl ()->filter (filter);
  }
}
