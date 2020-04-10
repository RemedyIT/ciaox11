// -*- C++ -*-
/**
 * @file    zmq_psdd_traits_base_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD traits for basic IDL types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD4CCM_TRAITS_BASE_T_H_
#define ZMQ_PSDD4CCM_TRAITS_BASE_T_H_

#include <string>
#include "psdd4ccm/impl/zmq_psdd_data.h"

#include "ace/CDR_Base.h"

namespace PSDD
{
  template <typename DATA_TYPE>
  struct basic_pack_append
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const DATA_TYPE& datum)
    {
      return (d->key_out () << datum);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const DATA_TYPE& datum,
        bool /*provides_key*/)
    {
      return (d->data_out () << datum);
    }
  };

  template <typename DATA_TYPE>
  struct basic_pack_extract
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        DATA_TYPE& datum)
    {
      return (d->key_in () >> datum);
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        DATA_TYPE& datum,
        bool /*provides_key*/)
    {
      return (d->data_in () >> datum);
    }
  };

  template <typename DATA_TYPE>
  struct basic_packing
  : public basic_pack_append<DATA_TYPE>
  , public basic_pack_extract<DATA_TYPE>
  {
  };

  template <>
  struct basic_pack_append<bool>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const bool& datum)
    {
      uint8_t const b = datum ? 1 : 0;
      return (d->key_out ().write_octet (b));
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const bool& datum,
        bool /*provides_key*/)
    {
      uint8_t const b = datum ? 1 : 0;
      return (d->data_out ().write_octet (b));
    }
  };

  template <>
  struct basic_pack_extract<bool>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        bool& datum)
    {
      uint8_t b;
      if (d->key_in ().read_octet (b))
      {
        datum = (b == 1);
        return true;
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        bool& datum,
        bool /*provides_key*/)
    {
      uint8_t b;
      if (d->data_in ().read_octet (b))
      {
        datum = (b == 1);
        return true;
      }
      return false;
    }
  };

  template <>
  struct basic_packing<bool>
  : public basic_pack_append<bool>
  , public basic_pack_extract<bool>
  {
  };

  template <>
  struct basic_pack_append<char>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const char& datum)
    {
      return (d->key_out ().write_char (datum));
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const char& datum,
        bool /*provides_key*/)
    {
      return (d->data_out ().write_char (datum));
    }
  };

  template <>
  struct basic_pack_extract<char>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        char& datum)
    {
      return d->key_in ().read_char (datum);
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        char& datum,
        bool /*provides_key*/)
    {
      return d->data_in ().read_char (datum);
    }
  };

  template <>
  struct basic_packing<char>
  : public basic_pack_append<char>
  , public basic_pack_extract<char>
  {
  };

  template <>
  struct basic_pack_append<uint8_t>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const uint8_t& datum)
    {
      return (d->key_out ().write_octet (datum));
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const uint8_t& datum,
        bool /*provides_key*/)
    {
      return (d->data_out ().write_octet (datum));
    }
  };

  template <>
  struct basic_pack_extract<uint8_t>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        uint8_t& datum)
    {
      return d->key_in ().read_octet (datum);
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        uint8_t& datum,
        bool /*provides_key*/)
    {
      return d->data_in ().read_octet (datum);
    }
  };

  template <>
  struct basic_packing<uint8_t>
  : public basic_pack_append<uint8_t>
  , public basic_pack_extract<uint8_t>
  {
  };

  // template methods for multi-byte swaps
  template<const size_t SIZE>
  bool swap (char const*, char*)
  { return false; }
  template<>
  bool swap<2> (char const* src, char* tgt)
  { ACE_CDR::swap_2 (src, tgt); return true; }
  template<>
  bool swap<4> (char const* src, char* tgt)
  { ACE_CDR::swap_4 (src, tgt); return true; }
  template<>
  bool swap<8> (char const* src, char* tgt)
  { ACE_CDR::swap_8 (src, tgt); return true; }
  template<>
  bool swap<16> (char const* src, char* tgt)
  { ACE_CDR::swap_16 (src, tgt); return true; }

  // multibyte packing
  template <typename DATA_TYPE>
  struct basic_pack_append_mb
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const DATA_TYPE& datum)
    {
      // make sure to swap on write if needed
      // AXCIOMA is CORBA compliant so uses
      // swap on read in CDR streams
      if (d->key_out ().do_byte_swap ())
      {
        DATA_TYPE swapped;
        return swap<sizeof (DATA_TYPE)> (
                  reinterpret_cast<const char*> (std::addressof(datum)),
                  reinterpret_cast<char*> (std::addressof(swapped)))
            && (d->key_out () << swapped);
      }
      return (d->key_out () << datum);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const DATA_TYPE& datum,
        bool /*provides_key*/)
    {
      // make sure to swap on write if needed
      // AXCIOMA is CORBA compliant so uses
      // swap on read in CDR streams
      if (d->data_out ().do_byte_swap ())
      {
        DATA_TYPE swapped;
        return swap<sizeof (DATA_TYPE)> (
                  reinterpret_cast<const char*> (std::addressof(datum)),
                  reinterpret_cast<char*> (std::addressof(swapped)))
            && (d->data_out () << swapped);
      }
      return (d->data_out () << datum);
    }
  };

  template <>
  struct basic_packing<uint16_t>
  : public basic_pack_append_mb<uint16_t>
  , public basic_pack_extract<uint16_t>
  {
  };

  template <>
  struct basic_packing<int16_t>
  : public basic_pack_append_mb<int16_t>
  , public basic_pack_extract<int16_t>
  {
  };

  template <>
  struct basic_packing<uint32_t>
  : public basic_pack_append_mb<uint32_t>
  , public basic_pack_extract<uint32_t>
  {
  };

  template <>
  struct basic_packing<int32_t>
  : public basic_pack_append_mb<int32_t>
  , public basic_pack_extract<int32_t>
  {
  };

  template <>
  struct basic_packing<float>
  : public basic_pack_append_mb<float>
  , public basic_pack_extract<float>
  {
  };

  template <>
  struct basic_packing<uint64_t>
  : public basic_pack_append_mb<uint64_t>
  , public basic_pack_extract<uint64_t>
  {
  };

  template <>
  struct basic_packing<int64_t>
  : public basic_pack_append_mb<int64_t>
  , public basic_pack_extract<int64_t>
  {
  };

  template <>
  struct basic_packing<double>
  : public basic_pack_append_mb<double>
  , public basic_pack_extract<double>
  {
  };

