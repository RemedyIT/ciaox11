// -*- C++ -*-
/**
 * @file    dds4ccm_dds_get_port_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds4ccm/logger/dds4ccm_log.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
DDS_Get_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::DDS_Get_Port_T (
  IDL::traits<CORBA::Object>::ref_type component)
  : DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (std::move(component))
{
  DDS4CCM_LOG_TRACE ("DDS_Get_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::DDS_Get_Port_T");
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Get_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_complete (
  IDL::traits<::DDS::Topic>::ref_type topic,
  IDL::traits<::DDS::Subscriber>::ref_type subscriber,
  const std::string &qos_profile)
{
  DDS4CCM_LOG_TRACE ("DDS_Get_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::configuration_complete");

  SubscriberBase_type::configuration_complete (topic, subscriber, qos_profile);

  if (this->dds4ccm_getter_)
  {
    this->dds4ccm_getter_->set_dds_reader (this->dds4ccm_reader_->get_dds_reader (), this->condition_manager_);
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::fresh_data_type>::ref_type
DDS_Get_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_fresh_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_Get_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_fresh_data");

  if (!this->dds4ccm_getter_)
  {
    this->dds4ccm_getter_ = CORBA::make_reference<DDS4CCM_Getter_type> (this->component_);
  }

  return this->dds4ccm_getter_;
}
