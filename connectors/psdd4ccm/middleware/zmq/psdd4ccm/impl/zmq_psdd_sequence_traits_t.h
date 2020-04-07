// -*- C++ -*-
/**
 * @file    zmq_psdd_sequence_traits_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD traits for basic IDL types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef ZMQ_SEQUENCE_PSDD4CCM_TRAITS_T_H_
#define ZMQ_SEQUENCE_PSDD4CCM_TRAITS_T_H_

#include "psdd4ccm/impl/zmq_psdd_basic_traits.h"

#include <vector>

namespace PSDD
{
  template <typename ELEM_TYPE, const uint32_t BOUND = 0>
  struct sequence_packing
  {
    typedef ELEM_TYPE elem_type;
    typedef std::vector<ELEM_TYPE> seq_type;

    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& /*d*/,
        const seq_type& /*datum*/)
    {
      // sequences cannot be used as key
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const seq_type& datum,
        bool /*provides_key*/)
    {
      uint32_t const l = (uint32_t)datum.size ();
      if (BOUND > 0 && BOUND < l)
        return false;
      if (!::PSDD::traits<uint32_t>::append_data (d, l, false))
        return false;
      for (const elem_type& _v : datum)
      {
        if (!::PSDD::traits<elem_type>::append_data (d, _v, false))
          return false;
      }
      return true;
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& /*d*/,
        seq_type& /*datum*/)
    {
      // sequences cannot be used as key
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        seq_type& datum,
        bool /*provides_key*/)
    {
      uint32_t vl;
      if (!::PSDD::traits<uint32_t>::extract_data (d, vl, false))
        return false;
      datum.resize (vl);
      for (uint32_t n=0; n<vl ;++n)
      {
        if (!::PSDD::traits<elem_type>::extract_data (d, datum[n], false))
          return false;
      }
      return true;
    }
  };

  // partial specialization for char sequences
  template <const uint32_t BOUND>
  struct sequence_packing<char, BOUND>
  {
    typedef char elem_type;
    typedef std::vector<elem_type> seq_type;

    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type&,
        const seq_type&)
    {
      // sequences cannot be used as key
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const seq_type& datum,
        bool /*provides_key*/)
    {
      uint32_t const l = (uint32_t)datum.size ();
      if (BOUND > 0 && BOUND < l)
        return false;
      if (!::PSDD::traits<uint32_t>::append_data (d, l, false))
        return false;
      return d->data_out ().write_char_array (
                              &datum[0], l);
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type&,
        seq_type&)
    {
      // sequences cannot be used as key
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        seq_type& datum,
        bool /*provides_key*/)
    {
      uint32_t vl;
      if (!::PSDD::traits<uint32_t>::extract_data (d, vl, false))
        return false;
      datum.resize (vl);
      return d->data_in ().read_char_array (
                             &datum[0], vl);
    }
  };

  // partial specialization for octet sequences
  template <const uint32_t BOUND>
  struct sequence_packing<uint8_t, BOUND>
  {
    typedef uint8_t elem_type;
    typedef std::vector<elem_type> seq_type;

    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type&,
        const seq_type&)
    {
      // sequences cannot be used as key
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const seq_type& datum,
        bool /*provides_key*/)
    {
      uint32_t const l = (uint32_t)datum.size ();
      if (BOUND > 0 && BOUND < l)
        return false;
      if (!::PSDD::traits<uint32_t>::append_data (d, l, false))
        return false;
      return d->data_out ().write_octet_array (
                              &datum[0], l);
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type&,
        seq_type&)
    {
      // sequences cannot be used as key
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        seq_type& datum,
        bool /*provides_key*/)
    {
      uint32_t vl;
      if (!::PSDD::traits<uint32_t>::extract_data (d, vl, false))
        return false;
      datum.resize (vl);
      return d->data_in ().read_octet_array (
                             &datum[0], vl);
    }
  };
}

#endif /* ZMQ_SEQUENCE_PSDD4CCM_TRAITS_T_H_ */
