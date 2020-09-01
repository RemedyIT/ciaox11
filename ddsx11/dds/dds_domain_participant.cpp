//// -*- C++ -*-
/**
 * @file    dds_domain_participant.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_domain_participant.h"
#include "dds/dds_subscriber.h"
#include "dds/dds_publisher.h"
#include "dds/dds_topic.h"
#include "dds/dds_topic_description.h"
#include "dds/dds_content_filtered_topic.h"
#include "dds/dds_publisher_listener.h"
#include "dds/dds_subscriber_listener.h"
#include "dds/dds_topic_listener.h"
#include "dds/dds_domain_participant_listener.h"
#include "dds/dds_status_condition.h"
#include "dds/dds_vendor_adapter.h"
#include "dds/dds_vendor_conversion_traits.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_proxy_entity_manager.h"

namespace DDSX11
{
  DDS_DomainParticipant_proxy::DDS_DomainParticipant_proxy (
    DDS_Native::DDS::DomainParticipant * dp)
    : NativeEntityBase_T<DDS_Native::DDS::DomainParticipant> (dp)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::DDS_DomainParticipant_proxy");
  }


  IDL::traits< ::DDS::Publisher>::ref_type
  DDS_DomainParticipant_proxy::create_publisher (
    const ::DDS::PublisherQos & qos,
    IDL::traits< ::DDS::PublisherListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::create_publisher");

    DDSX11_IMPL_LOG_DEBUG ( "DDS_DomainParticipant_proxy::create_publisher - "
      << "Start creating Publisher");

    ::DDSX11::traits< ::DDS::PublisherQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_publisher_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_publisher - "
          << "Error: Unable to retrieve default publisher qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return {};
      }
#endif

    // Use a guard which will make sure we destroy it the listener when we fail
    PublisherListener_Guard listener_guard {};
    if (a_listener)
      {
        listener_guard = VendorUtils::create_publisher_listener(a_listener);
      }

    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_publisher - "
      << "Using PublisherQos <"
      << IDL::traits< ::DDS::PublisherQos>::write (::DDSX11::traits< ::DDS::PublisherQos>::retn(qos_in))
      << ">");

    DDS_Native::DDS::Publisher_var native_pub =
      this->native_entity ()->create_publisher (
        qos_in,
        listener_guard.get (),
        ::DDSX11::traits< ::DDS::StatusMask>::in (mask));

    if (!native_pub)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_publisher - "
          << "Error: Unable to create Publisher.");
        return {};
      }

    // DDS was able to create a native entity. We can now safely release the
    // listener otherwise it would be destroyed when the guard goes out
    // of scope.
    listener_guard.release ();

    IDL::traits< ::DDS::Publisher>::ref_type publisher =
      VendorUtils::create_publisher_proxy (native_pub);

    if (publisher)
      {
        if (DDS_ProxyEntityManager::register_publisher_proxy (publisher))
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_publisher - "
              << "Successfully created and registered a publisher.");
          }
        else
          {
            publisher = nullptr;

            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_publisher - "
              << "ERROR: Failed to register a publisher proxy.");
          }
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_publisher - "
          << "ERROR: Failed to create a Publisher.");
      }
    return publisher;
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::delete_publisher (
    IDL::traits< ::DDS::Publisher>::ref_type p)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::delete_publisher");

    // First set the listener to null, this will delete any existing listener
    // when it has been set
    p->set_listener(nullptr, 0);

    IDL::traits< ::DDSX11::DDS_Publisher_proxy>::ref_type proxy =
      publisher_trait::proxy (p);

    DDS_Native::DDS::Publisher *native_pub = proxy->get_native_entity ();
    if (!native_pub)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_publisher - "
        << "Unable to retrieve the native publisher from the given ref_type.");
      return ::DDS::RETCODE_ERROR;
    }
    DDS_ProxyEntityManager::unregister_publisher_proxy (p);

    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_publisher (native_pub));

    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_publisher - "
          << "Error: delete_publisher returned non-ok error <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
      }
    else
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::delete_publisher - "
          << "Provided publisher successfully deleted.");
      }
    return retcode;
  }


  IDL::traits< ::DDS::Subscriber>::ref_type
  DDS_DomainParticipant_proxy::create_subscriber (
    const ::DDS::SubscriberQos & qos,
    IDL::traits< ::DDS::SubscriberListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::create_subscriber");

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_subscriber - "
      << "Creating Subscriber.");

    ::DDSX11::traits< ::DDS::SubscriberQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_subscriber_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_subscriber - "
          << "Error: Unable to retrieve default subscriber qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return {};
      }
#endif
    qos_in = qos;

    // Use a guard which will make sure we destroy it the listener when we fail
    SubscriberListener_Guard listener_guard {};
    if (a_listener)
      {
        listener_guard = new DDS_SubscriberListener_proxy (a_listener);
      }

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_subscriber - "
      << "Using SubscriberQos <"
      << IDL::traits< ::DDS::SubscriberQos>::write (::DDSX11::traits< ::DDS::SubscriberQos>::retn(qos_in))
      << ">");

    DDS_Native::DDS::Subscriber_var native_sub =
      this->native_entity ()->create_subscriber (
        qos_in,
        listener_guard.get (),
        ::DDSX11::traits< ::DDS::StatusMask>::in (mask));

    if (!native_sub)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_subscriber - "
          << "Error: DDS returned a null subscriber.");
        // Listener will be destroyed here since the guard goes out of scope.
        return {};
      }

    // DDS was able to create a native entity. We can now safely release the
    // listener otherwise it would be deleted when the unique pointer goes out
    // of scope.
    listener_guard.release ();

    IDL::traits< ::DDS::Subscriber>::ref_type subscriber =
      VendorUtils::create_subscriber_proxy (native_sub);

    if (subscriber)
      {
        // Register the fresh created proxy in the proxy entity manager
        if (DDS_ProxyEntityManager::register_subscriber_proxy (subscriber))
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_subscriber - "
              << "Successfully created and registered a subscriber.");
          }
        else
          {
            subscriber = nullptr;

            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_subscriber - "
              << "ERROR: Failed to register a subscriber proxy.");
          }
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_subscriber - "
          << "ERROR: Failed to create a Subscriber.");
      }

    return subscriber;
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::delete_subscriber (
    IDL::traits< ::DDS::Subscriber>::ref_type s)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::delete_subscriber");

    // First set the listener to null, this will delete any existing listener
    // when it has been set
    s->set_listener(nullptr, 0);

    IDL::traits< ::DDSX11::DDS_Subscriber_proxy>::ref_type proxy =
      subscriber_trait::proxy (s);

    DDS_Native::DDS::Subscriber *native_sub = proxy->get_native_entity ();

    if (!native_sub)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_subscriber - "
          << "Unable to retrieve the native subscriber from the given ref_type.");
        return ::DDS::RETCODE_ERROR;
      }
    DDS_ProxyEntityManager::unregister_subscriber_proxy (proxy);

    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_subscriber (native_sub));

    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_subscriber - "
          << "Error: delete_subscriber returned non-ok error <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
      }
    else
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::delete_subscriber - "
          << "Provided subscriber successfully deleted.");
      }
    return retcode;
  }


  IDL::traits< ::DDS::Subscriber>::ref_type
  DDS_DomainParticipant_proxy::get_builtin_subscriber ()
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_builtin_subscriber");

    if (this->builtin_subscriber_)
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::get_builtin_subscriber - "
          << "Returning already created builtin subscriber");
      }
    else
      {
        DDS_Native::DDS::Subscriber_var native_sub =
          this->native_entity ()->get_builtin_subscriber ();

        if (!native_sub)
          {
            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::get_builtin_subscriber - "
              << "Error: DDS returned a null subscriber.");
            return {};
          }

        // Try to retrieve the subscriber proxy from the proxy entity manager
        // The first time the builtin subscriber is returned this will return
        // no proxy, so we have to create one
        this->builtin_subscriber_ =
          DDS_ProxyEntityManager::get_subscriber_proxy (native_sub);

        if (!this->builtin_subscriber_)
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::get_builtin_subscriber - "
              << "ProxyEntityManager didn't have a proxy, creating a new proxy");
            this->builtin_subscriber_ = VendorUtils::create_subscriber_proxy (native_sub);
          }
      }

    return this->builtin_subscriber_;
  }


  IDL::traits< ::DDS::Topic>::ref_type
  DDS_DomainParticipant_proxy::create_topic (
    const std::string &impl_name,
    const std::string &type_name,
    const ::DDS::TopicQos & qos,
    IDL::traits< ::DDS::TopicListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::create_topic");

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_topic - "
      << "Attempting to create topic with name <" << impl_name
      << "> and type <" << type_name << ">");

    ::DDSX11::traits< ::DDS::TopicQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode = ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_topic_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_topic - "
          << "Error: Unable to retrieve default topic qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return {};
      }
#endif

    // Use a guard which will make sure we destroy it the listener when we fail
    TopicListener_Guard listener_guard {};
    if (a_listener)
      {
        listener_guard = new DDS_TopicListener_proxy (a_listener);
      }

    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_topic - "
      << "Using TopicQos <"
      << IDL::traits< ::DDS::TopicQos>::write (::DDSX11::traits< ::DDS::TopicQos>::retn (qos_in))
      << ">");

    DDS_Native::DDS::Topic_var dds_tp =
      this->native_entity ()->create_topic (
        ::DDSX11::traits<std::string>::in (impl_name),
        ::DDSX11::traits<std::string>::in (type_name),
        qos_in,
        listener_guard.get (),
        ::DDSX11::traits< ::DDS::StatusMask>::in (mask));

    if (!dds_tp)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_topic - "
          << "Error: DDS returned a null topic with name <" << impl_name
          << "> and type <" << type_name << ">");
        // Listener will be destroyed here since the unique guard
        // goes out of scope.
        return {};
      }

    // DDS was able to create a native entity. We can now safely release the
    // listener otherwise it would be destroyed when the listener goes out of
    // scope
    listener_guard.release ();

    IDL::traits< ::DDS::Topic>::ref_type topic_reference =
      TAOX11_CORBA::make_reference<DDS_Topic_proxy> (dds_tp);

    if (topic_reference)
      {
        if (DDS_ProxyEntityManager::register_topic_proxy (topic_reference))
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::create_topic - "
              << "Successfully created and registered a Topic.");
          }
        else
          {
            topic_reference = nullptr;

            DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_topic - "
              << "ERROR: Failed to register a topic proxy.");
          }
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::create_topic - "
          << "ERROR: Failed to create a Topic.");
      }

    return topic_reference;
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::delete_topic (
    IDL::traits< ::DDS::Topic>::ref_type a_topic)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::delete_topic");

    // First set the listener to null, this will delete any existing listener
    // when it has been set
    a_topic->set_listener(nullptr, 0);

    DDS_Native::DDS::Topic *top = topic_trait::native (a_topic);
    if (!top)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_topic - "
          << "Unable to retrieve the native topic from the given ref_type.");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }
    DDS_ProxyEntityManager::unregister_topic_proxy (a_topic);

    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->delete_topic (top));

    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::delete_topic - "
          << "Error: delete_topic returned non-ok error code <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
      }
    else
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::delete_topic - "
          << "Provided topic successfully deleted");
      }

    return retcode;
  }


  IDL::traits< ::DDS::Topic>::ref_type
  DDS_DomainParticipant_proxy::find_topic (const std::string &impl_name,
    const ::DDS::Duration_t & timeout)
  {
    return DDS_ProxyEntityManager::get_topic_proxy (
      this->native_entity ()->find_topic (
        ::DDSX11::traits<std::string>::in (impl_name),
        ::DDSX11::traits< ::DDS::Duration_t>::in (timeout)));

  }


  IDL::traits< ::DDS::TopicDescription>::ref_type
  DDS_DomainParticipant_proxy::lookup_topicdescription (const std::string &name)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::lookup_topicdescription");

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::lookup_topicdescription - "
      << "Looking up topic: name <" << name << ">");

    IDL::traits< ::DDS::TopicDescription>::ref_type td;
    DDS_Native::DDS::TopicDescription_var native_td =
      this->native_entity ()->lookup_topicdescription (
        ::DDSX11::traits<std::string>::in (name));
    if (native_td)
      {
        // Check the entity: is it a Topic or a ContentFilteredTopic
        DDS_Native::DDS::Topic_var native_tp =
#if (DDSX11_NDDS==1)
          DDS_Native::DDS::Topic::narrow (native_td);
#else
          DDS_Native::DDS::Topic::_narrow (native_td);
#endif
        if (native_tp)
          {
            td = DDS_ProxyEntityManager::get_topic_proxy (native_tp);
          }
        else
          {
            DDS_Native::DDS::ContentFilteredTopic_var native_cftp =
#if (DDSX11_NDDS==1)
              DDS_Native::DDS::ContentFilteredTopic::narrow (native_td);
#else
              DDS_Native::DDS::ContentFilteredTopic::_narrow (native_td);
#endif
            if (native_cftp)
              {
                td = TAOX11_CORBA::make_reference<DDS_ContentFilteredTopic_proxy> (native_cftp);
              }
          }
      }
    return td;
  }


  IDL::traits< ::DDS::ContentFilteredTopic>::ref_type
  DDS_DomainParticipant_proxy::create_contentfilteredtopic (
    const std::string &name,
    IDL::traits< ::DDS::Topic>::ref_type related_topic,
    const std::string &filter_expression,
    const ::DDS::StringSeq &expression_parameters)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::create_contentfilteredtopic");

    DDS_Native::DDS::Topic *top = topic_trait::native (related_topic);
    if (!top)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_i::create_contentfilteredtopic - "
          "Unable to retrieve proxy for provided topic.\n");
        return {};
      }

    DDS_Native::DDS::ContentFilteredTopic_var native_cftp =
      this->native_entity ()->create_contentfilteredtopic (
        ::DDSX11::traits<std::string>::in (name),
        top,
        ::DDSX11::traits<std::string>::in (filter_expression),
        ::DDSX11::traits< ::DDS::StringSeq, ::DDS_Native::DDS::StringSeq>::in (expression_parameters));
    if (!native_cftp)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_i::create_contentfilteredtopic - "
          "DDS returned a null ContentFilteredTopic for name <"
          << name << "> and filter expression <"
          << filter_expression << ">");
        return {};
      }
    return TAOX11_CORBA::make_reference<DDS_ContentFilteredTopic_proxy>(native_cftp);
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::delete_contentfilteredtopic (
    IDL::traits< ::DDS::ContentFilteredTopic>::ref_type a_contentfilteredtopic)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::delete_contentfilteredtopic");

    DDS_Native::DDS::ContentFilteredTopic* tp =
      cft_trait::native (a_contentfilteredtopic);
    if (!tp)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DDS_DomainParticipant_proxy::delete_contentfilteredtopic - "
          "Unable to retrieve a valid ContentFilteredTopic.\n");
        return ::DDS::RETCODE_BAD_PARAMETER;
      }
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_contentfilteredtopic (tp));
  }


  IDL::traits< ::DDS::MultiTopic>::ref_type
  DDS_DomainParticipant_proxy::create_multitopic (
    const std::string &/*name*/,
    const std::string &/*type_name*/,
    const std::string &/*subscription_expression*/,
    const ::DDS::StringSeq & /*expression_parameters*/)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::create_multitopic");
    //Not implemented in version ndds.4.5b.rev01 of RTI DDS.
    return {};
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::delete_multitopic (
    IDL::traits< ::DDS::MultiTopic>::ref_type /*a_multitopic*/)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::delete_multitopic");
    //Not implemented in version ndds.4.5b.rev01 of RTI DDS.
    return ::DDS::RETCODE_UNSUPPORTED;
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::delete_contained_entities ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->delete_contained_entities ());
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::set_qos (
    const ::DDS::DomainParticipantQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::set_qos");
    ::DDSX11::traits< ::DDS::DomainParticipantQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    // Get the default QOS from DDS
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::set_qos - "
          << "Error: Unable to retrieve participant qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::set_qos - "
      << "Setting DomainParticipantQos <"
      << IDL::traits< ::DDS::DomainParticipantQos>::write (::DDSX11::traits< ::DDS::DomainParticipantQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_qos (qos_in));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_qos (
    ::DDS::DomainParticipantQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_qos");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()-> get_qos (
        ::DDSX11::traits< ::DDS::DomainParticipantQos>::inout (qos)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::set_listener (
    IDL::traits< ::DDS::DomainParticipantListener>::ref_type a_listener,
    ::DDS::StatusMask mask)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::set_listener");

    // Retrieve the previously set listener, the guard will make sure we destroy it when we succeed
    // in setting a listener
    DomainParticipantListener_Guard old_guard (this->native_entity ()->get_listener ());
    DomainParticipantListener_Guard new_guard {};
    if (a_listener)
      {
        new_guard = new DDS_DomainParticipantListener_proxy (a_listener);
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


  IDL::traits< ::DDS::DomainParticipantListener>::ref_type
  DDS_DomainParticipant_proxy::get_listener ()
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_listener");

    DDS_Native::DDS::DomainParticipantListener_var native_listener =
      this->native_entity ()->get_listener ();

    if (!native_listener)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DDS_DomainParticipant_proxy::get_listener - DDS returned a null listener");
        return {};
      }

    native_domainparticipantlistener_trait::proxy_impl_type * proxy_impl =
       native_domainparticipantlistener_trait::proxy_impl (native_listener);

    if (!proxy_impl)
      {
        DDSX11_IMPL_LOG_ERROR (
          "DDS_DomainParticipant_proxy::get_listener - listener returned by DDS is not a DDSX11 listener");
        return {};
      }
    return proxy_impl->get_domainparticipantlistener ();
  }

  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::ignore_participant (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle)
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->ignore_participant (
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::ignore_topic (
    const ::DDS::InstanceHandle_t& handle)
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->ignore_topic (
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::ignore_publication (
    const ::DDS::InstanceHandle_t& handle)
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->ignore_publication (
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::ignore_subscription (
    const ::DDS::InstanceHandle_t& handle)
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->ignore_subscription (
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (handle)));
  }


  ::DDS::DomainId_t
  DDS_DomainParticipant_proxy::get_domain_id ()
  {
    return ::DDSX11::traits< ::DDS::DomainId_t>::retn (
      this->native_entity ()->get_domain_id ());
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::assert_liveliness ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->assert_liveliness ());
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::set_default_publisher_qos (
    const ::DDS::PublisherQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::set_default_publisher_qos");

    ::DDSX11::traits< ::DDS::PublisherQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_publisher_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::set_default_publisher_qos - "
          << "Error: Unable to retrieve default publisher qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::set_default_publisher_qos - "
      << "Setting PublisherQos <"
      << IDL::traits< ::DDS::PublisherQos>::write (::DDSX11::traits< ::DDS::PublisherQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_default_publisher_qos (qos_in));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_default_publisher_qos (
    ::DDS::PublisherQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_default_publisher_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_publisher_qos (
        ::DDSX11::traits< ::DDS::PublisherQos>::inout (qos)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::set_default_subscriber_qos (
    const ::DDS::SubscriberQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::set_default_subscriber_qos");

    ::DDSX11::traits< ::DDS::SubscriberQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_subscriber_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::set_default_subscriber_qos - "
          << "Error: Unable to retrieve default subscriber qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::set_default_subscriber_qos - "
      << "Setting SubscriberQos <"
      << IDL::traits< ::DDS::SubscriberQos>::write (::DDSX11::traits <::DDS::SubscriberQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_default_subscriber_qos (qos_in));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_default_subscriber_qos (
    ::DDS::SubscriberQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_default_subscriber_qos");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_subscriber_qos (
        ::DDSX11::traits< ::DDS::SubscriberQos>::inout (qos)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::set_default_topic_qos (
    const ::DDS::TopicQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::set_default_topic_qos");

    ::DDSX11::traits< ::DDS::TopicQos>::in qos_in;
#if defined(DDSX11_INITIALIZE_QOS_DEFAULTS)
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->get_default_topic_qos (qos_in.value_));
    if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_DomainParticipant_proxy::set_default_topic_qos - "
          << "Error: Unable to retrieve default topic qos <"
          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">");
        return retcode;
      }
#endif
    qos_in = qos;

    DDSX11_IMPL_LOG_DEBUG ("DDS_DomainParticipant_proxy::set_default_topic_qos - "
      << "Setting TopicQos <"
      << IDL::traits< ::DDS::TopicQos>::write (::DDSX11::traits< ::DDS::TopicQos>::retn (qos_in))
      << ">");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->set_default_topic_qos (qos_in));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_default_topic_qos (
    ::DDS::TopicQos & qos)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_default_topic_qos");
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_default_topic_qos (
        ::DDSX11::traits< ::DDS::TopicQos>::inout (qos)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_discovered_participants (
    ::DDS::InstanceHandleSeq & impl_handles)
  {
#if defined DDSX11_HAS_MINIMUM_BIT
    X11_UNUSED_ARG(impl_handles);
    return ::DDS::RETCODE_UNSUPPORTED;
#else
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_discovered_participants (
        ::DDSX11::traits< ::DDS::InstanceHandleSeq, ::DDS_Native::DDS::InstanceHandleSeq>::inout (impl_handles)));
#endif
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_discovered_participant_data (
    ::DDS::ParticipantBuiltinTopicData & impl_data,
    IDL::traits< ::DDS::InstanceHandle_t>::in_type impl_handle)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_discovered_participant_data");

#if defined DDSX11_HAS_MINIMUM_BIT
    X11_UNUSED_ARG(impl_data);
    X11_UNUSED_ARG(impl_handle);
    return ::DDS::RETCODE_UNSUPPORTED;
#else
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_discovered_participant_data (
        ::DDSX11::traits< ::DDS::ParticipantBuiltinTopicData>::inout (impl_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (impl_handle)));
#endif
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_discovered_topics (
    ::DDS::InstanceHandleSeq & impl_handles)
  {
#if defined DDSX11_HAS_MINIMUM_BIT
    X11_UNUSED_ARG(impl_handles);
    return ::DDS::RETCODE_UNSUPPORTED;
#else
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_discovered_topics (
        ::DDSX11::traits< ::DDS::InstanceHandleSeq,  ::DDS_Native::DDS::InstanceHandleSeq>::inout (impl_handles)));
#endif
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_discovered_topic_data (
    ::DDS::TopicBuiltinTopicData & impl_data,
    const ::DDS::InstanceHandle_t& impl_handle)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_discovered_topic_data");

#if defined DDSX11_HAS_MINIMUM_BIT
    X11_UNUSED_ARG(impl_data);
    X11_UNUSED_ARG(impl_handle);
    return ::DDS::RETCODE_UNSUPPORTED;
#else
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_discovered_topic_data (
        ::DDSX11::traits< ::DDS::TopicBuiltinTopicData>::inout (impl_data),
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (impl_handle)));
#endif
  }


  bool
  DDS_DomainParticipant_proxy::contains_entity (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type a_handle)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::contains_entity");

    return ::DDSX11::traits<bool>::retn (
      this->native_entity ()->contains_entity (
        ::DDSX11::traits< ::DDS::InstanceHandle_t>::in (a_handle)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::get_current_time (
    ::DDS::Time_t & current_time)
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_current_time");

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_current_time (
        ::DDSX11::traits< ::DDS::Time_t>::inout (current_time)));
  }


  ::DDS::ReturnCode_t
  DDS_DomainParticipant_proxy::enable ()
  {
    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->enable ());
  }


  IDL::traits< ::DDS::StatusCondition>::ref_type
  DDS_DomainParticipant_proxy::get_statuscondition ()
  {
    DDSX11_LOG_TRACE ("DDS_DomainParticipant_proxy::get_statuscondition");

    IDL::traits< ::DDS::StatusCondition>::ref_type retval;
    DDS_Native::DDS::StatusCondition_var sc =
      this->native_entity ()->get_statuscondition ();
    if (sc)
      {
        retval = TAOX11_CORBA::make_reference<DDS_StatusCondition_proxy> (sc);
      }
    return retval;
  }


  ::DDS::StatusMask
  DDS_DomainParticipant_proxy::get_status_changes ()
  {
    return ::DDSX11::traits< ::DDS::StatusMask>::retn (
      this->native_entity ()->get_status_changes ());
  }


  ::DDS::InstanceHandle_t
  DDS_DomainParticipant_proxy::get_instance_handle ()
  {
    return ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
      this->native_entity ()->get_instance_handle ());
  }
}
