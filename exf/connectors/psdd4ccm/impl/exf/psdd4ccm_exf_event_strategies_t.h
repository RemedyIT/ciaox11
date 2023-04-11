// -*- C++ -*-
/**
 * @file    psdd4ccm_exf_event_strategies_t.h
 * @author  Martin Corino
 *
 * @brief   Implements the ExF event handling strategy from PSDD middleware to PSDD4CCM
 *
 *          The class members (listener) are passed
 *          as weak references. We don't want to influence the life cycle of
 *          entities here.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_EXF_EVENT_STRATEGIES_T_H_
#define PSDD4CCM_EXF_EVENT_STRATEGIES_T_H_

#include "exf/deployment/core/ciaox11_exf_util.h"
#include "psdd4ccm/impl/exf/psdd4ccm_exf_event_executors.h"
#include "psdd4ccm/impl/psdd4ccm_conf.h"
#include "psdd4ccm/logger/psdd4ccm_log.h"


namespace CIAOX11
{
  namespace PSDD4CCM
  {
    namespace ExF
    {
      class EventStrategyBase
      {
      protected:
        EventStrategyBase () = default;
        EventStrategyBase (const Components::ConfigValues &config)
        {
          PSDD4CCM_LOG_TRACE ("ExF::EventStrategyBase::ctor");

          // check for scheduling lane
          for (const Components::ConfigValue& cval : config)
          {
            if (cval.name () == CIAOX11::ExF::SCHEDULING_LANE_REF)
            {
              IDL::traits<CORBA::Object>::ref_type objref {};
              if (!(cval.value () >>= objref))
              {
                throw std::runtime_error (
                    "ExF::EventStrategyBase: failed to extract " +
                    CIAOX11::ExF::SCHEDULING_LANE_REF);
              }
              this->scheduling_lane_ = IDL::traits<CIAOX11::ExF::SchedulingLane>::narrow (std::move(objref));
            }
          }
        }
        EventStrategyBase (const EventStrategyBase& des)
        : scheduling_lane_ (des.scheduling_lane_) {}

        void assign(const EventStrategyBase& des)
        { this->scheduling_lane_ = des.scheduling_lane_; }

      public:
        virtual ~EventStrategyBase () = default;

      private:
        EventStrategyBase (EventStrategyBase&&) = delete;
        EventStrategyBase& operator=(const EventStrategyBase&) = delete;
        EventStrategyBase& operator=(EventStrategyBase&&) = delete;

      protected:
        IDL::traits<CIAOX11::ExF::SchedulingLane>::ref_type scheduling_lane_ {};
      };

      template <typename CCM_TYPE>
      class PushConsumerEventStrategy_T
        : public EventStrategyBase
      {
      public:
        typedef typename CCM_TYPE::consumer_traits::data_listener_type listener_type;

        PushConsumerEventStrategy_T  () = default;
        PushConsumerEventStrategy_T  (
            typename IDL::traits< typename CCM_TYPE::context_type>::ref_type ctx)
          : EventStrategyBase (ctx->consumer_data_listener_configuration ())
          , listener_ (ctx->get_connection_consumer_data_listener ())
        {
          if (this->scheduling_lane_)
          {
            // get scheduling settings
            CIAOX11::ExF::Settings def_settings {};
            if (CIAOX11::ExF::Util::get_exf_defaults (ctx->consumer_data_listener_configuration (), def_settings))
            {
              this->data_available_exf_settings_ = def_settings;
            }

            // check for scheduling properties
            CIAOX11::ExF::Util::get_exf_settings (ctx->consumer_data_listener_configuration (), "data_available", this->data_available_exf_settings_);
          }
        }
        PushConsumerEventStrategy_T (const PushConsumerEventStrategy_T& dpces)
          : EventStrategyBase (dpces)
          , listener_ (dpces.listener_)
          , data_available_exf_settings_ (dpces.data_available_exf_settings_)
        {}

        ~PushConsumerEventStrategy_T () override = default;

        PushConsumerEventStrategy_T& operator =(const PushConsumerEventStrategy_T& dpces)
        {
          this->assign (dpces);
          this->listener_ = dpces.listener_;
          this->data_available_exf_settings_ = dpces.data_available_exf_settings_;
          return *this;
        }

        // on_data_available
        template <typename HANDLER>
        void handle_data_available_event (typename IDL::traits<HANDLER>::ref_type dh)
        {
          using DataListenerExec_type = PSDDDataListenerExecutor<listener_type, HANDLER>;

          try
          {
            CIAOX11::ExF::Executor::ref_type exec =
                std::make_unique<DataListenerExec_type> (
                    this->data_available_exf_settings_,
                    std::move(dh),
                    this->listener_);

            this->scheduling_lane_->submit (std::move (exec));
          }
          catch (const std::bad_alloc&)
          {
            PSDD4CCM_LOG_ERROR ("ExF::PushConsumerEventStrategy_T<CCM_TYPE>::handle_data_available_event - no memory");
          }
        }

      private:
        PushConsumerEventStrategy_T (PushConsumerEventStrategy_T&&) = delete;
        PushConsumerEventStrategy_T& operator=(PushConsumerEventStrategy_T&&) = delete;

        typename IDL::traits<listener_type>::weak_ref_type listener_ {};

        CIAOX11::ExF::Settings data_available_exf_settings_ {};
      };

    } /* ExF */
  } /* PSDD4CCM */
} /* CIAOX11 */

#endif /* PSDD4CCM_EXF_EVENT_STRATEGIES_T_H_ */
