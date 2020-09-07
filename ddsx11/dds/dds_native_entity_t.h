// -*- C++ -*-
/**
 * @file    dds_native_entity_t.h
 * @author  Marcel Smit
 *
 * @brief   Placeholder for the native DDS pointers. All DDS entity proxy classes
 *          are derived from this template class.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_NATIVE_ENTITY_T_H_
#define DDSX11_NATIVE_ENTITY_T_H_

namespace DDSX11
{
  /**
    * @class NativeEntityBase_T
    * @brief Manages the entity pointer of the native DDS vendor
    */
  template<typename DDS_NATIVE_TYPE>
  class NativeEntityBase_T
  {
  public:
    NativeEntityBase_T (DDS_NATIVE_TYPE *);
    virtual ~NativeEntityBase_T ();

    /**
      * @name   get_native_entity
      * @return Returns the pointer to the native DDS entity.
      */
    DDS_NATIVE_TYPE * get_native_entity ();

    /**
      * @name         clear_native_entity
      * @brief        Cleares the native DDS entity pointer.
      * @param entity The DDS entity pointer
      */
    void clear_native_entity ();

  protected:
    /**
      * @name   native_entity
      * @brief  All derived proxy classes should use this method when
      *         interacting with DDS.
      * @return The native DDS entity pointer
      * @throw  CORBA::BAD_INV_ORDER when the internal DDS entity pointer was not set yet
      */
    DDS_NATIVE_TYPE *native_entity ();

  private:
    DDS_NATIVE_TYPE *native_entity_ {};

  protected:
    NativeEntityBase_T() = delete;
    NativeEntityBase_T(const NativeEntityBase_T&) = delete;
    NativeEntityBase_T(NativeEntityBase_T&&) = delete;
    NativeEntityBase_T& operator=(const NativeEntityBase_T&) = delete;
    NativeEntityBase_T& operator=(NativeEntityBase_T&&) = delete;
  };
}

#include "dds/dds_native_entity_t.cpp"

#endif /* DDSX11_NATIVE_ENTITY_T_H_ */
