// -*- C++ -*-
/**
 * @file    dds4ccm_exf_dds_event_executors.h
 * @author  Martin Corino
 *
 * @brief   Implements the event handling strategies for ExF from DDS to DDS4CCM
 *
 *          The class members (listener and datareader/datawriter) are passed
 *          as weak references. We don't want to influence the life cycle of
 *          entities here.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_EXF_DDS_EVENT_EXECUTORS_H_
#define DDS4CCM_EXF_DDS_EVENT_EXECUTORS_H_

#include "exf/deployment/core/ciaox11_schedule.h"
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/idl/dds_rtf2_dcpsC.h"
#include "dds4ccm/idl/dds4ccm_connector_status_listenerC.h"
#include "dds4ccm/idl/dds4ccm_port_status_listenerC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    namespace ExF
    {
      using namespace CIAOX11::ExF;

      template <typename LISTENER>
      class DDSExecutorBase
        : public ExF::Executor
      {
      public:
        DDSExecutorBase (
            ExF::Priority prio,
            ExF::Deadline dltm,
            typename IDL::traits<LISTENER>::weak_ref_type lsn,
            std::string evtid)
          : Executor (prio, dltm)
          , listener_ (std::move (lsn))
          , event_id_ (std::move (evtid))
        {}
        virtual ~DDSExecutorBase () = default;

        void execute () noexcept(true) override
        {
          try
          {
            this->execute_i (this->listener_.lock ());
          }
          catch (const std::exception& ex)
          {
            DDS4CCM_LOG_ERROR ("DDS4CCM::ExF::ErrorExecutorBase::execute " <<
                               "caught exception [" << ex << ']' <<
                               " for event_id: " << this->event_id_);
          }
          catch (...)
          {
            DDS4CCM_LOG_ERROR ("DDS4CCM::ExF::ErrorExecutorBase::execute " <<
                               "caught unknown C++ exception" <<
                               " for event_id: " << this->event_id_);
          }
        }

        void finish () noexcept(true) override {}

        void cancel (
            ExF::CancellationType ctyp) noexcept(true) override
        {
          if (ctyp == CIAOX11::ExF::CancellationType::CT_SHUTDOWN)
            DDS4CCM_LOG_INFO ("DDS4CCM::ExF::ErrorExecutorBase::cancel received " <<
                              "CT_SHUTDOWN" << " for event_id: " << this->event_id_);
          else
            DDS4CCM_LOG_INFO ("DDS4CCM::ExF::ErrorExecutorBase::cancel received " <<
                              "CT_TIMEOUT" << " for event_id: " << this->event_id_);
        }

        const std::string& event_id () const noexcept(true) override
        {
          return this->event_id_;
        }

      protected:
        virtual void execute_i (typename IDL::traits<LISTENER>::ref_type) = 0;

      private:
        typename IDL::traits<LISTENER>::weak_ref_type listener_ {};
        std::string event_id_;
      };

      class UnexpectedStatusExecutor
        : public DDSExecutorBase<CCM_DDS::ConnectorStatusListener>
      {
      public:
        UnexpectedStatusExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits<CCM_DDS::ConnectorStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::Entity>::ref_type entity,
            ::DDS::StatusKind status_kind)
          : DDSExecutorBase<CCM_DDS::ConnectorStatusListener> (
              prio, dltm, lsn, "unexpected_status")
          , entity_ (entity)
          , status_kind_ (status_kind)
        {}
        virtual ~UnexpectedStatusExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::Entity>::ref_type entity = this->entity_.lock ();
          if (entity && listener)
          {
            listener->on_unexpected_status (std::move(entity), this->status_kind_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("UnexpectedStatusExecutor::execute_i - "
              << "Unable to acquire references to the Connector Status Listener, "
              << "to the Entity, or to both - Unable to invoke 'on_unexpected_status' for <"
              << this->status_kind_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::Entity >::weak_ref_type entity_;
        ::DDS::StatusKind status_kind_;
      };

      class RequestedIncompatibleQosExecutor
        : public DDSExecutorBase<CCM_DDS::ConnectorStatusListener>
      {
      public:
        RequestedIncompatibleQosExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits<CCM_DDS::ConnectorStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::RequestedIncompatibleQosStatus &status)
          : DDSExecutorBase<CCM_DDS::ConnectorStatusListener> (
              prio, dltm, lsn, "requested_incompatible_qos")
          , dr_ (dr)
          , status_ (status)
        {}
        virtual ~RequestedIncompatibleQosExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::DataReader>::ref_type dr = this->dr_.lock ();
          if (dr && listener)
          {
            listener->on_requested_incompatible_qos (std::move(dr), this->status_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("RequestedIncompatibleQosExecutor::execute_i - "
                << "Unable to acquire references to the Connector Status Listener, "
                << "to the DataReader, or to both - Unable to invoke 'on_requested_incompatible_qos' for <"
                << this->status_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::RequestedIncompatibleQosStatus const status_;
      };

      class SampleRejectedExecutor
        : public DDSExecutorBase<CCM_DDS::ConnectorStatusListener>
      {
      public:
        SampleRejectedExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits<CCM_DDS::ConnectorStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::SampleRejectedStatus &status)
          : DDSExecutorBase<CCM_DDS::ConnectorStatusListener> (
              prio, dltm, lsn, "sample_rejected")
          , dr_ (dr)
          , status_ (status)
        {}
        virtual ~SampleRejectedExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::DataReader>::ref_type dr = this->dr_.lock ();
          if (dr && listener)
          {
            listener->on_sample_rejected (std::move(dr), this->status_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("SampleRejectedExecutor::execute_i - "
                << "Unable to acquire references to the Connector Status Listener, "
                << "to the DataReader, or to both - Unable to invoke 'on_sample_rejected' for <"
                << this->status_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::SampleRejectedStatus const status_;
      };

      class InconsistentTopicExecutor
        : public DDSExecutorBase<CCM_DDS::ConnectorStatusListener>
      {
      public:
        InconsistentTopicExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits< CCM_DDS::ConnectorStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::Topic>::ref_type tp,
            const ::DDS::InconsistentTopicStatus &status)
          : DDSExecutorBase<CCM_DDS::ConnectorStatusListener> (
              prio, dltm, lsn, "inconsistent_topic")
          , tp_ (tp)
          , status_ (status)
        {}
        virtual ~InconsistentTopicExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::Topic>::ref_type tp = this->tp_.lock ();
          if (tp && listener)
          {
            listener->on_inconsistent_topic (std::move(tp), this->status_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("InconsistentTopicExecutor::execute_i - "
                << "Unable to acquire references to the Connector Status Listener, "
                << "to the Topic, or to both - Unable to invoke 'on_inconsistent_topic' for <"
                << this->status_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::Topic >::weak_ref_type tp_;
        ::DDS::InconsistentTopicStatus const status_;
      };

      class OfferedDeadlineMissedExecutor
        : public DDSExecutorBase<CCM_DDS::ConnectorStatusListener>
      {
      public:
        OfferedDeadlineMissedExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits<CCM_DDS::ConnectorStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::DataWriter>::ref_type dw,
            const ::DDS::OfferedDeadlineMissedStatus &status)
          : DDSExecutorBase<CCM_DDS::ConnectorStatusListener> (
              prio, dltm, lsn, "offered_deadline_missed")
          , dw_ (dw)
          , status_ (status)
        {}
        virtual ~OfferedDeadlineMissedExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::DataWriter>::ref_type dw = this->dw_.lock ();
          if (dw && listener)
          {
            listener->on_offered_deadline_missed (std::move(dw), this->status_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("OfferedDeadlineMissedExecutor::execute_i - "
                << "Unable to acquire references to the Connector Status Listener, "
                << "to the DataWriter, or to both - Unable to invoke 'on_offered_deadline_missed' for <"
                << this->status_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::DataWriter>::weak_ref_type dw_;
        ::DDS::OfferedDeadlineMissedStatus const status_;
      };

      class OfferedIncompatibleQoSExecutor
        : public DDSExecutorBase<CCM_DDS::ConnectorStatusListener>
      {
      public:
        OfferedIncompatibleQoSExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits<CCM_DDS::ConnectorStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::DataWriter>::ref_type dw,
            const ::DDS::OfferedIncompatibleQosStatus &status)
          : DDSExecutorBase<CCM_DDS::ConnectorStatusListener> (
              prio, dltm, lsn, "offered_deadline_missed")
          , dw_ (dw)
          , status_ (status)
        {}
        virtual ~OfferedIncompatibleQoSExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::ConnectorStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::DataWriter>::ref_type dw = this->dw_.lock ();
          if (dw && listener)
          {
            listener->on_offered_incompatible_qos (std::move(dw), this->status_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("OfferedDeadlineMissedExecutor::execute_i - "
                << "Unable to acquire references to the Connector Status Listener, "
                << "to the DataWriter, or to both - Unable to invoke 'on_offered_deadline_missed' for <"
                << this->status_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::DataWriter>::weak_ref_type dw_;
        ::DDS::OfferedIncompatibleQosStatus const status_;
      };

      class RequestedDeadlineMissedExecutor
        : public DDSExecutorBase<CCM_DDS::PortStatusListener>
      {
      public:
        RequestedDeadlineMissedExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits<CCM_DDS::PortStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::RequestedDeadlineMissedStatus &status)
          : DDSExecutorBase<CCM_DDS::PortStatusListener> (
              prio, dltm, lsn, "requested_deadline_missed")
          , dr_ (dr)
          , status_ (status)
        {}
        virtual ~RequestedDeadlineMissedExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::PortStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::DataReader>::ref_type dr = this->dr_.lock ();
          if (dr && listener)
          {
            listener->on_requested_deadline_missed (std::move(dr), this->status_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("OfferedDeadlineMissedExecutor::execute_i - "
                << "Unable to acquire references to the Port Status Listener, "
                << "to the DataReader, or to both - Unable to invoke 'on_requested_deadline_missed' for <"
                << this->status_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::RequestedDeadlineMissedStatus const status_;
      };

      class SampleLostExecutor
        : public DDSExecutorBase<CCM_DDS::PortStatusListener>
      {
      public:
        SampleLostExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            IDL::traits<CCM_DDS::PortStatusListener>::weak_ref_type lsn,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::SampleLostStatus &status)
          : DDSExecutorBase<CCM_DDS::PortStatusListener> (
              prio, dltm, lsn, "sample_lost")
          , dr_ (dr)
          , status_ (status)
        {}
        virtual ~SampleLostExecutor () = default;

      protected:
        virtual void execute_i (IDL::traits<CCM_DDS::PortStatusListener>::ref_type listener)
        {
          IDL::traits< ::DDS::DataReader>::ref_type dr = this->dr_.lock ();
          if (dr && listener)
          {
            listener->on_sample_lost (std::move(dr), this->status_);
          }
          else
          {
            DDS4CCM_LOG_ERROR ("OfferedDeadlineMissedExecutor::execute_i - "
                << "Unable to acquire references to the Port Status Listener, "
                << "to the DataReader, or to both - Unable to invoke 'on_sample_lost' for <"
                << this->status_ << ">.");
          }
        }

      private:
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::SampleLostStatus const status_;
      };

      template <typename LISTENER, typename DATA_LISTENER>
      class DataReaderExecutor_T
        : public DDSExecutorBase<DATA_LISTENER>
      {
      public:
        DataReaderExecutor_T (
            ExF::Priority prio,
            ExF::Deadline dltm,
            typename IDL::traits<DATA_LISTENER>::weak_ref_type lsn,
            typename IDL::traits<LISTENER>::ref_type drl,
            IDL::traits< ::DDS::DataReader>::ref_type dr)
          : DDSExecutorBase<DATA_LISTENER> (
              prio, dltm, lsn, "data_available")
          , drl_ (std::move(drl))
          , dr_ (std::move(dr))
        {}
        virtual ~DataReaderExecutor_T () = default;

      protected:
        virtual void execute_i (typename IDL::traits<DATA_LISTENER>::ref_type listener)
        {
          typename IDL::traits<LISTENER>::ref_type drl = this->drl_.lock ();
          IDL::traits< ::DDS::DataReader>::ref_type dr = this->dr_.lock ();
          if (drl && listener)
          {
            drl->on_data_available_i (std::move(dr), std::move(listener));
          }
          else
          {
            DDS4CCM_LOG_ERROR ("DataReaderExecutor_T<LISTENER,DATA_LISTENER>::execute_i - "
                "No DataReaderListener or user Listener implementation found.");
          }
        }

      private:
        /// The weak reference to the data reader listener.
        typename IDL::traits<LISTENER>::weak_ref_type drl_;
        /// The weak reference to the data reader
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
      };
    }
  }
}


#endif /* DDS4CCM_EXF_DDS_EVENT_EXECUTORS_H_ */
