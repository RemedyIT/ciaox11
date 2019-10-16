// -*- C++ -*-
/**
 * @file    dds_native_entity_base_t.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Vendor specific part of wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

namespace DDSX11
{
  template<typename DDS_NATIVE_TYPE>
  NativeEntityBase_T<DDS_NATIVE_TYPE>::~NativeEntityBase_T ()
  {
  }

  template<typename DDS_NATIVE_TYPE>
  void
  NativeEntityBase_T<DDS_NATIVE_TYPE>::clear_native_entity ()
  {
    this->native_entity_ = nullptr;
  }
}
