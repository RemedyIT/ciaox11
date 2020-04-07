// -*- C++ -*-
/**
 * @file    zmq_psdd_serializer_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ serializer template for PSDD
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_PSDD_SERIALIZER_T_H_
#define ZMQ_PSDD_SERIALIZER_T_H_

#include "psdd4ccm/impl/zmq_psdd_data.h"
#include "psdd4ccm/impl/zmq_psdd_standard_serializer_t.h"

namespace PSDD
{
  namespace ZMQ
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE>
    class Serializer_T
    {
    public:
      Serializer_T () = default;
      ~Serializer_T () = default;

      typedef typename CCM_TYPE::service_helper_type service_helper_type;
      typedef typename CCM_TYPE::custom_serializer_type custom_serializer_type;

      void initialize (const std::string& topic_name,
                       std::shared_ptr<service_helper_type> svhlp);

      bool setup_pack (IDL::traits<PSDataOut>::ref_type data);
      bool pack_key (IDL::traits<PSDataOut>::ref_type data,
                     typename IDL::traits<TOPIC_TYPE>::in_type keyvalue);
      bool pack_data (IDL::traits<PSDataOut>::ref_type data,
                      typename IDL::traits<TOPIC_TYPE>::in_type datum);
      void finalize_pack (IDL::traits<PSDataOut>::ref_type data);

      bool setup_unpack (IDL::traits<PSDataIn>::ref_type data);
      bool unpack_key (IDL::traits<PSDataIn>::ref_type data,
                       typename IDL::traits<TOPIC_TYPE>::inout_type keyvalue);
      bool unpack_data (IDL::traits<PSDataIn>::ref_type data,
                        typename IDL::traits<TOPIC_TYPE>::inout_type datum);
      void finalize_unpack (IDL::traits<PSDataIn>::ref_type data);

    private:
      std::shared_ptr<service_helper_type> service_helper_ {};
      StandardSerializer_T<CCM_TYPE, TOPIC_TYPE> std_serializer_ {};
      typename IDL::traits<custom_serializer_type>::ref_type custom_serializer_ {};
    };
  }
}

#include "psdd4ccm/impl/zmq_psdd_serializer_t.cpp"

#endif /* ZMQ_PSDD_SERIALIZER_T_H_ */
