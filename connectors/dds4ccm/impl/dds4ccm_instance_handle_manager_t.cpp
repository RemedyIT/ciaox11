// -*- C++ -*-
/**
 * @file    dds4ccm_instance_handle_manager_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "dds4ccm/impl/dds4ccm_utils.h"
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_ccm_data_writer.h"
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename BASE_TYPE, typename TOPIC_TYPE>
    InstanceHandleManager_T<BASE_TYPE, TOPIC_TYPE>::InstanceHandleManager_T (
      IDL::traits< CORBA::Object >::weak_ref_type component)
      : FacetBase<BASE_TYPE> (component)
    {
    }

    template <typename BASE_TYPE, typename TOPIC_TYPE>
    ::DDS::InstanceHandle_t
    InstanceHandleManager_T<BASE_TYPE, TOPIC_TYPE>::register_instance (
      const TOPIC_TYPE& datum)
    {
      return this->dds_writer_->register_instance (datum);
    }

    template <typename BASE_TYPE, typename TOPIC_TYPE>
    void
    InstanceHandleManager_T<BASE_TYPE, TOPIC_TYPE>::unregister_instance (
      const TOPIC_TYPE& datum,
      const ::DDS::InstanceHandle_t& instance_handle)
    {
      this->dds_writer_->unregister_instance (datum, instance_handle);
    }

    template <typename BASE_TYPE, typename TOPIC_TYPE>
    void
    InstanceHandleManager_T<BASE_TYPE, TOPIC_TYPE>::set_dds_writer (
      IDL::traits< ::DDS::DataWriter >::ref_type dds_writer)
    {
      DDS4CCM_LOG_TRACE ("CIAOX11::DDS4CCM::InstanceHandleManager_T::set_dds_writer");

      this->dds_writer_ = ::DDS::traits<TOPIC_TYPE>::narrow (dds_writer);

      if (dds_writer && !this->dds_writer_)
      {
        DDS4CCM_LOG_ERROR ("InstanceHandleManager_T::set_dds_writer - "
          "narrow failed.");
        throw ::CORBA::INTERNAL ();
      }
    }

    template <typename BASE_TYPE, typename TOPIC_TYPE>
    IDL::traits< ::DDS::DataWriter >::ref_type
    InstanceHandleManager_T<BASE_TYPE, TOPIC_TYPE>::get_dds_writer ()
    {
      return this->dds_writer_;
    }
  }
}
