// -*- C++ -*-
/**
 * @file    dds4ccm_getter_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM getter
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_utils.h"
#include "dds4ccm/impl/dds4ccm_sample_info.h"
#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Getter_T (
      IDL::traits<CORBA::Object>::weak_ref_type component)
      : FacetBase<GETTER_TYPE> (std::move(component))
    {
      DDS4CCM_LOG_TRACE ("Getter_T::Getter_T");
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::ReturnCode_t
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get (
      TOPIC_SEQ_TYPE & data,
      ::DDS::SampleInfoSeq & sample_info,
      uint32_t max_samples)
    {
      DDS4CCM_LOG_TRACE ("Getter_T::get");

      IDL::traits< ::DDS::ReadCondition>::ref_type rc =
        this->condition_manager_->read_condition ();
      if (rc)
      {
        // Read, using the read condition
        return this->get (data, sample_info, max_samples, rc);
      }
      else
      {
        // A filter has been set. Use the appropriate query condition
        // to read data from DDS.
        IDL::traits< ::DDS::QueryCondition>::ref_type qc =
          this->condition_manager_->query_condition_getter ();
        if (!qc)
        {
          DDS4CCM_LOG_ERROR ("Getter_T::get - "
            "Unable to retrieve QueryCondition from "
            "Condition manager.");
          return ::DDS::RETCODE_ERROR;
        }
        return this->get (data, sample_info, max_samples, qc);
      }
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::ReturnCode_t
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get (
      TOPIC_SEQ_TYPE & data,
      ::DDS::SampleInfoSeq & sample_info,
      uint32_t max_samples,
      IDL::traits< ::DDS::QueryCondition>::ref_type qc)
    {
      DDS4CCM_LOG_TRACE ("Getter_T::get (w_condition)");

      if (qc)
      {
        return this->dds_reader_->read_w_condition (
                        data,
                        sample_info,
                        max_samples,
                        qc);
      }
      return ::DDS::RETCODE_ERROR;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::ReturnCode_t
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get (
      TOPIC_SEQ_TYPE & data,
      ::DDS::SampleInfoSeq & sample_info,
      uint32_t max_samples,
      IDL::traits< ::DDS::ReadCondition>::ref_type rd)
    {
      DDS4CCM_LOG_TRACE ("CIAO::DDS4CCM::Getter_T::get");

      if (rd)
      {
        return this->dds_reader_->read_w_condition (
                        data,
                        sample_info,
                        max_samples,
                        rd);
      }
      return ::DDS::RETCODE_ERROR;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_many (
      TOPIC_SEQ_TYPE& instances,
      ::CCM_DDS::ReadInfoSeq& infos)
    {
      DDS4CCM_LOG_TRACE ("Getter_T::get_many");

      if (!this->condition_manager_->wait (this->time_out_))
      {
        // Wait hasn't been triggered (no samples which match the attached
        // conditions are received).
        return false;
      }

      uint32_t max_samples = this->max_delivered_data_;
      if (max_samples == 0)
      {
        max_samples = ::DDS::LENGTH_UNLIMITED;
      }

      ::DDS::SampleInfoSeq sample_info;
      TOPIC_SEQ_TYPE data;

      ::DDS::ReturnCode_t const retcode =
        this->get (data, sample_info, max_samples);

      if (retcode == ::DDS::RETCODE_OK && data.size () >= 1)
        {
          // Determine which samples are valid and return these to
          // the caller.
          typename TOPIC_SEQ_TYPE::size_type number_read = 0;
          for (::DDS::SampleInfo const &si : sample_info)
          {
            if (si.valid_data ())
            {
              ++number_read;
            }
          }
          DDS4CCM_LOG_DEBUG ("Getter_T::get_many: "
            << "read <" << sample_info.size () << "> - valid <"
            << number_read << ">.");
          infos.resize (number_read);
          instances.resize (number_read);
          number_read = 0;
          for (typename TOPIC_SEQ_TYPE::size_type j = 0;
               j < data.size ();
               ++j)
          {
            if (sample_info[j].valid_data ())
            {
              infos[number_read] = ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (sample_info[j]);
              instances[number_read] = data[j];
              ++number_read;
            }
          }
        }
      else
      {
        // RETCODE_NO_DATA should be an error
        // because after a timeout there should be
        // data.
        DDS4CCM_LOG_ERROR ("Getter_T::get_many - "
          << "Error while reading from DDS: <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");

        ::DDS::ReturnCode_t const retcode_returnloan =
          this->dds_reader_->return_loan (data, sample_info);
        if (retcode_returnloan != ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_ERROR ("Getter_T::get_many - Error returning loan to DDS - <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode_returnloan)
            << ">.");
        }
        throw ::CCM_DDS::InternalError (retcode, 1);
      }

      ::DDS::ReturnCode_t const retcode_returnloan =
        this->dds_reader_->return_loan (data, sample_info);
      if (retcode_returnloan != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("Getter_T::get_many - Error returning loan to DDS - <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode_returnloan)
          << ">.");

        throw ::CCM_DDS::InternalError (retcode_returnloan, 1);
      }

      return true;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::Duration_t
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::time_out ()
    {
      DDS4CCM_LOG_TRACE ("Getter_T::time_out");

      return this->time_out_;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::time_out (
      const ::DDS::Duration_t & time_out)
    {
      this->time_out_ = time_out;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::CCM_DDS::DataNumber_t
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::max_delivered_data ()
    {
      return this->max_delivered_data_;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::max_delivered_data (
      ::CCM_DDS::DataNumber_t max_delivered_data)
    {
      this->max_delivered_data_ = max_delivered_data;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::set_dds_reader (
      IDL::traits< ::DDS::DataReader>::ref_type dr,
      SharedConditionManager condition_manager)
    {
      DDS4CCM_LOG_TRACE ("Getter_T::set_dds_reader");

      this->dds_reader_ = ::DDS::traits<TOPIC_TYPE>::narrow (dr);

      if (dr && !this->dds_reader_)
      {
        DDS4CCM_LOG_ERROR ("Getter_T::set_dds_reader - narrow failed.");
        throw ::CORBA::INTERNAL ();
      }
      this->condition_manager_ = condition_manager;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    IDL::traits< ::DDS::DataReader>::ref_type
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_dds_reader ()
    {
      return this->dds_reader_;
    }

    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Getter_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_one (
      TOPIC_TYPE &an_instance,
      ::CCM_DDS::ReadInfo &info)
    {
      DDS4CCM_LOG_TRACE ("Getter_T::get_one");

      if (!this->condition_manager_->wait (this->time_out_))
        {
          // None of the attached conditions have triggered wait.
          return false;
        }

      bool valid_data_read = false;

      // Read the samples one by one until a valid sample
      // has been found.
      while (!valid_data_read)
      {
        ::DDS::SampleInfoSeq sample_info;
        TOPIC_SEQ_TYPE data;

        ::DDS::ReturnCode_t const retcode = this->get (data, sample_info, 1);

        if (retcode == ::DDS::RETCODE_NO_DATA)
        {
          DDS4CCM_LOG_DEBUG ("Getter_T::get_one - "
            << "DDS returned <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">. No data available in DDS.");
          return false;
        }
        else if (retcode != ::DDS::RETCODE_OK)
        {
          // Something went wrong.
          DDS4CCM_LOG_ERROR ("Getter_T::get_one - "
            << "Error while reading from DDS: <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">.");

          ::DDS::ReturnCode_t const retcode_returnloan =
            this->dds_reader_->return_loan (data, sample_info);
          if (retcode_returnloan != ::DDS::RETCODE_OK)
            {
              DDS4CCM_LOG_ERROR ("Getter_T::get_one - Error returning loan to DDS - <"
                << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode_returnloan)
                << ">.");
            }

          throw ::CCM_DDS::InternalError (retcode, 1);
        }
        else if (data.size () == 1 && sample_info.front ().valid_data ())
        {
          DDS4CCM_LOG_DEBUG ("Getter_T::get_one - "
            "Read one valid sample from DDS.");

          // Add the valid sample to the list which will be returned
          // to the caller
          info = ::DDS4CCM::traits< ::DDS::SampleInfo>::to_readinfo (sample_info.front ());
          an_instance = data.front ();
          valid_data_read = true;
        }
        else
        {
          DDS4CCM_LOG_DEBUG ("Getter_T::get_one - "
            "No valid data available in DDS.");
        }

        // Return the loan of each read.
        ::DDS::ReturnCode_t const retcode_returnloan =
          this->dds_reader_->return_loan (data, sample_info);
        if (retcode_returnloan != ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_ERROR ("Getter_T::get_one - Error returning loan to DDS - <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode_returnloan)
            << ">.");

          throw ::CCM_DDS::InternalError (retcode_returnloan, 1);
        }
      }

      return valid_data_read;
    }
  }
}

