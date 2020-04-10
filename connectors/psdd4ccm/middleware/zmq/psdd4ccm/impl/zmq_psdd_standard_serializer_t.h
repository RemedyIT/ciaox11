// -*- C++ -*-
/**
 * @file    zmq_psdd_standard_serializer_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ Standard Serializer template for PSDD
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_STANDARD_SERIALIZER_T_H_
#define ZMQ_PSDD_STANDARD_SERIALIZER_T_H_

#include "psdd4ccm/impl/zmq_psdd_data.h"

namespace PSDD
{
  namespace ZMQ
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE>
    class StandardSerializer_T
    {
    public:
      StandardSerializer_T () = default;
      ~StandardSerializer_T () = default;

      typedef typename CCM_TYPE::topic_psdd_traits_type topic_psdd_traits_type;

      void set_topic_name (const std::string& topic_name)
      { this->topic_name_ = topic_name; }

      bool setup_pack (IDL::traits<PSDataOut>::ref_type& data);
      bool pack_key (IDL::traits<PSDataOut>::ref_type& data,
                    typename IDL::traits<TOPIC_TYPE>::in_type keyvalue);
      bool pack_data (IDL::traits<PSDataOut>::ref_type& data,
                     typename IDL::traits<TOPIC_TYPE>::in_type datum);
      void finalize_pack (IDL::traits<PSDataOut>::ref_type& data);

      bool setup_unpack (IDL::traits<PSDataIn>::ref_type& data);
      bool unpack_key (IDL::traits<PSDataIn>::ref_type& data,
                      typename IDL::traits<TOPIC_TYPE>::inout_type keyvalue);
      bool unpack_data (IDL::traits<PSDataIn>::ref_type& data,
                       typename IDL::traits<TOPIC_TYPE>::inout_type datum);
      void finalize_unpack (IDL::traits<PSDataIn>::ref_type& data);

    private:
      std::string topic_name_;
    };
  }
}

#include "psdd4ccm/impl/zmq_psdd_standard_serializer_t.cpp"

#endif /* ZMQ_PSDD_STANDARD_SERIALIZER_T_H_ */
