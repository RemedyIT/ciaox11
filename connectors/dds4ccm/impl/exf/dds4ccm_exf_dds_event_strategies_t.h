// -*- C++ -*-
/**
 * @file    dds4ccm_exf_dds_event_strategies_t.h
 * @author  Martin Corino
 *
 * @brief   Implements the event handling strategies for ExF from DDS to DDS4CCM
 *
 *          The class members (listener and datareader/datawriter) are passed
 *          as weak references. We don't want to influence the life cycle of
 *          entities here.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_EXF_DDS_EVENT_STRATEGIES_T_H_
#define DDS4CCM_EXF_DDS_EVENT_STRATEGIES_T_H_

#include "exf/deployment/core/ciaox11_exf_util.h"
#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/logger/dds4ccm_log.h"

#include "dds4ccm/impl/exf/dds4ccm_exf_dds_event_executors.h"


namespace CIAOX11
{
  namespace DDS4CCM
  {
    namespace ExF
    {
      class EventStrategyBase
      {
      public:
        using uses_context_switch = std::true_type;
        static constexpr const char* context_switch_type = "ExF";

      protected:
        EventStrategyBase (const Components::ConfigValues &config)
        {
          DDS4CCM_LOG_TRACE ("ExF::EventStrategyBase::" << "ctor");

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
        EventStrategyBase (const EventStrategyBase& evs)
          : scheduling_lane_ (evs.scheduling_lane_) {}

      public:
        virtual ~EventStrategyBase () {}

      private:
        EventStrategyBase (EventStrategyBase&&) = delete;
        EventStrategyBase& operator=(const EventStrategyBase&) = delete;
        EventStrategyBase& operator=(EventStrategyBase&&) = delete;

      protected:
        IDL::traits<CIAOX11::ExF::SchedulingLane>::ref_type scheduling_lane_ {};
      };

      template <typename CCM_TYPE>
      class ErrorEventStrategy_T
        : public EventStrategyBase
      {
      public:
        ErrorEventStrategy_T (
          typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
          : EventStrategyBase (ctx->error_listener_configuration ())
        {
          IDL::traits< CCM_DDS::ConnectorStatusListener>::ref_type erl =
              ctx->get_connection_error_listener ();
          this->error_listener_ = erl;
          if (erl)
            this->error_listener_connected_ = true;

          if (this->scheduling_lane_)
          {
            const Components::ConfigValues &config =
                ctx->error_listener_configuration ();
            // get scheduling settings
            CIAOX11::ExF::Priority def_prio {};
            CIAOX11::ExF::Deadline def_deadline {};
            if (CIAOX11::ExF::Util::get_exf_defaults (
                    config, def_prio, def_deadline))
            {

              this->unexpected_status_deadline_ = def_deadline;
              this->unexpected_status_priority_ = def_prio;
              this->requested_incompatible_qos_deadline_ = def_deadline;
              this->requested_incompatible_qos_priority_ = def_prio;
              this->sample_rejected_deadline_ = def_deadline;
              this->sample_rejected_priority_ = def_prio;
              this->inconsistent_topic_deadline_ = def_deadline;
              this->inconsistent_topic_priority_ = def_prio;
              this->offered_deadline_missed_deadline_ = def_deadline;
              this->offered_deadline_missed_priority_ = def_prio;
              this->offered_incompatible_qos_deadline_ = def_deadline;
              this->offered_incompatible_qos_priority_ = def_prio;
            }

            // check for scheduling properties

            CIAOX11::ExF::Util::get_exf_settings (
                config,
                "unexpected_status",
                this->unexpected_status_priority_,
                this->unexpected_status_deadline_);

            CIAOX11::ExF::Util::get_exf_settings (
                config,
                "requested_incompatible_qos",
                this->requested_incompatible_qos_priority_,
                this->requested_incompatible_qos_deadline_);

            CIAOX11::ExF::Util::get_exf_settings (
                config,
                "sample_rejected",
                this->sample_rejected_priority_,
                this->sample_rejected_deadline_);

            CIAOX11::ExF::Util::get_exf_settings (
                config,
                "inconsistent_topic",
                this->inconsistent_topic_priority_,
                this->inconsistent_topic_deadline_);

            CIAOX11::ExF::Util::get_exf_settings (
                config,
                "offered_deadline_missed",
                this->offered_deadline_missed_priority_,
                this->offered_deadline_missed_deadline_);

            CIAOX11::ExF::Util::get_exf_settings (
                config,
                "offered_incompatible_qos",
                this->offered_incompatible_qos_priority_,
                this->offered_incompatible_qos_deadline_);
          }
        }
        ErrorEventStrategy_T (const ErrorEventStrategy_T& evs)
          : EventStrategyBase (evs)
          , error_listener_ (evs.error_listener_)
          , error_listener_connected_ (evs.error_listener_connected_)
          , unexpected_status_deadline_ (evs.unexpected_status_deadline_)
          , unexpected_status_priority_ (evs.unexpected_status_priority_)
          , requested_incompatible_qos_deadline_ (evs.requested_incompatible_qos_deadline_)
          , requested_incompatible_qos_priority_ (evs.requested_incompatible_qos_priority_)
          , sample_rejected_deadline_ (evs.sample_rejected_deadline_)
          , sample_rejected_priority_ (evs.sample_rejected_priority_)
          , inconsistent_topic_deadline_ (evs.inconsistent_topic_deadline_)
          , inconsistent_topic_priority_ (evs.inconsistent_topic_priority_)
          , offered_deadline_missed_deadline_ (evs.offered_deadline_missed_deadline_)
          , offered_deadline_missed_priority_ (evs.offered_deadline_missed_priority_)
          , offered_incompatible_qos_deadline_ (evs.offered_incompatible_qos_deadline_)
          , offered_incompatible_qos_priority_ (evs.offered_incompatible_qos_priority_)
        {}
        virtual ~ErrorEventStrategy_T () = default;

        // on_unexpected_status
        void
        handle_unexpected_status_event (
            IDL::traits< ::DDS::Entity>::ref_type entity,
            ::DDS::StatusKind status_kind)
        {
          if (!this->error_listener_connected_)
          {
            DDS4CCM_LOG_DEBUG ("ErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_unexpected_status_event" <<
                " - received <" <<
                status_kind << "> but no error listener connected");
          }
          else
          {
            try
            {
              CIAOX11::ExF::Executor::ref_type exec =
                  std::make_unique<UnexpectedStatusExecutor> (
                      this->unexpected_status_priority_,
                      this->unexpected_status_deadline_,
                      this->error_listener_,
                      std::move(entity), status_kind);

              this->scheduling_lane_->submit (std::move (exec));
            }
            catch (const std::bad_alloc&)
            {
              DDS4CCM_LOG_ERROR ("ErrorEventStrategy_T<CCM_TYPE>::handle_unexpected_status_event - no memory");
            }
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
            DDS4CCM_LOG_DEBUG ("ErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_requested_incompatible_qos_event" <<
                " - received <" <<
                status << "> but no error listener connected");
          }
          else
          {
            try
            {
              CIAOX11::ExF::Executor::ref_type exec =
                  std::make_unique<RequestedIncompatibleQosExecutor> (
                      this->requested_incompatible_qos_priority_,
                      this->requested_incompatible_qos_deadline_,
                      this->error_listener_,
                      std::move(dr), status);

              this->scheduling_lane_->submit (std::move (exec));
            }
            catch (const std::bad_alloc&)
            {
              DDS4CCM_LOG_ERROR ("ErrorEventStrategy_T<CCM_TYPE>::handle_requested_incompatible_qos_event - no memory");
            }
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
            DDS4CCM_LOG_DEBUG ("ErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_sample_rejected_event" <<
                " - received <" <<
                status << "> but no error listener connected");
          }
          else
          {
            try
            {
              CIAOX11::ExF::Executor::ref_type exec =
                  std::make_unique<SampleRejectedExecutor> (
                      this->sample_rejected_priority_,
                      this->sample_rejected_deadline_,
                      this->error_listener_,
                      std::move(dr), status);

              this->scheduling_lane_->submit (std::move (exec));
            }
            catch (const std::bad_alloc&)
            {
              DDS4CCM_LOG_ERROR ("ErrorEventStrategy_T<CCM_TYPE>::handle_sample_rejected_event - no memory");
            }
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
            DDS4CCM_LOG_DEBUG ("ErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_inconsistent_topic_event" <<
                " - received <" <<
                status << "> but no error listener connected");
          }
          else
          {
            try
            {
              CIAOX11::ExF::Executor::ref_type exec =
                  std::make_unique<InconsistentTopicExecutor> (
                      this->sample_rejected_priority_,
                      this->sample_rejected_deadline_,
                      this->error_listener_,
                      std::move(tp), status);

              this->scheduling_lane_->submit (std::move (exec));
            }
            catch (const std::bad_alloc&)
            {
              DDS4CCM_LOG_ERROR ("ErrorEventStrategy_T<CCM_TYPE>::handle_inconsistent_topic_event - no memory");
            }
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
            DDS4CCM_LOG_DEBUG ("ErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_offered_deadline_missed_event" <<
                " - received <" <<
                status << "> but no error listener connected");
          }
          else
          {
            try
            {
              CIAOX11::ExF::Executor::ref_type exec =
                  std::make_unique<OfferedDeadlineMissedExecutor> (
                      this->sample_rejected_priority_,
                      this->sample_rejected_deadline_,
                      this->error_listener_,
                      std::move(dw), status);

              this->scheduling_lane_->submit (std::move (exec));
            }
            catch (const std::bad_alloc&)
            {
              DDS4CCM_LOG_ERROR ("ErrorEventStrategy_T<CCM_TYPE>::handle_offered_deadline_missed_event - no memory");
            }
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
            DDS4CCM_LOG_DEBUG ("ErrorEventStrategy_T<CCM_TYPE>::" <<
                "handle_offered_incompatible_qos_event" <<
                " - received <" <<
                status << "> but no error listener connected");
          }
          else
          {
            try
            {
              CIAOX11::ExF::Executor::ref_type exec =
                  std::make_unique<OfferedIncompatibleQoSExecutor> (
                      this->sample_rejected_priority_,
                      this->sample_rejected_deadline_,
                      this->error_listener_,
                      std::move(dw), status);

              this->scheduling_lane_->submit (std::move (exec));
            }
            catch (const std::bad_alloc&)
            {
              DDS4CCM_LOG_ERROR ("ErrorEventStrategy_T<CCM_TYPE>::handle_offered_incompatible_qos_event - no memory");
            }
          }
        }

      private:
        ErrorEventStrategy_T (ErrorEventStrategy_T&&) = delete;
        ErrorEventStrategy_T& operator=(const ErrorEventStrategy_T&) = delete;
        ErrorEventStrategy_T& operator=(ErrorEventStrategy_T&&) = delete;

        IDL::traits<CCM_DDS::ConnectorStatusListener>::weak_ref_type error_listener_ {};
        bool error_listener_connected_ {};

        CIAOX11::ExF::Deadline unexpected_status_deadline_ {};
        CIAOX11::ExF::Priority unexpected_status_priority_ {};
        CIAOX11::ExF::Deadline requested_incompatible_qos_deadline_ {};
        CIAOX11::ExF::Priority requested_incompatible_qos_priority_ {};
        CIAOX11::ExF::Deadline sample_rejected_deadline_ {};
        CIAOX11::ExF::Priority sample_rejected_priority_ {};
        CIAOX11::ExF::Deadline inconsistent_topic_deadline_ {};
        CIAOX11::ExF::Priority inconsistent_topic_priority_ {};
        CIAOX11::ExF::Deadline offered_deadline_missed_deadline_ {};
        CIAOX11::ExF::Priority offered_deadline_missed_priority_ {};
        CIAOX11::ExF::Deadline offered_incompatible_qos_deadline_ {};
        CIAOX11::ExF::Priority offered_incompatible_qos_priority_ {};
      };

      class PortStatusEventStrategyBase
        : public EventStrategyBase
      {
      protected:
        PortStatusEventStrategyBase (
          const Components::ConfigValues &port_status_config,
          IDL::traits < ::CCM_DDS::PortStatusListener>::ref_type port_status_listener)
          : EventStrategyBase (port_status_config)
          , status_listener_ (port_status_listener)
        {
          if (this->scheduling_lane_)
          {
            // get scheduling settings
            CIAOX11::ExF::Priority def_prio {};
            CIAOX11::ExF::Deadline def_deadline {};
            if (CIAOX11::ExF::Util::get_exf_defaults (
                port_status_config, def_prio, def_deadline))
            {

              this->requested_deadline_missed_deadline_ = def_deadline;
              this->requested_deadline_missed_priority_ = def_prio;
              this->sample_lost_deadline_ = def_deadline;
              this->sample_lost_priority_ = def_prio;
            }

            // check for scheduling properties

            CIAOX11::ExF::Util::get_exf_settings (
                port_status_config,
                "requested_deadline_missed",
                this->requested_deadline_missed_priority_,
                this->requested_deadline_missed_deadline_);

            CIAOX11::ExF::Util::get_exf_settings (
                port_status_config,
                "sample_lost",
                this->sample_lost_priority_,
                this->sample_lost_deadline_);
          }
        }
        PortStatusEventStrategyBase (const PortStatusEventStrategyBase& pses)
          : EventStrategyBase (pses)
          , status_listener_ (pses.status_listener_)
        , requested_deadline_missed_deadline_ (pses.requested_deadline_missed_deadline_)
        , requested_deadline_missed_priority_ (pses.requested_deadline_missed_priority_)
        , sample_lost_deadline_ (pses.sample_lost_deadline_)
        , sample_lost_priority_ (pses.sample_lost_priority_)
        {}
      public:
        virtual ~PortStatusEventStrategyBase () = default;

        // on_requested_deadline_missed
        void
        handle_requested_deadline_missed_event (
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::RequestedDeadlineMissedStatus &status)
        {
          try
          {
            CIAOX11::ExF::Executor::ref_type exec =
                std::make_unique<RequestedDeadlineMissedExecutor> (
                    this->requested_deadline_missed_priority_,
                    this->requested_deadline_missed_deadline_,
                    this->status_listener_,
                    std::move(dr), status);

            this->scheduling_lane_->submit (std::move (exec));
          }
          catch (const std::bad_alloc&)
          {
            DDS4CCM_LOG_ERROR ("PortStatusEventStrategyBase::handle_requested_deadline_missed_event - no memory");
          }
        }

        // on_sample_lost
        void
        handle_sample_lost_event (
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::SampleLostStatus &status)
        {
          try
          {
            CIAOX11::ExF::Executor::ref_type exec =
                std::make_unique<SampleLostExecutor> (
                    this->sample_lost_priority_,
                    this->sample_lost_deadline_,
                    this->status_listener_,
                    std::move(dr), status);

            this->scheduling_lane_->submit (std::move (exec));
          }
          catch (const std::bad_alloc&)
          {
            DDS4CCM_LOG_ERROR ("PortStatusEventStrategyBase::handle_sample_lost_event - no memory");
          }
        }

      private:
        PortStatusEventStrategyBase (PortStatusEventStrategyBase&&) = delete;
        PortStatusEventStrategyBase& operator=(const PortStatusEventStrategyBase&) = delete;
        PortStatusEventStrategyBase& operator=(PortStatusEventStrategyBase&&) = delete;

        IDL::traits < ::CCM_DDS::PortStatusListener>::weak_ref_type status_listener_ {};

        CIAOX11::ExF::Deadline requested_deadline_missed_deadline_ {};
        CIAOX11::ExF::Priority requested_deadline_missed_priority_ {};
        CIAOX11::ExF::Deadline sample_lost_deadline_ {};
        CIAOX11::ExF::Priority sample_lost_priority_ {};
      };

      template <typename DATA_LISTENER>
      class DataEventStrategyBase_T
        : public PortStatusEventStrategyBase
      {
      protected:
        DataEventStrategyBase_T (
          const Components::ConfigValues &port_status_config,
          IDL::traits < ::CCM_DDS::PortStatusListener>::ref_type port_status_listener,
          const Components::ConfigValues &data_listener_config,
          typename IDL::traits < DATA_LISTENER>::ref_type data_listener)
          : PortStatusEventStrategyBase (port_status_config, port_status_listener)
          , data_listener_ (data_listener)
        {
          DDS4CCM_LOG_TRACE ("ExF::DataEventStrategyBase_T<DATA_LISTENER>::" << "ctor");

          // since it is theoretically possible the data listener is connected
          // from a different component (with a different scheduling lane) than
          // the status listener we have to retrieve the scheduling lane for
          // for the data events separately
          for (const Components::ConfigValue& cval : data_listener_config)
          {
            if (cval.name () == CIAOX11::ExF::SCHEDULING_LANE_REF)
            {
              IDL::traits<CORBA::Object>::ref_type objref {};
              if (!(cval.value () >>= objref))
              {
                throw std::runtime_error (
                    "ExF::DataEventStrategyBase_T<DATA_LISTENER>: failed to extract " +
                    CIAOX11::ExF::SCHEDULING_LANE_REF);
              }
              this->data_scheduling_lane_ =
                  IDL::traits<CIAOX11::ExF::SchedulingLane>::narrow (objref);
            }

            if (this->data_scheduling_lane_)
            {
              // get scheduling settings
              CIAOX11::ExF::Priority def_prio {};
              CIAOX11::ExF::Deadline def_deadline {};
              if (CIAOX11::ExF::Util::get_exf_defaults (
                  data_listener_config, def_prio, def_deadline))
              {

                this->data_available_deadline_ = def_deadline;
                this->data_available_priority_ = def_prio;
              }

              // check for scheduling properties

              CIAOX11::ExF::Util::get_exf_settings (
                  data_listener_config,
                  "data_available",
                  this->data_available_priority_,
                  this->data_available_deadline_);
            }

          }
        }
        DataEventStrategyBase_T (const DataEventStrategyBase_T& des)
          : PortStatusEventStrategyBase (des)
          , data_listener_ (des.data_listener_)
          , data_scheduling_lane_ (des.data_scheduling_lane_)
          , data_available_deadline_ (des.data_available_deadline_)
          , data_available_priority_ (des.data_available_priority_)
        {}
      public:
        virtual ~DataEventStrategyBase_T () = default;

        // on_data_available
        template <typename LISTENER>
        void handle_data_available_event (
            typename IDL::traits<LISTENER>::ref_type drl,
            IDL::traits< ::DDS::DataReader>::ref_type dr)
        {
          typedef DataReaderExecutor_T<LISTENER, DATA_LISTENER> DataReaderExec_type;

          try
          {
            CIAOX11::ExF::Executor::ref_type exec =
                std::make_unique<DataReaderExec_type> (
                    this->data_available_priority_,
                    this->data_available_deadline_,
                    this->data_listener_,
                    std::move(drl), std::move(dr));

            this->data_scheduling_lane_->submit (std::move (exec));
          }
          catch (const std::bad_alloc&)
          {
            DDS4CCM_LOG_ERROR ("DataEventStrategyBase_T<DATA_LISTENER>::handle_data_available_event - no memory");
          }
        }

      private:
        DataEventStrategyBase_T (DataEventStrategyBase_T&&) = delete;
        DataEventStrategyBase_T& operator=(const DataEventStrategyBase_T&) = delete;
        DataEventStrategyBase_T& operator=(DataEventStrategyBase_T&&) = delete;

        typename IDL::traits <DATA_LISTENER>::weak_ref_type data_listener_ {};

        IDL::traits<CIAOX11::ExF::SchedulingLane>::ref_type data_scheduling_lane_ {};
        CIAOX11::ExF::Deadline data_available_deadline_ {};
        CIAOX11::ExF::Priority data_available_priority_ {};
      };

      template <typename CCM_TYPE>
      class PushConsumerEventStrategy_T
        : public DataEventStrategyBase_T<
            typename CCM_TYPE::push_consumer_traits::data_listener_type>
      {
      public:
        PushConsumerEventStrategy_T (
          typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
          : DataEventStrategyBase_T<
              typename CCM_TYPE::push_consumer_traits::data_listener_type> (
                  ctx->push_consumer_status_configuration (),
                  ctx->get_connection_push_consumer_status (),
                  ctx->push_consumer_data_listener_configuration (),
                  ctx->get_connection_push_consumer_data_listener ())
        {}
        PushConsumerEventStrategy_T (const PushConsumerEventStrategy_T& pces)
          : DataEventStrategyBase_T<
              typename CCM_TYPE::push_consumer_traits::data_listener_type> (pces)
        {}
        virtual ~PushConsumerEventStrategy_T () = default;
      };

      template <typename CCM_TYPE>
      class PullConsumerEventStrategy_T
        : public PortStatusEventStrategyBase
      {
      public:
        PullConsumerEventStrategy_T (
          typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
          : PortStatusEventStrategyBase (
                  ctx->pull_consumer_status_configuration (),
                  ctx->get_connection_pull_consumer_status ())
        {}
        PullConsumerEventStrategy_T (const PullConsumerEventStrategy_T& pces)
          : PortStatusEventStrategyBase (pces)
        {}
        virtual ~PullConsumerEventStrategy_T () = default;
      };

      template <typename CCM_TYPE>
      class PassiveObserverEventStrategy_T
        : public PortStatusEventStrategyBase
      {
      public:
        PassiveObserverEventStrategy_T (
          typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
          : PortStatusEventStrategyBase (
                  ctx->passive_observer_status_configuration (),
                  ctx->get_connection_passive_observer_status ())
        {}
        PassiveObserverEventStrategy_T (const PassiveObserverEventStrategy_T& poes)
          : PortStatusEventStrategyBase (poes)
        {}
        virtual ~PassiveObserverEventStrategy_T () = default;
      };

      template <typename CCM_TYPE>
      class PullObserverEventStrategy_T
        : public PortStatusEventStrategyBase
      {
      public:
        PullObserverEventStrategy_T (
          typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
          : PortStatusEventStrategyBase (
                  ctx->pull_observer_status_configuration (),
                  ctx->get_connection_pull_observer_status ())
        {}
        PullObserverEventStrategy_T (const PullObserverEventStrategy_T& poes)
          : PortStatusEventStrategyBase (poes)
        {}
        virtual ~PullObserverEventStrategy_T () = default;
      };

      template <typename CCM_TYPE>
      class PushObserverEventStrategy_T
        : public DataEventStrategyBase_T<
            typename CCM_TYPE::push_observer_traits::data_listener_type>
      {
      public:
        PushObserverEventStrategy_T (
          typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
          : DataEventStrategyBase_T<
              typename CCM_TYPE::push_observer_traits::data_listener_type> (
                  ctx->push_observer_status_configuration (),
                  ctx->get_connection_push_observer_status (),
                  ctx->push_observer_data_listener_configuration (),
                  ctx->get_connection_push_observer_data_listener ())
        {}
        PushObserverEventStrategy_T (const PushObserverEventStrategy_T& poes)
          : DataEventStrategyBase_T<
              typename CCM_TYPE::push_observer_traits::data_listener_type> (poes)
        {}
        virtual ~PushObserverEventStrategy_T () = default;
      };

      template <typename CCM_TYPE>
      class PushStateObserverEventStrategy_T
        : public DataEventStrategyBase_T<
            typename CCM_TYPE::push_state_observer_traits::data_listener_type>
      {
      public:
        PushStateObserverEventStrategy_T (
          typename IDL::traits<typename CCM_TYPE::context_type>::ref_type ctx)
          : DataEventStrategyBase_T<
              typename CCM_TYPE::push_state_observer_traits::data_listener_type> (
                  ctx->push_state_observer_status_configuration (),
                  ctx->get_connection_push_state_observer_status (),
                  ctx->push_state_observer_data_listener_configuration (),
                  ctx->get_connection_push_state_observer_data_listener ())
        {}
        PushStateObserverEventStrategy_T (const PushStateObserverEventStrategy_T& psoes)
          : DataEventStrategyBase_T<
              typename CCM_TYPE::push_state_observer_traits::data_listener_type> (psoes)
        {}
        virtual ~PushStateObserverEventStrategy_T () = default;
      };

    } /* namespace ExF */

  } /* namespace DDS4CCM */

} /* namespace CIAOX11 */

#endif /* DDS4CCM_EXF_DDS_EVENT_STRATEGIES_T_H_ */
