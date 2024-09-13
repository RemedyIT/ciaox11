/**
 * @file    dds_conversion_traits.h
 * @author  Marcel Smit
 *
 * @brief   Base traits for the conversion traits
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_CONVERSION_TRAITS_BASE_H_
#define DDSX11_IMPL_CONVERSION_TRAITS_BASE_H_

#include <type_traits>

namespace DDSX11
{
  /**
   * Base struct for conversions
   */
  //@{
  template <typename DATA_TYPE, typename DDS_DATA_TYPE = DATA_TYPE>
  struct common_traits
  {
    using value_type = DATA_TYPE ;
    using dds_value_type = DDS_DATA_TYPE;
  };

  template <typename DATA_TYPE, typename DDS_DATA_TYPE = DATA_TYPE>
  struct traits
    : public common_traits<DATA_TYPE, DDS_DATA_TYPE>
  {
  };
  //@}

  /**
   * Conversion helpers for scalar types
   * (integrals, floating point, pointers, enums)
   */
  //@{
  template <typename DDS_DATA_TYPE, typename DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DATA_TYPE>::value>::type>
  void __to_dds (DDS_DATA_TYPE& to, DATA_TYPE from, std::false_type)
  { to = from; }
  template <typename DDS_DATA_TYPE, typename DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DATA_TYPE>::value>::type>
  void __to_dds (DDS_DATA_TYPE& to, DATA_TYPE from, std::true_type)
  { to = static_cast<DDS_DATA_TYPE> (from); }
  template <typename DDS_DATA_TYPE, typename DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DATA_TYPE>::value>::type>
  void __from_dds (DATA_TYPE& to, DDS_DATA_TYPE from, std::false_type)
  { to = from; }
  template <typename DDS_DATA_TYPE, typename DATA_TYPE, typename = typename
      std::enable_if<std::is_scalar<DATA_TYPE>::value>::type>
  void __from_dds (DATA_TYPE& to, DDS_DATA_TYPE from, std::true_type)
  { to = static_cast<DATA_TYPE> (from); }
  //@}

  /**
   * Default converter methods
   */
  //@{
  template <typename DDS_DATA_TYPE, typename DATA_TYPE>
  DDS_DATA_TYPE& to_dds (DDS_DATA_TYPE& to, DATA_TYPE const & from)
  { __to_dds (to, from, std::is_enum<DATA_TYPE>()); return to; }
  template <typename DDS_DATA_TYPE, typename DATA_TYPE>
  DATA_TYPE& from_dds (DATA_TYPE& to, DDS_DATA_TYPE const & from)
  { __from_dds (to, from, std::is_enum<DATA_TYPE>()); return to; }
  //@}

  /**
   * Converting DDS argument traits
   */
  //@{
  template <typename DATA_TYPE, typename DDS_DATA_TYPE = DATA_TYPE>
  struct convert_in
  {
    struct in
    {
      typedef DATA_TYPE in_type;
      typedef DDS_DATA_TYPE dds_in_type;
      dds_in_type value_;

      in () = default;
      in (const in_type& v) { ::DDSX11::to_dds (this->value_, v); }
      ~in () = default;
      in& operator =(const in_type& v) { ::DDSX11::to_dds (this->value_, v); return *this; }
      operator const dds_in_type& () const {  return this->value_; }
    };
  };

  template <typename DATA_TYPE, typename DDS_DATA_TYPE = DATA_TYPE>
  struct convert_entity_in
  {
    struct in
    {
      typedef DATA_TYPE in_type;
      typedef DDS_DATA_TYPE dds_in_type;
      in_type value_;
      dds_in_type dds_value_;

      in (DATA_TYPE v) { this->value_ = v; ::DDSX11::to_dds (this->dds_value_, this->value_); }
      operator dds_in_type () const {  return this->dds_value_; }
    };
  };

  template <typename DATA_TYPE, typename DDS_DATA_TYPE = DATA_TYPE>
  struct convert_retn
  {
    struct retn
    {
      typedef DATA_TYPE retn_type;
      typedef DDS_DATA_TYPE dds_retn_type;
      retn_type value_;

      retn () = default;
      retn (const dds_retn_type& v) { ::DDSX11::from_dds (this->value_, v); }
      retn& operator = (const dds_retn_type& v) { ::DDSX11::from_dds (this->value_, v); return *this; }
      operator retn_type () { return std::move(this->value_); }
    };
  };

  template <typename DATA_TYPE, typename DDS_DATA_TYPE = DATA_TYPE>
  struct convert_out_by_ref
  {
    struct out
    {
      typedef DATA_TYPE out_type;
      typedef DDS_DATA_TYPE dds_out_type;
      out_type& value_;
      dds_out_type dds_value_;

      out (out_type& v) : value_ (v) {}
      ~out () { ::DDSX11::from_dds (this->value_, this->dds_value_); }
      operator dds_out_type& () { return this->dds_value_; }
    };

    struct inout : public out
    {
      inout (typename out::out_type& v) : out (v) { ::DDSX11::to_dds (this->dds_value_, this->value_); }
      operator typename out::dds_out_type& () { return this->dds_value_; }
    };
  };

  template <typename DATA_TYPE, typename DDS_DATA_TYPE = DATA_TYPE>
  struct convert_out_by_ptr
  {
    struct out
    {
      typedef DATA_TYPE out_type;
      typedef DDS_DATA_TYPE dds_out_type;
      out_type* value_;
      dds_out_type dds_value_;

      out (out_type* v) : value_ (v) {}
      ~out () { ::DDSX11::from_dds (*this->value_, this->dds_value_); }
      operator dds_out_type* () { return &this->dds_value_; }
    };

    struct inout : public out
    {
      inout (typename out::out_type* v) : out (v) { ::DDSX11::to_dds (this->dds_value_, *this->value_); }
      operator typename out::dds_out_type* () { return &this->dds_value_; }
    };
  };
  //@}

  /**
   * NON-Converting DDS argument traits
   */
  //@{
  template <typename DATA_TYPE>
  struct pass_in
  {
    struct in
    {
      typedef DATA_TYPE in_type;
      typedef DATA_TYPE dds_in_type;
      const in_type& value_;

      in () = default;
      in (const in_type& v) : value_ (v) {}
      in& operator =(const in_type& v) { this->value_ = v; return *this; }
      operator const dds_in_type & () const { return this->value_; }
    };
  };

  template <typename DATA_TYPE>
  struct pass_retn
  {
    struct retn
    {
      typedef DATA_TYPE retn_type;
      typedef DATA_TYPE dds_retn_type;
      retn_type value_;

      retn () = default;
      retn (dds_retn_type v) : value_ (std::move(v)) { }
      retn& operator = (dds_retn_type v) { this->value_ = std::move(v); return *this; }
      operator retn_type () { return std::move(this->value_); }
    };
  };

  template <typename DATA_TYPE>
  struct pass_out_by_ref
  {
    struct out
    {
      typedef DATA_TYPE out_type;
      typedef DATA_TYPE dds_out_type;
      out_type& value_;

      out (out_type& v) : value_ (v) { }
      operator dds_out_type& () { return this->value_; }
    };

    typedef out inout;
  };

  template <typename DATA_TYPE>
  struct pass_out_by_ptr
  {
    struct out
    {
      typedef DATA_TYPE out_type;
      typedef DATA_TYPE dds_out_type;
      out_type* value_;

      out (out_type* v) : value_ (v) { }
      operator out_type* () { return this->value_; }
    };

    typedef out inout;
  };
  //@}
} // namespace DDSX11

#endif /* DDSX11_IMPL_CONVERSION_TRAITS_BASE_H_ */
