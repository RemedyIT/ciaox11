// -*- C++ -*-
/**
 * @file    dds_domain_participant_factory.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_domain_participant_factory.h"
#include "dds/dds_domain_participant.h"
#include "dds/dds_domain_participant_listener.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "dds/dds_vendor_adapter.h"

#include "logger/ddsx11_log.h"
#include "dds/dds_proxy_entity_manager.h"

namespace DDSX11
{
  DDS_DomainParticipantFactory_proxy::DDS_DomainParticipantFactory_proxy (
      DDS_Native::DDS::DomainParticipantFactory * dpf)
    : NativeEntityBase_T<DDS_Native::DDS::DomainParticipantFactory>(dpf)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantFactory_proxy::DDS_DomainParticipantFactory_proxy");
  }

  IDL::traits< ::DDS::DomainParticipant>::ref_type
  DDS_DomainParticipantFactory_proxy::create_participant (
    ::DDS::DomainId_t domain_id,
    const ::DDS::DomainParticipantQos & qos,
    IDL::traits< ::DDS::DomainParticipantListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantFactory_proxy::create_participant");

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::create_participant - "
      << "Start creating domain participant for domain <" << domain_id << ">");

    ::DDSX11::traits< ::DDS::DomainParticipantQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_participant_qos (qos_in.value_));

    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::create_participant - "
          << "Error: Unable to retrieve default participant QoS <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return {};
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::create_participant - "
      << "Using DomainParticipantQos <"
      << IDL::traits< ::DDS::DomainParticipantQos>::write (::DDSX11::traits< ::DDS::DomainParticipantQos>::retn (qos_in))
      << ">");

    // Use a guard which will make sure we destroy it the listener when we fail
    DomainParticipantListener_Guard listener_guard {};
    if (a_listener)
      {
        listener_guard = new (std::nothrow) DDS_DomainParticipantListener_proxy(a_listener);
        if (!listener_guard)
        {
          return {};
        }
      }

    DDS_Native::DDS::DomainParticipant_var dds_dp =
      this->native_entity ()->create_participant (
        domain_id,
        qos_in,
        listener_guard.get (),
        ::DDSX11::traits< ::DDS::StatusMask>::in (mask));

    if (!dds_dp)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::create_participant - "
          << "Error: Unable to create DomainParticipant for domain <"
          << domain_id << ">");
        // Listener will be destroyed here since the guard goes out of scope.
        return {};
      }

    // DDS was able to create a native entity. We can now safely release the
    // listener otherwise it would be deleted when the unique pointer goes out
    // of scope.
    listener_guard.release ();

    IDL::traits< ::DDS::DomainParticipant>::ref_type domain_participant =
      VendorUtils::create_domain_participant_proxy (dds_dp);

    if (domain_participant)
      {
        if (DDS_ProxyEntityManager::register_dp_proxy (domain_participant, dds_dp))
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::create_participant - "
              << "Successfully created and registered a DomainParticipant for domain <"
              << domain_id << ">");
          }
        else
          {
            domain_participant = nullptr;

            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::create_participant - "
              << "ERROR: Failed to register a domain participant proxy.");
          }
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::create_participant - "
          << "Error: Unable to create a DomainParticipant for domain <"
          << domain_id << ">");
      }

    return domain_participant;
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipantFactory_proxy::delete_participant (
    IDL::traits< ::DDS::DomainParticipant>::ref_type a_participant)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantFactory_proxy::delete_participant");

    IDL::traits< ::DDSX11::DDS_DomainParticipant_proxy>::ref_type proxy =
      domain_participant_trait::proxy (a_participant);
    if (!proxy)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::delete_participant - "
          << "Unable to retrieve the proxy from the provided object reference.");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }

    DDS_Native::DDS::DomainParticipant *part = proxy->get_native_entity ();
    if (!part)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::delete_participant - "
          << "Unable to retrieve the native domainparticipant from the provided object reference.");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::delete_participant - "
      << "Successfully retrieved the native entity from the provided domainparticipant");

    // Retrieve the DDS instance handle before deleting it, we need it when
    // unregistering our proxy
    ::DDS::InstanceHandle_t const handle = a_participant->get_instance_handle ();

    // Retrieve our listener so that we can delete it when the delete of the DDS entity
    // has been successful
    DomainParticipantListener_Guard listener_guard { part->get_listener () };

    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->delete_participant (part));

    if (retcode != ::DDS::RETCODE_OK)
      {
        // The delete failed so release the listener guard so that we don't delete
        // the listener
        listener_guard.release ();

        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::delete_participant - "
          << "delete_participant returned non-ok error <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
      }
    else
      {
        if (!DDS_ProxyEntityManager::unregister_dp_proxy (part, handle))
          {
            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_participant - "
              << "Error: Can't unregister domainparticpant proxy for <" << handle << ">");
            return ::DDS::RETCODE_ERROR;
          }
        proxy->clear_native_entity ();

        DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::delete_participant - "
          "Successfully deleted provided participant.");
      }
    return retcode;
  }


  IDL::traits< ::DDS::DomainParticipant>::ref_type
  DDS_DomainParticipantFactory_proxy::lookup_participant (
    ::DDS::DomainId_t domain_id)
  {
    IDL::traits< ::DDS::DomainParticipant>::ref_type retval;
    DDS_Native::DDS::DomainParticipant_var dp =
      this->native_entity ()->lookup_participant (domain_id);

    if (dp)
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::lookup_participant - "
          "Found native domain participant for domain <" << domain_id << ">");

        // Check if we already have a dp proxy in the proxy entity
        // manager, if so, return that one
        retval = DDS_ProxyEntityManager::get_dp_proxy (dp);
        if (!retval)
          {
            // No proxy found, as we get a previously created domain participant we
            // have an error now
            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::lookup_participant - "
               "Failed to get a domain participant proxy for domain <" << domain_id << ">");
          }
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::lookup_participant - "
          "No native domain participant for domain <" << domain_id << ">");
      }
    return retval;
  }

  ::DDS::ReturnCode_t
  DDS_DomainParticipantFactory_proxy::set_default_participant_qos (
    const ::DDS::DomainParticipantQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantFactory_proxy::set_default_participant_qos");

    ::DDSX11::traits< ::DDS::DomainParticipantQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_participant_qos (qos_in.value_));

    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipantFactory_proxy::set_default_participant_qos - "
          << "Error: Unable to retrieve default participant QoS <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::set_default_participant_qos - "
      << "Setting DomainParticipantQos <"
      << IDL::traits< ::DDS::DomainParticipantQos>::write (::DDSX11::traits< ::DDS::DomainParticipantQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_default_participant_qos (qos_in));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipantFactory_proxy::get_default_participant_qos (
    ::DDS::DomainParticipantQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantFactory_proxy::get_default_participant_qos");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_participant_qos (
        ::DDSX11::traits< ::DDS::DomainParticipantQos>::inout (qos)));
  }

  ::DDS::ReturnCode_t
  DDS_DomainParticipantFactory_proxy::set_qos (
    const ::DDS::DomainParticipantFactoryQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantFactory_proxy::set_qos");

    ::DDSX11::traits< ::DDS::DomainParticipantFactoryQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::set_qos - "
          << "Error: Unable to retrieve domain participant factory QoS <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipantFactory_proxy::set_qos - "
      << "Setting DomainParticipantQos <"
      << IDL::traits< ::DDS::DomainParticipantFactoryQos>::write (::DDSX11::traits< ::DDS::DomainParticipantFactoryQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_qos (qos_in));
  }

  ::DDS::ReturnCode_t
  DDS_DomainParticipantFactory_proxy::get_qos (
    ::DDS::DomainParticipantFactoryQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipantFactory_proxy::get_qos");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_qos (::DDSX11::traits< ::DDS::DomainParticipantFactoryQos>::inout (qos)));
  }
}
