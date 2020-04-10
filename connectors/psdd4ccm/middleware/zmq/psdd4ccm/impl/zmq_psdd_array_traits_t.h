// -*- C++ -*-
/**
 * @file    zmq_psdd_array_traits_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD traits for basic IDL types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_ARRAY_PSDD4CCM_TRAITS_T_H_
#define ZMQ_ARRAY_PSDD4CCM_TRAITS_T_H_

#include "psdd4ccm/impl/zmq_psdd_basic_traits.h"

#include <array>

namespace PSDD
{
  template <const uint32_t _Dim, typename _Tp, const std::size_t _Nm>
  struct array_packing
  {
    typedef _Tp elem_type;
    typedef std::array<elem_type, _Nm> array_type;

    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& /*d*/,
        const array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const array_type& datum,
        bool /*provides_key*/)
    {
      for (const elem_type& _ve : datum)
      {
        if (!::PSDD::array_packing<
              _Dim-1,
              typename elem_type::value_type,
              std::tuple_size<elem_type>::value>::append_data (d, _ve, false))
        {
          return false;
        }
      }
      return true;
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& /*d*/,
        array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        array_type& datum,
        bool /*provides_key*/)
    {
      for (elem_type& _ve : datum)
      {
        if (!::PSDD::array_packing<
              _Dim-1,
              typename elem_type::value_type,
              std::tuple_size<elem_type>::value>::extract_data (d, _ve, false))
        {
          return false;
        }
      }
      return true;
    }
  };

  // partial specialization for base dimension
  template <typename _Tp, const std::size_t _Nm>
  struct array_packing<0U, _Tp, _Nm>
  {
    typedef _Tp elem_type;
    typedef std::array<elem_type, _Nm> array_type;

    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& /*d*/,
        const array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const array_type& datum,
        bool /*provides_key*/)
    {
      for (const elem_type& _ve : datum)
      {
        if (!::PSDD::traits<elem_type>::append_data (d, _ve, false))
          return false;
      }
      return true;
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& /*d*/,
        array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        array_type& datum,
        bool /*provides_key*/)
    {
      for (elem_type& _ve : datum)
      {
        if (!::PSDD::traits<elem_type>::extract_data (d, _ve, false))
          return false;
      }
      return true;
    }
  };

  // partial specialization for char arrays
  template <const std::size_t _Nm>
  struct array_packing<0U, char, _Nm>
  {
    typedef char elem_type;
    typedef std::array<elem_type, _Nm> array_type;

    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& /*d*/,
        const array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const array_type& datum,
        bool /*provides_key*/)
    {
      return d->data_out ().write_char_array (
                            &datum[0], _Nm);
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& /*d*/,
        array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        array_type& datum,
        bool /*provides_key*/)
    {
      return d->data_in ().read_char_array (
                            &datum[0], _Nm);
    }
  };

  // partial specialization for octet arrays
  template <const std::size_t _Nm>
  struct array_packing<0U, uint8_t, _Nm>
  {
    typedef uint8_t elem_type;
    typedef std::array<elem_type, _Nm> array_type;

    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& /*d*/,
        const array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const array_type& datum,
        bool /*provides_key*/)
    {
      return d->data_out ().write_octet_array (
                            &datum[0], _Nm);
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& /*d*/,
        array_type& /*datum*/)
    {
      // arrays can not be used as key
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        array_type& datum,
        bool /*provides_key*/)
    {
      return d->data_in ().read_octet_array (
                            &datum[0], _Nm);
    }
  };
}

#endif /* ZMQ_ARRAY_PSDD4CCM_TRAITS_T_H_ */
