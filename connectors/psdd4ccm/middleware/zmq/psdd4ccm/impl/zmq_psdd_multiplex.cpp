// -*- C++ -*-
/**
 * @file    zmq_psdd_multiplex.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD publishing multiplexer
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "psdd4ccm/impl/zmq_psdd_multiplex.h"

#include "psdd4ccm/logger/psdd4ccm_log.h"

#include <sstream>

namespace PSDD
{
  namespace ZMQ
  {

    bool
    Multiplex::start (
        void* context,
        const Config& cfg)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Multiplex::start");

      // setup a guard
      std::lock_guard<std::mutex> __lg (this->lock_);

      if (this->started ())
      {
        // already started
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Multiplex::start" <<
          " - already started");

        return false;
      }

      // open up the actual publishing socket
      this->ps_ =
          WriterSocket (::zmq_socket (context, ZMQ_PUB));
      if (!this->ps_)
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Multiplex::start" <<
          " - failed to create publishing socket");

        return false;
      }
      // configure the socket
      cfg.configure_publisher_socket (this->ps_);
      // bind the primary publishing endpoints
      if (!this->bind_i (cfg.publisher_endpoints ()))
      {
        return false;
      }

      // setup the multiplex endpoint url
      std::ostringstream oss;
      oss << "inproc://psdd.zmq.multiplex." << reinterpret_cast<uint64_t> (this->ps_.handle ());
      this->multiplex_endpoint_ = oss.str ();

      // open up the multiplex socket
      this->rs_ =  ReaderSocket (::zmq_socket (context, ZMQ_PULL));
      if (!this->rs_)
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Multiplex::start" <<
          " - failed to create multiplex socket");

        return false;
      }
      // bind to the service endpoint
      if (!this->rs_.bind (this->multiplex_endpoint_))
      {
        return false;
      }

      // open up a control socket for the multiplexer
      this->cs_ =
          WriterSocket (::zmq_socket (context, ZMQ_PUSH));
      if (!this->cs_)
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Multiplex::start" <<
          " - failed to create multiplex control socket");

        return false;
      }
      // connect to the service endpoint
      if (!this->cs_.connect (this->multiplex_endpoint_))
      {
        return false;
      }

      // start the multiplex thread
      this->thread_ = std::thread (&Multiplex::run, this);

      this->shutdown_ = false;
      this->started_ = true;

      return true;
    }

    void
    Multiplex::stop ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Multiplex::stop");

      {
        // setup a guard
        std::lock_guard<std::mutex> __lg (this->lock_);

        // check if there is a service thread running
        if (!this->started () || this->shutdown_)
          return;

        this->shutdown_ = true; // signal shutdown
      }

      // send wakeup signal (single zero byte)
      uint8_t buf[1] = {0};
      this->cs_.send (buf, 1);

      // wait for thread to shut down
      try
      {
        this->thread_.join ();
      }
      catch (const std::system_error& e)
      {
        PSDD4CCM_LOG_CRITICAL (
            "PSDD::ZMQ::Multiplex::stop" <<
            " - exception caught from stopping multiplex thread ["
            << e.what () << ", " << e.code () << "]");
      }

      // clean up
      {
        // setup a guard
        std::lock_guard<std::mutex> __lg (this->lock_);

        this->thread_ = {}; // reset
        this->cs_ = {}; // reset
        this->rs_ = {}; // reset
        this->ps_ = {}; // reset
        this->started_ = false;
      }
    }

    bool
    Multiplex::bind (
        const std::vector<std::string>& eps)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Multiplex::bind");

      // setup a guard
      std::unique_lock<std::mutex> _lk (this->lock_);

      if (!this->started () || this->shutdown_)
        return false;

      return this->bind_i (eps, &_lk);
    }

    bool
    Multiplex::bind_i (
        const std::vector<std::string>& eps,
        std::unique_lock<std::mutex>* lck)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Multiplex::bind_i");

      std::vector<std::string> bind_eps;
      if (!this->started ())
      {
        // no endpoints can be bound yet; all new
        bind_eps = eps;
        this->bound_pub_eps_.insert (eps.begin (), eps.end ());
      }
      else
      {
        // determine non-bound endpoints to bind
        for (const std::string& ep : eps)
        {
          if (this->bound_pub_eps_.find (ep) ==
                            this->bound_pub_eps_.end ())
          {
            // add
            bind_eps.push_back (ep);
            this->bound_pub_eps_.insert (ep);
          }
        }
      }

      // any additional endpoints to bind?
      if (bind_eps.empty ())
        return true;

      if (this->started ())
      {
        this->suspend_ = true; // signal suspend

        // send wakeup signal (single byte value 0)
        uint8_t buf[1] = {0};
        this->cs_.send (buf, 1);

        // wait till the thread releases
        this->condition_.wait (*lck);
      }

      bool rc = true;

      for (const std::string& ep : bind_eps)
      {
        if (!this->ps_.bind (ep))
        {
          rc = false;
          break;
        }
      }

      if (this->started ())
      {
        // release suspended thread
        this->condition_.notify_all ();
      }

      return rc;
    }

    void
    Multiplex::run ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Multiplex::run");

      // run the multiplexer until shutdown is signaled
      for(;;)
      {
        ::zmq_msg_t key_frame;
        SafeMsg safe_key_frame;
        ::zmq_msg_t data_frame;
        SafeMsg safe_data_frame;

        if (this->rs_.receive_topic (
                &key_frame, safe_key_frame,
                &data_frame, safe_data_frame,
                false))
        {
          uint8_t* data = static_cast<uint8_t*> (
              ::zmq_msg_data (std::addressof(key_frame)));
          size_t sz = ::zmq_msg_size (std::addressof(key_frame));

          if (sz == 1 && data[0] == '\0' &&
              (this->shutdown_ || this->suspend_))
          {
            if (this->shutdown_)
            {
              // shutdown on shutdown signal
              break;
            }

            // otherwise suspend
            {
              // acquire
              std::unique_lock<std::mutex> _lk (this->lock_);
              // release waiting client
              this->condition_.notify_all ();
              // wait till released
              this->condition_.wait (_lk);

              this->suspend_ = false; // reset
            }
          }
          else
          {
            // route message frames to writer socket
            try
            {
              this->ps_.send_topic (
                  safe_key_frame,
                  safe_data_frame);
            }
            catch (const ::CCM_PSDD::InternalError& ex)
            {
              PSDD4CCM_LOG_PANIC (
                "PSDD::ZMQ::Multiplex::run" <<
                " - error routing message frames [" <<
                ex << "]");
            }
          }
        }
      }

      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Multiplex::run -> exit");
    }

  }
}
