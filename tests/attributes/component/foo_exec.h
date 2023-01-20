// -*- C++ -*-
/**
 * @file    foo_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 attribute test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_FOO_EXEC_H_DIHEJGFA_INCLUDED__
#define __RIDL_FOO_EXEC_H_DIHEJGFA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_impl.h[Header]

#pragma once

#include "fooEC.h"

#include /**/ "foo_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : foo_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : foo_impl.h[user_global_decl]

/// Namespace for implementation of Base component
namespace Base_Impl
{
  /// Forward declarations
  class Base_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Base_exec_i
  class Base_exec_i final
    : public virtual IDL::traits< CCM_Base>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[ctor]
    /// Constructor
    Base_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[ctor]
    /// Destructor
    ~Base_exec_i () override;

    /** @name Supported attributes. */
    //@{

    /// Attribute m_base_pt_base_pt
    int16_t m_base_pt_base_pt () override;
    void m_base_pt_base_pt (int16_t m_base_pt_base_pt) override;

    /// Attribute attr_base
    int16_t attr_base () override;
    void attr_base (int16_t attr_base) override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_Base_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of m_base_pt_base_pt attribute
    int16_t m_base_pt_base_pt_{};
    /// Class member storing value of attr_base attribute
    int16_t attr_base_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Base_exec_i(const Base_exec_i&) = delete;
    Base_exec_i(Base_exec_i&&) = delete;
    Base_exec_i& operator=(const Base_exec_i&) = delete;
    Base_exec_i& operator=(Base_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[user_namespace_end_decl]

} // namespace Base_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[factory]
extern "C" FOO_EXEC_Export  void
create_Base_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[factory]

/// Namespace for implementation of Foo component
namespace Foo_Impl
{
  /// Forward declarations
  class Foo_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Foo_exec_i
  class Foo_exec_i final
    : public virtual IDL::traits< CCM_Foo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ctor]
    /// Constructor
    Foo_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ctor]
    /// Destructor
    ~Foo_exec_i () override;

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute m_base_pt_base_pt
    int16_t m_base_pt_base_pt () override;
    void m_base_pt_base_pt (int16_t m_base_pt_base_pt) override;

    /// Attribute attr_base
    int16_t attr_base () override;
    void attr_base (int16_t attr_base) override;

    /// Attribute m_foo_pt_foo_pt
    int16_t m_foo_pt_foo_pt () override;
    void m_foo_pt_foo_pt (int16_t m_foo_pt_foo_pt) override;

    /// Attribute the_byte_get_set_raise
    uint8_t the_byte_get_set_raise () override;
    void the_byte_get_set_raise (uint8_t the_byte_get_set_raise) override;

    /// Attribute the_byte_set_raise
    uint8_t the_byte_set_raise () override;
    void the_byte_set_raise (uint8_t the_byte_set_raise) override;

    /// Attribute the_byte_get_raise
    uint8_t the_byte_get_raise () override;
    void the_byte_get_raise (uint8_t the_byte_get_raise) override;

    /// Attribute readonly_short_raise
    int16_t readonly_short_raise () override;

    /// Attribute readonly_short
    int16_t readonly_short () override;

    /// Attribute my_char
    char my_char () override;
    void my_char (char my_char) override;

    /// Attribute my_octet
    uint8_t my_octet () override;
    void my_octet (uint8_t my_octet) override;

    /// Attribute my_boolean
    bool my_boolean () override;
    void my_boolean (bool my_boolean) override;

    /// Attribute my_short
    int16_t my_short () override;
    void my_short (int16_t my_short) override;

    /// Attribute my_long
    int32_t my_long () override;
    void my_long (int32_t my_long) override;

    /// Attribute my_float
    float my_float () override;
    void my_float (float my_float) override;

    /// Attribute my_double
    double my_double () override;
    void my_double (double my_double) override;

    /// Attribute my_ulong
    uint32_t my_ulong () override;
    void my_ulong (uint32_t my_ulong) override;

    /// Attribute my_longlong
    int64_t my_longlong () override;
    void my_longlong (int64_t my_longlong) override;

    /// Attribute my_ulonglong
    uint64_t my_ulonglong () override;
    void my_ulonglong (uint64_t my_ulonglong) override;

    /// Attribute my_default_char
    char my_default_char () override;
    void my_default_char (char my_default_char) override;

    /// Attribute my_default_octet
    uint8_t my_default_octet () override;
    void my_default_octet (uint8_t my_default_octet) override;

    /// Attribute my_default_boolean
    bool my_default_boolean () override;
    void my_default_boolean (bool my_default_boolean) override;

    /// Attribute my_default_short
    int16_t my_default_short () override;
    void my_default_short (int16_t my_default_short) override;

    /// Attribute my_default_long
    int32_t my_default_long () override;
    void my_default_long (int32_t my_default_long) override;

    /// Attribute my_default_float
    float my_default_float () override;
    void my_default_float (float my_default_float) override;

    /// Attribute my_default_double
    double my_default_double () override;
    void my_default_double (double my_default_double) override;

    /// Attribute my_default_ulong
    uint32_t my_default_ulong () override;
    void my_default_ulong (uint32_t my_default_ulong) override;

    /// Attribute my_default_longlong
    int64_t my_default_longlong () override;
    void my_default_longlong (int64_t my_default_longlong) override;

    /// Attribute my_default_ulonglong
    uint64_t my_default_ulonglong () override;
    void my_default_ulonglong (uint64_t my_default_ulonglong) override;

    /// Attribute my_longdouble
    long double my_longdouble () override;
    void my_longdouble (long double my_longdouble) override;

    /// Attribute my_default_longdouble
    long double my_default_longdouble () override;
    void my_default_longdouble (long double my_default_longdouble) override;

    /// Attribute my_bounded_string
    ::bounded_string my_bounded_string () override;
    void my_bounded_string (const ::bounded_string& my_bounded_string) override;

    /// Attribute my_variable_string
    std::string my_variable_string () override;
    void my_variable_string (const std::string& my_variable_string) override;

    /// Attribute my_default_variable_string
    std::string my_default_variable_string () override;
    void my_default_variable_string (const std::string& my_default_variable_string) override;

    /// Attribute my_bounded_wstring
    ::bounded_wstring my_bounded_wstring () override;
    void my_bounded_wstring (const ::bounded_wstring& my_bounded_wstring) override;

    /// Attribute my_variable_wstring
    std::wstring my_variable_wstring () override;
    void my_variable_wstring (const std::wstring& my_variable_wstring) override;

    /// Attribute my_long_array
    ::long_array my_long_array () override;
    void my_long_array (const ::long_array& my_long_array) override;

    /// Attribute my_ulong_array
    ::ulong_array my_ulong_array () override;
    void my_ulong_array (const ::ulong_array& my_ulong_array) override;

    /// Attribute my_longlong_array
    ::longlong_array my_longlong_array () override;
    void my_longlong_array (const ::longlong_array& my_longlong_array) override;

    /// Attribute my_ulonglong_array
    ::ulonglong_array my_ulonglong_array () override;
    void my_ulonglong_array (const ::ulonglong_array& my_ulonglong_array) override;

    /// Attribute my_short_array
    ::short_array my_short_array () override;
    void my_short_array (const ::short_array& my_short_array) override;

    /// Attribute my_ushort_array
    ::ushort_array my_ushort_array () override;
    void my_ushort_array (const ::ushort_array& my_ushort_array) override;

    /// Attribute my_string_array
    ::string_array my_string_array () override;
    void my_string_array (const ::string_array& my_string_array) override;

    /// Attribute my_wstring_array
    ::wstring_array my_wstring_array () override;
    void my_wstring_array (const ::wstring_array& my_wstring_array) override;

    /// Attribute my_char_array
    ::char_array my_char_array () override;
    void my_char_array (const ::char_array& my_char_array) override;

    /// Attribute my_wchar_array
    ::wchar_array my_wchar_array () override;
    void my_wchar_array (const ::wchar_array& my_wchar_array) override;

    /// Attribute my_double_array
    ::double_array my_double_array () override;
    void my_double_array (const ::double_array& my_double_array) override;

    /// Attribute my_longdouble_array
    ::longdouble_array my_longdouble_array () override;
    void my_longdouble_array (const ::longdouble_array& my_longdouble_array) override;

    /// Attribute my_float_array
    ::float_array my_float_array () override;
    void my_float_array (const ::float_array& my_float_array) override;

    /// Attribute my_boolean_array
    ::boolean_array my_boolean_array () override;
    void my_boolean_array (const ::boolean_array& my_boolean_array) override;

    /// Attribute my_octet_array
    ::octet_array my_octet_array () override;
    void my_octet_array (const ::octet_array& my_octet_array) override;

    /// Attribute my_multi_dimensional_short_array
    ::multi_dimensional_short_array my_multi_dimensional_short_array () override;
    void my_multi_dimensional_short_array (const ::multi_dimensional_short_array& my_multi_dimensional_short_array) override;

    /// Attribute my_short_sequence
    ::short_sequence my_short_sequence () override;
    void my_short_sequence (const ::short_sequence& my_short_sequence) override;

    /// Attribute my_empty_sequence
    ::short_sequence my_empty_sequence () override;
    void my_empty_sequence (const ::short_sequence& my_empty_sequence) override;

    /// Attribute my_long_sequence
    ::long_sequence my_long_sequence () override;
    void my_long_sequence (const ::long_sequence& my_long_sequence) override;

    /// Attribute my_float_sequence
    ::float_sequence my_float_sequence () override;
    void my_float_sequence (const ::float_sequence& my_float_sequence) override;

    /// Attribute my_double_sequence
    ::double_sequence my_double_sequence () override;
    void my_double_sequence (const ::double_sequence& my_double_sequence) override;

    /// Attribute my_string_sequence
    ::string_sequence my_string_sequence () override;
    void my_string_sequence (const ::string_sequence& my_string_sequence) override;

    /// Attribute my_string_sequence_2
    ::string_sequence2 my_string_sequence_2 () override;
    void my_string_sequence_2 (const ::string_sequence2& my_string_sequence_2) override;

    /// Attribute my_array_sequence
    ::array_sequence my_array_sequence () override;
    void my_array_sequence (const ::array_sequence& my_array_sequence) override;

    /// Attribute my_bar_struct
    ::Bar my_bar_struct () override;
    void my_bar_struct (const ::Bar& my_bar_struct) override;

    /// Attribute my_default_bar_struct
    ::Bar my_default_bar_struct () override;
    void my_default_bar_struct (const ::Bar& my_default_bar_struct) override;

    /// Attribute my_bar_array
    ::BarArray my_bar_array () override;
    void my_bar_array (const ::BarArray& my_bar_array) override;

    /// Attribute my_bar_array_2
    ::BarArray2 my_bar_array_2 () override;
    void my_bar_array_2 (const ::BarArray2& my_bar_array_2) override;

    /// Attribute my_sequence_array
    ::SequenceArray my_sequence_array () override;
    void my_sequence_array (const ::SequenceArray& my_sequence_array) override;

    /// Attribute my_bar_struct_array
    ::BarStruct my_bar_struct_array () override;
    void my_bar_struct_array (const ::BarStruct& my_bar_struct_array) override;

    /// Attribute my_baz_struct
    ::Baz my_baz_struct () override;
    void my_baz_struct (const ::Baz& my_baz_struct) override;

    /// Attribute my_data_union
    ::Data my_data_union () override;
    void my_data_union (const ::Data& my_data_union) override;

    /// Attribute my_var_data_union
    ::Data2 my_var_data_union () override;
    void my_var_data_union (const ::Data2& my_var_data_union) override;

    /// Attribute my_struct_struct
    ::StructModule::StructStruct my_struct_struct () override;
    void my_struct_struct (const ::StructModule::StructStruct& my_struct_struct) override;

    /// Attribute my_sequence_bounded_string
    ::sequence_bounded_string my_sequence_bounded_string () override;
    void my_sequence_bounded_string (const ::sequence_bounded_string& my_sequence_bounded_string) override;

    /// Attribute my_sequence_bounded_wstring
    ::sequence_bounded_wstring my_sequence_bounded_wstring () override;
    void my_sequence_bounded_wstring (const ::sequence_bounded_wstring& my_sequence_bounded_wstring) override;

    /// Attribute my_bounded_sequence_bounded_string
    ::bounded_sequence_bounded_string my_bounded_sequence_bounded_string () override;
    void my_bounded_sequence_bounded_string (const ::bounded_sequence_bounded_string& my_bounded_sequence_bounded_string) override;

    /// Attribute my_bounded_sequence_bounded_wstring
    ::bounded_sequence_bounded_wstring my_bounded_sequence_bounded_wstring () override;
    void my_bounded_sequence_bounded_wstring (const ::bounded_sequence_bounded_wstring& my_bounded_sequence_bounded_wstring) override;

    /// Attribute my_bounded_string_array
    ::bounded_string_array my_bounded_string_array () override;
    void my_bounded_string_array (const ::bounded_string_array& my_bounded_string_array) override;

    /// Attribute my_bounded_wstring_array
    ::bounded_wstring_array my_bounded_wstring_array () override;
    void my_bounded_wstring_array (const ::bounded_wstring_array& my_bounded_wstring_array) override;

    /// Attribute my_data_type
    ::DataType my_data_type () override;
    void my_data_type (::DataType my_data_type) override;

    /// Attribute my_data_type_type
    ::data_type_type my_data_type_type () override;
    void my_data_type_type (::data_type_type my_data_type_type) override;

    /// Attribute my_any
    CORBA::Any my_any () override;
    void my_any (const CORBA::Any& my_any) override;

    /// Attribute my_any_type
    ::any_type my_any_type () override;
    void my_any_type (const ::any_type& my_any_type) override;

    /// Attribute my_foo_interface
    IDL::traits<::MyFoo>::ref_type my_foo_interface () override;
    void my_foo_interface (IDL::traits<::MyFoo>::ref_type my_foo_interface) override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_Foo_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of m_base_pt_base_pt attribute
    int16_t m_base_pt_base_pt_{};
    /// Class member storing value of attr_base attribute
    int16_t attr_base_{};
    /// Class member storing value of m_foo_pt_foo_pt attribute
    int16_t m_foo_pt_foo_pt_{};
    /// Class member storing value of the_byte_get_set_raise attribute
    uint8_t the_byte_get_set_raise_{};
    /// Class member storing value of the_byte_set_raise attribute
    uint8_t the_byte_set_raise_{};
    /// Class member storing value of the_byte_get_raise attribute
    uint8_t the_byte_get_raise_{};
    /// Class member storing value of readonly_short_raise attribute
    int16_t readonly_short_raise_{};
    /// Class member storing value of readonly_short attribute
    int16_t readonly_short_{};
    /// Class member storing value of my_char attribute
    char my_char_{};
    /// Class member storing value of my_octet attribute
    uint8_t my_octet_{};
    /// Class member storing value of my_boolean attribute
    bool my_boolean_{};
    /// Class member storing value of my_short attribute
    int16_t my_short_{};
    /// Class member storing value of my_long attribute
    int32_t my_long_{};
    /// Class member storing value of my_float attribute
    float my_float_{};
    /// Class member storing value of my_double attribute
    double my_double_{};
    /// Class member storing value of my_ulong attribute
    uint32_t my_ulong_{};
    /// Class member storing value of my_longlong attribute
    int64_t my_longlong_{};
    /// Class member storing value of my_ulonglong attribute
    uint64_t my_ulonglong_{};
    /// Class member storing value of my_default_char attribute
    char my_default_char_{};
    /// Class member storing value of my_default_octet attribute
    uint8_t my_default_octet_{};
    /// Class member storing value of my_default_boolean attribute
    bool my_default_boolean_{};
    /// Class member storing value of my_default_short attribute
    int16_t my_default_short_{};
    /// Class member storing value of my_default_long attribute
    int32_t my_default_long_{};
    /// Class member storing value of my_default_float attribute
    float my_default_float_{};
    /// Class member storing value of my_default_double attribute
    double my_default_double_{};
    /// Class member storing value of my_default_ulong attribute
    uint32_t my_default_ulong_{};
    /// Class member storing value of my_default_longlong attribute
    int64_t my_default_longlong_{};
    /// Class member storing value of my_default_ulonglong attribute
    uint64_t my_default_ulonglong_{};
    /// Class member storing value of my_longdouble attribute
    long double my_longdouble_{};
    /// Class member storing value of my_default_longdouble attribute
    long double my_default_longdouble_{};
    /// Class member storing value of my_bounded_string attribute
    ::bounded_string my_bounded_string_{};
    /// Class member storing value of my_variable_string attribute
    std::string my_variable_string_{};
    /// Class member storing value of my_default_variable_string attribute
    std::string my_default_variable_string_{};
    /// Class member storing value of my_bounded_wstring attribute
    ::bounded_wstring my_bounded_wstring_{};
    /// Class member storing value of my_variable_wstring attribute
    std::wstring my_variable_wstring_{};
    /// Class member storing value of my_long_array attribute
    ::long_array my_long_array_{{}};
    /// Class member storing value of my_ulong_array attribute
    ::ulong_array my_ulong_array_{{}};
    /// Class member storing value of my_longlong_array attribute
    ::longlong_array my_longlong_array_{{}};
    /// Class member storing value of my_ulonglong_array attribute
    ::ulonglong_array my_ulonglong_array_{{}};
    /// Class member storing value of my_short_array attribute
    ::short_array my_short_array_{{}};
    /// Class member storing value of my_ushort_array attribute
    ::ushort_array my_ushort_array_{{}};
    /// Class member storing value of my_string_array attribute
    ::string_array my_string_array_{{}};
    /// Class member storing value of my_wstring_array attribute
    ::wstring_array my_wstring_array_{{}};
    /// Class member storing value of my_char_array attribute
    ::char_array my_char_array_{{}};
    /// Class member storing value of my_wchar_array attribute
    ::wchar_array my_wchar_array_{{}};
    /// Class member storing value of my_double_array attribute
    ::double_array my_double_array_{{}};
    /// Class member storing value of my_longdouble_array attribute
    ::longdouble_array my_longdouble_array_{{}};
    /// Class member storing value of my_float_array attribute
    ::float_array my_float_array_{{}};
    /// Class member storing value of my_boolean_array attribute
    ::boolean_array my_boolean_array_{{}};
    /// Class member storing value of my_octet_array attribute
    ::octet_array my_octet_array_{{}};
    /// Class member storing value of my_multi_dimensional_short_array attribute
    ::multi_dimensional_short_array my_multi_dimensional_short_array_{{}};
    /// Class member storing value of my_short_sequence attribute
    ::short_sequence my_short_sequence_{};
    /// Class member storing value of my_empty_sequence attribute
    ::short_sequence my_empty_sequence_{};
    /// Class member storing value of my_long_sequence attribute
    ::long_sequence my_long_sequence_{};
    /// Class member storing value of my_float_sequence attribute
    ::float_sequence my_float_sequence_{};
    /// Class member storing value of my_double_sequence attribute
    ::double_sequence my_double_sequence_{};
    /// Class member storing value of my_string_sequence attribute
    ::string_sequence my_string_sequence_{};
    /// Class member storing value of my_string_sequence_2 attribute
    ::string_sequence2 my_string_sequence_2_{};
    /// Class member storing value of my_array_sequence attribute
    ::array_sequence my_array_sequence_{};
    /// Class member storing value of my_bar_struct attribute
    ::Bar my_bar_struct_{};
    /// Class member storing value of my_default_bar_struct attribute
    ::Bar my_default_bar_struct_{};
    /// Class member storing value of my_bar_array attribute
    ::BarArray my_bar_array_{{}};
    /// Class member storing value of my_bar_array_2 attribute
    ::BarArray2 my_bar_array_2_{{}};
    /// Class member storing value of my_sequence_array attribute
    ::SequenceArray my_sequence_array_{{}};
    /// Class member storing value of my_bar_struct_array attribute
    ::BarStruct my_bar_struct_array_{};
    /// Class member storing value of my_baz_struct attribute
    ::Baz my_baz_struct_{};
    /// Class member storing value of my_data_union attribute
    ::Data my_data_union_{};
    /// Class member storing value of my_var_data_union attribute
    ::Data2 my_var_data_union_{};
    /// Class member storing value of my_struct_struct attribute
    ::StructModule::StructStruct my_struct_struct_{};
    /// Class member storing value of my_sequence_bounded_string attribute
    ::sequence_bounded_string my_sequence_bounded_string_{};
    /// Class member storing value of my_sequence_bounded_wstring attribute
    ::sequence_bounded_wstring my_sequence_bounded_wstring_{};
    /// Class member storing value of my_bounded_sequence_bounded_string attribute
    ::bounded_sequence_bounded_string my_bounded_sequence_bounded_string_{};
    /// Class member storing value of my_bounded_sequence_bounded_wstring attribute
    ::bounded_sequence_bounded_wstring my_bounded_sequence_bounded_wstring_{};
    /// Class member storing value of my_bounded_string_array attribute
    ::bounded_string_array my_bounded_string_array_{{}};
    /// Class member storing value of my_bounded_wstring_array attribute
    ::bounded_wstring_array my_bounded_wstring_array_{{}};
    /// Class member storing value of my_data_type attribute
    ::DataType my_data_type_{};
    /// Class member storing value of my_data_type_type attribute
    ::data_type_type my_data_type_type_{};
    /// Class member storing value of my_any attribute
    CORBA::Any my_any_{};
    /// Class member storing value of my_any_type attribute
    ::any_type my_any_type_{};
    /// Class member storing value of my_foo_interface attribute
    IDL::traits<::MyFoo>::ref_type my_foo_interface_{};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_private_ops]
    // Bar checkers
    bool check_bar (Bar const &bar, Bar const &check);
    bool check_bar_array (BarArray const &ba, BarArray const &ca);
    bool check_bar_array_2 ();

    // Baz checkers
    bool check_baz (Baz const &baz, Baz const &check);

    // sequence checkers
    uint16_t check_sequence_of_bounded_strings ();
    uint16_t check_bounded_sequence_of_bounded_strings ();

    // Array checkes
    uint16_t check_two_dimensional_array ();

    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Foo_exec_i(const Foo_exec_i&) = delete;
    Foo_exec_i(Foo_exec_i&&) = delete;
    Foo_exec_i& operator=(const Foo_exec_i&) = delete;
    Foo_exec_i& operator=(Foo_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_end_decl]

} // namespace Foo_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[factory]
extern "C" FOO_EXEC_Export  void
create_Foo_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[Footer]

#endif /* __RIDL_FOO_EXEC_H_DIHEJGFA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
