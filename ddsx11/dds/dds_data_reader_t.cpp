// -*- C++ -*-
/**
 * @file    dds_data_reader_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_data_reader_listener.h"
#include "dds/dds_status_condition.h"
#include "dds/dds_read_condition.h"
#include "dds/dds_query_condition.h"
#include "dds/dds_subscriber.h"
#include "dds/dds_topic_description.h"
#include "dds/dds_topic.h"
#include "dds/dds_content_filtered_topic.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_proxy_entity_manager.h"
#include "dds/dds_traits.h"

#include "logger/ddsx11_log.h"

// DDS vendor specific implementation part
#include "dds/dds_data_reader_native_entity_t.cpp"

namespace DDSX11
{
  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::complete_read (
      NATIVE_SEQ_TYPE & native_data_values,
      SEQ_TYPE & data_values,
      DDS_Native::DDS::SampleInfoSeq & native_sample_infos,
      ::DDS::SampleInfoSeq & sample_infos,
      const ::DDS::ReturnCode_t & retcode,
      const std::string& method_name)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::complete_read");

    if (retcode == ::DDS::RETCODE_OK)
    {
      sample_infos = ::DDSX11::traits< ::DDS::SampleInfoSeq, ::DDS_Native::DDS::SampleInfoSeq>::retn (native_sample_infos);
      data_values = typename ::DDSX11::traits<SEQ_TYPE>::retn (native_data_values);
    }
    else if (retcode != ::DDS::RETCODE_NO_DATA)
    {
      DDSX11_IMPL_LOG_ERROR ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::" << method_name << " - "
        << "Error while reading samples from DDS - <"
        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">");
    }

    ::DDS::ReturnCode_t const retcode_return_loan =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->return_loan (native_data_values, native_sample_infos));
    if (retcode_return_loan != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::" << method_name << " - Error returning loan to DDS - <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode_return_loan)
          << ">");
        // In case a read action from DDS causes errors, the users wants to see
        // this error (and not the return loan error).
        if (retcode == ::DDS::RETCODE_OK)
          return retcode_return_loan;
      }
    return retcode;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::read (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq & sample_infos,
      int32_t max_samples,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;

    ::DDS::ReturnCode_t const retcode_read =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->read (
          native_data_values,
          native_sample_infos,
          ::DDSX11::traits < int32_t>::in (max_samples),
          ::DDSX11::traits < ::DDS::SampleStateMask>:: in (sample_states),
          ::DDSX11::traits < ::DDS::ViewStateMask>:: in (view_states),
          ::DDSX11::traits < ::DDS::InstanceStateMask>:: in (instance_states)));

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_read, "read");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::take (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;

    ::DDS::ReturnCode_t const retcode_take =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->take (
          native_data_values,
          native_sample_infos,
          ::DDSX11::traits < int32_t>::in (max_samples),
          ::DDSX11::traits < ::DDS::SampleStateMask>:: in (sample_states),
          ::DDSX11::traits < ::DDS::ViewStateMask>:: in (view_states),
          ::DDSX11::traits < ::DDS::InstanceStateMask>:: in (instance_states)));

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_take, "read");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::read_w_condition (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read_w_condition");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;
    ::DDS::ReturnCode_t retcode_read_w_condition = ::DDS::RETCODE_OK;

    DDS_Native::DDS::ReadCondition *dds_rc =
      read_condition_trait::native (a_condition);

    if (dds_rc)
      {
        retcode_read_w_condition =
          ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
            this->native_entity ()->read_w_condition (
              native_data_values,
              native_sample_infos,
              ::DDSX11::traits<int32_t>::in (max_samples),
              dds_rc));
      }
    else
      {
        DDS_Native::DDS::QueryCondition *dds_qc =
          query_condition_trait::native (
            IDL::traits< ::DDS::QueryCondition>::narrow (a_condition));
        if (dds_qc)
          {
            retcode_read_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->read_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  dds_qc));
          }
        else
          {
            retcode_read_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->read_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  nullptr));
          }
      }
    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_read_w_condition, "read_w_condition");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::take_w_condition (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take_w_condition");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;
    ::DDS::ReturnCode_t retcode_take_w_condition = ::DDS::RETCODE_OK;

    DDS_Native::DDS::ReadCondition *dds_rc =
      read_condition_trait::native (a_condition);

    if (dds_rc)
      {
        retcode_take_w_condition =
          ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
            this->native_entity ()->take_w_condition (
              native_data_values,
              native_sample_infos,
              ::DDSX11::traits<int32_t>::in (max_samples),
              dds_rc));
      }
    else
      {
        DDS_Native::DDS::QueryCondition *dds_qc =
          query_condition_trait::native (
            IDL::traits< ::DDS::QueryCondition>::narrow (a_condition));
        if (dds_qc)
          {
            retcode_take_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->take_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  dds_qc));
          }
        else
          {
            retcode_take_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->take_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  nullptr));
          }
      }
    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_take_w_condition, "take_w_condition");
    return retcode_take_w_condition;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::read_next_sample (
    TOPIC_TYPE & data_values,
    ::DDS::SampleInfo & sample_info)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read_next_sample");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->read_next_sample (
        typename ::DDSX11::traits< TOPIC_TYPE>::inout (data_values),
        ::DDSX11::traits< ::DDS::SampleInfo>::inout (sample_info)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::take_next_sample (
    TOPIC_TYPE & data_values,
    ::DDS::SampleInfo & sample_info)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take_next_sample");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->take_next_sample (
        typename ::DDSX11::traits< TOPIC_TYPE>::inout (data_values),
        ::DDSX11::traits< ::DDS::SampleInfo>::inout (sample_info)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::read_instance (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    const ::DDS::InstanceHandle_t& a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read_instance");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;

    ::DDS::ReturnCode_t const retcode_read_instance =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->read_instance (
          native_data_values,
          native_sample_infos,
          ::DDSX11::traits < int32_t>::in (max_samples),
          ::DDSX11::traits < ::DDS::InstanceHandle_t>::in (a_handle),
          ::DDSX11::traits < ::DDS::SampleStateMask>:: in (sample_states),
          ::DDSX11::traits < ::DDS::ViewStateMask>:: in (view_states),
          ::DDSX11::traits < ::DDS::InstanceStateMask>:: in (instance_states)));

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_read_instance, "read_instance");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::take_instance (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    const ::DDS::InstanceHandle_t& a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take_instance");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;

    ::DDS::ReturnCode_t const retcode_take_instance =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->take_instance (
          native_data_values,
          native_sample_infos,
          ::DDSX11::traits < int32_t>::in (max_samples),
          ::DDSX11::traits < ::DDS::InstanceHandle_t>::in (a_handle),
          ::DDSX11::traits < ::DDS::SampleStateMask>:: in (sample_states),
          ::DDSX11::traits < ::DDS::ViewStateMask>:: in (view_states),
          ::DDSX11::traits < ::DDS::InstanceStateMask>:: in (instance_states)));

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_take_instance, "take_instance");
  }


  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::read_instance_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq& sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& a_handle,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read_instance_w_condition");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;
    ::DDS::ReturnCode_t retcode_read_instance_w_condition { ::DDS::RETCODE_OK };

    DDS_Native::DDS::ReadCondition *dds_rc =
      read_condition_trait::native (a_condition);

    if (dds_rc)
      {
        retcode_read_instance_w_condition =
          ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
            this->native_entity ()->read_instance_w_condition (
              native_data_values,
              native_sample_infos,
              ::DDSX11::traits<int32_t>::in (max_samples),
              ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (a_handle),
              dds_rc));
      }
    else
      {
        DDS_Native::DDS::QueryCondition *dds_qc =
          query_condition_trait::native (
            IDL::traits< ::DDS::QueryCondition>::narrow (a_condition));
        if (dds_qc)
          {
            retcode_read_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->read_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (a_handle),
                  dds_qc));
          }
        else
          {
            retcode_read_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->read_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (a_handle),
                  nullptr));
          }
      }

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_read_instance_w_condition, "read_instance_w_condition");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::take_instance_w_condition (
      SEQ_TYPE & data_values,
      ::DDS::SampleInfoSeq& sample_infos,
      int32_t max_samples,
      const ::DDS::InstanceHandle_t& a_handle,
      IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take_instance_w_condition");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;
    ::DDS::ReturnCode_t retcode_take_instance_w_condition { ::DDS::RETCODE_OK };

    DDS_Native::DDS::ReadCondition *dds_rc =
      read_condition_trait::native (a_condition);

    if (dds_rc)
      {
        retcode_take_instance_w_condition =
          ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
            this->native_entity ()->take_instance_w_condition (
              native_data_values,
              native_sample_infos,
              ::DDSX11::traits<int32_t>::in (max_samples),
              ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (a_handle),
              dds_rc));
      }
    else
      {
        DDS_Native::DDS::QueryCondition *dds_qc =
          query_condition_trait::native (
            IDL::traits< ::DDS::QueryCondition>::narrow (a_condition));
        if (dds_qc)
          {
            retcode_take_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->take_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (a_handle),
                  dds_qc));
          }
        else
          {
            retcode_take_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->take_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (a_handle),
                  nullptr));
          }
      }

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_take_instance_w_condition, "take_instance_w_condition");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::read_next_instance (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    const ::DDS::InstanceHandle_t& a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read_next_instance");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;

    ::DDS::ReturnCode_t const retcode_read_instance =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->read_next_instance (
          native_data_values,
          native_sample_infos,
          ::DDSX11::traits < int32_t>::in (max_samples),
          ::DDSX11::traits < ::DDS::InstanceHandle_t>::in (a_handle),
          ::DDSX11::traits < ::DDS::SampleStateMask>:: in (sample_states),
          ::DDSX11::traits < ::DDS::ViewStateMask>:: in (view_states),
          ::DDSX11::traits < ::DDS::InstanceStateMask>:: in (instance_states)));

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_read_instance, "read_next_instance");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::take_next_instance (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    const ::DDS::InstanceHandle_t& a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take_next_instance");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;

    ::DDS::ReturnCode_t const retcode_take_instance =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->take_next_instance (
          native_data_values,
          native_sample_infos,
          ::DDSX11::traits < int32_t>::in (max_samples),
          ::DDSX11::traits < ::DDS::InstanceHandle_t>::in (a_handle),
          ::DDSX11::traits < ::DDS::SampleStateMask>:: in (sample_states),
          ::DDSX11::traits < ::DDS::ViewStateMask>:: in (view_states),
          ::DDSX11::traits < ::DDS::InstanceStateMask>:: in (instance_states)));

    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_take_instance, "take_next_instance");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::read_next_instance_w_condition (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    const ::DDS::InstanceHandle_t& previous_handle,
    IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::read_next_instance_w_condition");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE                native_data_values;
    ::DDS::ReturnCode_t retcode_read_next_instance_w_condition { ::DDS::RETCODE_OK };

    DDS_Native::DDS::ReadCondition *dds_rc =
      read_condition_trait::native (a_condition);

    if (dds_rc)
      {
        retcode_read_next_instance_w_condition =
          ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
            this->native_entity ()->read_next_instance_w_condition (
              native_data_values,
              native_sample_infos,
              ::DDSX11::traits<int32_t>::in (max_samples),
              ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (previous_handle),
              dds_rc));
      }
    else
      {
        DDS_Native::DDS::QueryCondition *dds_qc =
          query_condition_trait::native (
            IDL::traits< ::DDS::QueryCondition>::narrow (a_condition));
        if (dds_qc)
          {
            retcode_read_next_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->read_next_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (previous_handle),
                  dds_qc));
          }
        else
          {
            retcode_read_next_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->read_next_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (previous_handle),
                  nullptr));
          }
      }
    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_read_next_instance_w_condition, "read_next_instance_w_condition");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::take_next_instance_w_condition (
    SEQ_TYPE & data_values,
    ::DDS::SampleInfoSeq & sample_infos,
    int32_t max_samples,
    const ::DDS::InstanceHandle_t& previous_handle,
    IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::take_next_instance_w_condition");

    DDS_Native::DDS::SampleInfoSeq native_sample_infos;
    NATIVE_SEQ_TYPE native_data_values;
    ::DDS::ReturnCode_t retcode_take_next_instance_w_condition { ::DDS::RETCODE_OK };

    DDS_Native::DDS::ReadCondition *dds_rc =
      read_condition_trait::native (a_condition);

    if (dds_rc)
      {
        retcode_take_next_instance_w_condition =
          ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
            this->native_entity ()->take_next_instance_w_condition (
              native_data_values,
              native_sample_infos,
              ::DDSX11::traits<int32_t>::in (max_samples),
              ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (previous_handle),
              dds_rc));
      }
    else
      {
        DDS_Native::DDS::QueryCondition *dds_qc =
          query_condition_trait::native (
            IDL::traits< ::DDS::QueryCondition>::narrow (a_condition));
        if (dds_qc)
          {
            retcode_take_next_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->take_next_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (previous_handle),
                  dds_qc));
          }
        else
          {
            retcode_take_next_instance_w_condition =
              ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                this->native_entity ()->take_next_instance_w_condition (
                  native_data_values,
                  native_sample_infos,
                  ::DDSX11::traits<int32_t>::in (max_samples),
                  ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (previous_handle),
                  nullptr));
          }
      }
    return this->complete_read (
      native_data_values, data_values, native_sample_infos,
      sample_infos, retcode_take_next_instance_w_condition, "take_next_instance_w_condition");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::return_loan (
    SEQ_TYPE & /*data_values*/,
    ::DDS::SampleInfoSeq & /*sample_infos*/)
  {
    // No need to implement this since a return_loan is
    // done every read/take operation in this proxy
    return ::DDS::RETCODE_OK;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_key_value (
    TOPIC_TYPE & key_holder,
    const ::DDS::InstanceHandle_t& handle)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_key_value");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_key_value (
        typename ::DDSX11::traits<TOPIC_TYPE>::inout (key_holder),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::InstanceHandle_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::lookup_instance (
    const TOPIC_TYPE& an_instance)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::lookup_instance");

    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->lookup_instance (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (an_instance)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::enable ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::enable");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->enable ());
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  IDL::traits< ::DDS::StatusCondition>::ref_type
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_statuscondition ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_statuscondition");

    IDL::traits< ::DDS::StatusCondition>::ref_type retval;
    DDS_Native::DDS::StatusCondition_var sc = this->native_entity ()->get_statuscondition ();
    if (sc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_StatusCondition_proxy>(sc);
      }
    return retval;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::StatusMask
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_status_changes ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_status_changes");

    return ::DDSX11::traits< ::DDS::StatusMask>::retn (
      this->native_entity ()->get_status_changes ());
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename RTI_SEQ_TYPE>
  ::DDS::InstanceHandle_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, RTI_SEQ_TYPE>::get_instance_handle ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_instance_handle");

    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->get_instance_handle ());
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  IDL::traits< ::DDS::ReadCondition>::ref_type
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::create_readcondition (
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::create_readcondition");

    IDL::traits< ::DDS::ReadCondition>::ref_type retval;

    DDS_Native::DDS::ReadCondition_var rc =
      this->native_entity ()->create_readcondition (
        ::DDSX11::traits< ::DDS::SampleStateMask>::in (sample_states),
        ::DDSX11::traits< ::DDS::ViewStateMask>::in (view_states),
        ::DDSX11::traits< ::DDS::InstanceStateMask>::in (instance_states));
    if (rc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_ReadCondition_proxy>(rc);
      }
    return retval;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  IDL::traits< ::DDS::QueryCondition>::ref_type
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::create_querycondition (
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states,
    const std::string &query_expression,
    const ::DDS::StringSeq &query_parameters)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::create_querycondition");

    IDL::traits< ::DDS::QueryCondition>::ref_type retval;

    DDS_Native::DDS::QueryCondition_var qc =
      this->native_entity ()->create_querycondition (
        ::DDSX11::traits< ::DDS::SampleStateMask>::in (sample_states),
        ::DDSX11::traits< ::DDS::ViewStateMask>::in (view_states),
        ::DDSX11::traits< ::DDS::InstanceStateMask>::in (instance_states),
        ::DDSX11::traits<std::string>::in (query_expression),
        ::DDSX11::traits< ::DDS::StringSeq, ::DDS_Native::DDS::StringSeq>::in (query_parameters));
    if (qc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_QueryCondition_proxy>(qc);
      }
    return retval;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::delete_readcondition (
    IDL::traits< ::DDS::ReadCondition>::ref_type a_condition)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::delete_readcondition");

    DDS_Native::DDS::ReadCondition *native_rc {};

    IDL::traits< ::DDS::QueryCondition>::ref_type qc =
      IDL::traits< ::DDS::QueryCondition>::narrow (a_condition);

    if (qc)
      {
        IDL::traits< ::DDSX11::DDS_QueryCondition_proxy>::ref_type proxy =
          query_condition_trait::proxy (qc);

        native_rc = dynamic_cast<DDS_Native::DDS::ReadCondition *> (
          proxy->get_native_entity ());

        proxy->clear_native_entity ();
      }
    else
      {
        IDL::traits< ::DDSX11::DDS_ReadCondition_proxy>::ref_type proxy =
          read_condition_trait::proxy (a_condition);

        native_rc = proxy->get_native_entity ();

        proxy->clear_native_entity ();
      }

    if (!native_rc)
    {
      DDSX11_IMPL_LOG_DEBUG ("DataReader_T::delete_readcondition - "
        "Unable to determine the native read condition");
      return ::DDS::RETCODE_BAD_PARAMETER;
    }
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_readcondition (native_rc));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::delete_contained_entities ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::delete_contained_entities");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_contained_entities ());
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::set_qos (
    const ::DDS::DataReaderQos & qos)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::set_qos");

    ::DDSX11::traits< ::DDS::DataReaderQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::set_qos - Error: Unable to retrieve QoS <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << "::set_qos - Setting DataReaderQoS <"
      << IDL::traits< ::DDS::DataReaderQos>::write (::DDSX11::traits< ::DDS::DataReaderQos>::retn(qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_qos (::DDSX11::traits< ::DDS::DataReaderQos>::in (qos_in)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_qos (
    ::DDS::DataReaderQos & qos)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()-> get_qos (
        ::DDSX11::traits< ::DDS::DataReaderQos>::inout (qos)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::set_listener (
    IDL::traits< ::DDS::DataReaderListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::set_listener");

    // Retrieve the previously set listener, the guard will make sure we destroy it when we succeed
    // in setting a new listener
    DataReaderListener_Guard old_guard { this->native_entity ()->get_listener () };
    DataReaderListener_Guard new_guard {};
    if (a_listener)
      {
        new_guard = new DDS_DataReaderListener_proxy (a_listener);
      }

    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->set_listener (new_guard.get (),
          ::DDSX11::traits< ::DDS::StatusMask>::in (mask)));

    if (retcode == ::DDS::RETCODE_OK)
      {
        // Release the guard here and 'give' it to DDS otherwise the listener
        // would be destroyed when goes out of scope.
        new_guard.release ();
      }
    else
      {
        // Setting the new listener failed so we have to assume the old
        // listener is still installed so we can't let the guard destroy it
        old_guard.release ();
      }

    return retcode;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  IDL::traits< ::DDS::DataReaderListener>::ref_type
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_listener ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_listener");

    DDS_Native::DDS::DataReaderListener_var native_listener =
      this->native_entity ()->get_listener ();

    if (!native_listener)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::get_listener - DDS returned a null listener");
        return {};
      }

    native_datareaderlistener_trait::proxy_impl_type * proxy_impl =
       native_datareaderlistener_trait::proxy_impl (native_listener);

    if (!proxy_impl)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::get_listener - listener returned by DDS is not a DDSX11 listener");
        return {};
      }
    return proxy_impl->get_datareaderlistener ();
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  IDL::traits< ::DDS::TopicDescription>::ref_type
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_topicdescription ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_topicdescription");

    IDL::traits< ::DDS::TopicDescription>::ref_type td;
    DDS_Native::DDS::TopicDescription_var native_td =
      this->native_entity ()->get_topicdescription ();

    if (native_td)
      {
        DDS_Native::DDS::Topic_var native_tp =
#if (DDSX11_NDDS==1)
          DDS_Native::DDS::Topic::narrow (native_td);
#else
          DDS_Native::DDS::Topic::_narrow (native_td);
#endif

        if (native_tp)
          {
            td = DDS_ProxyEntityManager::get_topic_proxy (native_tp);
          }
        else
          {
            DDS_Native::DDS::ContentFilteredTopic_var native_cft =
#if (DDSX11_NDDS==1)
              DDS_Native::DDS::ContentFilteredTopic::narrow (native_td);
#else
              DDS_Native::DDS::ContentFilteredTopic::_narrow (native_td);
#endif

            if (native_cft)
              {
                td = TAOX11_CORBA::make_reference<DDS_ContentFilteredTopic_proxy> (native_cft);
              }
          }
      }
    return td;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  IDL::traits< ::DDS::Subscriber>::ref_type
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_subscriber ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_subscriber");

    DDS_Native::DDS::Subscriber_var subscriber =
      this->native_entity ()->get_subscriber ();

    return DDS_ProxyEntityManager::get_subscriber_proxy (subscriber);
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_sample_rejected_status (
    ::DDS::SampleRejectedStatus & status)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_sample_rejected_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_sample_rejected_status (
        ::DDSX11::traits< ::DDS::SampleRejectedStatus>::inout (status)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_liveliness_changed_status (
    ::DDS::LivelinessChangedStatus & status)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_liveliness_changed_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_liveliness_changed_status (
        ::DDSX11::traits< ::DDS::LivelinessChangedStatus>::inout (status)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_requested_deadline_missed_status (
    ::DDS::RequestedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_requested_deadline_missed_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_requested_deadline_missed_status (
        ::DDSX11::traits< ::DDS::RequestedDeadlineMissedStatus>::inout (status)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_requested_incompatible_qos_status (
    ::DDS::RequestedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_requested_incompatible_qos_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_requested_incompatible_qos_status (
        ::DDSX11::traits< ::DDS::RequestedIncompatibleQosStatus>::inout (status)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_subscription_matched_status (
    ::DDS::SubscriptionMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_subscription_matched_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_subscription_matched_status (
        ::DDSX11::traits< ::DDS::SubscriptionMatchedStatus>::inout (status)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_sample_lost_status (
    ::DDS::SampleLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_sample_lost_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_sample_lost_status (
        ::DDSX11::traits< ::DDS::SampleLostStatus>::inout (status)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::wait_for_historical_data (
    const ::DDS::Duration_t & max_wait)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::wait_for_historical_data");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->wait_for_historical_data (
        ::DDSX11::traits< ::DDS::Duration_t>::in (max_wait)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_matched_publications (
    ::DDS::InstanceHandleSeq & publication_handles)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_matched_publications");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_matched_publications (
        ::DDSX11::traits< ::DDS::InstanceHandleSeq, ::DDS_Native::DDS::InstanceHandleSeq>::inout (publication_handles)));
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  ::DDS::ReturnCode_t
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_matched_publication_data (
    ::DDS::PublicationBuiltinTopicData & publication_data,
    const ::DDS::InstanceHandle_t& publication_handle)
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_matched_publication_data");

#if defined DDSX11_HAS_MINIMUM_BIT
    X11_UNUSED_ARG(publication_data);
    X11_UNUSED_ARG(publication_handle);
    return ::DDS::RETCODE_UNSUPPORTED;
#else
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_matched_publication_data (
        ::DDSX11::traits< ::DDS::PublicationBuiltinTopicData>::inout (publication_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (publication_handle)));
#endif
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  NATIVE_TYPED_READER *
  DataReader_T<NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::native_entity ()
  {
    if (!this->native_entity_)
      {
        DDSX11_IMPL_LOG_DEBUG ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::entity Throwing BAD_INV_ORDER.");
        throw TAOX11_CORBA::BAD_INV_ORDER ();
      }
    return this->native_entity_;
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  DDS_Native::DDS::DataReader *
  DataReader_T<NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::get_native_entity ()
  {
    return this->native_entity_;
  }
}
