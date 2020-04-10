// -*- C++ -*-
/**
 * @file    zmq_psdd_standard_serializer_t.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ Standard Serializer template for PSDD
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_STANDARD_SERIALIZER_T_CPP_
#define ZMQ_PSDD_STANDARD_SERIALIZER_T_CPP_

#include "zmq_psdd_traits.h"
#include "ace/Truncate.h"

namespace PSDD
{
  namespace ZMQ
  {
    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::setup_pack (
        IDL::traits<PSDataOut>::ref_type& data)
    {
      // Use little endian byte order for standard serialization
      data->set_byte_order (EByteOrder::eLittleEndian);

      // each key starts with topic name
      // do not write string size since we always now that
      // and should always match
      return data->key_out ().write_char_array (
          this->topic_name_.c_str (),
          ACE_Utils::truncate_cast<ACE_CDR::ULong> (this->topic_name_.size ()));
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::pack_key (
        IDL::traits<PSDataOut>::ref_type& data,
        typename IDL::traits<TOPIC_TYPE>::in_type keyvalue)
    {
      // no key for this topic or append key data
      return typename topic_psdd_traits_type::no_key ()
        || topic_psdd_traits_type::append_key (
            data,
            keyvalue);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::pack_data (
        IDL::traits<PSDataOut>::ref_type& data,
        typename IDL::traits<TOPIC_TYPE>::in_type datum)
    {
      // key only for this topic or append non-key data (all if no key)
      return typename topic_psdd_traits_type::key_only ()
        || topic_psdd_traits_type::append_data (
            data,
            datum,
            !typename topic_psdd_traits_type::no_key ());
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    void
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::finalize_pack (
        IDL::traits<PSDataOut>::ref_type&)
    {
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::setup_unpack (
        IDL::traits<PSDataIn>::ref_type& data)
    {
      // Use little endian byte order for standard serialization
      data->set_byte_order (EByteOrder::eLittleEndian);

      // each key starts with topic name
      // do not read size from key frame, only string data
      // size is known to be same as topic name (if valid)
      std::string topic;
      topic.resize (this->topic_name_.size ());
      return data->key_in ().read_char_array(
          std::addressof(topic[0]),
          ACE_Utils::truncate_cast<ACE_CDR::ULong> (this->topic_name_.size ()))
        && topic == this->topic_name_;
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::unpack_key (
        IDL::traits<PSDataIn>::ref_type& data,
        typename IDL::traits<TOPIC_TYPE>::inout_type keyvalue)
    {
      // no key for this topic or extract key data
      return typename topic_psdd_traits_type::no_key ()
        || topic_psdd_traits_type::extract_key (
            data,
            keyvalue);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::unpack_data (
        IDL::traits<PSDataIn>::ref_type& data,
        typename IDL::traits<TOPIC_TYPE>::inout_type datum)
    {
      // key only for this topic or extract non-key data (all if no key)
      return typename topic_psdd_traits_type::key_only ()
        || topic_psdd_traits_type::extract_data (
            data,
            datum,
            !typename topic_psdd_traits_type::no_key ());
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    void
    StandardSerializer_T<CCM_TYPE, TOPIC_TYPE>::finalize_unpack (
        IDL::traits<PSDataIn>::ref_type&)
    {
    }
  }
}

#endif /* ZMQ_PSDD_STANDARD_SERIALIZER_T_CPP_ */
