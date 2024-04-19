/**
 * @file    psdd4ccm_config_util.h
 * @author  Martin Corino
 *
 * @brief   PSDD4CCM service configuration utilities.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#if !defined(PSDD4CCM_CONFIG_UTIL_H_)
#define PSDD4CCM_CONFIG_UTIL_H_

#include "ccm/ccm_configC.h"
#include <map>

namespace PSDD
{
  namespace Util
  {
    typedef std::map<std::string, CORBA::Any> property_map_t;

    inline void build_property_map (const ::Components::ConfigValues &values, property_map_t& map)
    {
      for (const ::Components::ConfigValue& v : values)
        map.insert (std::pair{v.name (), v.value ()});
    }

  }
}

#endif /* PSDD4CCM_CONFIG_UTIL_H_ */
