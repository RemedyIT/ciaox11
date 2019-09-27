// -*- C++ -*-
/**
 * @file    dds4ccm_reader_t.cpp
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM Reader implementation for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "dds4ccm/impl/dds4ccm_utils.h"

#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_sample_info.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Reader_T (
      IDL::traits< CORBA::Object >::weak_ref_type component)
      : FacetBase< READER_TYPE > (component)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::Reader_T");
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    SharedConditionManager
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::condition_manager ()
    {
      if (!this->condition_manager_)
      {
        DDS4CCM_LOG_ERROR ("Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::condition_manager - "
          "Condition manager not set. Throwing a InternalError");
        throw CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 0);
      }
      return this->condition_manager_;
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::InstanceHandle_t
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::check_handle (
      const TOPIC_TYPE &an_instance,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::check_handle");

      ::DDS::InstanceHandle_t const lookup_hnd =
        this->dds_reader_->lookup_instance (an_instance);

      return
        this->condition_manager ()->check_handle (
          instance_handle,
          lookup_hnd);
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    uint32_t
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_nr_valid_samples (
      const ::DDS::SampleInfoSeq &sample_infos,
      bool determine_last)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::get_nr_valid_samples");

      uint32_t nr_of_samples = 0;
      if (determine_last)
      {
        for (const ::DDS::SampleInfo &si : sample_infos)
        {
          if (si.valid_data () && si.sample_rank () == 0)
          {
            ++nr_of_samples;
          }
        }
      }
      else
      {
        for (const ::DDS::SampleInfo &si : sample_infos)
        {
          if (si.valid_data ())
          {
            ++nr_of_samples;
          }
        }
      }
      return nr_of_samples;
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::convert_data (
      const TOPIC_SEQ_TYPE &all_data,
      TOPIC_SEQ_TYPE &data_to_return,
      ::CCM_DDS::ReadInfoSeq &infos,
      const ::DDS::SampleInfoSeq &sample_info)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::convert_data");

      uint32_t samples_to_return =
        this->get_nr_valid_samples (sample_info, false);
      infos.resize (samples_to_return);
      data_to_return.resize (samples_to_return);

      ::DDS::SampleInfoSeq::size_type ix = 0;
      for (::DDS::SampleInfoSeq::size_type i = 0; i < sample_info.size (); ++i)
      {
        if (sample_info[i].valid_data ())
          {
            infos[ix] = ::DDS4CCM::traits< ::DDS::SampleInfo >::to_readinfo(sample_info[i]);
            data_to_return[ix] = all_data[i];
            ++ix;
          }
      }
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_w_instance (
      TOPIC_SEQ_TYPE &data,
      ::DDS::SampleInfoSeq &sample_info,
      const ::DDS::InstanceHandle_t& lookup_hnd,
      IDL::traits< ::DDS::QueryCondition >::ref_type qc)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::read_w_instance");

      DDS4CCM_LOG_DEBUG (
        "Reader_T::read_w_instance - Start reading with instance <"
        << IDL::traits< ::DDS::InstanceHandle_t >::write (lookup_hnd) << ">.");
      ::DDS::ReturnCode_t retcode = ::DDS::RETCODE_ERROR;

      if (qc)
      {
        retcode = this->dds_reader_->read_instance_w_condition (
          data, sample_info, ::DDS::LENGTH_UNLIMITED, lookup_hnd, qc);
      }
      else
      {
        retcode = this->dds_reader_->read_instance (
          data, sample_info, ::DDS::LENGTH_UNLIMITED, lookup_hnd,
          ::DDS::READ_SAMPLE_STATE | ::DDS::NOT_READ_SAMPLE_STATE,
          ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
          ::DDS::ALIVE_INSTANCE_STATE);
      }
      if (retcode != ::DDS::RETCODE_OK && retcode != ::DDS::RETCODE_NO_DATA)
        {
          // Return the loan but don't throw an exception since an error returning
          // the loan is less important than an error during the retrieval  of
          // data from DDS.
          this->return_loan (data, sample_info, false);
          DDS4CCM_LOG_ERROR ("Reader_T::read_w_instance - retval is <"
            << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
            << ">.");
          throw ::CCM_DDS::InternalError (retcode, 0);
        }
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_wo_instance (
      TOPIC_SEQ_TYPE &data,
      ::DDS::SampleInfoSeq &sample_info,
      IDL::traits< ::DDS::QueryCondition >::ref_type qc)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::read_wo_instance");

      ::DDS::ReturnCode_t retval = ::DDS::RETCODE_ERROR;

      if (qc)
      {
        retval = this->dds_reader_->read_w_condition (
                    data,
                    sample_info,
                    ::DDS::LENGTH_UNLIMITED,
                    qc);
      }
      else
      {
        retval = this->dds_reader_->read (
                    data,
                    sample_info,
                    ::DDS::LENGTH_UNLIMITED,
                    ::DDS::READ_SAMPLE_STATE | ::DDS::NOT_READ_SAMPLE_STATE,
                    ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
                    ::DDS::ALIVE_INSTANCE_STATE);
      }
      if (retval != ::DDS::RETCODE_OK && retval != ::DDS::RETCODE_NO_DATA)
      {
        // Return the loan but don't throw an exception since an error returning
        // the loan is less important than an error during the retrieval  of
        // data from DDS.
        this->return_loan (data, sample_info, false);
        DDS4CCM_LOG_ERROR ("Reader_T::read_wo_instance - retval is " << retval);
        throw ::CCM_DDS::InternalError (retval, 0);
      }
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::return_loan (
      TOPIC_SEQ_TYPE &data,
      ::DDS::SampleInfoSeq sample_info,
      bool throw_exception)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::return_loan");

      ::DDS::ReturnCode_t const retcode =
        this->dds_reader_->return_loan (data, sample_info);
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("Reader_T::return_loan - Error returning loan to DDS - <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        if (throw_exception)
        {
          throw ::CCM_DDS::InternalError (retcode, 0);
        }
      }
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_last (
      TOPIC_SEQ_TYPE &instances,
      ::CCM_DDS::ReadInfoSeq &infos)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::read_last");

      // This function has to return the last sample of all instances
      ::DDS::SampleInfoSeq sample_info;
      TOPIC_SEQ_TYPE data;

      IDL::traits< ::DDS::QueryCondition >::ref_type qc =
        this->condition_manager ()->query_condition_reader ();
      this->read_wo_instance (data, sample_info, qc);

      // Determine how many samples to return
      uint32_t const samples_to_return =
        this->get_nr_valid_samples (sample_info, true);

      infos.resize (samples_to_return);
      instances.resize (samples_to_return);
      ::DDS::SampleInfoSeq::size_type ix = 0;
      for (::DDS::SampleInfoSeq::size_type i = 0; i < sample_info.size (); ++i)
      {
        if (sample_info[i].valid_data () && sample_info[i].sample_rank () == 0)
        {
          infos[ix] = ::DDS4CCM::traits< ::DDS::SampleInfo >::to_readinfo(sample_info[i]);
          instances[ix] = data[i];
          ++ix;
        }
      }
      this->return_loan (data, sample_info);
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_all (
      TOPIC_SEQ_TYPE &instances,
      ::CCM_DDS::ReadInfoSeq &infos)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::read_all");

      // This function has to return all samples of all instances
      ::DDS::SampleInfoSeq sample_info;
      TOPIC_SEQ_TYPE data;

      IDL::traits< ::DDS::QueryCondition >::ref_type qc =
        this->condition_manager ()->query_condition_reader ();
      this->read_wo_instance (data, sample_info, qc);

      this->convert_data (data, instances, infos, sample_info);
      this->return_loan (instances, sample_info);
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_one_last (
      TOPIC_TYPE &an_instance,
      CCM_DDS::ReadInfo &info,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::read_one_last");

      ::DDS::InstanceHandle_t const lookup_hnd =
        this->check_handle (an_instance, instance_handle);

      ::DDS::SampleInfoSeq sample_info;
      TOPIC_SEQ_TYPE data;

      IDL::traits< ::DDS::QueryCondition >::ref_type qc =
        this->condition_manager ()->query_condition_reader ();
      this->read_w_instance (data, sample_info, lookup_hnd, qc);

      typename TOPIC_SEQ_TYPE::size_type sample = data.size ();
      DDS4CCM_LOG_DEBUG ("Reader_T::read_one_last - "
        "total number of samples <" << sample << ">.");
      while (sample > 0 && !sample_info[sample-1].valid_data ())
      {
        --sample;
      }
      if (sample > 0)
      {
        if (sample_info[sample-1].valid_data ())
        {
          an_instance = data[sample-1];
          info = ::DDS4CCM::traits< ::DDS::SampleInfo >::to_readinfo(sample_info[sample-1]);
        }
      }
      this->return_loan (data, sample_info);
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_one_all (
      const TOPIC_TYPE &an_instance,
      TOPIC_SEQ_TYPE &instances,
      ::CCM_DDS::ReadInfoSeq &infos,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::read_one_all");

      ::DDS::InstanceHandle_t const lookup_hnd =
        this->check_handle (an_instance, instance_handle);

      ::DDS::SampleInfoSeq sample_info;
      TOPIC_SEQ_TYPE data;

      IDL::traits< ::DDS::QueryCondition >::ref_type qc =
        this->condition_manager ()->query_condition_reader ();
      this->read_w_instance (data, sample_info, lookup_hnd, qc);
      this->convert_data (data, instances, infos, sample_info);
      this->return_loan (instances, sample_info);
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::CCM_DDS::QueryFilter
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::query ()
    {
      DDS4CCM_LOG_TRACE ("Reader_T::query");

      return this->condition_manager ()->query ();
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::query (
      const ::CCM_DDS::QueryFilter &query)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::query");

      this->condition_manager ()->query (query);
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::set_dds_reader (
      IDL::traits< ::DDS::DataReader >::ref_type dr,
      SharedConditionManager condition_manager)
    {
      DDS4CCM_LOG_TRACE ("Reader_T::set_dds_reader");

      this->dds_reader_ = ::DDS::traits<TOPIC_TYPE>::narrow (dr);

      if (dr && !this->dds_reader_)
      {
        DDS4CCM_LOG_ERROR ("Reader_T::set_dds_reader - narrow failed.");
        throw ::CORBA::INTERNAL ();
      }
      this->condition_manager_ = condition_manager;
    }

    template <typename READER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    IDL::traits< ::DDS::DataReader >::ref_type
    Reader_T<READER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_dds_reader ()
    {
      DDS4CCM_LOG_TRACE ("Reader_T::get_dds_reader");

      return this->dds_reader_;
    }
  }
}
