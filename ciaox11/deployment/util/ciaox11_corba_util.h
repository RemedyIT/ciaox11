/**
 * @file   ciaox11_corba_util.h
 * @author Martin Corino
 *
 * @brief CIAOX11 CORBA deployment utility methods
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef CIAOX11_CORBA_UTIL_H
#define CIAOX11_CORBA_UTIL_H

#include "ciaox11_corba_util_export.h"
#include "ccm/ccm_configC.h"

namespace CIAOX11
{
  namespace Corba
  {
    namespace Utility
    {
      CIAOX11_CORBA_UTIL_Export IDL::traits<CORBA::Object>::ref_type
      get_provider_reference (const Components::ConfigValues&);
    }
  }
}

#endif /* CIAOX11_CORBA_UTIL_H */
