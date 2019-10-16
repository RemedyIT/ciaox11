// -*- C++ -*-
/**
 * @file    dds4ccm_state_listener_t.h
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef DDS4CCM_STATE_LISTENER_T_H_
#define DDS4CCM_STATE_LISTENER_T_H_

#include "dds4ccm/impl/dds4ccm_listener_base_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE, DDS4CCM_LISTENER_READ_TAKE LRT>
    class DataReaderStateListener_T;

    /**
     * @class DataReaderStateListenerBase_T
     * @brief Handle the on_data_available from DDS in case a thread switch
     *        is configured.
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class DataReaderStateListenerBase_T
      : public ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    {
    public:
      explicit DataReaderStateListenerBase_T (
        const typename CCM_TYPE::event_strategy_type &evs,
        IDL::traits < ::CCM_DDS::StateListenerControl >::ref_type control,
        SharedConditionManager condition_manager);

      /// Destructor
      virtual ~DataReaderStateListenerBase_T () = default;

      void
      on_data_available_i (
        IDL::traits < ::DDS::DataReader >::ref_type rdr,
        typename IDL::traits< typename CCM_TYPE::data_listener_type >::ref_type listener) override;

    private:
      /// Helper method to get data from DDS
      virtual ::DDS::ReturnCode_t
      get_data_i (
        typename ::DDS::traits< TOPIC_TYPE >::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition >::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples) override = 0;

      DataReaderStateListenerBase_T() = delete;
      DataReaderStateListenerBase_T(const DataReaderStateListenerBase_T&) = delete;
      DataReaderStateListenerBase_T(DataReaderStateListenerBase_T&&) = delete;
      DataReaderStateListenerBase_T& operator=(const DataReaderStateListenerBase_T&) = delete;
      DataReaderStateListenerBase_T& operator=(DataReaderStateListenerBase_T&&) = delete;
    };

    /**
     * @class DataReaderListener_T
     * @brief Handle the on_data_available from DDS in case a thread switch
     *        is configured.
     *
     * Takes the data from DDS, removing the data from DDS.
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class DataReaderStateListener_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, CIAOX11::DDS4CCM::DDS4CCM_TAKE> final
      : public DataReaderStateListenerBase_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    {
    public:
      /// Constructor
      explicit DataReaderStateListener_T (
        const typename CCM_TYPE::event_strategy_type &evs,
        IDL::traits< ::CCM_DDS::StateListenerControl >::ref_type control,
        SharedConditionManager condition_manager)
      : DataReaderStateListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (
          evs, std::move(control), condition_manager)
      {
      }
    private:
      /// Helper method to take data from DDS
      ::DDS::ReturnCode_t get_data_i (
        typename ::DDS::traits< TOPIC_TYPE >::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition >::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples) override
      {
        return ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::take_data_i (
          std::move(reader), std::move(qc), data, sample_info, max_samples);
      }

      DataReaderStateListener_T() = delete;
      DataReaderStateListener_T(const DataReaderStateListener_T&) = delete;
      DataReaderStateListener_T(DataReaderStateListener_T&&) = delete;
      DataReaderStateListener_T& operator=(const DataReaderStateListener_T&) = delete;
      DataReaderStateListener_T& operator=(DataReaderStateListener_T&&) = delete;
    };

    /**
     * @class DataReaderStateListener_T
     * @brief Handle the on_data_available from DDS in case a thread switch
     *        is configured.
     *
     * Reads the data from DDS, leaving it in DDS.
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class DataReaderStateListener_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, CIAOX11::DDS4CCM::DDS4CCM_READ> final
      : public DataReaderStateListenerBase_T <CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    {
    public:
      /// Constructor
      explicit DataReaderStateListener_T (
        const typename CCM_TYPE::event_strategy_type &evs,
        IDL::traits< ::CCM_DDS::StateListenerControl >::ref_type control,
        SharedConditionManager condition_manager)
      : DataReaderStateListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (
          evs, std::move(control), condition_manager)
      {
      }

    private:
      /// Helper method to read data from DDS
      ::DDS::ReturnCode_t get_data_i (
        typename ::DDS::traits< TOPIC_TYPE >::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition >::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples) override
      {
        return ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_data_i (
          std::move(reader), std::move(qc), data, sample_info, max_samples);
      }

      DataReaderStateListener_T() = delete;
      DataReaderStateListener_T(const DataReaderStateListener_T&) = delete;
      DataReaderStateListener_T(DataReaderStateListener_T&&) = delete;
      DataReaderStateListener_T& operator=(const DataReaderStateListener_T&) = delete;
      DataReaderStateListener_T& operator=(DataReaderStateListener_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_state_listener_t.cpp"

#endif /* DDS4CCM_STATE_LISTENER_T_H_ */

