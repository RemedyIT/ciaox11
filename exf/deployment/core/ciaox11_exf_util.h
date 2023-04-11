/**
 * @file   ciaox11_exf_util.h
 * @author Martin Corino
 *
 * @brief Utility methods for the Axcioma execution framework.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_UTIL_H
#define CIAOX11_EXF_UTIL_H

#include "exf/deployment/core/ciaox11_schedule.h"

namespace CIAOX11
{
  namespace ExF
  {
    namespace Util
    {
      CIAOX11_EXF_CORE_Export
      bool get_exf_defaults (
          const Components::ConfigValues& config,
          ExF::Settings& settings);

      CIAOX11_EXF_CORE_Export
      void get_exf_settings (
          const Components::ConfigValues& config,
          const std::string& event,
          ExF::Settings& settings);
    }
  }
};

#endif
