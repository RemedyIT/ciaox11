// -*- C++ -*-
/**
 * @file    ndds_utils.cpp
 * @author  Marcel Smit
 *
 * @brief   Utility class for the NDDS specific profile strings
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/ndds_utils.h"
#include "logger/ddsx11_log.h"

#include <string.h>

namespace DDSX11
{
  namespace NDDS_PROXY
  {

    bool split_qos_profile (
      const std::string &qos_profile,
      std::string& library_name,
      std::string& profile_name)
    {
      std::size_t const pos = qos_profile.find ("#");
      if (pos == std::string::npos)
      {
        DDSX11_IMPL_LOG_ERROR ("split_qos_profile <" << qos_profile
          << "> - Error: malformed qos_profile. Expected format: "
          << "<library_name>#<profile_name>.");
        return false;
      }
      library_name = qos_profile.substr (0, pos);
      profile_name = qos_profile.substr (pos+1, qos_profile.length ());
      return true;
    }
  }
}
