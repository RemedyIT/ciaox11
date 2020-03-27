// -*- C++ -*-
/**
 * @file    dds_topic_listener.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_topic_listener.h"
#include "dds/dds_topic.h"
#include "dds/dds_proxy_entity_manager.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  DDS_TopicListener_proxy::DDS_TopicListener_proxy (
    IDL::traits< ::DDS::TopicListener>::ref_type t)
    : impl_ (std::move (t))
  {
  }

  void
  DDS_TopicListener_proxy::on_inconsistent_topic (
    DDS_Native::DDS::Topic* the_topic,
    const DDS_Native::DDS::InconsistentTopicStatus & status)
  {
    DDSX11_LOG_TRACE ("DDS_TopicListener_proxy::on_inconsistent_topic");

    IDL::traits< ::DDS::Topic>::ref_type tp =
      DDS_ProxyEntityManager::get_topic_proxy (the_topic);
    if (tp)
    {
      this->impl_->on_inconsistent_topic (std::move(tp),
        ::DDSX11::traits< ::DDS::InconsistentTopicStatus>::retn (status));
    }
  }

  IDL::traits< ::DDS::TopicListener>::ref_type
  DDS_TopicListener_proxy::get_topic_listener ()
  {
    return this->impl_;
  }
}

