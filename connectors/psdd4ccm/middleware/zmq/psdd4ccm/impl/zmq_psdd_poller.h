// -*- C++ -*-
/**
 * @file    zmq_psdd_poller.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD subscription poller
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_PSDD_POLLER_H_
#define ZMQ_PSDD_POLLER_H_

#include "psdd4ccm/impl/zmq_psdd_sockets.h"
#include "psdd4ccm/impl/zmq_psdd_config.h"

#include "psdd4ccm/impl/zmq_psdd_stub_export.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <set>

namespace PSDD
{
  namespace ZMQ
  {

    class ZMQ_PSDD_STUB_Export ListenPoller
    {
    public:
      virtual ~ListenPoller () = default;

      void start (
          void* context,
          uint32_t max_sockets,
          uint32_t num_threads);

      void stop ();

      bool started () const
      { return !this->threads_.empty (); }

      void add_listener (
          ListenSocket);

      void remove_listener (
          ListenSocket);

      void interrupt ();

    private:
      friend class Context_Impl;

      void interrupt_i ();

      void run ();

      ListenPoller () = default;
      ListenPoller (const ListenPoller&) = delete;
      ListenPoller (ListenPoller&& wp) = delete;

      ListenPoller& operator= (const ListenPoller&) = delete;
      ListenPoller& operator= (ListenPoller&& wp) = delete;

      std::mutex lock_ {};
      std::condition_variable condition_ {};
      std::vector<std::thread> threads_ {};
      WriterSocket pipe_wr_ {};
      ReaderSocket pipe_rd_ {};
      std::atomic<bool> stopping_ { false };
      bool polling_ { false };
      uint32_t max_sockets_ {};
      std::vector<ListenSocket> listeners_ {};
      std::unique_ptr<zmq_pollitem_t[]> poll_items_ {};
      std::vector<ListenSocket> poll_listeners_ {};
    };

  }
}

#endif
