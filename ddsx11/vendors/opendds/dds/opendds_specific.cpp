/**
 * @file    opendds_specific.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Generic class which creates the OpenDDS specific entities.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/DCPS/Service_Participant.h"
#include "dds/dds_vendor_adapter.h"
#include <dds/DCPS/Marked_Default_Qos.h>
#include "dds/DCPS/transport/framework/TransportDebug.h"
#include "dds/DCPS/transport/framework/TransportConfig_rch.h"
#include "dds/DCPS/transport/framework/TransportRegistry.h"

#include "dds/opendds_publisher.h"
#include "dds/opendds_subscriber.h"
#include "dds/opendds_domain_participant.h"
#include "dds/dds_publisher_listener.h"
#include "dds/opendds_domain_participant_factory.h"
#include "dds/dds_wait_set.h"
#include "dds/dds_vendor_conversion_traits.h"

#include "ace/Env_Value_T.h"

namespace DDSX11
{
  namespace VendorUtils
  {
    IDL::traits< ::DDS::Publisher>::ref_type
    create_publisher_proxy (
      DDS_Native::DDS::Publisher *p)
    {
      auto proxy = TAOX11_CORBA::make_reference<OpenDDS_PROXY::OpenDDS_Publisher_proxy> (p);
      return proxy;
    }

    IDL::traits< ::DDS::Subscriber>::ref_type
    create_subscriber_proxy (
      DDS_Native::DDS::Subscriber *s)
    {
      auto proxy = TAOX11_CORBA::make_reference<OpenDDS_PROXY::OpenDDS_Subscriber_proxy> (s);
      return proxy;
    }

    IDL::traits< ::DDS::DomainParticipant>::ref_type
    create_domain_participant_proxy (
      DDS_Native::DDS::DomainParticipant *dp)
    {
      auto proxy = TAOX11_CORBA::make_reference<OpenDDS_PROXY::OpenDDS_DomainParticipant_proxy> (dp);
      return proxy;
    }

    IDL::traits< ::DDS::WaitSet>::ref_type
    create_waitset ()
    {
      DDS_Native::DDS::WaitSet_var waitset = new (std::nothrow) DDS_Native::DDS::WaitSet ();
      if (!waitset)
      {
        return {};
      }
      return TAOX11_CORBA::make_reference<DDSX11::DDS_WaitSet_proxy> (waitset);
    }

    IDL::traits< ::DDS::DomainParticipantFactory>::ref_type
    init_dds ()
    {
      DDSX11_IMPL_LOG_DEBUG ("DDSX11::VendorUtils::init_dds - Initializing OpenDDS");

      ACE_Env_Value<int> dcpsdl (ACE_TEXT("DDSX11_OPENDDS_LOG_LEVEL"), 0);
      OpenDDS::DCPS::DCPS_debug_level = dcpsdl;
      ACE_Env_Value<int> dcpsdtl (ACE_TEXT("DDSX11_OPENDDS_TRANSPORT_LOG_LEVEL"), 0);
      OpenDDS::DCPS::Transport_debug_level = dcpsdtl;

      TheServiceParticipant->set_default_discovery (OpenDDS::DCPS::Discovery::DEFAULT_RTPS);

      // For appendable extensibility to work we need to make sure rtps_udp is used
      /*
      OpenDDS::DCPS::TransportConfig_rch transport_config =
        TheTransportRegistry->create_config("default_rtps_transport_config");
      OpenDDS::DCPS::TransportInst_rch transport_inst =
        TheTransportRegistry->create_inst("default_rtps_transport", "rtps_udp");
      transport_config->instances_.push_back(transport_inst);
      TheTransportRegistry->global_config(transport_config);
      */

      DDS_Native::DDS::DomainParticipantFactory_var dpf = TheParticipantFactory;
      return TAOX11_CORBA::make_reference<DDSX11::OpenDDS_PROXY::OpenDDS_DomainParticipantFactory_proxy> (dpf);
    }

    DDS_Native::DDS::PublisherListener*
    create_publisher_listener (
      IDL::traits< ::DDS::PublisherListener>::ref_type listener)
    {
      return new DDS_PublisherListener_proxy (listener);
    }

    ::DDS::DomainParticipantQos
    participant_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::DomainParticipantQos>::retn (PARTICIPANT_QOS_DEFAULT);
    }

    ::DDS::TopicQos
    topic_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::TopicQos>::retn (TOPIC_QOS_DEFAULT);
    }

    ::DDS::PublisherQos
    publisher_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::PublisherQos>::retn (PUBLISHER_QOS_DEFAULT);
    }

    ::DDS::SubscriberQos
    subscriber_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::SubscriberQos>::retn (SUBSCRIBER_QOS_DEFAULT);
    }

    ::DDS::DataWriterQos
    datawriter_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::DataWriterQos>::retn (DATAWRITER_QOS_DEFAULT);
    }

    ::DDS::DataReaderQos
    datareader_qos_default ()
    {
      return ::DDSX11::traits< ::DDS::DataReaderQos>::retn (DATAREADER_QOS_DEFAULT);
    }
  }
}
