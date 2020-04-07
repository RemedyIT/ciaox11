// -*- C++ -*-
/**
 * @file    zmq_psdd_config.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD configuration parser/handler
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "psdd4ccm/impl/zmq_psdd_config.h"
#include "psdd4ccm/logger/psdd4ccm_log.h"

#include "ciaox11/deployment/handlers/ciaox11_state.h"

#include "ace/OS_NS_dlfcn.h"

#include <string>
#include <cctype>

using namespace CIAOX11;

namespace PSDD
{
  namespace ZMQ
  {
    // anonymous namespace with utility method for case insensitive string compare
    namespace
    {
      inline bool icasecmp(const std::string& l, const std::string& r)
      {
          typedef typename std::string::value_type valtype;
          return l.size() == r.size()
              && std::equal(l.cbegin(), l.cend(), r.cbegin(),
                  [](valtype l1, valtype r1)
                      { return std::toupper(l1) == std::toupper(r1); });
      }
    }

    /* Initialize service configuration from deployment plan
     * properties for component instance.
     */
    void
    Config::initialize (const std::string& inst, bool publish, bool subscribe)
    {
      PSDD4CCM_LOG_TRACE("PSDD::ZMQ::Config::initialize");

      // determine the container in which this component is installed
      this->container_id_ = DEPLOYMENT_STATE->component_container_id(inst);

      // retrieve deployment properties from deployment state
      Components::ConfigValues config;
      DEPLOYMENT_STATE->fetch_component_configuration (inst, config);

      if (config.empty ())
      {
        this->parse_error (
            "no configuration properties found",
            "MISSING_CONFIG");
      }

      // build property map from config for easier searching
      Util::property_map_t propmap;
      Util::build_property_map (config, propmap);

      // do we need to check for publisher config?
      if (publish)
      {
        this->parse_publisher_settings (propmap);
        this->publisher_enabled_ = true;
      }

      // do we need to check for subscriber config?
      if (subscribe)
      {
        this->parse_subscriber_settings (propmap);
        this->subscriber_enabled_ = true;
      }

      // check for custom serializer settings (if any)
      this->parse_serializer_settings (propmap);
    }

    void
    Config::parse_error (
        const char* log,
        const char* err)
    {
      PSDD4CCM_LOG_ERROR(
          "PSDD::ZMQ::Config::initialize" << " - " <<
          log);

      throw ::CCM_PSDD::InternalError (
          "PSDD::ZMQ::Config::initialize",
          err);
    }

    void
    Config::parse_publisher_settings (
        const Util::property_map_t& propmap)
    {
      PSDD4CCM_LOG_TRACE(
          "PSDD::ZMQ::Config::parse_publisher_settings");

      Util::property_map_t::const_iterator pit;
      if ((pit = propmap.find (PUBLISHER_ENDPOINTS)) != propmap.cend ())
      {
        if (!(pit->second >>= this->publisher_endpoints_))
        {
          this->parse_error (
              "failed to extract publisher endpoints",
              "INV_PUBEP");
        }
      }
      else
      {
        this->parse_error (
            "missing required publisher endpoints",
            "INV_PUBEP");
      }

      if ((pit = propmap.find (PUBLISHER_IPV6)) != propmap.cend ())
      {
        if (!(pit->second >>= this->publisher_ipv6_))
        {
          this->parse_error (
              "failed to extract publisher ipv6",
              "INV_PUBIPV6");
        }
      }

      if ((pit = propmap.find (PUBLISHER_CONN_SCHEME)) != propmap.cend ())
      {
        std::string conn_scheme;
        if (!(pit->second >>= conn_scheme))
        {
          this->parse_error (
              "failed to extract publisher connection scheme",
              "INV_PUBCONNSCHEME");
        }
        else
        {
          if (icasecmp (conn_scheme, CONN_BIND_MULTPLEX))
            this->publisher_conn_scheme_ = ConnectionScheme::BIND_MULTIPLEX;
          else if (icasecmp (conn_scheme, CONN_CONNECT))
            this->publisher_conn_scheme_ = ConnectionScheme::CONNECT;
          else if (icasecmp (conn_scheme, CONN_BIND))
            this->publisher_conn_scheme_ = ConnectionScheme::BIND;
          else
          {
            this->parse_error (
                "invalid publisher connection scheme specified",
                "INV_PUBCONNSCHEME");
          }
        }
      }

      if ((pit = propmap.find (PUBLISHER_SEND_TIMEOUT)) != propmap.cend ())
      {
        if (!(pit->second >>= this->publisher_send_timeout_))
        {
          this->parse_error (
              "failed to extract publisher send timeout",
              "INV_PUBSNDTO");
        }
      }

      if ((pit = propmap.find (PUBLISHER_RECOVERY_IVL)) != propmap.cend ())
      {
        if (!(pit->second >>= this->publisher_recovery_ivl_))
        {
          this->parse_error (
              "failed to extract publisher send timeout",
              "INV_PUBRECOVIVL");
        }
      }

      // check for tuning options
      this->parse_tuning_settings (
          true,
          propmap,
          this->publisher_tuning_params_);

      // check for security settings
      this->parse_security_settings (
          true,
          propmap,
          this->publisher_security_params_);
    }

    void
    Config::parse_subscriber_settings (
        const Util::property_map_t& propmap)
    {
      PSDD4CCM_LOG_TRACE(
          "PSDD::ZMQ::Config::parse_subscriber_settings");

      Util::property_map_t::const_iterator pit;
      if ((pit = propmap.find (SUBSCRIBER_ENDPOINTS)) != propmap.cend ())
      {
        if (!(pit->second >>= this->subscriber_endpoints_))
        {
          this->parse_error (
              "failed to extract subscriber endpoints",
              "INV_SUBEP");
        }
      }
      else
      {
        this->parse_error (
            "missing required subscriber endpoints",
            "INV_SUBEP");
      }

      if ((pit = propmap.find (SUBSCRIBER_CONN_SCHEME)) != propmap.cend ())
      {
        std::string conn_scheme;
        if (!(pit->second >>= conn_scheme))
        {
          this->parse_error (
              "failed to extract subscriber connection scheme",
              "INV_SUBCONNSCHEME");
        }
        else
        {
          if (icasecmp (conn_scheme, CONN_BIND))
            this->subscriber_conn_scheme_ = ConnectionScheme::BIND;
          else if (icasecmp (conn_scheme, CONN_CONNECT))
            this->subscriber_conn_scheme_ = ConnectionScheme::CONNECT;
          else
          {
            this->parse_error (
                "invalid subscriber connection scheme specified",
                "INV_SUBCONNSCHEME");
          }
        }
      }

      if ((pit = propmap.find (SUBSCRIBER_IPV6)) != propmap.cend ())
      {
        if (!(pit->second >>= this->subscriber_ipv6_))
        {
          this->parse_error (
              "failed to extract subscriber ipv6",
              "INV_SUBIPV6");
        }
      }

      if ((pit = propmap.find (SUBSCRIBER_RECEIVE_TIMEOUT)) != propmap.cend ())
      {
        if (!(pit->second >>= this->subscriber_receive_timeout_))
        {
          this->parse_error (
              "failed to extract subscriber receive timeout",
              "INV_SUBRCVTO");
        }
      }

      if ((pit = propmap.find (SUBSCRIBER_RECONNECT_IVL)) != propmap.cend ())
      {
        if (!(pit->second >>= this->subscriber_reconnect_ivl_))
        {
          this->parse_error (
              "failed to extract subscriber reconnect ivl",
              "INV_SUBRECONIVL");
        }
      }

      if ((pit = propmap.find (SUBSCRIBER_RECONNECT_IVL_MAX)) != propmap.cend ())
      {
        if (!(pit->second >>= this->subscriber_reconnect_ivl_max_))
        {
          this->parse_error (
              "failed to extract subscriber reconnect ivl max",
              "INV_SUBRECONIVLMAX");
        }
      }

      // check for tuning options
      this->parse_tuning_settings (
          false,
          propmap,
          this->subscriber_tuning_params_);

      // check for security settings
      this->parse_security_settings (
          false,
          propmap,
          this->subscriber_security_params_);
    }

    void
    Config::parse_tuning_settings (
        bool publisher,
        const Util::property_map_t& propmap,
        tuning_param_type& tuning_params)
    {
      PSDD4CCM_LOG_TRACE(
          "PSDD::ZMQ::Config::parse_tuning_settings");

      Util::property_map_t::const_iterator pit;
      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_TOS : SUBSCRIBER_TUNING_TOS)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.tos_))
        {
          this->parse_error (
              "failed to extract tuning tos",
              "INV_TOS");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_IO_AFFINITY : SUBSCRIBER_TUNING_IO_AFFINITY)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.io_affinity_))
        {
          this->parse_error (
              "failed to extract tuning tos",
              "INV_TOS");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_LINGER : SUBSCRIBER_TUNING_LINGER)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.linger_))
        {
          this->parse_error (
              "failed to extract tuning linger",
              "INV_LINGER");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_MAXMSGSIZE : SUBSCRIBER_TUNING_MAXMSGSIZE)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.maxmsgsize_))
        {
          this->parse_error (
              "failed to extract tuning maxmsgsize",
              "INV_MAXMSGSIZE");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_MCAST_HOPS : SUBSCRIBER_TUNING_MCAST_HOPS)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.multicast_hops_))
        {
          this->parse_error (
              "failed to extract tuning multicast_hops",
              "INV_MCASTHOPS");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_MCAST_MAXTPDU : SUBSCRIBER_TUNING_MCAST_MAXTPDU)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.multicast_maxtpdu_))
        {
          this->parse_error (
              "failed to extract tuning multicast_maxtpdu",
              "INV_MCASTMAXTPDU");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_MCAST_RATE : SUBSCRIBER_TUNING_MCAST_RATE)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.multicast_rate_))
        {
          this->parse_error (
              "failed to extract tuning multicast_rate",
              "INV_MCASTRATE");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_RCVBUF : SUBSCRIBER_TUNING_RCVBUF)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.rcvbuf_))
        {
          this->parse_error (
              "failed to extract tuning rcvbuf",
              "INV_RCVBUF");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_RCVHWM : SUBSCRIBER_TUNING_RCVHWM)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.rcvhwm_))
        {
          this->parse_error (
              "failed to extract tuning rcvhwm",
              "INV_RCVHWM");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_SNDBUF : SUBSCRIBER_TUNING_SNDBUF)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.rcvbuf_))
        {
          this->parse_error (
              "failed to extract tuning sndbuf_",
              "INV_SNDBUF");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_SNDHWM : SUBSCRIBER_TUNING_SNDHWM)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.sndhwm_))
        {
          this->parse_error (
              "failed to extract tuning sndhwm",
              "INV_SNDHWM");
        }
        tuning_params.tuning_ = true;
      }

      if ((pit = propmap.find (publisher ? PUBLISHER_TUNING_HANDSHAKE_IVL : SUBSCRIBER_TUNING_HANDSHAKE_IVL)) != propmap.cend ())
      {
        if (!(pit->second >>= tuning_params.handshake_ivl_))
        {
          this->parse_error (
              "failed to extract tuning handshake_ivl",
              "INV_HSHAKEIVL");
        }
        tuning_params.tuning_ = true;
      }
    }

    void
    Config::parse_security_settings (
        bool publisher,
        const Util::property_map_t& propmap,
        security_param_type& security_params)
    {
      PSDD4CCM_LOG_TRACE(
          "PSDD::ZMQ::Config::parse_security_settings");

      Util::property_map_t::const_iterator pit;
      if ((pit = propmap.find (publisher ? PUBLISHER_CURVE_SERVER : SUBSCRIBER_CURVE_SERVER)) != propmap.cend ())
      {
        if (!(pit->second >>= security_params.curve_server_))
        {
          this->parse_error (
              "failed to extract security curve_server",
              "INV_SECCURVESRV");
        }

        if ((pit = propmap.find (publisher ? PUBLISHER_CURVE_KEY : SUBSCRIBER_CURVE_KEY)) != propmap.cend ())
        {
          if (!(pit->second >>= security_params.curve_key_))
          {
            this->parse_error (
                "failed to extract security curve_key",
                "INV_SECCURVEKEY");
          }
        }
        else
        {
          this->parse_error (
              "missing required security curve_key",
              "NO_SECCURVEKEY");
        }

        security_params.security_ = true;
      }
    }

    void
    Config::parse_serializer_settings (
        const Util::property_map_t& propmap)
    {
      PSDD4CCM_LOG_TRACE(
          "PSDD::ZMQ::Config::parse_serializer_settings");

      Util::property_map_t::const_iterator pit;
      if ((pit = propmap.find (SERIALIZER_MSG_ENVELOPE)) != propmap.cend ())
      {
        if (!(pit->second >>= this->use_message_envelope_))
        {
          this->parse_error (
              "failed to extract serializer msg envelope option",
              "INV_SERMSGENV");
        }
      }

      if ((pit = propmap.find (SERIALIZER_MODULE)) != propmap.cend ())
      {
        if (!(pit->second >>= this->serializer_module_))
        {
          this->parse_error (
              "failed to extract serializer module",
              "INV_SERMOD");
        }

        if ((pit = propmap.find (SERIALIZER_FACTORY)) != propmap.cend ())
        {
          if (!(pit->second >>= this->serializer_entrypoint_))
          {
            this->parse_error (
                "failed to extract serializer factory",
                "INV_SERFACTORY");
          }
        }
        else
        {
          this->parse_error (
              "missing required serializer factory",
              "NO_SERFACTORY");
        }

        if ((pit = propmap.find (SERIALIZER_OPENMODE)) != propmap.cend ())
        {
          if (!(pit->second >>= this->serializer_openmode_))
          {
            this->parse_error (
                "failed to extract serializer openmode",
                "INV_OPENMODE");
          }
        }
        else
        {
          this->serializer_openmode_ = ACE_DEFAULT_SHLIB_MODE;
        }

        this->custom_serializer_ = true;
      }
    }

    void
    Config::configure_subscriber_socket (
        Socket& s) const
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Config::configure_subscriber_socket" );

      if (this->subscriber_ipv6_)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::configure_subscriber_socket" <<
            " - enabling ipv6");

        int flag = 1;
        if (!s.set_option (ZMQ_IPV6, &flag, sizeof (flag)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::configure_subscriber_socket",
              "SETSOCKOPT:IPV6");
        }
      }

      if (this->subscriber_receive_timeout_ != -1)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::configure_subscriber_socket" <<
            " - setting receive timeout [" << this->subscriber_receive_timeout_ << "]");

        if (!s.set_option (ZMQ_RCVTIMEO,
                           &this->subscriber_receive_timeout_,
                           sizeof (this->subscriber_receive_timeout_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::configure_subscriber_socket",
              "SETSOCKOPT:RCVTIMEO");
        }
      }

      if (this->subscriber_reconnect_ivl_ != -1)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::configure_subscriber_socket" <<
            " - setting reconnect ivl [" << this->subscriber_reconnect_ivl_ << "]");

        if (!s.set_option (ZMQ_RECONNECT_IVL,
                           &this->subscriber_reconnect_ivl_,
                           sizeof (this->subscriber_reconnect_ivl_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::configure_subscriber_socket",
              "SETSOCKOPT:RECONIVL");
        }
      }

      if (this->subscriber_reconnect_ivl_max_ != -1)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::configure_subscriber_socket" <<
            " - setting reconnect ivl max [" << this->subscriber_reconnect_ivl_max_ << "]");

        if (!s.set_option (ZMQ_RECONNECT_IVL_MAX,
                           &this->subscriber_reconnect_ivl_max_,
                           sizeof (this->subscriber_reconnect_ivl_max_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::configure_subscriber_socket",
              "SETSOCKOPT:RECONIVLMAX");
        }
      }

      if (this->subscriber_tuning_params_.tuning_)
      {
        this->tune_socket (s, this->subscriber_tuning_params_);
      }

      if (this->subscriber_security_params_.security_)
      {
        this->secure_socket (s, this->subscriber_security_params_);
      }
    }

    void
    Config::configure_publisher_socket (
        Socket& s) const
    {
      if (this->publisher_ipv6_)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::create_subscriber_socket" <<
            " - enabling ipv6");

        int flag = 1;
        if (!s.set_option (ZMQ_IPV6, &flag, sizeof (flag)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::create_publisher_socket",
              "SETSOCKOPT:IPV6");
        }
      }

      // configure the send timeout
      if (this->publisher_send_timeout_ != -1)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::create_publisher_socket" <<
            " - setting send timeout [" << this->publisher_send_timeout_ << "]");

        if (!s.set_option (ZMQ_SNDTIMEO,
                           &this->publisher_send_timeout_,
                           sizeof (this->publisher_send_timeout_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::create_publisher_socket",
              "SETSOCKOPT:SNDTIMEO");
        }
      }

      if (this->publisher_recovery_ivl_ != -1)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::create_publisher_socket" <<
            " - setting recovery ivl [" << this->publisher_recovery_ivl_ << "]");

        if (!s.set_option (ZMQ_RECOVERY_IVL,
                           &this->publisher_recovery_ivl_,
                           sizeof (this->publisher_recovery_ivl_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::create_publisher_socket",
              "SETSOCKOPT:RECOVERIVL");
        }
      }

      if (this->publisher_tuning_params_.tuning_)
      {
        this->tune_socket (s, this->publisher_tuning_params_);
      }

      if (this->publisher_security_params_.security_)
      {
        this->secure_socket (s, this->publisher_security_params_);
      }
    }

    void
    Config::tune_socket (
        Socket& s,
        const tuning_param_type& tuning_param) const
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Config::tune_socket");

