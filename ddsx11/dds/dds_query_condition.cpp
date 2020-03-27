// -*- C++ -*-
/**
 * @file    dds_query_condition.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_query_condition.h"

#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_proxy_entity_manager.h"

#include "logger/ddsx11_log.h"

namespace DDSX11
{
  DDS_QueryCondition_proxy::DDS_QueryCondition_proxy (
    DDS_Native::DDS::QueryCondition * qc)
    : NativeEntityBase_T<DDS_Native::DDS::QueryCondition>(qc)
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::DDS_QueryCondition_proxy");
  }

  bool
  DDS_QueryCondition_proxy::get_trigger_value ()
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::get_trigger_value");

    return ::DDSX11::traits<bool>::retn (
      this->native_entity ()->get_trigger_value ());
  }

  ::DDS::SampleStateMask
  DDS_QueryCondition_proxy::get_sample_state_mask ()
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::get_sample_state_mask");

    return ::DDSX11::traits< ::DDS::SampleStateMask>::retn (
      this->native_entity ()->get_sample_state_mask ());
  }

  ::DDS::ViewStateMask
  DDS_QueryCondition_proxy::get_view_state_mask ()
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::get_view_state_mask");

    return ::DDSX11::traits< ::DDS::ViewStateMask>::retn (
      this->native_entity ()->get_view_state_mask ());
  }

  ::DDS::InstanceStateMask
  DDS_QueryCondition_proxy::get_instance_state_mask ()
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::get_instance_state_mask");

    return ::DDSX11::traits< ::DDS::InstanceStateMask>::retn (
      this->native_entity ()->get_instance_state_mask ());
  }

  IDL::traits< ::DDS::DataReader>::ref_type
  DDS_QueryCondition_proxy::get_datareader ()
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::get_datareader");

    return DDS_ProxyEntityManager::get_datareader_proxy (
      this->native_entity ()->get_datareader ());
  }

  std::string
  DDS_QueryCondition_proxy::get_query_expression ()
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::get_query_expression");

    return ::DDSX11::traits<std::string>::retn (
      this->native_entity ()->get_query_expression ());
  }

  ::DDS::ReturnCode_t
  DDS_QueryCondition_proxy::get_query_parameters (
    ::DDS::StringSeq & query_parameters)
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::get_query_parameters");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_query_parameters (
          ::DDSX11::traits< ::DDS::StringSeq, ::DDS_Native::DDS::StringSeq>::inout (query_parameters)));
  }

  ::DDS::ReturnCode_t
  DDS_QueryCondition_proxy::set_query_parameters (
    const ::DDS::StringSeq & query_parameters)
  {
    DDSX11_LOG_TRACE ("DDS_QueryCondition_proxy::set_query_parameters");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_query_parameters (
          ::DDSX11::traits< ::DDS::StringSeq, ::DDS_Native::DDS::StringSeq>::in (query_parameters)));
  }
}
