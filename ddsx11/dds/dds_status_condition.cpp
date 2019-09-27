// -*- C++ -*-
/**
 * @file    dds_status_condition.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "dds/dds_common.h"
#include "dds/dds_status_condition.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_proxy_entity_manager.h"

#include "logger/ddsx11_log.h"

namespace DDSX11
{
  DDS_StatusCondition_proxy::DDS_StatusCondition_proxy (
    DDS_Native::DDS::StatusCondition * sc)
    : NativeEntityBase_T<DDS_Native::DDS::StatusCondition > (sc)
  {
  }

  bool
  DDS_StatusCondition_proxy::get_trigger_value ()
  {
    return ::DDSX11::traits< bool >::retn (
      this->native_entity ()->get_trigger_value ());
  }

  ::DDS::StatusMask
  DDS_StatusCondition_proxy::get_enabled_statuses ()
  {
    return ::DDSX11::traits< ::DDS::StatusMask >::retn (
      this->native_entity ()->get_enabled_statuses ());
  }

  ::DDS::ReturnCode_t
  DDS_StatusCondition_proxy::set_enabled_statuses (
    ::DDS::StatusMask mask)
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t >::retn (
      this->native_entity ()->set_enabled_statuses (
        ::DDSX11::traits< ::DDS::StatusMask >::in (mask)));
  }

  IDL::traits< ::DDS::Entity >::ref_type
  DDS_StatusCondition_proxy::get_entity ()
  {
    return DDS_ProxyEntityManager::get_entity_proxy (
      this->native_entity ()->get_entity ());
  }
}

