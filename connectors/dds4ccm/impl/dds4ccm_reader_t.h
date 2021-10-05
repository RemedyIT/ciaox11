// -*- C++ -*-
/**
 * @file    dds4ccm_reader_t.h
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM Reader implementation for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_READER_T_H_
#define DDS4CCM_READER_T_H_

#include "dds4ccm/idl/ccm_ddsC.h"
#include "dds4ccm/impl/dds4ccm_condition_manager.h"
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class Reader_T
      : public virtual FacetBase< READER_TYPE >
    {
    public:
      explicit Reader_T (IDL::traits<CORBA::Object>::weak_ref_type component);
      ~Reader_T () override = default;

      void
      read_last (
        TOPIC_SEQ_TYPE &instances,
        CCM_DDS::ReadInfoSeq &infos) override;

      void
      read_all (
        TOPIC_SEQ_TYPE &instances,
        ::CCM_DDS::ReadInfoSeq &infos) override;

      void
      read_one_last (
        TOPIC_TYPE &an_instance,
        CCM_DDS::ReadInfo &info,
        const ::DDS::InstanceHandle_t& instance_handle) override;

      void
      read_one_all (
        const TOPIC_TYPE &an_instance,
        TOPIC_SEQ_TYPE &instances,
        CCM_DDS::ReadInfoSeq &infos,
        const ::DDS::InstanceHandle_t& instance_handle) override;

      ::CCM_DDS::QueryFilter
      query () override;

      void
      query (const CCM_DDS::QueryFilter &filter) override;

      void set_dds_reader (
        IDL::traits< ::DDS::DataReader>::ref_type dr,
        SharedConditionManager condition_manager);

      IDL::traits< ::DDS::DataReader>::ref_type
      get_dds_reader ();

    private:
      typename ::DDS::traits<TOPIC_TYPE>::typed_datareader_ref_type dds_reader_ {};

      SharedConditionManager condition_manager_ {};

      SharedConditionManager condition_manager ();

      /**
      * @name Reader helper methods
      */
      //@{

      /**
       * Checks the valid_data of each read sample. If determine_last is true,
       * this method also takes the sample_rank attribute into account.
       */
      uint32_t
      get_nr_valid_samples (
        const ::DDS::SampleInfoSeq& sample_infos,
        bool determine_last);

      /**
       * Check whether the given instance belongs to the given instance handle.
       * The instance handle of the instance will be retrieved from DDS by
       * calling 'lookup_instance'.
       */
      ::DDS::InstanceHandle_t
      check_handle (
        const TOPIC_TYPE &an_instance,
        const ::DDS::InstanceHandle_t& instance_handle);

      /**
       * DDS4CCM returns only the valid samples. This methods filters out
       * the invalid samples.
       */
      void
      convert_data (
        TOPIC_SEQ_TYPE &all_data,
        TOPIC_SEQ_TYPE &data_to_return,
        CCM_DDS::ReadInfoSeq &infos,
        const ::DDS::SampleInfoSeq &sample_info);

      /**
       * Switches between read_w_condition or just read
       */
      void
      read_wo_instance (
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc);

      /**
       * Switches between read_instance_w_condition or just read_instance
       */
      void
      read_w_instance (
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        const ::DDS::InstanceHandle_t& lookup_hnd,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc);

      /**
       * Uniform way of returning the loan of the read samples back to DDS.
       * Throwing an exception upon failure when indicated.
       */
      void
      return_loan (
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq sample_info,
        bool throw_exception=true);
      //@}

      Reader_T() = delete;
      Reader_T(const Reader_T&) = delete;
      Reader_T(Reader_T&&) = delete;
      Reader_T& operator=(const Reader_T&) = delete;
      Reader_T& operator=(Reader_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_reader_t.cpp"

#endif /* DDS4CCM_READER_T_H_ */

