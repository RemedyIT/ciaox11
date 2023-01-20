// -*- C++ -*-
/**
 * @file    dds4ccm_condition_manager.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_CONDITION_MANAGER_H_
#define DDS4CCM_CONDITION_MANAGER_H_

#include "dds4ccm/idl/dds4ccm_baseC.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

#include "dds4ccm/impl/dds4ccm_impl_export.h"

namespace CCM_DDS
{
  class QueryFilter;
}

namespace CIAOX11
{
  namespace DDS4CCM
  {
    /**
      * @class ConditionManager
      *
      * @brief Helper class
      *
      * Manages the read and query conditions for the Getter,
      * Reader and listeners.
      */
    class DDS4CCM_IMPL_Export ConditionManager
    {
    public:
      /// Constructor
      ConditionManager () = default;

      /// Destructor
      ~ConditionManager () = default;

      /// Returns the read condition in general
      IDL::traits<::DDS::ReadCondition>::ref_type read_condition ();

      /// Returns the query condition for the getter
      IDL::traits<::DDS::QueryCondition>::ref_type query_condition_getter ();

      /// Returns the query condition for the reader
      IDL::traits<::DDS::QueryCondition>::ref_type query_condition_reader ();

      /// Returns the query condition for the listener
      IDL::traits<::DDS::QueryCondition>::ref_type query_condition_listener ();

      /**
        * Used in the Reader in order to check whether the
        * user has supplied the correct handle with the type specific
        * instance. See the DDS4CCM spec for more info.
        *
        * Checks whether two DDS-handles are equal. If no error
        * occurs and the lookup_handle exists, this method will return
        * the lookup_handle.
        *
        * If instance_handle != DDS::HANDLE_NIL and when
        * instance_handle != lookup_handle, a
        * ::CCM_DDS::InternalError exception is called.
        * Error will be ::DDS::RETCODE_ERROR
        *
        * When the lookup_hnd is DDS::HANDLE_NIL,
        * a ::CCM_DDS::NonExistent exception is thrown.
        */
      ::DDS::InstanceHandle_t check_handle (
        const ::DDS::InstanceHandle_t& instance_handle,
        const ::DDS::InstanceHandle_t& lookup_handle);

      /**
        * Getter functionality.
        * Creates a read_condition for the getter.
        * It will also initialize the waitset and attaches the
        * read_condition to the waitset.
        */
      void init_read_condition ();

      /**
        * Getter functionality, waits for the attached conditions.
        * Only returns true when one of the getter conditions has
        * been triggered and we have data
        */
      bool wait (const ::DDS::Duration_t &time_out);

      /**
        * Returns the internal filter. This is the DDS4CCM QueryFilter
        * (a representation of the DDS query).
        *
        * If the QueryFilter hasn't been initialized, a ::CCM_DDS::InternalError
        * exception with error code ::DDS::RETCODE_ERROR is thrown.
        */
      CCM_DDS::QueryFilter query ();

      /**
        * Sets the DDS4CCM query filter.
        * The following rules apply when a filter is set:
        *
        * If there's a read condition set, this will be removed.
        * The read condition is replaced by a query condition.
        *
        * If there're no query conditions yet (i.e. the filter hasn't
        * been set before), three query conditions are created:
        * 1. One for the Getter
        * 2. One for the Reader
        * 3. One for the Listener
        * Each query condition has it's own sample_state,
        * instance_state and view_state set but the filters are
        * the same.
        *
        * Off course the query condition for the getter will be
        * attached to the waitset.
        *
        * If the internal filter has already been set, this method sets
        * the parameters for this filter on all three query conditions.
        *
        * If the filter expression (the actual query) is empty, all three query
        * conditions will be removed (the query condition for the getter will be
        * detached from the waitset first) and the initial read condition will
        * created (see init_readcondition()).
        */
      void query (const CCM_DDS::QueryFilter &filter);

      /**
        * Sets the internal datareader.
        * Applies to Getter, Reader and Listener
        */
      void set_dds_entity (IDL::traits<::DDS::DataReader>::ref_type dr);

      /**
        * Retrieves the internal datareader.
        */
      IDL::traits<::DDS::DataReader>::ref_type get_dds_entity ();

      /**
        * Detaches conditions from the waitset and
        * removes all conditions by calling
        * delete_readcondition on the DataReader.
        */
      void passivate ();

    private:
      IDL::traits<::DDS::DataReader>::ref_type dr_ {};

      /**
       * Internal waitset. The getter extended port uses this waitset to control
       * reading from DDS.
       */
      IDL::traits<::DDS::WaitSet>::ref_type ws_ {};

      /**
        * Different QueryConditions since the sample mask
        * differs per extended port (reader/getter/listener).
        */
      IDL::traits<::DDS::QueryCondition>::ref_type qc_reader_ {};
      IDL::traits<::DDS::QueryCondition>::ref_type qc_getter_ {};
      IDL::traits<::DDS::QueryCondition>::ref_type qc_listener_ {};

      /**
       * When no query condition has been used, the read condition
       * 'takes over'. This read condition (for the getter) is then
       * attached to the internal waitset.
       */
      IDL::traits<::DDS::ReadCondition>::ref_type rd_condition_ {};

      /**
        * Will create the waitset if not already created.
        */
      IDL::traits<::DDS::WaitSet>::ref_type waitset ();

      /**
        * Removes the internal (read/query) condition by invoking
        * delete_condition on the DataReader.
        */
      void remove_condition (
        IDL::traits<::DDS::QueryCondition>::ref_type qc,
        const std::string &type);

      /**
        * Calling 'remove_condition' for each query and read
        * condition.
        *
        * The query condition for the getter will be detached from
        * the waitset first.
        */
      void remove_conditions ();

      /**
        * Getter functionality.
        *
        * Attaches the query condition for the getter to the
        * waitset. It the waitset doesn't exist, it will be
        * created.
        */
      void attach_querycondition ();

      /**
        * Generic method which sets the parameters of the given
        * filter on the given query condition.
        */
      void
      set_parameters (
        const ::CCM_DDS::QueryFilter &filter,
        IDL::traits<::DDS::QueryCondition>::ref_type qc);

      ConditionManager(const ConditionManager&) = delete;
      ConditionManager(ConditionManager&&) = delete;
      ConditionManager& operator=(const ConditionManager&) = delete;
      ConditionManager& operator=(ConditionManager&&) = delete;
    };

    using SharedConditionManager = std::shared_ptr<ConditionManager>;
  }
}

#endif /* DDS4CCM_CONDITION_MANAGER_H_ */
