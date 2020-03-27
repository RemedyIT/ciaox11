// -*- C++ -*-
/**
 * @file    dds_proxy_entity_manager.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_proxy_entity_manager.h"

#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  DDS_ProxyEntityManager::DataReaderProxies DDS_ProxyEntityManager::dr_proxies;
  DDS_ProxyEntityManager::DataWriterProxies DDS_ProxyEntityManager::dw_proxies;
  DDS_ProxyEntityManager::SubscriberProxies DDS_ProxyEntityManager::sub_proxies;
  DDS_ProxyEntityManager::PublisherProxies DDS_ProxyEntityManager::pub_proxies;
  DDS_ProxyEntityManager::TopicProxies DDS_ProxyEntityManager::tp_proxies;
  DDS_ProxyEntityManager::DomainParticipantProxies DDS_ProxyEntityManager::dp_proxies;
  std::mutex DDS_ProxyEntityManager::dr_mutex;
  std::mutex DDS_ProxyEntityManager::dw_mutex;
  std::mutex DDS_ProxyEntityManager::pub_mutex;
  std::mutex DDS_ProxyEntityManager::sub_mutex;
  std::mutex DDS_ProxyEntityManager::tp_mutex;
  std::mutex DDS_ProxyEntityManager::dp_mutex;

  template<typename PROXY_TYPE, typename PROXY_MAP>
  void
  DDS_ProxyEntityManager::register_proxy (
    PROXY_TYPE proxy,
    PROXY_MAP &lst)
  {
    std::pair<typename PROXY_MAP::iterator, bool> ret =
      lst.insert (typename PROXY_MAP::value_type (
        proxy->get_instance_handle (), proxy));
    if (!ret.second)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::register_proxy - "
        "Registering proxy <" << proxy->get_instance_handle () << "> failed");
      proxy = nullptr;
    }
    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_proxy - "
      "Registered proxy with handle <" << proxy->get_instance_handle () << ">");
  }

  template<typename PROXY_TYPE, typename PROXY_MAP>
  PROXY_TYPE
  DDS_ProxyEntityManager::get_proxy (
    DDS_Native::DDS::Entity *native_entity,
    PROXY_MAP &lst)
  {
    if (!native_entity)
    {
      DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::get_proxy - "
        << "Got a null entity from DDS.");
      return nullptr;
    }

    PROXY_TYPE proxy {};
    const ::DDS::InstanceHandle_t handle =
      ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
        native_entity->get_instance_handle ());

    typename PROXY_MAP::iterator it = lst.find (handle);
    if (it != lst.end ())
    {
      proxy = it->second;
    }
    else
    {
      DDSX11_IMPL_LOG_INFO ("DDS_ProxyEntityManager::get_proxy - "
        << "Could not find a proxy with handle <" << handle
        << ">");
    }
    return proxy;
  }

  template<typename PROXY_TYPE, typename PROXY_MAP>
  void
  DDS_ProxyEntityManager::unregister_proxy (
    PROXY_TYPE proxy,
    PROXY_MAP &lst)
  {
    const ::DDS::InstanceHandle_t handle = proxy->get_instance_handle ();
    typename PROXY_MAP::iterator it = lst.find (handle);
    if (it != lst.end ())
    {
      lst.erase (it);
      proxy = nullptr;
      DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_proxy - "
        << "Removed proxy with handle <" << handle
        << "> from the list");
    }
    else
    {
      DDSX11_IMPL_LOG_INFO ("DDS_ProxyEntityManager::unregister_proxy - "
        << "Could not find a proxy with handle <" << handle
        << ">. Nothing to do");
    }
  }

  void
  DDS_ProxyEntityManager::register_datareader_proxy (
    ::IDL::traits< ::DDS::DataReader>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dr_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_datareader_proxy - "
      "Registered proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::DataReader>::ref_type,
      DDS_ProxyEntityManager::DataReaderProxies>
        (proxy, DDS_ProxyEntityManager::dr_proxies);
  }

  void
  DDS_ProxyEntityManager::register_datawriter_proxy (
    ::IDL::traits< ::DDS::DataWriter>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dw_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_datawriter_proxy - "
      "Registered proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::DataWriter>::ref_type,
      DDS_ProxyEntityManager::DataWriterProxies>
        (proxy, DDS_ProxyEntityManager::dw_proxies);
  }

  void
  DDS_ProxyEntityManager::register_subscriber_proxy (
    ::IDL::traits< ::DDS::Subscriber>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::sub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_subscriber_proxy - "
      "Registered proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::Subscriber>::ref_type,
      DDS_ProxyEntityManager::SubscriberProxies>
        (proxy, DDS_ProxyEntityManager::sub_proxies);
  }

  void
  DDS_ProxyEntityManager::register_publisher_proxy (
    ::IDL::traits< ::DDS::Publisher>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::pub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_publisher_proxy - "
      "Registered proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::Publisher>::ref_type,
      DDS_ProxyEntityManager::PublisherProxies>
        (proxy, DDS_ProxyEntityManager::pub_proxies);
  }

  void
  DDS_ProxyEntityManager::register_topic_proxy (
    ::IDL::traits< ::DDS::Topic>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::tp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_topic_proxy - "
      "Registered proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::Topic>::ref_type,
      DDS_ProxyEntityManager::TopicProxies>
        (proxy, DDS_ProxyEntityManager::tp_proxies);
  }

  void
  DDS_ProxyEntityManager::register_dp_proxy (
    ::IDL::traits< ::DDS::DomainParticipant>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_dp_proxy - "
      "Registered proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::DomainParticipant>::ref_type,
      DDS_ProxyEntityManager::DomainParticipantProxies>
        (proxy, DDS_ProxyEntityManager::dp_proxies);
  }

  void
  DDS_ProxyEntityManager::unregister_datareader_proxy (
    ::IDL::traits< ::DDS::DataReader>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dr_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_datareader_proxy - "
      "Unregistered proxy with handle <" << proxy->get_instance_handle () << ">");

    DDS_ProxyEntityManager::unregister_proxy<
      ::IDL::traits< ::DDS::DataReader>::ref_type,
      DDS_ProxyEntityManager::DataReaderProxies>
        (proxy, DDS_ProxyEntityManager::dr_proxies);
  }

  void
  DDS_ProxyEntityManager::unregister_datawriter_proxy (
    ::IDL::traits< ::DDS::DataWriter>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dw_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_datawriter_proxy - "
      "Unregistered proxy with handle <" << proxy->get_instance_handle () << ">");

    DDS_ProxyEntityManager::unregister_proxy<
      ::IDL::traits< ::DDS::DataWriter>::ref_type,
      DDS_ProxyEntityManager::DataWriterProxies>
        (proxy, DDS_ProxyEntityManager::dw_proxies);
  }

  void
  DDS_ProxyEntityManager::unregister_subscriber_proxy (
    ::IDL::traits< ::DDS::Subscriber>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::sub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_subscriber_proxy - "
      "Unregistered proxy with handle <" << proxy->get_instance_handle () << ">");

    DDS_ProxyEntityManager::unregister_proxy<
      ::IDL::traits< ::DDS::Subscriber>::ref_type,
      DDS_ProxyEntityManager::SubscriberProxies>
        (proxy, DDS_ProxyEntityManager::sub_proxies);
  }

  void
  DDS_ProxyEntityManager::unregister_publisher_proxy (
    ::IDL::traits< ::DDS::Publisher>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::pub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_publisher_proxy - "
      "Unregistered proxy with handle <" << proxy->get_instance_handle () << ">");

    DDS_ProxyEntityManager::unregister_proxy<
      ::IDL::traits< ::DDS::Publisher>::ref_type,
      DDS_ProxyEntityManager::PublisherProxies>
        (proxy, DDS_ProxyEntityManager::pub_proxies);
  }

  void
  DDS_ProxyEntityManager::unregister_topic_proxy (
    ::IDL::traits< ::DDS::Topic>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::tp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_topic_proxy - "
      "Unregistered proxy with handle <" << proxy->get_instance_handle () << ">");

    DDS_ProxyEntityManager::unregister_proxy<
      ::IDL::traits< ::DDS::Topic>::ref_type,
      DDS_ProxyEntityManager::TopicProxies>
        (proxy, DDS_ProxyEntityManager::tp_proxies);
  }

  void
  DDS_ProxyEntityManager::unregister_dp_proxy (
    ::IDL::traits< ::DDS::DomainParticipant>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_dp_proxy - "
      "Unregistered proxy with handle <" << proxy->get_instance_handle () << ">");

    DDS_ProxyEntityManager::unregister_proxy<
      ::IDL::traits< ::DDS::DomainParticipant>::ref_type,
      DDS_ProxyEntityManager::DomainParticipantProxies>
        (proxy, DDS_ProxyEntityManager::dp_proxies);
  }

  ::IDL::traits< ::DDS::DataReader>::ref_type
  DDS_ProxyEntityManager::get_datareader_proxy (
    DDS_Native::DDS::Entity *native_entity)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dr_mutex);
    return DDS_ProxyEntityManager::get_proxy<
      ::IDL::traits< ::DDS::DataReader>::ref_type,
      DDS_ProxyEntityManager::DataReaderProxies>
        (native_entity, DDS_ProxyEntityManager::dr_proxies);
  }

  ::IDL::traits< ::DDS::DataWriter>::ref_type
  DDS_ProxyEntityManager::get_datawriter_proxy (
    DDS_Native::DDS::Entity *native_entity)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dw_mutex);
    return DDS_ProxyEntityManager::get_proxy<
      ::IDL::traits< ::DDS::DataWriter>::ref_type,
      DDS_ProxyEntityManager::DataWriterProxies>
        (native_entity, DDS_ProxyEntityManager::dw_proxies);
  }

  ::IDL::traits< ::DDS::Subscriber>::ref_type
  DDS_ProxyEntityManager::get_subscriber_proxy (
    DDS_Native::DDS::Entity *native_entity)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::sub_mutex);
    return DDS_ProxyEntityManager::get_proxy<
      ::IDL::traits< ::DDS::Subscriber>::ref_type,
      DDS_ProxyEntityManager::SubscriberProxies>
        (native_entity, DDS_ProxyEntityManager::sub_proxies);
  }

  ::IDL::traits< ::DDS::Publisher>::ref_type
  DDS_ProxyEntityManager::get_publisher_proxy (
    DDS_Native::DDS::Entity *native_entity)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::pub_mutex);
    return DDS_ProxyEntityManager::get_proxy<
      ::IDL::traits< ::DDS::Publisher>::ref_type,
      DDS_ProxyEntityManager::PublisherProxies>
        (native_entity, DDS_ProxyEntityManager::pub_proxies);
  }

  ::IDL::traits< ::DDS::Topic>::ref_type
  DDS_ProxyEntityManager::get_topic_proxy (
    DDS_Native::DDS::Entity *native_entity)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::tp_mutex);
    return DDS_ProxyEntityManager::get_proxy<
      ::IDL::traits< ::DDS::Topic>::ref_type,
      DDS_ProxyEntityManager::TopicProxies>
        (native_entity, DDS_ProxyEntityManager::tp_proxies);
  }

  ::IDL::traits< ::DDS::DomainParticipant>::ref_type
  DDS_ProxyEntityManager::get_dp_proxy (
    DDS_Native::DDS::Entity *native_entity)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dp_mutex);
    return DDS_ProxyEntityManager::get_proxy<
      ::IDL::traits< ::DDS::DomainParticipant>::ref_type,
      DDS_ProxyEntityManager::DomainParticipantProxies>
        (native_entity, DDS_ProxyEntityManager::dp_proxies);
  }

  ::IDL::traits< ::DDS::Entity>::ref_type
  DDS_ProxyEntityManager::get_entity_proxy (
    DDS_Native::DDS::Entity *native_entity)
  {
    if (!native_entity)
    {
      DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::get_entity_proxy - "
        << "Got a null entity from DDS.");
      return nullptr;
    }

    ::IDL::traits< ::DDS::Entity>::ref_type proxy {};
    const ::DDS::InstanceHandle_t handle =
      ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
        native_entity->get_instance_handle ());

    {
      std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dr_mutex);
      DDS_ProxyEntityManager::DataReaderProxies::iterator dr_it =
        DDS_ProxyEntityManager::dr_proxies.find (handle);
      if (dr_it != DDS_ProxyEntityManager::dr_proxies.end ())
      {
        proxy = dr_it->second;
      }
    }

    if (!proxy)
    {
      {
        std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dw_mutex);
        DDS_ProxyEntityManager::DataWriterProxies::iterator dw_it =
          DDS_ProxyEntityManager::dw_proxies.find (handle);
        if (dw_it != DDS_ProxyEntityManager::dw_proxies.end ())
        {
          proxy = dw_it->second;
        }
      }
    }

    if (!proxy)
    {
      {
        std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::sub_mutex);
        DDS_ProxyEntityManager::SubscriberProxies::iterator sub_it =
          DDS_ProxyEntityManager::sub_proxies.find (handle);
        if (sub_it != DDS_ProxyEntityManager::sub_proxies.end ())
        {
          proxy = sub_it->second;
        }
      }
    }

    if (!proxy)
    {
      {
        std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::pub_mutex);
        DDS_ProxyEntityManager::PublisherProxies::iterator pub_it =
          DDS_ProxyEntityManager::pub_proxies.find (handle);
        if (pub_it != DDS_ProxyEntityManager::pub_proxies.end ())
        {
          proxy = pub_it->second;
        }
      }
    }

    if (!proxy)
    {
      {
        std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::tp_mutex);
        DDS_ProxyEntityManager::TopicProxies::iterator tp_it =
          DDS_ProxyEntityManager::tp_proxies.find (handle);
        if (tp_it != DDS_ProxyEntityManager::tp_proxies.end ())
        {
          proxy = tp_it->second;
        }
      }
    }

    if (!proxy)
    {
      {
        std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dp_mutex);
        DDS_ProxyEntityManager::DomainParticipantProxies::iterator dp_it =
          DDS_ProxyEntityManager::dp_proxies.find (handle);
        if (dp_it != DDS_ProxyEntityManager::dp_proxies.end ())
        {
          proxy = dp_it->second;
        }
      }
    }

    return proxy;
  }

  void
  DDS_ProxyEntityManager::finalize ()
  {
    for (auto& it : DDS_ProxyEntityManager::dr_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered DataReader with handle <" << it.first
        << ">. Resetting the registered reference.");
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::dr_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::dw_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered DataWriter with handle <" << it.first
        << ">. Resetting the registered reference.");
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::dw_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::pub_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered Publisher with handle <" << it.first
        << ">. Resetting the registered reference.");
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::pub_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::sub_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered Subscriber with handle <" << it.first
        << ">. Resetting the registered reference.");
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::sub_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::dp_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered DomainParticipant with handle <" << it.first
        << ">. Resetting the registered reference.");
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::dp_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::tp_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered Topic with handle <" << it.first
        << ">. Resetting the registered reference.");
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::tp_proxies.clear ();
  }
}
