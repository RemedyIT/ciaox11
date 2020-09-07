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

      return &instance_;
    }

    //============================================================
    // DomainParticipantManager::DDSParticipantTopic::DDSParticipantTopic
    //============================================================
    DomainParticipantManager::DDSParticipantTopic::DDSParticipantTopic (
      IDL::traits< ::DDS::DomainParticipant>::ref_type dp)
      : dp_ (std::move(dp))
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::DDSParticipantTopic::DDSParticipantTopic");
    }

    DomainParticipantManager::DDSParticipantTopic::~DDSParticipantTopic ()
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::DDSParticipantTopic::~DDSParticipantTopic");
    }

    IDL::traits< ::DDS::DomainParticipant>::ref_type
    DomainParticipantManager::DDSParticipantTopic::get_participant ()
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::DDSParticipantTopic::get_participant");

      return this->dp_;
    }

    uint32_t
    DomainParticipantManager::DDSParticipantTopic::_ref_count () const
    {
      return this->ref_count_;
    }

    void
    DomainParticipantManager::DDSParticipantTopic::_inc_ref ()
    {
      ++this->ref_count_;
    }

    void
    DomainParticipantManager::DDSParticipantTopic::_dec_ref ()
    {
      --this->ref_count_;
    }


    //============================================================
    // DomainParticipantManager::DomainParticipantManager
    //============================================================
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

      IdQosProfile idqos = std::make_pair (qos_profile, domain_id);
      DomainParticipants_iterator it_found = this->dps_.find (idqos);

      if (it_found != this->dps_.end () && it_found->second)
      {
        it_found->second->_inc_ref ();
        IDL::traits< ::DDS::DomainParticipant>::ref_type dp =
          it_found->second->get_participant ();
        DDS4CCM_LOG_DEBUG ("DomainParticipantManager::get_participant - "
          << "DomainParticipant found. domain <" << domain_id << "> - "
          << "profile <" << qos_profile << "> - ref_count <"
          << it_found->second->_ref_count () << "> - handle <"
          << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
          << ">.");
        return dp;
      }
      DDS4CCM_LOG_DEBUG ("DomainParticipantManager::get_participant - "
        << "DomainParticipant for domain <" << domain_id << "> with profile <"
        << qos_profile << "> does not exist.");
      return nullptr;
    }

    bool
    DomainParticipantManager::register_participant (
      ::DDS::DomainId_t domain_id,
      const std::string &qos_profile,
      IDL::traits< ::DDS::DomainParticipant>::ref_type dp)
    {
      DDS4CCM_LOG_TRACE ("DomainParticipantManager::register_participant");

      std::lock_guard<std::mutex> __guard (this->dps_mutex_);

      if (!dp)
      {
        return false;
      }

      IdQosProfile const idqos = std::make_pair (qos_profile, domain_id);
      DomainParticipants_iterator const it_found = this->dps_.find (idqos);

      if (it_found == this->dps_.end())
      {
        try
        {
          std::unique_ptr<DDSParticipantTopic> dt =
            std::make_unique<DDSParticipantTopic> (dp);
          std::pair <DomainParticipants_iterator, bool> to_insert =
            this->dps_.insert (std::make_pair (idqos, std::move (dt)));
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

      std::lock_guard<std::mutex> __guard (this->dps_mutex_);

      if (!dp)
      {
        return false;
      }

      IdQosProfile const idqos = std::make_pair (qos_profile, domain_id);
      DomainParticipants_iterator const iter = this->dps_.find (idqos);

      if (iter != this->dps_.end ())
      {
        if (iter->second->_ref_count () == 1)
        {
          DDS4CCM_LOG_DEBUG ("DomainParticipantManager::unregister_participant - "
            << "Delete participant <"
            << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
            << "> for domain <" << domain_id << "> with profile <"
            << qos_profile << "> since ref_count is one.");

          // Save to remove from list
          iter->second = nullptr;
          this->dps_.erase (iter);
        }
        else
        {
          DDS4CCM_LOG_DEBUG ("DomainParticipantManager::unregister_participant - "
            << "Decrement refcount for participant <"
            << IDL::traits< ::DDS::Entity>::write<entity_formatter> (dp)
            << "> for domain <" << domain_id << "> with profile <"
            << qos_profile << "> since " << "it's still used - ref_count is <"
            << iter->second->_ref_count () << ">");
          iter->second->_dec_ref ();
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

          ::DDS::ReturnCode_t retcode =
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

      return false;
    }
  }
}
