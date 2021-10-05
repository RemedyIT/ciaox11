/**
 * @file   ciaox11_config_util.h
 * @author Martin Corino
 *
 * @brief Common CIAOX11 ConfigValue utility methods
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
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
      /// Check if there is a config value with name @a name in the @a cfgval
      /// sequence
      CIAOX11_CONFIG_Export bool has_config_value (const Components::ConfigValues& cfgval,
                                                   const Components::FeatureName& name);
      /// Find the config value with name @a name in the @a cfgval sequence.
      /// @retval false Config value with name @a name doesn't exist
      /// @retval true Config value with name @a name exists, the value it passed back
      /// using the @a value argument
      CIAOX11_CONFIG_Export bool find_config_value (const Components::ConfigValues& cfgval,
                                                    const Components::FeatureName& name,
                                                    CORBA::Any& value);
    }
  }
}

#endif /* CIAOX11_CONFIG_UTIL_H */