#if (ACE_SIZEOF_LONG_DOUBLE != 16)
  // template specialization for abstracted long double
  template <>
  struct basic_pack_append_mb<long double>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const long double& datum)
    {
      ACE_CDR::LongDouble ld;
      ld.assign (datum);
      char* buf {};
      if (d->key_out ().adjust (ACE_CDR::LONGDOUBLE_SIZE,
                                ACE_CDR::LONGDOUBLE_ALIGN,
                                buf) == 0)
      {
        // make sure to swap on write if needed
        // AXCIOMA is CORBA compliant so uses
        // swap on read in CDR streams
        if (d->key_out ().do_byte_swap ())
        {
          return swap<16> (reinterpret_cast<const char*> (&ld), buf);
        }
        else
        {
          *reinterpret_cast<ACE_CDR::LongDouble *> (buf) = ld;
          return true;
        }
      }
      return false;
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const long double& datum,
        bool /*provides_key*/)
    {
      ACE_CDR::LongDouble ld;
      ld.assign (datum);
      char* buf {};
      if (d->data_out ().adjust (ACE_CDR::LONGDOUBLE_SIZE,
                                    ACE_CDR::LONGDOUBLE_ALIGN,
                                    buf) == 0)
      {
        // make sure to swap on write if needed
        // AXCIOMA is CORBA compliant so uses
        // swap on read in CDR streams
        if (d->data_out ().do_byte_swap ())
        {
          return swap<16> (reinterpret_cast<const char*> (&ld), buf);
        }
        else
        {
          *reinterpret_cast<ACE_CDR::LongDouble *> (buf) = ld;
          return true;
        }
      }
      return false;
    }
  };

  // template specialization for abstracted long double
  template <>
  struct basic_pack_extract<long double>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        long double& datum)
    {
      ACE_CDR::LongDouble ld;
      if (d->key_in () >> ld)
      {
        datum = ld;
        return true;
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        long double& datum,
        bool /*provides_key*/)
    {
      ACE_CDR::LongDouble ld;
      if (d->data_in () >> ld)
      {
        datum = ld;
        return true;
      }
      return false;
    }
  };

