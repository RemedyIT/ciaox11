// -*- C++ -*-
/**
 * @file    dds4ccm_writer_t.cpp
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM Writer implementation for DDS4CCM4CIAOX11
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_utils.h"
#include "dds4ccm/impl/dds4ccm_coherent_changes_guard.h"
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_instance_handle_manager_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename WRITER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Writer_T<WRITER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Writer_T (
      IDL::traits< CORBA::Object >::weak_ref_type component)
      : FacetBase<WRITER_TYPE> (component)
      , InstanceHandleManager_T<WRITER_TYPE, TOPIC_TYPE> (component)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Writer_T::Writer_T");
    }

    template <typename WRITER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Writer_T<WRITER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::write_i (
      const TOPIC_TYPE &datum,
      const ::DDS::InstanceHandle_t& instance_handle,
      typename TOPIC_SEQ_TYPE::size_type index)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Writer_T::write_i");

      ::DDS::ReturnCode_t const retcode =
        this->dds_writer_->write (datum, instance_handle);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("Writer_T::write_i - "
          << "Write unsuccessful, received error code <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        throw CCM_DDS::InternalError (
            retcode,
            ACE_Utils::truncate_cast< ::CCM_DDS::DataNumber_t> (index));
      }
    }

    template <typename WRITER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Writer_T<WRITER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::write_one (
      const TOPIC_TYPE &an_instance,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Writer_T::write_one");

      this->write_i (an_instance, instance_handle, 0);

      DDS4CCM_LOG_DEBUG ("Writer_T::write_one - Write successful.");
    }

    template <typename WRITER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Writer_T<WRITER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::write_many (
      const TOPIC_SEQ_TYPE &instances)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::Writer_T::write_many");

      IDL::traits< ::DDS::Publisher >::ref_type pub = this->dds_writer_->get_publisher ();
      if (!pub)
      {
        DDS4CCM_LOG_ERROR ("Writer_T::write_many - "
          << "Publisher on DataWriter seems to be NIL.");
        throw CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 0);
      }

      Coherent_Changes_Guard guard (
        pub,
        this->is_coherent_write_);

      DDS4CCM_LOG_DEBUG ("Writer_T::write_many - Preparing to write to DDS.");

      typename TOPIC_SEQ_TYPE::size_type index = 0;
      for (const TOPIC_TYPE& vt : instances)
      {
        this->write_i (vt, ::DDS::HANDLE_NIL, index++);
      }

      DDS4CCM_LOG_DEBUG ("Writer_T::write_many - Write successful.");
    }

    template <typename WRITER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Writer_T<WRITER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::is_coherent_write ()
    {
      return this->is_coherent_write_;
    }

    template <typename WRITER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Writer_T<WRITER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::is_coherent_write (
      bool value)
    {
      this->is_coherent_write_ = value;
    }
  }
}
