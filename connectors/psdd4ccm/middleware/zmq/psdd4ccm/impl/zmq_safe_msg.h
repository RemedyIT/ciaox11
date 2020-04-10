// -*- C++ -*-
/**
 * @file    zmq_safe_msg.h
 * @author  Martin Corino
 *
 * @brief   ZMQ safe message wrapper
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_SAFE_MSG_H_
#define ZMQ_SAFE_MSG_H_

#include "psdd4ccm/logger/psdd4ccm_log.h"

#include <zmq.h>

namespace PSDD
{
  namespace ZMQ
  {
    class SafeMsg
    {
    public:
      SafeMsg () = default;
      SafeMsg (SafeMsg&& smsg)
      { this->reset (smsg.release ()); }
      SafeMsg (::zmq_msg_t* msg)
      { this->reset (msg); }
      ~SafeMsg ()
      { this->reset (); }

      void reset (::zmq_msg_t* msg = nullptr)
      {
        if (this->msg_ && ::zmq_msg_close (this->msg_) != 0)
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::SafeMsg::reset" <<
            " - failed to close ZMQ message [" <<
            ::zmq_strerror (::zmq_errno ()) << "]");
        }
        this->msg_ = msg;
      }

      bool initialize (::zmq_msg_t* msg)
      {
        if (::zmq_msg_init (msg) == 0)
        {
          this->reset (msg);
          return true;
        }
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::SafeMsg::initialize" <<
          " - failed to initialize empty ZMQ message [" <<
          ::zmq_strerror (::zmq_errno ()) << "]");
        return false;
      }
      bool initialize (::zmq_msg_t* msg,
                       void* data, size_t size,
                       ::zmq_free_fn* fn_free = nullptr,
                       void* hint = nullptr)
      {
        if (::zmq_msg_init_data (msg, data, size, fn_free, hint) == 0)
        {
          this->reset (msg);
          return true;
        }
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::SafeMsg::initialize" <<
          " - failed to initialize ZMQ message data [" <<
          ::zmq_strerror (::zmq_errno ()) << "]");
        return false;
      }

      ::zmq_msg_t* release ()
      { ::zmq_msg_t* msg = this->msg_; this->msg_ = nullptr; return msg; }

      ::zmq_msg_t* operator& () const
      { return this->msg_; }

      SafeMsg& operator =(SafeMsg&& smsg)
      { this->reset (smsg.release ()); return *this; }

      SafeMsg& operator =(::zmq_msg_t* msg)
      { this->reset (msg); return *this; }

      explicit operator bool() const // never throws
      { return msg_ == nullptr ? false : true; }
      bool operator ==(std::nullptr_t) const // never throws
      { return msg_ == nullptr ? true : false; }
      bool operator !=(std::nullptr_t) const // never throws
      { return msg_ == nullptr ? false : true; }

    private:
      SafeMsg (const SafeMsg& smsg) = delete;
      SafeMsg& operator =(const SafeMsg& smsg) = delete;

      ::zmq_msg_t* msg_ {nullptr};
    };
  }
}

#endif /* ZMQ_SAFE_MSG_H_ */
