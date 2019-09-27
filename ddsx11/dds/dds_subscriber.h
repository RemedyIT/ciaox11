// -*- C++ -*-
/**
 * @file    dds_subscriber.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_IMPL_SUBSCRIBER_H_
#define DDSX11_IMPL_SUBSCRIBER_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

namespace DDSX11
{
#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
  namespace Native {
    namespace DDS {
      class Subscriber;
      class DataReaderListener;
      class DataReader;
    }
  }
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

  class DDSX11_IMPL_Export DDS_Subscriber_proxy
    : public virtual IDL::traits< ::DDS::Subscriber>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::Subscriber>
  {
  public:
    /// Constructor
    DDS_Subscriber_proxy (
      DDS_Native::DDS::Subscriber * sub);

    /// Destructor
    virtual ~DDS_Subscriber_proxy () = default;

    virtual ::DDS::ReturnCode_t
    enable () override;

    virtual IDL::traits< ::DDS::StatusCondition >::ref_type
    get_statuscondition () override;

    virtual ::DDS::StatusMask
    get_status_changes () override;

    virtual ::DDS::InstanceHandle_t
    get_instance_handle () override;

    virtual IDL::traits< ::DDS::DataReader >::ref_type
    create_datareader (
      IDL::traits< ::DDS::TopicDescription >::ref_type a_topic,
      const ::DDS::DataReaderQos & qos,
      IDL::traits< ::DDS::DataReaderListener >::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    virtual ::DDS::ReturnCode_t
    delete_datareader (
      IDL::traits< ::DDS::DataReader >::ref_type a_datareader) override;

    virtual ::DDS::ReturnCode_t
    delete_contained_entities () override;

    virtual IDL::traits< ::DDS::DataReader >::ref_type
    lookup_datareader (const std::string &impl_name) override;

    virtual ::DDS::ReturnCode_t
    get_datareaders (
      ::DDS::DataReaderSeq & readers,
      ::DDS::SampleStateMask sample_states,
      ::DDS::ViewStateMask view_states,
      ::DDS::InstanceStateMask instance_states) override;

    virtual ::DDS::ReturnCode_t
    notify_datareaders () override;

    virtual ::DDS::ReturnCode_t
    set_qos (
      const ::DDS::SubscriberQos & qos) override;

    virtual ::DDS::ReturnCode_t
    get_qos (
      ::DDS::SubscriberQos & qos) override;

    virtual ::DDS::ReturnCode_t
    set_listener (
      IDL::traits< ::DDS::SubscriberListener >::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    virtual IDL::traits< ::DDS::SubscriberListener >::ref_type
    get_listener () override;

    virtual ::DDS::ReturnCode_t
    begin_access () override;

    virtual ::DDS::ReturnCode_t
    end_access () override;

    virtual IDL::traits< ::DDS::DomainParticipant >::ref_type
    get_participant () override;

    virtual ::DDS::ReturnCode_t
    set_default_datareader_qos (
      const ::DDS::DataReaderQos & qos) override;

    virtual ::DDS::ReturnCode_t
    get_default_datareader_qos (
      ::DDS::DataReaderQos & qos) override;

    virtual ::DDS::ReturnCode_t
    copy_from_topic_qos (
      ::DDS::DataReaderQos & a_datareader_qos,
      const ::DDS::TopicQos & a_impl_qos) override;

  private:
    DDS_Native::DDS::DataReader *
    create_datareader (
      IDL::traits< ::DDS::Topic >::ref_type topic,
      DDS_Native::DDS::DataReaderListener * proxy_drl,
      ::DDS::StatusMask mask,
      const ::DDS::DataReaderQos & qos);

    DDS_Native::DDS::DataReader *
    create_datareader (
      IDL::traits< ::DDS::ContentFilteredTopic >::ref_type topic,
      DDS_Native::DDS::DataReaderListener * proxy_drl,
      ::DDS::StatusMask mask,
      const ::DDS::DataReaderQos & qos);

    DDS_Subscriber_proxy() = delete;
    DDS_Subscriber_proxy(const DDS_Subscriber_proxy&) = delete;
    DDS_Subscriber_proxy(DDS_Subscriber_proxy&&) = delete;
    DDS_Subscriber_proxy& operator=(const DDS_Subscriber_proxy&) = delete;
    DDS_Subscriber_proxy& operator=(DDS_Subscriber_proxy&&) = delete;
  };

  typedef entity_traits< ::DDS::Subscriber, DDS_Subscriber_proxy, DDS_Native::DDS::Subscriber >
    subscriber_trait;
}

#endif /* SUBSCRIBER_T_H_ */
