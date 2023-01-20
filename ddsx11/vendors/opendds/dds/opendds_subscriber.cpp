// -*- C++ -*-
/**
 * @file    opendds_subscriber.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/opendds_subscriber.h"

#include "dds/dds_data_reader_listener.h"

#include "dds/base_traits.h"
#include "dds/dds_type_support.h"
#include "dds/DCPS/QOS_XML_Handler/QOS_XML_Loader.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    OpenDDS_Subscriber_proxy::OpenDDS_Subscriber_proxy (
      DDS_Native::DDS::Subscriber * sub)
      : NativeEntityBase_T<DDS_Native::DDS::Subscriber>(sub)
      , DDS_Subscriber_proxy (sub)
    {
    }

    IDL::traits<::DDS::DataReader>::ref_type
    OpenDDS_Subscriber_proxy::create_datareader_with_profile (
      IDL::traits<::DDS::TopicDescription>::ref_type a_topic,
      const std::string &qos_profile,
      IDL::traits<::DDS::DataReaderListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("OpenDDS_Subscriber_proxy::create_datareader_with_profile");

      // Re are creating a XML Loader for each time we use it, we should
      // be able to reuse an instance, but each dds entity could have its own unique qos
      // file at the DDSX11 level but the XML loader can only handle one file at the time.
      OpenDDS::DCPS::QOS_XML_Loader xml_loader;
      ::DDS::ReturnCode_t retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        xml_loader.init (::DDSX11::traits<std::string>::in (qos_profile)));
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_Subscriber_proxy::create_datareader_with_profile - "
            << "Error: Unable to load the XML for <"
            << qos_profile
            << "> init returns <"
            << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      ::DDS::DataReaderQos qos;
      retcode = this->get_default_datareader_qos (qos);
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_Subscriber_proxy::create_datareader_with_profile - "
            << "Error: Unable to retrieve the default datareader qos <"
            << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
          return {};
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_Subscriber_proxy::create_datareader_with_profile - "
        << "Retrieved default DataReaderQos <"
        << IDL::traits<::DDS::DataReaderQos>::write (qos)
        << ">");

      std::string const topic_name = a_topic->get_name ();
      xml_loader.get_datareader_qos (
        ::DDSX11::traits< ::DDS::DataReaderQos>::inout (qos),
        ::DDSX11::traits<std::string>::in (qos_profile),
        ::DDSX11::traits<std::string>::in (topic_name));

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_Subscriber_proxy::create_datareader_with_profile - "
        << "Retrieved XML DataReaderQos <"
        << IDL::traits<::DDS::DataReaderQos>::write (qos)
        << ">");

      return this->create_datareader (std::move(a_topic), qos, std::move(a_listener), mask);
    }
  }
}
