// -*- C++ -*-
/**
 * @file    dds_topic_description.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_topic_description.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_proxy_entity_manager.h"

namespace DDSX11
{
  DDS_TopicDescription_proxy::DDS_TopicDescription_proxy (
    DDS_Native::DDS::TopicDescription * td)
    : NativeEntityBase_T<DDS_Native::DDS::TopicDescription >(td)
  {
  }

  std::string
  DDS_TopicDescription_proxy::get_type_name ()
  {
    return ::DDSX11::traits< std::string >::retn (
      this->native_entity ()->get_type_name ());
  }

  std::string
  DDS_TopicDescription_proxy::get_name ()
  {
    return ::DDSX11::traits< std::string >::retn (
      this->native_entity ()->get_name ());
  }

  IDL::traits< ::DDS::DomainParticipant >::ref_type
  DDS_TopicDescription_proxy::get_participant ()
  {
    DDSX11_LOG_TRACE ("DDS_TopicDescription_proxy::get_participant");

    return DDS_ProxyEntityManager::get_dp_proxy (
      this->native_entity ()->get_participant ());
  }
}
