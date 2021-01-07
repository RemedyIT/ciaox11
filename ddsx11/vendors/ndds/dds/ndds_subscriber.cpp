// -*- C++ -*-
/**
 * @file    ndds_subscriber.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/ndds_subscriber.h"
#include "dds/dds_data_reader_listener.h"
#include "dds/ndds_utils.h"
#include "dds/ndds_base_traits.h"
#include "dds/dds_type_support.h"
#include "dds/dds_content_filtered_topic.h"
#include "dds/dds_topic.h"
#include "dds/dds_proxy_entity_manager.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    NDDS_Subscriber_proxy::NDDS_Subscriber_proxy (
      DDS_Native::DDS::Subscriber * sub)
      : NativeEntityBase_T<DDS_Native::DDS::Subscriber>(sub)
      , DDS_Subscriber_proxy (sub)
    {
    }

    DDS_Native::DDS::DataReader *
    NDDS_Subscriber_proxy::create_native_datareader_with_profile (
      IDL::traits< ::DDS::ContentFilteredTopic>::ref_type topic,
      const std::string &qos_profile,
      DDS_Native::DDS::DataReaderListener * native_drl,
      ::DDS::StatusMask mask)
    {
      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      if (!lib_name.empty () && !prof_name.empty ())
        {
          return
            this->native_entity ()->create_datareader_with_profile (
              DDSX11::cft_trait::native (topic),
              ::DDSX11::traits<std::string>::in (lib_name),
              ::DDSX11::traits<std::string>::in (prof_name),
              native_drl,
              ::DDSX11::traits< ::DDS::StatusMask>::in (mask));
        }
      return nullptr;
    }

    DDS_Native::DDS::DataReader *
    NDDS_Subscriber_proxy::create_native_datareader_with_profile (
      IDL::traits< ::DDS::Topic>::ref_type topic,
      const std::string &qos_profile,
      DDS_Native::DDS::DataReaderListener * native_drl,
      ::DDS::StatusMask mask)
    {
      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      if (!lib_name.empty () && !prof_name.empty ())
        {
          return
            this->native_entity ()->create_datareader_with_profile (
              DDSX11::topic_trait::native (topic),
              ::DDSX11::traits<std::string>::in (lib_name),
              ::DDSX11::traits<std::string>::in (prof_name),
              native_drl,
              ::DDSX11::traits< ::DDS::StatusMask>::in (mask));
        }
      return nullptr;
    }

    IDL::traits< ::DDS::DataReader>::ref_type
    NDDS_Subscriber_proxy::create_datareader_with_profile (
      IDL::traits< ::DDS::TopicDescription>::ref_type a_topic,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DataReaderListener>::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("NDDS_Subscriber_proxy::create_datareader_with_profile");

      std::unique_ptr<DDSX11::DDS_DataReaderListener_proxy> proxy_drl {};
      if (a_listener)
        {
          proxy_drl = std::make_unique<DDSX11::DDS_DataReaderListener_proxy> (a_listener);
        }

      DDS_Native::DDS::DataReader_var native_dr {};

      IDL::traits< ::DDS::Topic>::ref_type topic =
        IDL::traits< ::DDS::Topic>::narrow (a_topic);

      if (!topic)
        {
          IDL::traits< ::DDS::ContentFilteredTopic>::ref_type cf_topic =
            IDL::traits< ::DDS::ContentFilteredTopic>::narrow (a_topic);
          if (!cf_topic)
            {
              DDSX11_IMPL_LOG_ERROR (
                "NDDS_Subscriber_proxy::create_datareader_with_profile <"
                << qos_profile << "> - Error: Unable retrieve the native "
                "topic from the provided topic.\n");
              // Listener will be destroyed here since the guard goes out of scope.
              return {};
            }
          else
            {
              native_dr = this->create_native_datareader_with_profile (
                cf_topic, qos_profile, proxy_drl.get (), mask);
            }
        }
      else
        {
          native_dr = this->create_native_datareader_with_profile (
            topic, qos_profile, proxy_drl.get (), mask);
        }

      if (!native_dr)
        {
          DDSX11_IMPL_LOG_ERROR (
            "NDDS_Subscriber_proxy::create_datareader_with_profile <"
            << qos_profile << "> - Error: DDS Subscriber returned a "
            "null datareader");
          return nullptr;
        }

      // DDS was able to create a native entity. We can now safely release the
      // listener otherwise it would be deleted when the unique pointer goes out
      // of scope.
      proxy_drl.release ();

      DDSX11_IMPL_LOG_DEBUG (
          "NDDS_Subscriber_proxy::create_datareader_with_profile - "
          "Successfully created native datareader with profile <"
          << qos_profile << ">");

      DDS_Native::DDS::DomainParticipant_var native_dp =
        this->native_entity ()->get_participant ();

      // Create the X11 typed data reader
      IDL::traits< ::DDS::DataReader>::ref_type datareader =
        DDS_TypeSupport_i::create_datareader (
              native_dp,
              a_topic->get_type_name (),
              native_dr);

      if (datareader)
        {
          // Register the fresh created proxy in the proxy entity manager
          if (DDS_ProxyEntityManager::register_datareader_proxy (datareader, native_dr))
          {
            DDSX11_IMPL_LOG_DEBUG ("NDDS_Subscriber_proxy::create_datareader_with_profile - "
              << "Successfully created and registered a datareader with profile <"
              << qos_profile << ">");
          }
          else
          {
            datareader = nullptr;

            DDSX11_IMPL_LOG_ERROR ("NDDS_Subscriber_proxy::create_datareader_with_profile - "
              << "ERROR: Failed to register a datareader proxy.");
          }
        }
      else
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_Subscriber_proxy::create_datareader_with_profile - "
            << "ERROR: Failed to create a data reader.");
        }

      return datareader;
    }
  }
}
