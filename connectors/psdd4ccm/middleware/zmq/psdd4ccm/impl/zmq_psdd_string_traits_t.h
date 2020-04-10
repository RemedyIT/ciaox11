// -*- C++ -*-
/**
 * @file    zmq_psdd_string_traits_t.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD traits for basic IDL types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD4CCM_STRING_TRAITS_T_H_
#define ZMQ_PSDD4CCM_STRING_TRAITS_T_H_

#include "psdd4ccm/impl/zmq_psdd_basic_traits.h"
#include "ace/Truncate.h"

namespace PSDD
{
  template <const uint32_t BOUND = 0>
  struct string_packing
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const std::string& datum)
    {
      // get string size
      uint32_t const l = (uint32_t)datum.size ();
      // check bound (if any)
      if (BOUND > 0 && BOUND < l)
        return false;
      // write size to data frame and string data to key frame
      return ::PSDD::traits<uint32_t>::append_data (d, l, false)
          && d->key_out ().write_char_array (datum.c_str (), l);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const std::string& datum,
        bool /*provides_key*/)
    {
      // get string size
      uint32_t const l = (uint32_t)datum.size ();
      // check bound (if any)
      if (BOUND > 0 && BOUND < l)
        return false;
      // write size followed by string data to data frame
      return ::PSDD::traits<uint32_t>::append_data (d, l, false)
          && d->data_out ().write_char_array (datum.c_str (), l);
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        std::string& datum)
    {
      uint32_t l;
      if (::PSDD::traits<uint32_t>::extract_data (d, l, false))
      {
        // reserve space
        datum.resize (l);
        // read string data from key frame
        return d->key_in ().read_char_array(std::addressof(datum[0]), l);
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        std::string& datum,
        bool /*provides_key*/)
    {
      // read string size from data frame
      uint32_t l;
      if (::PSDD::traits<uint32_t>::extract_data (d, l, false))
      {
        // reserve space
        datum.resize (l);
        // read string data from data frame
        return d->data_in ().read_char_array(std::addressof(datum[0]), l);
      }
      return false;
    }
  };

  // template methods for swap_array to forego the need
  // for a switch statement
  template<const size_t SIZE>
  bool swap_array (char const*, char*, size_t)
  { return false; }
  template<>
  bool swap_array<2> (char const* src, char* tgt, size_t len)
  { ACE_CDR::swap_2_array (src, tgt, len); return true; }
  template<>
  bool swap_array<4> (char const* src, char* tgt, size_t len)
  { ACE_CDR::swap_4_array (src, tgt, len); return true; }
  template<>
  bool swap_array<8> (char const* src, char* tgt, size_t len)
  { ACE_CDR::swap_8_array (src, tgt, len); return true; }
  template<>
  bool swap_array<16> (char const* src, char* tgt, size_t len)
  { ACE_CDR::swap_16_array (src, tgt, len); return true; }


  // local helper method copying some of the
  // ACE_OutputCDR::write_array code to help
  // with encoding here
  inline bool write_wchar_array_i(
      ACE_OutputCDR& os,
      const wchar_t* x,
      uint32_t length)
  {
    if (length == 0)
      return true;
    // make sure to swap on write if needed
    // AXCIOMA is CORBA compliant so uses
    // swap on read in CDR streams
    if (os.do_byte_swap ())
    {
      size_t const align = sizeof (wchar_t) == 2
          ? ACE_CDR::SHORT_ALIGN
          : ACE_CDR::LONG_ALIGN;
      char *buf {};
      if (os.adjust (sizeof(wchar_t) * length, align, buf) == 0)
      {
        const char *source = reinterpret_cast<const char *> (x);
        return swap_array<sizeof(wchar_t)> (source, buf, length);
      }
      return false;
    }
    else
    {
      const char *source = reinterpret_cast<const char *> (x);
      return os.write_char_array (source, length * sizeof(wchar_t));
    }
  }

  // local helper method copying some of the
  // ACE_OutputCDR::write_array code to help
  // with encoding here
  inline bool read_wchar_array_i(
      ACE_InputCDR& is,
      wchar_t* x,
      uint32_t length)
  {
    if (length == 0)
      return true;
    // make sure to swap on read if needed
    // AXCIOMA is CORBA compliant so uses
    // swap on read in CDR streams
    if (is.do_byte_swap ())
    {
      size_t const align = sizeof (wchar_t) == 2
          ? ACE_CDR::SHORT_ALIGN
          : ACE_CDR::LONG_ALIGN;
      char *buf {};
      if (is.adjust (sizeof(wchar_t) * length, align, buf) == 0)
      {
        char *target = reinterpret_cast<char*> (x);
        return swap_array<sizeof(wchar_t)> (buf, target, length);
      }
      return false;
    }
    else
    {
      char *target = reinterpret_cast<char*> (x);
      return is.read_char_array (target, length * sizeof(wchar_t));
    }
  }

  template <const uint32_t BOUND = 0>
  struct wstring_packing
  {
    static
    bool append_key (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const std::wstring& datum)
    {
      // get string size
      uint32_t const l = (uint32_t)datum.size ();
      // check bound (if any)
      if (BOUND > 0 && BOUND < l)
        return false;
#if !defined(NDEBUG)
      PSDD4CCM_LOG_DEBUG (
        "PSDD::traits<wstring>::append_key" <<
        " | "  <<
        x11_logger::hexdump (reinterpret_cast<const char*> (std::addressof(datum[0])), (uint32_t)l * sizeof(wchar_t)));
#endif
      // write size to data frame and string data to key frame
      return ::PSDD::traits<uint32_t>::append_data (d, l, false)
          && write_wchar_array_i (d->key_out (), datum.c_str (), l);
    }

    static
    bool append_data (
        IDL::traits<ZMQ::PSDataOut>::ref_type& d,
        const std::wstring& datum,
        bool /*provides_key*/)
    {
      // get string size
      uint32_t const l = (uint32_t)datum.size ();
      // check bound (if any)
      if (BOUND > 0 && BOUND < datum.size ())
        return false;
#if !defined(NDEBUG)
      PSDD4CCM_LOG_DEBUG (
        "PSDD::traits<wstring>::append_data" <<
        " | "  <<
        x11_logger::hexdump (reinterpret_cast<const char*> (std::addressof(datum[0])), (uint32_t)l * sizeof(wchar_t)));
#endif
      // write size followed by string data to data frame
      return ::PSDD::traits<uint32_t>::append_data (d, l, false)
          && write_wchar_array_i (d->data_out (), datum.c_str (), l);
    }

    static
    bool extract_key (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        std::wstring& datum)
    {
      uint32_t l;
      if (::PSDD::traits<uint32_t>::extract_data (d, l, false))
      {
        // reserve space
        datum.resize (l);
        // read string data from key frame
        if (read_wchar_array_i (d->key_in (), std::addressof(datum[0]), l))
        {
#if !defined(NDEBUG)
          PSDD4CCM_LOG_DEBUG (
            "PSDD::traits<wstring>::extract_key" <<
            " | "  <<
            x11_logger::hexdump (
                reinterpret_cast<const char*> (std::addressof(datum[0])),
                ACE_Utils::truncate_cast<uint32_t> (datum.size () * sizeof(wchar_t))));
#endif
          return true;
        }
      }
      return false;
    }

    static
    bool extract_data (
        IDL::traits<ZMQ::PSDataIn>::ref_type& d,
        std::wstring& datum,
        bool /*provides_key*/)
    {
      // read string size from data frame
      uint32_t l;
      if (::PSDD::traits<uint32_t>::extract_data (d, l, false))
      {
        // reserve space
        datum.resize (l);
        // read string data from data frame
        if (read_wchar_array_i (d->data_in (), std::addressof(datum[0]), l))
        {
#if !defined(NDEBUG)
          PSDD4CCM_LOG_DEBUG (
            "PSDD::traits<wstring>::extract_data" <<
            " | "  <<
            x11_logger::hexdump (
                reinterpret_cast<const char*> (std::addressof(datum[0])),
                ACE_Utils::truncate_cast<uint32_t> (datum.size () * sizeof(wchar_t))));
#endif
          return true;
        }
      }
      return false;
    }
  };

  template <>
  struct traits <std::string>
    : public common_traits<std::string>
    , public string_packing<>
  {
    static
    std::string get_type_name () { return "string"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <std::wstring>
    : public common_traits<std::wstring>
    , public wstring_packing<>
  {
    static
    std::string get_type_name () { return "wstring"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };
}

#endif /* ZMQ_PSDD4CCM_STRING_TRAITS_T_H_ */
