// -*- C++ -*-
/**
 * @file    dds_proxy_entity_manager.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_proxy_entity_manager.h"
#include "dds/dds_data_reader.h"
#include "dds/dds_data_writer.h"
#include "dds/dds_publisher.h"
#include "dds/dds_subscriber.h"
#include "dds/dds_domain_participant.h"
#include "dds/dds_topic.h"

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
  bool
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
      return false;
    }

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_proxy - "
      "Registering proxy with handle <" << proxy->get_instance_handle () << "> succeeded");

    return true;
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

    typename PROXY_MAP::iterator const it = lst.find (handle);
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

  template<typename PROXY_MAP>
  bool
  DDS_ProxyEntityManager::unregister_proxy (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle,
    PROXY_MAP &lst)
  {
    bool retval = false;
    typename PROXY_MAP::iterator const it = lst.find (handle);
    if (it != lst.end ())
    {
      lst.erase (it);
      DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_proxy - "
        << "Removed proxy with handle <" << handle
        << "> from the list");
      retval = true;
    }
    else
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::unregister_proxy - "
        << "Could not find a proxy with handle <" << handle
        << ">");
    }
    return retval;
  }

  bool
  DDS_ProxyEntityManager::register_datareader_proxy (
    ::IDL::traits< ::DDS::DataReader>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dr_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_datareader_proxy - "
      "Registering proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::DataReader>::ref_type,
      DDS_ProxyEntityManager::DataReaderProxies>
        (proxy, DDS_ProxyEntityManager::dr_proxies);
  }

  bool
  DDS_ProxyEntityManager::register_datawriter_proxy (
    ::IDL::traits< ::DDS::DataWriter>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dw_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_datawriter_proxy - "
      "Registering proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::DataWriter>::ref_type,
      DDS_ProxyEntityManager::DataWriterProxies>
        (proxy, DDS_ProxyEntityManager::dw_proxies);
  }

  bool
  DDS_ProxyEntityManager::register_subscriber_proxy (
    ::IDL::traits< ::DDS::Subscriber>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::sub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_subscriber_proxy - "
      "Registering proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::Subscriber>::ref_type,
      DDS_ProxyEntityManager::SubscriberProxies>
        (proxy, DDS_ProxyEntityManager::sub_proxies);
  }

  bool
  DDS_ProxyEntityManager::register_publisher_proxy (
    ::IDL::traits< ::DDS::Publisher>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::pub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_publisher_proxy - "
      "Registering proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::Publisher>::ref_type,
      DDS_ProxyEntityManager::PublisherProxies>
        (proxy, DDS_ProxyEntityManager::pub_proxies);
  }

  bool
  DDS_ProxyEntityManager::register_topic_proxy (
    ::IDL::traits< ::DDS::Topic>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::tp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_topic_proxy - "
      "Registering proxy with handle <" << proxy->get_instance_handle () << ">");

    // Let us find first whether we already have a topic proxy for the
    // given instance handle
    typename TopicProxies::iterator const it = tp_proxies.find (proxy->get_instance_handle ());
    if (it != tp_proxies.end ())
    {
      // We have found a topic proxy, increment its reference count
      ++it->second.first;
    }
    else
    {
      // We have not found a topic proxy, so add one to the map with a refcount of 1
      TopicRefcount const refcount_pair = std::make_pair (1, proxy);
      std::pair<typename TopicProxies::iterator, bool> ret =
        tp_proxies.insert (typename TopicProxies::value_type (
        proxy->get_instance_handle (), refcount_pair));
      if (!ret.second)
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::register_topic_proxy - "
          "Registering proxy <" << proxy->get_instance_handle () << "> failed");
        return false;
      }

      DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_topic_proxy - "
        "Registering topic proxy with handle <" << proxy->get_instance_handle () << "> succeeded");
    }

    return true;
  }

  bool
  DDS_ProxyEntityManager::register_dp_proxy (
    ::IDL::traits< ::DDS::DomainParticipant>::ref_type proxy)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::register_dp_proxy - "
      "Registering proxy with handle <" << proxy->get_instance_handle () << ">");

    return DDS_ProxyEntityManager::register_proxy<
      ::IDL::traits< ::DDS::DomainParticipant>::ref_type,
      DDS_ProxyEntityManager::DomainParticipantProxies>
        (proxy, DDS_ProxyEntityManager::dp_proxies);
  }

  bool
  DDS_ProxyEntityManager::unregister_datareader_proxy (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dr_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_datareader_proxy - "
      "Unregistering proxy with handle <" << handle << ">");

    return DDS_ProxyEntityManager::unregister_proxy<DDS_ProxyEntityManager::DataReaderProxies>
      (handle, DDS_ProxyEntityManager::dr_proxies);
  }

  bool
  DDS_ProxyEntityManager::unregister_datawriter_proxy (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dw_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_datawriter_proxy - "
      "Unregistering proxy with handle <" << handle << ">");

    return DDS_ProxyEntityManager::unregister_proxy<DDS_ProxyEntityManager::DataWriterProxies>
      (handle, DDS_ProxyEntityManager::dw_proxies);
  }

  bool
  DDS_ProxyEntityManager::unregister_subscriber_proxy (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::sub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_subscriber_proxy - "
      "Unregistering proxy with handle <" << handle << ">");

    return DDS_ProxyEntityManager::unregister_proxy<DDS_ProxyEntityManager::SubscriberProxies>
      (handle, DDS_ProxyEntityManager::sub_proxies);
  }

  bool
  DDS_ProxyEntityManager::unregister_publisher_proxy (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::pub_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_publisher_proxy - "
      "Unregistering proxy with handle <" << handle << ">");

    return DDS_ProxyEntityManager::unregister_proxy<DDS_ProxyEntityManager::PublisherProxies>
      (handle, DDS_ProxyEntityManager::pub_proxies);
  }

  bool
  DDS_ProxyEntityManager::unregister_topic_proxy (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::tp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_topic_proxy - "
      "Unregistering proxy with handle <" << handle << ">");

    bool retval = false;
    typename TopicProxies::iterator const it = tp_proxies.find (handle);
    if (it != tp_proxies.end ())
    {
      uint32_t const refcount = --it->second.first;
      if (refcount == 0)
        {
          DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_topic_proxy - "
            << "Removed topic proxy with handle <" << handle
            << "> from the list because its refcount dropped to zero");
          tp_proxies.erase (it);
          retval = true;
        }
      else
        {
          DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_topic_proxy - "
            << "Did not remove topic proxy with handle <" << handle
            << "> from the list because its refcount dropped to " << refcount);
        }
    }
    else
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::unregister_proxy - "
        << "Could not find a proxy with handle <" << handle
        << ">");
    }

    return retval;
  }

  bool
  DDS_ProxyEntityManager::unregister_dp_proxy (
    IDL::traits< ::DDS::InstanceHandle_t>::in_type handle)
  {
    std::lock_guard<std::mutex> __guard (DDS_ProxyEntityManager::dp_mutex);

    DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::unregister_dp_proxy - "
      "Unregistering proxy with handle <" << handle << ">");

    return DDS_ProxyEntityManager::unregister_proxy<DDS_ProxyEntityManager::DomainParticipantProxies>
      (handle, DDS_ProxyEntityManager::dp_proxies);
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

    if (!native_entity)
    {
      DDSX11_IMPL_LOG_DEBUG ("DDS_ProxyEntityManager::get_topic_proxy - "
        << "Got a null entity from DDS.");
      return {};
    }

    ::IDL::traits< ::DDS::Topic>::ref_type proxy {};
    ::DDS::InstanceHandle_t const handle =
      ::DDSX11::traits< ::DDS::InstanceHandle_t>::retn (
        native_entity->get_instance_handle ());

    typename TopicProxies::iterator const it = tp_proxies.find (handle);
    if (it != tp_proxies.end ())
    {
      proxy = it->second.second;
    }
    else
    {
      DDSX11_IMPL_LOG_INFO ("DDS_ProxyEntityManager::get_proxy - "
        << "Could not find a proxy with handle <" << handle
        << ">");
    }
    return proxy;
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
      return {};
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
          proxy = tp_it->second.second;
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
      IDL::traits< ::DDSX11::DDS_DataReader_proxy>::ref_type proxy =
        data_reader_trait::proxy (it.second);
      if (proxy)
      {
        proxy->clear_native_entity();
      }
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::dr_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::dw_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered DataWriter with handle <" << it.first
        << ">. Resetting the registered reference.");
      IDL::traits< ::DDSX11::DDS_DataWriter_proxy>::ref_type proxy =
        data_writer_trait::proxy (it.second);
      if (proxy)
      {
        proxy->clear_native_entity();
      }
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::dw_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::pub_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered Publisher with handle <" << it.first
        << ">. Resetting the registered reference.");
      IDL::traits< ::DDSX11::DDS_Publisher_proxy>::ref_type proxy =
        publisher_trait::proxy (it.second);
      if (proxy)
      {
        proxy->clear_native_entity();
      }
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::pub_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::sub_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered Subscriber with handle <" << it.first
        << ">. Resetting the registered reference.");
      IDL::traits< ::DDSX11::DDS_Subscriber_proxy>::ref_type proxy =
        subscriber_trait::proxy (it.second);
      if (proxy)
      {
        proxy->clear_native_entity();
      }
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::sub_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::tp_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered Topic with handle <" << it.first
        << ">. Resetting the registered reference.");
      IDL::traits< ::DDSX11::DDS_Topic_proxy>::ref_type proxy =
        topic_trait::proxy (it.second.second);
      if (proxy)
      {
        proxy->clear_native_entity();
      }
      it.second.second = nullptr;
    }
    DDS_ProxyEntityManager::tp_proxies.clear ();

    for (auto& it : DDS_ProxyEntityManager::dp_proxies)
    {
      DDSX11_IMPL_LOG_ERROR ("DDS_ProxyEntityManager::finalize - "
        << "Found a registered DomainParticipant with handle <" << it.first
        << ">. Resetting the registered reference.");
      IDL::traits< ::DDSX11::DDS_DomainParticipant_proxy>::ref_type proxy =
        domain_participant_trait::proxy (it.second);
      if (proxy)
      {
        proxy->clear_native_entity();
      }
      it.second = nullptr;
    }
    DDS_ProxyEntityManager::dp_proxies.clear ();
  }
}
