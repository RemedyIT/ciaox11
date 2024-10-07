// -*- C++ -*-
/**
 * @file    dds_common.h
 * @author  Marcel Smit
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
#include "dds/ndds_typedefs.h"

#if (RTI_DDS_VERSION_MAJOR < 7) || ((RTI_DDS_VERSION_MAJOR == 7) && (RTI_DDS_VERSION_MINOR < 3))
# error Only RTI Connext DDS 7.3 or newer are supported
#endif

#endif /* DDSX11_IMPL_COMMON_H_ */
