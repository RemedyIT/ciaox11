// -*- C++ -*-
/**
 * @file    psdd4ccm_event_connector_t.h
 * @author  Martin Corino
 *
 * @brief   Implementation of the PSDD4CCM Event connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_EVENT_CONNECTOR_H
#define PSDD4CCM_EVENT_CONNECTOR_H

#include "psdd4ccm/logger/psdd4ccm_log.h"

#include "psdd4ccm/idl/ccm_psddC.h"

#include "psdd4ccm/impl/psdd4ccm_conf.h"
#include "psdd4ccm/impl/psdd/psdd_publisher_t.h"
#include "psdd4ccm/impl/psdd/psdd_subscriber_t.h"

namespace CIAOX11
{
  namespace PSDD
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class Event_Connector_T
      : public virtual CCM_TYPE::base_type
    {
    public:
      Event_Connector_T () = default;
      virtual ~Event_Connector_T () = default;

      /**
       * @name attributes of PSDD4CCM PSDD_Base
       * Attributes of PSDD4CCM PSDD_Base
       */
      //@{
      void
      topic_name (
        const std::string &topic_name) override;

      std::string
      topic_name () override;

      std::string
      type_name () override;

      void
      publish (
        bool f) override;

      bool
      publish () override;

      void
      subscribe (
        bool f) override;

      bool
      subscribe() override;
      //@}

      /**
       * @name PSDD4CCM PSD_Events ports
       * PSDD4CCM PSD_Events ports
       */
      //@{
      typename IDL::traits< typename CCM_TYPE::supplier_data_type>::ref_type
      get_supplier_data () override;

      typename IDL::traits< typename CCM_TYPE::pull_consumer_data_type>::ref_type
      get_pull_consumer_data () override;

      typename IDL::traits< typename CCM_TYPE::consumer_data_subscriber_type>::ref_type
      get_consumer_data_subscriber () override;
      //@}

      /**
       * @name life cycle methods
       * Life cycle methods, specific for this class.
       */
      //@{
      void configuration_complete () override;

      void ccm_activate () override;

      void ccm_passivate () override;

      void ccm_remove () override;
      //@}

      /**
       * Sets the context of the connector.
       * The context is used to make connections to the user component,
       * like the interfaces to the data listeners.
       */
      void
      set_session_context (
        IDL::traits<Components::SessionContext>::ref_type ctx) override;

    protected:
      /**
       * Protected getters and setters
       */
      /// Get configuration_completed
      bool
      configuration_completed ();

      /// Set configuration_completed
      void
      configuration_completed (bool configuration_completed);

      /// Get the context of this connector.
      typename IDL::traits< typename CCM_TYPE::context_type>::ref_type
      context ();

      /**
       * @name PSDD entity getters
       *
       * Getters for the PSDD entities.
       */
      typedef ::PSDD::Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
          publisher_type;
      typedef ::PSDD::Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
          subscriber_type;

      typename IDL::traits< publisher_type>::ref_type
      publisher ();
      typename IDL::traits< subscriber_type>::ref_type
      subscriber ();

      typename IDL::traits< publisher_type>::ref_type publisher_;
      typename IDL::traits< subscriber_type>::ref_type subscriber_;

    private:
      std::string topic_name_;
      bool publish_ {};
      bool subscribe_ {};

      std::shared_ptr<typename CCM_TYPE::service_helper_type> service_helper_;

      /**
       * Indicates whether configuration_complete has been invoked. Once invoked,
       * changing a connector attribute is not allowed anymore. If the user still
       * wants to set an attribute, a NonChangeable exception is thrown.
        */
      bool configuration_completed_ { false };

      /**
       * Context of the connector. Used to make connections to the user component
       * like the interfaces to the data listeners.
       */
      typename IDL::traits< typename CCM_TYPE::context_type>::ref_type context_;


      Event_Connector_T(const Event_Connector_T&) = delete;
      Event_Connector_T(Event_Connector_T&&) = delete;
      Event_Connector_T& operator=(const Event_Connector_T&) = delete;
      Event_Connector_T& operator=(Event_Connector_T&&) = delete;
    };
  }; /* namespace PSDD */
}; /* namespace CIAOX11 */

#include "psdd4ccm_event_connector_t.cpp"

#endif /* PSDD4CCM_EVENT_CONNECTOR_H */
