/**
 * @file    ndds_specific.cpp
 * @author  Marcel Smit
 *
 * @brief   Generic class which creates the NDDS specific entities.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_vendor_adapter.h"

#include "dds/ndds_publisher.h"
#include "dds/ndds_subscriber.h"
#include "dds/ndds_domain_participant.h"
#include "dds/ndds_publisher_listener.h"
#include "dds/ndds_domain_participant_factory.h"
#include "dds/ndds_base_traits.h"
#include "dds/dds_proxy_entity_manager.h"
#include "dds/dds_wait_set.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  namespace VendorUtils
  {
    IDL::traits<::DDS::Publisher>::ref_type
    create_publisher_proxy (
      DDS_Native::DDS::Publisher *p)
    {
      auto proxy = CORBA::make_reference<NDDS_PROXY::NDDS_Publisher_proxy> (p);
      return proxy;
    }

    IDL::traits<::DDS::Subscriber>::ref_type
    create_subscriber_proxy (
      DDS_Native::DDS::Subscriber *s)
    {
      auto proxy = CORBA::make_reference<NDDS_PROXY::NDDS_Subscriber_proxy> (s);
      return proxy;
    }

    IDL::traits<::DDS::DomainParticipant>::ref_type
    create_domain_participant_proxy (
      DDS_Native::DDS::DomainParticipant *dp)
    {
      auto proxy = CORBA::make_reference<NDDS_PROXY::NDDS_DomainParticipant_proxy> (dp);
      return proxy;
    }

    IDL::traits<::DDS::WaitSet>::ref_type
    create_waitset ()
    {
      DDS_Native::DDS::WaitSet_var waitset = new (std::nothrow) DDS_Native::DDS::WaitSet ();
      if (!waitset)
      {
        return {};
      }
      return CORBA::make_reference<DDSX11::DDS_WaitSet_proxy> (waitset);
    }

    IDL::traits<::DDS::DomainParticipantFactory>::ref_type
    init_dds ()
    {
      DDSX11_IMPL_LOG_DEBUG ("DDSX11::VendorUtils::init_dds - Initializing NDDS");

      const char * log_verbosity_env = std::getenv ("DDSX11_NDDS_LOG_VERBOSITY");
      if (log_verbosity_env != nullptr)
      {
        if (std::strcmp (log_verbosity_env, "NDDS_CONFIG_LOG_VERBOSITY_SILENT") == 0)
          NDDSConfigLogger::get_instance()->set_verbosity (NDDS_CONFIG_LOG_VERBOSITY_SILENT);
        else if (std::strcmp (log_verbosity_env, "NDDS_CONFIG_LOG_VERBOSITY_ERROR") == 0)
          NDDSConfigLogger::get_instance()->set_verbosity (NDDS_CONFIG_LOG_VERBOSITY_ERROR);
        else if (std::strcmp (log_verbosity_env, "NDDS_CONFIG_LOG_VERBOSITY_WARNING") == 0)
          NDDSConfigLogger::get_instance()->set_verbosity (NDDS_CONFIG_LOG_VERBOSITY_WARNING);
        else if (std::strcmp (log_verbosity_env, "NDDS_CONFIG_LOG_VERBOSITY_STATUS_LOCAL") == 0)
          NDDSConfigLogger::get_instance()->set_verbosity (NDDS_CONFIG_LOG_VERBOSITY_STATUS_LOCAL);
        else if (std::strcmp (log_verbosity_env, "NDDS_CONFIG_LOG_VERBOSITY_STATUS_REMOTE") == 0)
          NDDSConfigLogger::get_instance()->set_verbosity (NDDS_CONFIG_LOG_VERBOSITY_STATUS_REMOTE);
        else if (std::strcmp (log_verbosity_env, "NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL") == 0)
          NDDSConfigLogger::get_instance()->set_verbosity (NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
      }
      const char * log_format_env = std::getenv ("DDSX11_NDDS_LOG_PRINT_FORMAT");
      if (log_format_env != nullptr)
      {
        if (std::strcmp (log_format_env, "NDDS_CONFIG_LOG_PRINT_FORMAT_DEFAULT") == 0)
          NDDSConfigLogger::get_instance()->set_print_format (NDDS_CONFIG_LOG_PRINT_FORMAT_DEFAULT);
        else if (std::strcmp (log_format_env, "NDDS_CONFIG_LOG_PRINT_FORMAT_TIMESTAMPED") == 0)
          NDDSConfigLogger::get_instance()->set_print_format (NDDS_CONFIG_LOG_PRINT_FORMAT_TIMESTAMPED);
        else if (std::strcmp (log_format_env, "NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE") == 0)
          NDDSConfigLogger::get_instance()->set_print_format (NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE);
        else if (std::strcmp (log_format_env, "NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE_TIMESTAMPED") == 0)
          NDDSConfigLogger::get_instance()->set_print_format (NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE_TIMESTAMPED);
        else if (std::strcmp (log_format_env, "NDDS_CONFIG_LOG_PRINT_FORMAT_DEBUG") == 0)
          NDDSConfigLogger::get_instance()->set_print_format (NDDS_CONFIG_LOG_PRINT_FORMAT_DEBUG);
        else if (std::strcmp (log_format_env, "NDDS_CONFIG_LOG_PRINT_FORMAT_MINIMAL") == 0)
          NDDSConfigLogger::get_instance()->set_print_format (NDDS_CONFIG_LOG_PRINT_FORMAT_MINIMAL);
        else if (std::strcmp (log_format_env, "NDDS_CONFIG_LOG_PRINT_FORMAT_MAXIMAL") == 0)
          NDDSConfigLogger::get_instance()->set_print_format (NDDS_CONFIG_LOG_PRINT_FORMAT_MAXIMAL);
      }

      return CORBA::make_reference<DDSX11::NDDS_PROXY::NDDS_DomainParticipantFactory_proxy> (DDS_Native::DDS::DomainParticipantFactory::get_instance());
    }

    IDL::traits<::DDS::DomainParticipantFactory>::ref_type
    domain_participant_factory ()
    {
      DDSX11_IMPL_LOG_DEBUG ("DDSX11::VendorUtils::domain_participant_factory");
      // See C++ specification section 6.7 [stmt.dcl] p4
      static IDL::traits<::DDS::DomainParticipantFactory>::ref_type dpf = init_dds ();
      return dpf;
    }

    DDS_Native::DDS::PublisherListener*
    create_publisher_listener (
      IDL::traits<::DDS::PublisherListener>::ref_type listener)
    {
      return new NDDS_PROXY::NDDS_PublisherListener_proxy (std::move(listener));
    }

    ::DDS::DomainParticipantQos
    participant_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::DomainParticipantQos>::retn (DDS_PARTICIPANT_QOS_DEFAULT);
    }

    ::DDS::TopicQos
    topic_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::TopicQos>::retn (DDS_TOPIC_QOS_DEFAULT);
    }

    ::DDS::PublisherQos
    publisher_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::PublisherQos>::retn (DDS_PUBLISHER_QOS_DEFAULT);
    }

    ::DDS::SubscriberQos
    subscriber_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::SubscriberQos>::retn (DDS_SUBSCRIBER_QOS_DEFAULT);
    }

    ::DDS::DataWriterQos
    datawriter_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::DataWriterQos>::retn (DDS_DATAWRITER_QOS_DEFAULT);
    }

    ::DDS::DataReaderQos
    datareader_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::DataReaderQos>::retn (DDS_DATAREADER_QOS_DEFAULT);
    }
  }
}
