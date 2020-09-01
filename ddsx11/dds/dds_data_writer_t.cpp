// -*- C++ -*-
/**
 * @file    dds_data_writer_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_proxy_entity_manager.h"
#include "dds/dds_status_condition.h"
#include "dds/dds_publisher.h"
#include "dds/dds_data_writer_listener.h"
#include "dds/dds_topic.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_traits.h"

#include "logger/ddsx11_log.h"

// DDS vendor specific implementation part
#include "dds/dds_data_writer_native_entity_t.cpp"

namespace DDSX11
{
  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::set_qos (
    const ::DDS::DataWriterQos & qos)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::set_qos");

    ::DDSX11::traits< ::DDS::DataWriterQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::set_qos - Error: Unable to retrieve QoS <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::set_qos - Setting DataWriterQos <"
      << IDL::traits< ::DDS::DataWriterQos>::write (::DDSX11::traits< ::DDS::DataWriterQos>::retn(qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_qos (qos_in));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_qos (
    ::DDS::DataWriterQos & qos)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()-> get_qos (
        ::DDSX11::traits< ::DDS::DataWriterQos>::inout (qos)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::set_listener (
    IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::set_listener");

    // Retrieve the previously set listener, the guard will make sure we destroy it when we succeed
    // in setting a listener
    DataWriterListener_Guard old_guard { this->native_entity ()->get_listener () };
    DataWriterListener_Guard new_guard {};
    if (a_listener)
      {
        new_guard = new DDS_DataWriterListener_proxy (a_listener);
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

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  IDL::traits< ::DDS::DataWriterListener>::ref_type
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_listener ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_listener");

    DDS_Native::DDS::DataWriterListener_var native_listener =
      this->native_entity ()->get_listener ();

    if (!native_listener)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::get_listener - DDS returned a null listener");
        return {};
      }

    native_datawriterlistener_trait::proxy_impl_type * proxy_impl =
       native_datawriterlistener_trait::proxy_impl (native_listener);

    if (!proxy_impl)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::get_listener - listener returned by DDS is not a DDSX11 listener");
        return {};
      }
    return proxy_impl->get_datawriterlistener ();
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  IDL::traits< ::DDS::Topic>::ref_type
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_topic ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_topic");

    DDS_Native::DDS::Topic_var topic =
      this->native_entity ()->get_topic ();

    return DDS_ProxyEntityManager::get_topic_proxy (topic);
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  IDL::traits< ::DDS::Publisher>::ref_type
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_publisher ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_publisher");

    DDS_Native::DDS::Publisher_var publisher =
      this->native_entity ()->get_publisher ();

    return DDS_ProxyEntityManager::get_publisher_proxy (publisher);
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::wait_for_acknowledgments (
    const ::DDS::Duration_t & max_wait)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::wait_for_acknowledgments");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->wait_for_acknowledgments (
        ::DDSX11::traits< ::DDS::Duration_t>::in (max_wait)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_liveliness_lost_status (
    ::DDS::LivelinessLostStatus & status)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_liveliness_lost_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_liveliness_lost_status (
        ::DDSX11::traits< ::DDS::LivelinessLostStatus>::inout (status)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_offered_deadline_missed_status (
    ::DDS::OfferedDeadlineMissedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_offered_deadline_missed_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_offered_deadline_missed_status (
        ::DDSX11::traits< ::DDS::OfferedDeadlineMissedStatus>::inout (status)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_offered_incompatible_qos_status (
    ::DDS::OfferedIncompatibleQosStatus & status)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_offered_incompatible_qos_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_offered_incompatible_qos_status (
        ::DDSX11::traits< ::DDS::OfferedIncompatibleQosStatus>::inout (status)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_publication_matched_status (
    ::DDS::PublicationMatchedStatus & status)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_publication_matched_status");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_publication_matched_status (
        ::DDSX11::traits< ::DDS::PublicationMatchedStatus>::inout (status)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::assert_liveliness ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::assert_liveliness");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->assert_liveliness ());
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_matched_subscriptions (
    ::DDS::InstanceHandleSeq & subscription_handles)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_matched_subscription");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_matched_subscriptions (
        ::DDSX11::traits< ::DDS::InstanceHandleSeq,  ::DDS_Native::DDS::InstanceHandleSeq>::inout (subscription_handles)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_matched_subscription_data (
    ::DDS::SubscriptionBuiltinTopicData & subscription_data,
    const ::DDS::InstanceHandle_t& subscription_handle)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_matched_subscription_data");

#if defined DDSX11_HAS_MINIMUM_BIT
    X11_UNUSED_ARG(subscription_data);
    X11_UNUSED_ARG(subscription_handle);
    return ::DDS::RETCODE_UNSUPPORTED;
#else
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_matched_subscription_data (
        ::DDSX11::traits< ::DDS::SubscriptionBuiltinTopicData>::inout (subscription_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (subscription_handle)));
#endif
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::enable ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::enable");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->enable ());
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  IDL::traits< ::DDS::StatusCondition>::ref_type
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_statuscondition ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_statuscondition");

    IDL::traits< ::DDS::StatusCondition>::ref_type retval;
    DDS_Native::DDS::StatusCondition_var sc = this->native_entity ()->get_statuscondition ();
    if (sc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_StatusCondition_proxy>(sc);
      }
    return retval;
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::StatusMask
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_status_changes ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_status_changes");

    return ::DDSX11::traits< ::DDS::StatusMask>::retn (
      this->native_entity ()->get_status_changes ());
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::InstanceHandle_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_instance_handle ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_instance_handle");

    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->get_instance_handle ());
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::InstanceHandle_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::register_instance (
    const TOPIC_TYPE &instance_data)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::register_instance");

    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->register_instance (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::InstanceHandle_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::register_instance_w_timestamp (
    const TOPIC_TYPE &instance_data,
    const ::DDS::Time_t & source_timestamp)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::register_instance_w_timestamp");

    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->register_instance_w_timestamp (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data),
        ::DDSX11::traits< ::DDS::Time_t>::in (source_timestamp)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::unregister_instance (
    const TOPIC_TYPE & instance_data,
    const ::DDS::InstanceHandle_t& handle)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::unregister_instance");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->unregister_instance (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::unregister_instance_w_timestamp (
    const TOPIC_TYPE & instance_data,
    const ::DDS::InstanceHandle_t& handle,
    const ::DDS::Time_t & source_timestamp)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::unregister_instance_w_timestamp");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->unregister_instance_w_timestamp (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle),
        ::DDSX11::traits< ::DDS::Time_t>::in (source_timestamp)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::write (
    const TOPIC_TYPE &instance_data,
    const ::DDS::InstanceHandle_t& handle)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::write");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->write (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::write_w_timestamp (
    const TOPIC_TYPE & instance_data,
    const ::DDS::InstanceHandle_t& handle,
    const ::DDS::Time_t & source_timestamp)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::write_w_timestamp");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->write_w_timestamp (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle),
        ::DDSX11::traits< ::DDS::Time_t>::in (source_timestamp)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::dispose (
    const TOPIC_TYPE & instance_data,
    const ::DDS::InstanceHandle_t& handle)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::dispose");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->dispose (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::dispose_w_timestamp (
    const TOPIC_TYPE & instance_data,
    const ::DDS::InstanceHandle_t& handle,
    const ::DDS::Time_t & source_timestamp)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::dispose_w_timestamp");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->dispose_w_timestamp (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle),
        ::DDSX11::traits< ::DDS::Time_t>::in (source_timestamp)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::ReturnCode_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_key_value (
    TOPIC_TYPE & key_holder,
    const ::DDS::InstanceHandle_t& handle)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_key_value");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_key_value (
        typename ::DDSX11::traits<TOPIC_TYPE>::inout (key_holder),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  ::DDS::InstanceHandle_t
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::lookup_instance (
    const TOPIC_TYPE & instance_data)
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::lookup_instance");

    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->lookup_instance (
        typename ::DDSX11::traits<TOPIC_TYPE>::in (instance_data)));
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  NATIVE_TYPED_WRITER *
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::native_entity ()
  {
    if (!this->native_entity_)
      {
        DDSX11_IMPL_LOG_DEBUG ("DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::native_entity Throwing BAD_INV_ORDER.");
        throw TAOX11_CORBA::BAD_INV_ORDER ();
      }
    return this->native_entity_;
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  DDS_Native::DDS::DataWriter *
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::get_native_entity ()
  {
    return this->native_entity_;
  }
}
