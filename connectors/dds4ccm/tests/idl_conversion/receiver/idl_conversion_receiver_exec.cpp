// -*- C++ -*-
/**
 * @file    idl_conversion_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the IDL conversion test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : idl_conversion_receiver_impl.cpp[Header]

#include "idl_conversion_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_global_impl]

namespace IDL_Conversion_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
      IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context,
      std::atomic_ulong &samples_received)
    : context_ (std::move (context))
    , samples_received_ (samples_received)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  void
  info_out_data_listener_exec_i::check_datum (
    const ::Example::IDLConversionMessage& datum)
  {
    this->check_standard_types (datum);

    /// Check b_10 [Example::B10 (std::vector< Example::B02 >)]
    if (datum.b_10 ().size () != 5)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_10.size: expected<5> - got <" << datum.b_10 ().size ()
        << "> - details <" << datum.b_10 () << ">"
        << std::endl;
    }
    uint16_t c = 0;
    for (const Example::B02 &b02 : datum.b_10 ())
    {
      int32_t expected = ++c*datum.iteration ();
      if (expected != b02.B02_1 ())
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_10[" << c-1 << "]: expected <" << expected << "> - got <"
          << b02.B02_1 () << ">" << std::endl;
      }
    }


    /// Check b_11 [Example::B11 ( IDL::bounded_vector < B02, 15> )]
    if (datum.b_11 ().size () != 15)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_11.size: expected<15> - got <" << datum.b_11 ().size ()
        << "> - details <" << datum.b_11 () << ">"
        << std::endl;
    }
    c = 0;
    for (const Example::B02 &b02 : datum.b_11 ())
    {
      int32_t expected = (++c+1)*datum.iteration ();
      if (expected != b02.B02_1 ())
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_11[" << c-1 << "]: expected <" << expected << "> - got <"
          << b02.B02_1 () << ">" << std::endl;
      }
    }


    /// Check b_12 [Example::B12 (std::vector< uint8_t >)]
    if (datum.b_12 ().size () != 15)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_12.size: expected<15> - got <" << datum.b_12 ().size ()
        << "> - details <" << datum.b_12 () << ">"
        << std::endl;
    }


    /// Check b_13 [Example::B13 (IDL::bounded_vector < uint8_t, 15>)]
    if (datum.b_13 ().size () != 15)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_13.size: expected<15> - got <" << datum.b_13 ().size ()
        << "> - details <" << datum.b_13 () << ">"
        << std::endl;
    }


    /// Check b_14 [Example::B12 (std::vector< uint8_t >)]
    if (datum.b_14 ().size () != 15)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_14.size: expected<15> - got <" << datum.b_14 ().size ()
        << "> - details <" << datum.b_14 () << ">"
        << std::endl;
    }


    c = 0;
    /// Check b_15 [Example::B15 (std::vector< int32_t>)]
    for (int32_t val : datum.b_15 ())
    {
      int32_t expected = c * datum.iteration ();
      if (val != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_15[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      c++;
    }

    uint32_t x = 0;
    uint32_t y = 0;
    for (int x = 0; x < 4; ++x)
    {
      for (int y = 0; y < 5; ++y)
      {
        double expected = x*y*datum.iteration ();
        if (datum.b_16 ()[x][y] != expected)
        {
          DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_16[" << x*y << "]: expected <" << expected << "> - got <"
            << datum.b_16 ()[x][y] << ">" << std::endl;
        }
      }
    }

    c = 0;
    /// Check b_17 [Example::B17 (std::vector< bool >)]
    for (bool val : datum.b_17 ())
    {
      bool expected = (c%2) ? true : false;
      if (val != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_17[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      c++;
    }

    c = 0;
    /// Check b_18 [Example::B18 (IDL::bounded_vector< bool, 15 >)]
    for (bool val : datum.b_18 ())
    {
      bool expected = (c%2) ? true : false;
      if (val != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_18[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      c++;
    }

    /// Check b_20 [Example::B20_4 (IDL::bounded_vector < B20_4, 1>)]
    if (datum.b_20 ().size () != 0)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_20.size: expected<0> - got <" << datum.b_20 ().size ()
        << "> - details <" << datum.b_20 () << ">"
        << std::endl;
    }

    /// Check b_21 [Example::B21_6 (IDL::bounded_vector < B20_2, 1>)]
    if (datum.b_21 ().size () != 1 || datum.b_21 ()[0] != 21.6)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_21: expected single element 21.6 - got <" << datum.b_21 () << ">"
        << std::endl;
    }

    /// Check b_32 [Example::B32 (std::array< B31, 2 >)]
    this->check_b31_array (datum.b_32 (), datum.iteration ());

    /// Check b_33 [Example::B33 (std::array< std::array< B31, 5 >, 4 >)]
    x = 0;
    y = 0;
    for (const std::array< Example::B31, 5 > &arr : datum.b_33 ())
    {
      y = 0;
      for (const Example::B31 &val : arr)
      {
        int32_t expected = x*y*datum.iteration ();
        if (val.B31_1 () != expected)
        {
          DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_33[" << x*y << "]: expected <" << expected << "> - got <"
            << val.B31_1 () << ">" << std::endl;
        }
        ++y;
      }
      ++x;
    }

    /// Check b_34 [Example::B34 (std::array< std::array< std::array< B31, 8 >, 7 >, 6 >)]
    x = 0;
    y = 0;
    uint32_t z = 0;
    for (const std::array< std::array< Example::B31, 8 >, 7 > &arr_1 : datum.b_34 ())
    {
      y = 0;
      for (const std::array< Example::B31, 8 > &arr_2 : arr_1)
      {
        z = 0;
        for (const Example::B31 &val : arr_2)
        {
          int32_t expected = x*y*z*datum.iteration ();
          if (val.B31_1 () != expected)
          {
            DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
              << "datum.b_34[" << x*y*z << "]: expected <" << expected << "> - got <"
              << val.B31_1 () << ">" << std::endl;
          }
          ++z;
        }
        ++y;
      }
      ++x;
    }


    /// Check b_40 [Example::B40 (std::array< int32_t, 2 >)]
    c = 0;
    for (int32_t val : datum.b_40 ())
    {
      int32_t expected = (c++ + 2)*datum.iteration ();
      if (val != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_40[" << c-1 << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
    }


    /// Check b_41 [Example::B41 (std::array< int32_t, 3 >, 2 >)]
    x = 0;
    y = 0;
    for (const std::array< int32_t, 3 > &arr : datum.b_41 ())
    {
      y = 0;
      for (int32_t val : arr)
      {
        int32_t expected = (x+1)*(y+2)*datum.iteration ();
        if (val != expected)
        {
          DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_41[" << x*y << "]: expected <" << expected << "> - got <"
            << val << ">" << std::endl;
        }
        ++y;
      }
      ++x;
    }


    /// Check b_42 [Example::B42 (std::array< int32_t, 2 >)]
    if (datum.b_42 () != datum.b_40 ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_42: expected <" << datum.b_40 () << "> - got <"
        << datum.b_42 () << ">" << std::endl;
    }


    /// Check b_43 [Example::B43 (std::array< int32_t, 4 >)]
    const std::array<int32_t, 4> arr {{5,4,3,2}};
    if (datum.b_43 () != arr)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_43: expected <" << arr << "> - got <"
        << datum.b_43 () << ">" << std::endl;
    }

    /// Check b_50 [Example::B_50 (std::string)]
    std::string tmp = datum.key ();
    const std::string expected_4_b50 ("ITERATION_" + tmp.erase (0, 4) +
        "_" + std::to_string (datum.iteration ()));

    if (datum.b__50 () != expected_4_b50)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b__50: expected <" << expected_4_b50 << "> - got <"
        << datum.b__50 () << ">" << std::endl;
    }

    /// Check b_51 [Example::B51 (IDL::bounded_basic_string<char, 5> B51)]
    if (datum.b_51 ().size () > 5)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected size for "
        << "datum.b_51: expected <5> - got <"
        << datum.b_51 ().size () << ">" << std::endl;
    }
    std::string iter = std::to_string (datum.iteration ());
    Example::B51 expected_b51 (5-iter.length (), '*');
    expected_b51 += iter;
    if (datum.b_51 () != expected_b51)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_51: expected <" << expected_b51 << "> - got <"
        << datum.b_51 () << ">" << std::endl;
    }

    /// Check b_52 [Example::B52 (double)]
    double expected_4_b52 (datum.iteration ()^datum.iteration ());
    if (datum.b_52 () != expected_4_b52)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_52: expected <" << expected_4_b52 << "> - got <"
        << datum.b_52 () << ">" << std::endl;
    }


    /// Check b_53 [Example::B53 (Example::B32)]
    this->check_b31_array (datum.b_53 (), datum.iteration ());


    /// Check b__54 [Example::B_54 (Example::B_50)]
    if (datum.b__54 () != datum.b__50 ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b__54: expected <" << datum.b__50 () << "> - got <"
        << datum.b__54 () << ">" << std::endl;
    }


    /// Check b_55 [Example::B55 (Example::B51)]
    if (datum.b_55 ().size () > 5)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected size for "
        << "datum.b_55: expected <5> - got <"
        << datum.b_55 ().size () << ">" << std::endl;
    }
    if (datum.b_55 () != datum.b_51 ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_55: expected <" << datum.b_51 () << "> - got <"
        << datum.b_55 () << ">" << std::endl;
    }


    /// Check b_56 [Example::B56 (std::array< std::array< std::string, 5 >, 6 >)]
    for (uint16_t x = 0; x < 6; ++x)
    {
      for (uint16_t y = 0; y < 5; ++y)
      {
        const std::string expected (
          std::to_string (x + y + datum.iteration ()));
        if (datum.b_56 ()[x][y] != expected)
        {
          DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_56[" << x*y << "]: expected <" << expected << "> - got <"
            << datum.b_56 ()[x][y] << ">" << std::endl;
        }
      }
    }


    /// Check b_57 [Example::B57 (std::vector < std::string>)]
    c = 0;
    for (const std::string &val : datum.b_57 ())
    {
      const std::string expected ("VALUE_"+std::to_string (datum.iteration () + c));
      if (val != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_57[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }

    /// Check b_59 [Example::B59 (std::vector < IDL::bounded_basic_string<char, 512> B58>)]
    c = 0;
    for (const Example::B58 &val : datum.b_59 ())
    {
      const std::string expected ("BOUNDED STRING VALUE_"+std::to_string (datum.iteration () + c));
      if (val != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_59[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }

    /// Check b_60 [Example::B60 (alias for Example::B59)]
    c = 33;
    for (const Example::B58 &val : datum.b_60 ())
    {
      const std::string expected ("BOUNDED STRING VALUE_"+std::to_string (datum.iteration () + c));
      if (val != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_60[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }

    /// Check b_70 [Example::B70 (enum class B70 : uint32_t)]
    Example::B70 expected;
    datum.a_13 () ? expected = Example::B70::B70_1 : expected = Example::B70::B70_2;
    if (datum.b_70 () != expected)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_70: expected <" << expected << "> - got <"
        << datum.b_70 () << ">" << std::endl;
    }

    /// Check b_80 [Example::B80 (class B80)]
    switch (datum.b_80 ()._d ())
    {
      case Example::B70::B70_1:
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected discriminator "
          << "for datum.b_80: expected <Example::B70::B70_2> - got "
          << "<Example::B70::B70_1>." << std::endl;
        break;
      case Example::B70::B70_2:
        if (datum.b_80 ().b_80_2 () != Example::B70::B70_3)
        {
          DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_80 ().b_80_2 (): expected <Example::B70::B70_3> - got <"
            << datum.b_80 ().b_80_2 () << ">" << std::endl;
        }
        break;
      default:
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected discriminator "
          << "for datum.b_80: expected <Example::B70::B70_2> - got "
          << "<default>." << std::endl;
        break;
    }

    c = 0;
    for (const Example::B81 &val : datum.b_83 ().f())
    {
      std::string const expected_b ("B81 STRING B VALUE_"+std::to_string (datum.iteration () + c));
      std::string const expected_c ("B81 BOUNDED STRING C VALUE_"+std::to_string (datum.iteration () + c));
      if (val.b () != expected_b)
      {
          DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_83 ().f()[" << c << "]).b(): expected <" << expected_b  << "> - got <"
            << val.b() << ">" << std::endl;
      }
      if (val.c () != expected_c)
      {
          DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_83 ().f()[" << c << "]).c(): expected <" << expected_c  << "> - got <"
            << val.c () << ">" << std::endl;
      }
      ++c;
    }

    if (datum.b_85()._d () != 1)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_85 ()._d(): expected <" << 1  << "> - got <"
        << datum.b_85()._d () << ">" << std::endl;
    }
    else
    {
      Example::B42 b85_1 = datum.b_85().b_85_1 ();
      if (b85_1[0] != 5)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_85 ().b_85_1()[0]: expected <" << 5  << "> - got <"
          << b85_1[0] << ">" << std::endl;
      }
      if (b85_1[1] != 12)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_85 ().b_85_1()[1]: expected <" << 12  << "> - got <"
          << b85_1[1] << ">" << std::endl;
      }
    }
  }

  void
  info_out_data_listener_exec_i::check_standard_types (
    const ::Example::IDLConversionMessage& datum)
  {
    if (datum.a_01 () != 'A')
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_01: expected <'A'> - got <"
        << datum.a_01 () << ">" << std::endl;
    }
    if (datum.a_02 () != L'A')
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_02: expected <'A'> - got <"
        << datum.a_02 () << ">" << std::endl;
    }

    uint8_t a_03 = 0;
    datum.iteration () > 255 ? a_03 = 255 : a_03 = datum.a_03 ();
    if (datum.a_03 () != a_03)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_03: expected <" << a_03 << "> - got <"
        << datum.a_03 () << ">" << std::endl;
    }
    if (datum.a_04 () != -1 * datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_04: expected <" << -1 * datum.iteration () << "> - got <"
        << datum.a_04 () << ">" << std::endl;
    }
    if (datum.a_05 () != datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_05: expected <" << datum.iteration () << "> - got <"
        << datum.a_05 () << ">" << std::endl;
    }
    if (datum.a_06 () != -2 * datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_06: expected <" << -2 * datum.iteration () << "> - got <"
        << datum.a_06 () << ">" << std::endl;
    }
    uint32_t multiplier = 2;
    if (datum.a_07 () != multiplier * datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_07: expected <" << 2 * datum.iteration () << "> - got <"
        << datum.a_07 () << ">" << std::endl;
    }
    if (datum.a_08 () != -200 * datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_08: expected <" << -200 * datum.iteration () << "> - got <"
        << datum.a_08 () << ">" << std::endl;
    }
    multiplier = 200;
    if (datum.a_09 () != multiplier * datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_09: expected <" << 200 * datum.iteration () << "> - got <"
        << datum.a_09 () << ">" << std::endl;
    }
    if (datum.a_10 () != datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_10: expected <" << datum.iteration () << "> - got <"
        << datum.a_10 () << ">" << std::endl;
    }
    if (datum.a_11 () != datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_11: expected <" << datum.iteration () << "> - got <"
        << datum.a_11 () << ">" << std::endl;
    }
    if (datum.a_12 () != datum.iteration ())
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_12: expected <" << datum.iteration () * 123.456 << "> - got <"
        << datum.a_12 () << ">" << std::endl;
    }
    bool expected = (datum.iteration () % 2) == 1;
    if (datum.a_13 () != expected)
    {
      DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_13: expected <" << expected << "> - got <"
        << datum.a_13 () << ">" << std::endl;
    }
  }

  void
  info_out_data_listener_exec_i::check_b31_array (const std::array< Example::B31, 2 > &to_check, int32_t iter)
  {
    uint32_t c = 0;
    for (const Example::B31 &val : to_check)
    {
      int32_t expected = (c++ + 3)*iter;
      if (val.B31_1 () != expected)
      {
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "a b31_array[" << c-1 << "]: expected <" << expected << "> - got <"
          << val.B31_1 () << ">" << std::endl;
      }
    }
  }

  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::Example::IDLConversionMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(info);

    ++this->samples_received_;
    this->check_datum (datum);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::Example::IDLConversionMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type lc =
      this->context_->get_connection_info_out_data_control ();

    if (!lc)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener control receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->samples_received_ != 300)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of samples received. Expected <300> - received <"
        << this->samples_received_ << ">." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_passivate - OK: "
        "<" << this->samples_received_ << "> samples received" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::Example::IDLConversionTestConnector::CCM_Listener>::ref_type
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
    if (!this->info_out_data_listener_)
      {
        this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (
          this->context_, this->samples_received_);
      }
    return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_status]
    if (!this->info_out_status_)
      {
        this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (this->context_);
      }
    return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace IDL_Conversion_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[factory]
extern "C" void
create_IDL_Conversion_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
