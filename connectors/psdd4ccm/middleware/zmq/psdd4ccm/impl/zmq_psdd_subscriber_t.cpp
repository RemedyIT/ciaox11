// -*- C++ -*-
/**
 * @file    zmq_psdd_subscriber_t.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD subscriber template
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_SUBSCRIBER_T_CPP
#define ZMQ_PSDD_SUBSCRIBER_T_CPP

#include "psdd4ccm/logger/psdd4ccm_log.h"

#include <new>
#include <stdexcept>

namespace PSDD
{
  namespace ZMQ
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::Subscriber_T ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::Subscriber_T()");
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::~Subscriber_T ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::~Subscriber_T()");

      this->shutdown ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::_is_a (
        const std::string& local_type_id)
    {
      return this->::PSDD::Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::_is_a (local_type_id)
          || this->CCM_TYPE::consumer_traits::data_type::_is_a (local_type_id)
          || this->::PSDD::ZMQ::Listener::_is_a (local_type_id);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::_ref_type
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::_this ()
    {
      return _traits_type::narrow (this->Object::_lock ());
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::initialize (
          const std::string& topic_name,
          std::shared_ptr<service_helper_type> svhlp)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::initialize");

      this->service_helper_ = svhlp;

      if (this->service_helper_->subscriber_enabled ())
      {
        this->topic_name_ = topic_name;

        // initialize message stream object
        this->data_in_ = CORBA::make_reference<PSDataIn_Impl>(
            this->service_helper_->get_config ().use_message_envelope ());

        // initialize the serializer
        this->serializer_.initialize (topic_name, svhlp);

        if (!this->socket_) // should always be true
        {
          // create a ZMQ subscriber socket
          this->socket_ =
              this->service_helper_->create_subscriber_socket ();

          this->mark_readable ();
        }
        else
        {
          PSDD4CCM_LOG_WARNING (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::initialize" <<
            " - already initialized");
        }
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::shutdown ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::shutdown");

      // check if a listener has been activated
      if (this->listening_)
      {
        this->listening_ = false;

        // deactivate listener
        this->service_helper_->remove_listener (this->_this ());
      }

      this->readable_ = false;

      this->socket_.close ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    typename IDL::traits<typename Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_consumer_data_type>::ref_type
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_pull_consumer_data ()
    {
      return this->_this ();
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::activate_push_consumer_data_listener (
          const event_strategy_type& evs)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::activate_push_consumer_data_listener");

      if (this->service_helper_->subscriber_enabled ())
      {
        if (this->readable_ && !this->listening_) // should always be true
        {
          this->readable_ = false;
          this->listening_ = true;

          this->evs_ = evs;

          // activate listener
          this->service_helper_->schedule_listener (this->_this ());
        }
        else
        {
          PSDD4CCM_LOG_WARNING (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::activate_push_consumer_data_listener" <<
            " - no socket or already listening");
        }
      }
    }

      /**
       * ZQM PSDD Listener methods
       */
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::mark_readable ()
    {
      this->readable_ = true;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::on_data_available ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::on_data_available");

      if (this->socket_ && this->readable_)
      {
        this->evs_.template handle_data_available_event<_this_type> (this->_this ());
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::PSDD::ZMQ::socket_type
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::listen_socket ()
    {
      if (this->listening_ && !this->readable_)
      {
        return this->socket_.handle ();
      }
      return nullptr;
    }

    /// Handler method for data event strategy
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::dispatch_data_available (
          typename IDL::traits<push_consumer_data_listener_type>::ref_type dl)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::dispatch_data_available");

      try
      {
        ::CCM_PSDD::ListenerMode const lm =
            dl->listen_mode ();

        if (this->socket_ && lm != ::CCM_PSDD::ListenerMode::NOT_ENABLED)
        {
          TOPIC_SEQ_TYPE dataseq;
          if (lm == ::CCM_PSDD::ListenerMode::ONE_BY_ONE)
          {
            TOPIC_TYPE datum;
            {
              std::lock_guard<std::mutex> _g(this->lock_);

              if (this->read_i (datum, true))
                dataseq.push_back (datum);
            }

          }
          else
          {
            ::CCM_PSDD::DataCount_t const max_data =
                dl->max_data ();

            while (max_data == ::CCM_PSDD::UNLIMITED
                    || dataseq.size () < max_data)
            {
              TOPIC_TYPE datum;
              std::lock_guard<std::mutex> _g(this->lock_);

              if (!this->read_i (datum, true))
                break; // no data

              dataseq.push_back (datum);
            }

          }
          if (!dataseq.empty ())
          {
            try
            {
              dl->on_data (dataseq);
            }
            catch(const std::exception& x)
            {
              PSDD4CCM_LOG_ERROR (
                "PSDD::ZMQ::Subscriber_T<>{" <<
                topic_psdd_traits_type::get_type_name () <<
                "}::dispatch_data_available" <<
                " - on_data exception [" << x << "]");
            }
            catch(...)
            {
              PSDD4CCM_LOG_ERROR (
                "PSDD::ZMQ::Subscriber_T<>{" <<
                topic_psdd_traits_type::get_type_name () <<
                "}::dispatch_data_available" <<
                " - on_data unknown exception");
            }
          }
          else
          {
            PSDD4CCM_LOG_WARNING (
              "PSDD::ZMQ::Subscriber_T<>{" <<
              topic_psdd_traits_type::get_type_name () <<
              "}::dispatch_data_available" <<
              " - no data available");
          }
        }
      }
      catch(...)
      {
        this->readable_ = false; // reset
        throw;
      }

      this->readable_ = false; // reset
      // alert context to the fact that our socket
      // is ready for listening again
      this->service_helper_->reset_listeners ();
    }

    /**
     * CCM_PSDD Subscriber methods
     */

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscribe_any ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::subscribe_any");

      if (this->socket_)
      {
        IDL::traits<PSDataOut_Impl>::ref_type data_out_ =
            CORBA::make_reference<PSDataOut_Impl>(
                this->service_helper_->get_config ().use_message_envelope ());

        data_out_->start_message ();

        if (this->serializer_.setup_pack (data_out_)
              && data_out_->key_out ().consolidate () == 0)
        {
          this->subscribe_i (data_out_);
        }
        else
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::subscribe_any" <<
            " - failed to setup subscription");

          throw ::CCM_PSDD::InternalError (
              "Subscriber_T<>::subscribe_any",
              "PACK_ERR");
        }
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::subscribe_any" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
            "Subscriber_T<>::subscribe_any",
            "NO_CONNECTION");
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscribe (
        typename IDL::traits<TOPIC_TYPE>::in_type keyvalue)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::subscribe");

      if (this->socket_)
      {
        IDL::traits<PSDataOut_Impl>::ref_type data_out_ =
            CORBA::make_reference<PSDataOut_Impl>(
                this->service_helper_->get_config ().use_message_envelope ());

        data_out_->start_message ();

        if (this->serializer_.setup_pack (data_out_)
              && this->serializer_.pack_key (data_out_, keyvalue)
              && data_out_->key_out ().consolidate () == 0)
        {
          this->subscribe_i (data_out_);
        }
        else
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::subscribe" <<
            " - failed to setup subscription");

          throw ::CCM_PSDD::InternalError (
              "Subscriber_T<>::subscribe",
              "PACK_ERR");
        }
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::subscribe" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
            "Subscriber_T<>::subscribe",
            "NO_CONNECTION");
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::unsubscribe_any ()
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::unsubscribe_any");

      if (this->socket_)
      {
        IDL::traits<PSDataOut_Impl>::ref_type data_out_ =
            CORBA::make_reference<PSDataOut_Impl>(
                this->service_helper_->get_config ().use_message_envelope ());

        data_out_->start_message ();

        if (this->serializer_.setup_pack (data_out_)
              && data_out_->key_out ().consolidate () == 0)
        {
          this->unsubscribe_i (data_out_);
        }
        else
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::unsubscribe_any" <<
            " - failed to setup subscription");

          throw ::CCM_PSDD::InternalError (
              "Subscriber_T<>::unsubscribe_any",
              "PACK_ERR");
        }
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::unsubscribe_any" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
            "Subscriber_T<>::unsubscribe_any",
            "NO_CONNECTION");
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::unsubscribe (
        typename IDL::traits<TOPIC_TYPE>::in_type keyvalue)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::unsubscribe");

      if (this->socket_)
      {
        IDL::traits<PSDataOut_Impl>::ref_type data_out_ =
            CORBA::make_reference<PSDataOut_Impl>(
                this->service_helper_->get_config ().use_message_envelope ());

        data_out_->start_message ();

        if (this->serializer_.setup_pack (data_out_)
              && this->serializer_.pack_key (data_out_, keyvalue)
              && data_out_->key_out ().consolidate () == 0)
        {
          this->unsubscribe_i (data_out_);
        }
        else
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::unsubscribe" <<
            " - failed to setup subscription");

          throw ::CCM_PSDD::InternalError (
              "Subscriber_T<>::unsubscribe",
              "PACK_ERR");
        }
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::unsubscribe" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
            "Subscriber_T<>::unsubscribe",
            "NO_CONNECTION");
      }
    }

    /**
     * CCM_PSDD Getter methods
     */

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_one (
        typename IDL::traits<TOPIC_TYPE>::out_type datum)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::get_one");

      if (this->socket_)
      {
        std::lock_guard<std::mutex> _g(this->lock_);

        return this->read_i (datum);
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::get_one" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
            "Subscriber_T<>::get_one",
            "NO_CONNECTION");
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_many (
        typename IDL::traits<TOPIC_SEQ_TYPE>::out_type data)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::get_many");

      if (this->socket_)
      {
        std::lock_guard<std::mutex> _g(this->lock_);

        data.clear ();
        TOPIC_TYPE datum;
        bool nowait {false};
        ::CCM_PSDD::DataCount_t const max_data = this->max_data_;
        while (this->read_i (datum, nowait))
        {
          data.push_back (std::move (datum));
          if (max_data != ::CCM_PSDD::UNLIMITED
              && data.size () == max_data)
          {
            break;
          }
          // only wait for first datum; after that only get what's available
          nowait = true;
        }
        return !data.empty ();
      }
      else
      {
        PSDD4CCM_LOG_ERROR (
          "PSDD::ZMQ::Subscriber_T<>{" <<
          topic_psdd_traits_type::get_type_name () <<
          "}::get_many" <<
          " - no connection");

        throw ::CCM_PSDD::InternalError (
            "Subscriber_T<>::get_many",
            "NO_CONNECTION");
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    ::CCM_PSDD::DataCount_t
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::max_data ()
    {
      return this->max_data_;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::max_data (
        ::CCM_PSDD::DataCount_t _v)
    {
      this->max_data_ = _v;
    }

    /**
     * private methods
     */

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::subscribe_i (
        IDL::traits<PSDataOut_Impl>::ref_type data_out)
    {
      std::lock_guard<std::mutex> _g(this->lock_);

      // check if a listener has been activated
      bool was_listening {false};
      if (this->listening_)
      {
        was_listening = true;
        // disable listener temporarily
        this->listening_ = false;
        // deactivate listener
        this->service_helper_->remove_listener (this->_this ());
      }

      PSDD4CCM_LOG_DEBUG (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::subscribe_i" <<
        " - subscription key | " <<
        x11_logger::hexdump (
                     data_out->key_out ().buffer (),
                     (uint32_t)data_out->key_out ().length ()));

      this->socket_.subscribe_topic(
          data_out->key_out ().buffer (),
          data_out->key_out ().length ());

      // re-activate listener if necessary
      if (was_listening)
      {
        this->listening_ = true;
        // resume listener
        this->service_helper_->schedule_listener (this->_this ());
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    void
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::unsubscribe_i (
        IDL::traits<PSDataOut_Impl>::ref_type data_out)
    {
      std::lock_guard<std::mutex> _g(this->lock_);

      // check if a listener has been activated
      bool was_listening {false};
      if (this->listening_)
      {
        was_listening = true;
        // disable listener temporarily
        this->listening_ = false;
        // deactivate listener
        this->service_helper_->remove_listener (this->_this ());
      }

      this->socket_.unsubscribe_topic(
          data_out->key_out ().buffer (),
          data_out->key_out ().length ());

      // re-activate listener if necessary
      if (was_listening)
      {
        this->listening_ = true;
        // resume listener
        this->service_helper_->schedule_listener (this->_this ());
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    bool
    Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::read_i (
        typename IDL::traits<TOPIC_TYPE>::out_type datum,
        bool no_wait)
    {
      PSDD4CCM_LOG_DEBUG (
        "PSDD::ZMQ::Subscriber_T<>{" <<
        topic_psdd_traits_type::get_type_name () <<
        "}::read_i");

      ::zmq_msg_t key_frame;
      SafeMsg safe_key_frame;
      ::zmq_msg_t data_frame;
      SafeMsg safe_data_frame;

      if (this->socket_.receive_topic (
              &key_frame, safe_key_frame,
              &data_frame, safe_data_frame,
              no_wait))
      {
        // initialize extraction
        this->data_in_->start_message (
            &safe_key_frame,
            &safe_data_frame);

        // setup unpacking and unpack keys
        if (!this->serializer_.setup_unpack (this->data_in_)
              || !this->serializer_.unpack_key (this->data_in_, datum))
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::read_i" <<
            " - failed to unpack topic key");

          // cleanup unpacking
          this->serializer_.finalize_unpack (this->data_in_);

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Subscriber_T<>::read_i",
              "UNPACK_ERR");
        }

        // unpack any data
        if(!this->serializer_.unpack_data (this->data_in_, datum))
        {
          PSDD4CCM_LOG_ERROR (
            "PSDD::ZMQ::Subscriber_T<>{" <<
            topic_psdd_traits_type::get_type_name () <<
            "}::read_i" <<
            " - failed to unpack topic data");

          // cleanup unpacking
          this->serializer_.finalize_unpack (this->data_in_);

          throw ::CCM_PSDD::InternalError (
              "PSDD::ZMQ::Subscriber_T<>::read_i",
              "UNPACK_ERR");
        }

        // cleanup unpacking
        this->serializer_.finalize_unpack (this->data_in_);

        return true;
      }

      // no data
      return false;
    }

  };
};

#endif
