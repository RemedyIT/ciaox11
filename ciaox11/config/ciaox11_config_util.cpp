/**
 * @file   ciaox11_config_util.cpp
 * @author Martin Corino
 *
 * @brief Common CIAOX11 ConfigValue utility methods
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "ciaox11_config_util.h"

namespace CIAOX11
{
  namespace Config
  {
    namespace Utility
    {
      static bool _find_config_value(const Components::ConfigValues& cfgval,
                                     const Components::FeatureName& name,
                                     const Components::ConfigValue* &value)
      {
        for (const Components::ConfigValue& cv : cfgval)
        {
          if (cv.name () == name)
          {
            value = &cv;
            return true;
          }
        }
        return false;
      }

      bool find_config_value (const Components::ConfigValues& cfgval,
                              const Components::FeatureName& name,
                              CORBA::Any& value)
      {
        const Components::ConfigValue* cv {};
        if (_find_config_value (cfgval, name, cv))
        {
          value = cv->value ();
          return true;
        }
        return false;
      }

      bool has_config_value (const Components::ConfigValues& cfgval,
                             const Components::FeatureName& name)
      {
        const Components::ConfigValue* cv {};
        return _find_config_value (cfgval, name, cv);
      }
    }
  }
}