#if ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 1, 0)
      if (tuning_param.tos_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting TOS [" << tuning_param.tos_ << "]");

        if (!s.set_option(ZMQ_TOS,
                         &tuning_param.tos_,
                         sizeof (tuning_param.tos_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:TOS");
        }
      }
#endif

      if (tuning_param.io_affinity_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting IO affinity [" <<
            tuning_param.io_affinity_ << "]");

        if (!s.set_option (ZMQ_AFFINITY,
                           &tuning_param.io_affinity_,
                           sizeof (tuning_param.io_affinity_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:AFFINITY");
        }
      }

      if (tuning_param.linger_ >= -1)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting LINGER [" << tuning_param.linger_ << "]");

        if (!s.set_option (ZMQ_LINGER,
                          &tuning_param.linger_,
                          sizeof (tuning_param.linger_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:LINGER");
        }
      }

      if (tuning_param.maxmsgsize_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting max msgsize [" <<
            tuning_param.maxmsgsize_ << "]");

        if (!s.set_option (ZMQ_MAXMSGSIZE,
                           &tuning_param.maxmsgsize_,
                           sizeof (tuning_param.maxmsgsize_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:MAXMSGSZ");
        }
      }

      if (tuning_param.multicast_hops_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting multicast hops [" <<
            tuning_param.multicast_hops_ << "]");

        if (!s.set_option (ZMQ_MULTICAST_HOPS,
                           &tuning_param.multicast_hops_,
                           sizeof (tuning_param.multicast_hops_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:MCASTHOPS");
        }
      }

#if ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 2, 0)
      if (tuning_param.multicast_maxtpdu_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting multicast max TPDU size [" <<
            tuning_param.multicast_maxtpdu_ << "]");

        if (!s.set_option (ZMQ_MULTICAST_MAXTPDU,
                           &tuning_param.multicast_maxtpdu_,
                           sizeof (tuning_param.multicast_maxtpdu_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:MCASTMAXTPDU");
        }
      }
#endif

      if (tuning_param.multicast_rate_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting multicast rate [" <<
            tuning_param.multicast_rate_ << "]");

        if (!s.set_option (ZMQ_RATE,
                           &tuning_param.multicast_rate_,
                           sizeof (tuning_param.multicast_rate_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:MCASTRATE");
        }
      }

      if (tuning_param.rcvbuf_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting rcvbuf size [" <<
            tuning_param.rcvbuf_ << "]");

        if (!s.set_option (ZMQ_RCVBUF,
                           &tuning_param.rcvbuf_,
                           sizeof (tuning_param.rcvbuf_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:RCVBUF");
        }
      }

      if (tuning_param.rcvhwm_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting rcvhwm [" <<
            tuning_param.rcvhwm_ << "]");

        if (!s.set_option (ZMQ_RCVHWM,
                           &tuning_param.rcvhwm_,
                           sizeof (tuning_param.rcvhwm_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:RCVHWM");
        }
      }

      if (tuning_param.sndbuf_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting sndbuf size [" <<
            tuning_param.sndbuf_ << "]");

        if (!s.set_option (ZMQ_SNDBUF,
                           &tuning_param.sndbuf_,
                           sizeof (tuning_param.sndbuf_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:SNDBUF");
        }
      }

      if (tuning_param.sndhwm_ > 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting sndhwm [" <<
            tuning_param.sndhwm_ << "]");

        if (!s.set_option (ZMQ_SNDHWM,
                           &tuning_param.sndhwm_,
                           sizeof (tuning_param.sndhwm_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:SNDHWM");
        }
      }

#if ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 1, 0)
      if (tuning_param.handshake_ivl_ >= 0)
      {
        PSDD4CCM_LOG_DEBUG (
            "PSDD::ZMQ::Config::tune_socket" <<
            " - setting handshake ivl [" <<
            tuning_param.handshake_ivl_ << "]");

        if (!s.set_option (ZMQ_HANDSHAKE_IVL,
                           &tuning_param.handshake_ivl_,
                           sizeof (tuning_param.handshake_ivl_)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::tune_socket",
              "SETSOCKOPT:HNDSHKIVL");
        }
      }
#endif
    }

    void
    Config::secure_socket (
        Socket& s,
        const security_param_type& security_param) const
    {
      PSDD4CCM_LOG_TRACE (
          "PSDD::ZMQ::Config::secure_socket");

#if ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 1, 0)
      // check how to setup : as CURVE server or client
      if (security_param.curve_server_)
      {
        PSDD4CCM_LOG_INFO (
            "PSDD::ZMQ::Config::secure_socket" <<
            " - setting up CURVE server");

        // setup as CURVE server
        int flag = 1;
        if (!s.set_option (ZMQ_CURVE_SERVER,
                           &flag,
                           sizeof (flag)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::secure_socket",
              "SETSOCKOPT:CURVESRV");
        }

        // install CURVE server secret key
        if (!s.set_option (ZMQ_CURVE_SECRETKEY,
                           security_param.curve_key_.c_str (),
                           security_param.curve_key_.size ()+1))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::secure_socket",
              "SETSOCKOPT:CURVESECKEY");
        }
      }
      else
      {
        PSDD4CCM_LOG_INFO (
            "PSDD::ZMQ::Config::secure_socket" <<
            " - setting up CURVE client");

        // CURVE client is the default setting

        // install CURVE server public key
        if (!s.set_option (ZMQ_CURVE_SERVERKEY,
                           security_param.curve_key_.c_str (),
                           security_param.curve_key_.size ()+1))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::secure_socket",
              "SETSOCKOPT:CURVESRVKEY");
        }

        // generate client CURVE keypair
        char secret_key[41];
        char public_key[41];
        if (::zmq_curve_keypair (public_key, secret_key) != 0)
        {
          PSDD4CCM_LOG_ERROR (
              "PSDD::ZMQ::Config::secure_socket" <<
            " - failed to generate client CURVE keypair [" <<
            ::zmq_strerror (::zmq_errno ()) << "]");

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::secure_socket",
              "CURVEGEN");
        }

        // install client CURVE keypair
        if (!s.set_option (ZMQ_CURVE_SECRETKEY,
                           &secret_key[0],
                           sizeof(secret_key))
            ||
            !s.set_option (ZMQ_CURVE_PUBLICKEY,
                           &public_key[0],
                           sizeof(public_key)))
        {
          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Config::secure_socket",
              "SETSOCKOPT:CURVEKEYPAIR");
        }
      }
#else
    PSDD4CCM_LOG_WARNING (
      "PSDD::ZMQ::Config::secure_socket" <<
      " - CURVE security only supported with ZMQ >= 4.1.0");
#endif
    }
  }
}
