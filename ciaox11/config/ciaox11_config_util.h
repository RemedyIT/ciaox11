/**
 * @file   ciaox11_config_util.h
 * @author Martin Corino
 *
 * @brief Common CIAOX11 ConfigValue utility methods
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef CIAOX11_CONFIG_UTIL_H
#define CIAOX11_CONFIG_UTIL_H

#include "ciaox11_config_export.h"
#include "ccm/ccm_configC.h"

namespace CIAOX11
{
  namespace Config
  {
    namespace Utility
    {
      CIAOX11_CONFIG_Export bool find_config_value (const Components::ConfigValues&,
                                                    const Components::FeatureName&,
                                                    CORBA::Any&);
      CIAOX11_CONFIG_Export bool has_config_value (const Components::ConfigValues&,
                                                   const Components::FeatureName&);
    }
  }
}

#endif /* CIAOX11_CONFIG_UTIL_H */
