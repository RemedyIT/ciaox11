// -*- C++ -*-
/**
 * @file    zmq_psdd_service_helper.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ Service configuration for PSDD implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "zmq_psdd_service_helper.h"

#include "psdd4ccm/logger/psdd4ccm_log.h"
#include "psdd4ccm/impl/psdd4ccm_dynamic_loader.h"

namespace PSDD
{
  namespace ZMQ
  {
    void
    ServiceHelper::get_service_context (
        IDL::traits<::Components::SessionContext>::ref_type ctx)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::ServiceHelper::get_service_context");

      // check if an ZMQ context already exists
      IDL::traits<CORBA::Object>::ref_type ctx_obj;
      try
      {
        ctx_obj =
          ctx->the_service_registry()->resolve_service (
              PSDD4CCM_ZMQ_CONTEXT_ID);
      }
      catch (const Components::CCMException&)
      {
        // ignore
      }
      if (!ctx_obj)
      {
        PSDD4CCM_LOG_INFO (
          "PSDD::ZMQ::ServiceHelper::get_service_context" <<
          " - creating ZMQ service context");

        // create the ZMQ context
        IDL::traits<::PSDD::ZMQ::Context_Impl>::ref_type context_ =
            CORBA::make_reference< ::PSDD::ZMQ::Context_Impl>();
        // initialize the context
        context_->initialize (this->config_);
        // register the context
        ctx->the_service_registry()->install_service (
            PSDD4CCM_ZMQ_CONTEXT_ID,
            context_);

        this->svc_context_ = context_;
      }
      else
      {
        PSDD4CCM_LOG_INFO (
            "PSDD::ZMQ::ServiceHelper::get_service_context" <<
          " - retrieved existing ZMQ service context");

        this->svc_context_ =
            IDL::traits<::PSDD::ZMQ::Context_Impl>::narrow (ctx_obj);
      }
    }

    void
    ServiceHelper::initialize (
        IDL::traits<::Components::SessionContext>::ref_type ctx,
        bool publish,
        bool subscribe)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ServiceHelper::initialize");

      // initialize service configuration
      this->config_.initialize (ctx->instance_id (), publish, subscribe);

      // get (or create) the service context
      this->get_service_context (ctx);
      // check the context
      if (this->svc_context_)
      {
        // register as client
        this->svc_context_->register_client ();
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::ServiceHelper::initialize" <<
          " - failed to retrieve ZMQ service context");

        throw ::CCM_PSDD::InternalError (
                  "PSDD::ZMQ::ServiceHelper::::initialize",
                  "NO_CONTEXT");
      }
    }

    void
    ServiceHelper::shutdown ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ServiceHelper::shutdown");

      if (this->svc_context_)
      {
        // unregister as client
        this->svc_context_->unregister_client ();

        this->svc_context_.reset ();
      }
    }

    IDL::traits<CORBA::LocalObject>::ref_type
    ServiceHelper::get_custom_serializer () const
    {
      std::string err_string;
      PSDD::DL_Module serializer_mod (
          this->config_.serializer_module (),
          this->config_.serializer_openmode ());
      auto serializer_factory =
          serializer_mod.resolve <void, IDL::traits<CORBA::LocalObject>::ref_type&>(
              err_string, this->config_.serializer_entry_point ());
      if (!serializer_factory)
      {
        PSDD4CCM_LOG_PANIC(
            "PSDD::ZMQ::ServiceHelper::get_custom_serializer" <<
            " - failed loading custom serializer : " <<
            err_string);

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ServiceHelper::get_custom_serializer",
            "FAIL_LOAD");
      }
      try
      {
        IDL::traits<CORBA::LocalObject>::ref_type serializer_ref;
        serializer_factory (serializer_ref);
        return serializer_ref;
      }
      catch (...)
      {
        PSDD4CCM_LOG_PANIC(
            "PSDD::ZMQ::ServiceHelper::get_custom_serializer" <<
            " - unexpected exception loading custom serializer");

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ServiceHelper::get_custom_serializer",
            "ERR_LOAD");
      }
    }

    SubscriberSocket
    ServiceHelper::create_subscriber_socket ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ServiceHelper::create_subscriber_socket" );

      SubscriberSocket ss;
      if (!(ss = this->svc_context_->create_subscriber_socket (
              this->config_)))
      {
        PSDD4CCM_LOG_PANIC (
            "PSDD::ZMQ::ServiceHelper::create_subscriber_socket" <<
          " - failed to create ZMQ socket [" <<
          ::zmq_strerror (::zmq_errno ()) << "]");

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::Context_Impl::create_subscriber_socket",
            "NO_MEMORY");
      }
      return ss;
    }

    WriterSocket
    ServiceHelper::create_publisher_socket ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ServiceHelper::create_publisher_socket");

      // create the socket
      WriterSocket ws;
      if (this->config_.publisher_connection_scheme() == ConnectionScheme::BIND_MULTIPLEX)
      {
        ws = this->svc_context_->create_publisher_multiplex_socket (this->config_);
      }
      else
      {
        ws = this->svc_context_->create_publisher_socket (this->config_);
      }
      if (!ws)
      {
        PSDD4CCM_LOG_PANIC (
            "PSDD::ZMQ::ServiceHelper::create_publisher_socket" <<
          " - failed to create ZMQ socket [" <<
          ::zmq_strerror (::zmq_errno ()) << "]");

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::Context_Impl::create_publisher_socket",
            "NO_MEMORY");
      }
      return ws;
    }

    void
    ServiceHelper::schedule_listener (
        IDL::traits<::PSDD::ZMQ::Listener>::ref_type l)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ServiceHelper::schedule_listener");

      this->svc_context_->schedule_listener (l);
    }

    void
    ServiceHelper::remove_listener (
        IDL::traits<::PSDD::ZMQ::Listener>::ref_type l)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ServiceHelper::remove_listener");

      this->svc_context_->remove_listener (l);
    }

    void
    ServiceHelper::reset_listeners ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ServiceHelper::reset_listeners");

      this->svc_context_->reset_listeners ();
    }
  }
}
