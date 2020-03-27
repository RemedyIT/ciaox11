// -*- C++ -*-
/**
 * @file    dds_topic.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_TOPIC_H_
#define DDSX11_IMPL_TOPIC_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class Topic;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_Topic_proxy final
    : public virtual IDL::traits< ::DDS::Topic>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::Topic>
  {
  public:
    /// Constructor
    DDS_Topic_proxy (DDS_Native::DDS::Topic* topic);

    /// Destructor
    virtual ~DDS_Topic_proxy () = default;

    ::DDS::ReturnCode_t
    set_qos (const ::DDS::TopicQos & qos) override;

    ::DDS::ReturnCode_t
    get_qos (::DDS::TopicQos & qos) override;

    ::DDS::ReturnCode_t
    set_listener (
      IDL::traits< ::DDS::TopicListener>::ref_type a_listener,
      ::DDS::StatusMask mask) override;

    IDL::traits< ::DDS::TopicListener>::ref_type
    get_listener () override;

    ::DDS::ReturnCode_t
    get_inconsistent_topic_status (
      ::DDS::InconsistentTopicStatus & a_status) override;

    ::DDS::ReturnCode_t
    enable () override;

    IDL::traits< ::DDS::StatusCondition>::ref_type
    get_statuscondition () override;

    ::DDS::StatusMask
    get_status_changes () override;

    ::DDS::InstanceHandle_t
    get_instance_handle () override;

    std::string
    get_type_name () override;

    std::string
    get_name () override;

    IDL::traits< ::DDS::DomainParticipant>::ref_type
    get_participant () override;

  private:

    DDS_Topic_proxy() = delete;
    DDS_Topic_proxy(const DDS_Topic_proxy&) = delete;
    DDS_Topic_proxy(DDS_Topic_proxy&&) = delete;
    DDS_Topic_proxy& operator=(const DDS_Topic_proxy&) = delete;
    DDS_Topic_proxy& operator=(DDS_Topic_proxy&&) = delete;
  };

  typedef entity_traits< ::DDS::Topic, DDS_Topic_proxy, DDS_Native::DDS::Topic>
    topic_trait;
}

#endif /* DDSX11_IMPL_TOPIC_H_ */
