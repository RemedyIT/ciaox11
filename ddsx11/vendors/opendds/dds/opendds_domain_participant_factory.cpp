// -*- C++ -*-
/**
 * @file    opendds_domain_participant_factory.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/DCPS/Service_Participant.h"
#include "dds/opendds_domain_participant_factory.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_adapter.h"
#include "dds/dds_domain_participant_listener.h"
#include "dds/base_traits.h"
#include "dds/dds_proxy_entity_manager.h"
#include "dds/DCPS/QOS_XML_Handler/QOS_XML_Loader.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/opendds_xml_error_handler.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    OpenDDS_DomainParticipantFactory_proxy::OpenDDS_DomainParticipantFactory_proxy (
      DDS_Native::DDS::DomainParticipantFactory * dpf)
      : NativeEntityBase_T<DDS_Native::DDS::DomainParticipantFactory> (dpf)
      , DDSX11::DDS_DomainParticipantFactory_proxy (dpf)
    {
      DDSX11_LOG_TRACE ("OpenDDS_DomainParticipantFactory_proxy::OpenDDS_DomainParticipantFactory_proxy");
    }

    IDL::traits< ::DDS::DomainParticipant>::ref_type
    OpenDDS_DomainParticipantFactory_proxy::create_participant_with_profile (
      ::DDS::DomainId_t domain_id,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DomainParticipantListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE (
        "OpenDDS_DomainParticipantFactory_proxy::create_participant_with_profile");

      DDSX11_IMPL_LOG_DEBUG (
        "OpenDDS_DomainParticipantFactory_proxy::create_participant_with_profile - "
        << "Start creating domain participant: profile <" << qos_profile
        << "> - domain <" << domain_id << ">");

      // Re are creating a XML Loader for each time we use it, we should
      // be able to reuse an instance, but each dds entity could have its own unique QoS
      // file at the DDSX11 level but the XML loader can only handle one file at the time.
      OpenDDS::DCPS::QOS_XML_Loader xml_loader (new DDSX11::DDSX11_XML_Error_Handler);

      ::DDS::ReturnCode_t retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        xml_loader.init (::DDSX11::traits<std::string>::in (qos_profile)));
      if (retcode != ::DDS::RETCODE_OK)
        {
          // Could be a QoS XML error
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipantFactory_proxy::create_participant_with_profile - "
            << "Error: Unable to load the XML for <"
            << qos_profile
            << "> init returns <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      ::DDS::DomainParticipantQos qos;
      retcode = this->get_default_participant_qos (qos);
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipantFactory_proxy::create_participant_with_profile - "
            << "Error: Unable to retrieve the default DomainParticipantQos <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipantFactory_proxy::create_participant_with_profile - "
        << "Retrieved default DomainParticipantQos <"
        << IDL::traits< ::DDS::DomainParticipantQos>::write (qos)
        << ">");

      xml_loader.get_participant_qos (::DDSX11::traits< ::DDS::DomainParticipantQos>::inout (qos), ::DDSX11::traits<std::string>::in (qos_profile));

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipantFactory_proxy::create_participant_with_profile - "
        << "Retrieved XML DomainParticipantQos <"
        << IDL::traits< ::DDS::DomainParticipantQos>::write (qos)
        << ">");

      return this->create_participant (domain_id, qos, std::move(a_listener), mask);
    }

    ::DDS::ReturnCode_t
    OpenDDS_DomainParticipantFactory_proxy::finalize_instance ()
    {
      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipantFactory_proxy::finalize_instance - Finalizing OpenDDS");

      ::DDS::ReturnCode_t const retcode =
        ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (TheServiceParticipant->shutdown ());

      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipantFactory_proxy::finalize_instance - "
            << "Error: Unable to shutdown TheServiceParticipant <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return retcode;
        }
      else
        {
          DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipantFactory_proxy::finalize_instance - "
            << "Shutdown TheServiceParticipant");

          this->clear_native_entity ();

          DDS_ProxyEntityManager::finalize ();
        }

      return retcode;
    }

    ::DDS::ReturnCode_t
    OpenDDS_DomainParticipantFactory_proxy::set_default_participant_qos_with_profile (
      const std::string &qos_profile)
    {
      DDSX11_LOG_TRACE ("OpenDDS_DomainParticipantFactory_proxy::set_default_participant_qos_with_profile");

      // Re are creating a XML Loader for each time we use it, we should
      // be able to reuse an instance, but each dds entity could have its own unique qos
      // file at the DDSX11 level but the XML loader can only handle one file at the time.
      OpenDDS::DCPS::QOS_XML_Loader xml_loader;
      ::DDS::ReturnCode_t retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        xml_loader.init (::DDSX11::traits<std::string>::in (qos_profile)));
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipantFactory_proxy::set_default_participant_qos_with_profile - "
            << "Error: Unable to load the XML for <"
            << qos_profile
            << "> init returns <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return retcode;
        }

      ::DDS::DomainParticipantQos qos;
      retcode = this->get_default_participant_qos (qos);
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipantFactory_proxy::set_default_participant_qos_with_profile - "
            << "Error: Unable to retrieve the default DomainParticipantQos <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return retcode;
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipantFactory_proxy::set_default_participant_qos_with_profile - "
        << "Retrieved default DomainParticipantQos <"
        << IDL::traits< ::DDS::DomainParticipantQos>::write (qos)
        << ">");

      xml_loader.get_participant_qos (::DDSX11::traits< ::DDS::DomainParticipantQos>::inout (qos), ::DDSX11::traits<std::string>::in (qos_profile));

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipantFactory_proxy::set_default_participant_qos_with_profile - "
        << "Retrieved XML DomainParticipantQos <"
        << IDL::traits< ::DDS::DomainParticipantQos>::write (qos)
        << ">");

      return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
          this->native_entity ()->set_default_participant_qos (::DDSX11::traits< ::DDS::DomainParticipantQos>::in (qos)));
    }
  }
}
