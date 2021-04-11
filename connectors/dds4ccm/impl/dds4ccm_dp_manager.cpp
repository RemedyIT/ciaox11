// -*- C++ -*-
/**
 * @file    dds4ccm_dp_manager.cpp
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM4CIAOX11 DomainParticipant implementation
 *

 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_vendor_adapter.h"
#include "dds4ccm/impl/dds4ccm_dp_manager.h"
#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {

    DomainParticipantManager* DomainParticipantManager::getInstance ()
    {
      static DomainParticipantManager instance_;

      return std::addressof(instance_);
    }

    DomainParticipantManager::DomainParticipantManager ()
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::DomainParticipantManager");
    }

    DomainParticipantManager::~DomainParticipantManager ()
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::~DomainParticipantManager");
    }

    IDL::traits< ::DDS::DomainParticipant>::ref_type
    DomainParticipantManager::get_participant (const ::DDS::DomainId_t domain_id,
      const std::string &qos_profile)
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::get_participant");

      DDS4CCM_LOG_DEBUG ("DomainParticipantManager::get_participant - "
        << "Searching DomainParticipant for domain <" << domain_id
        << "> with profile <" << qos_profile << ">");

      std::lock_guard<std::mutex> __guard (this->dps_mutex_);

      IdQosProfile const idqos = std::make_pair (qos_profile, domain_id);
      DomainParticipants_iterator const it_found = this->dps_.find (idqos);

      if (it_found != this->dps_.end () && it_found->second.first)
      {
        // Increment refcount on the domain participant
        uint32_t const refcount = ++it_found->second.second;
        IDL::traits< ::DDS::DomainParticipant>::ref_type const dp = it_found->second.first;
        DDS4CCM_LOG_DEBUG ("DomainParticipantManager::get_participant - "
          << "DomainParticipant found. domain <" << domain_id << "> - "
          << "profile <" << qos_profile << "> - ref_count <"
          << refcount << "> - handle <"
          << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
          << ">.");
        return dp;
      }
      DDS4CCM_LOG_DEBUG ("DomainParticipantManager::get_participant - "
        << "DomainParticipant for domain <" << domain_id << "> with profile <"
        << qos_profile << "> does not exist.");
      return {};
    }

    bool
    DomainParticipantManager::register_participant (
      ::DDS::DomainId_t domain_id,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DomainParticipant>::ref_type dp)
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::register_participant");

      if (!dp)
      {
        return false;
      }

      std::lock_guard<std::mutex> __guard (this->dps_mutex_);

      IdQosProfile const idqos = std::make_pair (qos_profile, domain_id);
      DomainParticipants_iterator const it_found = this->dps_.find (idqos);

      if (it_found == this->dps_.end())
      {
        try
        {
          DomainParticipantRefcount const dp_pair = std::make_pair (dp, 1);
          std::pair <DomainParticipants_iterator, bool> to_insert =
            this->dps_.insert (std::make_pair (idqos, std::move (dp_pair)));
          if (!to_insert.second)
          {
            DDS4CCM_LOG_ERROR ("DomainParticipantManager::register_participant - "
              << "Unable to insert a DomainParticipant for domain <"
              << domain_id << "> with profile <" << qos_profile << ">");
            return false;
          }
        }
        catch (const std::bad_alloc&)
        {
          DDS4CCM_LOG_ERROR ("DomainParticipantManager::register_participant - no memory");
          return false;
        }

        DDS4CCM_LOG_DEBUG ("DomainParticipantManager::register_participant - "
          << "Added a DomainParticipant for domain <"
          << domain_id << "> with profile <" << qos_profile << "> - handle <"
          << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
          << ">.");
        return true;

      }

      DDS4CCM_LOG_DEBUG ("DomainParticipantManager::register_participant - "
        << "Don't add participant for domain <" << domain_id << "> with profile <"
        << qos_profile << "> since it already exists as handle <"
        << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
        << ">");

      return false;
    }

    bool
    DomainParticipantManager::unregister_participant (
      ::DDS::DomainId_t domain_id,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DomainParticipant>::ref_type dp)
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::unregister_participant");

      if (!dp)
      {
        return false;
      }

      std::lock_guard<std::mutex> __guard (this->dps_mutex_);

      IdQosProfile const idqos = std::make_pair (qos_profile, domain_id);
      DomainParticipants_iterator const iter = this->dps_.find (idqos);

      if (iter != this->dps_.end ())
      {
        uint32_t const refcount = --iter->second.second;

        if (refcount == 0)
        {
          DDS4CCM_LOG_DEBUG ("DomainParticipantManager::unregister_participant - "
            << "Delete participant <"
            << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
            << "> for domain <" << domain_id << "> with profile <"
            << qos_profile << "> ref_count <0>");
          // Save to remove from list
          iter->second.first = nullptr;
          this->dps_.erase (iter);
        }
        else
        {

          DDS4CCM_LOG_DEBUG ("DomainParticipantManager::unregister_participant - "
            << "Decremented refcount for participant <"
            << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
            << "> for domain <" << domain_id << "> with profile <"
            << qos_profile << "> since " << "it's still used - ref_count <"
            << refcount << ">");
          return false;
        }
      }

      return true;
    }

    bool
    DomainParticipantManager::close ()
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::close");

      if (this->dps_.empty ())
        {
          DDS4CCM_LOG_DEBUG ("DomainParticipantManager::close - "
            << "No participants anymore, shutting down DDS.");

          ::DDS::ReturnCode_t const retcode =
            ::DDS::traits< ::DDS::DomainParticipantFactory>::get_instance ()->finalize_instance ();

          if (retcode != ::DDS::RETCODE_OK)
          {
            DDS4CCM_LOG_ERROR ("DomainParticipantManager::close - "
              << "Error finalizing domain participant factory - return code <"
              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
              << ">");
          }

          return true;
        }
      else
        {
          DDS4CCM_LOG_DEBUG ("DomainParticipantManager::close - "
            << "Not shutting down DDS, still <" << this->dps_.size() << "> participants in existence");

          return false;
        }
    }
  }
}
