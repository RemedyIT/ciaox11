// -*- C++ -*-
/**
 * @file    dds_condition.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "dds/dds_common.h"
#include "dds/dds_condition.h"

#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  DDS_Condition_proxy::DDS_Condition_proxy (DDS_Native::DDS::Condition *condition)
    : NativeEntityBase_T<DDS_Native::DDS::Condition> (condition)
  {
    DDSX11_LOG_TRACE ("DDS_Condition_proxy::DDS_Condition_proxy");
  }

  bool
  DDS_Condition_proxy::get_trigger_value ()
  {
    DDSX11_LOG_TRACE ("DDS_Condition_proxy::get_trigger_value");

    return ::DDSX11::traits< bool >::retn (
      this->native_entity ()->get_trigger_value ());
  }
}
