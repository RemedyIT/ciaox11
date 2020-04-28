// -*- C++ -*-
/**
 * @file    zmq_psdd_subscriber_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD subscriber template
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_SUBSCRIBER_T_H
#define ZMQ_PSDD_SUBSCRIBER_T_H

#include "psdd4ccm/idl/ccm_psddC.h"

#include "psdd4ccm/impl/psdd/psdd_subscriber_t.h"

#include "psdd4ccm/impl/zmq_psdd_listenerC.h"
#include "psdd4ccm/impl/zmq_psdd_context_i.h"
#include "psdd4ccm/impl/zmq_psdd_sockets.h"
#include "psdd4ccm/impl/zmq_psdd_serializer_t.h"
#include "psdd4ccm/impl/zmq_psdd_data_i.h"

#include <atomic>
#include <mutex>

#include <zmq.h>
#include "zmq_psdd_service_helper.h"

namespace PSDD
{
  namespace ZMQ
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class Subscriber_T
      : public ::PSDD::Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
      , public CCM_TYPE::consumer_traits::data_type
      , public ::PSDD::ZMQ::Listener
    {
    public:
      typedef Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> _this_type;
      typedef CORBA::object_traits<_this_type>  _traits_type;
      typedef typename _traits_type::ref_type _ref_type;

      typedef typename CCM_TYPE::event_strategy_type event_strategy_type;
      typedef typename CCM_TYPE::consumer_traits::data_type pull_consumer_data_type;
      typedef typename CCM_TYPE::consumer_traits::data_listener_type push_consumer_data_listener_type;
      typedef typename CCM_TYPE::service_helper_type service_helper_type;
      typedef typename CCM_TYPE::topic_psdd_traits_type topic_psdd_traits_type;

      Subscriber_T ();
      virtual ~Subscriber_T ();

      // override because inherited multiple times
      bool
      _is_a (const std::string& local_type_id) override;

      // overload because inherited multiple times
      _ref_type
      _this ();

      void
      initialize (
          const std::string &topic_name,
          std::shared_ptr<service_helper_type> svhlp) override;

      void
      shutdown () override;

      typename IDL::traits<typename Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::pull_consumer_data_type>::ref_type
      get_pull_consumer_data () override;

      void
      activate_push_consumer_data_listener (const event_strategy_type&) override;

      /// Handler method for data event strategy
      void
      dispatch_data_available (
          typename IDL::traits<push_consumer_data_listener_type>::ref_type dl) override;

      /**
       * ZQM PSDD Listener methods
       */
      void
      mark_readable () override;

      void
      on_data_available () override;

      ::PSDD::ZMQ::socket_type
       listen_socket () override;

      /**
       * CCM_PSDD Subscriber methods
       */

      /// @copydoc helloPS.idl::Test::Hello::Subscriber::subscribe_any
      void
      subscribe_any () override;

      /// @copydoc helloPS.idl::Test::Hello::Subscriber::subscribe
      void
      subscribe (
          typename IDL::traits<TOPIC_TYPE>::in_type keyvalue) override;

      /// @copydoc helloPS.idl::Test::Hello::Subscriber::unsubscribe_any
      void
      unsubscribe_any () override;

      /// @copydoc helloPS.idl::Test::Hello::Subscriber::unsubscribe
      void
      unsubscribe (
          typename IDL::traits<TOPIC_TYPE>::in_type keyvalue) override;

      /**
       * CCM_PSDD Getter methods
       */

      bool
      get_one (
          typename IDL::traits<TOPIC_TYPE>::out_type datum) override;

      bool
      get_many (
          typename IDL::traits<TOPIC_SEQ_TYPE>::out_type data) override;

      ::CCM_PSDD::DataCount_t
      max_data () override;

      void
      max_data (
          ::CCM_PSDD::DataCount_t _v) override;

    private:
      void subscribe_i (IDL::traits<PSDataOut_Impl>::ref_type);
      void unsubscribe_i (IDL::traits<PSDataOut_Impl>::ref_type);

      bool read_i (
          typename IDL::traits<TOPIC_TYPE>::out_type datum,
          bool no_wait = false);

      typedef Serializer_T<CCM_TYPE, TOPIC_TYPE> serializer_type;

      std::string topic_name_ {};
      serializer_type serializer_ {};
      ::PSDD::ZMQ::SubscriberSocket socket_ {};
      std::atomic_bool readable_ {false};
      std::atomic_bool listening_ {false};
      event_strategy_type evs_;
      std::mutex lock_;

      std::shared_ptr<ServiceHelper> service_helper_ {};

      std::atomic<::CCM_PSDD::DataCount_t> max_data_ {::CCM_PSDD::UNLIMITED};

      IDL::traits<PSDataIn_Impl>::ref_type data_in_ {};
    };
  };
};

#include "psdd4ccm/impl/zmq_psdd_subscriber_t.cpp"

#endif
