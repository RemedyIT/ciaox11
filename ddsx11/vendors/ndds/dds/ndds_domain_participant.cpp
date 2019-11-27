// -*- C++ -*-
/**
 * @file    ndds_domain_participant.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/ndds_domain_participant.h"
#include "dds/ndds_utils.h"
#include "dds/dds_vendor_adapter.h"
#include "dds/ndds_base_traits.h"

#include "dds/ndds_publisher_listener.h"
#include "dds/dds_subscriber_listener.h"
#include "dds/dds_topic_listener.h"
#include "dds/dds_topic.h"
#include "dds/dds_proxy_entity_manager.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    NDDS_DomainParticipant_proxy::NDDS_DomainParticipant_proxy (
        DDS_Native::DDS::DomainParticipant *dp)
      : NativeEntityBase_T<DDS_Native::DDS::DomainParticipant > (dp)
      , DDS_DomainParticipant_proxy (dp)
    {
    }

    IDL::traits< ::DDS::Publisher >::ref_type
    NDDS_DomainParticipant_proxy::create_publisher_with_profile (
      const std::string &qos_profile,
      IDL::traits< ::DDS::PublisherListener >::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("NDDS_DomainParticipant_proxy::create_publisher_with_profile");

      DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipant_proxy::create_publisher_with_profile <"
        << qos_profile << "> - Start creating Publisher.");

      // We're in NDDS so we can use the NDDS specific publisher listener straight
      // away.
      std::unique_ptr<NDDS_PROXY::NDDS_PublisherListener_proxy> dds_proxy_pl {};
      if (a_listener)
        {
          dds_proxy_pl = std::make_unique<NDDS_PROXY::NDDS_PublisherListener_proxy> (a_listener);
        }
      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      DDS_Native::DDS::Publisher *native_pub = nullptr;

      if (!lib_name.empty () && !prof_name.empty ())
        {
          native_pub =
            this->native_entity ()->create_publisher_with_profile (
              ::DDSX11::traits< std::string >::in (lib_name),
              ::DDSX11::traits< std::string >::in (prof_name),
              dds_proxy_pl.get (),
              ::DDSX11::traits< ::DDS::StatusMask >::in (mask));
        }

      if (!native_pub)
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_publisher_with_profile <"
            << qos_profile << "> - Error: Unable to create Publisher.");
          // Listener will be deleted here since the guard goes out of scope.
          return {};
        }

      // DDS was able to create a native entity. We can now safely release the
      // listener otherwise it would be deleted when the unique pointer goes out
      // of scope.
      dds_proxy_pl.release ();

      IDL::traits< ::DDS::Publisher >::ref_type publisher =
        DDSX11::VendorUtils::create_publisher_proxy (native_pub);

      if (publisher)
        {
          DDS_ProxyEntityManager::register_publisher_proxy (publisher);

          DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipant_proxy::create_publisher_with_profile <"
            << qos_profile << "> - Successfully created a Publisher.");
        }
      else
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_publisher_with_profile <"
            << qos_profile << "> - ERROR: Failed to create a Publisher.");
        }

      return publisher;
    }


    IDL::traits< ::DDS::Subscriber >::ref_type
    NDDS_DomainParticipant_proxy::create_subscriber_with_profile (
      const std::string &qos_profile,
      IDL::traits< ::DDS::SubscriberListener >::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("NDDS_DomainParticipant_proxy::create_subscriber_with_profile");

      DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipant_proxy::create_subscriber_with_profile <"
        << qos_profile << "> - Creating Subscriber.");

      std::unique_ptr<DDSX11::DDS_SubscriberListener_proxy> dds_proxy_sl {};
      if (a_listener)
        {
          dds_proxy_sl = std::make_unique<DDSX11::DDS_SubscriberListener_proxy> (a_listener);
        }
      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      DDS_Native::DDS::Subscriber * native_sub {};

      if (!lib_name.empty () && !prof_name.empty ())
        {
          native_sub =
            this->native_entity ()->create_subscriber_with_profile (
              ::DDSX11::traits< std::string >::in (lib_name),
              ::DDSX11::traits< std::string >::in (prof_name),
              dds_proxy_sl.get (),
              ::DDSX11::traits< ::DDS::StatusMask >::in (mask));
        }
      if (!native_sub)
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_subscriber_with_profile <"
            << qos_profile << "> - Error: DDS returned a nil subscriber.");
          // Listener will be deleted here since the guard goes out of scope.
          return {};
        }

      // DDS was able to create a native entity. We can now safely release the
      // listener otherwise it would be deleted when the unique pointer goes out
      // of scope.
      dds_proxy_sl.release ();

      IDL::traits< ::DDS::Subscriber >::ref_type subscriber =
        DDSX11::VendorUtils::create_subscriber_proxy (native_sub);

      if (subscriber)
        {
          // Register the fresh created proxy in the proxy entity manager
          DDS_ProxyEntityManager::register_subscriber_proxy (subscriber);

          DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipant_proxy::create_subscriber_with_profile <"
            << qos_profile << "> - Successfully created a Subscriber.");
        }
      else
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_subscriber_with_profile <"
            << qos_profile << "> - ERROR: Failed to create a Subscriber.");
        }

      return subscriber;
    }


    IDL::traits< ::DDS::Topic >::ref_type
    NDDS_DomainParticipant_proxy::create_topic_with_profile (
      const std::string &impl_name,
      const std::string &type_name,
      const std::string &qos_profile,
      IDL::traits< ::DDS::TopicListener >::ref_type a_listener,
      ::DDS::StatusMask mask)
    {
      DDSX11_LOG_TRACE ("NDDS_DomainParticipant_proxy::create_topic_with_profile");

      if (impl_name.empty ())
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_topic_with_profile <"
            << qos_profile << "> - Error: provided nil topic name.");
          return nullptr;
        }

      if (type_name.empty ())
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_topic_with_profile <"
            << qos_profile << "> - Error: provided nil type name.");
          return nullptr;
        }

      DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipant_proxy::create_topic_with_profile <"
        << qos_profile << "> - Attempting to create topic with name <"
        << impl_name << "> and type <" << type_name << ">");

      std::unique_ptr<DDSX11::DDS_TopicListener_proxy> ccm_dds_tl {};
      if (a_listener != nullptr)
        {
          // Topic will be set later (using set_dds_topic)
          ccm_dds_tl = std::make_unique<DDSX11::DDS_TopicListener_proxy> (a_listener);
        }

      DDS_Native::DDS::Topic * dds_tp = nullptr;

      std::string lib_name, prof_name;
      split_qos_profile (qos_profile, lib_name, prof_name);

      if (!lib_name.empty () && !prof_name.empty ())
        {
          dds_tp =
            this->native_entity ()->create_topic_with_profile (
              ::DDSX11::traits< std::string >::in (impl_name),
              ::DDSX11::traits< std::string >::in (type_name),
              ::DDSX11::traits< std::string >::in (lib_name),
              ::DDSX11::traits< std::string >::in (prof_name),
              ccm_dds_tl.get (),
              ::DDSX11::traits< ::DDS::StatusMask >::in (mask));
        }
      if (!dds_tp)
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_topic_with_profile <"
            << qos_profile << "> - Error: DDS returned a nil topic.");
          // Listener will be deleted here since the guard goes out of scope.
          return {};
        }

      // DDS was able to create a native entity. We can now safely release the
      // listener otherwise it would be deleted when the unique pointer goes out
      // of scope.
      ccm_dds_tl.release ();

      IDL::traits< ::DDS::Topic >::ref_type retval =
        TAOX11_CORBA::make_reference<DDSX11::DDS_Topic_proxy>(dds_tp);
      DDS_ProxyEntityManager::register_topic_proxy (retval);
      if (retval)
        {
          DDSX11_IMPL_LOG_DEBUG ("NDDS_DomainParticipant_proxy::create_topic_with_profile <"
            << qos_profile << "> - Successfully created a Topic.");
        }
      else
        {
          DDSX11_IMPL_LOG_ERROR ("NDDS_DomainParticipant_proxy::create_topic_with_profile <"
            << qos_profile << "> - ERROR: Failed to create a Topic.");
        }
      return retval;
    }
  }
}
