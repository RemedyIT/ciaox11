// -*- C++ -*-
/**
 * @file    dds4ccm_listener_base_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_sample_info.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ListenerBase_T (
      const typename CCM_TYPE::event_strategy_type& evs,
      IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type control,
      SharedConditionManager condition_manager)
      : PortStatusListener_T<typename CCM_TYPE::event_strategy_type> (evs) ,
        control_ (std::move(control)),
        condition_manager_ (condition_manager)
    {
      DDS4CCM_LOG_TRACE ("ListenerBase_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ListenerBase_T");
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::on_data_available (
      IDL::traits< ::DDS::DataReader>::ref_type rdr)
    {
      DDS4CCM_LOG_TRACE ("ListenerBase_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::on_data_available");

      if (rdr && this->control_ && this->control_->mode () != ::CCM_DDS::ListenerMode::NOT_ENABLED)
      {
        auto drl = IDL::traits< ListenerBase_type>::narrow (this->_this ());
        this->evs_.handle_data_available_event<ListenerBase_type> (drl, rdr);
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::StatusMask
    ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_mask (
      typename IDL::traits<typename CCM_TYPE::data_listener_type>::ref_type listener,
      IDL::traits< ::CCM_DDS::PortStatusListener>::ref_type status)
    {
      DDS4CCM_LOG_TRACE ("ListenerBase_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_mask");

      ::DDS::StatusMask mask { ::DDS::STATUS_MASK_NONE };

      if (listener)
      {
        mask = ::DDS::DATA_AVAILABLE_STATUS;
        mask |= PortStatusListener_T<typename CCM_TYPE::event_strategy_type>::get_mask (status);
      }

      DDS4CCM_LOG_DEBUG ("ListenerBase_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::get_mask - Mask becomes <"
        << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask)
        << ">.");
      return mask;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::ReturnCode_t
    ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::take_data_i (
      typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
      IDL::traits< ::DDS::QueryCondition>::ref_type qc,
      TOPIC_SEQ_TYPE &data,
      ::DDS::SampleInfoSeq &sample_info,
      int32_t max_samples)
    {
      DDS4CCM_LOG_TRACE ("ListenerBase_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take_data_i");

      ::DDS::ReturnCode_t result = ::DDS::RETCODE_OK;
      if (qc)
      {
        result = reader->take_w_condition (data,
                                           sample_info,
                                           max_samples,
                                           qc);
      }
      else
      {
        result = reader->take (data,
                               sample_info,
                               max_samples,
                               ::DDS::NOT_READ_SAMPLE_STATE,
                               ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
                               ::DDS::ANY_INSTANCE_STATE);
      }
      return result;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::ReturnCode_t
    ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_data_i (
      typename ::DDS::traits< TOPIC_TYPE>::typed_datareader_ref_type reader,
      IDL::traits< ::DDS::QueryCondition>::ref_type qc,
      TOPIC_SEQ_TYPE &data,
      ::DDS::SampleInfoSeq &sample_info,
      int32_t max_samples)
    {
      DDS4CCM_LOG_TRACE ("ListenerBase_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read_data_i");

      ::DDS::ReturnCode_t result = ::DDS::RETCODE_OK;
      if (qc)
      {
        result = reader->read_w_condition (data,
                                           sample_info,
                                           max_samples,
                                           qc);
      }
      else
      {
        result = reader->read (data,
                               sample_info,
                               max_samples,
                               ::DDS::NOT_READ_SAMPLE_STATE,
                               ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
                               ::DDS::ANY_INSTANCE_STATE);
      }
      return result;
    }
  }
}
