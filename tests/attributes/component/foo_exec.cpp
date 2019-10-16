// -*- C++ -*-
/**
 * @file    foo_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 attribute test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_impl.cpp[Header]

#include "foo_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[user_includes]
#include "ace/ACE.h"
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[user_global_impl]

namespace Base_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Base_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[ctor]
  Base_exec_i::Base_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[ctor]

  Base_exec_i::~Base_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[user_private_ops]

  /** Session component operations */
  void Base_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[configuration_complete]
  }

  void Base_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[ccm_activate]
  }

  void Base_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[ccm_passivate]
  }

  void Base_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[ccm_remove]
  }


  int16_t
  Base_exec_i::m_base_pt_base_pt ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i::m_base_pt_base_pt[getter]
    return this->m_base_pt_base_pt_;
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i::m_base_pt_base_pt[getter]
  }

  void
  Base_exec_i::m_base_pt_base_pt (
      int16_t m_base_pt_base_pt)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i::m_base_pt_base_pt[setter]
    this->m_base_pt_base_pt_ = m_base_pt_base_pt;
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i::m_base_pt_base_pt[setter]
  }

  int16_t
  Base_exec_i::attr_base ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i::attr_base[getter]
    return this->attr_base_;
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i::attr_base[getter]
  }

  void
  Base_exec_i::attr_base (
      int16_t attr_base)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i::attr_base[setter]
    this->attr_base_ = attr_base;
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i::attr_base[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Base_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl::Base_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_Base_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl::Base_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[user_namespace_end_impl]

} // namespace Base_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Base_Impl[factory]
extern "C" void
create_Base_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Base_Impl::Base_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Base_Impl[factory]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_global_impl]

