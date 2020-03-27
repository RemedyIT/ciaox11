/**
 * @file    dds_vendor_adapter.h
 * @author  Marcel Smit
 *
 * @brief   Generic class which creates the NDDS specific entities.
 *          Entry point for the vendor specific DLL.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_VENDOR_ADAPTER_H_
#define DDSX11_IMPL_VENDOR_ADAPTER_H_

#define DDSX11_INITIALIZE_QOS_DEFAULTS

#include "dds/dds_export.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_traits.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native
{
  namespace DDS
  {
    class Publisher;
    class Subscriber;
    class PublisherListener;
    class DomainParticipant;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  namespace VendorUtils
  {
    DDSX11_IMPL_Export IDL::traits< ::DDS::Publisher>::ref_type
    create_publisher_proxy (
      DDS_Native::DDS::Publisher *p);

    DDSX11_IMPL_Export IDL::traits< ::DDS::Subscriber>::ref_type
    create_subscriber_proxy (
      DDS_Native::DDS::Subscriber *s);

    DDSX11_IMPL_Export IDL::traits< ::DDS::DomainParticipant>::ref_type
    create_domain_participant_proxy (
      DDS_Native::DDS::DomainParticipant *dp);

    DDSX11_IMPL_Export IDL::traits< ::DDS::WaitSet>::ref_type
    create_waitset ();

    DDSX11_IMPL_Export IDL::traits< ::DDS::DomainParticipantFactory>::ref_type
    init_dds ();

    /** @name Create DDS Listeners. */
    //@{
    DDS_Native::DDS::PublisherListener*
    create_publisher_listener (
      IDL::traits< ::DDS::PublisherListener>::ref_type listener);
    //@}

    /** @name Create DDS entities with profile. */
    //@{
    IDL::traits< ::DDS::DomainParticipant>::ref_type
    create_participant_with_profile (
      IDL::traits< ::DDS::DomainParticipantFactory>::ref_type participant_factory,
      ::DDS::DomainId_t domain_id,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DomainParticipantListener>::ref_type listener,
      ::DDS::StatusMask mask);

    IDL::traits< ::DDS::Topic>::ref_type
    create_topic_with_profile (
      IDL::traits< ::DDS::DomainParticipant>::ref_type participant,
      const std::string &topic_name,
      const std::string &type_name,
      const std::string &qos_profile,
      IDL::traits< ::DDS::TopicListener>::ref_type listener,
      ::DDS::StatusMask mask);

    IDL::traits< ::DDS::Publisher>::ref_type
    create_publisher_with_profile (
      IDL::traits< ::DDS::DomainParticipant>::ref_type participant,
      const std::string &profile,
      IDL::traits< ::DDS::PublisherListener>::ref_type listener,
      ::DDS::StatusMask mask);

    IDL::traits< ::DDS::Subscriber>::ref_type
    create_subscriber_with_profile (
      IDL::traits< ::DDS::DomainParticipant>::ref_type participant,
      const std::string &profile,
      IDL::traits< ::DDS::SubscriberListener>::ref_type listener,
      ::DDS::StatusMask mask);

    IDL::traits< ::DDS::DataWriter>::ref_type
    create_datawriter_with_profile (
      IDL::traits< ::DDS::Publisher>::ref_type publisher,
      IDL::traits< ::DDS::Topic>::ref_type topic,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DataWriterListener>::ref_type listener,
      ::DDS::StatusMask mask);

    IDL::traits< ::DDS::DataReader>::ref_type
    create_datareader_with_profile (
      IDL::traits< ::DDS::Subscriber>::ref_type subscriber,
      IDL::traits< ::DDS::TopicDescription>::ref_type topic,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DataReaderListener>::ref_type listener,
      ::DDS::StatusMask mask);
    //@}

    /** @name Default QOSs. */
    //@{
    DDSX11_IMPL_Export ::DDS::DomainParticipantQos participant_qos_default ();
    DDSX11_IMPL_Export ::DDS::TopicQos topic_qos_default ();
    DDSX11_IMPL_Export ::DDS::PublisherQos publisher_qos_default ();
    DDSX11_IMPL_Export ::DDS::SubscriberQos subscriber_qos_default ();
    DDSX11_IMPL_Export ::DDS::DataWriterQos datawriter_qos_default ();
    DDSX11_IMPL_Export ::DDS::DataReaderQos datareader_qos_default ();
    //@}
  } // namespace VendorUtils
} // namespace DDSX11

// @todo Move this part below to its own file
namespace DDS
{
  // Declare the default QoS
  const DomainParticipantQos PARTICIPANT_QOS_DEFAULT { DDSX11::VendorUtils::participant_qos_default () };
  const TopicQos TOPIC_QOS_DEFAULT { DDSX11::VendorUtils::topic_qos_default () };
  const PublisherQos PUBLISHER_QOS_DEFAULT { DDSX11::VendorUtils::publisher_qos_default () };
  const SubscriberQos SUBSCRIBER_QOS_DEFAULT { DDSX11::VendorUtils::subscriber_qos_default () };
  const DataWriterQos DATAWRITER_QOS_DEFAULT { DDSX11::VendorUtils::datawriter_qos_default () };
  const DataReaderQos DATAREADER_QOS_DEFAULT { DDSX11::VendorUtils::datareader_qos_default () };

  template<>
  struct traits< ::DDS::DomainParticipantFactory>
  {
    static IDL::traits< ::DDS::DomainParticipantFactory>::ref_type
    get_instance ()
    {
      // See C++ specification section 6.7 [stmt.dcl] p4
      static IDL::traits< ::DDS::DomainParticipantFactory>::ref_type dpf =
        ::DDSX11::VendorUtils::init_dds ();
      return dpf;
    }
  };
}

#endif /* DDSX11_IMPL_VENDOR_ADAPTER_H_ */
