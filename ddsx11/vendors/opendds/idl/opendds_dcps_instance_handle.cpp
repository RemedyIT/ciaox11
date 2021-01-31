/**
 * @file    opendds_dcps_instance_handle.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Place holder for specific IDL definitions
 *          This file is used as include in all generated OpenDDS
 *          specific stub and skeleton code.
 *          HANDLE_NIL is not defined in IDL for OpenDDS.
 *          HANDLE_NIL is defined here so that the user is able
 *          to use it.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "opendds_dcps_instance_handle.h"

bool
operator== (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2)
{
  return (instancehandle1.value () == instancehandle2.value ());
}

bool
operator!= (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2)
{
  return (instancehandle1.value () != instancehandle2.value ());
}

bool
operator< (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2)
{
  // Comparing two values of type
  // typedef std::array< uint8_t, 16>
  // Array comparison on cppreference.com:
  // 1. Checks if the contents of lhs and rhs are equal, that is, whether each element in lhs compares
  //    equal with the element in rhs at the same position.
  // 2. Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function
  //    equivalent to std::lexicographical_compare.

  return instancehandle1.value () < instancehandle2.value ();
}
