// -*- C++ -*-
/**
 * @file    dds4ccm_ccm_data_writer.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for the DataWriter
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm_ccm_data_writer.h"
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm_sample_info.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    CCM_DataWriter::CCM_DataWriter (
      IDL::traits<CORBA::Object>::weak_ref_type component)
      : FacetBase< ::DDS::CCM_DataWriter> (component)
    {
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::enable ()
    {
      return this->dds_entity_->enable ();
    }

    IDL::traits<::DDS::StatusCondition>::ref_type
    CCM_DataWriter::get_statuscondition ()
    {
      return this->dds_entity_->get_statuscondition ();
    }

    ::DDS::StatusMask
    CCM_DataWriter::get_status_changes ()
    {
      return this->dds_entity_->get_status_changes ();
    }

    ::DDS::InstanceHandle_t
    CCM_DataWriter::get_instance_handle ()
    {
      return this->dds_entity_->get_instance_handle ();
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::set_qos (
      const ::DDS::DataWriterQos &qos)
    {
      return this->dds_entity_->set_qos (qos);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::get_qos (
      ::DDS::DataWriterQos &qos)
    {
      return this->dds_entity_->get_qos (qos);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::set_listener (
      IDL::traits<::DDS::DataWriterListener>::ref_type listener,
      ::DDS::StatusMask mask)
    {
      return this->dds_entity_->set_listener (std::move(listener), mask);
    }

    IDL::traits<::DDS::DataWriterListener>::ref_type
    CCM_DataWriter::get_listener ()
    {
      return this->dds_entity_->get_listener ();
    }

    IDL::traits<::DDS::Topic>::ref_type
    CCM_DataWriter::get_topic ()
    {
      return this->dds_entity_->get_topic ();
    }

    IDL::traits<::DDS::Publisher>::ref_type
    CCM_DataWriter::get_publisher ()
    {
      return this->dds_entity_->get_publisher ();
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::wait_for_acknowledgments (
      const ::DDS::Duration_t &duration)
    {
      return this->dds_entity_->wait_for_acknowledgments (duration);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::get_liveliness_lost_status (
      ::DDS::LivelinessLostStatus &status)
    {
      return this->dds_entity_->get_liveliness_lost_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::get_offered_deadline_missed_status (
      ::DDS::OfferedDeadlineMissedStatus &status)
    {
      return this->dds_entity_->get_offered_deadline_missed_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::get_offered_incompatible_qos_status (
      ::DDS::OfferedIncompatibleQosStatus &status)
    {
      return this->dds_entity_->get_offered_incompatible_qos_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::get_publication_matched_status (
      ::DDS::PublicationMatchedStatus &status)
    {
      return this->dds_entity_->get_publication_matched_status (status);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::assert_liveliness ()
    {
      return this->dds_entity_->assert_liveliness ();
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::get_matched_subscriptions (
      ::DDS::InstanceHandleSeq &seq)
    {
      return this->dds_entity_->get_matched_subscriptions (seq);
    }

    ::DDS::ReturnCode_t
    CCM_DataWriter::get_matched_subscription_data (
      ::DDS::SubscriptionBuiltinTopicData & data,
      const ::DDS::InstanceHandle_t& handle)
    {
      return this->dds_entity_->get_matched_subscription_data (data, handle);
    }

    void
    CCM_DataWriter::set_dds_entity (
      IDL::traits<::DDS::DataWriter>::ref_type dw)
    {
      DDS4CCM_LOG_TRACE ("CCM_DataWriter::set_dds_entity");

      this->dds_entity_ = std::move(dw);
    }

    IDL::traits<::DDS::DataWriter>::ref_type
    CCM_DataWriter::get_dds_entity ()
    {
      DDS4CCM_LOG_TRACE ("CCM_DataWriter::get_dds_entity");

      return this->dds_entity_;
    }
  }
}
