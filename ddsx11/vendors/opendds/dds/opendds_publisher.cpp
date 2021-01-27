// -*- C++ -*-
/**
 * @file    opendds_publisher.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/opendds_publisher.h"
#include "dds/dds_publisher_listener.h"
#include "dds/dds_type_support.h"
#include "dds/DCPS/QOS_XML_Handler/QOS_XML_Loader.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    OpenDDS_Publisher_proxy::OpenDDS_Publisher_proxy (
        DDS_Native::DDS::Publisher * p)
      : NativeEntityBase_T<DDS_Native::DDS::Publisher>(p)
      , DDS_Publisher_proxy (p)
    {
    }

    IDL::traits< ::DDS::DataWriter>::ref_type
    OpenDDS_Publisher_proxy::create_datawriter_with_profile (
      IDL::traits< ::DDS::Topic>::ref_type a_topic,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("OpenDDS_Publisher_proxy::create_datawriter_with_profile");

      // We are creating a XML Loader for each time we use it, we should
      // be able to reuse an instance, but each dds entity could have its own unique qos
      // file at the DDSX11 level but the XML loader can only handle one file at the time.
      OpenDDS::DCPS::QOS_XML_Loader xml_loader;
      ::DDS::ReturnCode_t retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        xml_loader.init (::DDSX11::traits<std::string>::in (qos_profile)));
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_Publisher_proxy::create_datawriter_with_profile - "
            << "Error: Unable to load the XML for <"
            << qos_profile
            << "> init returns <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      ::DDS::DataWriterQos qos;
      retcode = this->get_default_datawriter_qos (qos);
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_Publisher_proxy::create_datawriter_with_profile - "
            << "Error: Unable to retrieve the default DataWriterQos <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_Publisher_proxy::create_datawriter_with_profile - "
        << "Retrieved default DataWriterQos <"
        << IDL::traits< ::DDS::DataWriterQos>::write (qos)
        << ">");

      std::string const topic_name = a_topic->get_name ();
      xml_loader.get_datawriter_qos (
        ::DDSX11::traits< ::DDS::DataWriterQos>::inout (qos),
        ::DDSX11::traits<std::string>::in (qos_profile),
        ::DDSX11::traits<std::string>::in (topic_name));

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_Publisher_proxy::create_datawriter_with_profile - "
        << "Retrieved XML DataWriterQos <"
        << IDL::traits< ::DDS::DataWriterQos>::write (qos)
        << ">");

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_Publisher_proxy::create_datawriter_with_profile - "
        << "Retrieved XML DataWriterQos <"
        << IDL::traits< ::DDS::DataWriterQos>::write (qos)
        << ">");

      return this->create_datawriter (std::move(a_topic), qos, std::move(a_listener), mask);
    }
  }
}

