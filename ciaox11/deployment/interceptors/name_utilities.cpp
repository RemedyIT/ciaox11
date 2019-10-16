/**
 * @file name_utilities.cpp
 * @author Johnny Willemsen, Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include <fstream>
#include "name_utilities.h"
#include "ciaox11/logger/log.h"

namespace CIAOX11
{
  namespace Name_Utilities {
    bool
    write_ior (const std::string& file, const std::string& ior)
    {
      std::ofstream fos(file);
      if (fos)
        {
          fos << ior;
          fos.close ();
          return true;
        }
      return false;
    }

    bool
    bind_object (const std::string& name,
                 IDL::traits<CORBA::Object>::ref_type obj,
                 IDL::traits<CosNaming::NamingContext>::ref_type ctx)
    {
      if (!ctx)
        {
          CIAOX11_LOG_ERROR ("Name_Utilities::bind_object - Provided name, component <" << name << "> will not be registered");
          return false;
        }

      try
        {
          CosNaming::Name cos_name;

          Name_Utilities::build_name (name, cos_name);

          if (name.size () == 0)
            {
              CIAOX11_LOG_ERROR ("Name_Utilities::bind_object - build_name resulted in an invalid name for component <"
                                  << IDL::traits<CosNaming::Name>::write (cos_name) << ">");
              return false;
            }

          Name_Utilities::bind_context (cos_name, ctx);

          try
            {
              ctx->bind (cos_name, obj);
            }
          catch (const CosNaming::NamingContext::AlreadyBound &)
            {
              CIAOX11_LOG_ERROR ("Name_Utilities::bind_object - component <" << name << "> already bound, rebinding");
              ctx->rebind (cos_name, obj);
            }
        }
      catch (const CORBA::Exception &ex)
        {
          CIAOX11_LOG_ERROR ("Name_Utilities::bind_object - Caught exception while attempting to bind component <"
                              << name << "> : <" << ex << ">");
          return false;
        }

      return true;
    }

    void
    bind_context (CosNaming::Name &name,
                  IDL::traits<CosNaming::NamingContext>::ref_type ctx)
    {
      if (!ctx)
        {
          CIAOX11_LOG_ERROR ("Name_Utilities::bind_context - Provided naming context is nil, name <"
                             << IDL::traits<CosNaming::Name>::write (name) << "> will not be bound");
          return;
        }

      CosNaming::Name newname;


      for (CosNaming::Name::size_type i = 0;
           i < (name.size () - 1); ++i)
        {
          newname.push_back (name[i]);

          try
            {
              ctx->bind_new_context (newname);
              CIAOX11_LOG_DEBUG ("Name_Utilities::bind_context - Bound context <"
                                 << IDL::traits<CosNaming::Name>::write (newname) << ">");
            }
          catch (const CosNaming::NamingContext::AlreadyBound &)
            {
              CIAOX11_LOG_DEBUG ("Name_Utilities::bind_context - Context <"
                                 << IDL::traits<CosNaming::Name>::write (newname) << "> already bound");
            }
        }
    }

    bool
    unbind_object (const std::string& name,
                   IDL::traits<CosNaming::NamingContext>::ref_type ctx)
    {
      if (!ctx)
        {
          CIAOX11_LOG_ERROR ("Name_Utilities::unbind_object - Provided naming context is nil, name <" << name << "> will not be unbound");
          return false;
        }

      CosNaming::Name cos_name;
      Name_Utilities::build_name (name, cos_name);

      try
        {
          ctx->unbind (cos_name);
        }
      catch (const CORBA::Exception &e)
        {
          CIAOX11_LOG_ERROR ("Name_Utilities::unbind_object - Caught exception while unbinding <" << name << ">:<" << e << ">");
          return false;
        }
      return true;
    }

    void
    build_name (const std::string& name, CosNaming::Name &cos_name)
    {
      // @todo, C++11 coding
      const char* str = name.c_str ();
      do
        {
          const char *begin = name.c_str ();
          while(*str != '/' && *str)
            {
              str++;
            }
          cos_name.push_back (CosNaming::NameComponent (begin, str));
        }
      while (0 != *str++);
    }
  }
}
