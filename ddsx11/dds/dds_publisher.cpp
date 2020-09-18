// -*- C++ -*-
/**
 * @file    dds_publisher.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_publisher.h"
#include "dds/dds_publisher_listener.h"
#include "dds/dds_domain_participant.h"
#include "dds/dds_topic.h"
#include "dds/dds_data_writer_t.h"
#include "dds/dds_status_condition.h"
#include "dds/dds_data_writer_listener.h"
#include "dds/dds_type_support.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_vendor_adapter.h"

#include "logger/ddsx11_log.h"

namespace DDSX11
{
  DDS_Publisher_proxy::DDS_Publisher_proxy (
    DDS_Native::DDS::Publisher * p)
    : NativeEntityBase_T<DDS_Native::DDS::Publisher> (p)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::DDS_Publisher_proxy");
  }

  IDL::traits< ::DDS::DataWriter>::ref_type
  DDS_Publisher_proxy::create_datawriter (
    IDL::traits< ::DDS::Topic>::ref_type a_topic,
    const ::DDS::DataWriterQos &qos,
    IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::create_datawriter");

    ::DDSX11::traits< ::DDS::DataWriterQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_datawriter_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::create_datawriter - "
          << "Error: Unable to retrieve default datawriter QoS <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return nullptr;
      }
#endif

    // Use a guard which will make sure we destroy it the listener when we fail
    DataWriterListener_Guard listener_guard {};
    if (a_listener)
      {
        listener_guard = new DDS_DataWriterListener_proxy (a_listener);
      }

    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::create_datawriter - "
      << "Using DataWriterQos <"
      << IDL::traits< ::DDS::DataWriterQos>::write (::DDSX11::traits <::DDS::DataWriterQos>::retn (qos_in))
      << ">");

     DDS_Native::DDS::DataWriter_var native_dw =
      this->native_entity ()->create_datawriter (
        topic_trait::native (a_topic),
        qos_in,
        listener_guard.get (),
        ::DDSX11::traits< ::DDS::StatusMask>::in (mask));

    if (!native_dw)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::create_datawriter - "
          << "Error: create_datawriter returned a null native datawriter.");
        // Listener will be destroyed here since the guard goes out of scope.
        return {};
      }

    // DDSX11 was able to create a DDS11 proxy. We can now safely release the
    // listener otherwise it would be destroyed when the guard goes out
    // of scope.
    listener_guard.release ();

    IDL::traits< ::DDS::DataWriter>::ref_type datawriter =
      DDS_TypeSupport_i::create_datawriter (this->get_participant (),
                                            a_topic->get_type_name (),
                                            native_dw);
    if (datawriter)
    {
      if (DDS_ProxyEntityManager::register_datawriter_proxy (datawriter))
        {
          DDSX11_IMPL_LOG_DEBUG ("DDS_Publisher_proxy::create_datawriter - "
            << "Successfully created and registered a DataWriter");
        }
      else
        {
          datawriter = nullptr;

          DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::create_datawriter - "
            << "ERROR: Failed to register a datawriter proxy.");
        }
    }
    else
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::create_datawriter - "
        << "Error: Unable to create a DataWriter");
    }
    return datawriter;
  }

  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::delete_datawriter (
    IDL::traits< ::DDS::DataWriter>::ref_type a_datawriter)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::delete_datawriter");

    IDL::traits< ::DDSX11::DDS_DataWriter_proxy>::ref_type dw_proxy =
      data_writer_trait::proxy (a_datawriter);
    if (!dw_proxy)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_i::delete_datawriter - "
          << "Unable to retrieve the proxy from the provided datawriter.");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }

    DDS_Native::DDS::DataWriter *native_dw = dw_proxy->get_native_entity ();
    if (!native_dw)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_i::delete_datawriter - "
          << "Unable to retrieve the native entity from the provided "
          << "datawriter.");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }

    DDSX11_IMPL_LOG_DEBUG ("DDS_Publisher_i::delete_datawriter - "
      << "Successfully retrieved the native entity from the provided "
      << "datawriter.");

    // Retrieve the DDS instance handle before deleting it, we need it when
    // unregistering our proxy
    ::DDS::InstanceHandle_t const handle = a_datawriter->get_instance_handle ();

    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->delete_datawriter (native_dw));

    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_i::delete_datawriter - "
          << "Error: Native delete_datawriter returned non-ok error <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
      }
    else
      {
        if (!DDS_ProxyEntityManager::unregister_datawriter_proxy (handle))
          {
            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_datawriter - "
              << "Error: Can't unregister datawriter proxy for <" << handle << ">");
            return ::DDS::RETCODE_ERROR;
          }

        dw_proxy->clear_native_entity ();

        DDSX11_IMPL_LOG_DEBUG ("DDS_Publisher_i::delete_datawriter - "
          << "Provided datawriter successfully deleted");
      }

    return retcode;
  }


  IDL::traits< ::DDS::DataWriter>::ref_type
  DDS_Publisher_proxy::lookup_datawriter (
    const std::string &impl_name)
  {
    DDS_Native::DDS::DataWriter_var native_dw =
      this->native_entity ()->lookup_datawriter (
        ::DDSX11::traits<std::string>::in (impl_name));
    if (!native_dw)
    {
      DDSX11_IMPL_LOG_DEBUG ("DDS_Publisher_proxy::lookup_datawriter - "
        << "DDS returned a null DataWriter.");
      return nullptr;
    }

    return DDS_ProxyEntityManager::get_datawriter_proxy (native_dw);
  }

  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::delete_contained_entities ()
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::delete_contained_entities");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_contained_entities ());
  }

  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::set_qos (const ::DDS::PublisherQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::set_qos");

    ::DDSX11::traits< ::DDS::PublisherQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::set_qos - "
          << "Error: Unable to retrieve publisher QoS <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::set_qos - "
      << "Setting PublisherQos <"
      << IDL::traits< ::DDS::PublisherQos>::write (::DDSX11::traits< ::DDS::PublisherQos>::retn(qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_qos (qos_in));
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::get_qos (
    ::DDS::PublisherQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::get_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()-> get_qos (
        ::DDSX11::traits< ::DDS::PublisherQos>::inout (qos)));
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::set_listener (
    IDL::traits< ::DDS::PublisherListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::set_listener");

    // Retrieve the previously set listener, the guard will make sure we destroy it when we succeed
    // in setting a listener
    PublisherListener_Guard old_guard (this->native_entity ()->get_listener ());
    PublisherListener_Guard new_guard {};
    if (a_listener)
      {
        new_guard = VendorUtils::create_publisher_listener (a_listener);
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


  IDL::traits< ::DDS::PublisherListener>::ref_type
  DDS_Publisher_proxy::get_listener ()
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::get_listener");

    DDS_Native::DDS::PublisherListener_var native_listener =
      this->native_entity ()->get_listener ();

    if (!native_listener)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DDS_Publisher_proxy::get_listener - DDS returned a null listener");
        return {};
      }

    native_publisherlistener_trait::proxy_impl_type * proxy_impl =
       native_publisherlistener_trait::proxy_impl (native_listener);

    if (!proxy_impl)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DDS_Publisher_proxy::get_listener - listener returned by DDS is not a DDSX11 listener");
        return {};
      }
    return proxy_impl->get_publisher_listener ();
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::suspend_publications ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->suspend_publications ());
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::resume_publications ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->resume_publications ());
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::begin_coherent_changes ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->begin_coherent_changes ());
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::end_coherent_changes ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->end_coherent_changes ());
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::wait_for_acknowledgments (
    const ::DDS::Duration_t & max_wait)
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->wait_for_acknowledgments (
        ::DDSX11::traits< ::DDS::Duration_t>::in (max_wait)));
  }


  IDL::traits< ::DDS::DomainParticipant>::ref_type
  DDS_Publisher_proxy::get_participant ()
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::get_participant");

    DDS_Native::DDS::DomainParticipant_var dp =
      this->native_entity ()->get_participant ();

    return DDS_ProxyEntityManager::get_dp_proxy (dp);
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::set_default_datawriter_qos (
    const ::DDS::DataWriterQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::set_default_datawriter_qos");

    ::DDSX11::traits< ::DDS::DataWriterQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_datawriter_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::set_default_datawriter_qos - "
          << "Error: Unable to retrieve default datawriter <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::set_default_datawriter_qos - "
      << "Setting PublisherQos <"
      << IDL::traits< ::DDS::DataWriterQos>::write (::DDSX11::traits< ::DDS::DataWriterQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_default_datawriter_qos (qos_in));
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::get_default_datawriter_qos (
    ::DDS::DataWriterQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::get_default_datawriter_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_datawriter_qos (
        ::DDSX11::traits< ::DDS::DataWriterQos>::inout (qos)));
  }


  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::copy_from_topic_qos (
    ::DDS::DataWriterQos & a_datawriter_qos,
    const ::DDS::TopicQos & a_topic_qos)
  {
    DDSX11_LOG_TRACE ("DDS_Publisher_proxy::copy_from_topic_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->copy_from_topic_qos (
        ::DDSX11::traits< ::DDS::DataWriterQos>::inout (a_datawriter_qos),
        ::DDSX11::traits< ::DDS::TopicQos>::in (a_topic_qos)));
  }

  ::DDS::ReturnCode_t
  DDS_Publisher_proxy::enable ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->enable ());
  }

  IDL::traits< ::DDS::StatusCondition>::ref_type
  DDS_Publisher_proxy::get_statuscondition ()
  {
    IDL::traits< ::DDS::StatusCondition>::ref_type retval;
    DDS_Native::DDS::StatusCondition_var sc = this->native_entity ()->get_statuscondition ();
    if (sc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_StatusCondition_proxy> (sc);
      }
    return retval;
  }

  ::DDS::StatusMask
  DDS_Publisher_proxy::get_status_changes ()
  {
    return ::DDSX11::traits< ::DDS::StatusMask>::retn (
      this->native_entity ()->get_status_changes ());
  }

  ::DDS::InstanceHandle_t
  DDS_Publisher_proxy::get_instance_handle ()
  {
    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->get_instance_handle ());
  }
}

