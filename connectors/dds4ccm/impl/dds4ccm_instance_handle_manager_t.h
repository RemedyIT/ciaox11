// -*- C++ -*-
/**
 * @file    dds4ccm_instance_handle_manager_t.h
 * @author  Marcel Smit
 *
 * @brief   Base class for the publishing side of the DDS4CCM connector.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_WRITER_BASE_T_H_
#define DDS4CCM_WRITER_BASE_T_H_

#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename BASE_TYPE, typename TOPIC_TYPE>
    class InstanceHandleManager_T
      : public virtual FacetBase< BASE_TYPE >
    {
    public:
      /// Constructor
      explicit InstanceHandleManager_T (
        IDL::traits<CORBA::Object>::weak_ref_type component);

      /// Destructor
      virtual ~InstanceHandleManager_T () = default;

      virtual ::DDS::InstanceHandle_t
      register_instance (
        const TOPIC_TYPE& datum) override;

      virtual void
      unregister_instance (
        const TOPIC_TYPE& datum,
        const ::DDS::InstanceHandle_t& instance_handle) override;

      void
      set_dds_writer (
        IDL::traits< ::DDS::DataWriter>::ref_type dds_writer);

      IDL::traits< ::DDS::DataWriter>::ref_type
      get_dds_writer ();

    protected:
      typename ::DDS::traits<TOPIC_TYPE>::typed_datawriter_ref_type dds_writer_ {};

    private:
      InstanceHandleManager_T() = delete;
      InstanceHandleManager_T(const InstanceHandleManager_T&) = delete;
      InstanceHandleManager_T(InstanceHandleManager_T&&) = delete;
      InstanceHandleManager_T& operator=(const InstanceHandleManager_T&) = delete;
      InstanceHandleManager_T& operator=(InstanceHandleManager_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_instance_handle_manager_t.cpp"

#endif /* DDS4CCM_WRITER_BASE_T_H_ */
