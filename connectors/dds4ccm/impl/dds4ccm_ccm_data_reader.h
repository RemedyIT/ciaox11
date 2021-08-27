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
    class DDS4CCM_IMPL_Export CCM_DataReader
      : public virtual FacetBase< ::DDS::CCM_DataReader>
    {
    public:
      /// Constructor
      explicit CCM_DataReader (IDL::traits<CORBA::Object>::weak_ref_type component);

      /// Destructor
      virtual ~CCM_DataReader () = default;

      /**
       * IDL defined wrapper methods.
       */
      //@{
      ::DDS::ReturnCode_t enable () override;

      IDL::traits< ::DDS::StatusCondition>::ref_type
      get_statuscondition () override;

      ::DDS::StatusMask get_status_changes () override;

      ::DDS::InstanceHandle_t get_instance_handle () override;

      IDL::traits< ::DDS::ReadCondition>::ref_type
      create_readcondition (
        ::DDS::SampleStateMask,
        ::DDS::ViewStateMask,
        ::DDS::InstanceStateMask) override;

      IDL::traits< ::DDS::QueryCondition>::ref_type
      create_querycondition (
        ::DDS::SampleStateMask,
        ::DDS::ViewStateMask,
        ::DDS::InstanceStateMask,
        const std::string & ,
        const ::DDS::StringSeq & ) override;

      ::DDS::ReturnCode_t
      delete_readcondition (IDL::traits< ::DDS::ReadCondition>::ref_type) override;

      ::DDS::ReturnCode_t
      delete_contained_entities () override;

      ::DDS::ReturnCode_t
      set_qos (const ::DDS::DataReaderQos & ) override;

      ::DDS::ReturnCode_t
      get_qos (::DDS::DataReaderQos & ) override;

      ::DDS::ReturnCode_t
      set_listener (
        IDL::traits< ::DDS::DataReaderListener>::ref_type,
        ::DDS::StatusMask) override;

      IDL::traits< ::DDS::DataReaderListener>::ref_type
      get_listener () override;

      IDL::traits< ::DDS::TopicDescription>::ref_type
      get_topicdescription () override;

      IDL::traits< ::DDS::Subscriber>::ref_type
      get_subscriber () override;

      ::DDS::ReturnCode_t
      get_sample_rejected_status (
        ::DDS::SampleRejectedStatus & ) override;

      ::DDS::ReturnCode_t
      get_liveliness_changed_status (
        ::DDS::LivelinessChangedStatus & ) override;

      ::DDS::ReturnCode_t
      get_requested_deadline_missed_status (
        ::DDS::RequestedDeadlineMissedStatus & ) override;

      ::DDS::ReturnCode_t
      get_requested_incompatible_qos_status (
        ::DDS::RequestedIncompatibleQosStatus &  ) override;

      ::DDS::ReturnCode_t
      get_subscription_matched_status (
        ::DDS::SubscriptionMatchedStatus & ) override;

      ::DDS::ReturnCode_t
      get_sample_lost_status (
        ::DDS::SampleLostStatus & ) override;

      ::DDS::ReturnCode_t
      wait_for_historical_data (
        const ::DDS::Duration_t & ) override;

      ::DDS::ReturnCode_t
      get_matched_publications (
        ::DDS::InstanceHandleSeq & ) override;

      ::DDS::ReturnCode_t
      get_matched_publication_data (::DDS::PublicationBuiltinTopicData & ,
        const ::DDS::InstanceHandle_t&) override;
      //@}

      /**
       * Helper methods.
       */
      //@{
      void
      set_dds_entity (IDL::traits< ::DDS::DataReader>::ref_type dr);

      IDL::traits< ::DDS::DataReader>::ref_type
      get_dds_entity ();
      //@}

    private:
      IDL::traits< ::DDS::DataReader>::ref_type dds_entity_;

      CCM_DataReader() = delete;
      CCM_DataReader(const CCM_DataReader&) = delete;
      CCM_DataReader(CCM_DataReader&&) = delete;
      CCM_DataReader& operator=(const CCM_DataReader&) = delete;
      CCM_DataReader& operator=(CCM_DataReader&&) = delete;
    };
  }
}

#endif /* DDS4CCM_CCM_DATA_READER_H_ */
