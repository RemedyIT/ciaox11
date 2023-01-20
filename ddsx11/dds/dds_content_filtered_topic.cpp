// -*- C++ -*-
/**
 * @file    dds_content_filtered_topic.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds/dds_common.h"
#include "dds/dds_content_filtered_topic.h"
#include "dds/dds_topic.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_proxy_entity_manager.h"

#include "logger/ddsx11_log.h"

namespace DDSX11
{
  DDS_ContentFilteredTopic_proxy::DDS_ContentFilteredTopic_proxy (
    DDS_Native::DDS::ContentFilteredTopic * cft)
    : NativeEntityBase_T<DDS_Native::DDS::ContentFilteredTopic>(cft)
  {
  }

  std::string
  DDS_ContentFilteredTopic_proxy::get_filter_expression ()
  {
    DDSX11_LOG_TRACE ("DDS_ContentFilteredTopic_proxy::get_filter_expression");
    return ::DDSX11::traits<std::string>::retn (
      this->native_entity ()->get_filter_expression ());
  }

  ::DDS::ReturnCode_t
  DDS_ContentFilteredTopic_proxy::get_expression_parameters (
    ::DDS::StringSeq & expression_parameters)
  {
    DDSX11_LOG_TRACE ("DDS_ContentFilteredTopic_proxy::get_expression_parameters");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_expression_parameters (
        ::DDSX11::traits< ::DDS::StringSeq, ::DDS_Native::DDS::StringSeq>::inout (expression_parameters)));
  }

  ::DDS::ReturnCode_t
  DDS_ContentFilteredTopic_proxy::set_expression_parameters (
    const ::DDS::StringSeq & expression_parameters)
  {
    DDSX11_LOG_TRACE ("DDS_ContentFilteredTopic_proxy::set_expression_parameters");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_expression_parameters (
        ::DDSX11::traits< ::DDS::StringSeq, ::DDS_Native::DDS::StringSeq>::in (expression_parameters)));
  }

  IDL::traits<::DDS::Topic>::ref_type
  DDS_ContentFilteredTopic_proxy::get_related_topic ()
  {
    DDSX11_LOG_TRACE ("DDS_ContentFilteredTopic_proxy::get_related_topic");

    DDS_Native::DDS::Topic_var topic =
      this->native_entity ()->get_related_topic ();
    return DDS_ProxyEntityManager::get_topic_proxy (topic);
  }

  std::string
  DDS_ContentFilteredTopic_proxy::get_type_name ()
  {
    return ::DDSX11::traits<std::string>::retn (
      this->native_entity ()->get_type_name ());
  }

  std::string
  DDS_ContentFilteredTopic_proxy::get_name ()
  {
    return ::DDSX11::traits<std::string>::retn (
      this->native_entity ()->get_name ());
  }

  IDL::traits<::DDS::DomainParticipant>::ref_type
  DDS_ContentFilteredTopic_proxy::get_participant ()
  {
    DDSX11_LOG_TRACE ("DDS_ContentFilteredTopic_proxy::get_participant");

    DDS_Native::DDS::DomainParticipant_var dp =
      this->native_entity ()->get_participant ();
    return DDS_ProxyEntityManager::get_dp_proxy (dp);
  }
}
