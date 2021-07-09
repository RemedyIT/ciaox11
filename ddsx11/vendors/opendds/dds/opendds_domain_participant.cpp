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
      OpenDDS::DCPS::QOS_XML_Loader xml_loader;
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
      OpenDDS::DCPS::QOS_XML_Loader xml_loader;
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
      OpenDDS::DCPS::QOS_XML_Loader xml_loader;
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

#if OPENDDS_VERSION_EXACTLY(3, 17, 0)
    // Special OpenDDS version of delete_topic. Within OpenDDS the find_topic
    // returns a topic but on which we can only call delete_topic when we
    // don't use it at all anymore, at the moment we call it before any
    // reader/writer attached to it has been deleted we get a pre condition
    // not met which we ignore, see https://github.com/objectcomputing/OpenDDS/issues/2062
    ::DDS::ReturnCode_t
    OpenDDS_DomainParticipant_proxy::delete_topic (
      IDL::traits< ::DDS::Topic>::ref_type a_topic)
    {
      DDSX11_LOG_TRACE ("OpenDDS_DomainParticipant_proxy::delete_topic");

      IDL::traits< ::DDSX11::DDS_Topic_proxy>::ref_type proxy =
        topic_trait::proxy (a_topic);
      if (!proxy)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::delete_topic - "
            << "Unable to retrieve the proxy topic from the given ref_type.");
          return ::DDS::RETCODE_BAD_PARAMETER;
        }

      DDS_Native::DDS::Topic *top = proxy->get_native_entity ();
      if (!top)
        {
          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::delete_topic - "
            << "Unable to retrieve the native topic from the given ref_type.");
          return ::DDS::RETCODE_BAD_PARAMETER;
        }

      DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::delete_topic - "
        << "Successfully retrieved the native entity from the provided topic");

      // Retrieve the DDS instance handle before deleting it, we need it when
      // unregistering our proxy
      ::DDS::InstanceHandle_t const handle = a_topic->get_instance_handle ();

      // Retrieve our listener so that we can delete it when the delete of the DDS entity
      // has been successful
      TopicListener_Guard listener_guard { top->get_listener () };

      ::DDS::ReturnCode_t retcode =
        ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
          this->native_entity ()->delete_topic (top));

      // Check here also for RETCODE_PRECONDITION_NOT_MET, at that moment we get RETCODE_PRECONDITION_NOT_MET
      // we should still drop the refcount with OpenDDS
      if ((retcode != ::DDS::RETCODE_OK) && (retcode != ::DDS::RETCODE_PRECONDITION_NOT_MET))
        {
          // The delete failed so release the listener guard so that we don't delete
          // the listener
          listener_guard.release ();

          DDSX11_IMPL_LOG_ERROR ("OpenDDS_DomainParticipant_proxy::delete_topic - "
            << "Error: delete_topic returned non-ok error code <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">");
        }
      else
        {
          if (!DDS_ProxyEntityManager::unregister_topic_proxy (top, handle))
            {
              // The topic proxy is still used, so don't destruct the listener yet
              listener_guard.release ();

              DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::delete_topic - "
                << "Did not unregister topic proxy for <" << handle << "> because it is still used");
            }
          else
            {
              // At the moment delete_topic has returned ok and we don't have any
              // references to it anymore, it can be that OpenDDS still has references
              // internally in its topic map, so we call here delete_topic multiple
              // times so that we drop its count to zero, at that moment that has been
              // done by OpenDDS the next call will return not equal to RETCODE_OK
              while (retcode == ::DDS::RETCODE_OK)
                {
                  DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::delete_topic - "
                    << "Trying to delete topic proxy for <" << handle << "> another time from DDS");

                  retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
                    this->native_entity ()->delete_topic (top));
                }

              // Ok, delete_topic returned different retcode, let us put it back to ok
              // so that our caller doesn't get a strange value
              retcode = ::DDS::RETCODE_OK;

              // The unregister_topic_proxy returned true so only at this moment
              // we don't have any references anymore to this proxy so we can clear
              // the pointer to our native entity
              proxy->clear_native_entity ();
            }

          DDSX11_IMPL_LOG_DEBUG ("OpenDDS_DomainParticipant_proxy::delete_topic - "
            << "Provided topic successfully deleted");
        }

      return retcode;
    }
#endif
  }
}
