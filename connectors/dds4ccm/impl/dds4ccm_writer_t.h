// -*- C++ -*-
/**
 * @file    dds4ccm_writer_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_WRITER_T_H_
#define DDS4CCM_WRITER_T_H_

#include "dds4ccm/impl/dds4ccm_instance_handle_manager_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename WRITER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class Writer_T
      : public virtual InstanceHandleManager_T<WRITER_TYPE, TOPIC_TYPE>
    {
    public:
      explicit Writer_T (IDL::traits<CORBA::Object>::weak_ref_type component);
      ~Writer_T () override = default;

      void
      write_one (
        const TOPIC_TYPE &an_instance,
        const ::DDS::InstanceHandle_t& instance_handle) override;

      void write_many (const TOPIC_SEQ_TYPE& instances) override;

      /**
       * @name is_coherent_write
       * Accessors for is_coherent_write
       */
      //@{
      bool is_coherent_write () override;
      void is_coherent_write (bool value) override;
      //@}

    private:
      void write_i (
        const TOPIC_TYPE &datum,
        const ::DDS::InstanceHandle_t& instance_handle,
        typename TOPIC_SEQ_TYPE::size_type index);

      bool is_coherent_write_ { false };

      Writer_T() = delete;
      Writer_T(const Writer_T&) = delete;
      Writer_T(Writer_T&&) = delete;
      Writer_T& operator=(const Writer_T&) = delete;
      Writer_T& operator=(Writer_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_writer_t.cpp"

#endif /* DDS4CCM_WRITER_T_H_ */
