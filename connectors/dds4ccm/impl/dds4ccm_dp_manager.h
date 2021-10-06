// -*- C++ -*-
/**
 * @file    dds4ccm_dp_manager.h
 * @author  Marcel Smit
 *
 * @brief   Domain Participant Manager for DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_DP_MANAGER_H_
#define DDS4CCM_DP_MANAGER_H_

#include "dds4ccm/impl/dds4ccm_impl_export.h"
#include "dds4ccm/idl/dds_rtf2_dcpsC.h"

#include <map>
#include <string>
#include <mutex>

namespace CIAOX11
{
  namespace DDS4CCM
  {
    /**
     *
     * @class DomainParticipantManager
     *
     * Stores a DDSParticipantTopic per domain ID and QOS profile string.
     * When several connectors are joining the same domain ID, using the
     * same QOS settings (ie have the same QOS profile string),
     * the DomainParticipant for that combination is shared. This is done
     * to save resources (running threads/memory usage).
     *
     * The DomainParticipantManager is a singleton.
     */
    class DDS4CCM_IMPL_Export DomainParticipantManager
    {
    private:
      DomainParticipantManager ();
      ~DomainParticipantManager ();

    public:
      /**
      * Searches for the DomainParticipant in the internal map.
      * Search is based on the given domain ID and the given QOS
      * (QOS profile string). If found, it'll increment the
      * reference count of the DDSParticipantTopic instance.
      */
      IDL::traits< ::DDS::DomainParticipant>::ref_type
      get_participant (const ::DDS::DomainId_t domain_id,
        const std::string &qos_profile);

      /**
      * Adding a DDSParticipantTopic instance when the
      * internal maps doesn't contain a reference. Returns
      * false if there's already an DDSParticipantTopic
      * available (base on domain ID and QOS)
      */
      bool
      register_participant (::DDS::DomainId_t domain_id,
        const std::string &qos_profile,
        IDL::traits< ::DDS::DomainParticipant>::ref_type dp);

      /**
      * Removes the DDSParticipantTopic instance when the
      * reference count is one.
      * Returns false if the reference count of the corresponding
      * DDSParticipantTopic was not nil
      */
      bool
      unregister_participant (::DDS::DomainId_t domain_id,
        const std::string& qos_profile,
        IDL::traits< ::DDS::DomainParticipant>::ref_type dp);

      /**
      * Try to close the DPM, at the moment no domain participants are
      * registered anymore we are going to shutdown DDS interaction
      * @retval true The DPM is now fully closed, no domain participants
      * are registered anymore
      * @retval false The DPM stays active because there are domain
      * participants registered
      */
      bool close ();

      /**
      * Get DPM singleton instance.
      */
      static DomainParticipantManager* getInstance ();

    private:
      std::mutex dps_mutex_;

      /// Key type, we store a domain participant for the unique combination of
      /// QoS profile and Domain Id
      using IdQosProfile = std::pair<std::string, ::DDS::DomainId_t>;
      /// A domain participant can be used multiple times, so keep a ref count how many times
      /// it is used
      using DomainParticipantRefcount = std::pair<IDL::traits< ::DDS::DomainParticipant>::ref_type, uint32_t>;
      using DomainParticipants = std::map<IdQosProfile, DomainParticipantRefcount>;
      DomainParticipants dps_;

      using DomainParticipants_iterator = DomainParticipants::iterator;

      DomainParticipantManager(const DomainParticipantManager&) = delete;
      DomainParticipantManager(DomainParticipantManager&&) = delete;
      DomainParticipantManager& operator=(const DomainParticipantManager&) = delete;
      DomainParticipantManager& operator=(DomainParticipantManager&&) = delete;
    };
  }
}

#define DPMANAGER CIAOX11::DDS4CCM::DomainParticipantManager::getInstance ()

#endif
