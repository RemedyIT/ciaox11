// -*- C++ -*-
/**
 * @file    zmq_psdd_publisher_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD publisher template
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_PSDD_PUBLISHER_T_H
#define ZMQ_PSDD_PUBLISHER_T_H

#include "psdd4ccm/idl/ccm_psddC.h"

#include "psdd4ccm/impl/psdd/psdd_publisher_t.h"

#include "psdd4ccm/impl/zmq_psdd_baseC.h"
#include "psdd4ccm/impl/zmq_psdd_context_i.h"
#include "psdd4ccm/impl/zmq_psdd_serializer_t.h"
#include "psdd4ccm/impl/zmq_psdd_data_i.h"

#include <zmq.h>

#include <mutex>

namespace PSDD
{
  namespace ZMQ
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class Publisher_T
      : public ::PSDD::Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    {
    public:
      typedef typename CCM_TYPE::service_helper_type service_helper_type;
      typedef typename CCM_TYPE::topic_psdd_traits_type topic_psdd_traits_type;

      Publisher_T ();
      virtual ~Publisher_T ();

      void
      initialize (
          const std::string &topic_name,
          std::shared_ptr<service_helper_type> svhlp) override;

      void shutdown () override;

      /**
       * CCM_PSDD Publisher methods
       */
      void
      write_one (
          typename IDL::traits<TOPIC_TYPE>::in_type datum) override;

      void
      write_many (
          typename IDL::traits<TOPIC_SEQ_TYPE>::in_type data) override;

    private:
      void write_i (typename IDL::traits<TOPIC_TYPE>::in_type datum);

      typedef Serializer_T<CCM_TYPE, TOPIC_TYPE> serializer_type;

      serializer_type serializer_ {};
      WriterSocket socket_ {};
      std::mutex lock_;

      std::shared_ptr<service_helper_type> service_helper_ {};

      IDL::traits<PSDataOut_Impl>::ref_type data_out_ {};
    };
  };
};

#include "psdd4ccm/impl/zmq_psdd_publisher_t.cpp"

#endif /* ZMQ_PSDD_PUBLISHER_T_H */
