// -*- C++ -*-
/**
 * @file    dds4ccm_listener_base_t.h
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_LISTENER_BASE_T_H_
#define DDS4CCM_LISTENER_BASE_T_H_

#include "dds4ccm/impl/dds4ccm_condition_manager.h"
#include "dds4ccm_port_status_listener_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    /**
     * @class ListenerBase_T
     * @brief Handle the on_data_available from DDS in case a thread switch
     *        is configured.
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class ListenerBase_T
      : public PortStatusListener_T<typename CCM_TYPE::event_strategy_type>
    {
    typedef ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
      ListenerBase_type;

    typedef typename CCM_TYPE::event_strategy_type
        EventStrategy_type;

    public:
      /// Constructor
      explicit ListenerBase_T (
        const typename CCM_TYPE::event_strategy_type& evs,
        IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type control,
        SharedConditionManager condition_manager);

      /// Destructor
      virtual ~ListenerBase_T () = default;

      /// Implements the thread switch
      void
      on_data_available (IDL::traits< ::DDS::DataReader>::ref_type rdr) override;

      /// Publishes data to the user defined facet. Invokes on_one_data of on_many_data
      /// based on what's the end user configured in the DataListenerControl.
      virtual void on_data_available_i (
          IDL::traits< ::DDS::DataReader>::ref_type rdr,
          typename IDL::traits<typename CCM_TYPE::data_listener_type>::ref_type listener) = 0;

      static ::DDS::StatusMask get_mask (
        typename IDL::traits<typename CCM_TYPE::data_listener_type>::ref_type listener,
        IDL::traits< ::CCM_DDS::PortStatusListener>::ref_type status);

      static ::DDS::ReturnCode_t take_data_i (
        typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples);

      static ::DDS::ReturnCode_t read_data_i (
        typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples);

    protected:
      IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type control_;
      SharedConditionManager condition_manager_;

    private:
      /// Pure virtual helper method to get (read/take) data from DDS
      virtual ::DDS::ReturnCode_t get_data_i (
        typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc,
        TOPIC_SEQ_TYPE &data,
        ::DDS::SampleInfoSeq &sample_info,
        int32_t max_samples) = 0;

      ListenerBase_T() = delete;
      ListenerBase_T(const ListenerBase_T&) = delete;
      ListenerBase_T(ListenerBase_T&&) = delete;
      ListenerBase_T& operator=(const ListenerBase_T&) = delete;
      ListenerBase_T& operator=(ListenerBase_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_listener_base_t.cpp"

#endif /* DDS4CCM_LISTENER_BASE_T_H_ */
