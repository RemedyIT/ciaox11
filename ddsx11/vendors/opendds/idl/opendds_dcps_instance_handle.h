/**
 * @file    opendds_dcps_instance_handle.h
 * @author  Johnny Willemsen
 *
 * @brief   Place holder for specific IDL definitions
 *
 * This file is used as include in all generated OpenDDS specific stub and
 * skeleton code.
 * HANDLE_NIL is not defined in IDL for OpenDDS. HANDLE_NIL is defined here so
 * that the user is able to use it.
 * The same applies to the == and != operators. These operators needs to be
 * accessible via the (lem)stub code since the user component don't include
 * DDS proxy core files directly.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_OPENDDS_DCPS_INSTANCE_HANDLE_H_
#define DDSX11_OPENDDS_DCPS_INSTANCE_HANDLE_H_

#include "ddsx11_opendds_stub_export.h"
#include "opendds_dcps_instance_handleC.h"

namespace DDS
{
  ::DDS::InstanceHandle_t const HANDLE_NIL {{0}};
}

DDSX11_OPENDDS_STUB_Export bool operator== (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2);
DDSX11_OPENDDS_STUB_Export bool operator!= (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2);
DDSX11_OPENDDS_STUB_Export bool operator< (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2);

#endif /* DDSX11_OPENDDS_DCPS_INSTANCE_HANDLE_H_ */
