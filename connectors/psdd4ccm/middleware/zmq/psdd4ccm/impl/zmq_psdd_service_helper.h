// -*- C++ -*-
/**
 * @file    zmq_psdd_service_helper.h
 * @author  Martin Corino
 *
 * @brief   ZMQ Service Helper for PSDD implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_SERVICE_HELPER_H_
#define ZMQ_PSDD_SERVICE_HELPER_H_

#include "psdd4ccm/idl/psdd4ccm_baseC.h"
#include "session/ccm_sessioncontextC.h"

#include "psdd4ccm/impl/zmq_psdd_stub_export.h"

#include "psdd4ccm/impl/zmq_psdd_context_i.h"
#include "psdd4ccm/impl/zmq_psdd_config.h"
#include "psdd4ccm/impl/zmq_safe_msg.h"

#include <limits>

namespace PSDD
{
  namespace ZMQ
  {
    class ZMQ_PSDD_STUB_Export ServiceHelper
    {
    public:
      ServiceHelper () = default;
      ~ServiceHelper () = default;

      void
      initialize (
          IDL::traits<::Components::SessionContext>::ref_type ctx,
          bool publish,
          bool subscribe);

      void
      shutdown ();

      bool
      publisher_enabled () const
      { return this->config_.publisher_enabled (); }

      bool
      subscriber_enabled () const
      { return this->config_.subscriber_enabled (); }

      const Config&
      get_config () const
      { return this->config_; }

      bool
      has_custom_serializer () const
      { return this->config_.has_custom_serializer (); }

      IDL::traits<CORBA::LocalObject>::ref_type
      get_custom_serializer () const;

      SubscriberSocket
      create_subscriber_socket ();

      WriterSocket
      create_publisher_socket ();

      void
      schedule_listener (IDL::traits<::PSDD::ZMQ::Listener>::ref_type l);

      void
      remove_listener (IDL::traits<::PSDD::ZMQ::Listener>::ref_type l);

      void
      reset_listeners ();

    private:
      friend class Context_Impl;

      void
      get_service_context (
          IDL::traits<::Components::SessionContext>::ref_type ctx);

      IDL::traits<::PSDD::ZMQ::Context_Impl>::ref_type svc_context_
      {};

      Config config_ {};
    };
  }
}

#endif /* ZMQ_PSDD_SERVICE_HELPER_H_ */
