// -*- C++ -*-
/**
 * @file    dds_proxy_traits_t.h
 * @author  Marcel Smit
 *
 * @brief   Placeholder for proxy traits.
 *
 * Supplies 'conversion' traits for the conversion of a DDS entity ref_type
 * to a native entity pointer and conversions from a DDS entity ref_type to
 * its implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_DDSX11_IMPL_PROXY_TRAITS_T_H_
#define DDSX11_DDSX11_IMPL_PROXY_TRAITS_T_H_

#include "idl/dds_dcpsC.h"

namespace DDSX11
{
  /**
    * @class traits
    * @brief Provides 'conversion' traits for DDS entities.
    */
  template<typename DDS_TYPE, typename DDSX11_IMPL_TYPE, typename NATIVE_TYPE>
  class entity_traits
  {
  public:
    /**
      * @brief Narrows a DDS entity to its (proxy) implementation.
      * @param from The DDS entity ref_type
      * @return A ref_type to the proxy implementation.
      */
    static inline typename IDL::traits<DDSX11_IMPL_TYPE>::ref_type
    proxy (typename IDL::traits<DDS_TYPE>::ref_type const &from)
    {
      return IDL::traits<DDSX11_IMPL_TYPE>::narrow (from);
    }

    /**
      * @brief Returns the pointer to the native DDS entity
      * @param from The DDS entity ref_type
      * @return The pointer to the native DDS entity
      */
    static inline NATIVE_TYPE*
    native (typename IDL::traits<DDS_TYPE>::ref_type const &from)
    {
      // Be aware that 'proxy' can return a nullptr
      typename IDL::traits<DDSX11_IMPL_TYPE>::ref_type pr = proxy (from);
      return pr ? pr->get_native_entity () : nullptr;
    }
  };

  /**
   * Helper template to cast a DDS listener pointer to our implementation
   * type
   */
  template<typename DDS_TYPE, typename DDSX11_IMPL_TYPE, typename NATIVE_TYPE>
  class native_entity_traits
  {
  public:
    typedef DDSX11_IMPL_TYPE proxy_impl_type;
    /**
      * @brief Narrows a native DDS entity to its proxy implementation.
      * @param from The native DDS pointer
      * @return A pointer to the proxy implementation.
      */
    static inline DDSX11_IMPL_TYPE*
    proxy_impl (NATIVE_TYPE* from)
    {
      return dynamic_cast <DDSX11_IMPL_TYPE*> (from);
    }
  };
}

#endif /* DDSX11_DDSX11_IMPL_PROXY_TRAITS_T_H_ */
