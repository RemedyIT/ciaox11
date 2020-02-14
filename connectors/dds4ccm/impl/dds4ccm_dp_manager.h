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
     *
     */
    class DDS4CCM_IMPL_Export DomainParticipantManager
    {
      /**
      * @class DDSParticipantTopic
      *
      * Stores a list of topics for a specific domain. If
      * several connectors run in the same process and those
      * connectors are making use of the same topic, the topics
      * are shared amongst the connectors.
      *
      * This class maintains a reference count. It's save to remove
      * a topic once the reference count becomes one.
      *
      */
      class DDSParticipantTopic
      {
        public:
          explicit DDSParticipantTopic (
            IDL::traits< ::DDS::DomainParticipant>::ref_type dp);
          ~DDSParticipantTopic ();

          /**
          * Returns the reference count of this class
          */
          uint32_t _ref_count () const;
          /**
          * Increments the reference count of this class
          */
          void _inc_ref ();
          /**
          * Decrements the reference count of this class
          */
          void _dec_ref ();

          IDL::traits< ::DDS::DomainParticipant>::ref_type get_participant ();

        private:
          IDL::traits< ::DDS::DomainParticipant>::ref_type dp_;

          uint32_t ref_count_ { 1 };

          DDSParticipantTopic() = delete;
          DDSParticipantTopic(const DDSParticipantTopic&) = delete;
          DDSParticipantTopic(DDSParticipantTopic&&) = delete;
          DDSParticipantTopic& operator=(const DDSParticipantTopic&) = delete;
          DDSParticipantTopic& operator=(DDSParticipantTopic&&) = delete;
      };

      private:
        DomainParticipantManager () = default;

      public:
        ~DomainParticipantManager () = default;

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

        typedef std::pair<std::string, ::DDS::DomainId_t> IdQosProfile;
        typedef std::map<IdQosProfile, std::unique_ptr<DDSParticipantTopic>> DomainParticipants;
        DomainParticipants dps_;

        typedef DomainParticipants::iterator DomainParticipants_iterator;

        DomainParticipantManager(const DomainParticipantManager&) = delete;
        DomainParticipantManager(DomainParticipantManager&&) = delete;
        DomainParticipantManager& operator=(const DomainParticipantManager&) = delete;
        DomainParticipantManager& operator=(DomainParticipantManager&&) = delete;
      };
  }
}

#define DPMANAGER CIAOX11::DDS4CCM::DomainParticipantManager::getInstance ()

#endif
