// -*- C++ -*-
/**
 * @file    dds_data_writer_t.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DATA_WRITER_T_H_
#define DDSX11_IMPL_DATA_WRITER_T_H_

#include "dds/dds_data_writer.h"

namespace DDSX11
{
  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  class DataWriter_T final
    : public virtual TYPED_WRITER_TYPE
    , public virtual DDS_DataWriter_proxy
  {
  public:
    explicit DataWriter_T (
      DDS_Native::DDS::DataWriter * dw);

    virtual ~DataWriter_T ();

    ::DDS::ReturnCode_t
    set_qos (const ::DDS::DataWriterQos & qos) override;

    ::DDS::ReturnCode_t
    get_qos (::DDS::DataWriterQos & qos) override;

    ::DDS::ReturnCode_t
    set_listener (
      IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    IDL::traits< ::DDS::DataWriterListener>::ref_type
      get_listener () override;

    IDL::traits< ::DDS::Topic>::ref_type get_topic () override;

    IDL::traits< ::DDS::Publisher>::ref_type get_publisher () override;

    ::DDS::ReturnCode_t
    wait_for_acknowledgments (
      const ::DDS::Duration_t & max_wait) override;

    ::DDS::ReturnCode_t
    get_liveliness_lost_status (
      ::DDS::LivelinessLostStatus & status) override;

    ::DDS::ReturnCode_t
    get_offered_deadline_missed_status (
      ::DDS::OfferedDeadlineMissedStatus & status) override;

    ::DDS::ReturnCode_t
    get_offered_incompatible_qos_status (
      ::DDS::OfferedIncompatibleQosStatus & status) override;

    ::DDS::ReturnCode_t
    get_publication_matched_status (
      ::DDS::PublicationMatchedStatus & status) override;

    ::DDS::ReturnCode_t assert_liveliness () override;

    ::DDS::ReturnCode_t
    get_matched_subscriptions (::DDS::InstanceHandleSeq & subscription_handles) override;

    ::DDS::ReturnCode_t
    get_matched_subscription_data (
      ::DDS::SubscriptionBuiltinTopicData & subscription_data,
      const ::DDS::InstanceHandle_t& subscription_handle) override;

    ::DDS::ReturnCode_t enable () override;

    IDL::traits< ::DDS::StatusCondition>::ref_type
    get_statuscondition () override;

    ::DDS::StatusMask get_status_changes () override;

    ::DDS::InstanceHandle_t get_instance_handle () override;

    ::DDS::InstanceHandle_t
    register_instance (
      const TOPIC_TYPE &instance_data) override;

    ::DDS::InstanceHandle_t
    register_instance_w_timestamp (
      const TOPIC_TYPE &instance_data,
      const ::DDS::Time_t & source_timestamp) override;

    ::DDS::ReturnCode_t
    unregister_instance (
      const TOPIC_TYPE &instance_data,
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::ReturnCode_t
    unregister_instance_w_timestamp (
      const TOPIC_TYPE &instance_data,
      const ::DDS::InstanceHandle_t& handle,
      const ::DDS::Time_t & source_timestamp) override;

    ::DDS::ReturnCode_t
    write (
      const TOPIC_TYPE &instance_data,
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::ReturnCode_t
    write_w_timestamp (
      const TOPIC_TYPE &instance_data,
      const ::DDS::InstanceHandle_t& handle,
      const ::DDS::Time_t & source_timestamp) override;

    ::DDS::ReturnCode_t
    dispose (
      const TOPIC_TYPE &instance_data,
      const ::DDS::InstanceHandle_t& instance_handle) override;

    ::DDS::ReturnCode_t
    dispose_w_timestamp (
      const TOPIC_TYPE &instance_data,
      const ::DDS::InstanceHandle_t& instance_handle,
      const ::DDS::Time_t & source_timestamp) override;

    ::DDS::ReturnCode_t
    get_key_value (
      TOPIC_TYPE &key_holder,
      const ::DDS::InstanceHandle_t& handle) override;

    ::DDS::InstanceHandle_t
    lookup_instance (
      const TOPIC_TYPE &instance_data) override;

    DDS_Native::DDS::DataWriter *get_native_entity () override;
    void clear_native_entity () override;

  private:
    NATIVE_TYPED_WRITER *native_entity ();

    NATIVE_TYPED_WRITER *native_entity_ {};
  };
}

#include "dds/dds_data_writer_t.cpp"

#endif /* DDSX11_IMPL_DATA_WRITER_T_H_ */
