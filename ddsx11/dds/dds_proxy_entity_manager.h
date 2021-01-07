// -*- C++ -*-
/**
 * @file    dds_proxy_entity_manager.h
 * @author  Marcel Smit
 *
 * @brief   Class which manages the C++11 proxies and DDS vendor entities
 *
 * The concept between the DDSX11 proxies is that there is one DDSX11 proxy
 * for each native DDS entity. Without this one to one relationship we can have
 * multiple DDSX11 proxies pointing to the same native DDS entity and this
 * could result in dangling pointers at the moment the native DDS entity
 * gets deleted. Some DDS vendors do provide reference counting for their
 * native entities, but others don't.
 *
 * The C++11 proxies are stored in internal maps for data readers/data
 * writers/subscribers/publishers/topics/domain participants. This way
 * narrows are prevented in the critical path.
 *
 * The DDS InstanceHandle_t is not guaranteed to be unique within the same
 * proces, some vendors do have it unique, but others don't have an
 * id which is only unique within a single domain participant. Because
 * of this the maps within this class all use the DDS native entity
 * pointer as key.
 *
 * The maps are the only place in the DDS proxy where a strong reference
 * is kept!!
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
  class DDSX11_IMPL_Export DDS_ProxyEntityManager final
  {
  public:
    /// Constructor
    DDS_ProxyEntityManager () = default;

    /// Destructor
    ~DDS_ProxyEntityManager () = default;

    /**
      * @name         register_xxx_proxy
      * @brief        Storing the DDSX11 proxy into the corresponding map
      * @param proxy  The C++11 proxy to store
      * @param native The pointer to the native DDS entity
      * @retval true  Registering the proxy succeeded
      * @retval false Registering the proxy failed
      */
    //@{
    static bool register_datareader_proxy (::IDL::traits< ::DDS::DataReader>::ref_type proxy, DDS_Native::DDS::Entity *native_entity);

    static bool register_datawriter_proxy (::IDL::traits< ::DDS::DataWriter>::ref_type proxy, DDS_Native::DDS::Entity *native_entity);

    static bool register_subscriber_proxy (::IDL::traits< ::DDS::Subscriber>::ref_type proxy, DDS_Native::DDS::Entity *native_entity);

    static bool register_publisher_proxy (::IDL::traits< ::DDS::Publisher>::ref_type proxy, DDS_Native::DDS::Entity *native_entity);

    static bool register_topic_proxy (::IDL::traits< ::DDS::Topic>::ref_type proxy, DDS_Native::DDS::Entity *native_entity);

    static bool register_dp_proxy (::IDL::traits< ::DDS::DomainParticipant>::ref_type proxy, DDS_Native::DDS::Entity *native_entity);
    //@}

    /**
      * @name  unregister_xxx_proxy
      * @brief Looking up the given DDSX11 proxy and remove it from
      *        the corresponding map
      * @param native_entity The pointer to the native DDS entity for which we should unregister the DDSX11 proxy
      * @param instance_handle The DDS instance handle of the DDS entity, passed here because we can't
      * assume that it is safe to retrieve it from the @a native_entity at this point anymore
      * @retval true The proxy has been successfully unregistered
      * @retval false The proxy was not found
      */
    //@{
    static bool unregister_datareader_proxy (DDS_Native::DDS::Entity *native_entity, IDL::traits< ::DDS::InstanceHandle_t>::in_type instance_handle);

    static bool unregister_datawriter_proxy (DDS_Native::DDS::Entity *native_entity, IDL::traits< ::DDS::InstanceHandle_t>::in_type instance_handle);

    static bool unregister_subscriber_proxy (DDS_Native::DDS::Entity *native_entity, IDL::traits< ::DDS::InstanceHandle_t>::in_type instance_handle);

    static bool unregister_publisher_proxy (DDS_Native::DDS::Entity *native_entity, IDL::traits< ::DDS::InstanceHandle_t>::in_type instance_handle);

    static bool unregister_topic_proxy (DDS_Native::DDS::Entity *native_entity, IDL::traits< ::DDS::InstanceHandle_t>::in_type instance_handle);

    static bool unregister_dp_proxy (DDS_Native::DDS::Entity *native_entity, IDL::traits< ::DDS::InstanceHandle_t>::in_type instance_handle);
    //@}

    /**
      * @name                get_xxx_proxy
      * @brief               Retrieving the DDSX11 proxy from the corresponding map
      * @param native_entity The native pointer of which to find the C++11 counterpart
      * @return              The C++11 proxy if found; nullptr otherwise
      */
    //@{
    static ::IDL::traits< ::DDS::DataReader>::ref_type get_datareader_proxy (DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::DataWriter>::ref_type get_datawriter_proxy (DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::Subscriber>::ref_type get_subscriber_proxy (DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::Publisher>::ref_type get_publisher_proxy (DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::Topic>::ref_type get_topic_proxy (DDS_Native::DDS::Entity *native_entity);

    static ::IDL::traits< ::DDS::DomainParticipant>::ref_type get_dp_proxy (DDS_Native::DDS::Entity *native_entity);

    /// Search every map for the given entity
    static ::IDL::traits< ::DDS::Entity>::ref_type get_entity_proxy (DDS_Native::DDS::Entity *native_entity);
    //@}

    static void finalize ();

  private:
    /**
      * @name          register_proxy
      * @brief         Helper method, preventing double code.
      *                Stores the C++11 proxy in the given map in a consistent way.
      * @tparam PROXY_TYPE The type of entity to unregister (DataReader/DataWRiter/Topic/...)
      * @tparam PROXY_MAP  The type of the map in which to store the given proxy
      * @param  proxy   The DDSX11 proxy to store
      * @param  native  The pointer to the native entity
      * @param  lst     Reference to the map in which to store the proxy
      * @retval true    The registering of the proxy succeeded
      * @retval false   The registering of the proxy failed
      *
      */
    template<typename PROXY_TYPE, typename PROXY_MAP>
    static bool
    register_proxy (
      PROXY_TYPE proxy,
      DDS_Native::DDS::Entity *native_entity,
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
      * @param native_entity  The pointer to the native entity for which we want to unregister the proxy
      * @param instance_handle The DDS instance handle of the DDS entity, passed here because we can't
      * assume that it is safe to retrieve it from the @a native_entity at this point anymore
      * @param lst     Reference to the map from which to unregister the proxy
      * @retval true The proxy has been successfully unregistered
      * @retval false The proxy was not found
      */
    template<typename PROXY_MAP>
    static bool
    unregister_proxy (
      DDS_Native::DDS::Entity *native_entity,
      IDL::traits< ::DDS::InstanceHandle_t>::in_type instance_handle,
      PROXY_MAP &lst);

    /// Map containing all DataReader C++11 proxies
    typedef std::map<DDS_Native::DDS::Entity *, IDL::traits< ::DDS::DataReader>::ref_type> DataReaderProxies;
    static DataReaderProxies dr_proxies;
    static std::mutex dr_mutex;

    /// Map containing all DataWriter C++11 proxies
    typedef std::map<DDS_Native::DDS::Entity *, IDL::traits< ::DDS::DataWriter>::ref_type> DataWriterProxies;
    static DataWriterProxies dw_proxies;
    static std::mutex dw_mutex;

    /// Map containing all Subscriber C++11 proxies
    typedef std::map<DDS_Native::DDS::Entity *, IDL::traits< ::DDS::Subscriber>::ref_type> SubscriberProxies;
    static SubscriberProxies sub_proxies;
    static std::mutex sub_mutex;

    /// Map containing all Publisher C++11 proxies
    typedef std::map<DDS_Native::DDS::Entity *, IDL::traits< ::DDS::Publisher>::ref_type> PublisherProxies;
    static PublisherProxies pub_proxies;
    static std::mutex pub_mutex;

    /// Map containing all Topic C++11 proxies
    /// A topic can be registered multiple times because using find_topic the native DDS
    /// implementation can return multiple times the same topic for which multiple times the delete_topic
    /// must be called, only for the last instance the unregister will remove it from the map
    typedef std::pair <uint32_t, IDL::traits< ::DDS::Topic>::ref_type> TopicRefcount;
    typedef std::map<DDS_Native::DDS::Entity *, TopicRefcount> TopicProxies;
    static TopicProxies tp_proxies;
    static std::mutex tp_mutex;

    /// Map containing all DomainParticipant C++11 proxies
    typedef std::map<DDS_Native::DDS::Entity *, IDL::traits< ::DDS::DomainParticipant>::ref_type> DomainParticipantProxies;
    static DomainParticipantProxies dp_proxies;
    static std::mutex dp_mutex;

    DDS_ProxyEntityManager(const DDS_ProxyEntityManager&) = delete;
    DDS_ProxyEntityManager(DDS_ProxyEntityManager&&) = delete;
    DDS_ProxyEntityManager& operator=(const DDS_ProxyEntityManager&) = delete;
    DDS_ProxyEntityManager& operator=(DDS_ProxyEntityManager&&) = delete;
  };
}

#endif /* DDSX11_IMPL_ENTITY_MANAGER_H_ */
