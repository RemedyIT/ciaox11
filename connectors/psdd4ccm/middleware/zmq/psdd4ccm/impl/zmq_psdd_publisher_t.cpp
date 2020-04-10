// -*- C++ -*-
/**
 * @file    zmq_psdd_publisher_t.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD publisher template
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_PUBLISHER_T_CPP
#define ZMQ_PSDD_PUBLISHER_T_CPP

#include "psdd4ccm/logger/psdd4ccm_log.h"

namespace PSDD
{
  namespace ZMQ
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Publisher_T ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Publisher_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::Publisher_T()");
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::~Publisher_T ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Publisher_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::~Publisher_T()");

      this->shutdown ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::initialize (
        const std::string &topic_name,
        std::shared_ptr<service_helper_type> svhlp)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Publisher_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::initialize");

      this->service_helper_ = svhlp;

      if (this->service_helper_->publisher_enabled ())
      {
        // initialize message stream object
        this->data_out_ = CORBA::make_reference<PSDataOut_Impl>(
            this->service_helper_->get_config ().use_message_envelope ());

        // initialize the serializer
        this->serializer_.initialize (topic_name, svhlp);

        if (!this->socket_) // should always be true
        {
          // create a ZMQ publisher socket
          this->socket_ =
              this->service_helper_->create_publisher_socket ();
        }
        else
        {
          PSDD4CCM_LOG_WARNING (
            "PSDD::ZMQ::Publisher_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::initialize" <<
            " - already initialized");
        }
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::shutdown ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Publisher_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::shutdown");

      // close the ZMQ publisher socket
      this->socket_.close ();
    }

    /**
     * CCM_PSDD Publisher methods
     */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::write_one (
        typename IDL::traits<TOPIC_TYPE>::in_type datum)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Publisher_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::write_one");

      if (this->socket_)
      {
        std::lock_guard<std::mutex> g_ (this->lock_);

        this->write_i (datum);
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::write_one" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
                  "PSDD::ZMQ::Publisher_T<>::write_one", "NO_CONNECTION");
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::write_many (
        typename IDL::traits<TOPIC_SEQ_TYPE>::in_type data)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Publisher_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::write_one");

      if (this->socket_)
      {
        std::lock_guard<std::mutex> g_ (this->lock_);

        for (typename IDL::traits<TOPIC_TYPE>::in_type datum : data)
        {
          this->write_i (datum);
        }
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::write_one" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
                  "PSDD::ZMQ::Publisher_T<>::write_many", "NO_CONNECTION");
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::write_i (
        typename IDL::traits<TOPIC_TYPE>::in_type datum)
    {
      // start the message buffer
      this->data_out_->start_message ();

      PSDD4CCM_LOG_DEBUG (
        "PSDD::ZMQ::Publisher_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::write_i" <<
        " - serializing key");

      // setup packing and serialize the key
      if (this->serializer_.setup_pack (this->data_out_)
            && this->serializer_.pack_key (this->data_out_, datum))
      {
        PSDD4CCM_LOG_DEBUG (
          "PSDD::ZMQ::Publisher_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::write_i" <<
          " - traits::key_only=" <<
          (typename topic_psdd_traits_type::key_only () ? "true" : "false") <<
          " custom serializer=" <<
          (this->service_helper_->has_custom_serializer () ? "true" : "false"));

        // serialize any non-key data
        PSDD4CCM_LOG_DEBUG (
          "PSDD::ZMQ::Publisher_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::write_i" <<
          " - serializing data");

        bool pack_rc =
            this->serializer_.pack_data (this->data_out_, datum);

        // cleanup packing
        this->serializer_.finalize_pack (this->data_out_);

        if (!pack_rc)
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Publisher_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::write_i" <<
            " - failed to serialize non-key data");

          throw ::CCM_PSDD::InternalError (
                    "PSDD::ZMQ::Publisher_T<>::write_i", "PACK_ERR");
        }

        ::zmq_msg_t key_frame, data_frame;
        SafeMsg safe_key_frame, safe_data_frame;
        // setup the message frames
        this->data_out_->finish_message (
            &key_frame, safe_key_frame,
            &data_frame, safe_data_frame);

        this->socket_.send_topic (
            safe_key_frame,
            safe_data_frame);
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Publisher_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::subscribe_any" <<
          " - failed to serialize key data");

        // cleanup (for custom serializers)
        this->serializer_.finalize_pack (this->data_out_);

        throw ::CCM_PSDD::InternalError (
                  "PSDD::ZMQ::Publisher_T<>::write_i",
                  "PACK_ERR");
      }
    }

  };
};

#endif /* ZMQ_PSDD_PUBLISHER_T_CPP */
