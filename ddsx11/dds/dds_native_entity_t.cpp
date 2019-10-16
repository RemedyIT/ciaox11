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
#include <stdexcept>

// DDS vendor specific implementation part
#include "dds/dds_native_entity_base_t.cpp"

namespace DDSX11
{
  template<typename DDS_NATIVE_TYPE>
  NativeEntityBase_T<DDS_NATIVE_TYPE>::NativeEntityBase_T (
    DDS_NATIVE_TYPE *entity)
    : native_entity_ (entity)
  {
  }

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
        DDSX11_IMPL_LOG_PANIC ("NativeEntityBase_T<DDS_NATIVE_TYPE>::entity "
          << "Throwing BAD_INV_ORDER.");
        throw std::logic_error ("Called native_entity");
      }
    return this->native_entity_;
  }
}
