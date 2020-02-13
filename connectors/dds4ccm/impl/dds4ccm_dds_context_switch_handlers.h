// -*- C++ -*-
/**
 * @file    dds4ccm_dds_context_switch_handlers.h
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 *          The class members (listener and datareader/datawriter) are stored
 *          as weak references. We don't want to influence the life cycle of
 *          entities here.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_CONTEXT_SWITCH_HANDLERS_H_
#define DDS4CCM_CONTEXT_SWITCH_HANDLERS_H_

#include "dds4ccm/idl/dds_rtf2_dcpsC.h"
#include "dds4ccm/idl/dds4ccm_connector_status_listenerC.h"
#include "dds4ccm/idl/dds4ccm_port_status_listenerC.h"
#include "ace/Event_Handler.h"
#include "dds4ccm/impl/dds4ccm_impl_export.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    class DDSContextSwitchHandlerBase
      : public ACE_Event_Handler
    {
      public:
        DDSContextSwitchHandlerBase ();
        ~DDSContextSwitchHandlerBase () = default;
    };

    class DDS4CCM_IMPL_Export OnUnexpectedStatusHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnUnexpectedStatusHandler (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl,
            IDL::traits< ::DDS::Entity>::ref_type entity,
            ::DDS::StatusKind status_kind);
        virtual ~OnUnexpectedStatusHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::ref_type csl,
            IDL::traits< ::DDS::Entity>::ref_type entity,
            ::DDS::StatusKind status_kind);
      private:
        IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl_;
        IDL::traits< ::DDS::Entity>::weak_ref_type entity_;
        ::DDS::StatusKind status_kind_;

        OnUnexpectedStatusHandler() = delete;
        OnUnexpectedStatusHandler(const OnUnexpectedStatusHandler&) = delete;
        OnUnexpectedStatusHandler(OnUnexpectedStatusHandler&&) = delete;
        OnUnexpectedStatusHandler& operator=(const OnUnexpectedStatusHandler&) = delete;
        OnUnexpectedStatusHandler& operator=(OnUnexpectedStatusHandler&&) = delete;
    };

    class DDS4CCM_IMPL_Export OnRequestedIncompatibleQosHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnRequestedIncompatibleQosHandler (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::RequestedIncompatibleQosStatus &status);
        virtual ~OnRequestedIncompatibleQosHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::ref_type csl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::RequestedIncompatibleQosStatus &status);
      private:
        IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl_;
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::RequestedIncompatibleQosStatus const status_;

        OnRequestedIncompatibleQosHandler() = delete;
        OnRequestedIncompatibleQosHandler(const OnRequestedIncompatibleQosHandler&) = delete;
        OnRequestedIncompatibleQosHandler(OnRequestedIncompatibleQosHandler&&) = delete;
        OnRequestedIncompatibleQosHandler& operator=(const OnRequestedIncompatibleQosHandler&) = delete;
        OnRequestedIncompatibleQosHandler& operator=(OnRequestedIncompatibleQosHandler&&) = delete;
    };

    class DDS4CCM_IMPL_Export OnSampleRejectedHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnSampleRejectedHandler (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::SampleRejectedStatus &status);
        virtual ~OnSampleRejectedHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::ref_type csl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::SampleRejectedStatus &status);
      private:
        IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl_;
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::SampleRejectedStatus const status_;

        OnSampleRejectedHandler() = delete;
        OnSampleRejectedHandler(const OnSampleRejectedHandler&) = delete;
        OnSampleRejectedHandler(OnSampleRejectedHandler&&) = delete;
        OnSampleRejectedHandler& operator=(const OnSampleRejectedHandler&) = delete;
        OnSampleRejectedHandler& operator=(OnSampleRejectedHandler&&) = delete;
    };

    class DDS4CCM_IMPL_Export OnInconsistentTopicHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnInconsistentTopicHandler (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl,
            IDL::traits< ::DDS::Topic>::ref_type tp,
            const ::DDS::InconsistentTopicStatus &status);
        virtual ~OnInconsistentTopicHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::ref_type csl,
            IDL::traits< ::DDS::Topic>::ref_type tp,
            const ::DDS::InconsistentTopicStatus &status);
      private:
        IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl_;
        IDL::traits< ::DDS::Topic>::weak_ref_type tp_;
        ::DDS::InconsistentTopicStatus const status_;

        OnInconsistentTopicHandler() = delete;
        OnInconsistentTopicHandler(const OnInconsistentTopicHandler&) = delete;
        OnInconsistentTopicHandler(OnInconsistentTopicHandler&&) = delete;
        OnInconsistentTopicHandler& operator=(const OnInconsistentTopicHandler&) = delete;
        OnInconsistentTopicHandler& operator=(OnInconsistentTopicHandler&&) = delete;
    };

    class DDS4CCM_IMPL_Export OnOfferedDeadlineMissedHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnOfferedDeadlineMissedHandler (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl,
            IDL::traits< ::DDS::DataWriter>::ref_type dw,
            const ::DDS::OfferedDeadlineMissedStatus &status);
        virtual ~OnOfferedDeadlineMissedHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::ref_type csl,
            IDL::traits< ::DDS::DataWriter>::ref_type dw,
            const ::DDS::OfferedDeadlineMissedStatus &status);
      private:
        IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl_;
        IDL::traits< ::DDS::DataWriter>::weak_ref_type dw_;
        ::DDS::OfferedDeadlineMissedStatus const status_;

        OnOfferedDeadlineMissedHandler() = delete;
        OnOfferedDeadlineMissedHandler(const OnOfferedDeadlineMissedHandler&) = delete;
        OnOfferedDeadlineMissedHandler(OnOfferedDeadlineMissedHandler&&) = delete;
        OnOfferedDeadlineMissedHandler& operator=(const OnOfferedDeadlineMissedHandler&) = delete;
        OnOfferedDeadlineMissedHandler& operator=(OnOfferedDeadlineMissedHandler&&) = delete;
    };

    class DDS4CCM_IMPL_Export OnOfferedIncompatibleQoSHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnOfferedIncompatibleQoSHandler (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl,
            IDL::traits< ::DDS::DataWriter>::ref_type dw,
            const ::DDS::OfferedIncompatibleQosStatus &status);
        virtual ~OnOfferedIncompatibleQoSHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::ConnectorStatusListener>::ref_type csl,
            IDL::traits< ::DDS::DataWriter>::ref_type dw,
            const ::DDS::OfferedIncompatibleQosStatus &status);
      private:
        IDL::traits< ::CCM_DDS::ConnectorStatusListener>::weak_ref_type csl_;
        IDL::traits< ::DDS::DataWriter>::weak_ref_type dw_;
        ::DDS::OfferedIncompatibleQosStatus const status_;

        OnOfferedIncompatibleQoSHandler() = delete;
        OnOfferedIncompatibleQoSHandler(const OnOfferedIncompatibleQoSHandler&) = delete;
        OnOfferedIncompatibleQoSHandler(OnOfferedIncompatibleQoSHandler&&) = delete;
        OnOfferedIncompatibleQoSHandler& operator=(const OnOfferedIncompatibleQoSHandler&) = delete;
        OnOfferedIncompatibleQoSHandler& operator=(OnOfferedIncompatibleQoSHandler&&) = delete;
    };

    class DDS4CCM_IMPL_Export OnRequestedDeadlineMissedHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnRequestedDeadlineMissedHandler (
            IDL::traits< ::CCM_DDS::PortStatusListener>::weak_ref_type psl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::RequestedDeadlineMissedStatus &status);
        virtual ~OnRequestedDeadlineMissedHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::PortStatusListener>::ref_type psl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::RequestedDeadlineMissedStatus &status);
      private:
        IDL::traits< ::CCM_DDS::PortStatusListener>::weak_ref_type psl_;
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::RequestedDeadlineMissedStatus const status_;

        OnRequestedDeadlineMissedHandler() = delete;
        OnRequestedDeadlineMissedHandler(const OnRequestedDeadlineMissedHandler&) = delete;
        OnRequestedDeadlineMissedHandler(OnRequestedDeadlineMissedHandler&&) = delete;
        OnRequestedDeadlineMissedHandler& operator=(const OnRequestedDeadlineMissedHandler&) = delete;
        OnRequestedDeadlineMissedHandler& operator=(OnRequestedDeadlineMissedHandler&&) = delete;
    };

    class DDS4CCM_IMPL_Export OnSampleLostHandler
      : public DDSContextSwitchHandlerBase
    {
      public:
        explicit OnSampleLostHandler (
            IDL::traits< ::CCM_DDS::PortStatusListener>::weak_ref_type psl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::SampleLostStatus &status);
        virtual ~OnSampleLostHandler () = default;
        virtual int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE);
        static void handle_event (
            IDL::traits< ::CCM_DDS::PortStatusListener>::ref_type psl,
            IDL::traits< ::DDS::DataReader>::ref_type dr,
            const ::DDS::SampleLostStatus &status);
      private:
        IDL::traits< ::CCM_DDS::PortStatusListener>::weak_ref_type psl_;
        IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;
        ::DDS::SampleLostStatus const status_;

        OnSampleLostHandler() = delete;
        OnSampleLostHandler(const OnSampleLostHandler&) = delete;
        OnSampleLostHandler(OnSampleLostHandler&&) = delete;
        OnSampleLostHandler& operator=(const OnSampleLostHandler&) = delete;
        OnSampleLostHandler& operator=(OnSampleLostHandler&&) = delete;
    };
  }
}

#endif /* DDS4CCM_CONTEXT_SWITCH_HANDLERS_H_ */
