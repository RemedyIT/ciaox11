// -*- C++ -*-
/**
 * @file    psdd4ccm_event_connector_t.cpp
 * @author  Martin Corino
 *
 * @brief   Implementation of the PSDD4CCM Event connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "psdd4ccm/logger/psdd4ccm_log.h"

#include <memory>

namespace CIAOX11
{
  namespace PSDD
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    std::string
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::topic_name ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::topic_name (get)");

      return this->topic_name_.empty () ? this->type_name () : this->topic_name_;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::topic_name (
      const std::string &topic_name)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::topic_name (set)");

      this->topic_name_ = topic_name;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    std::string
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::type_name ()
    {
      return ::PSDD::traits<TOPIC_TYPE>::
      ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::publish ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::publish (get)");

      return this->publish_;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::publish (
      bool f)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () <<
        "}::publish (" << f << ")");

      if (this->configuration_completed_)
        throw ::CCM_PSDD::NonChangeable ();

      this->publish_ = f;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscribe ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::subscribe (get)");

      return this->subscribe_;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscribe (
      bool f)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () <<
        "}::subscribe (" << f << ")");

      if (this->configuration_completed_)
        throw ::CCM_PSDD::NonChangeable ();

      this->subscribe_ = f;
    }

    /**
     * PSDD4CCM PSD_Events ports
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename IDL::traits< typename CCM_TYPE::supplier_traits::data_type>::ref_type
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_supplier_data ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::get_supplier_data");

      return this->publisher ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename IDL::traits< typename CCM_TYPE::consumer_traits::data_type>::ref_type
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_consumer_data ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::get_pull_consumer_data");

      return this->subscriber ()->get_pull_consumer_data ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename IDL::traits< typename CCM_TYPE::consumer_traits::data_subscriber_type>::ref_type
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_consumer_data_subscriber ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::get_consumer_data_subscriber");

      return this->subscriber ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename IDL::traits< typename Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::publisher_type>::ref_type
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::publisher ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::publisher");

      if (!this->publisher_)
      {
        this->publisher_ =
            ::CIAOX11::PSDD::MWUtils::create_publisher<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> ();
      }
      return this->publisher_;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename IDL::traits< typename Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscriber_type>::ref_type
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscriber ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::subscriber");

      if (!this->subscriber_)
      {
        this->subscriber_ =
            ::CIAOX11::PSDD::MWUtils::create_subscriber<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> ();
      }
      return this->subscriber_;
    }

    /**
     * Life cycle methods
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_complete ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::configuration_complete");

      this->configuration_completed (true);

      PSDD4CCM_LOG_INFO (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::configuration_complete" <<
        " - creating service config with " <<
        "[ publish=" << this->publish_ <<
        ", subscribe=" << this->subscribe_ << " ]");

      this->service_helper_ =
          ::CIAOX11::PSDD::MWUtils::create_service_helper<CCM_TYPE> (
              this->context_,
              this->publish_,
              this->subscribe_);
      if (!this->service_helper_)
      {
        throw CORBA::NO_MEMORY ();
      }

      PSDD4CCM_LOG_INFO (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::configuration_complete" <<
        " - initializing subscriber");

      this->subscriber ()->initialize (
          this->topic_name (),
          this->service_helper_);

      PSDD4CCM_LOG_INFO (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::configuration_complete" <<
        " - initializing publisher");

      this->publisher ()->initialize (
          this->topic_name (),
          this->service_helper_);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_activate ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::ccm_activate");

      if (this->context ()->get_connection_consumer_data_listener ())
      {
        PSDD4CCM_LOG_INFO (
          "PSDD::Event_Connector_T<>{" << this->type_name () << "}::ccm_activate" <<
          " - activating data listener");

        this->subscriber ()->activate_push_consumer_data_listener (
            typename CCM_TYPE::event_strategy_type (this->context_));
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_passivate ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::ccm_passivate");

      if (this->publisher_)
      {
        PSDD4CCM_LOG_INFO (
          "PSDD::Event_Connector_T<>{" << this->type_name () << "}::ccm_passivate" <<
          " - shutting down publisher");
        this->publisher_->shutdown ();
      }

      if (this->subscriber_)
      {
        PSDD4CCM_LOG_INFO (
          "PSDD::Event_Connector_T<>{" << this->type_name () << "}::ccm_passivate" <<
          " - shutting down subscriber");
        this->subscriber_->shutdown ();
      }

      if (this->service_helper_)
      {
        PSDD4CCM_LOG_INFO (
          "PSDD::Event_Connector_T<>{" << this->type_name () << "}::ccm_passivate" <<
          " - shutting down service configuration");
        this->service_helper_->shutdown ();
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_remove ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::Event_Connector_T<>{" << this->type_name () << "}::ccm_remove");

      this->publisher_.reset ();
      this->subscriber_.reset ();
      this->service_helper_.reset ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::set_session_context (
      IDL::traits<Components::SessionContext>::ref_type ctx)
    {
      PSDD4CCM_LOG_TRACE ("PSDD::Event_Connector_T<>{" << this->type_name () << "}::set_session_context");

      this->context_ = CCM_TYPE::context_type::_traits_type::narrow (std::move(ctx));
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_completed ()
    {
      PSDD4CCM_LOG_TRACE ("PSDD::Event_Connector_T<>{" << this->type_name () << "}::configuration_completed");
      return this->configuration_completed_;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_completed (
      bool configuration_completed)
    {
      PSDD4CCM_LOG_TRACE ("PSDD::Event_Connector_T<>{" << this->type_name () << "}::configuration_completed");
      this->configuration_completed_ = configuration_completed;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename IDL::traits< typename CCM_TYPE::context_type>::ref_type
    Event_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::context ()
    {
      return this->context_;
    }
  };
};
