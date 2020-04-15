// -*- C++ -*-
/**
 * @file    zmq_psdd_sockets.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD socket wrappers
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "psdd4ccm/impl/zmq_psdd_sockets.h"

namespace PSDD
{
  namespace ZMQ
  {
    Socket::~Socket ()
    {
      this->close ();
    }

    void
    Socket::close ()
    {
      ::PSDD::ZMQ::socket_type s {nullptr};
      std::swap (s, this->h_);
      if (s != nullptr && ::zmq_close (s))
      {
        this->last_error_ = ::zmq_errno ();
        PSDD4CCM_LOG_WARNING (
          "PSDD::ZMQ::Socket::close" <<
          " - error closing ZMQ socket [" <<
          ::zmq_strerror (this->last_error_) << "]");
      }
    }

    bool
    Socket::bind (const std::string& ep)
    {
      PSDD4CCM_LOG_DEBUG (
          "PSDD::ZMQ::Socket::bind" <<
          " - binding " << ep);

      if (::zmq_bind (this->h_, ep.c_str ()) != 0)
      {
        this->last_error_ = ::zmq_errno ();
        PSDD4CCM_LOG_PANIC (
          "PSDD::ZMQ::Socket::bind" <<
          " - failed to bind to \'" << ep << "\'[" <<
          ::zmq_strerror (this->last_error_) << "]");

        return false;
      }
      return true;
    }

    bool
    Socket::connect (const std::string& ep)
    {
      PSDD4CCM_LOG_DEBUG (
          "PSDD::ZMQ::Socket::connect" <<
          " - connecting " << ep);

      if (::zmq_connect (this->h_, ep.c_str ()) != 0)
      {
        this->last_error_ = ::zmq_errno ();
        PSDD4CCM_LOG_PANIC (
          "PSDD::ZMQ::Socket::connect" <<
          " - failed to connect to \'" << ep << "\'[" <<
          ::zmq_strerror (this->last_error_) << "]");

        return false;
      }
      return true;
    }

    bool
    Socket::send_buf (void* buf, size_t len, int f)
    {
      if (::zmq_send (this->h_, buf, len, f) == -1)
      {
        this->last_error_ = ::zmq_errno ();
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Socket::send" <<
          " - failed to send [" <<
          ::zmq_strerror (this->last_error_) << "]");

        return false;
      }
      return true;
    }

    bool
    Socket::send_msg (SafeMsg& msg, int f)
    {
      if (::zmq_msg_send (&msg, this->h_, f) == -1)
      {
        this->last_error_ = ::zmq_errno ();
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Socket::send_msg" <<
          " - failed to send [" <<
          ::zmq_strerror (this->last_error_) << "]");

        return false;
      }
      msg.release (); // ZMQ has taken ownership
      return true;
    }

    bool
    Socket::receive_buf (void* buf, size_t& len, int f)
    {
      size_t rlen = len;
      int rc;
      if ((rc = ::zmq_recv (this->h_, buf, rlen, f)) == -1)
      {
        this->last_error_ = ::zmq_errno ();
        if (this->last_error_ != EAGAIN)
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Socket::receive" <<
            " - failed to receive [" <<
            ::zmq_strerror (this->last_error_) << "]");
        }

        return false;
      }
      len = static_cast<size_t> (rc);
      return true;
    }

    bool
    Socket::receive_msg (SafeMsg& msg, int f)
    {
      if (::zmq_msg_recv (&msg, this->h_, f) == -1)
      {
        this->last_error_ = ::zmq_errno ();
        if (this->last_error_ != EAGAIN)
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Socket::receive_msg" <<
            " - failed to receive [" <<
            ::zmq_strerror (this->last_error_) << "]");
        }
        return false;
      }
      return true;
    }

    bool
    Socket::set_option (int opt, const void* val, size_t len)
    {
      if (::zmq_setsockopt (this->h_, opt, val, len) == -1)
      {
        this->last_error_ = ::zmq_errno ();
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Socket::set_option" <<
          " - failed to set socket option [" <<
          ::zmq_strerror (this->last_error_) << "]");

        return false;
      }
      return true;
    }

    void
    WriterSocket::send (
        void* d,
        size_t l)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::WriterSocket::send");

      if (!this->send_buf (d, l))
      {
        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::WriterSocket::send",
            this->last_strerror ());
      }
    }

    void
    WriterSocket::send_topic (
        SafeMsg& key,
        SafeMsg& data)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::WriterSocket::send_topic");

      // send the frame(s)
      // in case no key-lengths nor non-key data have been serialized
      // (in which case the safe_data_frame is left unset)
      // we do not send a separate data frame (irrespective of
      // serializer type)
      bool has_data = (data != nullptr);
      bool rc_key = this->send_msg (
                        key,
                        (has_data ? ZMQ_SNDMORE : 0));
      if ( !rc_key ||
              (has_data && !this->send_msg (data)))
      {
        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::WriterSocket::send_topic",
            this->last_strerror ());
      }
    }

    bool
    ReaderSocket::receive_topic (
        ::zmq_msg_t* key_frame, SafeMsg& key,
        ::zmq_msg_t* data_frame, SafeMsg& data,
        bool no_wait)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::ReaderSocket::receive_topic");

      bool rc = 0;

      if (!key.initialize (key_frame))
        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ReaderSocket::receive_topic",
            "MSG_INIT");

      rc = this->receive_msg (
                key,
                no_wait ? ZMQ_DONTWAIT : 0);

      if (!rc)
      {
        if (this->last_error () == EAGAIN)
          return false; // no data available

        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::ReaderSocket::receive_topic",
            "RECV_KEY");
      }

      PSDD4CCM_LOG_DEBUG (
        "PSDD::ZMQ::ReaderSocket::receive_topic" <<
        " - received key frame");

      // check for availability data frame
      bool const has_data_frame = (::zmq_msg_more (&key) != 0);

      if (has_data_frame)
      {
        if (!data.initialize (data_frame))
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::ReaderSocket::receive_topic",
              "MSG_INIT");

        if (!this->receive_msg (
                      data,
                      ZMQ_DONTWAIT))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::ReaderSocket::receive_topic",
              "RECV_DATA");
        }
      }

      PSDD4CCM_LOG_DEBUG (
        "PSDD::ZMQ::ReaderSocket::receive_topic" <<
        " - key_frame size=" << zmq_msg_size (&key) <<
        " data_frame size=" << (data ? zmq_msg_size (&data) : 0));

      return true;
    }

    void
    SubscriberSocket::subscribe_topic (
        const void* d,
        size_t l)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::SubscriberSocket::subscribe_topic");

      if (!this->set_option (ZMQ_SUBSCRIBE, d, l))
      {
        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::SubscriberSocket::subscribe_topic",
            "SETSOCKOPT");
      }
    }

    void
    SubscriberSocket::unsubscribe_topic (
        const void* d,
        size_t l)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::SubscriberSocket::unsubscribe_topic");

      if (!this->set_option (ZMQ_UNSUBSCRIBE, d, l))
      {
        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::SubscriberSocket::unsubscribe_topic",
            "SETSOCKOPT");
      }
    }

    bool
    ListenSocket::setup (zmq_pollitem_t* pi)
    {
      if ( (pi->socket = this->listener_->listen_socket ()) )
      {
        pi->events = ZMQ_POLLIN;
        pi->fd = 0;
        pi->revents = 0;
        return true;
      }
      return false;
    }

    void
    ListenSocket::mark_input ()
    {
      this->listener_->mark_readable ();
    }

    void
    ListenSocket::handle_input ()
    {
      this->listener_->on_data_available ();
    }
  }
}
