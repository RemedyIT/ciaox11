// -*- C++ -*-
/**
 * @file    zmq_psdd_basic_traits.h
 * @author  Martin Corino
 *
 * @brief   ZMQ PSDD traits for basic IDL types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD4CCM_BASIC_TRAITS_H_
#define ZMQ_PSDD4CCM_BASIC_TRAITS_H_

#include "psdd4ccm/impl/psdd/psdd_traits_base_t.h"
#include "psdd4ccm/impl/zmq_psdd_traits_base_t.h"

namespace PSDD
{
  template <>
  struct traits <char>
    : public common_traits<char>
    , public basic_packing<char>
  {
    static
    std::string get_type_name () { return "char"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <uint8_t>
    : public common_traits<uint8_t>
    , public basic_packing<uint8_t>
  {
    static
    std::string get_type_name () { return "uint8_t"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <bool>
    : public common_traits<bool>
    , public basic_packing<bool>
  {
    static
    std::string get_type_name () { return "bool"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <wchar_t>
    : public common_traits<wchar_t>
    , public basic_packing<wchar_t>
  {
    static
    std::string get_type_name () { return "wchar"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <int16_t>
    : public common_traits<int16_t>
    , public basic_packing<int16_t>
  {
    static
    std::string get_type_name () { return "int16_t"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <uint16_t>
    : public common_traits<uint16_t>
    , public basic_packing<uint16_t>
  {
    static
    std::string get_type_name () { return "uint16_t"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <int32_t>
    : public common_traits<int32_t>
    , public basic_packing<int32_t>
  {
    static
    std::string get_type_name () { return "int32_t"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <uint32_t>
    : public common_traits<uint32_t>
    , public basic_packing<uint32_t>
  {
    static
    std::string get_type_name () { return "uint32_t"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <int64_t>
    : public common_traits<int64_t>
    , public basic_packing<int64_t>
  {
    static
    std::string get_type_name () { return "int64_t"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <uint64_t>
    : public common_traits<uint64_t>
    , public basic_packing<uint64_t>
  {
    static
    std::string get_type_name () { return "uint64_t"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <float>
    : public common_traits<float>
    , public basic_packing<float>
  {
    static
    std::string get_type_name () { return "float"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <double>
    : public common_traits<double>
    , public basic_packing<double>
  {
    static
    std::string get_type_name () { return "double"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };

  template <>
  struct traits <long double>
    : public common_traits<long double>
    , public basic_packing<long double>
  {
    static
    std::string get_type_name () { return "long double"; }

    typedef std::true_type key_only;
    typedef std::false_type no_key;
  };
}

#endif
