// -*- C++ -*-
/**
 * @file    dds4ccm_updater_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector Updater
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_UPDATER_T_H_
#define DDS4CCM_UPDATER_T_H_

#include "dds4ccm/impl/dds4ccm_instance_handle_manager_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename UPDATER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class Updater_T final
      : public virtual InstanceHandleManager_T<UPDATER_TYPE, TOPIC_TYPE>
    {
    public:
      /// Constructor
      explicit Updater_T (IDL::traits< CORBA::Object >::weak_ref_type component);

      /// Destructor
      virtual ~Updater_T () = default;

      /**
       * @name updater operations
       * Spec defined Updater operations.
       */
      //@{
      virtual void
      create_one (const TOPIC_TYPE& datum) override;

      virtual void
      update_one (
        const TOPIC_TYPE& datum,
        const ::DDS::InstanceHandle_t& instance_handle) override;

      virtual void
      delete_one (
        const TOPIC_TYPE& datum,
        const ::DDS::InstanceHandle_t& instance_handle) override;

      virtual void
      create_many (
        const TOPIC_SEQ_TYPE& data) override;

      virtual void
      update_many (
        const TOPIC_SEQ_TYPE& data) override;

      virtual void
      delete_many (
        const TOPIC_SEQ_TYPE& data) override;
      //@}

      /**
       * @name is_global_scope
       * Getter for is_global_scope
       */
      //@{
      virtual bool
      is_global_scope () override;
      //@}

      /**
       * @name is_coherent_write
       * Accessors for is_coherent_write
       */
      //@{
      virtual bool
      is_coherent_write () override;

      virtual void
      is_coherent_write (
        bool value) override;
      //@}

    private:
      bool is_global_scope_ { false };
      bool is_coherent_write_ { false };

      /**
        * @name Updater private helper methods
        */
      //@{
      void
      create_i (
        const TOPIC_TYPE& datum,
        typename TOPIC_SEQ_TYPE::size_type index);

      void
      update_i (
        const TOPIC_TYPE& an_instance,
        const ::DDS::InstanceHandle_t& instance_handle,
        typename TOPIC_SEQ_TYPE::size_type index);

      void
      delete_i (
        const TOPIC_TYPE& an_instance,
        const ::DDS::InstanceHandle_t& instance_handle,
        typename TOPIC_SEQ_TYPE::size_type index);

      ::DDS::InstanceHandle_t
      determine_instance (
        const TOPIC_TYPE& an_instance,
        const ::DDS::InstanceHandle_t& instance_handle);

      void
      check_already_created (
        const TOPIC_SEQ_TYPE& data);

      void
      check_existence (
        const TOPIC_SEQ_TYPE& data);
      //@}


      Updater_T() = delete;
      Updater_T(const Updater_T&) = delete;
      Updater_T(Updater_T&&) = delete;
      Updater_T& operator=(const Updater_T&) = delete;
      Updater_T& operator=(Updater_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_updater_t.cpp"

#endif /* DDS4CCM_UPDATER_T_H_ */
