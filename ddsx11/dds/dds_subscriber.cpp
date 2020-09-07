// -*- C++ -*-
/**
 * @file    dds_subscriber.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_subscriber.h"
#include "dds/dds_topic.h"
#include "dds/dds_content_filtered_topic.h"
#include "dds/dds_data_reader_t.h"
#include "dds/dds_data_reader_listener.h"
#include "dds/dds_status_condition.h"
#include "dds/dds_domain_participant.h"
#include "dds/dds_type_support.h"
#include "dds/dds_subscriber_listener.h"
#include "dds/dds_vendor_conversion_traits.h"

#include "logger/ddsx11_log.h"

namespace DDSX11
{
  DDS_Subscriber_proxy::DDS_Subscriber_proxy (
    DDS_Native::DDS::Subscriber * sub)
    : NativeEntityBase_T<DDS_Native::DDS::Subscriber>(sub)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::DDS_Subscriber_proxy");
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::enable ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->enable ());
  }

  IDL::traits< ::DDS::StatusCondition>::ref_type
  DDS_Subscriber_proxy::get_statuscondition ()
  {
    IDL::traits< ::DDS::StatusCondition>::ref_type retval;
    DDS_Native::DDS::StatusCondition* sc =
      this->native_entity ()->get_statuscondition ();
    if (sc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_StatusCondition_proxy> (sc);
      }
    return retval;
  }

  ::DDS::StatusMask
  DDS_Subscriber_proxy::get_status_changes ()
  {
    return ::DDSX11::traits< ::DDS::StatusMask>::retn (
      this->native_entity ()->get_status_changes ());
  }

  ::DDS::InstanceHandle_t
  DDS_Subscriber_proxy::get_instance_handle ()
  {
    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
        this->native_entity ()->get_instance_handle ());
  }

  DDS_Native::DDS::DataReader *
  DDS_Subscriber_proxy::create_native_datareader (
    IDL::traits< ::DDS::ContentFilteredTopic>::ref_type topic,
    DDS_Native::DDS::DataReaderListener * native_drl,
    ::DDS::StatusMask mask,
    const ::DDS::DataReaderQos & qos)
  {
    ::DDSX11::traits< ::DDS::DataReaderQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_datareader_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::create_native_datareader - "
          << "Error: Unable to retrieve default datareader qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return nullptr;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::create_native_datareader - "
      << "Using DataReaderQos <"
      << IDL::traits< ::DDS::DataReaderQos>::write (::DDSX11::traits< ::DDS::DataReaderQos>::retn (qos_in))
      << ">");

    return
      this->native_entity ()->create_datareader (
        cft_trait::native (topic),
        qos_in,
        native_drl,
        ::DDSX11::traits< ::DDS::StatusMask>::in (mask));
  }

  DDS_Native::DDS::DataReader *
  DDS_Subscriber_proxy::create_native_datareader (
    IDL::traits< ::DDS::Topic>::ref_type topic,
    DDS_Native::DDS::DataReaderListener * native_drl,
    ::DDS::StatusMask mask,
    const ::DDS::DataReaderQos & qos)
  {
    ::DDSX11::traits< ::DDS::DataReaderQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_datareader_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::create_native_datareader - "
          << "Error: Unable to retrieve default datareader qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return nullptr;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::create_native_datareader - "
      << "Using DataReaderQos <"
      << IDL::traits< ::DDS::DataReaderQos>::write (::DDSX11::traits< ::DDS::DataReaderQos>::retn (qos_in))
      << ">");

    return
      this->native_entity ()->create_datareader (
        topic_trait::native (topic),
        qos_in,
        native_drl,
        ::DDSX11::traits< ::DDS::StatusMask>::in (mask));
  }

  IDL::traits< ::DDS::DataReader>::ref_type
  DDS_Subscriber_proxy::create_datareader (
    IDL::traits< ::DDS::TopicDescription>::ref_type a_topic,
    const ::DDS::DataReaderQos & qos,
    IDL::traits< ::DDS::DataReaderListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::create_datareader");

    // Use a guard which will make sure we destroy it the listener when we fail
    DataReaderListener_Guard listener_guard {};
    if (a_listener)
      {
        listener_guard = new DDS_DataReaderListener_proxy (a_listener);
      }

    DDS_Native::DDS::DataReader * native_dr {};

    IDL::traits< ::DDS::Topic>::ref_type dds_tp =
      IDL::traits< ::DDS::Topic>::narrow (a_topic);

    if (!dds_tp)
      {
        IDL::traits< ::DDS::ContentFilteredTopic>::ref_type cftp =
          IDL::traits< ::DDS::ContentFilteredTopic>::narrow (a_topic);
        if (!cftp)
          {
            DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::create_datareader - "
              << "Error: Unable to retrieve a valid ContentFilteredTopic "
              << "from the EntityFactory.");
            // Pointer of the listener will be destroyed here since the guard
            // goes out of scope.
            return {};
          }
        else
          {
            native_dr = this->create_native_datareader (cftp, listener_guard.get (), mask, qos);
          }
      }
    else
      {
         native_dr = this->create_native_datareader (dds_tp, listener_guard.get (), mask, qos);
      }

    if (!native_dr)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::create_datareader - "
          << "Error: create_datareader returned a null datareader");
        return {};
      }

    // DDS was able to create a native entity. We can now safely release the
    // listener otherwise it would be destroyed when the guard goes out
    // of scope.
    listener_guard.release ();

    DDSX11_IMPL_LOG_DEBUG ("DDS_Subscriber_proxy::create_datareader - "
      << "Successfully created native datareader");

    // Create the X11 typed datareader
    IDL::traits< ::DDS::DataReader>::ref_type datareader =
      DDS_TypeSupport_i::create_datareader (
            this->get_participant (),
            a_topic->get_type_name (),
            native_dr);

    if (datareader)
      {
        // Register the fresh created proxy in the proxy entity manager
        if (DDS_ProxyEntityManager::register_datareader_proxy (datareader))
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_Subscriber_proxy::create_datareader - "
              << "Successfully created and registered a datareader.");
          }
        else
          {
            datareader = nullptr;

            DDSX11_IMPL_LOG_ERROR ("DDS_Publisher_proxy::create_datareader - "
              << "ERROR: Failed to register a datareader proxy.");
          }
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::create_datareader - "
          << "ERROR: Failed to create a datareader.");
      }

    return datareader;
  }


  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::delete_datareader (
    IDL::traits< ::DDS::DataReader>::ref_type a_datareader)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::delete_datareader");

    // First set the listener to null, this will delete any existing listener
    // when it has been set
    a_datareader->set_listener (nullptr, 0);

    IDL::traits< ::DDSX11::DDS_DataReader_proxy>::ref_type dr_proxy =
      data_reader_trait::proxy (a_datareader);
    if (!dr_proxy)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_i::delete_datareader - "
          << "Unable to retrieve the proxy from the provided datareader.");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }

    DDS_Native::DDS::DataReader *native_dr =
      dr_proxy->get_native_entity ();
    if (!native_dr)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_i::delete_datareader - "
          << "Unable to retrieve the native entity from the provided datareader");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }

    DDSX11_IMPL_LOG_DEBUG ("DDS_Subscriber_i::delete_datareader - "
      << "Successfully retrieved the native entity from the provided datareader");

    // Retrieve the DDS instance handle before deleting it, we need it when
    // unregistering our proxy
    ::DDS::InstanceHandle_t const handle = a_datareader->get_instance_handle ();

    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_datareader (native_dr));

    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_i::delete_datareader - "
          << "Error: Native delete_datareader returned non-ok error code <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
      }
    else
      {
        DDS_ProxyEntityManager::unregister_datareader_proxy (handle);
        dr_proxy->clear_native_entity ();

        DDSX11_IMPL_LOG_DEBUG ("DDS_Subscriber_i::delete_datareader - "
          << "Provided datareader successfully deleted");
      }

    return retcode;
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::delete_contained_entities ()
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::delete_contained_entities");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_contained_entities ());
  }

  IDL::traits< ::DDS::DataReader>::ref_type
  DDS_Subscriber_proxy::lookup_datareader (
    const std::string &topic_name)
  {
    DDS_Native::DDS::DataReader *native_dr =
      this->native_entity ()->lookup_datareader (
        ::DDSX11::traits<std::string>::in (topic_name));
    if (!native_dr)
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_Subscriber_proxy::lookup_datareader - "
          << "DDS returned a null DataReader");
        return {};
      }

    // Now see if we already have a proxy for the datareader
    IDL::traits< ::DDS::DataReader>::ref_type dr =
      DDS_ProxyEntityManager::get_datareader_proxy (native_dr);

    if (!dr)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::lookup_datareader - "
          << "ProxyEntityManager didn't have a proxy");
      }
    else
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_Subscriber_proxy::lookup_datareader - "
          << "ProxyEntityManager did have a proxy");
      }

    return dr;
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::get_datareaders (
    ::DDS::DataReaderSeq & readers,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::get_datareaders");
    DDS_Native::DDS::DataReaderSeq native_readers;

    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_datareaders (
          native_readers,
          ::DDSX11::traits< ::DDS::SampleStateMask>::in (sample_states),
          ::DDSX11::traits< ::DDS::ViewStateMask>::in (view_states),
          ::DDSX11::traits< ::DDS::InstanceStateMask>::in (instance_states)));

    if (retcode == ::DDS::RETCODE_OK)
      {
        readers.resize (native_readers.length ());
        uint32_t c {};
        for (DDS_Native::DDS::sequence_size_type i {}; i < native_readers.length (); ++i)
          {
            readers [c++] =
              DDS_ProxyEntityManager::get_datareader_proxy (native_readers[i]);
          }
      }
    return retcode;
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::notify_datareaders ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->notify_datareaders ());
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::set_qos (
    const ::DDS::SubscriberQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::set_qos");

    ::DDSX11::traits< ::DDS::SubscriberQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::set_qos - "
          << "Error: Unable to retrieve subscriber qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::set_qos - "
      << "Setting SubscriberQos <"
      << IDL::traits< ::DDS::SubscriberQos>::write (::DDSX11::traits < ::DDS::SubscriberQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_qos (qos_in));
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::get_qos (
    ::DDS::SubscriberQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::get_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()-> get_qos (
        ::DDSX11::traits< ::DDS::SubscriberQos>::inout (qos)));
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::set_listener (
    IDL::traits< ::DDS::SubscriberListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::set_listener");

    // Retrieve the previously set listener, the guard will make sure we destroy it when we succeed
    // in setting a listener
    SubscriberListener_Guard old_guard { this->native_entity ()->get_listener () };
    SubscriberListener_Guard new_guard {};
    if (a_listener)
      {
        new_guard = new DDS_SubscriberListener_proxy (a_listener);
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

  IDL::traits< ::DDS::SubscriberListener>::ref_type
  DDS_Subscriber_proxy::get_listener ()
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::get_listener");

    DDS_SubscriberListener_proxy *list_proxyroxy =
      dynamic_cast <DDS_SubscriberListener_proxy *> (
        this->native_entity ()->get_listener ());
    if (!list_proxyroxy)
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_Subscriber_proxy::get_listener - "
          << "DDS returned a null listener.");
        return {};
      }
    return list_proxyroxy->get_subscriber_listener ();
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::begin_access ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->begin_access ());
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::end_access ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->end_access ());
  }

  IDL::traits< ::DDS::DomainParticipant>::ref_type
  DDS_Subscriber_proxy::get_participant ()
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::get_participant");

    return DDS_ProxyEntityManager::get_dp_proxy (
      this->native_entity ()->get_participant ());
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::set_default_datareader_qos (
    const ::DDS::DataReaderQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::set_default_datareader_qos");

    ::DDSX11::traits< ::DDS::DataReaderQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_datareader_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_Subscriber_proxy::set_default_datareader_qos - "
          << "Error: Unable to retrieve default datareader qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::set_default_datareader_qos - "
      << "Setting DataReaderQos <"
      << IDL::traits< ::DDS::DataReaderQos>::write (::DDSX11::traits < ::DDS::DataReaderQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_default_datareader_qos (qos_in));
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::get_default_datareader_qos (
    ::DDS::DataReaderQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::get_default_datareader_qos");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_datareader_qos (
        ::DDSX11::traits< ::DDS::DataReaderQos>::inout (qos)));
  }

  ::DDS::ReturnCode_t
  DDS_Subscriber_proxy::copy_from_topic_qos (
    ::DDS::DataReaderQos & a_datareader_qos,
    const ::DDS::TopicQos & a_topic_qos)
  {
    DDSX11_LOG_TRACE ("DDS_Subscriber_proxy::copy_from_topic_qos");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->copy_from_topic_qos (
        ::DDSX11::traits< ::DDS::DataReaderQos>::inout (a_datareader_qos),
        ::DDSX11::traits< ::DDS::TopicQos>::in (a_topic_qos)));
  }
}

