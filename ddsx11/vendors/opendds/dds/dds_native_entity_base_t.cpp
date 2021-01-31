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
  NativeEntityBase_T<DDS_NATIVE_TYPE>::NativeEntityBase_T (
    DDS_NATIVE_TYPE *entity)
    : native_entity_ (entity)
  {
    if (this->native_entity_)
    {
      this->native_entity_->_add_ref();
    }
  }

  template<typename DDS_NATIVE_TYPE>
  NativeEntityBase_T<DDS_NATIVE_TYPE>::~NativeEntityBase_T ()
  {
    if (this->native_entity_)
    {
      this->native_entity_->_remove_ref();
    }
  }

  template<typename DDS_NATIVE_TYPE>
  void
  NativeEntityBase_T<DDS_NATIVE_TYPE>::clear_native_entity ()
  {
    if (native_entity_)
    {
      this->native_entity_->_remove_ref();
      this->native_entity_ = nullptr;
    }
  }
}
