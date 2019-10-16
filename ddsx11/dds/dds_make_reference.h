// -*- C++ -*-
/**
 * @file    dds_make_reference.h
 * @author  Johnny Willemsen
 *
 * @brief   DDS::make_reference factory method for creating DDS listeners
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_MAKE_REFERENCE_H_
#define DDSX11_MAKE_REFERENCE_H_

namespace DDS
{
  /// DDS::make_reference template which just forwards to the CORBA::make_reference
  template <typename T, typename = typename
    std::enable_if<std::is_base_of<::DDS::Listener, T>::value>::type, typename ...Args>
  TAOX11_CORBA::object_reference<T> make_reference(Args&& ...args)
  {
    return TAOX11_CORBA::make_reference<T>(std::forward<Args>(args)...);
  }
}

#endif /* DDSX11_MAKE_REFERENCE_H_ */