#endif

  template <>
  struct basic_packing<long double>
  : public basic_pack_append_mb<long double>
  , public basic_pack_extract<long double>
  {
  };

  template <const size_t SIZE>
  struct basic_pack_append_wc
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type&,
        const wchar_t&)
    { return false; }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type&,
        const wchar_t&,
        bool /*provides_key*/)
    { return false; }
  };

  template <>
  struct basic_pack_append_wc<2>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum)
    {
      uint16_t temp = static_cast<uint16_t> (datum);
      return basic_packing<uint16_t>::append_key (d, temp);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum,
        bool /*provides_key*/)
    {
      uint16_t temp = static_cast<uint16_t> (datum);
      return basic_packing<uint16_t>::append_data (d, temp, false);
    }
  };

  template <>
  struct basic_pack_append_wc<4>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum)
    {
      uint32_t temp = static_cast<uint32_t> (datum);
      return basic_packing<uint32_t>::append_key (d, temp);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum,
        bool /*provides_key*/)
    {
      uint32_t temp = static_cast<uint32_t> (datum);
      return basic_packing<uint32_t>::append_data (d, temp, false);
    }
  };

  template <>
  struct basic_pack_append_wc<8>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum)
    {
      uint64_t temp = static_cast<uint64_t> (datum);
      return basic_packing<uint64_t>::append_key (d, temp);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum,
        bool /*provides_key*/)
    {
      uint64_t temp = static_cast<uint64_t> (datum);
      return basic_packing<uint64_t>::append_data (d, temp, false);
    }
  };

  template <>
  struct basic_pack_append_wc<16>
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum)
    {
      long double temp = static_cast<long double> (datum);
      return basic_packing<long double>::append_key (d, temp);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const wchar_t& datum,
        bool /*provides_key*/)
    {
      long double temp = static_cast<long double> (datum);
      return basic_packing<long double>::append_data (d, temp, false);
    }
  };

  template <const size_t SIZE>
  struct basic_pack_extract_wc
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type&,
        wchar_t&)
    { return false; }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type&,
        wchar_t&,
        bool /*provides_key*/)
    { return false; }
  };

  template <>
  struct basic_pack_extract_wc<2>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum)
    {
      uint16_t temp;
      if (basic_packing<uint16_t>::extract_key (d, temp))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum,
        bool /*provides_key*/)
    {
      uint16_t temp;
      if (basic_packing<uint16_t>::extract_data (d, temp, false))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }
  };

  template <>
  struct basic_pack_extract_wc<4>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum)
    {
      uint32_t temp;
      if (basic_packing<uint32_t>::extract_key (d, temp))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum,
        bool /*provides_key*/)
    {
      uint32_t temp;
      if (basic_packing<uint32_t>::extract_data (d, temp, false))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }
  };

  template <>
  struct basic_pack_extract_wc<8>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum)
    {
      uint64_t temp;
      if (basic_packing<uint64_t>::extract_key (d, temp))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum,
        bool /*provides_key*/)
    {
      uint64_t temp;
      if (basic_packing<uint64_t>::extract_data (d, temp, false))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }
  };

  template <>
  struct basic_pack_extract_wc<16>
  {
    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum)
    {
      long double temp;
      if (basic_packing<long double>::extract_key (d, temp))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        wchar_t& datum,
        bool /*provides_key*/)
    {
      long double temp;
      if (basic_packing<long double>::extract_data (d, temp, false))
      {
        datum = static_cast<wchar_t> (temp);
        return true;
      }
      return false;
    }
  };

  template <>
  struct basic_packing<wchar_t>
  : public basic_pack_append_wc<sizeof (wchar_t)>
  , public basic_pack_extract_wc<sizeof (wchar_t)>
  {
  };
}

#endif /* ZMQ_PSDD4CCM_TRAITS_BASE_T_H_ */
