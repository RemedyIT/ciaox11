/**
 * @file deployment_interceptors.cpp
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Deployment interceptors for CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "deployment_interceptors.h"
#include "name_utilities.h"
#include "dancex11/deployment/deployment_starterrorC.h"
#include "dancex11/core/dancex11_propertiesC.h"
#include "dancex11/core/dancex11_utility.h"
#include "dancex11/core/dancex11_deployment_state.h"
#include "ciaox11/logger/log.h"

#include <algorithm>

namespace CIAOX11
{
  /// Implementation skeleton constructor
  StoreReferences_i::StoreReferences_i ()
  {
    this->orb_ = DAnCEX11::State::instance ()->orb ();

    if (!this->orb_)
    {
      CIAOX11_LOG_ERROR ("StoreReferences_i::StoreReferences_i - Unable to locate ORB");
      throw ::Deployment::StartError ("StoreReferences_i",
                                      "Unable to locate ORB");
    }
  }

  /// Implementation skeleton destructor
  StoreReferences_i::~StoreReferences_i ()
  {
  }

  void
  StoreReferences_i::post_install (
    const ::Deployment::DeploymentPlan &plan,
    uint32_t index,
    const ::CORBA::Any &reference,
    const ::CORBA::Any &exception)
  {
    const ::Deployment::InstanceDeploymentDescription &inst =
      plan.instance ()[index];

    CIAOX11_LOG_DEBUG ("StoreReferences_i::post_install - "
                       "Interceptor post install starting for instance <" <<
                       inst.name () << ">");

    if (exception.type()->kind () != CORBA::TCKind::tk_null)
    {
      CIAOX11_LOG_ERROR ("StoreReferences_i::post_install - "
                         "Propagating exception from instance <" <<
                         inst.name () << ">");
      DAnCEX11::Utility::throw_exception_from_any (exception);
    }

    if (reference.type()->kind () == CORBA::TCKind::tk_null)
    {
      CIAOX11_LOG_INFO ("StoreReferences_i::post_install - "
                        "Empty reference Any; nothing to store for instance <" <<
                        inst.name () << ">");
      return;
    }

    IDL::traits<CORBA::Object>::ref_type obj;
    if (!(reference >>= obj) || !obj)
    {
      CIAOX11_LOG_INFO ("StoreReferences_i::post_install - "
                        << "No reference extracted from Any for instance <"
                        << inst.name () << ">");
      return;
    }

    std::string name;
    if (DAnCEX11::Utility::get_property_value (DAnCEX11::REGISTER_NAMING,
                                               inst.configProperty (),
                                               name))
    {
      if (Name_Utilities::bind_object (name, obj, this->ctx_))
      {
        CIAOX11_LOG_DEBUG ("StoreReferences_i::post_install - "
                          "Registered <" << name << "> for instance <"
                          << inst.name () << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("StoreReferences_i::post_install - "
                          "Error registering <" << name << "> for instance <"
                          << inst.name () << ">");
      }
    }
    else if (DAnCEX11::Utility::get_property_value (DAnCEX11::INSTANCE_IOR_FILE,
                                                    inst.configProperty (),
                                                    name))
    {
      std::string const ior = this->orb_->object_to_string (obj);
      if (Name_Utilities::write_ior (name, ior))
      {
        CIAOX11_LOG_DEBUG ("StoreReferences_i::post_install - "
                          "Written IOR for instance <"
                          << inst.name () << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("StoreReferences_i::post_install - "
                          "Unable to write IOR for instance <"
                          << inst.name () << ">");
      }
    }

    CIAOX11_LOG_DEBUG ("StoreReferences_i::post_install - "
                       "Interceptor post install finished for instance <" << inst.name () << ">");
  }

  void
  StoreReferences_i::post_remove (
    const ::Deployment::DeploymentPlan &plan,
    uint32_t instanceRef,
    const CORBA::Any & exception_thrown)
  {
    const ::Deployment::InstanceDeploymentDescription &inst =
      plan.instance ()[instanceRef];

    CIAOX11_LOG_DEBUG ("StoreReferences_i::post_remove - "
                       "Interceptor post remove starting for instance <"
                       << inst.name () << ">");

    if (exception_thrown.type()->kind () != CORBA::TCKind::tk_null)
    {
      CIAOX11_LOG_ERROR ("StoreReferences_i::post_remove - "
                         "Propagating exception from instance <"
                         << inst.name () << ">");
      DAnCEX11::Utility::throw_exception_from_any (exception_thrown);
    }

    std::string name;
    if (DAnCEX11::Utility::get_property_value (DAnCEX11::REGISTER_NAMING,
                                               inst.configProperty (),
                                               name))
    {
      if (Name_Utilities::unbind_object (name, this->ctx_))
      {
        CIAOX11_LOG_DEBUG ("StoreReferences_i::post_remove - "
                          "Un-registered <" << name << "> for instance <"
                          << inst.name () << ">");
      }
      else
      {
        CIAOX11_LOG_ERROR ("StoreReferences_i::post_remove - "
                          "Error un-registering <" << name << "> for instance <"
                          << inst.name () << ">");
      }
    }

    CIAOX11_LOG_DEBUG ("StoreReferences_i::post_remove - "
                       "Interceptor post remove finished for instance <"
                       << inst.name () << ">");
  }

  void
  StoreReferences_i::configure (const Deployment::Properties &props)
  {
    CIAOX11_LOG_TRACE ("StoreReferences_i::configure");

    auto itprop = std::find_if (props.cbegin (), props.cend (),
                                [&](const Deployment::Property& prop) {
                                  return prop.name () == DAnCEX11::LOCALITY_NAMINGCONTEXT;
                                });
    if (itprop == props.cend ())
    {
      CIAOX11_LOG_DEBUG ("StoreReferences_i::configure - "
                         "no <" << DAnCEX11::LOCALITY_NAMINGCONTEXT << "> property found; "
                         "checking for <" << DAnCEX11::DOMAIN_NC << "> instead");

      itprop = std::find_if (props.cbegin (), props.cend (),
                             [&](const Deployment::Property& prop) {
                                return prop.name () == DAnCEX11::DOMAIN_NC;
                             });
    }
    if (itprop != props.cend ())
    {
      std::string nc_ior;
      if (itprop->value () >>= nc_ior)
      {
        CIAOX11_LOG_DEBUG ("StoreReferences_i::configure - "
                           "found NC value <" << nc_ior << ">");

        IDL::traits<CORBA::Object>::ref_type obj =
          this->orb_->string_to_object (nc_ior);
        if (obj)
        {
          this->ctx_ = IDL::traits<CosNaming::NamingContext>::narrow (obj);
          if (!this->ctx_)
          {
            CIAOX11_LOG_ERROR ("StoreReferences_i::configure - " <<
                              "unable to narrow naming context from resolved IOR <"
                              << nc_ior << ">");
          }
        }
        else
        {
          CIAOX11_LOG_ERROR ("StoreReferences_i::configure - " <<
                            "unable to resolve naming context IOR <"
                            << nc_ior << ">");
        }
      }
      else
      {
        CIAOX11_LOG_ERROR ("StoreReferences_i::configure - " <<
                           "Unable to extract naming context from Any <"
                           << itprop->name ());
      }
    }
  }

  /// Implementation skeleton constructor
  ReferenceLookup_i::ReferenceLookup_i ()
  {
    this->orb_ = DAnCEX11::State::instance ()->orb ();

    if (!this->orb_)
    {
      CIAOX11_LOG_ERROR ("ReferenceLookup_i::ReferenceLookup_i - Unable to locate ORB");
      throw ::Deployment::StartError ("ReferenceLookup_i",
                                      "Unable to locate ORB");
    }
  }

  /// Implementation skeleton destructor
  ReferenceLookup_i::~ReferenceLookup_i ()
  {
  }

  void
  ReferenceLookup_i::pre_connect (
    ::Deployment::DeploymentPlan &plan,
    uint32_t connRef,
    ::CORBA::Any &providedRef)
  {
    const ::Deployment::PlanConnectionDescription &conn =
      plan.connection ()[connRef];

    CIAOX11_LOG_DEBUG ("ReferenceLookup_i::pre_connect - "
                       "Interceptor pre connect starting for connection <"
                       << conn.name () << ">");

    // attempt to resolve CORBA IOR type external references
    if (conn.externalReference ().size () > 0)
    {
      IDL::traits<CORBA::Object>::ref_type obj;
      if (!(providedRef >>= obj))
      {
        CIAOX11_LOG_ERROR ("ReferenceLookup_i::pre_connect - "
                          "Unable to extract reference from Any for connection <"
                          << conn.name () << ">");
      }

      if (!obj)
      {
        try
        {
          obj =
            this->orb_->string_to_object(conn.externalReference ()[0].location());
          providedRef <<= obj;
        }
        catch (const CORBA::INV_OBJREF&)
        {
          CIAOX11_LOG_ERROR ("ReferenceLookup_i::pre_connect - "
                            "Unable to resolve external reference for connection <"
                            << conn.name () << ">");
        }
        catch (const CORBA::Exception &ex)
        {
          CIAOX11_LOG_ERROR ("ReferenceLookup_i::pre_connect - "
                            "Caught CORBA exception while resolving external reference for connection <"
                            << conn.name () << ">:<" << ex << ">");
          throw;
        }
        catch (...)
        {
          CIAOX11_LOG_ERROR ("ReferenceLookup_i::pre_connect - "
                            "Caught exception while resolving external reference for connection <"
                            << conn.name () << ">");
          throw;
        }
      }
    }

  }
}

extern "C"
{
  void
  CIAOX11_Deployment_Interceptors_Export create_CIAOX11_StoreReferences (
    IDL::traits<DAnCEX11::DeploymentInterceptor>::ref_type& interceptor)
  {
    interceptor = CORBA::make_reference <CIAOX11::StoreReferences_i> ();
  }

  void
  CIAOX11_Deployment_Interceptors_Export create_CIAOX11_ReferenceLookup (
    IDL::traits<DAnCEX11::DeploymentInterceptor>::ref_type& interceptor)
  {
    interceptor = CORBA::make_reference <CIAOX11::ReferenceLookup_i> ();
  }
}