namespace Foo_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_impl]
  template<typename ARRAY, typename MULTIPLIER_TYPE, typename SIZE_TYPE>
  class check_array
  {
  public:
    check_array () {}

    static bool
    check (ARRAY const &array, std::string const &name,
      MULTIPLIER_TYPE multiplier, SIZE_TYPE size)
    {
      bool ret = true;

      if (array.size () != size)
      {
        CIAOX11_TEST_ERROR << "ERROR: Unexpected size of <" << name
          << ">. Expected <" << size << "> - found <"
          << array.size () << ">." << std::endl;
        ret = false;
      }

      for (SIZE_TYPE i = 0; i < array.size (); ++i)
      {
        if (array[i] != static_cast<MULTIPLIER_TYPE> ((i+1)*multiplier))
          {
          CIAOX11_TEST_ERROR << "ERROR: " << name << "[" << i << "]!= "
          << (i+1)*multiplier << ", it is " << array[i]<< std::endl;
          ret = false;
        }
      }
      return ret;
    }
  };

  // Check for static lists (array or sequences). Static means 'no calculations'
  template<typename LIST>
  class check_static_list
  {
  public:
    check_static_list () {}

    static bool
    check (LIST const &list, std::string const &name, LIST const &check)
    {
      bool ret = true;

      if (list.size () != check.size ())
      {
        CIAOX11_TEST_ERROR << "ERROR: Unexpected size of <" << name
          << ">. Expected <" << check.size () << "> - found <"
          << list.size () << ">." << std::endl;
        ret = false;
      }

      if (list != check)
      {
        CIAOX11_TEST_ERROR << "ERROR: " << name << " != " << check << ", it is "
          << list << std::endl;
        ret = false;
      }
      return ret;
    }
  };

  // Check for static string lists (array or sequences), containing "Hello World", "Bye World"
  template<typename LIST, typename TYPE_IN_LIST>
  class check_hello_bye_world_list
  {
  public:
    check_hello_bye_world_list () {}

    static bool
    check (LIST const &list, LIST const &check, std::string const &name)
    {
      if (!check_static_list<const LIST>::check (list, name, check))
      {
        CIAOX11_TEST_ERROR << "ERROR: " << name << " != " << check << " , it is "
          << list << std::endl;
        return false;
      }

      // Double check the sequence.
      if (!check_static_list<const TYPE_IN_LIST>::check (list[0], name+"[0]", check[0]))
      {
        CIAOX11_TEST_ERROR << "ERROR: " << name << "[0] != " << check[0] << " , it is "
          << list[0] << std::endl;
        return false;
      }

      if (!check_static_list<const TYPE_IN_LIST>::check (list[1], name+"[1]", check[1]))
      {
        CIAOX11_TEST_ERROR << "ERROR: " << name << "[1] != " << check[1] << " , it is "
          << list[1] << std::endl;
        return false;
      }

      return true;
    }
  };

  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Foo_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ctor]
  Foo_exec_i::Foo_exec_i ()
   : readonly_short_ (100)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ctor]

  Foo_exec_i::~Foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_private_ops]
  bool
  Foo_exec_i::check_bar (Bar const &bar, Bar const &check)
  {
    return bar.s () == check.s () &&
      bar.l () == check.l () &&
      ACE::is_equal (bar.f (), check.f ()) &&
      ACE::is_equal (bar.d (), check.d ());
  }

  bool
  Foo_exec_i::check_bar_array (BarArray const &ba, BarArray const &ca)
  {
    bool ret = true;
    for (BarArray::size_type i = 0; i < ba.size () && ret; ++i)
    {
      ret = this->check_bar (ba[i], ca[i]);
    }
    return ret;
  }

  bool
  Foo_exec_i::check_bar_array_2 ()
  {
    BarArray2 const check = { {
      { { Bar { 1, 2, 3.4F, 5.6 }, Bar { 2, 3, 4.5F, 6.7 }, Bar { 3, 4, 5.6F, 7.8 } } },
      { { Bar {11, 12, 13.4F, 15.6}, Bar {12, 13, 14.5F, 16.7}, Bar {13, 14, 15.6F, 17.8} } }
    } };

    bool ret = this->check_bar_array (this->my_bar_array_2 ()[0], check[0]);
    ret &= this->check_bar_array (this->my_bar_array_2 ()[1], check[1]);
    return ret;
  }

  bool
  Foo_exec_i::check_baz (Baz const &baz, Baz const &check)
  {
    bool ret = baz.name () == check.name ();

    if (baz.my_bar_sequence ().size () != 5)
    {
      CIAOX11_TEST_ERROR << "ERROR: Unexpected size of <my_bar_sequence> in Baz struct. "
        << "Expected <" << check.my_bar_sequence ().size () << "> - found <"
        << baz.my_bar_sequence ().size () << ">." << std::endl;
      ret = false;
    }

    if (!IDL::traits< BarSeq >::is_bounded ())
    {
      CIAOX11_TEST_ERROR << "ERROR: <my_bar_sequence> is not bounded. " << std::endl;
      ret = false;
    }

    for (BarSeq::size_type i = 0; i < baz.my_bar_sequence ().size () && ret; ++i)
    {
      ret = this->check_bar (baz.my_bar_sequence ()[i], check.my_bar_sequence ()[i]);
    }
    return ret;
  }

  uint16_t
  Foo_exec_i::check_sequence_of_bounded_strings ()
  {
    uint16_t error = 0;

    if (IDL::traits< sequence_bounded_string >::is_bounded ())
    {
      CIAOX11_TEST_ERROR << "ERROR: my_sequence_bounded_string should not be "
        "bounded" << std::endl;
      ++error;
    }

    if (IDL::traits< bounded_string >::bound () != 50)
    {
      CIAOX11_TEST_ERROR << "ERROR: Unexpected bound of <bounded_string> "
        << "Expected <50> - found <"
        << IDL::traits< bounded_string >::bound ()
        << ">." << std::endl;
      ++error;
    }

    if (this->my_sequence_bounded_string ().size () != 2)
    {
      CIAOX11_TEST_ERROR << "ERROR: Unexpected size of <my_bar_sequence>. "
        << "Expected <2> - found <"
        << this->my_sequence_bounded_string ().size ()
        << ">." << std::endl;
      return ++error;
    }

    if (this->my_sequence_bounded_string ()[0] != "Hi")
    {
      CIAOX11_TEST_ERROR << "ERROR: my_sequence_bounded_string[0] != \"Hi\", it is "
        << this->my_sequence_bounded_string ()[0] << std::endl;
      ++error;
    }
    if (this->my_sequence_bounded_string ()[1] != "World")
    {
      CIAOX11_TEST_ERROR << "ERROR: my_sequence_bounded_string[1] != \"World\", it is "
        << this->my_sequence_bounded_string ()[1] << std::endl;
      ++error;
    }
    return error;
  }

  uint16_t
  Foo_exec_i::check_bounded_sequence_of_bounded_strings ()
  {
    uint16_t error = 0;
    if (!IDL::traits< bounded_sequence_bounded_string >::is_bounded ())
    {
      CIAOX11_TEST_ERROR << "ERROR: bounded_sequence_bounded_string should be "
        "bounded" << std::endl;
      ++error;
    }

    if (IDL::traits< bounded_sequence_bounded_string >::bound () != 5)
    {
      CIAOX11_TEST_ERROR << "ERROR: Unexpected bound for bounded_sequence_bounded_string. "
        << "Expected <5> - found <"
        << IDL::traits< bounded_sequence_bounded_string >::bound ()
        << ">." << std::endl;
      ++error;
    }

    bounded_sequence_bounded_string check { "Hi", "World" };
    if (this->my_bounded_sequence_bounded_string () != check)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_bounded_sequence_bounded_string != " << check << ", it is "
        << this->my_bounded_sequence_bounded_string () << std::endl;
      ++error;
    }
    return error;
  }

  uint16_t
  Foo_exec_i::check_two_dimensional_array ()
  {
    uint16_t error = 0;

    multi_dimensional_short_array const multi_dimensional_short_array_check =
    {{
      { {10, 20, 30, 40, 50} },
      { {15, 30, 45, 60, 75} }
    }};

    std::integral_constant<uint32_t, 2> const two_dimensions;
    if (IDL::traits< multi_dimensional_short_array >::dimensions () != two_dimensions)
    {
      CIAOX11_TEST_ERROR << "ERROR: Unexpected dimension found. Expected <"
        << two_dimensions << "> - found <" << IDL::traits< multi_dimensional_short_array >::dimensions ()
        << ">." << std::endl;
      ++error;
    }


    // Check one by one.
    for (multi_dimensional_short_array::size_type arr = 0; arr < this->my_multi_dimensional_short_array ().size (); ++arr)
    {
      if (!check_array<const short_array,
        int16_t, short_array::size_type>::check (
          this->my_multi_dimensional_short_array ()[arr],
          "my_multi_dimensional_short_array["+std::to_string (arr)+"]",
          ACE_Utils::truncate_cast<int16_t> (5 * (arr+2)), 5))
      {
        // Error is already logged in check_array.
        ++error;
      }
    }

    // Check the array as a whole
    if (this->my_multi_dimensional_short_array () != multi_dimensional_short_array_check)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_multi_dimensional_short_array != "
        << multi_dimensional_short_array_check << ", it is "
        << this->my_multi_dimensional_short_array () << std::endl;
      ++error;
    }

    return error;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_private_ops]

  /** Session component operations */
  void Foo_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[configuration_complete]
  }

  void Foo_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_activate]
  }

  void Foo_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_passivate]
  }

  void Foo_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_remove]

    // Not checked. Generation purpose only
    // the_byte_get_set_raise
    // the_byte_set_raise
    // the_byte_get_raise
    // readonly_short_raise

    // Not supported since it's NOT configured in the XSD.
    // my_char
    // my_bounded_wstring
    // my_variable_wstring
    // my_wstring_array ())
    // my_char_array ())
    // my_wchar_array ())
    // my_bounded_sequence_bounded_wstring
    // my_sequence_bounded_wstring
    // my_bounded_wstring_array

    // Not supported.
    // my_data_union ()
    // my_var_data_union ()
    // my_foo_interface ()
    // my_any

    // Long double is not supported since a longdouble is defined in the xsd as double.
    // We are then creating a long double initialized with a regular
    // double. This is a very tricky conversion and doesn't work in
    // combination with certain (versions of) compilers.
    // Therefor no check for
    // my_longdouble
    // my_longdouble_array

    uint16_t error = 0;

    if (this->m_base_pt_base_pt () != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: m_base_pt_base_pt != 22, it is "
        << this->m_base_pt_base_pt () << std::endl;
      ++error;
    }
    if (this->attr_base () != 23)
    {
      CIAOX11_TEST_ERROR << "ERROR: attr_base != 23, it is "
        << this->attr_base () << std::endl;
      ++error;
    }
    if (this->readonly_short () != 100)
    {
      CIAOX11_TEST_ERROR << "ERROR: readonly_short != 100, it is "
        << this->readonly_short () << std::endl;
      ++error;
    }
    if (this->my_octet () != 20)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_octet != 20, it is "
        << this->my_octet () << std::endl;
      ++error;
    }
    if (!this->my_boolean ())
    {
      CIAOX11_TEST_ERROR << "ERROR: my_boolean != true, it is "
        << this->my_boolean () << std::endl;
      ++error;
    }
    if (this->my_short () != 24)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_short != 24, it is "
        << this->my_short () << std::endl;
      ++error;
    }
    if (this->my_long () != 33)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_long != 33, it is "
        << this->my_long () << std::endl;
      ++error;
    }
    if (ACE::is_inequal (this->my_float (), 45.67F))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_float != 45.67F, it is "
        << this->my_float () << std::endl;
      ++error;
    }
    if (ACE::is_inequal (this->my_double (), 56.78))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_double != 56.78, it is "
        << this->my_double () << std::endl;
      ++error;
    }
    if (this->my_ulong () != 34)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_ulong != 34, it is "
        << this->my_ulong () << std::endl;
      ++error;
    }
    if (this->my_longlong () != 35)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_longlong != 35, it is "
        << this->my_longlong () << std::endl;
      ++error;
    }
    if (this->my_ulonglong () != 36)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_ulonglong != 36, it is "
        << this->my_ulonglong () << std::endl;
      ++error;
    }
    if (this->my_default_char () != '\0')
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_char != '\\0', it is "
        << this->my_default_char () << std::endl;
      ++error;
    }
    if (this->my_default_octet () != 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_octet != 0, it is "
        << this->my_default_octet () << std::endl;
      ++error;
    }
    if (this->my_default_boolean ())
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_boolean != false, it is "
        << this->my_default_boolean () << std::endl;
      ++error;
    }
    if (this->my_default_short () != 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_short != 0, it is "
        << this->my_default_short () << std::endl;
      ++error;
    }
    if (this->my_default_long () != 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_long != 0, it is "
        << this->my_default_long () << std::endl;
      ++error;
    }
    if (ACE::is_inequal (this->my_default_float (), 0.0F))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_float != 0.0F, it is "
        << this->my_default_float () << std::endl;
      ++error;
    }
    if (ACE::is_inequal (this->my_default_double (), 0.0))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_double != 0.0, it is "
        << this->my_default_double () << std::endl;
      ++error;
    }
    if (this->my_default_ulong () != 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_ulong != 0, it is "
        << this->my_default_ulong () << std::endl;
      ++error;
    }
    if (this->my_default_longlong () != 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_longlong != 0, it is "
        << this->my_default_longlong () << std::endl;
      ++error;
    }
    if (this->my_default_ulonglong () != 0)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_ulonglong != 0, it is "
        << this->my_default_ulonglong () << std::endl;
      ++error;
    }

    if (ACE::is_inequal (this->my_default_longdouble (), 0.0L))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_longdouble != 0.0, it is "
        << this->my_default_longdouble () << std::endl;
      ++error;
    }
    if (this->my_bounded_string () != "Hi")
    {
      CIAOX11_TEST_ERROR << "ERROR: my_bounded_string != \"Hi\", it is \""
        << this->my_bounded_string () << "\"" << std::endl;
      ++error;
    }
    if (this->my_variable_string () != "Bye")
    {
      CIAOX11_TEST_ERROR << "ERROR: my_variable_string != \"Bye\", it is \""
        << this->my_variable_string () << "\"" << std::endl;
      ++error;
    }
    if (!this->my_default_variable_string ().empty ())
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_variable_string is not empty, it is \""
        << this->my_default_variable_string () << "\"" << std::endl;
      ++error;
    }

    if (!check_array<const long_array, int32_t, long_array::size_type>::check (
      this->my_long_array (), "my_long_array", 1, 5))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_long_array. Expected "
        << this->my_long_array () << std::endl;
      ++error;
    }
    if (!check_array<const ulong_array, uint32_t, ulong_array::size_type>::check (
      this->my_ulong_array (), "my_ulong_array", 2, 5))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_ulong_array. Expected "
        << this->my_ulong_array () << std::endl;
      ++error;
    }
    if (!check_array<const longlong_array, int64_t, longlong_array::size_type>::check (
      this->my_longlong_array (), "my_longlong_array", 3, 5))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_longlong_array. Expected "
        << this->my_longlong_array () << std::endl;
      ++error;
    }
    if (!check_array<const ulonglong_array, uint64_t, ulonglong_array::size_type>::check (
      this->my_ulonglong_array (), "my_ulonglong_array", 4, 5))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_ulonglong_array. Expected "
        << this->my_ulonglong_array () << std::endl;
      ++error;
    }
    if (!check_array<const short_array, int16_t, short_array::size_type>::check (
      this->my_short_array (), "my_short_array", 5, 5))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_short_array. Expected "
        << this->my_short_array () << std::endl;
      ++error;
    }
    if (!check_array<const ushort_array, uint16_t, ushort_array::size_type>::check (
      this->my_ushort_array (), "my_ushort_array", 6, 5))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_ushort_array. Expected "
        << this->my_ushort_array () << std::endl;
      ++error;
    }

    string_array const string_array_check {{ "Hello", "World" }};
    if (!check_static_list<const string_array>::check (this->my_string_array (), "my_string_array", string_array_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_string_array. Expected "
        << this->my_string_array () << std::endl;
      ++error;
    }

    if (!check_array<const short_array, int16_t, short_array::size_type>::check (
      this->my_short_array (), "my_short_array", 5, 5))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_short_array. Expected "
        << this->my_short_array () << std::endl;
      ++error;
    }

    double_array const double_array_check {{ 0.123, 4.56, 78.9 }};
    if (!check_static_list<const double_array>::check (this->my_double_array (), "my_double_array", double_array_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_double_array. Expected "
        << this->my_double_array () << std::endl;
      ++error;
    }

    float_array const float_array_check {{ 0.369F, 13.68F, 236.7F }};
    if (!check_static_list<const float_array>::check (this->my_float_array (), "my_float_array", float_array_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_float_array. Expected "
        << this->my_float_array () << std::endl;
      ++error;
    }

    boolean_array const boolean_array_check {{ true, false }};
    if (!check_static_list<const boolean_array>::check (this->my_boolean_array (), "my_boolean_array", boolean_array_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_boolean_array. Expected "
        << this->my_boolean_array () << std::endl;
      ++error;
    }

    octet_array const octet_array_check {{ 1, 2 }};
    if (!check_static_list<const octet_array>::check (this->my_octet_array (), "my_octet_array", octet_array_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_octet_array. Expected "
        << this->my_octet_array () << std::endl;
      ++error;
    }

    error += this->check_two_dimensional_array ();

    short_sequence const short_sequence_check { 11, 12, 13 };
    if (!check_static_list<const short_sequence>::check (this->my_short_sequence (), "my_short_sequence", short_sequence_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_short_sequence. Expected "
        << this->my_short_sequence () << std::endl;
      ++error;
    }

    long_sequence const long_sequence_check { 21, 22, 23 };
    if (!check_static_list<const long_sequence>::check (this->my_long_sequence (), "my_long_sequence", long_sequence_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_long_sequence. Expected "
        << this->my_long_sequence () << std::endl;
      ++error;
    }

    float_sequence const float_sequence_check { 21.12F, 22.22F, 23.32F };
    if (!check_static_list<const float_sequence>::check (this->my_float_sequence (), "my_float_sequence", float_sequence_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_float_sequence. Expected "
        << this->my_float_sequence () << std::endl;
      ++error;
    }

    double_sequence const double_sequence_check { 621.12, 622.22, 623.32 };
    if (!check_static_list<const double_sequence>::check (this->my_double_sequence (), "my_double_sequence", double_sequence_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_double_sequence. Expected "
        << this->my_double_sequence () << std::endl;
      ++error;
    }

    string_sequence const string_sequence_check { "Hi", "World" };
    if (!check_static_list<const string_sequence>::check (this->my_string_sequence (), "my_string_sequence", string_sequence_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_string_sequence. Expected "
        << this->my_string_sequence () << std::endl;
      ++error;
    }

    // sequence
    string_sequence const hello_sequence { "Hi", "World" };
    string_sequence const bye_sequence   { "Bye", "World" };
    // array
    string_array const hello_array {{ "Hi", "World" }};
    string_array const bye_array {{ "Bye", "World" }};

    string_sequence2 const check_string_sequence { hello_sequence, bye_sequence };
    if (!check_hello_bye_world_list<string_sequence2, string_sequence>::check (
      this->my_string_sequence_2 (), check_string_sequence, "my_string_sequence_2"))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_string_sequence_2. Expected "
        << this->my_string_sequence_2 () << std::endl;
      ++error;
    }

    array_sequence const check_string_array { hello_array, bye_array };
    if (!check_hello_bye_world_list<array_sequence, string_array>::check (
      this->my_array_sequence (), check_string_array, "my_array_sequence"))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_array_sequence. Expected "
        << this->my_array_sequence () << std::endl;
      ++error;
    }

    Bar const bar_check (3, 4, 5.6F, 7.8);
    if (!this->check_bar (this->my_bar_struct (), bar_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_bar_struct != " << bar_check << ", it is "
        << this->my_bar_struct () << std::endl;
      ++error;
    }
    Bar const default_bar_check (0, 0, 0.0F, 0.0);
    if (!this->check_bar (this->my_default_bar_struct (), default_bar_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_default_bar_struct != " << default_bar_check << ", it is "
        << this->my_default_bar_struct () << std::endl;
      ++error;
    }

    BarArray const bar_array_check = { {
      Bar {1, 2, 3.4F, 5.6},
      Bar {2, 3, 4.5F, 6.7},
      Bar {3, 4, 5.6F, 7.8}
    } };
    if (!this->check_bar_array (this->my_bar_array (), bar_array_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_bar_array != " << bar_array_check << ", it is "
        << this->my_bar_array () << std::endl;
      ++error;
    }

    if (!this->check_bar_array_2 ())
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_bar_array_2. Expected "
        << this->my_bar_array_2 () << std::endl;
      ++error;
    }

    SequenceArray const check_sequence_array {{ hello_sequence, bye_sequence }};
    if (!check_hello_bye_world_list<SequenceArray, string_sequence>::check (
      this->my_sequence_array (), check_sequence_array, "my_sequence_array"))
    {
      CIAOX11_TEST_ERROR << "ERROR: unexpected values in my_sequence_array. Expected "
        << this->my_sequence_array () << std::endl;
      ++error;
    }

    // Same as the bar array
    if (!this->check_bar_array (this->my_bar_struct_array ().bar (), bar_array_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_bar_struct_array != " << bar_array_check << ", it is "
        << this->my_bar_struct_array () << std::endl;
      ++error;
    }

    BarSeq bar_seq_check {
      Bar (3, 4, 5.6F, 7.8),
      Bar (13, 14, 15.6F, 17.8),
      Bar (23, 24, 25.6F, 27.8),
      Bar (33, 34, 35.6F, 37.8),
      Bar (43, 44, 45.6F, 47.8)
    };
    Baz const baz_check ("My Baz Struct", bar_seq_check);
    if (!this->check_baz (this->my_baz_struct (), baz_check))
    {
      CIAOX11_TEST_ERROR << "ERROR: my_baz_struct != " << baz_check << ", it is "
        << this->my_baz_struct () << std::endl;
      ++error;
    }

    StructModule::Time const tm (15, 20);
    StructModule::StructStruct struct_struct_check (tm, StructModule::EndTime::DLT_HARD);
    if (this->my_struct_struct ().struct_time ().sec () != tm.sec () ||
      this->my_struct_struct ().struct_time ().nanosec () != tm.nanosec () ||
      this->my_struct_struct ().type () != struct_struct_check.type ())
    {
      CIAOX11_TEST_ERROR << "ERROR: my_struct_struct != " << struct_struct_check << ", it is "
        << this->my_struct_struct () << std::endl;
      ++error;
    }

    this->check_sequence_of_bounded_strings ();
    this->check_bounded_sequence_of_bounded_strings ();

    bounded_string_array const check_bounded_string_array {{ "Hello", "World" }};
    if (this->my_bounded_string_array () != check_bounded_string_array)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_bounded_string_array != " << check_bounded_string_array << ", it is "
        << this->my_bounded_string_array () << std::endl;
      ++error;
    }

    if (this->my_data_type () != ::DataType::dtLong)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_data_type != ::DataType::dtLong, it is "
        << this->my_data_type () << std::endl;
      ++error;
    }

    if (this->my_data_type_type () != ::DataType::dtShort)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_data_type_type != ::DataType::dtShort, it is "
        << this->my_data_type_type () << std::endl;
      ++error;
    }

    if (this->my_foo_interface () != nullptr)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_foo_interface != nullptr, it is "
        << this->my_foo_interface () << std::endl;
      ++error;
    }

    if (error == 0)
    {
      CIAOX11_TEST_INFO << "OK, no errors found in test." << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR: <" << error << "> errors found in test." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_remove]
  }


  int16_t
  Foo_exec_i::m_base_pt_base_pt ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_base_pt_base_pt[getter]
    return this->m_base_pt_base_pt_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_base_pt_base_pt[getter]
  }

  void
  Foo_exec_i::m_base_pt_base_pt (
      int16_t m_base_pt_base_pt)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_base_pt_base_pt[setter]
    this->m_base_pt_base_pt_ = m_base_pt_base_pt;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_base_pt_base_pt[setter]
  }

  int16_t
  Foo_exec_i::attr_base ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::attr_base[getter]
    return this->attr_base_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::attr_base[getter]
  }

  void
  Foo_exec_i::attr_base (
      int16_t attr_base)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::attr_base[setter]
    this->attr_base_ = attr_base;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::attr_base[setter]
  }

  int16_t
  Foo_exec_i::m_foo_pt_foo_pt ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_foo_pt_foo_pt[getter]
    return this->m_foo_pt_foo_pt_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_foo_pt_foo_pt[getter]
  }

  void
  Foo_exec_i::m_foo_pt_foo_pt (
      int16_t m_foo_pt_foo_pt)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_foo_pt_foo_pt[setter]
    this->m_foo_pt_foo_pt_ = m_foo_pt_foo_pt;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_foo_pt_foo_pt[setter]
  }

  uint8_t
  Foo_exec_i::the_byte_get_set_raise ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::the_byte_get_set_raise[getter]
    return this->the_byte_get_set_raise_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::the_byte_get_set_raise[getter]
  }

  void
  Foo_exec_i::the_byte_get_set_raise (
      uint8_t the_byte_get_set_raise)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::the_byte_get_set_raise[setter]
    this->the_byte_get_set_raise_ = the_byte_get_set_raise;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::the_byte_get_set_raise[setter]
  }

  uint8_t
  Foo_exec_i::the_byte_set_raise ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::the_byte_set_raise[getter]
    return this->the_byte_set_raise_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::the_byte_set_raise[getter]
  }

  void
  Foo_exec_i::the_byte_set_raise (
      uint8_t the_byte_set_raise)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::the_byte_set_raise[setter]
    this->the_byte_set_raise_ = the_byte_set_raise;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::the_byte_set_raise[setter]
  }

  uint8_t
  Foo_exec_i::the_byte_get_raise ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::the_byte_get_raise[getter]
    return this->the_byte_get_raise_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::the_byte_get_raise[getter]
  }

  void
  Foo_exec_i::the_byte_get_raise (
      uint8_t the_byte_get_raise)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::the_byte_get_raise[setter]
    this->the_byte_get_raise_ = the_byte_get_raise;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::the_byte_get_raise[setter]
  }

  int16_t
  Foo_exec_i::readonly_short_raise ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::readonly_short_raise[getter]
    return this->readonly_short_raise_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::readonly_short_raise[getter]
  }

  int16_t
  Foo_exec_i::readonly_short ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::readonly_short[getter]
    return this->readonly_short_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::readonly_short[getter]
  }

  char
  Foo_exec_i::my_char ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_char[getter]
    return this->my_char_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_char[getter]
  }

  void
  Foo_exec_i::my_char (
      char my_char)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_char[setter]
    this->my_char_ = my_char;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_char[setter]
  }

  uint8_t
  Foo_exec_i::my_octet ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_octet[getter]
    return this->my_octet_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_octet[getter]
  }

  void
  Foo_exec_i::my_octet (
      uint8_t my_octet)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_octet[setter]
    this->my_octet_ = my_octet;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_octet[setter]
  }

  bool
  Foo_exec_i::my_boolean ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_boolean[getter]
    return this->my_boolean_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_boolean[getter]
  }

  void
  Foo_exec_i::my_boolean (
      bool my_boolean)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_boolean[setter]
    this->my_boolean_ = my_boolean;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_boolean[setter]
  }

  int16_t
  Foo_exec_i::my_short ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_short[getter]
    return this->my_short_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_short[getter]
  }

  void
  Foo_exec_i::my_short (
      int16_t my_short)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_short[setter]
    this->my_short_ = my_short;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_short[setter]
  }

  int32_t
  Foo_exec_i::my_long ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_long[getter]
    return this->my_long_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_long[getter]
  }

  void
  Foo_exec_i::my_long (
      int32_t my_long)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_long[setter]
    this->my_long_ = my_long;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_long[setter]
  }

  float
  Foo_exec_i::my_float ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_float[getter]
    return this->my_float_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_float[getter]
  }

  void
  Foo_exec_i::my_float (
      float my_float)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_float[setter]
    this->my_float_ = my_float;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_float[setter]
  }

  double
  Foo_exec_i::my_double ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_double[getter]
    return this->my_double_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_double[getter]
  }

  void
  Foo_exec_i::my_double (
      double my_double)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_double[setter]
    this->my_double_ = my_double;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_double[setter]
  }

  uint32_t
  Foo_exec_i::my_ulong ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulong[getter]
    return this->my_ulong_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulong[getter]
  }

  void
  Foo_exec_i::my_ulong (
      uint32_t my_ulong)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulong[setter]
    this->my_ulong_ = my_ulong;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulong[setter]
  }

  int64_t
  Foo_exec_i::my_longlong ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longlong[getter]
    return this->my_longlong_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longlong[getter]
  }

  void
  Foo_exec_i::my_longlong (
      int64_t my_longlong)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longlong[setter]
    this->my_longlong_ = my_longlong;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longlong[setter]
  }

  uint64_t
  Foo_exec_i::my_ulonglong ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulonglong[getter]
    return this->my_ulonglong_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulonglong[getter]
  }

  void
  Foo_exec_i::my_ulonglong (
      uint64_t my_ulonglong)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulonglong[setter]
    this->my_ulonglong_ = my_ulonglong;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulonglong[setter]
  }

  char
  Foo_exec_i::my_default_char ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_char[getter]
    return this->my_default_char_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_char[getter]
  }

  void
  Foo_exec_i::my_default_char (
      char my_default_char)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_char[setter]
    this->my_default_char_ = my_default_char;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_char[setter]
  }

  uint8_t
  Foo_exec_i::my_default_octet ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_octet[getter]
    return this->my_default_octet_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_octet[getter]
  }

  void
  Foo_exec_i::my_default_octet (
      uint8_t my_default_octet)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_octet[setter]
    this->my_default_octet_ = my_default_octet;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_octet[setter]
  }

  bool
  Foo_exec_i::my_default_boolean ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_boolean[getter]
    return this->my_default_boolean_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_boolean[getter]
  }

  void
  Foo_exec_i::my_default_boolean (
      bool my_default_boolean)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_boolean[setter]
    this->my_default_boolean_ = my_default_boolean;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_boolean[setter]
  }

  int16_t
  Foo_exec_i::my_default_short ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_short[getter]
    return this->my_default_short_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_short[getter]
  }

  void
  Foo_exec_i::my_default_short (
      int16_t my_default_short)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_short[setter]
    this->my_default_short_ = my_default_short;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_short[setter]
  }

  int32_t
  Foo_exec_i::my_default_long ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_long[getter]
    return this->my_default_long_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_long[getter]
  }

  void
  Foo_exec_i::my_default_long (
      int32_t my_default_long)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_long[setter]
    this->my_default_long_ = my_default_long;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_long[setter]
  }

  float
  Foo_exec_i::my_default_float ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_float[getter]
    return this->my_default_float_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_float[getter]
  }

  void
  Foo_exec_i::my_default_float (
      float my_default_float)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_float[setter]
    this->my_default_float_ = my_default_float;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_float[setter]
  }

  double
  Foo_exec_i::my_default_double ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_double[getter]
    return this->my_default_double_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_double[getter]
  }

  void
  Foo_exec_i::my_default_double (
      double my_default_double)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_double[setter]
    this->my_default_double_ = my_default_double;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_double[setter]
  }

  uint32_t
  Foo_exec_i::my_default_ulong ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_ulong[getter]
    return this->my_default_ulong_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_ulong[getter]
  }

  void
  Foo_exec_i::my_default_ulong (
      uint32_t my_default_ulong)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_ulong[setter]
    this->my_default_ulong_ = my_default_ulong;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_ulong[setter]
  }

  int64_t
  Foo_exec_i::my_default_longlong ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_longlong[getter]
    return this->my_default_longlong_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_longlong[getter]
  }

  void
  Foo_exec_i::my_default_longlong (
      int64_t my_default_longlong)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_longlong[setter]
    this->my_default_longlong_ = my_default_longlong;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_longlong[setter]
  }

  uint64_t
  Foo_exec_i::my_default_ulonglong ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_ulonglong[getter]
    return this->my_default_ulonglong_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_ulonglong[getter]
  }

  void
  Foo_exec_i::my_default_ulonglong (
      uint64_t my_default_ulonglong)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_ulonglong[setter]
    this->my_default_ulonglong_ = my_default_ulonglong;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_ulonglong[setter]
  }

  long double
  Foo_exec_i::my_longdouble ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longdouble[getter]
    return this->my_longdouble_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longdouble[getter]
  }

  void
  Foo_exec_i::my_longdouble (
      long double my_longdouble)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longdouble[setter]
    this->my_longdouble_ = my_longdouble;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longdouble[setter]
  }

  long double
  Foo_exec_i::my_default_longdouble ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_longdouble[getter]
    return this->my_default_longdouble_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_longdouble[getter]
  }

  void
  Foo_exec_i::my_default_longdouble (
      long double my_default_longdouble)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_longdouble[setter]
    this->my_default_longdouble_ = my_default_longdouble;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_longdouble[setter]
  }

  ::bounded_string
  Foo_exec_i::my_bounded_string ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_string[getter]
    return this->my_bounded_string_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_string[getter]
  }

  void
  Foo_exec_i::my_bounded_string (
      const ::bounded_string& my_bounded_string)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_string[setter]
    this->my_bounded_string_ = my_bounded_string;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_string[setter]
  }

  std::string
  Foo_exec_i::my_variable_string ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_variable_string[getter]
    return this->my_variable_string_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_variable_string[getter]
  }

  void
  Foo_exec_i::my_variable_string (
      const std::string& my_variable_string)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_variable_string[setter]
    this->my_variable_string_ = my_variable_string;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_variable_string[setter]
  }

  std::string
  Foo_exec_i::my_default_variable_string ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_variable_string[getter]
    return this->my_default_variable_string_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_variable_string[getter]
  }

  void
  Foo_exec_i::my_default_variable_string (
      const std::string& my_default_variable_string)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_variable_string[setter]
    this->my_default_variable_string_ = my_default_variable_string;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_variable_string[setter]
  }

  ::bounded_wstring
  Foo_exec_i::my_bounded_wstring ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_wstring[getter]
    return this->my_bounded_wstring_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_wstring[getter]
  }

  void
  Foo_exec_i::my_bounded_wstring (
      const ::bounded_wstring& my_bounded_wstring)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_wstring[setter]
    this->my_bounded_wstring_ = my_bounded_wstring;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_wstring[setter]
  }

  std::wstring
  Foo_exec_i::my_variable_wstring ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_variable_wstring[getter]
    return this->my_variable_wstring_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_variable_wstring[getter]
  }

  void
  Foo_exec_i::my_variable_wstring (
      const std::wstring& my_variable_wstring)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_variable_wstring[setter]
    this->my_variable_wstring_ = my_variable_wstring;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_variable_wstring[setter]
  }

  ::long_array
  Foo_exec_i::my_long_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_long_array[getter]
    return this->my_long_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_long_array[getter]
  }

  void
  Foo_exec_i::my_long_array (
      const ::long_array& my_long_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_long_array[setter]
    this->my_long_array_ = my_long_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_long_array[setter]
  }

  ::ulong_array
  Foo_exec_i::my_ulong_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulong_array[getter]
    return this->my_ulong_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulong_array[getter]
  }

  void
  Foo_exec_i::my_ulong_array (
      const ::ulong_array& my_ulong_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulong_array[setter]
    this->my_ulong_array_ = my_ulong_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulong_array[setter]
  }

  ::longlong_array
  Foo_exec_i::my_longlong_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longlong_array[getter]
    return this->my_longlong_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longlong_array[getter]
  }

  void
  Foo_exec_i::my_longlong_array (
      const ::longlong_array& my_longlong_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longlong_array[setter]
    this->my_longlong_array_ = my_longlong_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longlong_array[setter]
  }

  ::ulonglong_array
  Foo_exec_i::my_ulonglong_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulonglong_array[getter]
    return this->my_ulonglong_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulonglong_array[getter]
  }

  void
  Foo_exec_i::my_ulonglong_array (
      const ::ulonglong_array& my_ulonglong_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ulonglong_array[setter]
    this->my_ulonglong_array_ = my_ulonglong_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ulonglong_array[setter]
  }

  ::short_array
  Foo_exec_i::my_short_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_short_array[getter]
    return this->my_short_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_short_array[getter]
  }

  void
  Foo_exec_i::my_short_array (
      const ::short_array& my_short_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_short_array[setter]
    this->my_short_array_ = my_short_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_short_array[setter]
  }

  ::ushort_array
  Foo_exec_i::my_ushort_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ushort_array[getter]
    return this->my_ushort_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ushort_array[getter]
  }

  void
  Foo_exec_i::my_ushort_array (
      const ::ushort_array& my_ushort_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_ushort_array[setter]
    this->my_ushort_array_ = my_ushort_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_ushort_array[setter]
  }

  ::string_array
  Foo_exec_i::my_string_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_string_array[getter]
    return this->my_string_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_string_array[getter]
  }

  void
  Foo_exec_i::my_string_array (
      const ::string_array& my_string_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_string_array[setter]
    this->my_string_array_ = my_string_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_string_array[setter]
  }

  ::wstring_array
  Foo_exec_i::my_wstring_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_wstring_array[getter]
    return this->my_wstring_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_wstring_array[getter]
  }

  void
  Foo_exec_i::my_wstring_array (
      const ::wstring_array& my_wstring_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_wstring_array[setter]
    this->my_wstring_array_ = my_wstring_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_wstring_array[setter]
  }

  ::char_array
  Foo_exec_i::my_char_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_char_array[getter]
    return this->my_char_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_char_array[getter]
  }

  void
  Foo_exec_i::my_char_array (
      const ::char_array& my_char_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_char_array[setter]
    this->my_char_array_ = my_char_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_char_array[setter]
  }

  ::wchar_array
  Foo_exec_i::my_wchar_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_wchar_array[getter]
    return this->my_wchar_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_wchar_array[getter]
  }

  void
  Foo_exec_i::my_wchar_array (
      const ::wchar_array& my_wchar_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_wchar_array[setter]
    this->my_wchar_array_ = my_wchar_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_wchar_array[setter]
  }

  ::double_array
  Foo_exec_i::my_double_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_double_array[getter]
    return this->my_double_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_double_array[getter]
  }

  void
  Foo_exec_i::my_double_array (
      const ::double_array& my_double_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_double_array[setter]
    this->my_double_array_ = my_double_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_double_array[setter]
  }

  ::longdouble_array
  Foo_exec_i::my_longdouble_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longdouble_array[getter]
    return this->my_longdouble_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longdouble_array[getter]
  }

  void
  Foo_exec_i::my_longdouble_array (
      const ::longdouble_array& my_longdouble_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_longdouble_array[setter]
    this->my_longdouble_array_ = my_longdouble_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_longdouble_array[setter]
  }

  ::float_array
  Foo_exec_i::my_float_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_float_array[getter]
    return this->my_float_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_float_array[getter]
  }

  void
  Foo_exec_i::my_float_array (
      const ::float_array& my_float_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_float_array[setter]
    this->my_float_array_ = my_float_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_float_array[setter]
  }

  ::boolean_array
  Foo_exec_i::my_boolean_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_boolean_array[getter]
    return this->my_boolean_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_boolean_array[getter]
  }

  void
  Foo_exec_i::my_boolean_array (
      const ::boolean_array& my_boolean_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_boolean_array[setter]
    this->my_boolean_array_ = my_boolean_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_boolean_array[setter]
  }

  ::octet_array
  Foo_exec_i::my_octet_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_octet_array[getter]
    return this->my_octet_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_octet_array[getter]
  }

  void
  Foo_exec_i::my_octet_array (
      const ::octet_array& my_octet_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_octet_array[setter]
    this->my_octet_array_ = my_octet_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_octet_array[setter]
  }

  ::multi_dimensional_short_array
  Foo_exec_i::my_multi_dimensional_short_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_multi_dimensional_short_array[getter]
    return this->my_multi_dimensional_short_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_multi_dimensional_short_array[getter]
  }

  void
  Foo_exec_i::my_multi_dimensional_short_array (
      const ::multi_dimensional_short_array& my_multi_dimensional_short_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_multi_dimensional_short_array[setter]
    this->my_multi_dimensional_short_array_ = my_multi_dimensional_short_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_multi_dimensional_short_array[setter]
  }

  ::short_sequence
  Foo_exec_i::my_short_sequence ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_short_sequence[getter]
    return this->my_short_sequence_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_short_sequence[getter]
  }

  void
  Foo_exec_i::my_short_sequence (
      const ::short_sequence& my_short_sequence)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_short_sequence[setter]
    this->my_short_sequence_ = my_short_sequence;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_short_sequence[setter]
  }

  ::short_sequence
  Foo_exec_i::my_empty_sequence ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_empty_sequence[getter]
    return this->my_empty_sequence_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_empty_sequence[getter]
  }

  void
  Foo_exec_i::my_empty_sequence (
      const ::short_sequence& my_empty_sequence)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_empty_sequence[setter]
    this->my_empty_sequence_ = my_empty_sequence;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_empty_sequence[setter]
  }

  ::long_sequence
  Foo_exec_i::my_long_sequence ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_long_sequence[getter]
    return this->my_long_sequence_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_long_sequence[getter]
  }

  void
  Foo_exec_i::my_long_sequence (
      const ::long_sequence& my_long_sequence)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_long_sequence[setter]
    this->my_long_sequence_ = my_long_sequence;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_long_sequence[setter]
  }

  ::float_sequence
  Foo_exec_i::my_float_sequence ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_float_sequence[getter]
    return this->my_float_sequence_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_float_sequence[getter]
  }

  void
  Foo_exec_i::my_float_sequence (
      const ::float_sequence& my_float_sequence)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_float_sequence[setter]
    this->my_float_sequence_ = my_float_sequence;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_float_sequence[setter]
  }

  ::double_sequence
  Foo_exec_i::my_double_sequence ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_double_sequence[getter]
    return this->my_double_sequence_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_double_sequence[getter]
  }

  void
  Foo_exec_i::my_double_sequence (
      const ::double_sequence& my_double_sequence)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_double_sequence[setter]
    this->my_double_sequence_ = my_double_sequence;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_double_sequence[setter]
  }

  ::string_sequence
  Foo_exec_i::my_string_sequence ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_string_sequence[getter]
    return this->my_string_sequence_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_string_sequence[getter]
  }

  void
  Foo_exec_i::my_string_sequence (
      const ::string_sequence& my_string_sequence)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_string_sequence[setter]
    this->my_string_sequence_ = my_string_sequence;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_string_sequence[setter]
  }

  ::string_sequence2
  Foo_exec_i::my_string_sequence_2 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_string_sequence_2[getter]
    return this->my_string_sequence_2_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_string_sequence_2[getter]
  }

  void
  Foo_exec_i::my_string_sequence_2 (
      const ::string_sequence2& my_string_sequence_2)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_string_sequence_2[setter]
    this->my_string_sequence_2_ = my_string_sequence_2;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_string_sequence_2[setter]
  }

  ::array_sequence
  Foo_exec_i::my_array_sequence ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_array_sequence[getter]
    return this->my_array_sequence_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_array_sequence[getter]
  }

  void
  Foo_exec_i::my_array_sequence (
      const ::array_sequence& my_array_sequence)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_array_sequence[setter]
    this->my_array_sequence_ = my_array_sequence;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_array_sequence[setter]
  }

  ::Bar
  Foo_exec_i::my_bar_struct ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_struct[getter]
    return this->my_bar_struct_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_struct[getter]
  }

  void
  Foo_exec_i::my_bar_struct (
      const ::Bar& my_bar_struct)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_struct[setter]
    this->my_bar_struct_ = my_bar_struct;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_struct[setter]
  }

  ::Bar
  Foo_exec_i::my_default_bar_struct ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_bar_struct[getter]
    return this->my_default_bar_struct_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_bar_struct[getter]
  }

  void
  Foo_exec_i::my_default_bar_struct (
      const ::Bar& my_default_bar_struct)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_default_bar_struct[setter]
    this->my_default_bar_struct_ = my_default_bar_struct;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_default_bar_struct[setter]
  }

  ::BarArray
  Foo_exec_i::my_bar_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_array[getter]
    return this->my_bar_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_array[getter]
  }

  void
  Foo_exec_i::my_bar_array (
      const ::BarArray& my_bar_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_array[setter]
    this->my_bar_array_ = my_bar_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_array[setter]
  }

  ::BarArray2
  Foo_exec_i::my_bar_array_2 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_array_2[getter]
    return this->my_bar_array_2_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_array_2[getter]
  }

  void
  Foo_exec_i::my_bar_array_2 (
      const ::BarArray2& my_bar_array_2)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_array_2[setter]
    this->my_bar_array_2_ = my_bar_array_2;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_array_2[setter]
  }

  ::SequenceArray
  Foo_exec_i::my_sequence_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_sequence_array[getter]
    return this->my_sequence_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_sequence_array[getter]
  }

  void
  Foo_exec_i::my_sequence_array (
      const ::SequenceArray& my_sequence_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_sequence_array[setter]
    this->my_sequence_array_ = my_sequence_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_sequence_array[setter]
  }

  ::BarStruct
  Foo_exec_i::my_bar_struct_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_struct_array[getter]
    return this->my_bar_struct_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_struct_array[getter]
  }

  void
  Foo_exec_i::my_bar_struct_array (
      const ::BarStruct& my_bar_struct_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bar_struct_array[setter]
    this->my_bar_struct_array_ = my_bar_struct_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bar_struct_array[setter]
  }

  ::Baz
  Foo_exec_i::my_baz_struct ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_baz_struct[getter]
    return this->my_baz_struct_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_baz_struct[getter]
  }

  void
  Foo_exec_i::my_baz_struct (
      const ::Baz& my_baz_struct)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_baz_struct[setter]
    this->my_baz_struct_ = my_baz_struct;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_baz_struct[setter]
  }

  ::Data
  Foo_exec_i::my_data_union ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_data_union[getter]
    return this->my_data_union_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_data_union[getter]
  }

  void
  Foo_exec_i::my_data_union (
      const ::Data& my_data_union)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_data_union[setter]
    this->my_data_union_ = my_data_union;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_data_union[setter]
  }

  ::Data2
  Foo_exec_i::my_var_data_union ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_var_data_union[getter]
    return this->my_var_data_union_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_var_data_union[getter]
  }

  void
  Foo_exec_i::my_var_data_union (
      const ::Data2& my_var_data_union)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_var_data_union[setter]
    this->my_var_data_union_ = my_var_data_union;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_var_data_union[setter]
  }

  ::StructModule::StructStruct
  Foo_exec_i::my_struct_struct ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_struct_struct[getter]
    return this->my_struct_struct_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_struct_struct[getter]
  }

  void
  Foo_exec_i::my_struct_struct (
      const ::StructModule::StructStruct& my_struct_struct)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_struct_struct[setter]
    this->my_struct_struct_ = my_struct_struct;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_struct_struct[setter]
  }

  ::sequence_bounded_string
  Foo_exec_i::my_sequence_bounded_string ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_sequence_bounded_string[getter]
    return this->my_sequence_bounded_string_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_sequence_bounded_string[getter]
  }

  void
  Foo_exec_i::my_sequence_bounded_string (
      const ::sequence_bounded_string& my_sequence_bounded_string)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_sequence_bounded_string[setter]
    this->my_sequence_bounded_string_ = my_sequence_bounded_string;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_sequence_bounded_string[setter]
  }

  ::sequence_bounded_wstring
  Foo_exec_i::my_sequence_bounded_wstring ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_sequence_bounded_wstring[getter]
    return this->my_sequence_bounded_wstring_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_sequence_bounded_wstring[getter]
  }

  void
  Foo_exec_i::my_sequence_bounded_wstring (
      const ::sequence_bounded_wstring& my_sequence_bounded_wstring)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_sequence_bounded_wstring[setter]
    this->my_sequence_bounded_wstring_ = my_sequence_bounded_wstring;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_sequence_bounded_wstring[setter]
  }

  ::bounded_sequence_bounded_string
  Foo_exec_i::my_bounded_sequence_bounded_string ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_string[getter]
    return this->my_bounded_sequence_bounded_string_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_string[getter]
  }

  void
  Foo_exec_i::my_bounded_sequence_bounded_string (
      const ::bounded_sequence_bounded_string& my_bounded_sequence_bounded_string)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_string[setter]
    this->my_bounded_sequence_bounded_string_ = my_bounded_sequence_bounded_string;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_string[setter]
  }

  ::bounded_sequence_bounded_wstring
  Foo_exec_i::my_bounded_sequence_bounded_wstring ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_wstring[getter]
    return this->my_bounded_sequence_bounded_wstring_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_wstring[getter]
  }

  void
  Foo_exec_i::my_bounded_sequence_bounded_wstring (
      const ::bounded_sequence_bounded_wstring& my_bounded_sequence_bounded_wstring)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_wstring[setter]
    this->my_bounded_sequence_bounded_wstring_ = my_bounded_sequence_bounded_wstring;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_sequence_bounded_wstring[setter]
  }

  ::bounded_string_array
  Foo_exec_i::my_bounded_string_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_string_array[getter]
    return this->my_bounded_string_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_string_array[getter]
  }

  void
  Foo_exec_i::my_bounded_string_array (
      const ::bounded_string_array& my_bounded_string_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_string_array[setter]
    this->my_bounded_string_array_ = my_bounded_string_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_string_array[setter]
  }

  ::bounded_wstring_array
  Foo_exec_i::my_bounded_wstring_array ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_wstring_array[getter]
    return this->my_bounded_wstring_array_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_wstring_array[getter]
  }

  void
  Foo_exec_i::my_bounded_wstring_array (
      const ::bounded_wstring_array& my_bounded_wstring_array)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_bounded_wstring_array[setter]
    this->my_bounded_wstring_array_ = my_bounded_wstring_array;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_bounded_wstring_array[setter]
  }

  ::DataType
  Foo_exec_i::my_data_type ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_data_type[getter]
    return this->my_data_type_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_data_type[getter]
  }

  void
  Foo_exec_i::my_data_type (
      ::DataType my_data_type)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_data_type[setter]
    this->my_data_type_ = my_data_type;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_data_type[setter]
  }

  ::data_type_type
  Foo_exec_i::my_data_type_type ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_data_type_type[getter]
    return this->my_data_type_type_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_data_type_type[getter]
  }

  void
  Foo_exec_i::my_data_type_type (
      ::data_type_type my_data_type_type)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_data_type_type[setter]
    this->my_data_type_type_ = my_data_type_type;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_data_type_type[setter]
  }

  CORBA::Any
  Foo_exec_i::my_any ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_any[getter]
    return this->my_any_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_any[getter]
  }

  void
  Foo_exec_i::my_any (
      const CORBA::Any& my_any)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_any[setter]
    this->my_any_ = my_any;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_any[setter]
  }

  ::any_type
  Foo_exec_i::my_any_type ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_any_type[getter]
    return this->my_any_type_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_any_type[getter]
  }

  void
  Foo_exec_i::my_any_type (
      const ::any_type& my_any_type)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_any_type[setter]
    this->my_any_type_ = my_any_type;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_any_type[setter]
  }

  IDL::traits< ::MyFoo>::ref_type
  Foo_exec_i::my_foo_interface ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_foo_interface[getter]
    return this->my_foo_interface_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_foo_interface[getter]
  }

  void
  Foo_exec_i::my_foo_interface (
      IDL::traits< ::MyFoo>::ref_type my_foo_interface)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::my_foo_interface[setter]
    this->my_foo_interface_ = my_foo_interface;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::my_foo_interface[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Foo_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_Foo_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_end_impl]

} // namespace Foo_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[factory]
extern "C" void
create_Foo_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Foo_Impl::Foo_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
