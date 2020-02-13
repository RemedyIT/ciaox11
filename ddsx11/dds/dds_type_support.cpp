// -*- C++ -*-
/**
 * @file    dds_type_support.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_type_support.h"

namespace DDSX11
{
  DDS_TypeFactory_i::~DDS_TypeFactory_i ()
  {
  }

  DDS_TypeFactory_i_ref::DDS_TypeFactory_i_ref (
    std::shared_ptr<DDS_TypeFactory_i> tf)
    : tf_ (tf)
  {
    DDSX11_LOG_TRACE ("DDS_TypeFactory_i_ref::DDS_TypeFactory_i_ref");
  }

  std::shared_ptr<DDS_TypeFactory_i>
  DDS_TypeFactory_i_ref::get_factory ()
  {
    DDSX11_LOG_TRACE ("DDS_TypeFactory_i_ref::get_typefactory");
    return tf_;
  }

  uint32_t
  DDS_TypeFactory_i_ref::_inc_ref ()
  {
    DDSX11_LOG_TRACE ("DDS_TypeFactory_i_ref::_inc_ref");
    return ++this->ref_count_;
  }

  uint32_t
  DDS_TypeFactory_i_ref::_dec_ref ()
  {
    DDSX11_LOG_TRACE ("DDS_TypeFactory_i_ref::_dec_ref");
    return --this->ref_count_;
  }


  // -------------------------------------------------------------------------
  DDS_TypeSupport_i::participantfactories DDS_TypeSupport_i::participant_factories;

  std::shared_ptr<DDS_TypeFactory_i>
  DDS_TypeSupport_i::get_factory_i (
    IDL::traits< ::DDS::DomainParticipant>::ref_type dp,
    const std::string &type)
  {
    DDSX11_LOG_TRACE ("DDS_TypeSupport_i::get_factory_i");

    participantfactories::iterator entry =
      participant_factories.find (
        dp->get_instance_handle ().value ());
    if (entry != participant_factories.end ())
      {
        // We have found the domain participant, now search for a type factory
        // within the domain participant
        typefactories::iterator it = entry->second.find (type);
        if (it != entry->second.end ())
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::get_factory_i - "
            << "A factory for domain participant <"
            << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
            << "> of type <" << type << "> has been found.");
            return it->second->get_factory ();
          }
      }

    DDSX11_IMPL_LOG_ERROR ("DDS_TypeSupport_i::get_factory_i - "
      << "A factory for domain participant <"
      << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
      << "> of type <" << type << "> could not be found.");

    return nullptr;
  }

  bool
  DDS_TypeSupport_i::register_type (
    IDL::traits< ::DDS::DomainParticipant>::ref_type dp,
    const std::string &type,
    const std::shared_ptr<DDS_TypeFactory_i> &factory)
  {
    DDSX11_LOG_TRACE ("DDS_TypeSupport_i::register_type");

    participantfactories::iterator dp_entry =
      participant_factories.find (dp->get_instance_handle ().value ());
    if (dp_entry == participant_factories.end ())
      {
        // The domain participant has not been found, insert the domain
        // participant first
        std::pair<participantfactories::iterator, bool> dp_ret =
          participant_factories.insert (
            participantfactories::value_type (
              dp->get_instance_handle ().value (), typefactories ()));
        if (!dp_ret.second)
          {
            DDSX11_IMPL_LOG_ERROR ("DDS_TypeSupport_i::register_type - "
              << "Unable to create DomainParticipant entry: type <"
              << type << "> - DomainParticipant <"
              << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
              << ">");
            return false;
          }
        dp_entry = dp_ret.first;
      }

    // DomainParticipant is in the list or has been added
    // search for the given type
    typefactories::iterator tf_entry = dp_entry->second.find (type);
    bool retval = false;
    if (tf_entry == dp_entry->second.end ())
      {
        // Factory not registered for specified type.
        // Register it
        std::unique_ptr<DDS_TypeFactory_i_ref> factory_ref =
          std::make_unique<DDS_TypeFactory_i_ref> (factory);
        std::pair <typefactories::iterator, bool> tf_ret =
          dp_entry->second.insert(typefactories::value_type (type, std::move (factory_ref)));

        if (tf_ret.second)
          {
            DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::register_type - "
              << "Created factory entry for type <" << type << "> for "
              << "participant <"
              << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
              << ">");
            // Returning true in case we first register the type, that way the
            // caller knows we also have to register the type with DDS
            retval = true;
          }
        else
          {
            DDSX11_IMPL_LOG_ERROR ("DDS_TypeSupport_i::register_type - "
              << "Unable to create -new- factory entry type <" << type
              << "> for participant <"
              << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
              << ">");
          }
      }
    else
      {
        uint32_t const refcount = tf_entry->second->_inc_ref ();
        DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::register_type - "
          << "Incremented refcount to <" << refcount
          << "> for type-factory " << "for participant <"
          << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
          << "> since it already exists for "
          << "type <" << type << ">");
      }
    return retval;
  }

  bool
  DDS_TypeSupport_i::unregister_type (
    IDL::traits< ::DDS::DomainParticipant>::ref_type dp,
    const std::string &type)
  {
    DDSX11_LOG_TRACE ("DDS_TypeSupport_i::unregister_type");

    bool retval = false;
    participantfactories::iterator dp_entry =
      participant_factories.find (dp->get_instance_handle().value ());

    if (dp_entry != participant_factories.end ())
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::unregister_type - "
          << "Found entry for participant <"
          << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
          << "> and type <" << type << ">");
        // Found the domain participant
        typefactories::iterator it = dp_entry->second.find (type);
        if (it != dp_entry->second.end ())
          {
            uint32_t const refcount = it->second->_dec_ref ();
            if (refcount == 0)
              {
                // We return true in this case because at this moment we don't
                // use the type anymore, the caller can now unregister it from
                // the DDS vendor
                retval = true;
                // Erase it from the list will decrement the use_count with one.
                DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::unregister_type - "
                  << "Decremented refcount on factory for participant <"
                  << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
                  << "> and type <" << type << ">. Refcount dropped to zero");

                it->second = nullptr;
                dp_entry->second.erase (it);
                if (dp_entry->second.size () == 0UL)
                  { // no more entries -> remove the participant from
                    // the list
                    participant_factories.erase (dp_entry);

                    DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::unregister_type - "
                      << "Erased participant entry for participant <"
                      << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
                      << ">, no type factories left anymore");
                  }
              }
            else
              {
                DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::unregister_type - "
                  << "Decremented refcount to <" << refcount
                  << "> for factory for participant <"
                  << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
                  << "> and type <" << type << ">");
              }
          }
        else
          {
            DDSX11_IMPL_LOG_ERROR ("DDS_TypeSupport_i::unregister_type - "
              << "Could not find the correct factory belonging to participant <"
              << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
              << "> and type <" << type << ">. Unable to remove.");
          }
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_TypeSupport_i::unregister_type - "
          << "Could not find the entry for participant <"
          << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
          << ">. Unable to remove.");
      }
    return retval;
  }

  IDL::traits< ::DDS::DataWriter>::ref_type
  DDS_TypeSupport_i::create_datawriter (
    IDL::traits< ::DDS::DomainParticipant>::ref_type dp,
    const std::string& type_name,
    DDS_Native::DDS::DataWriter* dw)
  {
    DDSX11_LOG_TRACE ("DDS_TypeSupport_i::create_datawriter");

    std::shared_ptr<DDS_TypeFactory_i> f = get_factory_i (dp, type_name);
    if (f)
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::create_datawriter - "
          << "Type factory found for type <" << type_name << "> for "
          << "participant <"
          << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
          << ">");

        return f->create_datawriter (dw);
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_TypeSupport_i::create_datawriter - "
          << "Error creating DDS_Native::DDS::DataWriter for type <" << type_name
          << "> for participant <"
          << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
          << ">");
      }

    return nullptr;
  }

  IDL::traits< ::DDS::DataReader>::ref_type
  DDS_TypeSupport_i::create_datareader (
    IDL::traits< ::DDS::DomainParticipant>::ref_type dp,
    const std::string& type_name,
    DDS_Native::DDS::DataReader* dr)
  {
    DDSX11_LOG_TRACE ("DDS_TypeSupport_i::create_datareader");

    std::shared_ptr<DDS_TypeFactory_i> f = get_factory_i (dp, type_name);
    if (f)
      {
        DDSX11_IMPL_LOG_DEBUG ("DDS_TypeSupport_i::create_datareader - "
          << "Created DDS_Native::DDS::DataReader for type <" << type_name
          << "> for participant <"
          << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
          << ">");

        return f->create_datareader (dr);
      }
    else
      {
        DDSX11_IMPL_LOG_ERROR ("DDS_TypeSupport_i::create_datareader - "
          << "Error creating DDS_Native::DDS::DataReader for type <" << type_name
          << "> for participant <"
          << IDL::traits< ::DDS::Entity >::write<entity_formatter> (dp)
          << ">");
      }

    return nullptr;
  }

  void
  DDS_TypeSupport_i::close ()
  {
    DDSX11_LOG_TRACE ("DDS_TypeSupport_i::close");

    for (participantfactories::iterator i = participant_factories.begin ();
        i != participant_factories.end ();
        ++i)
      {
        for (typefactories::iterator j = i->second.begin ();
            j != i->second.end ();
            ++j)
          {
            j->second = nullptr;
          }
        i->second.clear ();
      }
    participant_factories.clear ();
  }
}

