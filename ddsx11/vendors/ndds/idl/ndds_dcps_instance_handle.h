/**
 * @file    ndds_dcps_instance_handle.h
 * @author  Marcel Smit
 *
 * @brief   Place holder for specific IDL definitions
 *
 * This file is used as include in all generated NDDS specific stub and
 * skeleton code.
 * HANDLE_NIL is not defined in IDL for NDDS. HANDLE_NIL is defined here so
 * that the user is able to use it.
 * The same applies to the == and != operators. These operators needs to be
 * accessible via the (lem)stub code since the user component don't include
 * DDS proxy core files directly.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS_NDDS_NDDS_DCPS_INSTANCE_HANDLE_H_
#define DDS_NDDS_NDDS_DCPS_INSTANCE_HANDLE_H_

#include "ddsx11_ndds_stub_export.h"
#include "ndds_dcps_instance_handleC.h"

namespace DDS
{
  ::DDS::octet_value const OCTET_NIL = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  ::DDS::InstanceHandle_t const HANDLE_NIL (OCTET_NIL, 16, 0);
}

DDSX11_NDDS_STUB_Export bool operator== (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2);
DDSX11_NDDS_STUB_Export bool operator!= (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2);
DDSX11_NDDS_STUB_Export bool operator< (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2);

#endif /* DDS_NDDS_NDDS_DCPS_INSTANCE_HANDLE_H_ */
