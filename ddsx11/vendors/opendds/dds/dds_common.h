// -*- C++ -*-
/**
 * @file    dds_common.h
 * @author  Johnny Willemsen
 *
 * @brief   Manages includes per vendor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_COMMON_H_
#define DDSX11_IMPL_COMMON_H_

// At the moment we have a DDS vendor for which we convert from the DDSX11 to the native QoS
// representation we need to retrieve the native QoS before doing the conversion, else
// vendor specific settings that are not supported by DDSX11 do possible get an incorrect
// default value
#define DDSX11_INITIALIZE_QOS_DEFAULTS
#include "dds/DdsDcpsC.h"
#include "dds/opendds_typedefs.h"

#endif /* DDSX11_IMPL_COMMON_H_ */
