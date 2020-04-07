// -*- C++ -*-
/**
 * @file    zmq_psdd_context_i.h
 * @author  Martin Corino
 *
 * @brief   ZMQ Context for PSDD implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_PSDD_CONTEXT_I_H_
#define ZMQ_PSDD_CONTEXT_I_H_

#include "psdd4ccm/idl/psdd4ccm_baseC.h"

#include "psdd4ccm/impl/zmq_psdd_contextC.h"
#include "psdd4ccm/impl/zmq_psdd_listenerC.h"
#include "psdd4ccm/impl/zmq_psdd_sockets.h"
#include "psdd4ccm/impl/zmq_psdd_config.h"
#include "psdd4ccm/impl/zmq_psdd_multiplex.h"
#include "psdd4ccm/impl/zmq_psdd_poller.h"

#include "psdd4ccm/impl/zmq_psdd_stub_export.h"

#include <zmq.h>

#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>
#include <thread>

namespace PSDD
{
  namespace ZMQ
  {
    class ZMQ_PSDD_STUB_Export Context_Impl
      : public ContextBase
    {
    public:
      Context_Impl ();
      virtual
      ~Context_Impl ();

      void
      initialize (const Config&);

      void
      register_client ();

      void
      unregister_client ();

      SubscriberSocket
      create_subscriber_socket (
          const Config&);

      WriterSocket
      create_publisher_socket (
          const Config&);

      WriterSocket
      create_publisher_multiplex_socket (
          const Config&);

      void
      schedule_listener (
          IDL::traits< ::PSDD::ZMQ::Listener>::ref_type l);

      void
      remove_listener (
          IDL::traits< ::PSDD::ZMQ::Listener>::ref_type l);

      void
      reset_listeners ();

    private:
      bool
      bind (
          Socket&,
          const std::vector<std::string>&);

      bool
      connect (
          Socket&,
          const std::vector<std::string>&);

      bool
      setup_multiplex (
        const Config&);

      void* context_ { nullptr };

      uint32_t client_count_ {0};

      uint32_t max_sockets_ {127};
      uint32_t num_poll_threads_ {2};

      ListenPoller poller_ {};
      Multiplex multiplexer_ {};
    };
  }
}

#endif /* ZMQ_PSDD_CONTEXT_I_H_ */
