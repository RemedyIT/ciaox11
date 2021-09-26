// -*- C++ -*-
/**
 * @file    opendds_domain_participant.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/opendds_domain_participant.h"
#include "dds/dds_vendor_adapter.h"
#include "dds/base_traits.h"

#include "dds/dds_subscriber_listener.h"
#include "dds/dds_publisher_listener.h"
#include "dds/dds_topic_listener.h"
#include "dds/dds_topic.h"

#include "dds/dds_proxy_entity_manager.h"
#include "dds/DCPS/QOS_XML_Handler/QOS_XML_Loader.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/opendds_xml_error_handler.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    OpenDDS_DomainParticipant_proxy::OpenDDS_DomainParticipant_proxy (
        DDS_Native::DDS::DomainParticipant *dp)
      : NativeEntityBase_T<DDS_Native::DDS::DomainParticipant> (dp)
      , DDS_DomainParticipant_proxy (dp)
    {
    }

    IDL::traits< ::DDS::Publisher>::ref_type
    OpenDDS_DomainParticipant_proxy::create_publisher_with_profile (
      const std::string &qos_profile,
      IDL::traits< ::DDS::PublisherListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("OpenDDS_DomainParticipant_proxy::create_publisher_with_profile");

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_publisher_with_profile <"
        << qos_profile << "> - Start creating Publisher.");

      // Re are creating a XML Loader for each time we use it, we should
      // be able to reuse an instance, but each dds entity could have its own unique qos
      // file at the DDSX11 level but the XML loader can only handle one file at the time.
      OpenDDS::DCPS::QOS_XML_Loader xml_loader (new DDSX11::DDSX11_XML_Error_Handler);

      ::DDS::ReturnCode_t retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        xml_loader.init (::DDSX11::traits<std::string>::in (qos_profile)));
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::create_publisher_with_profile - "
            << "Error: Unable to load the XML for <"
            << qos_profile
            << "> init returns <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      ::DDS::PublisherQos qos;
      retcode = this->get_default_publisher_qos (qos);
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::create_publisher_with_profile - "
            << "Error: Unable to retrieve the default PublisherQos <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_publisher_with_profile - "
        << "Retrieved default PublisherQos <"
        << IDL::traits< ::DDS::PublisherQos>::write (qos)
        << ">");

      xml_loader.get_publisher_qos (
        ::DDSX11::traits< ::DDS::PublisherQos>::inout (qos),
        ::DDSX11::traits<std::string>::in (qos_profile));

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_publisher_with_profile - "
        << "Retrieved XML PublisherQos <"
        << IDL::traits< ::DDS::PublisherQos>::write (qos)
        << ">");

      return this->create_publisher (qos, std::move(a_listener), mask);
    }

    IDL::traits< ::DDS::Subscriber>::ref_type
    OpenDDS_DomainParticipant_proxy::create_subscriber_with_profile (
      const std::string &qos_profile,
      IDL::traits< ::DDS::SubscriberListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("OpenDDS_DomainParticipant_proxy::create_subscriber_with_profile");

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_subscriber_with_profile <"
        << qos_profile << "> - Creating Subscriber.");

      // Re are creating a XML Loader for each time we use it, we should
      // be able to reuse an instance, but each dds entity could have its own unique qos
      // file at the DDSX11 level but the XML loader can only handle one file at the time.
      OpenDDS::DCPS::QOS_XML_Loader xml_loader (new DDSX11::DDSX11_XML_Error_Handler);

      ::DDS::ReturnCode_t retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        xml_loader.init (::DDSX11::traits<std::string>::in (qos_profile)));
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::create_subscriber_with_profile - "
            << "Error: Unable to load the XML for <"
            << qos_profile
            << "> init returns <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      ::DDS::SubscriberQos qos;
      retcode = this->get_default_subscriber_qos (qos);
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::create_subscriber_with_profile - "
            << "Error: Unable to retrieve the default SubscriberQos <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_subscriber_with_profile - "
        << "Retrieved default SubscriberQos <"
        << IDL::traits< ::DDS::SubscriberQos>::write (qos)
        << ">");

      xml_loader.get_subscriber_qos (
        ::DDSX11::traits< ::DDS::SubscriberQos>::inout (qos),
        ::DDSX11::traits<std::string>::in (qos_profile));

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_subscriber_with_profile - "
        << "Retrieved XML SubscriberQos <"
        << IDL::traits< ::DDS::SubscriberQos>::write (qos)
        << ">");

      return this->create_subscriber (qos, std::move(a_listener), mask);
    }

    IDL::traits< ::DDS::Topic>::ref_type
    OpenDDS_DomainParticipant_proxy::create_topic_with_profile (
      const std::string &topic_name,
      const std::string &type_name,
      const std::string &qos_profile,
      IDL::traits< ::DDS::TopicListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("OpenDDS_DomainParticipant_proxy::create_topic_with_profile");

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_topic_with_profile <"
        << qos_profile << "> - Attempting to create topic with name <"
        << topic_name << "> and type <" << type_name << ">");

      // Re are creating a XML Loader for each time we use it, we should
      // be able to reuse an instance, but each dds entity could have its own unique qos
      // file at the DDSX11 level but the XML loader can only handle one file at the time.
      OpenDDS::DCPS::QOS_XML_Loader xml_loader (new DDSX11::DDSX11_XML_Error_Handler);

      ::DDS::ReturnCode_t retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        xml_loader.init (::DDSX11::traits<std::string>::in (qos_profile)));
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::create_topic_with_profile - "
            << "Error: Unable to load the XML for <"
            << qos_profile
            << "> init returns <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      ::DDS::TopicQos qos;
      retcode = this->get_default_topic_qos (qos);
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::create_topic_with_profile - "
            << "Error: Unable to retrieve the default TopicQos <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_topic_with_profile - "
        << "Retrieved default TopicQos <"
        << IDL::traits< ::DDS::TopicQos>::write (qos)
        << ">");

      xml_loader.get_topic_qos (
        ::DDSX11::traits< ::DDS::TopicQos>::inout (qos),
        ::DDSX11::traits<std::string>::in (qos_profile),
        ::DDSX11::traits<std::string>::in (topic_name));

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::create_topic_with_profile - "
        << "Retrieved XML TopicQos <"
        << IDL::traits< ::DDS::TopicQos>::write (qos)
        << ">");

      return this->create_topic (topic_name, type_name, qos, std::move(a_listener), mask);
    }
  }
}
