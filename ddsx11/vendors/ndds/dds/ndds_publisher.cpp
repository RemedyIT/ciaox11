// -*- C++ -*-
/**
 * @file    ndds_publisher.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/ndds_publisher.h"
#include "dds/ndds_publisher_listener.h"
#include "dds/dds_type_support.h"
#include "dds/ndds_utils.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    NDDS_Publisher_proxy::NDDS_Publisher_proxy (
        DDS_Native::DDS::Publisher * p)
      : NativeEntityBase_T<DDS_Native::DDS::Publisher>(p)
      , DDS_Publisher_proxy (p)
    {
    }

    IDL::traits< ::DDS::DataWriter>::ref_type
    NDDS_Publisher_proxy::create_datawriter_with_profile (
      IDL::traits< ::DDS::Topic>::ref_type a_topic,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("NDDS_Publisher_proxy::create_datawriter_with_profile");

      DDS_Native::DDS::Topic *topic = DDSX11::topic_trait::native (a_topic);

      if (!topic)
      {
        DDSX11_IMPL_LOG_ERROR (
          "NDDS_Publisher_proxy::create_datawriter_with_profile <"
          << qos_profile << ">- Error: Unable to retrieve the topic proxy.");
        return nullptr;
      }

      std::unique_ptr<DDSX11::DDS_DataWriterListener_proxy> proxy_dwl {};
      if (a_listener)
      {
        proxy_dwl = std::make_unique<DDSX11::DDS_DataWriterListener_proxy> (a_listener);
      }

      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      DDS_Native::DDS::DataWriter_var native_dw {};

      if (!lib_name.empty () && !prof_name.empty ())
      {
        native_dw =
          this->native_entity ()->create_datawriter_with_profile (
            topic,
            ::DDSX11::traits<std::string>::in (lib_name),
            ::DDSX11::traits<std::string>::in (prof_name),
            proxy_dwl.get (),
            ::DDSX11::traits< ::DDS::StatusMask>::in (mask));
      }
      if (!native_dw)
      {
        DDSX11_IMPL_LOG_ERROR ("NDDS_Publisher_proxy::create_datawriter_with_profile <"
          << qos_profile << "> - Error: Native publisher returned a null datawriter.");
        // Listener will be destroyed here since the guard goes out of scope.
        return {};
      }

      // DDS was able to create a native entity. We can now safely release the
      // listener otherwise it would be deleted when the unique pointer goes out
      // of scope.
      proxy_dwl.release ();

      IDL::traits< ::DDS::DataWriter>::ref_type datawriter =
        DDS_TypeSupport_i::create_datawriter (this->get_participant (),
                                              a_topic->get_type_name (),
                                              native_dw);

      if (datawriter)
      {
        if (DDS_ProxyEntityManager::register_datawriter_proxy (datawriter))
        {
          DDSX11_IMPL_LOG_DEBUG ("NDDS_Publisher_proxy::create_datawriter_with_profile - "
            << "Successfully created and registered a datawriter with profile <"
            << qos_profile << ">");
        }
        else
        {
          datawriter = nullptr;

          DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::create_datawriter - "
            << "ERROR: Failed to register a datawriter proxy.");
        }
      }
      else
      {
        DDSX11_IMPL_LOG_ERROR ("NDDS_Publisher_proxy::create_datawriter_with_profile - "
          << "Error: Unable to create a DataWriter with profile <"
          << qos_profile << ">");
      }
      return datawriter;
    }

    IDL::traits< ::DDS::PublisherListener>::ref_type
    NDDS_Publisher_proxy::get_listener ()
    {
      DDSX11_LOG_TRACE ("NDDS_Publisher_proxy::get_listener");

      NDDS_PublisherListener_proxy * publisher_proxy =
        dynamic_cast <NDDS_PublisherListener_proxy *> (
          this->native_entity ()->get_listener ());
      if (!publisher_proxy)
        {
          DDSX11_IMPL_LOG_DEBUG ("NDDS_Publisher_proxy::get_listener - "
            << "DDS returned a null listener.");
          return nullptr;
        }
      return publisher_proxy->get_publisher_listener ();
    }
  }
}

