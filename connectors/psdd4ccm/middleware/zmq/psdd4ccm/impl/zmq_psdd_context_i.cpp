// -*- C++ -*-
/**
 * @file    zmq_psdd_context_i.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ Context for PSDD implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "psdd4ccm/impl/psdd4ccm_config_util.h"
#include "psdd4ccm/impl/zmq_psdd_context_i.h"

#include "psdd4ccm/logger/psdd4ccm_log.h"

#include "ciaox11/deployment/handlers/ciaox11_state.h"

#include "zmq_psdd_propertiesC.h"

#include <new>
#include <stdexcept>

using namespace CIAOX11;

namespace PSDD
{
  namespace ZMQ
  {
    Context_Impl::Context_Impl ()
    {
    }

    Context_Impl::~Context_Impl ()
    {
      if (this->context_)
        ::zmq_ctx_term (this->context_);
    }

    void
    Context_Impl::initialize (const Config& cfg)
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Context_Impl::initialize" );

      // create new ZMQ context
      if ((this->context_ = ::zmq_ctx_new ()) == nullptr)
      {
        throw ::CCM_PSDD::InternalError (
            "PSDD::ZMQ::Context_Impl::initialize",
            "NO_MEMORY");
      }

      // retrieve container instance config properties
      Components::ConfigValues config;
      DEPLOYMENT_STATE->fetch_container_configuration (cfg.container (), config);

      // build property map from config for easier searching
      Util::property_map_t propmap;
      Util::build_property_map (config, propmap);

      Util::property_map_t::const_iterator pit;
      if ((pit = propmap.find (SERVICE_MAX_SOCKETS)) != propmap.cend ())
      {
        if (!(pit->second >>= this->max_sockets_))
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to extract max sockets");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "INV_MAXSOCK");
        }
      }
      // compare configured (default) setting with ZMQ default
      int n = ::zmq_ctx_get (this->context_, ZMQ_MAX_SOCKETS);
      if (((uint32_t)n) < this->max_sockets_)
      {
        // update ZMQ context for our setting
        n = this->max_sockets_;
        if (::zmq_ctx_set (this->context_, ZMQ_MAX_SOCKETS, n) != 0)
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to set max sockets [" <<
              ::zmq_strerror (::zmq_errno ()) << "]");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "CTXSET");
        }
      }

      if ((pit = propmap.find (SERVICE_IO_THREADS)) != propmap.cend ())
      {
        int n;
        if (!(pit->second >>= n))
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to extract io threads");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "INV_IOTHREADS");
        }

        if (::zmq_ctx_set (this->context_, ZMQ_IO_THREADS, n) != 0)
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to set io threads [" <<
              ::zmq_strerror (::zmq_errno ()) << "]");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "CTXSET");
        }
      }

#if ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 1, 0)
      if ((pit = propmap.find (SERVICE_THREAD_PRIO)) != propmap.cend ())
      {
        int n;
        if (!(pit->second >>= n))
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to extract io thread prio");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "INV_THREADPRIO");
        }

        if (::zmq_ctx_set (this->context_, ZMQ_THREAD_PRIORITY, n) != 0)
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to set io thread priority [" <<
              ::zmq_strerror (::zmq_errno ()) << "]");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "CTXSET");
        }
      }

      if ((pit = propmap.find (SERVICE_THREAD_SCHED_POLICY)) != propmap.cend ())
      {
        int n;
        if (!(pit->second >>= n))
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to extract thread scheduling policy");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "INV_THREADSCHEDPOL");
        }

        if (::zmq_ctx_set (this->context_, ZMQ_THREAD_SCHED_POLICY, n) != 0)
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to set io thread scheduling policy [" <<
              ::zmq_strerror (::zmq_errno ()) << "]");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "CTXSET");
        }
      }
#endif

      if ((pit = propmap.find (SERVICE_POLLING_THREADS)) != propmap.cend ())
      {
        if (!(pit->second >>= this->num_poll_threads_))
        {
          PSDD4CCM_LOG_PANIC (
              "PSDD::ZMQ::Context_Impl::initialize" <<
              " - failed to extract polling thread number");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Context_Impl::initialize",
              "INV_NUMPOLLTHREADS");
        }
      }
   }

   void
   Context_Impl::register_client ()
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::register_client" );

     this->client_count_++;

     PSDD4CCM_LOG_DEBUG (
         "PSDD::ZMQ::Context_Impl::register_client" <<
         " - client #" << this->client_count_);
   }

   void
   Context_Impl::unregister_client ()
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::unregister_client" );

     if (this->client_count_ > 0)
     {
       this->client_count_--;

       PSDD4CCM_LOG_DEBUG (
           "PSDD::ZMQ::Context_Impl::unregister_client" <<
           " - client #" << this->client_count_);

       if (this->client_count_ == 0)
       {
         // shutdown service context threads
         PSDD4CCM_LOG_INFO (
             "PSDD::ZMQ::Context_Impl::unregister_client" <<
             " - shutting down service threads");

         this->poller_.stop ();

         this->multiplexer_.stop ();
       }
     }
     else
     {
       PSDD4CCM_LOG_ERROR (
           "PSDD::ZMQ::Context_Impl::unregister_client" <<
           " - no clients registered");
     }
   }

   SubscriberSocket
   Context_Impl::create_subscriber_socket (
       const Config& cfg)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::create_subscriber_socket" );

     SubscriberSocket ss (::zmq_socket (this->context_, ZMQ_SUB));
     if (ss)
     {
       // configure the socket
       cfg.configure_subscriber_socket (ss);

       // check connection scheme
       if (cfg.subscriber_connection_scheme () == ConnectionScheme::CONNECT)
       {
         // connect endpoints
         if (this->connect (ss, cfg.subscriber_endpoints ()))
           return ss;
       }
       else
       {
         // bind endpoints
         if (this->bind (ss, cfg.subscriber_endpoints ()))
           return ss;
       }
     }
     return {};
   }

   WriterSocket
   Context_Impl::create_publisher_socket (
       const Config& cfg)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::create_publisher_socket");

     WriterSocket ps (::zmq_socket (this->context_, ZMQ_PUB));
     if (ps)
     {
       // configure the socket
       cfg.configure_publisher_socket (ps);

       // check connection scheme
       if (cfg.publisher_connection_scheme () == ConnectionScheme::CONNECT)
       {
         // connect endpoints
         if (this->connect (ps, cfg.publisher_endpoints ()))
           return ps;
       }
       else
       {
         // bind endpoints
         if (this->bind (ps, cfg.publisher_endpoints ()))
           return ps;
       }
     }
     return {};
   }

   WriterSocket
   Context_Impl::create_publisher_multiplex_socket (
       const Config& cfg)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::create_publisher_multiplex_socket");

     // setup (or update) the multiplexer
     if (this->setup_multiplex (cfg))
     {
       // open up a socket for the multiplexer
       WriterSocket pws (::zmq_socket (this->context_, ZMQ_PUSH));
       if (!pws)
       {
         PSDD4CCM_LOG_ERROR (
           "PSDD::ZMQ::Context_Impl::create_publisher_multiplex_socket" <<
           " - failed to create socket");

         return {};
       }
       // connect to multiplexer endpoint
       if (!pws.connect (this->multiplexer_.endpoint ()))
       {
         PSDD4CCM_LOG_ERROR (
           "PSDD::ZMQ::Context_Impl::create_publisher_multiplex_socket" <<
           " - failed to connect socket");

         return {};
       }

       return pws;
     }
     // no multiplexer available
     return {};
   }

   bool
   Context_Impl::bind (
       Socket& s,
       const std::vector<std::string>& eps)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::bind");

     // bind endpoints
     for (const std::string& ep : eps)
     {
       if (ep.empty ())
       {
         PSDD4CCM_LOG_WARNING (
           "PSDD::ZMQ::Context_Impl::bind" <<
           " - found empty endpoint");
       }
       else
       {
         PSDD4CCM_LOG_INFO (
           "PSDD::ZMQ::Context_Impl::bind" <<
           " - binding to \'" << ep << "\'");

         if (!s.bind (ep))
         {
           return false;
         }
       }
     }
     return true;
   }

   bool
   Context_Impl::connect (
       Socket& s,
       const std::vector<std::string>& eps)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::connect");

     // connect to the configured endpoints
     for (const std::string& ep : eps)
     {
       if (ep.empty ())
       {
         PSDD4CCM_LOG_WARNING (
           "PSDD::ZMQ::Context_Impl::connect" <<
           " - found empty endpoint");
       }
       else
       {
         PSDD4CCM_LOG_INFO (
           "PSDD::ZMQ::Context_Impl::connect" <<
           " - connecting to \'" << ep << "\'");

         if (!s.connect (ep))
         {
           return false;
         }
       }
     }
     return true;
   }

   bool
   Context_Impl::setup_multiplex (
     const Config& cfg)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::setup_multiplex");

     // check if we still have to start a multiplexer
     if (!this->multiplexer_.started ())
     {
       // start the multiplexer
       if (!this->multiplexer_.start (
             this->context_,
             cfg))
       {
         return false;
       }
     }
     else
     {
       // bind any additional publishing endpoints
       return this->multiplexer_.bind (
           cfg.publisher_endpoints ());
     }

     return true;
   }

   void
   Context_Impl::schedule_listener (
       IDL::traits< ::PSDD::ZMQ::Listener>::ref_type lr)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::schedule_listener");

     // make sure the polling threads have started
     this->poller_.start (
         this->context_,
         this->max_sockets_,
         this->num_poll_threads_);

     // add polling listener
     this->poller_.add_listener (
         ListenSocket (lr));
   }

   void
   Context_Impl::remove_listener (
       IDL::traits< ::PSDD::ZMQ::Listener>::ref_type lr)
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::remove_listener");

     // remove polling listener
     this->poller_.remove_listener (
         ListenSocket (lr));
   }

   void
   Context_Impl::reset_listeners ()
   {
     PSDD4CCM_LOG_TRACE (
         "PSDD::ZMQ::Context_Impl::reset_listeners");

     // wake up and reset poller
     this->poller_.interrupt ();
   }
 }
}
