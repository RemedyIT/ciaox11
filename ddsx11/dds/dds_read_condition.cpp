// -*- C++ -*-
/**
 * @file    dds_read_condition.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_read_condition.h"

#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_proxy_entity_manager.h"

#include "logger/ddsx11_log.h"

namespace DDSX11
{
  DDS_ReadCondition_proxy::DDS_ReadCondition_proxy (
    DDS_Native::DDS::ReadCondition * rc)
    : NativeEntityBase_T<DDS_Native::DDS::ReadCondition >(rc)
  {
    DDSX11_LOG_TRACE ("DDS_ReadCondition_proxy::DDS_ReadCondition_proxy");
  }

  bool
  DDS_ReadCondition_proxy::get_trigger_value ()
  {
    DDSX11_LOG_TRACE ("DDS_ReadCondition_proxy::get_trigger_value");

    return ::DDSX11::traits< bool >::retn (
      this->native_entity ()->get_trigger_value ());
  }

  ::DDS::SampleStateMask
  DDS_ReadCondition_proxy::get_sample_state_mask ()
  {
    DDSX11_LOG_TRACE ("DDS_ReadCondition_proxy::get_sample_state_mask");

    return ::DDSX11::traits< ::DDS::SampleStateMask>::retn (
      this->native_entity ()->get_sample_state_mask ());
  }

  ::DDS::ViewStateMask
  DDS_ReadCondition_proxy::get_view_state_mask ()
  {
    DDSX11_LOG_TRACE ("DDS_ReadCondition_proxy::get_view_state_mask");

    return ::DDSX11::traits< ::DDS::ViewStateMask>::retn (
      this->native_entity ()->get_view_state_mask ());
  }

  ::DDS::InstanceStateMask
  DDS_ReadCondition_proxy::get_instance_state_mask ()
  {
    DDSX11_LOG_TRACE ("DDS_ReadCondition_proxy::get_instance_state_mask");

    return ::DDSX11::traits< ::DDS::InstanceStateMask>::retn (
      this->native_entity ()->get_instance_state_mask ());
  }

  IDL::traits< ::DDS::DataReader>::ref_type
  DDS_ReadCondition_proxy::get_datareader ()
  {
    DDSX11_LOG_TRACE ("DDS_ReadCondition_proxy::get_datareader");

    return DDS_ProxyEntityManager::get_datareader_proxy (
      this->native_entity ()->get_datareader ());
  }
}

