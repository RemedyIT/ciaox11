// -*- C++ -*-
/**
 * @file    dds_proxy_entity_manager.h
 * @author  Marcel Smit
 *
 * @brief   Class which manages the C++11 proxies and DDS vendor entities
 *
 *          This way there's no need to create a C++ proxy once a callback from DDS
 *          gets invoked.
 *          Another advantage is that only one proxy represents the native entity.
 *          The C++11 proxies are stored in internal maps for data readers/data
 *          writers/subscribers/publishers/topics/domain participants. This way
 *          narrows are prevented in the critical path.
 *
 *          The internal maps have the DDS InstanceHandle_t as key.
 *
 *          The maps are the only place in the DDS proxy where a strong reference
 *          is kept!!
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_ENTITY_MANAGER_H_
#define DDSX11_IMPL_ENTITY_MANAGER_H_

#include "dds/dds_export.h"
#include "idl/dds_dcpsC.h"

#include <map>
#include <mutex>

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class Entity;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  /**
    * @name    CompareHandles
    * @brief   operator used by the internal maps to compare
    *          the InstanceHandle_t
    */
  struct CompareHandles
  {
    bool operator ()(const ::DDS::InstanceHandle_t &h1, const ::DDS::InstanceHandle_t &h2) const
    {
      return h1 < h2;
    }
  };

  class DDSX11_IMPL_Export DDS_ProxyEntityManager final
  {
  public:
    /// Constructor
    DDS_ProxyEntityManager () = default;

    /// Destructor
    ~DDS_ProxyEntityManager () = default;

    /**
      * @name         register_xxx_proxy
      * @brief        Storing the given proxy into the corresponding map
      * @param proxy  The C++11 proxy to store
      * @retval true  Registering the proxy succeeded
      * @retval false Registering the proxy failed
      */
    //@{
    static bool
    register_datareader_proxy (::IDL::traits<::DDS::DataReader>::ref_type proxy);

    static bool register_datawriter_proxy (::IDL::traits<::DDS::DataWriter>::ref_type proxy);

    static bool register_subscriber_proxy (::IDL::traits<::DDS::Subscriber>::ref_type proxy);

    static bool register_publisher_proxy (::IDL::traits<::DDS::Publisher>::ref_type proxy);

    static bool register_topic_proxy (::IDL::traits<::DDS::Topic>::ref_type proxy, DDS_Native::DDS::Entity *native_entity);

    static bool register_dp_proxy (::IDL::traits<::DDS::DomainParticipant>::ref_type proxy);
    //@}

    /**
      * @name  unregister_xxx_proxy
      * @brief Looking up the given proxy and remove it from
      *        the corresponding map
      * @param handle The instance handle of the proxy to unregister
      * @retval true The proxy has been successfully unregistered
      * @retval false The proxy was not found
      */
    //@{
    static bool
    unregister_datareader_proxy (
      IDL::traits<::DDS::InstanceHandle_t>::in_type handle);

    static bool
    unregister_datawriter_proxy (
      IDL::traits<::DDS::InstanceHandle_t>::in_type handle);

    static bool
    unregister_subscriber_proxy (
      IDL::traits<::DDS::InstanceHandle_t>::in_type handle);

    static bool
    unregister_publisher_proxy (
      IDL::traits<::DDS::InstanceHandle_t>::in_type handle);

    static bool
    unregister_topic_proxy (
      DDS_Native::DDS::Entity *native_entity,
      IDL::traits<::DDS::InstanceHandle_t>::in_type handle);

    static bool
    unregister_dp_proxy (
      IDL::traits<::DDS::InstanceHandle_t>::in_type handle);
    //@}

    /**
      * @name                get_xxx_proxy
      * @brief               Retrieving the C++11 proxy from the corresponding map
      * @param native_entity The native pointer of which to find the C++11 counterpart
      * @return              The C++11 proxy if found; nullptr otherwise
      */
    //@{
    static ::IDL::traits<::DDS::DataReader>::ref_type
    get_datareader_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits<::DDS::DataWriter>::ref_type
    get_datawriter_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits<::DDS::Subscriber>::ref_type
    get_subscriber_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits<::DDS::Publisher>::ref_type
    get_publisher_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits<::DDS::Topic>::ref_type
    get_topic_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits<::DDS::DomainParticipant>::ref_type
    get_dp_proxy (
      DDS_Native::DDS::Entity *native_entity);

    /// Search every map for the given entity
    static ::IDL::traits<::DDS::Entity>::ref_type
    get_entity_proxy (
        DDS_Native::DDS::Entity *native_entity);
    //@}

    static void
    finalize ();

  private:
    /**
      * @name          register_proxy
      * @brief         Helper method, preventing double code.
      *                Stores the C++11 proxy in the given map in a consistent way.
      * @tparam PROXY_TYPE The type of entity to unregister (DataReader/DataWRiter/Topic/...)
      * @tparam PROXY_MAP  The type of the map in which to store the given proxy
      * @param  proxy   The C++11 proxy to store
      * @param  lst     Reference to the map in which to store the proxy
      * @retval true    The registering of the proxy succeeded
      * @retval false   The registering of the proxy failed
      *
      */
    template<typename PROXY_TYPE, typename PROXY_MAP>
    static bool
    register_proxy (
      PROXY_TYPE proxy,
      PROXY_MAP &lst);

    /**
      * @name          get_proxy
      * @brief         Helper method, preventing double code.
      *                Retrieves the C++11 proxy in the given map in a consistent way.
      * @tparam PROXY_TYPE The type of entity to unregister (DataReader/DataWRiter/Topic/...)
      * @tparam PROXY_MAP  The type of the map from which to retrieve the given proxy
      * @param  native_entity The native pointer to the entity
      * @param  lst     Reference to the map in which to store the proxy.
      * @return         The C++11 proxies if found in the map, a nullptr if not found
      *
      */
    template<typename PROXY_TYPE, typename PROXY_MAP>
    static PROXY_TYPE
    get_proxy (
      DDS_Native::DDS::Entity *native_entity,
      PROXY_MAP &lst);

    /**
      * @name          unregister_proxy
      * @brief         Helper method, preventing double code.
      *                Removes the given proxy from the corresponding list.
      * @tparam PROXY_MAP  The type of the map from which to unregister the given proxy
      * @param handle  The instance handle of the proxy we need to unregister
      * @param lst     Reference to the map from which to unregister the proxy
      * @retval true The proxy has been successfully unregistered
      * @retval false The proxy was not found
      */
    template<typename PROXY_MAP>
    static bool
    unregister_proxy (
      IDL::traits<::DDS::InstanceHandle_t>::in_type handle,
      PROXY_MAP &lst);

    /// Map containing all DataReader C++11 proxies
    using DataReaderProxies = std::map< ::DDS::InstanceHandle_t, IDL::traits<::DDS::DataReader>::ref_type, CompareHandles>;
    static DataReaderProxies dr_proxies;
    static std::mutex dr_mutex;

    /// Map containing all DataWriter C++11 proxies
    using DataWriterProxies = std::map< ::DDS::InstanceHandle_t, IDL::traits<::DDS::DataWriter>::ref_type, CompareHandles>;
    static DataWriterProxies dw_proxies;
    static std::mutex dw_mutex;

    /// Map containing all Subscriber C++11 proxies
    using SubscriberProxies = std::map< ::DDS::InstanceHandle_t, IDL::traits<::DDS::Subscriber>::ref_type, CompareHandles>;
    static SubscriberProxies sub_proxies;
    static std::mutex sub_mutex;

    /// Map containing all Publisher C++11 proxies
    using PublisherProxies = std::map< ::DDS::InstanceHandle_t, IDL::traits<::DDS::Publisher>::ref_type, CompareHandles>;
    static PublisherProxies pub_proxies;
    static std::mutex pub_mutex;

    /// Map containing all Topic C++11 proxies
    /// A topic can be registered multiple times because using find_topic the native DDS
    /// implementation can return multiple times the same topic for which multiple times the delete_topic
    /// must be called, only for the last instance the unregister will remove it from the map
    using TopicRefcount = std::pair <uint32_t, IDL::traits<::DDS::Topic>::ref_type>;
    using TopicProxies = std::map<DDS_Native::DDS::Entity *, TopicRefcount>;
    static TopicProxies tp_proxies;
    static std::mutex tp_mutex;

    /// Map containing all DomainParticipant C++11 proxies
    using DomainParticipantProxies = std::map< ::DDS::InstanceHandle_t, IDL::traits<::DDS::DomainParticipant>::ref_type, CompareHandles>;
    static DomainParticipantProxies dp_proxies;
    static std::mutex dp_mutex;

    DDS_ProxyEntityManager(const DDS_ProxyEntityManager&) = delete;
    DDS_ProxyEntityManager(DDS_ProxyEntityManager&&) = delete;
    DDS_ProxyEntityManager& operator=(const DDS_ProxyEntityManager&) = delete;
    DDS_ProxyEntityManager& operator=(DDS_ProxyEntityManager&&) = delete;
  };
}

#endif /* DDSX11_IMPL_ENTITY_MANAGER_H_ */
