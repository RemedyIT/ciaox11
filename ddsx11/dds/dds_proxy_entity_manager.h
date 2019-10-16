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
      * @name          register_xxx_proxy
      * @brief         Storing the given proxy into the corresponding map
      * @param proxy   The C++11 proxy to store. Will be set to a nullptr
      *                if registration fails.
      */
    //@{
    static void
    register_datareader_proxy (
      ::IDL::traits< ::DDS::DataReader>::ref_type proxy);

    static void
    register_datawriter_proxy (
      ::IDL::traits< ::DDS::DataWriter>::ref_type proxy);

    static void
    register_subscriber_proxy (
      ::IDL::traits< ::DDS::Subscriber>::ref_type proxy);

    static void
    register_publisher_proxy (
      ::IDL::traits< ::DDS::Publisher>::ref_type proxy);

    static void
    register_topic_proxy (
      ::IDL::traits< ::DDS::Topic>::ref_type proxy);

    static void
    register_dp_proxy (
      ::IDL::traits< ::DDS::DomainParticipant>::ref_type proxy);
    //@}

    /**
      * @name          unregister_xxx_proxy
      * @brief         Looking up the given proxy and remove it from
      *                the corresponding map
      * @param proxy   The C++11 proxy to unregister
      * @return        The pointer to the native entity if ok, nullptr if an
      *                error occurred.
      */
    //@{
    static void
    unregister_datareader_proxy (
      ::IDL::traits< ::DDS::DataReader>::ref_type proxy);

    static void
    unregister_datawriter_proxy (
      ::IDL::traits< ::DDS::DataWriter>::ref_type proxy);

    static void
    unregister_subscriber_proxy (
      ::IDL::traits< ::DDS::Subscriber>::ref_type proxy);

    static void
    unregister_publisher_proxy (
      ::IDL::traits< ::DDS::Publisher>::ref_type proxy);

    static void
    unregister_topic_proxy (
      ::IDL::traits< ::DDS::Topic>::ref_type proxy);

    static void
    unregister_dp_proxy (
      ::IDL::traits< ::DDS::DomainParticipant>::ref_type proxy);
    //@}

    /**
      * @name                get_xxx_proxy
      * @brief               Retrieving the C++11 proxy from the corresponding map
      * @param native_entity The native pointer of which to find the C++11 counterpart
      * @return              The C++11 proxy if found; nullptr otherwise
      */
    //@{
    static ::IDL::traits< ::DDS::DataReader>::ref_type
    get_datareader_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::DataWriter>::ref_type
    get_datawriter_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::Subscriber>::ref_type
    get_subscriber_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::Publisher>::ref_type
    get_publisher_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::Topic>::ref_type
    get_topic_proxy (
      DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::DomainParticipant>::ref_type
    get_dp_proxy (
      DDS_Native::DDS::Entity *native_entity);

    /// Search every map for the given entity
    static ::IDL::traits< ::DDS::Entity>::ref_type
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
      * @tparam ENTITY_TYPE The type of entity to store (DataReader/DataWRiter/Topic/...)
      * @tparam PROXY_MAP   The type of the map in which to store the given proxy
      * @param  proxy   The C++11 proxy to store. Will be set to a nullptr is registration
      *                 fails.
      * @param  lst     reference to the map in which to store the proxy.
      *
      */
    template<typename PROXY_TYPE, typename PROXY_MAP>
    static void
    register_proxy (
      PROXY_TYPE proxy,
      PROXY_MAP &lst);

    /**
      * @name          get_proxy
      * @brief         Helper method, preventing double code.
      *                Retrieves the C++11 proxy in the given map in a consistent way.
      * @tparam ENTITY_TYPE The type of entity to return (DataReader/DataWRiter/Topic/...)
      * @tparam PROXY_MAP   The type of the map from which to retrieve the given proxy
      * @param  native_entity The native pointer to the entity
      * @param  lst     reference to the map in which to store the proxy.
      * @return        The C++11 proxies if found in the map, a nullptr if not found
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
      *                Removes the given proxy from the corresponding list and
      *                sets it to a nullptr.
      * @tparam ENTITY_TYPE The type of entity to unregister (DataReader/DataWRiter/Topic/...)
      * @tparam PROXY_MAP   The type of the map from which to unregister the given proxy
      * @param  proxy   The C++11 proxy to unregister
      * @param  lst     reference to the map from which to unregister the proxy.
      *
      */
    template<typename PROXY_TYPE, typename PROXY_MAP>
    static void
    unregister_proxy (
      PROXY_TYPE proxy,
      PROXY_MAP &lst);

    /// Place holder for DataReader C++11 proxies
    typedef std::map< ::DDS::InstanceHandle_t, IDL::traits< ::DDS::DataReader>::ref_type, CompareHandles> DataReaderProxies;
    static DataReaderProxies dr_proxies;
    static std::mutex dr_mutex;

    /// Place holder for DataWriter C++11 proxies
    typedef std::map< ::DDS::InstanceHandle_t, IDL::traits< ::DDS::DataWriter>::ref_type, CompareHandles> DataWriterProxies;
    static DataWriterProxies dw_proxies;
    static std::mutex dw_mutex;

    /// Place holder for Subscriber C++11 proxies
    typedef std::map< ::DDS::InstanceHandle_t, IDL::traits< ::DDS::Subscriber>::ref_type, CompareHandles> SubscriberProxies;
    static SubscriberProxies sub_proxies;
    static std::mutex sub_mutex;

    /// Place holder for Publisher C++11 proxies
    typedef std::map< ::DDS::InstanceHandle_t, IDL::traits< ::DDS::Publisher>::ref_type, CompareHandles> PublisherProxies;
    static PublisherProxies pub_proxies;
    static std::mutex pub_mutex;

    /// Place holder for Topic C++11 proxies
    typedef std::map< ::DDS::InstanceHandle_t, IDL::traits< ::DDS::Topic>::ref_type, CompareHandles> TopicProxies;
    static TopicProxies tp_proxies;
    static std::mutex tp_mutex;

    /// Place holder for Participant C++11 proxies
    typedef std::map< ::DDS::InstanceHandle_t, IDL::traits< ::DDS::DomainParticipant>::ref_type, CompareHandles> DomainParticipantProxies;
    static DomainParticipantProxies dp_proxies;
    static std::mutex dp_mutex;

    DDS_ProxyEntityManager(const DDS_ProxyEntityManager&) = delete;
    DDS_ProxyEntityManager(DDS_ProxyEntityManager&&) = delete;
    DDS_ProxyEntityManager& operator=(const DDS_ProxyEntityManager&) = delete;
    DDS_ProxyEntityManager& operator=(DDS_ProxyEntityManager&&) = delete;
  };
}

#endif /* DDSX11_IMPL_ENTITY_MANAGER_H_ */
