// -*- C++ -*-
/**
 * @file    psdd4ccm_event_strategies_default_t.h
 * @author  Martin Corino
 *
 * @brief   Implements the default event handling strategy from PSDD middleware to PSDD4CCM
 *
 *          The class members (listener and datareader/datawriter) are passed
 *          as weak references. We don't want to influence the life cycle of
 *          entities here.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_EVENT_STRATEGIES_DEFAULT_T_H_
#define PSDD4CCM_EVENT_STRATEGIES_DEFAULT_T_H_

#include "psdd4ccm/impl/psdd4ccm_context_switch_handlers_t.h"
#include "psdd4ccm/impl/psdd4ccm_conf.h"
#include "psdd4ccm/logger/psdd4ccm_log.h"

#include "ace/Reactor.h"

namespace CIAOX11
{
  namespace PSDD4CCM
  {
    class DefaultEventStrategyBase
    {
    protected:
      DefaultEventStrategyBase () = default;
      DefaultEventStrategyBase (IDL::traits<Components::SessionContext>::ref_type ctx)
      {
        PSDD4CCM_LOG_TRACE ("PSDD4CCM::DefaultEventStrategyBase::" << "ctor");

#if (CIAOX11_PSDD4CCM_CONTEXT_SWITCH == 1)
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
            PSDD4CCM_LOG_WARNING ("PSDD4CCM::DefaultEventStrategyBase::" << "ctor" <<
                " - unable to resolve ORB for reactor" );
          }
#endif
      }
      DefaultEventStrategyBase (const DefaultEventStrategyBase& des)
#if (CIAOX11_PSDD4CCM_CONTEXT_SWITCH == 1)
        : reactor_ (des.reactor_)
#endif
      {}

      void assign(const DefaultEventStrategyBase& des)
      { this->reactor_ = des.reactor_; }

    public:
      virtual ~DefaultEventStrategyBase () = default;

    private:
      DefaultEventStrategyBase (DefaultEventStrategyBase&&) = delete;
      DefaultEventStrategyBase& operator=(const DefaultEventStrategyBase&) = delete;
      DefaultEventStrategyBase& operator=(DefaultEventStrategyBase&&) = delete;

    protected:
#if (CIAOX11_PSDD4CCM_CONTEXT_SWITCH == 1)
      ACE_Reactor *reactor_ {};
#endif
    };

    template <typename CCM_TYPE>
    class DefaultPushConsumerEventStrategy_T
      : public DefaultEventStrategyBase
    {
    public:
      typedef typename CCM_TYPE::consumer_traits::data_listener_type listener_type;

      DefaultPushConsumerEventStrategy_T () = default;
      DefaultPushConsumerEventStrategy_T (
        typename IDL::traits< typename CCM_TYPE::context_type>::ref_type ctx)
        : DefaultEventStrategyBase (ctx)
        , listener_ (ctx->get_connection_consumer_data_listener ())
      {}
      DefaultPushConsumerEventStrategy_T (const DefaultPushConsumerEventStrategy_T& dpces)
        : DefaultEventStrategyBase (dpces)
        , listener_ (dpces.listener_)
      {}

      virtual ~DefaultPushConsumerEventStrategy_T () = default;

      DefaultPushConsumerEventStrategy_T& operator =(
          const DefaultPushConsumerEventStrategy_T& dpces)
      {
        this->assign (dpces);
        this->listener_ = dpces.listener_;
        return *this;
      }

      // on_data_available
      template <typename HANDLER>
      void handle_data_available_event (
          typename IDL::traits< HANDLER>::ref_type dh)
      {
        typedef DataListenerContextSwitch_T<listener_type, HANDLER> DataListenerHandler_type;

#if (CIAOX11_PSDD4CCM_CONTEXT_SWITCH == 1)
        if (this->reactor_)
        {
          ACE_Event_Handler_var rh =
            ACE::make_event_handler<DataListenerHandler_type> (dh, this->listener_);

          if (this->reactor_->notify (rh.handler ()) != 0)
          {
            PSDD4CCM_LOG_ERROR ("DefaultDataEventStrategyBase_T<LISTENER>::" <<
                "handle_data_available_event<LISTENER>" <<
                " - failed to use reactor.");
          }
        }
        else
#endif
        {
          DataListenerHandler_type::handle_event (dh, this->listener_.lock ());
        }
      }

    private:
      DefaultPushConsumerEventStrategy_T (DefaultPushConsumerEventStrategy_T&&) = delete;
      DefaultPushConsumerEventStrategy_T& operator=(DefaultPushConsumerEventStrategy_T&&) = delete;

      typename IDL::traits < listener_type >::weak_ref_type listener_ {};
    };

  } /* PSDD4CCM */
} /* CIAOX11 */

#endif /* PSDD4CCM_EVENT_STRATEGIES_DEFAULT_T_H_ */
