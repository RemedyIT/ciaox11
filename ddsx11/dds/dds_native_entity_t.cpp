// -*- C++ -*-
/**
 * @file    dds_native_entity_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Placeholder for the native DDS entities.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "logger/ddsx11_log.h"
#include "tao/x11/system_exception.h"

// DDS vendor specific implementation part
#include "dds/dds_native_entity_base_t.cpp"

namespace DDSX11
{
  template<typename DDS_NATIVE_TYPE>
  DDS_NATIVE_TYPE *
  NativeEntityBase_T<DDS_NATIVE_TYPE>::get_native_entity ()
  {
    return this->native_entity_;
  }

  template<typename DDS_NATIVE_TYPE>
  DDS_NATIVE_TYPE *
  NativeEntityBase_T<DDS_NATIVE_TYPE>::native_entity ()
  {
    if (!this->native_entity_)
      {
        DDSX11_IMPL_LOG_DEBUG ("NativeEntityBase_T<DDS_NATIVE_TYPE>::native_entity "
          << "Throwing CORBA::BAD_INV_ORDER because we have a nullptr to the native entity");
        throw TAOX11_CORBA::BAD_INV_ORDER ();
      }
    return this->native_entity_;
  }
}
