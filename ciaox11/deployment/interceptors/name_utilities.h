/**
 * @file name_utilities.h
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief A set of utility methods to manages references.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef CIAOX11_NAME_UTILITIES_H
#define CIAOX11_NAME_UTILITIES_H

#include "orbsvcs/naming_server/CosNamingC.h"

namespace CIAOX11
{
  namespace Name_Utilities
  {
    /// Write IOR to named file.  Will overwrite file if present.
    bool write_ior (const std::string& file, const std::string& ior);

    /// Binds object to provided name, which may be formatted with / to indicate
    /// naming contexts, e.g. A/B/C.
    bool bind_object (const std::string& name,
                      IDL::traits<CORBA::Object>::ref_type obj,
                      IDL::traits<CosNaming::NamingContext>::ref_type);

    /// Will unbind the provided name.
    bool unbind_object (const std::string& name,
                        IDL::traits<CosNaming::NamingContext>::ref_type);

    void bind_context (CosNaming::Name &nm,
                       IDL::traits<CosNaming::NamingContext>::ref_type);

    void build_name (const std::string& nm,
                     CosNaming::Name &);
  }
}

#endif /* CIAOX11_NAME_UTILITIES_H */
