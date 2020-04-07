// -*- C++ -*-
/**
 * @file    zmq_psdd_poller.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD subscription poller
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "psdd4ccm/impl/zmq_psdd_poller.h"

namespace PSDD
{
  namespace ZMQ
  {
    void
    ListenPoller::start (
        void* context,
        uint32_t max_sockets,
        uint32_t num_threads)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ListenPoller::start" );

      // enter lock
      std::lock_guard<std::mutex> _lg (this->lock_);

      if (this->started ())
      {
        // already started
        PSDD4CCM_LOG_DEBUG (
          "PSDD::ZMQ::ListenPoller::start" <<
          " - already started");
      }
      else
      {
        // remember max sockets configured
        this->max_sockets_ = max_sockets;

        // initialize storage for listener sockets
        this->poll_listeners_.resize (this->max_sockets_);
        try
        {
          this->poll_items_ = std::make_unique<zmq_pollitem_t[]> (this->max_sockets_);
        }
        catch (const std::bad_alloc&)
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::ListenPoller::start",
              "NO_MEMORY");
        }

        PSDD4CCM_LOG_DEBUG ("PSDD::ZMQ::ListenPoller::start" <<
                            " - creating control pipe");

        // create an inproc socket pair as control pipe for the poller threads
        this->pipe_wr_ = WriterSocket (::zmq_socket (context, ZMQ_PAIR));
        if (!this->pipe_wr_
            || !this->pipe_wr_.bind ("inproc://psdd.zmq.poll.pipe"))
        {
          PSDD4CCM_LOG_PANIC ("PSDD::ZMQ::ListenPoller::start" <<
                              " - failed to initialize pipe write end");
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::ListenPoller::start",
              "NOPIPE");
        }

        this->pipe_rd_ = ReaderSocket (::zmq_socket (context, ZMQ_PAIR));
        if (!this->pipe_rd_
            || !this->pipe_rd_.connect ("inproc://psdd.zmq.poll.pipe"))
        {
          PSDD4CCM_LOG_PANIC ("PSDD::ZMQ::ListenPoller::start" <<
                              " - failed to initialize pipe read end");
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::ListenPoller::start",
              "NOPIPE");
        }

        PSDD4CCM_LOG_DEBUG ("PSDD::ZMQ::ListenPoller::start" <<
                            " - starting " << num_threads <<
                            " polling thread(s)");

        try
        {
          for (uint32_t n=0; n<num_threads ;++n)
          {
            this->threads_.push_back (
                std::thread (&ListenPoller::run, this));
          }
          PSDD4CCM_LOG_INFO ("PSDD::ZMQ::ListenPoller::start" <<
                             " - started polling thread(s)");
        }
        catch (...)
        {
          PSDD4CCM_LOG_PANIC ("PSDD::ZMQ::ListenPoller::start" <<
                              " - exception starting polling threads");
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::ListenPoller::start",
              "THREAD_FAIL");
        }

      }
    }

    void
    ListenPoller::stop ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ListenPoller::stop");

      {
        // enter lock
        std::lock_guard<std::mutex> _lg (this->lock_);

        if (!this->started () || this->stopping_)
        {
          // already stopping or not started
          PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::ListenPoller::stop" <<
            " - not started");

          return;
        }

        this->stopping_ = true;
      }

      // signal polling leader to wake up
      // when woken up the leader in turn will
      // wake up all followers
      this->interrupt_i ();

      try
      {
        for (std::thread& t : this->threads_)
        {
          t.join ();
        }
        PSDD4CCM_LOG_DEBUG ("PSDD::ZMQ::ListenPoller::stop" <<
                           " - polling thread stopped");
      }
      catch (const std::system_error& e)
      {
        PSDD4CCM_LOG_CRITICAL (
            "PSDD::ZMQ::ListenPoller::stop" <<
            " - exception caught from stopping polling thread ["
            << e.what () << ", " << e.code () << "]");
      }

      this->pipe_wr_ = {};
      this->pipe_rd_ = {};

      this->threads_.clear ();

      this->stopping_ = false;
    }

    void
    ListenPoller::add_listener (
        ListenSocket ls)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ListenPoller::add_listener");

      // enter lock
      std::lock_guard<std::mutex> _lg (this->lock_);

      if (this->started () && !this->stopping_)
      {
        this->listeners_.push_back (ls);

        this->interrupt_i ();
      }
      else
      {
        // not started
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::ListenPoller::add_listener" <<
          " - not started");

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ListenPoller::add_listener",
            "NO_THREAD");
      }
    }

    void
    ListenPoller::remove_listener (
        ListenSocket ls)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ListenPoller::remove_listener");

      // enter lock
      std::unique_lock<std::mutex> _lk (this->lock_);

      if (this->started () && !this->stopping_)
      {
        PSDD4CCM_LOG_INFO ("PSDD::ZMQ::ListenPoller::remove_listener" <<
                     " - looking up listener");

        for (std::vector<ListenSocket>::iterator it = this->listeners_.begin ();
              it != this->listeners_.end () ; ++it)
        {
          if ((*it) == ls)
          {
            PSDD4CCM_LOG_INFO ("PSDD::ZMQ::ListenPoller::remove_listener" <<
                               " - removing listener");
            this->listeners_.erase (it);
            break;
          }
        }

        // wake up polling leader
        this->interrupt_i ();

        // wait for polling token release
        this->condition_.wait (_lk);
      }
      else
      {
        // no polling thread running
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::ListenPoller::remove_listener" <<
          " - no polling thread");

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ListenPoller::remove_listener",
            "NO_THREAD");
      }
    }

    void
    ListenPoller::interrupt ()
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ListenPoller::interrupt");

      // enter lock
      std::lock_guard<std::mutex> _lg (this->lock_);

      if (this->started () && !this->stopping_)
      {
        this->interrupt_i ();
      }
      else
      {
        PSDD4CCM_LOG_ERROR ("PSDD::ZMQ::ListenPoller::interrupt" <<
                            " - no control pipe");

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ListenPoller::interrupt",
            "NO_THREAD");
      }
    }

    void
    ListenPoller::interrupt_i ()
    {
      PSDD4CCM_LOG_INFO ("PSDD::ZMQ::ListenPoller::interrupt_i" <<
                          " - alerting polling thread");

      uint8_t buf[1] = {0};
      if (!this->pipe_wr_.send_buf(buf, 1))
      {
        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ListenPoller::interrupt_i",
            "SENDINT");
      }
    }

    void
    ListenPoller::run ()
    {
      // create registry to record the max nr of readable listeners
      // (don't need room for the control socket)
      std::vector<ListenSocket> readables;
      readables.resize (this->max_sockets_ - 1);

      // polling token cache
      bool polling {false};

      PSDD4CCM_LOG_TRACE ("PSDD::ZMQ::ListenPoller::run");

      try
      {
        while (!this->stopping_)
        {
          // setup polling
          zmq_pollitem_t* pi {};
          int pn {}; // number of sockets being polled (incl. control)
          int rn {}; // number of readable sockets
          {
            // enter lock
            std::unique_lock<std::mutex> _lk (this->lock_);

            if (!this->stopping_)
            {
              // check if we are the lucky one
              if (this->polling_)
              {
                // no, another thread is doing the real polling
                // we're just going to wait till the master is handling
                // events
                this->condition_.wait (_lk);
                continue;  // cycle loop
              }
              else
              {
                // yes, we're gonna poll all available listeners
                polling = this->polling_ = true;
                pi = this->poll_items_.get ();
                // always listen to control pipe read end also
                pi[pn].socket = this->pipe_rd_.handle ();
                pi[pn].events = ZMQ_POLLIN;
                pi[pn].revents = 0;
                pi[pn].fd = 0;
                ++pn;
                // now add all available listeners
                for (ListenSocket& ls : this->listeners_)
                {
                  PSDD4CCM_LOG_DEBUG (
                      "PSDD::ZMQ::ListenPoller::run" <<
                      " - checking listener availability");

                  // available?
                  if (ls.setup (std::addressof(pi[pn])))
                  {
                    PSDD4CCM_LOG_DEBUG (
                        "PSDD::ZMQ::ListenPoller::run" <<
                        " - adding listener #" << pn);

                    // slot 0 is never used here
                    this->poll_listeners_[pn] = ls;
                    ++pn;
                  }
                }
              }
            }
          }

          if (!this->stopping_ && polling)
          {
            // poll for events indefinitely
            int evt_rc = ::zmq_poll (pi, pn, -1);

            polling = false;

            if (evt_rc > 0)
            {
              // check control pipe read end in all cases
              if (!this->stopping_ && (pi[0].revents & ZMQ_POLLIN) == ZMQ_POLLIN)
              {
                PSDD4CCM_LOG_DEBUG (
                    "PSDD::ZMQ::ListenPoller::run" <<
                    " - control event received");

                // clear signal
                uint8_t buf[1];
                size_t rlen = 1;
                this->pipe_rd_.receive_buf (buf, rlen, ZMQ_DONTWAIT);
                // decrement event count
                --evt_rc;
              }
              // are there any data events we still need to handle?
              if (!this->stopping_ && evt_rc > 0)
              {
                PSDD4CCM_LOG_DEBUG (
                    "PSDD::ZMQ::ListenPoller::run" <<
                    " - " << evt_rc << " data events received");

                // collect all readable listeners and mark them
                for (int i=1; i<pn && evt_rc>0 ; ++i)
                {
                  PSDD4CCM_LOG_DEBUG (
                      "PSDD::ZMQ::ListenPoller::run" <<
                      " - checking listener #" << i);

                  if ((pi[i].revents & ZMQ_POLLIN) == ZMQ_POLLIN)
                  {
                    ListenSocket ls = std::move (this->poll_listeners_[i]);

                    PSDD4CCM_LOG_DEBUG (
                        "PSDD::ZMQ::ListenPoller::run" <<
                        " - registering listener #" << i <<
                        " for dispatch");

                    // mark the listener for input handling
                    // (prevents selection for next polling thread)
                    ls.mark_input ();
                    // register listener for reading
                    readables[rn++] = std::move (ls);
                    // decrement event count
                    --evt_rc;
                  }
                  else
                  {
                    // reset polled listener ref
                    this->poll_listeners_[i] = {};
                  }
                }
              }
            }
            else if (evt_rc == -1)
            {
              PSDD4CCM_LOG_ERROR ("PSDD::ZMQ::ListenPoller::run" <<
                                  " - error polling [" <<
                                  ::zmq_strerror (::zmq_errno ()) << "]");
            }

            // in all cases:
            //   release polling token and signal waiters
            {
              // enter lock
              std::lock_guard<std::mutex> _lg (this->lock_);

              this->polling_ = false;
            }

            // signal waiters to continue IO polling
            // while we work
            this->condition_.notify_all ();

            // as long as we're not stopping
            if (!this->stopping_)
            {
              // signal all readable listeners to handle
              // their incoming data
              for (int rix=0; rix < rn ;++rix)
              {
                PSDD4CCM_LOG_DEBUG (
                    "PSDD::ZMQ::ListenPoller::run" <<
                    " - dispatching listener #" << rix);

                readables[rix].handle_input ();
                readables[rix] = {}; // reset
              }
            }
          }
        }
      }
      catch (const ::CCM_PSDD::InternalError& x)
      {
        PSDD4CCM_LOG_PANIC ("PSDD::ZMQ::ListenPoller::run" <<
                            " - exception [" << x << "]");
      }

      PSDD4CCM_LOG_INFO ("PSDD::ZMQ::ListenPoller::run" <<
                          " - leaving");
    }

  }
}
