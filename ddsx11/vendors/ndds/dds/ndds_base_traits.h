/**
 * @file    ndds_base_traits.h
 * @author  Martin Corino
 *
 * @brief   'Static' (not generated) conversion traits for RTI NDDS.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_BASE_TRAITS_H_
#define DDSX11_IMPL_NDDS_BASE_TRAITS_H_

#include <cstring>
#include <algorithm>
#include "dds/dds_conversion_traits.h"
#include "ace/CDR_Base.h"

/// By default the RTI NDDS::String type manage strings up to 1k
constexpr uint32_t max_string_size () { return 1024; }
/// By default the RTI NDDS::DDS_Char* type for unbounded string members manages strings up to 255 characters
constexpr uint32_t max_member_string_size () { return 255; }

namespace DDSX11
{

  /**
   * Standard type DDS traits for NDDS implementation
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
  inline char *& to_dds<char*, std::string> (char*& to, const std::string& from)
  {
    if (to == nullptr)
    {
      // allocate a maximum size buffer
      to = ::DDS_String_alloc (max_member_string_size ());

    }
    // copy string content
    std::strncpy (to, from.c_str (), max_member_string_size ());
    return to;
  }

  template <>
  inline std::string& from_dds<const char*, std::string> (std::string& to, const char* const & from)
  { if (from) to = from; else to.clear (); return to; }

  template <>
  inline std::string& from_dds<char*, std::string> (std::string& to, char* const & from)
  { if (from) to = from; else to.clear (); return to; }

  template <>
  inline void dds_init (char*& sample)
  { sample = nullptr; }

  template <>
  struct traits<std::string>
    : public common_traits<std::string, char*>,
      public convert_in<std::string, char*>,
      public convert_retn<std::string, char const *>
  {
    struct in
    {
      typedef std::string in_type;
      typedef char * dds_in_type;
      char dds_value_[max_string_size ()];

      in (const in_type& v)
      {
        std::memcpy (this->dds_value_,
                     v.c_str (),
                     std::min<std::string::size_type> (v.size ()+1, max_string_size ()));
      }
      ~in () = default;
      operator dds_in_type () { return this->dds_value_; }
    };

    // special for strings
    struct out
    {
      typedef std::string out_type;
      typedef char * dds_out_type;
      out_type& value_;
      char dds_value_[max_string_size ()];

      out (out_type& v) : value_ (v) { }
      ~out () { this->value_ = this->dds_value_; }
      operator dds_out_type () { return this->dds_value_; }
    };

    struct inout : public out
    {
      inout (out::out_type& v) : out (v)
      {
        std::memcpy (this->dds_value_,
                     this->value_.c_str (),
                     std::min<std::string::size_type> (this->value_.size ()+1, max_string_size ()));
      };
      operator out::dds_out_type () { return this->dds_value_; }
    };
  };

  /// long double types.
  template<>
  inline ::DDS_Native::DDS::LongDouble&
  to_dds< ::DDS_Native::DDS::LongDouble, long double> (
    ::DDS_Native::DDS::LongDouble &to, const long double& from)
  {
    // Portable way to convert a long double on all 32/64 bits platforms
#if (ACE_SIZEOF_LONG_DOUBLE == 16)
    std::memcpy (to.bytes, &from, sizeof(to.bytes));
#else
    ACE_CDR::LongDouble ld; ACE_CDR_LONG_DOUBLE_ASSIGNMENT (ld, from);
    std::memcpy (to.bytes, ld.ld, sizeof(to.bytes));
#endif
    return to;
  }

  // long double FROM DDS
  template<>
  inline long double&
  from_dds<DDS_Native::DDS::LongDouble, long double> (
    long double &to, const DDS_Native::DDS::LongDouble &from)
  {
    // Portable way to convert a long double on all 32/64 bits platforms
#if (ACE_SIZEOF_LONG_DOUBLE == 16)
    std::memcpy (std::addressof(to), from.bytes, sizeof (to));
#else
    ACE_CDR::LongDouble to_ld;
    std::memcpy (to_ld.ld, from.bytes, sizeof (to_ld.ld));
    to = to_ld;
#endif
    return to;
  }

  template <>
  struct traits< long double>
    : public common_traits< long double, DDS_Native::DDS::LongDouble>
    , public convert_in< long double, DDS_Native::DDS::LongDouble>
    , public convert_out_by_ref< long double, DDS_Native::DDS::LongDouble>
    , public convert_retn< long double, DDS_Native::DDS::LongDouble>
  {
  };

  /// Booleans
  template <>
  inline DDS_Boolean& to_dds<DDS_Boolean, bool> (DDS_Boolean& to, const bool& from)
  { to = from ? 1 : 0; return to; }

  template <>
  inline bool& from_dds<DDS_Boolean, bool> (bool& to, const DDS_Boolean& from)
  { to = from == 0 ? false : true; return to; }

  template <>
  struct traits<bool>
    : public common_traits<bool, DDS_Boolean>,
      public convert_in<bool, DDS_Boolean>,
      public convert_out_by_ref<bool, DDS_Boolean>,
      public convert_retn<bool, DDS_Boolean>
  {
  };

  /// Unsigned long consts in IDL and enums in RTI NDDS
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

  /// long consts in IDL and enums in RTI NDDS
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

  /**
   * Special conversions
   */
  //@{
  /// DDS::InstanceHandle_t TO DDS
  template<>
  inline DDS_Native::DDS::InstanceHandle_t&
  to_dds<DDS_Native::DDS::InstanceHandle_t, DDS::InstanceHandle_t> (
    DDS_Native::DDS::InstanceHandle_t &to, const DDS::InstanceHandle_t &from)
  {
    std::memcpy (to.keyHash.value, &from.value (), sizeof (from.value ()));
    ::DDSX11::to_dds(to.keyHash.length, from.length ());
    ::DDSX11::to_dds(to.isValid, from.isValid ());
    return to;
  }

  // DDS::InstanceHandle_t FROM DDS
  template<>
  inline DDS::InstanceHandle_t&
  from_dds<DDS_Native::DDS::InstanceHandle_t, DDS::InstanceHandle_t> (
    DDS::InstanceHandle_t &to, const DDS_Native::DDS::InstanceHandle_t &from)
  {
    if (DDS_InstanceHandle_is_nil (std::addressof(from)))
      {
        to = ::DDS::HANDLE_NIL;
      }
    else
      {
        std::memcpy (std::addressof(to.value ()), from.keyHash.value, sizeof (from.keyHash.value));
        ::DDSX11::from_dds (to.length (), from.keyHash.length);
        ::DDSX11::from_dds (to.isValid (), from.isValid);
      }
    return to;
  }

  template <>
  struct traits<DDS::InstanceHandle_t>
    : public common_traits<DDS::InstanceHandle_t, DDS_Native::DDS::InstanceHandle_t>
    , public convert_in<DDS::InstanceHandle_t, DDS_Native::DDS::InstanceHandle_t>
    , public convert_out_by_ref<DDS::InstanceHandle_t, DDS_Native::DDS::InstanceHandle_t>
    , public convert_retn<DDS::InstanceHandle_t, DDS_Native::DDS::InstanceHandle_t>
  {
  };
  //@}

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    if (to.ensure_length (ACE_Utils::truncate_cast<DDS_Native::DDS::sequence_size_type> (from.size ()),
                          ACE_Utils::truncate_cast<DDS_Native::DDS::sequence_size_type> (from.size ())))
    {
      DDS_Native::DDS::sequence_size_type c {};
      for (const auto& val: from)
        {
          ::DDSX11::to_dds (to[c++], val);
        }
    }
    else
    {
      throw std::length_error ("Unable to set maximum and length to <" + std::to_string (from.size ()) + ">");
    }
    return to;
  }

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  fixedsize_sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    if (!to.from_array(from.data (), ACE_Utils::truncate_cast<DDS_Native::DDS::sequence_size_type> (from.size ())))
    {
      throw std::runtime_error ("Unable to copy sequence data to DDS");
    }
    return to;
  }

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  string_sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    return sequence_to_dds (to, from);
  }

  template <typename DDS_NATIVE_SEQ, typename DDS_SEQ>
  inline DDS_NATIVE_SEQ&
  bounded_string_sequence_to_dds (DDS_NATIVE_SEQ& to, const DDS_SEQ& from)
  {
    return sequence_to_dds (to, from);
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
  fixedsize_sequence_from_dds (DDS_SEQ& to, const DDS_NATIVE_SEQ& from)
  {
    to.resize (from.length ());
    const_cast<DDS_NATIVE_SEQ&> (from).to_array (to.data (), ACE_Utils::truncate_cast<DDS_Native::DDS::sequence_size_type> (to.size ()));
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
    return sequence_from_dds (to, from);
  }
}

#endif /* DDSX11_IMPL_NDDS_BASE_TRAITS_H_ */
