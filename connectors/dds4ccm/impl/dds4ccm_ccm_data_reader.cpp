// -*- C++ -*-
/**
 * @file    dds4ccm_ccm_data_reader.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for the DataReader
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm_ccm_data_reader.h"
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm_sample_info.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    CCM_DataReader::CCM_DataReader (
      IDL::traits<CORBA::Object>::weak_ref_type component)
      : FacetBase< ::DDS::CCM_DataReader > (component)
    {
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::enable ()
    {
      return this->dds_entity_->enable ();
    }

    IDL::traits< ::DDS::StatusCondition>::ref_type
    CCM_DataReader::get_statuscondition ()
    {
      return this->dds_entity_->get_statuscondition ();
    }

    ::DDS::StatusMask
    CCM_DataReader::get_status_changes ()
    {
      return this->dds_entity_->get_status_changes ();
    }

    ::DDS::InstanceHandle_t
    CCM_DataReader::get_instance_handle ()
    {
      return this->dds_entity_->get_instance_handle ();
    }

    IDL::traits< ::DDS::ReadCondition>::ref_type
    CCM_DataReader::create_readcondition (
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states)
    {
      return this->dds_entity_->create_readcondition (sample_states,
                                                      view_states,
                                                      instance_states);
    }

    IDL::traits< ::DDS::QueryCondition>::ref_type
    CCM_DataReader::create_querycondition (
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states,
      const std::string &query_expression,
      const ::DDS::StringSeq & query_parameters)
    {
      return this->dds_entity_->create_querycondition (sample_states,
                                                        view_states,
                                                        instance_states,
                                                        query_expression,
                                                        query_parameters);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::delete_readcondition (
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
    {
      return this->dds_entity_->delete_readcondition (std::move(a_condition));
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::delete_contained_entities ()
    {
      return this->dds_entity_->delete_contained_entities ();
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::set_qos (
      const ::DDS::DataReaderQos & qos)
    {
      return this->dds_entity_->set_qos (qos);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_qos (
      ::DDS::DataReaderQos & qos)
    {
      return this->dds_entity_->get_qos (qos);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::set_listener (
      IDL::traits< ::DDS::DataReaderListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      return this->dds_entity_->set_listener (std::move(a_listener), mask);
    }

    IDL::traits< ::DDS::DataReaderListener>::ref_type
    CCM_DataReader::get_listener ()
    {
      return this->dds_entity_->get_listener ();
    }

    IDL::traits< ::DDS::TopicDescription>::ref_type
    CCM_DataReader::get_topicdescription ()
    {
      return this->dds_entity_->get_topicdescription();
    }

    IDL::traits< ::DDS::Subscriber>::ref_type
    CCM_DataReader::get_subscriber ()
    {
      return this->dds_entity_->get_subscriber ();
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_sample_rejected_status (
      ::DDS::SampleRejectedStatus & status)
    {
      return this->get_dds_entity ()->get_sample_rejected_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_liveliness_changed_status (
      ::DDS::LivelinessChangedStatus & status)
    {
      return this->dds_entity_->get_liveliness_changed_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_requested_deadline_missed_status (
      ::DDS::RequestedDeadlineMissedStatus & status)
    {
      return this->dds_entity_->get_requested_deadline_missed_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_requested_incompatible_qos_status (
      ::DDS::RequestedIncompatibleQosStatus & status)
    {
      return this->dds_entity_->get_requested_incompatible_qos_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_subscription_matched_status (
      ::DDS::SubscriptionMatchedStatus & status)
    {
      return this->dds_entity_->get_subscription_matched_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_sample_lost_status (
      ::DDS::SampleLostStatus & status)
    {
      return this->dds_entity_->get_sample_lost_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::wait_for_historical_data (
      const ::DDS::Duration_t & max_wait)
    {
      return this->dds_entity_->wait_for_historical_data (max_wait);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_matched_publications (
      ::DDS::InstanceHandleSeq & publication_handles)
    {
      return this->dds_entity_->get_matched_publications (publication_handles);
    }

    ::DDS::ReturnCode_t
    CCM_DataReader::get_matched_publication_data (
      ::DDS::PublicationBuiltinTopicData & publication_data,
      const ::DDS::InstanceHandle_t& publication_handle)
    {
      return this->dds_entity_->get_matched_publication_data (publication_data,
                                                                publication_handle);
    }

    void
    CCM_DataReader::set_dds_entity (
      IDL::traits< ::DDS::DataReader>::ref_type dr)
    {
      DDS4CCM_LOG_TRACE ("CCM_DataReader::set_dds_entity");
      this->dds_entity_ = std::move(dr);
    }

    IDL::traits< ::DDS::DataReader>::ref_type
    CCM_DataReader::get_dds_entity ()
    {
      DDS4CCM_LOG_TRACE ("CCM_DataReader::get_dds_entity");

      return this->dds_entity_;
    }
  }
}
