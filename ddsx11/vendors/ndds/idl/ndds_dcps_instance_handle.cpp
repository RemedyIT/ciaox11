/**
 * @file    ndds_dcps_instance_handle.cpp
 * @author  Marcel Smit
 *
 * @brief   Place holder for specific IDL definitions
 *          This file is used as include in all generated NDDS
 *          specific stub and skeleton code.
 *          HANDLE_NIL is not defined in IDL for NDDS.
 *          HANDLE_NIL is defined here so that the user is able
 *          to use it.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "ndds_dcps_instance_handle.h"

bool
operator== (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2)
{
  if (instancehandle1.isValid ())
    {
      if (instancehandle2.isValid ())
        {
          // 1 and 2 are valid so compare the length and the value
          return ((instancehandle1.length () == instancehandle2.length ()) &&
                  (instancehandle1.value () == instancehandle2.value ()));
        }
    }
  else
    {
      if (!instancehandle2.isValid ())
        {
          // 1 is invalid and 2 is invalid, so return true
          return true;
        }
    }

  return false;
}

bool
operator!= (const ::DDS::InstanceHandle_t & instancehandle1, const ::DDS::InstanceHandle_t & instancehandle2)
{
  return !operator== (instancehandle1, instancehandle2);
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
