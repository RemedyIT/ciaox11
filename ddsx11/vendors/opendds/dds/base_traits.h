/**
 * @file    base_traits.h
 * @author  Martin Corino
 *
 * @brief   'Static' (not generated) conversion traits for OpenDDS.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_BASE_TRAITS_H_
#define DDSX11_IMPL_NDDS_BASE_TRAITS_H_

#include <cstring>
#include <algorithm>
#include "dds/dds_conversion_traits.h"
#include "ace/CDR_Base.h"
#include "tao/String_Manager_T.h"

namespace DDSX11
{

  /**
   * Standard type DDS traits for OpenDDS implementation
   */
  //@{
  template <>
  struct traits<uint8_t>
    : public common_traits<uint8_t>,
      public pass_in<uint8_t>,
      public pass_out_by_ref<uint8_t>,
      public pass_retn<uint8_t>
  {
  };

  template <>
  struct traits<char>
    : public common_traits<char>,
      public pass_in<char>,
      public pass_out_by_ref<char>,
      public pass_retn<char>
  {
  };

  template <>
  struct traits<wchar_t>
    : public common_traits<wchar_t>,
      public pass_in<wchar_t>,
      public pass_out_by_ref<wchar_t>,
      public pass_retn<wchar_t>
  {
  };

  template <>
  struct traits<int16_t>
    : public common_traits<int16_t>,
      public pass_in<int16_t>,
      public pass_out_by_ref<int16_t>,
      public pass_retn<int16_t>
  {
  };

  template <>
  struct traits<uint16_t>
    : public common_traits<uint16_t>,
      public pass_in<uint16_t>,
      public pass_out_by_ref<uint16_t>,
      public pass_retn<uint16_t>
  {
  };

  template <>
  struct traits<int32_t>
    : public common_traits<int32_t>,
      public pass_in<int32_t>,
      public pass_out_by_ref<int32_t>,
      public pass_retn<int32_t>
  {
  };

  template <>
  struct traits<uint32_t>
    : public common_traits<uint32_t>,
      public pass_in<uint32_t>,
      public pass_out_by_ref<uint32_t>,
      public pass_retn<uint32_t>
  {
  };

  template <>
  struct traits<int64_t>
    : public common_traits<int64_t>,
      public pass_in<int64_t>,
      public pass_out_by_ref<int64_t>,
      public pass_retn<int64_t>
  {
  };

  template <>
  struct traits<uint64_t>
    : public common_traits<uint64_t>,
      public pass_in<uint64_t>,
      public pass_out_by_ref<uint64_t>,
      public pass_retn<uint64_t>
  {
  };

  template <>
  struct traits<float>
    : public common_traits<float>,
      public pass_in<float>,
      public pass_out_by_ref<float>,
      public pass_retn<float>
  {
  };

  template <>
  struct traits<double>
    : public common_traits<double>,
      public pass_in<double>,
      public pass_out_by_ref<double>,
      public pass_retn<double>
  {
  };

  //@}

  /**
   * Special basic types
   */
  //@{
  /// String types
  template <>
  inline char*& to_dds<char*, std::string> (char*& to, const std::string& from)
  {
    to = TAO_CORBA::string_dup(from.c_str ());
    return to;
  }

  template <>
  inline const char*& to_dds<const char*, std::string> (const char*& to, const std::string& from)
  {
    to = from.c_str ();
    return to;
  }

  template <>
  inline TAO::String_Manager& to_dds<TAO::String_Manager, std::string> (TAO::String_Manager& to, const std::string& from)
  {
    to = TAO_CORBA::string_dup (from.c_str ());
    return to;
  }

  template <>
  inline TAO::unbounded_basic_string_sequence<char>::element_type& to_dds<TAO::unbounded_basic_string_sequence<char>::element_type, std::string> (TAO::unbounded_basic_string_sequence<char>::element_type & to, const std::string& from)
  {
    to = TAO_CORBA::string_dup (from.c_str ());
    return to;
  }

  template <>
  inline std::string& from_dds<TAO::String_Manager, std::string> (std::string& to, TAO::String_Manager const & from)
  {
    to = from.in ();
    return to;
  }

  template <>
  inline std::string& from_dds<TAO::unbounded_basic_string_sequence<char>::const_element_type, std::string> (std::string& to, TAO::unbounded_basic_string_sequence<char>::const_element_type const & from)
  {
    to = from.in ();
    return to;
  }

  template <>
  inline std::string& from_dds<const char*, std::string> (std::string& to, const char* const& from)
  {
    if (from) to = from; else to.clear ();
    return to;
  }

  template <>
  struct traits<std::string>
    : public common_traits<std::string, TAO::String_Manager>
  {
    struct in
    {
      typedef std::string in_type;
      typedef const char* dds_in_type;
      dds_in_type value_ {};

      in () {}
      in (const in_type& v) { ::DDSX11::to_dds (this->value_, v); }
      ~in () { ::DDSX11::dds_finalize (value_); }
      in& operator =(const in_type& v) { ::DDSX11::to_dds (this->value_, v); return *this; }
      operator dds_in_type () const {  return this->value_; }
    };

    // special for strings
    struct out
    {
      typedef std::string out_type;
      typedef char* dds_out_type;
      out_type& value_;
      TAO::String_Manager dds_value_;

      out (out_type& v) : value_ (v) { }
      ~out () { this->value_ = this->dds_value_; }
      operator dds_out_type& () { return this->dds_value_.out (); }
    };

    struct inout : public out
    {
      inout (out::out_type& v) : out (v)
      { this->dds_value_ = this->value_.c_str (); };
      operator out::dds_out_type& () { return this->dds_value_.inout (); }
    };

    struct retn
    {
      typedef std::string retn_type;
      typedef char* dds_retn_type;
      retn_type value_;

      retn () = default;
      retn (char* v)
      {
        this->value_ = v;
        TAO_CORBA::string_free(v);
      }
      retn& operator = (char* v)
      {
        this->value_ = v;
        TAO_CORBA::string_free (v);
        return *this;
      }
      operator retn_type () { return this->value_; }
    };
  };


  /// long double types.
  template<>
  inline DDS_Native::DDS::LongDouble&
  to_dds<DDS_Native::DDS::LongDouble, long double> (
    DDS_Native::DDS::LongDouble &to, const long double& from)
  {
    ACE_CDR_LONG_DOUBLE_ASSIGNMENT (to, from);
    return to;
  }

  /// long double from DDS
  template<>
  inline long double&
  from_dds <DDS_Native::DDS::LongDouble, long double> (
    long double &to, const DDS_Native::DDS::LongDouble &from)
  {
    to = from;
    return to;
  }

  template <>
  struct traits<long double>
    : public common_traits< long double, DDS_Native::DDS::LongDouble>
    , public convert_in< long double, DDS_Native::DDS::LongDouble>
    , public convert_out_by_ref< long double, DDS_Native::DDS::LongDouble>
    , public convert_retn< long double, DDS_Native::DDS::LongDouble>
  {
  };

  /// Booleans
  template <>
  inline bool& to_dds<bool, bool> (bool& to, const bool& from)
  { to = from; return to; }

  template <>
  inline bool& from_dds<bool, bool> (bool& to, const bool& from)
  { to = from; return to; }

  template <>
  struct traits<bool>
    : public common_traits<bool, bool>,
      public convert_in<bool, bool>,
      public convert_out_by_ref<bool, bool>,
      public convert_retn<bool, bool>
  {
  };

  /// Unsigned long const in IDL and enums in OpenDDS
  // uint32_t
  template <typename DDS_DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DDS_DATA_TYPE>::value>::type>
  void __int_to_enum_dds (DDS_DATA_TYPE& to, uint32_t from, std::false_type)
  { to = from; }
  template <typename DDS_DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DDS_DATA_TYPE>::value>::type>
  void __int_to_enum_dds (DDS_DATA_TYPE& to, uint32_t from, std::true_type)
  { to = static_cast<DDS_DATA_TYPE> (from); }
  template <typename DDS_DATA_TYPE>
  DDS_DATA_TYPE& to_dds (DDS_DATA_TYPE& to, uint32_t const & from)
  { __int_to_enum_dds (to, from, std::is_enum<DDS_DATA_TYPE>()); return to; }

  /// long consts in IDL and enums in OpenDDS
  template <typename DDS_DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DDS_DATA_TYPE>::value>::type>
  void __int_to_enum_dds (DDS_DATA_TYPE& to, int32_t from, std::false_type)
  { to = from; }
  template <typename DDS_DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DDS_DATA_TYPE>::value>::type>
  void __int_to_enum_dds (DDS_DATA_TYPE& to, int32_t from, std::true_type)
  { to = static_cast<DDS_DATA_TYPE> (from); }
  template <typename DDS_DATA_TYPE>
  DDS_DATA_TYPE& to_dds (DDS_DATA_TYPE& to, int32_t const & from)
  { __int_to_enum_dds (to, from, std::is_enum<DDS_DATA_TYPE>()); return to; }
  //@}

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    to.length (ACE_Utils::truncate_cast<DDS_Native::DDS::sequence_size_type> (from.size ()));
    DDS_Native::DDS::sequence_size_type c {};
    for (const auto& val: from)
      {
        ::DDSX11::to_dds (to[c++], val);
      }
    return to;
  }

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  fixedsize_sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    return sequence_to_dds (to, from);
  }

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  string_sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    to.length (ACE_Utils::truncate_cast<DDS_Native::DDS::sequence_size_type> (from.size ()));
    DDS_Native::DDS::sequence_size_type c {};
    for (const auto& val: from)
      {
        typename DDS_NATIVE_SEQ::element_type sequence_element = to[c++];
        ::DDSX11::to_dds (sequence_element, val);
      }
    return to;
  }

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  bounded_string_sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    to.length (ACE_Utils::truncate_cast<DDS_Native::DDS::sequence_size_type> (from.size ()));
    DDS_Native::DDS::sequence_size_type c {};
    for (const auto& val: from)
      {
        char* to_element {};
        ::DDSX11::to_dds (to_element, val);
        to[c++] = to_element;
      }
    return to;
  }

  template <typename DDS_SEQ, typename DDS_NATIVE_SEQ>
  inline DDS_SEQ&
  sequence_from_dds (DDS_SEQ& to, const DDS_NATIVE_SEQ& from)
  {
    to.resize (from.length ());
    typename DDS_SEQ::size_type c {};
    for (DDS_Native::DDS::sequence_size_type i {}; i < from.length(); ++i)
      {
        ::DDSX11::from_dds (to[c++], from[i]);
      }
    return to;
  }

  template <typename DDS_SEQ, typename DDS_NATIVE_SEQ>
  inline DDS_SEQ&
  boolean_sequence_from_dds (DDS_SEQ& to, const DDS_NATIVE_SEQ& from)
  {
    to.resize (from.length ());
    typename std::vector<bool>::size_type c {};
    for (DDS_Native::DDS::sequence_size_type i {}; i < from.length(); ++i)
    {
      to[c++] = (from[i] ? true : false);
    }
    return to;
  }

  template <typename DDS_SEQ, typename DDS_NATIVE_SEQ>
  inline DDS_SEQ&
  bounded_string_sequence_from_dds (DDS_SEQ& to, const DDS_NATIVE_SEQ& from)
  {
    to.resize (from.length ());
    typename DDS_SEQ::size_type c {};
    for (DDS_Native::DDS::sequence_size_type i {}; i < from.length(); ++i)
      {
        ::DDSX11::from_dds (to[c++], const_cast<char*>(from[i].in()));
      }
    return to;
  }
}

#endif /* DDSX11_IMPL_NDDS_BASE_TRAITS_H_ */
