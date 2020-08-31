// -*- C++ -*-
/**
 * @file    ndds_domain_participant_factory.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/ndds_domain_participant_factory.h"

#include "dds/ndds_utils.h"
#include "dds/dds_vendor_adapter.h"
#include "dds/dds_domain_participant_listener.h"
#include "dds/ndds_base_traits.h"
#include "dds/dds_proxy_entity_manager.h"
#include "logger/ddsx11_log.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    NDDS_DomainParticipantFactory_proxy::NDDS_DomainParticipantFactory_proxy (
      DDS_Native::DDS::DomainParticipantFactory * dpf)
      : NativeEntityBase_T<DDS_Native::DDS::DomainParticipantFactory> (dpf)
      , DDSX11::DDS_DomainParticipantFactory_proxy (dpf)
    {
    }

    IDL::traits< ::DDS::DomainParticipant>::ref_type
    NDDS_DomainParticipantFactory_proxy::create_participant_with_profile (
      ::DDS::DomainId_t domain_id,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DomainParticipantListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE (
        "NDDS_DomainParticipantFactory_proxy::create_participant_with_profile");

      DDSX11_IMPL_LOG_DEBUG (
        "NDDS_DomainParticipantFactory_proxy::create_participant_with_profile - "
        << "Start creating domain participant: profile <" << qos_profile
        << "> - domain <" << domain_id << ">");
      std::unique_ptr<DDSX11::DDS_DomainParticipantListener_proxy> ccm_dds_dpl {};
      if (a_listener)
        {
          ccm_dds_dpl = std::make_unique<DDSX11::DDS_DomainParticipantListener_proxy> (a_listener);
        }

      DDSX11_IMPL_LOG_DEBUG (
        "NDDS_DomainParticipantFactory_proxy::create_participant_with_profile - "
        << "Creating participant: profile <" << qos_profile << "> - domain <"
        << domain_id << ">");

      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      DDS_Native::DDS::DomainParticipant_var dds_dp {};
      if (!lib_name.empty () && !prof_name.empty ())
        {
          dds_dp =
            DDS_Native::DDS::DomainParticipantFactory::get_instance ()->
              create_participant_with_profile (
                ::DDSX11::traits< ::DDS::DomainId_t>::in (domain_id),
                ::DDSX11::traits<std::string>::in (lib_name),
                ::DDSX11::traits<std::string>::in (prof_name),
                ccm_dds_dpl.get (),
                ::DDSX11::traits< ::DDS::StatusMask>::in (mask));
        }

      if (!dds_dp)
        {
          DDSX11_IMPL_LOG_ERROR (
            "NDDS_DomainParticipantFactory_proxy::create_participant_with_profile <"
            << qos_profile << "> - Error: Unable to create DomainParticipant "
            << "for domain <" << domain_id << ">");
          // Listener will be destroyed here since the guard goes out of scope.
          return {};
        }

      // DDS was able to create a native entity. We can now safely release the
      // listener otherwise it would be deleted when the unique pointer goes out
      // of scope.
      ccm_dds_dpl.release ();

      IDL::traits< ::DDS::DomainParticipant>::ref_type retval =
        DDSX11::VendorUtils::create_domain_participant_proxy (dds_dp);

      if (retval)
        {
          // Register the fresh created proxy in the proxy entity manager
          if (DDS_ProxyEntityManager::register_dp_proxy (retval))
            {
              DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipantFactory_proxy::create_participant_with_profile <"
                << qos_profile << "> - Successfully created and registered a DomainParticipant "
                << "for domain <" << domain_id << ">");
            }
          else
            {
              retval = nullptr;

              DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_participant_with_profile - "
                << "ERROR: Failed to register a domainparticipant proxy.");
            }

        }
      else
        {
          DDSX11_IMPL_LOG_ERROR (
            "NDDS_DomainParticipantFactory_proxy::create_participant_with_profile <"
            << qos_profile << "> - Error: Unable to create a DomainParticipant "
            << "for domain <" << domain_id << ">");
        }
      return retval;
    }

    ::DDS::ReturnCode_t
    NDDS_DomainParticipantFactory_proxy::finalize_instance ()
    {
      ::DDS::ReturnCode_t retcode =
        ::DDSX11::traits< ::DDS::ReturnCode_t>::retn
          (DDSDomainParticipantFactory::finalize_instance ());
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipantFactory_proxy::finalize_instance - Error finalizing NDDS: retcode <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode) << ">");
      }
      else
      {
        DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipantFactory_proxy::finalize_instance - Finalizing NDDS");
        DDS_ProxyEntityManager::finalize ();
      }

      return retcode;
    }

    ::DDS::ReturnCode_t
    NDDS_DomainParticipantFactory_proxy::set_default_participant_qos_with_profile (
      const std::string &qos_profile)
    {
      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      ::DDS::ReturnCode_t retcode = ::DDS::RETCODE_ERROR;
      if (!lib_name.empty () && !prof_name.empty ())
        {
          retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
            DDS_Native::DDS::DomainParticipantFactory::get_instance ()->
              set_default_participant_qos_with_profile (
                ::DDSX11::traits<std::string>::in (lib_name),
                ::DDSX11::traits<std::string>::in (prof_name)));
        }

      return retcode;
    }

  }
}
