// -*- C++ -*-
/**
 * @file    ndds_utils.h
 * @author  Marcel Smit
 *
 * @brief   Utility class for the NDDS specific profile strings
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_UTILS_H_
#define DDSX11_IMPL_NDDS_UTILS_H_

#include <string>

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    bool split_qos_profile (
      const std::string &qos_profile,
      std::string& library_name,
      std::string& profile_name);
  }
}

#endif /* DDSX11_IMPL_NDDS_UTILS_H_ */
