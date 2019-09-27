// -*- C++ -*-
/**
 * @file    dds_topic_listener.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_IMPL_TOPIC_LISTENER_T_H_
#define DDSX11_IMPL_TOPIC_LISTENER_T_H_

#include "dds/dds_export.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_listener_guard_t.h"

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_TopicListener_proxy final
    : public DDS_Native::DDS::TopicListener
  {
  public:
    /// Constructor
    DDS_TopicListener_proxy (
      IDL::traits< ::DDS::TopicListener >::ref_type t);

    /// Destructor
    virtual ~DDS_TopicListener_proxy () = default;

    virtual void
    on_inconsistent_topic (
      DDS_Native::DDS::Topic* the_topic,
      const DDS_Native::DDS::InconsistentTopicStatus& status) override;

    IDL::traits< ::DDS::TopicListener >::ref_type
    get_topic_listener ();

  private:
    IDL::traits< ::DDS::TopicListener >::ref_type impl_;

    DDS_TopicListener_proxy() = delete;
    DDS_TopicListener_proxy(const DDS_TopicListener_proxy&) = delete;
    DDS_TopicListener_proxy(DDS_TopicListener_proxy&&) = delete;
    DDS_TopicListener_proxy& operator=(const DDS_TopicListener_proxy&) = delete;
    DDS_TopicListener_proxy& operator=(DDS_TopicListener_proxy&&) = delete;
  };

  typedef DDSX11_Listener_Guard_T<
    DDS_Native::DDS::TopicListener,
    ::DDS::TopicListener> TopicListener_Guard;
}

#endif /* DDSX11_IMPL_TOPIC_LISTENER_T_H_ */
