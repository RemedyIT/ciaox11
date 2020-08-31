// -*- C++ -*-
/**
 * @file    dds_data_reader_t.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DATA_READER_T_H_
#define DDSX11_IMPL_DATA_READER_T_H_

#include "dds/dds_data_reader.h"

namespace DDSX11
{
  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename RTI_SEQ_TYPE>
  class DataReader_T final
    : public virtual TYPED_READER_TYPE
    , public virtual DDS_DataReader_proxy
  {
  public:
    /// Constructor
    explicit DataReader_T (DDS_Native::DDS::DataReader * dr);

    /// Destructor
    virtual ~DataReader_T () = default;

    ::DDS::ReturnCode_t
    read (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    ::DDS::ReturnCode_t
    take (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    ::DDS::ReturnCode_t
    read_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition) override;

    ::DDS::ReturnCode_t
    take_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition) override;

    ::DDS::ReturnCode_t
    read_next_sample (
      TOPIC_TYPE & data_values,
      ::DDS::SampleInfo & sample_info) override;

    ::DDS::ReturnCode_t
    take_next_sample (
      TOPIC_TYPE & data_values,
      ::DDS::SampleInfo & sample_info) override;

    ::DDS::ReturnCode_t
    read_instance (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& a_handle,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    ::DDS::ReturnCode_t
    take_instance (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& a_handle,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    ::DDS::ReturnCode_t
    read_instance_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq& sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& a_handle,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition) override;

    ::DDS::ReturnCode_t
    take_instance_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq& sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& a_handle,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition) override;

    ::DDS::ReturnCode_t
    read_next_instance (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& previous_handle,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    ::DDS::ReturnCode_t
    take_next_instance (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& previous_handle,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    ::DDS::ReturnCode_t
    read_next_instance_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& previous_handle,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition) override;

    ::DDS::ReturnCode_t
    take_next_instance_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& previous_handle,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition) override;

    ::DDS::ReturnCode_t
    return_loan (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos) override;

    ::DDS::ReturnCode_t
    get_key_value (
      TOPIC_TYPE & key_holder,
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::InstanceHandle_t
    lookup_instance (
      const TOPIC_TYPE& an_instance) override;

    ::DDS::ReturnCode_t enable () override;

    IDL::traits< ::DDS::StatusCondition>::ref_type get_statuscondition () override;

    ::DDS::StatusMask get_status_changes () override;

    ::DDS::InstanceHandle_t get_instance_handle () override;

    IDL::traits< ::DDS::ReadCondition>::ref_type
    create_readcondition (
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    IDL::traits< ::DDS::QueryCondition>::ref_type
    create_querycondition (
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states,
      const std::string &query_expression,
      const ::DDS::StringSeq &query_parameters) override;

    ::DDS::ReturnCode_t
    delete_readcondition (
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition) override;

    ::DDS::ReturnCode_t delete_contained_entities () override;

    ::DDS::ReturnCode_t
    set_qos (const ::DDS::DataReaderQos & qos) override;

    ::DDS::ReturnCode_t
    get_qos (::DDS::DataReaderQos & qos) override;

    ::DDS::ReturnCode_t
    set_listener (
      IDL::traits< ::DDS::DataReaderListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    IDL::traits< ::DDS::DataReaderListener>::ref_type
    get_listener () override;

    IDL::traits< ::DDS::TopicDescription>::ref_type
    get_topicdescription () override;

    IDL::traits< ::DDS::Subscriber>::ref_type
    get_subscriber () override;

    ::DDS::ReturnCode_t
    get_sample_rejected_status (
      ::DDS::SampleRejectedStatus & status) override;

    ::DDS::ReturnCode_t
    get_liveliness_changed_status (
      ::DDS::LivelinessChangedStatus & status) override;

    ::DDS::ReturnCode_t
    get_requested_deadline_missed_status (
      ::DDS::RequestedDeadlineMissedStatus & status) override;

    ::DDS::ReturnCode_t
    get_requested_incompatible_qos_status (
      ::DDS::RequestedIncompatibleQosStatus & status) override;

    ::DDS::ReturnCode_t
    get_subscription_matched_status (
      ::DDS::SubscriptionMatchedStatus & status) override;

    ::DDS::ReturnCode_t
    get_sample_lost_status (
      ::DDS::SampleLostStatus & status) override;

    ::DDS::ReturnCode_t
    wait_for_historical_data (
      const ::DDS::Duration_t & max_wait) override;

    ::DDS::ReturnCode_t
    get_matched_publications (
      ::DDS::InstanceHandleSeq & publication_handles) override;

    ::DDS::ReturnCode_t
    get_matched_publication_data (
      ::DDS::PublicationBuiltinTopicData & publication_data,
      const ::DDS::InstanceHandle_t& publication_handle) override;

    DDS_Native::DDS::DataReader *get_native_entity () override;

  private:
    NATIVE_TYPED_READER *native_entity ();

    NATIVE_TYPED_READER *native_entity_ {};

    //TODO Should not be done in a proxy!!! Issue 3989
    ::DDS::ReturnCode_t complete_read (
      RTI_SEQ_TYPE & dds_data_values,
      SEQ_TYPE & data_values,
      DDS_Native::DDS::SampleInfoSeq & dds_sample_infos,
      ::DDS::SampleInfoSeq & sample_infos,
      const ::DDS::ReturnCode_t & retcode,
      const std::string& method_name);
  };
}

#include "dds/dds_data_reader_t.cpp"

#endif /* DDSX11_IMPL_DATA_READER_T_H_ */
