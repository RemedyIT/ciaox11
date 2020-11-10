// -*- C++ -*-
/**
 * @file    dds4ccm_state_listener_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
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
    DataReaderStateListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::DataReaderStateListenerBase_T (
      const typename CCM_TYPE::event_strategy_type &evs,
      IDL::traits< ::CCM_DDS::StateListenerControl>::ref_type control,
      SharedConditionManager condition_manager)
      : ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (evs, std::move(control), condition_manager)
    {
      DDS4CCM_LOG_TRACE ("DataReaderStateListenerBase_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::DataReaderStateListenerBase_T");
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    DataReaderStateListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::on_data_available_i (
      IDL::traits< ::DDS::DataReader>::ref_type rdr,
      typename IDL::traits<typename CCM_TYPE::data_listener_type>::ref_type listener)
    {
      DDS4CCM_LOG_TRACE ("DataReaderStateListenerBase_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::on_data_available_i");

      if (!rdr)
      {
        DDS4CCM_LOG_ERROR ("DataReaderStateListenerBase_T<"
          << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::on_data_available_i - No datareader received.");
        return;
      }

      ::CCM_DDS::ListenerMode const mode = this->control_->mode ();
      if (mode == ::CCM_DDS::ListenerMode::NOT_ENABLED)
      {
        // Listener is not enabled so return here
        return;
      }

      // Narrow to a type specific datareader
      typename ::DDS::traits<TOPIC_TYPE>::typed_datareader_ref_type reader =
        ::DDS::traits<TOPIC_TYPE>::narrow (rdr);

      if (!reader)
      {
        DDS4CCM_LOG_ERROR ("DataReaderStateListenerBase_T<"
          << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << "::on_data_available_i - Failed to narrow DataReader to a type specific DataReader.");
        return;
      }

      try
      {
        TOPIC_SEQ_TYPE data;
        ::DDS::SampleInfoSeq sample_info;
        int32_t max_samples = this->control_->max_delivered_data ();

        if (mode == ::CCM_DDS::ListenerMode::ONE_BY_ONE ||
          this->control_->max_delivered_data () == 0)
        {
          // Read everything. In case ONE_BY_ONE, the samples are provided to
          // the user one by one (on_one_data);
          // in case MANY_BY_MANY all samples are provided
          // to the user in one go (on_many_data).
          max_samples = ::DDS::LENGTH_UNLIMITED;
        }

        ::DDS::ReturnCode_t const retcode =
          this->get_data_i (reader,
            this->condition_manager_->query_condition_listener (),
            data, sample_info, max_samples);

        DDS4CCM_LOG_DEBUG ("DataReaderStateListenerBase_T<"
          << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::on_data_available_i - Get data returned <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");

        if (retcode == ::DDS::RETCODE_NO_DATA)
        {
          return;
        }
        else if (retcode != ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_ERROR ("DataReaderStateListenerBase_T<"
            << ::DDS::traits<TOPIC_TYPE>::get_type_name()
            << ">::on_data_available_i - Unable to get data from data reader: result <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">.");
          return;
        }
        if (mode == ::CCM_DDS::ListenerMode::ONE_BY_ONE)
        {
          typename TOPIC_SEQ_TYPE::size_type topic_idx = 0;
          for (::DDS::SampleInfo const &si : sample_info)
          {
            // Sample data may not be valid anymore when
            // deleted so don't check the valid_data flag
            // here.
            if (si.instance_state () == ::DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
            {
              listener->on_deletion (data[topic_idx],
                ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (si));
            }
            else if (si.valid_data ())
            {
              if (si.view_state () == ::DDS::NEW_VIEW_STATE)
              {
                listener->on_creation (data[topic_idx],
                  ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (si));
              }
              else
              {
                listener->on_one_update (data[topic_idx],
                  ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (si));
              }
            }
            ++topic_idx;
          }
        }
        else if (mode == ::CCM_DDS::ListenerMode::MANY_BY_MANY)
        {
          typedef std::vector<uint32_t> Updates;
          Updates updates;

          uint32_t idx_to_add = 0;
          for (::DDS::SampleInfo const &si : sample_info)
          {
            if ((si.valid_data () && si.view_state () == ::DDS::NEW_VIEW_STATE) ||
              si.instance_state () == ::DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
            {
              if (!updates.empty ())
              {
                // Sample_new or sample_delete found -> first send out the
                // updated samples in one go
                TOPIC_SEQ_TYPE inst_seq        (updates.size ());
                ::CCM_DDS::ReadInfoSeq infoseq (updates.size ());

                uint32_t ix = 0;
                for(uint32_t add : updates)
                {
                  infoseq[ix]  = ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (sample_info[add]);
                  inst_seq[ix] = data[add];
                  ++ix;
                }
                listener->on_many_updates (inst_seq, infoseq);
                // Clean up
                updates.clear ();
              }
              // Now invoke on_creation or on_deletion
              if (si.valid_data () && si.view_state () == ::DDS::NEW_VIEW_STATE)
              {
                listener->on_creation (data[idx_to_add],
                  ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (si));
              }
              else if (si.instance_state () == ::DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
              {
                listener->on_deletion (data[idx_to_add],
                  ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (si));
              }
            }
            else if (si.valid_data ())
            {
              updates.push_back (idx_to_add);
            }
            ++idx_to_add;
          }
          // Send the latest updates.
          if (!updates.empty ())
          {
            TOPIC_SEQ_TYPE         inst_seq (updates.size ());
            ::CCM_DDS::ReadInfoSeq infoseq  (updates.size ());

            uint32_t ix = 0;
            for (uint32_t add : updates)
            {
              infoseq[ix]  = ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (sample_info[add]);
              inst_seq[ix] = data[add];
              ++ix;
            }
            listener->on_many_updates (inst_seq, infoseq);
          }
        }
        // Return the loan
        ::DDS::ReturnCode_t const retcode_returnloan =
          reader->return_loan (data, sample_info);
        if (retcode_returnloan != ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_ERROR ("DataReaderStateListenerBase_T<"
            << ::DDS::traits<TOPIC_TYPE>::get_type_name()
            << ">::on_data_available_i - Error returning loan to DDS - <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode_returnloan)
            << ">.");
          // No exception here since this the DDS vendor doesn't expect this.
          // It will likely causes a crash in their implementation
        }
      }
      catch_dds4ccm_listener_ex(ex, "DataReaderStateListenerBase_T::on_data_available_i")
    }
  }
}
