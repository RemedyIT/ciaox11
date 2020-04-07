// -*- C++ -*-
/**
 * @file    zmq_psdd_multiplex.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD publishing multiplexer
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_PSDD_MULTIPLEX_H_
#define ZMQ_PSDD_MULTIPLEX_H_

#include "psdd4ccm/impl/zmq_psdd_sockets.h"
#include "psdd4ccm/impl/zmq_psdd_config.h"

#include "psdd4ccm/impl/zmq_psdd_stub_export.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <set>

namespace PSDD
{
  namespace ZMQ
  {

    class ZMQ_PSDD_STUB_Export Multiplex
    {
    public:
      virtual ~Multiplex () = default;

      bool start (
          void* context,
          const Config&);

      void stop ();

      bool started () const
      { return this->started_; }

      bool bind (
          const std::vector<std::string>& eps);

      const std::string& endpoint () const
      { return this->multiplex_endpoint_; }

    private:
      friend class Context_Impl;

      void run ();

      bool bind_i (
          const std::vector<std::string>& eps,
          std::unique_lock<std::mutex>* lck = nullptr);

      Multiplex () = default;
      Multiplex (const Multiplex&) = delete;
      Multiplex (Multiplex&& wp) = delete;

      Multiplex& operator= (const Multiplex&) = delete;
      Multiplex& operator= (Multiplex&& wp) = delete;

      std::string multiplex_endpoint_ {};
      std::thread thread_ {};
      WriterSocket cs_ {};
      WriterSocket ps_ {};
      ReaderSocket rs_ {};
      bool started_ {};
      bool shutdown_ {true};
      bool suspend_ {false};
      std::mutex lock_ {};
      std::condition_variable condition_ {};
      std::set<std::string> bound_pub_eps_ {};
    };

  }
}

#endif /* ZMQ_PSDD_MULTIPLEX_H_ */
