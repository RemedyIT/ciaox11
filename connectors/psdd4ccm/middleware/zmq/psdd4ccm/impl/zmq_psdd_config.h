// -*- C++ -*-
/**
 * @file    zmq_psdd_config.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD configuration parser/handler
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_PSDD_CONFIG_H_
#define ZMQ_PSDD_CONFIG_H_

#include "psdd4ccm/impl/zmq_psdd_sockets.h"
#include "psdd4ccm/impl/psdd4ccm_config_util.h"

#include "zmq_psdd_propertiesC.h"

#include "psdd4ccm/impl/zmq_psdd_stub_export.h"


namespace PSDD
{
  namespace ZMQ
  {
    class ZMQ_PSDD_STUB_Export Config
    {
    public:
      Config () = default;
      ~Config () = default;

      void
      initialize (
          const std::string&,
          bool,
          bool);

      bool
      publisher_enabled () const
      { return this->publisher_enabled_; }

      const std::vector<std::string>&
      publisher_endpoints () const
      { return this->publisher_endpoints_; }

      ConnectionScheme
      publisher_connection_scheme () const
      { return this->publisher_conn_scheme_; }

      bool
      subscriber_enabled () const
      { return this->subscriber_enabled_; }

      const std::vector<std::string>&
      subscriber_endpoints () const
      { return this->subscriber_endpoints_; }

      ConnectionScheme
      subscriber_connection_scheme () const
      { return this->subscriber_conn_scheme_; }

      bool use_message_envelope () const
      { return this->use_message_envelope_; }

      bool
      has_custom_serializer () const
      { return this->custom_serializer_; }

      const std::string&
      serializer_module () const
      { return this->serializer_module_; }

      const std::string&
      serializer_entry_point () const
      { return this->serializer_entrypoint_; }

      uint32_t
      serializer_openmode () const
      { return this->serializer_openmode_; }

      const std::string&
      container () const
      { return this->container_id_; }

    private:
      friend class Context_Impl;
      friend class Multiplex;

      void
      parse_error (const char* log, const char* err);

      struct tuning_param_type
      {
        bool tuning_ {false};
        int tos_ {-1};
        uint64_t io_affinity_ {0};
        int linger_ {std::numeric_limits<int>::min ()};
        int64_t maxmsgsize_ {-1};
        int multicast_hops_ {-1};
        int multicast_maxtpdu_ {-1};
        int multicast_rate_ {-1};
        int rcvbuf_ {-1};
        int rcvhwm_ {-1};
        int sndbuf_ {-1};
        int sndhwm_ {-1};
        int handshake_ivl_ {-1};
      };

      struct security_param_type
      {
        bool security_ {false};
        bool curve_server_ {false};
        // this should be either the server secret key when
        // curve_server_ == true or the server public key when
        // curve_server_ == false
        std::string curve_key_ {};
      };

      void
      parse_publisher_settings (
          const Util::property_map_t&);

      void
      parse_subscriber_settings (
          const Util::property_map_t&);

      void
      parse_tuning_settings (
          bool,
          const Util::property_map_t&,
          tuning_param_type&);

      void
      parse_security_settings (
          bool,
          const Util::property_map_t&,
          security_param_type&);

      void
      parse_serializer_settings (
          const Util::property_map_t&);

      void
      tune_socket (
          Socket&,
          const tuning_param_type&) const;

      void
      secure_socket (
          Socket&,
          const security_param_type&) const;

      void
      configure_subscriber_socket (
          Socket&) const;

      void
      configure_publisher_socket (
          Socket&) const;

      bool publisher_enabled_
      { false };
      std::vector<std::string> publisher_endpoints_
      {};
      ConnectionScheme publisher_conn_scheme_
      {ConnectionScheme::BIND};
      bool publisher_ipv6_
      {false};
      int publisher_send_timeout_
      {-1};
      int publisher_recovery_ivl_
      {-1};
      tuning_param_type publisher_tuning_params_ {};
      security_param_type publisher_security_params_ {};

      bool subscriber_enabled_
      { false };
      std::vector<std::string> subscriber_endpoints_
      {};
      ConnectionScheme subscriber_conn_scheme_
      {ConnectionScheme::CONNECT};
      bool subscriber_ipv6_
      {false};
      int subscriber_receive_timeout_
      {-1};
      int subscriber_reconnect_ivl_
      {-1};
      int subscriber_reconnect_ivl_max_
      {-1};
      tuning_param_type subscriber_tuning_params_ {};
      security_param_type subscriber_security_params_ {};

      bool use_message_envelope_
      { true };
      bool custom_serializer_
      { false};
      std::string serializer_module_
      {};
      std::string serializer_entrypoint_
      {};
      uint32_t serializer_openmode_
      {};

      std::string container_id_;
    };
  }
}

#endif
