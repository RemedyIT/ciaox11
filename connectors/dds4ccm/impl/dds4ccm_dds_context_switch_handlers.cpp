// -*- C++ -*-
/**
 * @file    dds4ccm_dds_context_switch_handlers.cpp
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_dds_context_switch_handlers.h"
#include "dds4ccm/impl/dds4ccm_utils.h"
#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    DDSContextSwitchHandlerBase::DDSContextSwitchHandlerBase ()
    {
      this->reference_counting_policy ().value
        (ACE_Event_Handler::Reference_Counting_Policy::ENABLED);
    }


    //============================================================
    // On_Unexpected_Status_Handler
    //============================================================
    OnUnexpectedStatusHandler::OnUnexpectedStatusHandler (
      IDL::traits< ::CCM_DDS::ConnectorStatusListener >::weak_ref_type csl,
      IDL::traits< ::DDS::Entity >::ref_type entity,
      ::DDS::StatusKind status_kind)
      : csl_ (std::move (csl))
      , entity_ (entity.weak_reference ())
      , status_kind_ (status_kind)
    {
    }

    int
    OnUnexpectedStatusHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (
          this->csl_.lock (),
          this->entity_.lock (),
          this->status_kind_);
      return 0;
    }


    void
    OnUnexpectedStatusHandler::handle_event (
        IDL::traits< ::CCM_DDS::ConnectorStatusListener >::ref_type csl,
        IDL::traits< ::DDS::Entity >::ref_type entity,
        ::DDS::StatusKind status_kind)
    {
      try
      {
        if (entity && csl)
        {
          csl->on_unexpected_status (std::move(entity), status_kind);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnUnexpectedStatusHandler::handle_event - "
            << "Unable to acquire references to the Connector Status Listener, "
            << "to the Entity, or to both - Unable to invoke 'on_unexpected_status' for <"
            << status_kind << ">.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnUnexpectedStatusHandler::handle_event")
    }

    //============================================================
    // OnRequestedIncompatibleQosHandler
    //============================================================
    OnRequestedIncompatibleQosHandler::OnRequestedIncompatibleQosHandler (
      IDL::traits< ::CCM_DDS::ConnectorStatusListener >::weak_ref_type csl,
      IDL::traits< ::DDS::DataReader >::ref_type dr,
      const ::DDS::RequestedIncompatibleQosStatus &status)
      : csl_ (std::move (csl))
      , dr_ (dr.weak_reference ())
      , status_ (status)
    {
    }

    int
    OnRequestedIncompatibleQosHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (this->csl_.lock (), this->dr_.lock (), this->status_);
      return 0;
    }

    void
    OnRequestedIncompatibleQosHandler::handle_event (
        IDL::traits< ::CCM_DDS::ConnectorStatusListener >::ref_type csl,
        IDL::traits< ::DDS::DataReader >::ref_type dr,
        const ::DDS::RequestedIncompatibleQosStatus &status)
    {
      try
      {
        if (csl && dr)
        {
          csl->on_requested_incompatible_qos (std::move(dr), status);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnRequestedIncompatibleQosHandler::handle_event - "
            << "Unable to acquire references to the Connector Status Listener, "
            << "to the DataReader, or to both - Unable to invoke 'on_requested_incompatible_qos' for <"
            << status << ">.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnRequestedIncompatibleQosHandler::handle_event")
    }

    //============================================================
    // OnSampleRejectedHandler
    //============================================================
    OnSampleRejectedHandler::OnSampleRejectedHandler (
      IDL::traits< ::CCM_DDS::ConnectorStatusListener >::weak_ref_type csl,
      IDL::traits< ::DDS::DataReader >::ref_type dr,
      const ::DDS::SampleRejectedStatus &status)
      : csl_ (std::move (csl))
      , dr_ (dr.weak_reference ())
      , status_ (status)
    {
    }

    int
    OnSampleRejectedHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (this->csl_.lock (), this->dr_.lock (), this->status_);
      return 0;
    }

    void
    OnSampleRejectedHandler::handle_event (
        IDL::traits< ::CCM_DDS::ConnectorStatusListener >::ref_type csl,
        IDL::traits< ::DDS::DataReader >::ref_type dr,
        const ::DDS::SampleRejectedStatus &status)
    {
      try
      {
        if (csl && dr)
        {
          csl->on_sample_rejected (std::move(dr), status);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnSampleRejectedHandler::handle_event - "
            << "Unable to acquire references to the Connector Status Listener, "
            << "to the DataReader, or to both - Unable to invoke 'on_sample_rejected' for <"
            << status << ">.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnSampleRejectedHandler::handle_event")
    }

    //============================================================
    // OnInconsistentTopicHandler
    //============================================================
    OnInconsistentTopicHandler::OnInconsistentTopicHandler (
      IDL::traits< ::CCM_DDS::ConnectorStatusListener >::weak_ref_type csl,
      IDL::traits< ::DDS::Topic >::ref_type tp,
      const ::DDS::InconsistentTopicStatus &status)
      : csl_ (std::move (csl))
      , tp_ (tp.weak_reference ())
      , status_ (status)
    {
    }

    int
    OnInconsistentTopicHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (this->csl_.lock (), tp_.lock (), this->status_);
      return 0;
    }

    void
    OnInconsistentTopicHandler::handle_event (
        IDL::traits< ::CCM_DDS::ConnectorStatusListener >::ref_type csl,
        IDL::traits< ::DDS::Topic >::ref_type tp,
        const ::DDS::InconsistentTopicStatus &status)
    {
      try
      {
        if (csl && tp)
        {
          csl->on_inconsistent_topic (std::move(tp), status);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnInconsistentTopicHandler::handle_event - "
            << "Unable to acquire references to the Connector Status Listener, "
            << "to the Topic, or to both - Unable to invoke 'in_inconsistent_topic' for <"
            << status << ">.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnInconsistentTopicHandler::handle_event")
    }

    //============================================================
    // OnOfferedDeadlineMissedHandler
    //============================================================
    OnOfferedDeadlineMissedHandler::OnOfferedDeadlineMissedHandler (
      IDL::traits< ::CCM_DDS::ConnectorStatusListener >::weak_ref_type csl,
      IDL::traits< ::DDS::DataWriter >::ref_type dw,
      const ::DDS::OfferedDeadlineMissedStatus &status)
      : csl_ (std::move (csl))
      , dw_ (dw.weak_reference ())
      , status_ (status)
    {
    }

    int
    OnOfferedDeadlineMissedHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (this->csl_.lock (), this->dw_.lock (), this->status_);
      return 0;
    }

    void
    OnOfferedDeadlineMissedHandler::handle_event (
        IDL::traits< ::CCM_DDS::ConnectorStatusListener >::ref_type csl,
        IDL::traits< ::DDS::DataWriter >::ref_type dw,
        const ::DDS::OfferedDeadlineMissedStatus &status)
    {
      try
      {
        if (csl && dw)
        {
          csl->on_offered_deadline_missed (std::move(dw), status);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnOfferedDeadlineMissedHandler::handle_event - "
            << "Unable to acquire references to the Connector Status Listener, "
            << "to the DataWriter, or to both - Unable to invoke 'on_offered_deadline_missed' for <"
            << status << ">.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnOfferedDeadlineMissedHandler::handle_event")
    }

    //============================================================
    // OnOfferedIncompatibleQoSHandler
    //============================================================
    OnOfferedIncompatibleQoSHandler::OnOfferedIncompatibleQoSHandler (
      IDL::traits< ::CCM_DDS::ConnectorStatusListener >::weak_ref_type csl,
      IDL::traits< ::DDS::DataWriter >::ref_type dw,
      const ::DDS::OfferedIncompatibleQosStatus &status)
      : csl_ (std::move (csl))
      , dw_ (dw.weak_reference ())
      , status_ (status)
    {
    }

    int
    OnOfferedIncompatibleQoSHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (this->csl_.lock (), this->dw_.lock (), this->status_);
      return 0;
    }

    void
    OnOfferedIncompatibleQoSHandler::handle_event (
        IDL::traits< ::CCM_DDS::ConnectorStatusListener >::ref_type csl,
        IDL::traits< ::DDS::DataWriter >::ref_type dw,
        const ::DDS::OfferedIncompatibleQosStatus &status)
    {
      try
      {
        if (csl && dw)
        {
          csl->on_offered_incompatible_qos (std::move(dw), status);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnOfferedIncompatibleQoSHandler::handle_event - "
            << "Unable to acquire references to the Connector Status Listener, "
            << "to the DataWriter, or to both - Unable to invoke 'on_offered_incompatible_qos' for <"
            << status << ">.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnOfferedIncompatibleQoSHandler::handle_event")
    }

    //============================================================
    // OnRequestedDeadlineMissedHandler
    //============================================================
    OnRequestedDeadlineMissedHandler::OnRequestedDeadlineMissedHandler (
      IDL::traits< ::CCM_DDS::PortStatusListener >::weak_ref_type psl,
      IDL::traits< ::DDS::DataReader >::ref_type dr,
      const ::DDS::RequestedDeadlineMissedStatus & status)
      : psl_ (std::move (psl))
      , dr_ (dr.weak_reference ())
      , status_ (status)
    {
    }

    int
    OnRequestedDeadlineMissedHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (this->psl_.lock (), this->dr_.lock (), this->status_);
      return 0;
    }

    void
    OnRequestedDeadlineMissedHandler::handle_event (
        IDL::traits< ::CCM_DDS::PortStatusListener >::ref_type psl,
        IDL::traits< ::DDS::DataReader >::ref_type dr,
        const ::DDS::RequestedDeadlineMissedStatus &status)
    {
      try
      {
        if (psl && dr)
        {
          psl->on_requested_deadline_missed (std::move(dr), status);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnRequestedDeadlineMissedHandler::handle_event - "
            << "Unable to acquire references to the Port Status Listener, "
            << "to the DataReader, or to both - Unable to invoke 'on_requested_deadline_missed' for <"
            << status << ">.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnRequestedDeadlineMissedHandler::handle_event")
    }

    //============================================================
    // OnSampleLostHandler
    //============================================================
    OnSampleLostHandler::OnSampleLostHandler (
      IDL::traits< ::CCM_DDS::PortStatusListener >::weak_ref_type psl,
      IDL::traits< ::DDS::DataReader >::ref_type dr,
      const ::DDS::SampleLostStatus & status)
      : psl_ (std::move (psl))
      , dr_ (dr.weak_reference ())
      , status_ (status)
    {
    }

    int
    OnSampleLostHandler::handle_exception (ACE_HANDLE)
    {
      handle_event (this->psl_.lock (), this->dr_.lock (), this->status_);
      return 0;
    }

    void
    OnSampleLostHandler::handle_event (
        IDL::traits< ::CCM_DDS::PortStatusListener >::ref_type psl,
        IDL::traits< ::DDS::DataReader >::ref_type dr,
        const ::DDS::SampleLostStatus &status)
    {
      try
      {
        if (psl && dr)
        {
          psl->on_sample_lost (std::move(dr), status);
        }
        else
        {
          DDS4CCM_LOG_ERROR ("OnSampleLostHandler::handle_event - "
            "Unable to acquire references to the Port Status Listener, "
            "to the DataReader, or to both - Unable to invoke "
            "'on_sample_lost'");
        }
      }
      catch_dds4ccm_listener_ex(ex, "OnSampleLostHandler::handle_event")
    }
  }
}
