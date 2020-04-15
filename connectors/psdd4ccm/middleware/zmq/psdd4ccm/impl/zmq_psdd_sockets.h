// -*- C++ -*-
/**
 * @file    zmq_psdd_sockets.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD socket wrappers
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_SOCKETS_H_
#define ZMQ_PSDD_SOCKETS_H_

#include "psdd4ccm/idl/psdd4ccm_baseC.h"
#include "psdd4ccm/impl/zmq_psdd_baseC.h"
#include "psdd4ccm/impl/zmq_psdd_listenerC.h"
#include "psdd4ccm/impl/zmq_safe_msg.h"

#include "psdd4ccm/impl/zmq_psdd_stub_export.h"

#include <memory>

namespace PSDD
{
  namespace ZMQ
  {
    class ZMQ_PSDD_STUB_Export Socket
    {
    public:
      Socket () = default;
      Socket (Socket&& s)
        : h_ (s.h_)
      { s.h_ = nullptr; }
      virtual ~Socket ();

      socket_type handle () const
      { return this->h_; }

      int last_error () const
      { return this->last_error_; }

      const char* last_strerror () const
      { return ::zmq_strerror (this->last_error_); }

      void close ();

      Socket& operator= (Socket&& s)
      { this->close (); std::swap (this->h_, s.h_); return *this; }

      explicit operator bool() const noexcept
      { return this->h_ == nullptr ? false : true; }
      bool operator ==(std::nullptr_t) const noexcept
      { return this->h_ == nullptr; }
      bool operator !=(std::nullptr_t) const noexcept
      { return this->h_ == nullptr; }

      bool
      bind (const std::string& ep);

      bool
      connect (const std::string& ep);

      bool
      send_buf (void* buf, size_t len, int f = 0);

      bool
      send_msg (SafeMsg& msg, int f = 0);

      bool
      receive_buf (void* buf, size_t& len, int f = 0);

      bool
      receive_msg (SafeMsg& msg, int f = 0);

      bool
      set_option (int opt, const void* val, size_t len);

    protected:
      Socket (socket_type h)
        : h_ (h) {}
      Socket (const Socket&) = delete;

      Socket& operator= (const Socket&) = delete;

      socket_type h_ {nullptr};
      int last_error_ {0};
    };

    class ZMQ_PSDD_STUB_Export WriterSocket
      : public Socket
    {
    public:
      WriterSocket () = default;
      WriterSocket (socket_type h)
        : Socket (h) {}
      WriterSocket (WriterSocket&& ws)
        : Socket (std::move (ws))
      {}
      virtual ~WriterSocket () = default;

      void send (
          void*,
          size_t);

      void send_topic (
          SafeMsg& key,
          SafeMsg& data);

      WriterSocket& operator= (WriterSocket&& ws)
      { this->Socket::operator= (std::move (ws)); return *this; }

    protected:
      WriterSocket (const WriterSocket&) = delete;

      WriterSocket& operator= (const WriterSocket&) = delete;
    };

    class ZMQ_PSDD_STUB_Export ReaderSocket
      : public Socket
    {
    public:
      ReaderSocket () = default;
      ReaderSocket (socket_type s)
        : Socket (s) {}
      ReaderSocket (ReaderSocket&& rs)
        : Socket (std::move (rs))
      {}
      virtual ~ReaderSocket () = default;

      bool
      receive_topic (
          ::zmq_msg_t* key_frame, SafeMsg& key,
          ::zmq_msg_t* data_frame, SafeMsg& data,
          bool no_wait);

      ReaderSocket& operator= (ReaderSocket&& rs)
      { this->Socket::operator= (std::move (rs)); return *this; }

    protected:
      ReaderSocket (const ReaderSocket&) = delete;

      ReaderSocket& operator= (const ReaderSocket&) = delete;
    };

    class ZMQ_PSDD_STUB_Export SubscriberSocket
      : public ReaderSocket
    {
    public:
      SubscriberSocket () = default;
      SubscriberSocket (socket_type s)
        : ReaderSocket (s) {}
      SubscriberSocket (SubscriberSocket&& ss)
        : ReaderSocket (std::move (ss))
      {}
      virtual ~SubscriberSocket () = default;

      void
      subscribe_topic (
          const void* d,
          size_t l);

      void
      unsubscribe_topic (
          const void* d,
          size_t l);

      SubscriberSocket& operator= (SubscriberSocket&& ss)
      { this->ReaderSocket::operator= (std::move (ss)); return *this; }

    protected:
      SubscriberSocket (const SubscriberSocket&) = delete;

      SubscriberSocket& operator= (const SubscriberSocket&) = delete;
    };

    class ZMQ_PSDD_STUB_Export ListenSocket
    {
    public:
      ListenSocket () = default;
      ListenSocket (const ListenSocket& ls)
        : listener_ (ls.listener_)
      {}
      ListenSocket (ListenSocket&& ls)
        : listener_ (std::move (ls.listener_))
      {}
      ~ListenSocket () = default;

      bool setup (zmq_pollitem_t*);
      void mark_input ();
      void handle_input ();

      ListenSocket& operator= (const ListenSocket& ls)
      {
        this->listener_  = ls.listener_;
        return *this;
      }
      ListenSocket& operator= (ListenSocket&& ls)
      {
        this->listener_  = std::move (ls.listener_);
        return *this;
      }

      bool operator== (const ListenSocket& ls) const
      {
        return ((this->listener_ == nullptr && ls.listener_ == nullptr)
            || const_cast<ListenSocket*> (this)->listener_->_is_equivalent (ls.listener_));
      }
      bool operator== (IDL::traits< ::PSDD::ZMQ::Listener>::ref_type lr) const
      {
        return ((this->listener_ == nullptr && lr == nullptr)
            || const_cast<ListenSocket*> (this)->listener_->_is_equivalent (lr));
      }

    protected:
      friend class Context_Impl;

      ListenSocket (
          IDL::traits< ::PSDD::ZMQ::Listener>::ref_type lr)
        : listener_ (lr)
      {}

      IDL::traits< ::PSDD::ZMQ::Listener>::ref_type listener_ {};
    };
  }
}

#endif
