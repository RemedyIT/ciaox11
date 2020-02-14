// -*- C++ -*-
/**
 * @file    dds4ccm_dds_event_strategies_default_t.h
 * @author  Martin Corino
 *
 * @brief   Implements the default event handling strategy from DDS to DDS4CCM
 *
 *          The class members (listener and datareader/datawriter) are passed
 *          as weak references. We don't want to influence the life cycle of
 *          entities here.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_DDS_EVENT_STRATEGIES_DEFAULT_T_H_
#define DDS4CCM_DDS_EVENT_STRATEGIES_DEFAULT_T_H_

#include "dds4ccm/impl/dds4ccm_dds_context_switch_handlers.h"
#include "dds4ccm/impl/dds4ccm_dds_context_switch_handlers_t.h"
#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/logger/dds4ccm_log.h"

#include "ace/Reactor.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    class DefaultEventStrategyBase
    {
    protected:
      DefaultEventStrategyBase (IDL::traits<Components::SessionContext>::ref_type ctx)
      {
        DDS4CCM_LOG_TRACE ("DefaultEventStrategyBase::" << "ctor");

#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        IDL::traits<CORBA::Object>::ref_type orb_object =
          ctx->the_service_registry ()->resolve_service (CIAOX11::SVCID_ORB);
        IDL::traits<CORBA::ORB>::ref_type orb =
          IDL::traits<CORBA::ORB>::narrow (orb_object);
        if (orb)
          {
            this->reactor_ = orb->reactor ();
          }
        else
          {
            DDS4CCM_LOG_WARNING ("DefaultEventStrategyBase::" << "ctor" <<
                " - unable to resolve ORB for reactor" );
          }
#endif
      }
      DefaultEventStrategyBase (const DefaultEventStrategyBase& des)
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        : reactor_ (des.reactor_)
#endif
      {}

    public:
      virtual ~DefaultEventStrategyBase () {}

    private:
      DefaultEventStrategyBase (DefaultEventStrategyBase&&) = delete;
      DefaultEventStrategyBase& operator=(const DefaultEventStrategyBase&) = delete;
      DefaultEventStrategyBase& operator=(DefaultEventStrategyBase&&) = delete;

    protected:
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
      ACE_Reactor *reactor_ {};
#endif
    };

    template <typename CCM_TYPE>
    class DefaultErrorEventStrategy_T
      : public DefaultEventStrategyBase
    {
    public:
      DefaultErrorEventStrategy_T (
        typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultEventStrategyBase (ctx)
      {
        IDL::traits< CCM_DDS::ConnectorStatusListener>::ref_type erl =
            ctx->get_connection_error_listener ();
        this->error_listener_ = erl;
        if (erl)
          this->error_listener_connected_ = true;
      }
      DefaultErrorEventStrategy_T (const DefaultErrorEventStrategy_T& des)
        : DefaultEventStrategyBase (des)
        , error_listener_ (des.error_listener_)
        , error_listener_connected_ (des.error_listener_connected_)
      {}
      virtual ~DefaultErrorEventStrategy_T () = default;

      // on_unexpected_status
      void
      handle_unexpected_status_event (
          IDL::traits< ::DDS::Entity>::ref_type entity,
          ::DDS::StatusKind status_kind)
      {
        if (!this->error_listener_connected_)
        {
          DDS4CCM_LOG_DEBUG ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
              "handle_unexpected_status_event" <<
              " - received <" <<
              status_kind << ">");
          return;
        }
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnUnexpectedStatusHandler> (
              this->error_listener_, entity, status_kind);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_unexpected_status_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnUnexpectedStatusHandler::handle_event (
              this->error_listener_.lock (), entity, status_kind);
        }
      }

      // on_requested_incompatible_qos
      void
      handle_requested_incompatible_qos_event (
          IDL::traits< ::DDS::DataReader>::ref_type dr,
          const ::DDS::RequestedIncompatibleQosStatus &status)
      {
        if (!this->error_listener_connected_)
        {
          DDS4CCM_LOG_DEBUG ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
              "handle_requested_incompatible_qos_event" <<
              " - received <" <<
              status << ">");
          return;
        }
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnRequestedIncompatibleQosHandler> (
                this->error_listener_, dr, status);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_requested_incompatible_qos_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnRequestedIncompatibleQosHandler::handle_event (
              this->error_listener_.lock (), dr, status);
        }
      }

      // on_sample_rejected
      void
      handle_sample_rejected_event (
          IDL::traits< ::DDS::DataReader>::ref_type dr,
          const ::DDS::SampleRejectedStatus &status)
      {
        if (!this->error_listener_connected_)
        {
          DDS4CCM_LOG_DEBUG ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
              "handle_sample_rejected_event" <<
              " - received <" <<
              status << ">");
          return;
        }
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnSampleRejectedHandler> (
                this->error_listener_, dr, status);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_sample_rejected_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnSampleRejectedHandler::handle_event (
              this->error_listener_.lock (), dr, status);
        }
      }

      // on_inconsistent_topic
      void
      handle_inconsistent_topic_event (
          IDL::traits< ::DDS::Topic>::ref_type tp,
          const ::DDS::InconsistentTopicStatus &status)
      {
        if (!this->error_listener_connected_)
        {
          DDS4CCM_LOG_DEBUG ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
              "handle_inconsistent_topic_event" <<
              " - received <" <<
              status << ">");
          return;
        }
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnInconsistentTopicHandler> (
                this->error_listener_, tp, status);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_inconsistent_topic_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnInconsistentTopicHandler::handle_event (
              this->error_listener_.lock (), tp, status);
        }
      }

      // on_offered_deadline_missed
      void
      handle_offered_deadline_missed_event (
          IDL::traits< ::DDS::DataWriter>::ref_type dw,
          const ::DDS::OfferedDeadlineMissedStatus &status)
      {
        if (!this->error_listener_connected_)
        {
          DDS4CCM_LOG_DEBUG ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
              "handle_offered_deadline_missed_event" <<
              " - received <" <<
              status << ">");
          return;
        }
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnOfferedDeadlineMissedHandler> (
                this->error_listener_, dw, status);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_offered_deadline_missed_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnOfferedDeadlineMissedHandler::handle_event (
              this->error_listener_.lock (), dw, status);
        }
      }

      // on_offered_incompatible_qos
      void
      handle_offered_incompatible_qos_event (
          IDL::traits< ::DDS::DataWriter>::ref_type dw,
          const ::DDS::OfferedIncompatibleQosStatus &status)
      {
        if (!this->error_listener_connected_)
        {
          DDS4CCM_LOG_DEBUG ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
              "handle_offered_incompatible_qos_event" <<
              " - received <" <<
              status << ">");
          return;
        }
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnOfferedIncompatibleQoSHandler> (
                this->error_listener_, dw, status);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_offered_incompatible_qos_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnOfferedIncompatibleQoSHandler::handle_event (
              this->error_listener_.lock (), dw, status);
        }
      }

    private:
      DefaultErrorEventStrategy_T (DefaultErrorEventStrategy_T&&) = delete;
      DefaultErrorEventStrategy_T& operator=(const DefaultErrorEventStrategy_T&) = delete;
      DefaultErrorEventStrategy_T& operator=(DefaultErrorEventStrategy_T&&) = delete;

      IDL::traits< CCM_DDS::ConnectorStatusListener>::weak_ref_type error_listener_ {};
      bool error_listener_connected_ {};
    };

    class DefaultPortStatusEventStrategyBase
      : public DefaultEventStrategyBase
    {
    protected:
      DefaultPortStatusEventStrategyBase (
        IDL::traits<Components::SessionContext>::ref_type ctx,
        IDL::traits< ::CCM_DDS::PortStatusListener>::ref_type port_status_listener)
        : DefaultEventStrategyBase (std::move(ctx))
        , status_listener_ (std::move(port_status_listener))
      {}
      DefaultPortStatusEventStrategyBase (const DefaultPortStatusEventStrategyBase& des)
        : DefaultEventStrategyBase (des)
        , status_listener_ (des.status_listener_)
      {}
    public:
      virtual ~DefaultPortStatusEventStrategyBase () = default;

      // on_requested_deadline_missed
      void
      handle_requested_deadline_missed_event (
          IDL::traits< ::DDS::DataReader>::ref_type dr,
          const ::DDS::RequestedDeadlineMissedStatus &status)
      {
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnRequestedDeadlineMissedHandler> (
              this->status_listener_, dr, status);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultPortStatusEventStrategyBase::" <<
                "handle_requested_deadline_missed_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnRequestedDeadlineMissedHandler::handle_event (
              this->status_listener_.lock (), dr, status);
        }
      }

      // on_sample_lost
      void
      handle_sample_lost_event (
          IDL::traits< ::DDS::DataReader>::ref_type dr,
          const ::DDS::SampleLostStatus &status)
      {
#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<OnSampleLostHandler> (
              this->status_listener_, dr, status);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultPortStatusEventStrategyBase::" <<
                "handle_sample_lost_event" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          OnSampleLostHandler::handle_event (
              this->status_listener_.lock (), dr, status);
        }
      }

    private:
      DefaultPortStatusEventStrategyBase (DefaultPortStatusEventStrategyBase&&) = delete;
      DefaultPortStatusEventStrategyBase& operator=(const DefaultPortStatusEventStrategyBase&) = delete;
      DefaultPortStatusEventStrategyBase& operator=(DefaultPortStatusEventStrategyBase&&) = delete;

      IDL::traits< ::CCM_DDS::PortStatusListener>::weak_ref_type status_listener_ {};
    };

    template <typename DATA_LISTENER>
    class DefaultDataEventStrategyBase_T
      : public DefaultPortStatusEventStrategyBase
    {
    protected:
      DefaultDataEventStrategyBase_T (
        IDL::traits<Components::SessionContext>::ref_type ctx,
        IDL::traits< ::CCM_DDS::PortStatusListener>::ref_type port_status_listener,
        typename IDL::traits< DATA_LISTENER>::ref_type data_listener)
        : DefaultPortStatusEventStrategyBase (std::move(ctx), std::move(port_status_listener))
        , data_listener_ (data_listener)
      {}
      DefaultDataEventStrategyBase_T (const DefaultDataEventStrategyBase_T& des)
        : DefaultPortStatusEventStrategyBase (des)
        , data_listener_ (des.data_listener_)
      {}
    public:
      virtual ~DefaultDataEventStrategyBase_T () = default;

      // on_data_available
      template <typename LISTENER>
      void handle_data_available_event (
          typename IDL::traits< LISTENER>::ref_type drl,
          IDL::traits< ::DDS::DataReader>::ref_type dr)
      {
        typedef DataReaderContextSwitch_T<LISTENER, DATA_LISTENER> DataReaderHandler_type;

#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<DataReaderHandler_type> (drl, dr, this->data_listener_);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            DDS4CCM_LOG_ERROR ("DefaultDataEventStrategyBase_T<DATA_LISTENER>::" <<
                "handle_data_available_event<LISTENER>" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          DataReaderHandler_type::handle_event (drl, dr, this->data_listener_.lock ());
        }
      }

    private:
      DefaultDataEventStrategyBase_T (DefaultDataEventStrategyBase_T&&) = delete;
      DefaultDataEventStrategyBase_T& operator=(const DefaultDataEventStrategyBase_T&) = delete;
      DefaultDataEventStrategyBase_T& operator=(DefaultDataEventStrategyBase_T&&) = delete;

      typename IDL::traits< DATA_LISTENER>::weak_ref_type data_listener_ {};
    };

    template <typename CCM_TYPE>
    class DefaultPushConsumerEventStrategy_T
      : public DefaultDataEventStrategyBase_T<
          typename CCM_TYPE::push_consumer_traits::data_listener_type>
    {
    public:
      DefaultPushConsumerEventStrategy_T (
        typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultDataEventStrategyBase_T<
            typename CCM_TYPE::push_consumer_traits::data_listener_type> (
                ctx,
                ctx->get_connection_push_consumer_status (),
                ctx->get_connection_push_consumer_data_listener ())
      {}
      DefaultPushConsumerEventStrategy_T (const DefaultPushConsumerEventStrategy_T& des)
        : DefaultDataEventStrategyBase_T<
            typename CCM_TYPE::push_consumer_traits::data_listener_type> (des)
      {}
      virtual ~DefaultPushConsumerEventStrategy_T () = default;
    };

    template <typename CCM_TYPE>
    class DefaultPullConsumerEventStrategy_T
      : public DefaultPortStatusEventStrategyBase
    {
    public:
      DefaultPullConsumerEventStrategy_T (
        typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultPortStatusEventStrategyBase (
                ctx,
                ctx->get_connection_pull_consumer_status ())
      {}
      DefaultPullConsumerEventStrategy_T (const DefaultPullConsumerEventStrategy_T& des)
        : DefaultPortStatusEventStrategyBase (des)
      {}
      virtual ~DefaultPullConsumerEventStrategy_T () = default;
    };

    template <typename CCM_TYPE>
    class DefaultPassiveObserverEventStrategy_T
      : public DefaultPortStatusEventStrategyBase
    {
    public:
      DefaultPassiveObserverEventStrategy_T (
        typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultPortStatusEventStrategyBase (
                ctx,
                ctx->get_connection_passive_observer_status ())
      {}
      DefaultPassiveObserverEventStrategy_T (const DefaultPassiveObserverEventStrategy_T& des)
        : DefaultPortStatusEventStrategyBase (des)
      {}
      virtual ~DefaultPassiveObserverEventStrategy_T () = default;
    };

    template <typename CCM_TYPE>
    class DefaultPullObserverEventStrategy_T
      : public DefaultPortStatusEventStrategyBase
    {
    public:
      DefaultPullObserverEventStrategy_T (
        typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultPortStatusEventStrategyBase (
                ctx,
                ctx->get_connection_pull_observer_status ())
      {}
      DefaultPullObserverEventStrategy_T (const DefaultPullObserverEventStrategy_T& des)
        : DefaultPortStatusEventStrategyBase (des)
      {}
      virtual ~DefaultPullObserverEventStrategy_T ()  = default;
    };

    template <typename CCM_TYPE>
    class DefaultPushObserverEventStrategy_T
      : public DefaultDataEventStrategyBase_T<
          typename CCM_TYPE::push_observer_traits::data_listener_type>
    {
    public:
      DefaultPushObserverEventStrategy_T (
        typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultDataEventStrategyBase_T<
            typename CCM_TYPE::push_observer_traits::data_listener_type> (
                ctx,
                ctx->get_connection_push_observer_status (),
                ctx->get_connection_push_observer_data_listener ())
      {}
      DefaultPushObserverEventStrategy_T (const DefaultPushObserverEventStrategy_T& des)
        : DefaultDataEventStrategyBase_T<
            typename CCM_TYPE::push_observer_traits::data_listener_type> (des)
      {}
      virtual ~DefaultPushObserverEventStrategy_T () = default;
    };

    template <typename CCM_TYPE>
    class DefaultPushStateObserverEventStrategy_T
      : public DefaultDataEventStrategyBase_T<
          typename CCM_TYPE::push_state_observer_traits::data_listener_type>
    {
    public:
      DefaultPushStateObserverEventStrategy_T (
        typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultDataEventStrategyBase_T<
            typename CCM_TYPE::push_state_observer_traits::data_listener_type> (
                ctx,
                ctx->get_connection_push_state_observer_status (),
                ctx->get_connection_push_state_observer_data_listener ())
      {}
      DefaultPushStateObserverEventStrategy_T (const DefaultPushStateObserverEventStrategy_T& des)
        : DefaultDataEventStrategyBase_T<
            typename CCM_TYPE::push_state_observer_traits::data_listener_type> (des)
      {}
      virtual ~DefaultPushStateObserverEventStrategy_T () = default;
    };
  }
}

#endif /* DDS4CCM_DDS_EVENT_STRATEGIES_DEFAULT_T_H_ */
