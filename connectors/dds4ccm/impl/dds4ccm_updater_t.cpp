// -*- C++ -*-
/**
 * @file    dds4ccm_updater_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector Updater
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/impl/dds4ccm_coherent_changes_guard.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Updater_T (
      IDL::traits<CORBA::Object>::weak_ref_type component)
      : FacetBase<UPDATER_TYPE> (component)
      , InstanceHandleManager_T<UPDATER_TYPE, TOPIC_TYPE> (component)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_T::Updater_T");
    }


    /**
      * @name Updater private helper methods
      */
    //@{
    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::create_i (
      const TOPIC_TYPE& datum,
      typename TOPIC_SEQ_TYPE::size_type index)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::create_i");

      ::DDS::InstanceHandle_t const hnd =
        this->dds_writer_->register_instance (datum);
      if (hnd == ::DDS::HANDLE_NIL)
      {
        DDS4CCM_LOG_ERROR ("CIAOX11::DDS4CCM::Updater_t::create_i - "
          "Unable to register instance, nil handle");
        throw ::CCM_DDS::InternalError (
            ::DDS::RETCODE_ERROR,
            ACE_Utils::truncate_cast< ::CCM_DDS::DataNumber_t> (index));
      }

      this->update_i (datum, hnd, index);
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::update_i (
      const TOPIC_TYPE& an_instance,
      const ::DDS::InstanceHandle_t& instance_handle,
      typename TOPIC_SEQ_TYPE::size_type index)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::update_i");

      ::DDS::ReturnCode_t const retcode  =
          this->dds_writer_->write (an_instance, instance_handle);
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("CIAOX11::DDS4CCM::Updater_t::update_i - "
          << "Unable to update data, error <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CCM_DDS::InternalError (
            retcode,
            ACE_Utils::truncate_cast< ::CCM_DDS::DataNumber_t> (index));
      }
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::delete_i (
      const TOPIC_TYPE& an_instance,
      const ::DDS::InstanceHandle_t& instance_handle,
      typename TOPIC_SEQ_TYPE::size_type index)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::delete_i");

      ::DDS::InstanceHandle_t hnd = instance_handle;
      if (instance_handle == ::DDS::HANDLE_NIL)
      {
        hnd = this->dds_writer_->lookup_instance (an_instance);
      }

      ::DDS::ReturnCode_t retcode = this->dds_writer_->dispose (an_instance, hnd);
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("CIAOX11::DDS4CCM::Updater_t::delete_i - "
          << "Unable to dispose instance, error <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CCM_DDS::InternalError (
            retcode,
            ACE_Utils::truncate_cast< ::CCM_DDS::DataNumber_t> (index));
      }

      retcode = this->dds_writer_->unregister_instance (an_instance, hnd);
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("CIAOX11::DDS4CCM::Updater_t::delete_i - "
          << "Unable to unregister instance, error <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CCM_DDS::InternalError (
            retcode,
            ACE_Utils::truncate_cast< ::CCM_DDS::DataNumber_t> (index));
      }
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::DDS::InstanceHandle_t
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::determine_instance (
      const TOPIC_TYPE& an_instance,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      ::DDS::InstanceHandle_t hnd = instance_handle;
      if (hnd == ::DDS::HANDLE_NIL)
      {
        hnd = this->dds_writer_->lookup_instance (an_instance);
      }
      else
      {
        // Check explicitly if the instance handle matches the instance, this
        // is not checked by, for instance, RTI DDS
        ::DDS::InstanceHandle_t const instance_handle_l =
            this->dds_writer_->lookup_instance (an_instance);

        if (hnd != instance_handle_l)
        {
          DDS4CCM_LOG_ERROR ("CIAOX11::DDS4CCM::Updater_t::update_one - "
            "Given data does not match the given instance handle.");
          throw ::CCM_DDS::InternalError (::DDS::RETCODE_BAD_PARAMETER, 0);
        }
      }

      if (hnd == ::DDS::HANDLE_NIL)
      {
        DDS4CCM_LOG_ERROR ("CIAOX11::DDS4CCM::Updater_t::update_one - "
          "Instance handle does not exist.");
        throw CCM_DDS::NonExistent ();
      }
      return hnd;
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::check_already_created (
      const TOPIC_SEQ_TYPE& data)
    {
      ::CCM_DDS::AlreadyCreated exception;
      typename TOPIC_SEQ_TYPE::size_type index = 0;
      for (TOPIC_TYPE const &tt : data)
      {
        if (this->dds_writer_->lookup_instance (tt) != ::DDS::HANDLE_NIL)
        {
          exception.indexes ().push_back (
              ACE_Utils::truncate_cast< ::CCM_DDS::DataNumber_t> (index));
        }
        ++index;
      }

      if (!exception.indexes ().empty ())
      {
        throw exception;
      }
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::check_existence (
        const TOPIC_SEQ_TYPE& data)
    {
      ::CCM_DDS::NonExistent exception;

      typename TOPIC_SEQ_TYPE::size_type index = 0;
      for (TOPIC_TYPE const &tt : data)
      {
        if (this->dds_writer_->lookup_instance (tt) == ::DDS::HANDLE_NIL)
        {
          exception.indexes ().push_back (
              ACE_Utils::truncate_cast< ::CCM_DDS::DataNumber_t> (index));
        }
        ++index;
      }

      if (!exception.indexes ().empty ())
      {
        throw exception;
      }
    }
    //@}

    /**
      * @name Updater public interface methods
      */
    //@{
    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::create_one (
      const TOPIC_TYPE& datum)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::create_one");
      ::DDS::InstanceHandle_t const hnd = this->dds_writer_->lookup_instance (datum);
      if (hnd != ::DDS::HANDLE_NIL)
      {
        DDS4CCM_LOG_ERROR ("CIAOX11::DDS4CCM::Updater_t::create_one - "
          << "Instance already registered with handle <"
          << IDL::traits< ::DDS::InstanceHandle_t >::write (hnd)
          << ">.");
        throw CCM_DDS::AlreadyCreated ();
      }
      this->create_i (datum, 0);
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::update_one (
      const TOPIC_TYPE& datum,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::update_one");

      this->update_i (
        datum,
        this->determine_instance (datum, instance_handle),
        0);
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::delete_one (
      const TOPIC_TYPE& datum,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::delete_one");

      this->delete_i (
        datum,
        this->determine_instance (datum, instance_handle),
        0);
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::create_many (
      const TOPIC_SEQ_TYPE& data)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::create_many");

      // Check for existence of instances.
      // Might throw a CCM_DDS::AlreadyCreated exception
      this->check_already_created (data);

      IDL::traits< ::DDS::Publisher >::ref_type pub =
        this->dds_writer_->get_publisher ();
      if (!pub)
      {
        DDS4CCM_LOG_ERROR ("Updater_T::update_many - "
          << "Publisher on DataWriter seems to be NIL.");
        throw CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 0);
      }
      Coherent_Changes_Guard guard (
        pub,
        this->is_coherent_write_);

      typename TOPIC_SEQ_TYPE::size_type index = 0;
      for (const TOPIC_TYPE& tt : data)
      {
        this->create_i (tt, index++);
      }
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::update_many (
      const TOPIC_SEQ_TYPE& data)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::update_many");

      // Check for existence of instances.
      // Might throw a CCM_DDS::NonExistent exception
      this->check_existence (data);

      typename TOPIC_SEQ_TYPE::size_type index = 0;
      for (const TOPIC_TYPE& tt : data)
      {
        this->update_i (tt,
          ::DDS::HANDLE_NIL,
          index++);
      }
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::delete_many (
      const TOPIC_SEQ_TYPE& data)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Updater_t::delete_many");

      // Check for existence of instances.
      // Might throw a CCM_DDS::NonExistent exception
      this->check_existence (data);

      typename TOPIC_SEQ_TYPE::size_type index = 0;
      for (const TOPIC_TYPE& tt : data)
      {
        this->delete_i (tt,
          ::DDS::HANDLE_NIL,
          index++);
      }
    }
    //@}

    /**
      * @name Updater attributes
      */
    //@{
    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::is_global_scope ()
    {
      return this->is_global_scope_;
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::is_coherent_write ()
    {
      return this->is_coherent_write_;
    }

    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Updater_T<UPDATER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::is_coherent_write (
      bool value)
    {
      this->is_coherent_write_ = value;
    }
    //@}

  }
}
