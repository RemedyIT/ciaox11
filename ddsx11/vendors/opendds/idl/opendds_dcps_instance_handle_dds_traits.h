/**
 * @file    opendds_dcps_instance_handle_dds_traits.h
 * @author  Johnny Willemsen
 *
 * @brief   Conversion traits for DDS::InstanceHandle_t
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#if !defined (OPENDDS_DCPS_INSTANCE_HANDLE_DDS_TRAITS_H_)
#define OPENDDS_DCPS_INSTANCE_HANDLE_DDS_TRAITS_H_

#include "dds/DdsDcpsC.h"
#include "idl/opendds_dcps_instance_handleC.h"
#include "dds/base_traits.h"

namespace DDSX11
{
  /**
   * Special conversions
   *
   */
  //@{
  /// DDS::InstanceHandle_t TO DDS
  template<>
  inline ::DDS_Native::DDS::InstanceHandle_t&
  to_dds< ::DDS_Native::DDS::InstanceHandle_t, ::DDS::InstanceHandle_t> (
    ::DDS_Native::DDS::InstanceHandle_t &to, const ::DDS::InstanceHandle_t &from)
  {
    ::DDSX11::to_dds(to, from.value ());
    return to;
  }

  // DDS::InstanceHandle_t FROM DDS
  template<>
  inline ::DDS::InstanceHandle_t&
  from_dds< ::DDS_Native::DDS::InstanceHandle_t, ::DDS::InstanceHandle_t> (
    ::DDS::InstanceHandle_t &to, const ::DDS_Native::DDS::InstanceHandle_t &from)
  {
    ::DDSX11::from_dds(to.value (), from);
    return to;
  }

  template <>
  struct traits< ::DDS::InstanceHandle_t>
    : public common_traits< ::DDS::InstanceHandle_t, ::DDS_Native::DDS::InstanceHandle_t>
    , public convert_in< ::DDS::InstanceHandle_t, ::DDS_Native::DDS::InstanceHandle_t>
    , public convert_out_by_ref< ::DDS::InstanceHandle_t, ::DDS_Native::DDS::InstanceHandle_t>
    , public convert_retn< ::DDS::InstanceHandle_t, ::DDS_Native::DDS::InstanceHandle_t>
  {
  };
  //@}
}

#endif /* OPENDDS_DCPS_INSTANCE_HANDLE_DDS_TRAITS_H_*/
