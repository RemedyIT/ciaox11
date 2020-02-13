// -*- C++ -*-
/**
 * @file    dds4ccm_data_listener_t.h
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef DDS4CCM_DATA_LISTENER_T_H_
#define DDS4CCM_DATA_LISTENER_T_H_

#include "dds4ccm/impl/dds4ccm_listener_base_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE, DDS4CCM_LISTENER_READ_TAKE LRT>
    class DataReaderListener_T;

    /**
     * @class DataReaderListenerBase_T
     * @brief Handle the on_data_available from DDS
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class DataReaderListenerBase_T
      : public ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    {
    public:
      /// Constructor
      explicit DataReaderListenerBase_T (
        const typename CCM_TYPE::event_strategy_type& evs,
        IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type control,
        SharedConditionManager condition_manager);

      /// Destructor
      virtual ~DataReaderListenerBase_T () = default;

      /// Publishes data to the user defined facet. Invokes on_one_data of on_many_data
      /// based on what's the end user configured in the DataListenerControl.
      virtual void
      on_data_available_i (
        IDL::traits< ::DDS::DataReader>::ref_type rdr,
        typename IDL::traits<typename CCM_TYPE::data_listener_type>::ref_type listener) override;

    private:
      /// Pure virtual helper method to get (read/take) data from DDS
      virtual ::DDS::ReturnCode_t
      get_data_i (
        typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples) override = 0;

      DataReaderListenerBase_T() = delete;
      DataReaderListenerBase_T(const DataReaderListenerBase_T&) = delete;
      DataReaderListenerBase_T(DataReaderListenerBase_T&&) = delete;
      DataReaderListenerBase_T& operator=(const DataReaderListenerBase_T&) = delete;
      DataReaderListenerBase_T& operator=(DataReaderListenerBase_T&&) = delete;
    };

    /**
     * @class DataReaderListener_T
     * @brief Handle the on_data_available from DDS in case a thread switch
     *        is configured.
     *
     * Takes the data from DDS, removing the data from DDS.
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class DataReaderListener_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, CIAOX11::DDS4CCM::DDS4CCM_TAKE>
      : public DataReaderListenerBase_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    {
    public:
      explicit DataReaderListener_T (
        const typename CCM_TYPE::event_strategy_type& evs,
        IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type control,
        SharedConditionManager condition_manager)
      : DataReaderListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (
          evs, std::move(control), condition_manager)
      {
      }
      ~DataReaderListener_T () = default;

    private:
      /// Helper method to take data from DDS
      ::DDS::ReturnCode_t get_data_i (
        typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples) override
      {
        return ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::take_data_i (
          std::move(reader), std::move(qc), data, sample_info, max_samples);
      }

      DataReaderListener_T() = delete;
      DataReaderListener_T(const DataReaderListener_T&) = delete;
      DataReaderListener_T(DataReaderListener_T&&) = delete;
      DataReaderListener_T& operator=(const DataReaderListener_T&) = delete;
      DataReaderListener_T& operator=(DataReaderListener_T&&) = delete;
    };

    /**
     * @class DataReaderListener_T
     * @brief Handle the on_data_available from DDS in case a thread switch
     *        is configured.
     *
     * Reads the data from DDS, leaving it in DDS.
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class DataReaderListener_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, CIAOX11::DDS4CCM::DDS4CCM_READ>
      : public DataReaderListenerBase_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    {
    public:
      explicit DataReaderListener_T (
        const typename CCM_TYPE::event_strategy_type& evs,
        IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type control,
        SharedConditionManager condition_manager)
      : DataReaderListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (
          evs, std::move(control), condition_manager)
      {
      }

      ~DataReaderListener_T () = default;

    private:
      /// Helper method to read data from DDS
      ::DDS::ReturnCode_t get_data_i (
        typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples) override
      {
        return ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_data_i (
          std::move(reader), std::move(qc), data, sample_info, max_samples);
      }

      DataReaderListener_T() = delete;
      DataReaderListener_T(const DataReaderListener_T&) = delete;
      DataReaderListener_T(DataReaderListener_T&&) = delete;
      DataReaderListener_T& operator=(const DataReaderListener_T&) = delete;
      DataReaderListener_T& operator=(DataReaderListener_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_data_listener_t.cpp"

#endif /* DDS4CCM_DATA_LISTENER_T_H_ */
