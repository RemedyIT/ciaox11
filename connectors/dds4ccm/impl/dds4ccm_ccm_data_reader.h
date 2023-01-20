// -*- C++ -*-
/**
 * @file    dds4ccm_ccm_data_reader.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for the IDL defined DataReader
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_CCM_DATA_READER_H_
#define DDS4CCM_CCM_DATA_READER_H_

#include "dds_dcpsEC.h"
#include "dds4ccm/impl/dds4ccm_impl_export.h"
#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    /**
     * DataReader implementation which is the proxy to DDSX11 at the moment
     * the user code directly wants to use DDS
     */
    class DDS4CCM_IMPL_Export CCM_DataReader
      : public virtual FacetBase< ::DDS::CCM_DataReader>
    {
    public:
      /// Constructor
      explicit CCM_DataReader (IDL::traits<CORBA::Object>::weak_ref_type component);

      /// Destructor
      ~CCM_DataReader () override = default;

      /**
       * IDL defined wrapper methods.
       */
      //@{
      ::DDS::ReturnCode_t enable () override;

      IDL::traits<::DDS::StatusCondition>::ref_type
      get_statuscondition () override;

      ::DDS::StatusMask get_status_changes () override;

      ::DDS::InstanceHandle_t get_instance_handle () override;

      IDL::traits<::DDS::ReadCondition>::ref_type
      create_readcondition (
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) override;

      IDL::traits<::DDS::QueryCondition>::ref_type
      create_querycondition (
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states,
        const std::string &query_expression,
        const ::DDS::StringSeq &query_parameters) override;

      ::DDS::ReturnCode_t
      delete_readcondition (IDL::traits<::DDS::ReadCondition>::ref_type a_condition) override;

      ::DDS::ReturnCode_t
      delete_contained_entities () override;

      ::DDS::ReturnCode_t
      set_qos (const ::DDS::DataReaderQos &qos) override;

      ::DDS::ReturnCode_t
      get_qos (::DDS::DataReaderQos &qos) override;

      ::DDS::ReturnCode_t
      set_listener (
        IDL::traits<::DDS::DataReaderListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;

      IDL::traits<::DDS::DataReaderListener>::ref_type get_listener () override;

      IDL::traits<::DDS::TopicDescription>::ref_type get_topicdescription () override;

      IDL::traits<::DDS::Subscriber>::ref_type get_subscriber () override;

      ::DDS::ReturnCode_t
      get_sample_rejected_status (::DDS::SampleRejectedStatus &status) override;

      ::DDS::ReturnCode_t
      get_liveliness_changed_status (::DDS::LivelinessChangedStatus &status) override;

      ::DDS::ReturnCode_t
      get_requested_deadline_missed_status (::DDS::RequestedDeadlineMissedStatus &status) override;

      ::DDS::ReturnCode_t
      get_requested_incompatible_qos_status (::DDS::RequestedIncompatibleQosStatus &status) override;

      ::DDS::ReturnCode_t
      get_subscription_matched_status (::DDS::SubscriptionMatchedStatus &status) override;

      ::DDS::ReturnCode_t
      get_sample_lost_status (::DDS::SampleLostStatus &status) override;

      ::DDS::ReturnCode_t
      wait_for_historical_data (
        const ::DDS::Duration_t &max_wait) override;

      ::DDS::ReturnCode_t
      get_matched_publications (
        ::DDS::InstanceHandleSeq &publication_handles) override;

      ::DDS::ReturnCode_t
      get_matched_publication_data (::DDS::PublicationBuiltinTopicData &publication_data,
        const ::DDS::InstanceHandle_t&publication_handle) override;
      //@}

      /**
       * Helper methods.
       */
      //@{
      void
      set_dds_entity (IDL::traits<::DDS::DataReader>::ref_type dr);

      IDL::traits<::DDS::DataReader>::ref_type
      get_dds_entity ();
      //@}

    private:
      IDL::traits<::DDS::DataReader>::ref_type dds_entity_;

      CCM_DataReader() = delete;
      CCM_DataReader(const CCM_DataReader&) = delete;
      CCM_DataReader(CCM_DataReader&&) = delete;
      CCM_DataReader& operator=(const CCM_DataReader&) = delete;
      CCM_DataReader& operator=(CCM_DataReader&&) = delete;
    };
  }
}

#endif /* DDS4CCM_CCM_DATA_READER_H_ */
