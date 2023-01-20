// -*- C++ -*-
/**
 * @file    dds_topic.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_topic.h"
#include "dds/dds_status_condition.h"
#include "dds/dds_topic_listener.h"

#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_proxy_entity_manager.h"

namespace DDSX11
{
  DDS_Topic_proxy::DDS_Topic_proxy (
    DDS_Native::DDS::Topic* topic)
    : NativeEntityBase_T<DDS_Native::DDS::Topic>(topic)
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::DDS_Topic_proxy");
  }

  ::DDS::ReturnCode_t
  DDS_Topic_proxy::set_qos (
    const ::DDS::TopicQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::set_qos");

    ::DDSX11::traits< ::DDS::TopicQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::set_qos - "
          << "Error: Unable to retrieve participant QoS <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_Topic_proxy::set_qos - "
      << "Setting TopicQos <"
      << IDL::traits<::DDS::TopicQos>::write (::DDSX11::traits< ::DDS::TopicQos>::retn(qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_qos (qos_in));
  }

  ::DDS::ReturnCode_t
  DDS_Topic_proxy::get_qos (
    ::DDS::TopicQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_qos");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()-> get_qos (
        ::DDSX11::traits< ::DDS::TopicQos>::inout (qos)));
  }

  ::DDS::ReturnCode_t
  DDS_Topic_proxy::set_listener (
    IDL::traits<::DDS::TopicListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::set_listener");

    // Retrieve the previously set listener, the guard will make sure we destroy it when we succeed
    // in setting a listener
    TopicListener_Guard old_guard { this->native_entity ()->get_listener () };
    TopicListener_Guard new_guard {};
    if (a_listener)
      {
        new_guard = new (std::nothrow) DDS_TopicListener_proxy (a_listener);
        if (!new_guard)
        {
          return ::DDS::RETCODE_ERROR;
        }
      }

    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->set_listener (new_guard.get (),
          ::DDSX11::traits< ::DDS::StatusMask>::in (mask)));

    if (retcode == ::DDS::RETCODE_OK)
      {
        // Release the guard here and 'give' it to DDS otherwise the listener
        // would be destroyed when goes out of scope.
        new_guard.release ();
      }
    else
      {
        // Setting the new listener failed so we have to assume the old
        // listener is still installed so we can't let the guard destroy it
        old_guard.release ();
      }

    return retcode;
  }

  IDL::traits<::DDS::TopicListener>::ref_type
  DDS_Topic_proxy::get_listener ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_listener");

    DDS_Native::DDS::TopicListener_var native_listener =
      this->native_entity ()->get_listener ();

    if (!native_listener)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DDS_Topic_proxy::get_listener - DDS returned a null listener");
        return {};
      }

    native_topiclistener_trait::proxy_impl_type * proxy_impl =
       native_topiclistener_trait::proxy_impl (native_listener);

    if (!proxy_impl)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DDS_Topic_proxy::get_listener - listener returned by DDS is not a DDSX11 listener");
        return {};
      }
    return proxy_impl->get_topic_listener ();
  }

  ::DDS::ReturnCode_t
  DDS_Topic_proxy::get_inconsistent_topic_status (
    ::DDS::InconsistentTopicStatus & a_status)
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_inconsistent_topic_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_inconsistent_topic_status (
        ::DDSX11::traits< ::DDS::InconsistentTopicStatus>::inout (a_status)));
  }

  ::DDS::ReturnCode_t
  DDS_Topic_proxy::enable ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::enable");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->enable ());
  }

  IDL::traits<::DDS::StatusCondition>::ref_type
  DDS_Topic_proxy::get_statuscondition ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_statuscondition");

    IDL::traits<::DDS::StatusCondition>::ref_type retval;
    DDS_Native::DDS::StatusCondition_var sc =
      this->native_entity ()->get_statuscondition ();
    if (sc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_StatusCondition_proxy> (sc);
      }
    return retval;
  }

  ::DDS::StatusMask
  DDS_Topic_proxy::get_status_changes ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_status_changes");

    return ::DDSX11::traits< ::DDS::StatusMask>::retn (
      this->native_entity ()->get_status_changes ());
  }

  ::DDS::InstanceHandle_t
  DDS_Topic_proxy::get_instance_handle ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_instance_handle");

    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
        this->native_entity ()->get_instance_handle ());
  }

  std::string
  DDS_Topic_proxy::get_type_name ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_type_name");

    return ::DDSX11::traits<std::string>::retn (
      this->native_entity ()->get_type_name ());
  }

  std::string
  DDS_Topic_proxy::get_name ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_name");

    return ::DDSX11::traits<std::string>::retn (
      this->native_entity ()->get_name ());
  }

  IDL::traits<::DDS::DomainParticipant>::ref_type
  DDS_Topic_proxy::get_participant ()
  {
    DDSX11_LOG_TRACE ("DDS_Topic_proxy::get_participant");

    DDS_Native::DDS::DomainParticipant_var dp =
      this->native_entity ()->get_participant ();

    return DDS_ProxyEntityManager::get_dp_proxy (dp);
  }
}
