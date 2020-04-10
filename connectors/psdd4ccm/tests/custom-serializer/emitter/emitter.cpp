// -*- C++ -*-
/**
 * @file    emitter.cpp
 * @author  Martin Corino
 *
 * @brief   Plain C++ ZMQ topic emitter.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */


#include "psdd4ccm/logger/psdd4ccm_log.h"

#include "zmq.h"

#include <string>
#include <sstream>
#include <chrono>
#include <thread>

const std::string endpoint {"tcp://*:50005"};
const uint32_t max_samples = 25;
std::string sample_keys[] = {
  {"sample/type1"},
  {"sample/type2"}
};
const uint32_t num_keys = sizeof(sample_keys) / sizeof (std::string);

int main (int, char *[])
{
  void *context;
  // create new ZMQ context
  if ((context = ::zmq_ctx_new ()) == nullptr)
  {
    PSDD4CCM_LOG_PANIC ("Unable to create ZMQ context.");
    return (1);
  }

  void *socket;
  if ((socket = ::zmq_socket (context, ZMQ_PUB)) == nullptr)
  {
    PSDD4CCM_LOG_PANIC ("Unable to create ZMQ socket.");
    return (1);
  }

  if (::zmq_bind (socket, endpoint.c_str ()) != 0)
  {
    PSDD4CCM_LOG_PANIC ("Unable to bind ZMQ socket to [" << endpoint << "]");
    return (1);
  }

  PSDD4CCM_LOG_DEBUG ("emitter socket bound to [" << endpoint << "]");

  // wait some to give the subscriber time to process the publisher coming online
  std::this_thread::sleep_for(std::chrono::milliseconds (500));

  for (uint32_t sample_count=0; sample_count<max_samples ;++sample_count)
  {
    for (uint32_t nkey=0; nkey<num_keys ;++nkey)
    {
      std::ostringstream oss;
      oss << sample_keys[nkey] << ':'                       // sample key
          << (1+(sample_count % 5)) << ':'                  // device id
          << sample_count << ':'                            // msgid
          << (((sample_count % 3) > 0) ? 'T' : 'F') << ':'  // status
          << (((sample_count+nkey) % 7) * 12.345);          // value
      std::string msg = oss.str ();

      PSDD4CCM_LOG_DEBUG ("emitter sending [" << msg << "]");

      if (::zmq_send (socket, msg.c_str (), msg.size (), 0) == -1)
      {
        int last_error = ::zmq_errno ();
        PSDD4CCM_LOG_PANIC (
          "failed to send [" <<
          ::zmq_strerror (last_error) << "]");

        ::zmq_close (socket);
        return (1);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
  }

  ::zmq_close (socket);
  return (0);
}
