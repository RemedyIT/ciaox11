// -*- C++ -*-
/**
 * @file    dds4ccm_condition_manager.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_condition_manager.h"

#if !defined (X11_NLOGGING)
#include <chrono>
#endif

#include "dds4ccm/logger/dds4ccm_log.h"

#include "dds/dds_vendor_adapter.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    IDL::traits<::DDS::ReadCondition>::ref_type
    ConditionManager::read_condition ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::read_condition");

      return this->rd_condition_;
    }

    IDL::traits<::DDS::QueryCondition>::ref_type
    ConditionManager::query_condition_getter ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::query_condition_getter");

      return this->qc_getter_;
    }

    IDL::traits<::DDS::QueryCondition>::ref_type
    ConditionManager::query_condition_listener ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::query_condition_listener");

      return this->qc_listener_;
    }

    IDL::traits<::DDS::QueryCondition>::ref_type
    ConditionManager::query_condition_reader ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::query_condition_reader");

      return this->qc_reader_;
    }

    ::DDS::InstanceHandle_t
    ConditionManager::check_handle (
      const ::DDS::InstanceHandle_t& instance_handle,
      const ::DDS::InstanceHandle_t& lookup_handle)
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::check_handle");

      DDS4CCM_LOG_DEBUG ("ConditionManager::check_handle - "
        << "Checking instance handle <"
        << instance_handle
        << "> with lookup handle <"
        << lookup_handle
        << ">.");

      if (instance_handle != ::DDS::HANDLE_NIL && instance_handle != lookup_handle)
        throw CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 0);
      if (lookup_handle == ::DDS::HANDLE_NIL)
        throw CCM_DDS::NonExistent ();
      return lookup_handle;
    }

    void
    ConditionManager::init_read_condition ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::init_read_condition");

      // The read condition is there for the getter to use. The read condition
      // will be attached to the waitset so that the getter extended port is able
      // to read samples from DDS, according to the DDS4CCM spec.
      if (!this->rd_condition_)
      {
        this->rd_condition_ =
          this->dr_->create_readcondition (
                                ::DDS::NOT_READ_SAMPLE_STATE,
                                ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
                                ::DDS::ALIVE_INSTANCE_STATE | ::DDS::NOT_ALIVE_INSTANCE_STATE);

        if (!this->rd_condition_)
        {
          DDS4CCM_LOG_ERROR ("ConditionManager::init_read_condition - "
            "Error creating read condition.");
          throw ::CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 0);
        }
      }

      ::DDS::ReturnCode_t const retcode =
        this->waitset ()->attach_condition (this->rd_condition_);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("ConditionManager::init_read_condition - "
          << "Unable to attach read condition to waitset. Error <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CCM_DDS::InternalError (retcode, 0);
      }
      DDS4CCM_LOG_DEBUG ("ConditionManager::init_read_condition - "
        "Read condition created and attached to Waitset.");
    }

    CCM_DDS::QueryFilter
    ConditionManager::query ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::query");

      CCM_DDS::QueryFilter filter;

      // If there's a query condition available, there's a query set in DDS.
      // We use this query condition to fill the filter variable.
      // If no query has been set in the past, an empty filter is returned.
      if (this->qc_reader_)
      {
        filter.expression (
          this->qc_reader_->get_query_expression ());
        ::DDS::StringSeq parameters;
        ::DDS::ReturnCode_t const retcode =
          this->qc_reader_->get_query_parameters (parameters);

        if (retcode != ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_ERROR ("ConditionManager::query - "
            << "Failed to get query parameters : <"
            << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">.");
          throw CCM_DDS::InternalError (retcode, 0);
        }
        filter.parameters (parameters);
      }
      return filter;
    }

    void
    ConditionManager::query (
      const ::CCM_DDS::QueryFilter &filter)
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::query");

      // Since the readcondition for the getter is always created (at start up),
      // this should be removed first. Instead of a readcondition, there should
      // be a QueryCondition attached to the waitset
      if (this->rd_condition_)
      {
        // Getter functionality
        // First remove the existing conditions from the waitset
        // Than create a (query) condition and attach it to the waitset
        // instead of the readcondition
        this->remove_conditions ();
      }

      // Check the main query condition. If this has not been set, we need
      // to create the query condition for all three extended ports
      // (reader/getter/listener)
      if (!this->qc_reader_)
      {
        DDS4CCM_LOG_DEBUG ("ConditionManager::query - "
          << "Creating query condition for the reader: <"
          << IDL::traits<::CCM_DDS::QueryFilter>::write (filter) << ">");
        this->qc_reader_ =
          this->dr_->create_querycondition (
            ::DDS::READ_SAMPLE_STATE | ::DDS::NOT_READ_SAMPLE_STATE,
            ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
            ::DDS::ALIVE_INSTANCE_STATE,
            filter.expression (),
            filter.parameters ());

        if (!this->qc_reader_)
        {
          DDS4CCM_LOG_ERROR ("ConditionManager::query - "
            << "Error query condition for the reader: filter <"
            << IDL::traits<::CCM_DDS::QueryFilter>::write (filter) << ">");
            throw ::CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 1);
        }

        if (!this->qc_getter_)
        {
          DDS4CCM_LOG_DEBUG ("ConditionManager::query - "
            << "Creating query condition for the getter: filter <"
            << IDL::traits<::CCM_DDS::QueryFilter>::write (filter) << ">");

          this->qc_getter_ =
            this->dr_->create_querycondition (
              ::DDS::NOT_READ_SAMPLE_STATE,
              ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
              ::DDS::ALIVE_INSTANCE_STATE | ::DDS::NOT_ALIVE_INSTANCE_STATE,
              filter.expression (),
              filter.parameters ());

          if (!this->qc_getter_)
          {
            DDS4CCM_LOG_ERROR ("ConditionManager::query - "
              << "Error query condition for the getter: filter <"
              << IDL::traits<::CCM_DDS::QueryFilter>::write (filter) << ">");
              throw ::CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 1);
          }

          // attach the query condition for the getter to the waitset since the
          // getter extended port will use the waitset to interact with DDS.
          // creates a waitset if not already created.
          this->attach_querycondition ();
        }
        if (!this->qc_listener_)
        {
          DDS4CCM_LOG_DEBUG ("Creating query condition for the listener: "
            << "filter <" << IDL::traits<::CCM_DDS::QueryFilter>::write (filter) << ">");

          this->qc_listener_ =
            this->dr_->create_querycondition (
              ::DDS::NOT_READ_SAMPLE_STATE,
              ::DDS::NEW_VIEW_STATE | ::DDS::NOT_NEW_VIEW_STATE,
              ::DDS::ANY_INSTANCE_STATE,
              filter.expression (),
              filter.parameters ());

          if (!this->qc_listener_)
          {
            DDS4CCM_LOG_ERROR ("ConditionManager::query - "
              << "Error query condition for the listener: filter <"
              << IDL::traits<::CCM_DDS::QueryFilter>::write (filter) << ">");
              throw ::CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 1);
          }
        }

        if (!this->qc_reader_ ||
            !this->qc_getter_ ||
            !this->qc_listener_)
        {
          DDS4CCM_LOG_ERROR ("ConditionManager::query - "
            << "Error creating query conditions reader <"
            << this->qc_reader_ << "> - getter <"
            << this->qc_getter_ << "> - listener <"
            << this->qc_listener_ << ">.");

          throw CCM_DDS::InternalError (::DDS::RETCODE_ERROR, 1);
        }
        else
        {
          DDS4CCM_LOG_DEBUG ("ConditionManager::query - "
            << "All query conditions created successfully: expression <"
            << filter.expression () << ">.");
        }
      }
      else if (!filter.expression().empty())
      {
        // Query conditions are available,  and the filter has been set =>
        // change the parameters of this filter.
        this->set_parameters (filter, this->qc_reader_);
        this->set_parameters (filter, this->qc_getter_);
        this->set_parameters (filter, this->qc_listener_);
      }
      else
      {
        // No expression set so remove the query conditions and
        // create the read condition again. ConditionManager has
        // the same state as at start up.
        this->remove_conditions ();
        this->init_read_condition ();
      }
    }

    void
    ConditionManager::set_parameters (
      const ::CCM_DDS::QueryFilter &filter,
      IDL::traits<::DDS::QueryCondition>::ref_type qc)
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::set_parameters");

      ::DDS::ReturnCode_t const retcode =
        qc->set_query_parameters (filter.parameters ());

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("ConditionManager::set_parameters - "
          << "Error setting expression_parameters. Retval is <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");
        throw CCM_DDS::InternalError (::DDS::RETCODE_ERROR, retcode);
      }
    }

    void
    ConditionManager::attach_querycondition ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::attach_querycondition");

      ::DDS::ReturnCode_t const retcode =
        this->waitset ()->attach_condition (this->qc_getter_);
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("ConditionManager::attach_querycondition - "
          << "Unable to attach query condition to waitset. "
          << "Error <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CCM_DDS::InternalError (retcode, 1);
      }
      else
      {
        DDS4CCM_LOG_DEBUG ("ConditionManager::attach_querycondition - "
          "Query condition created and attached to Waitset.");
      }
    }

    bool
    ConditionManager::wait (const ::DDS::Duration_t &time_out)
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::wait");

#if !defined (X11_NLOGGING)
      std::chrono::time_point<std::chrono::system_clock> start (
        std::chrono::system_clock::now ());
#endif

      ::DDS::ConditionSeq active_conditions;
      ::DDS::ReturnCode_t const retcode =
        this->waitset ()->wait (active_conditions, time_out);

#if !defined (X11_NLOGGING)
      std::chrono::milliseconds const elapsed_milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now () - start);
      DDS4CCM_LOG_DEBUG ("ConditionManager::wait - <"
        << IDL::traits<::DDS::Duration_t>::write<duration_formatter> (time_out)
        << "> - waited <" << elapsed_milliseconds.count () << " ms> - return code<"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
#endif

      bool ret = false;

      if (retcode == ::DDS::RETCODE_TIMEOUT)
      {
        DDS4CCM_LOG_DEBUG ("ConditionManager::wait - "
          "No data available after timeout.");
      }
      else if (this->rd_condition_)
      {
        ret = this->rd_condition_->get_trigger_value ();
      }
      else if (this->qc_getter_)
      {
        ret = this->qc_getter_->get_trigger_value();
      }

      return ret;
    }

    void
    ConditionManager::remove_condition (
      IDL::traits<::DDS::QueryCondition>::ref_type dds_qc,
      const std::string &type)
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::remove_condition");
      if (dds_qc)
      {
        ::DDS::ReturnCode_t const retcode =
          this->dr_->delete_readcondition (dds_qc);
        if (retcode == ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_DEBUG ("ConditionManager::remove_condition - "
            << "Succesfully removed query condition for <"
            << type << ">.");
        }
        else
        {
          DDS4CCM_LOG_ERROR ("ConditionManager::remove_condition - "
            << "Unable to remove query condition for <"
            << type << ">: Error <"
            << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">.");
        }
      }
    }

    void
    ConditionManager::remove_conditions ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::remove_conditions");

      // Safe to remove the query conditions of the reader and listener since
      // these are not attached to a waitset.
      // Explicitly setting the conditions to a nullptr. If not, the nullptr checks fail and
      // therefor the resetting the topicname fails.
      if (this->qc_reader_)
      {
        this->remove_condition (this->qc_reader_, "reader");
        this->qc_reader_ = nullptr;
      }
      if (this->qc_listener_)
      {
        this->remove_condition (this->qc_listener_, "listener");
        this->qc_listener_ = nullptr;
      }

      ::DDS::ReturnCode_t retcode = ::DDS::RETCODE_OK;
      // Check whether a query condition was created (and thus attached
      // to the waitset).
      if (this->qc_getter_)
      {
        // Waitset for the getter extended port has been created.
        // Therefor detach any condition from the waitset first
        // (in this case, the query condition).
        retcode = this->waitset ()->detach_condition (
          this->qc_getter_);
        if (retcode == ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_DEBUG ("ConditionManager::remove_conditions - "
            << "Query condition successfully detached from waitset.");
          // We can now safely remove the query condition from DDS.
          this->remove_condition (this->qc_getter_, "getter");
        }
        else
        {
          DDS4CCM_LOG_ERROR ("ConditionManager::remove_conditions - "
            << "Unable to detach query condition from waitset: Error: <"
            << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">.");
        }
        this->qc_getter_ = nullptr;
      }
      else
      {
        // No query condition on of the getter (and therefor attached to the waitset)
        // In this case there should be a read condition attached to the waitset.
        if (this->rd_condition_)
        {
          // Read condition should be attached to the waitset.
          retcode = this->ws_->detach_condition (this->rd_condition_);
          if (retcode != ::DDS::RETCODE_OK)
          {
            DDS4CCM_LOG_ERROR ("ConditionManager::remove_conditions - "
              << "Unable to detach read condition from waitset. Error <"
              << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
              << ">.");
          }
          else
          {
            DDS4CCM_LOG_DEBUG ("ConditionManager::remove_conditions - "
              "Read condition successfully detached from waitset.");
          }
        }
      }
      // Now we can safely remove the read condition
      if (this->rd_condition_)
      {
        retcode = this->dr_->delete_readcondition (this->rd_condition_);
        if (retcode != ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_ERROR ("ConditionManager::remove_conditions - "
            << "Unable to remove read condition from DDSDataReader. Error <"
            << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">.");
        }
        else
        {
          DDS4CCM_LOG_DEBUG ("ConditionManager::remove_conditions - "
            << "Read condition successfully removed from DDS::DataReader.");
        }
        this->rd_condition_ = nullptr;
      }
    }

    void
    ConditionManager::passivate ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::passivate");

      this->remove_conditions ();
    }

    IDL::traits<::DDS::WaitSet>::ref_type
    ConditionManager::waitset ()
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::waitset");

      if (!this->ws_)
      {
        this->ws_ = DDSX11::VendorUtils::create_waitset ();
      }
      return this->ws_;
    }

    void
    ConditionManager::set_dds_entity (
      IDL::traits<::DDS::DataReader>::ref_type dr)
    {
      DDS4CCM_LOG_TRACE ("ConditionManager::set_dds_entity");

      this->dr_ = std::move(dr);
    }

    IDL::traits<::DDS::DataReader>::ref_type
    ConditionManager::get_dds_entity ()
    {
      return this->dr_;
    }
  }
}
