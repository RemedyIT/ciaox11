// -*- C++ -*-
/**
 * @file    zmq_psdd_serializer_t.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ serializer template for PSDD
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_PSDD_SERIALIZER_T_CPP_
#define ZMQ_PSDD_SERIALIZER_T_CPP_

#include "psdd4ccm/logger/psdd4ccm_log.h"

namespace PSDD
{
  namespace ZMQ
  {
    template<typename CCM_TYPE, typename TOPIC_TYPE>
    void
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::initialize (
        const std::string& topic_name,
        std::shared_ptr<service_helper_type> svhlp)
    {
      PSDD4CCM_LOG_TRACE (
        "PSDD::ZMQ::Serializer_T<>{" << topic_name << "}::initialize");

      this->std_serializer_.set_topic_name (topic_name);
      this->service_helper_ = svhlp;

      if (this->service_helper_->has_custom_serializer ())
      {
        PSDD4CCM_LOG_INFO (
          "PSDD::ZMQ::Serializer_T<>{" << topic_name << "}::initialize" <<
          " - installing custom serializer");

        this->custom_serializer_ =
            IDL::traits<custom_serializer_type>::narrow (
                this->service_helper_->get_custom_serializer ());
      }
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::setup_pack (
        IDL::traits<PSDataOut>::ref_type data)
    {
      if (this->custom_serializer_)
        return this->custom_serializer_->setup_pack (data);
      else
        return this->std_serializer_.setup_pack (data);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    void
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::finalize_pack (
        IDL::traits<PSDataOut>::ref_type data)
    {
      if (this->custom_serializer_)
        this->custom_serializer_->finalize_pack (data);
      else
        this->std_serializer_.finalize_pack (data);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::pack_key (
        IDL::traits<PSDataOut>::ref_type data,
        typename IDL::traits<TOPIC_TYPE>::in_type keyvalue)
    {
      if (this->custom_serializer_)
        return this->custom_serializer_->pack_key (data, keyvalue);
      else
        return this->std_serializer_.pack_key (data, keyvalue);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::setup_unpack (
        IDL::traits<PSDataIn>::ref_type data)
    {
      if (this->custom_serializer_)
        return this->custom_serializer_->setup_unpack (data);
      else
        return this->std_serializer_.setup_unpack (data);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    void
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::finalize_unpack (
        IDL::traits<PSDataIn>::ref_type data)
    {
      if (this->custom_serializer_)
        this->custom_serializer_->finalize_unpack (data);
      else
        this->std_serializer_.finalize_unpack (data);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::unpack_key (
        IDL::traits<PSDataIn>::ref_type data,
        typename IDL::traits<TOPIC_TYPE>::inout_type keyvalue)
    {
      if (this->custom_serializer_)
        return this->custom_serializer_->unpack_key (data, keyvalue);
      else
        return this->std_serializer_.unpack_key (data, keyvalue);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::pack_data (
        IDL::traits<PSDataOut>::ref_type data,
        typename IDL::traits<TOPIC_TYPE>::in_type datum)
    {
      if (this->custom_serializer_)
        return this->custom_serializer_->pack_data (data, datum);
      else
        return this->std_serializer_.pack_data (data, datum);
    }

    template <typename CCM_TYPE, typename TOPIC_TYPE>
    bool
    Serializer_T<CCM_TYPE, TOPIC_TYPE>::unpack_data (
        IDL::traits<PSDataIn>::ref_type data,
        typename IDL::traits<TOPIC_TYPE>::inout_type datum)
    {
      if (this->custom_serializer_)
        return this->custom_serializer_->unpack_data (data, datum);
      else
        return this->std_serializer_.unpack_data (data, datum);
    }
  }
}

#endif /* ZMQ_PSDD_SERIALIZER_T_CPP_ */
