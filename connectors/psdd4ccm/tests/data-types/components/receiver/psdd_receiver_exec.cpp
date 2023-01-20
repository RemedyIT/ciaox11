// -*- C++ -*-
/**
 * @file    psdd_receiver_exec.cpp
 * @author  Martin Corino
 *
 * @brief   PSDD Receiver executor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psdd_receiver_impl.cpp[Header]

#include "psdd_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_includes]
#include "psdd4ccm/logger/psdd4ccm_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_global_impl]

namespace Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits<::Test::CCM_Receiver>::weak_ref_type component_executor)
    : component_executor_(component_executor)
     {}
    virtual ~TT_Callback () = default;

    void
    on_trigger (
        IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits<::Test::CCM_Receiver>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
      IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    X11_UNUSED_ARG(time);
    X11_UNUSED_ARG(round);
    X11_UNUSED_ARG(timer);
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick ();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  : interval_ (10)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  void
  Receiver_exec_i::tick ()
  {
    try
    {
      if (this->count () > this->topic_counter_)
      {
        IDL::traits<Test::TopicInterface::Getter>::ref_type reader =
          this->context_->get_connection_topic_read ();
        Test::Topic topic {};
        if (reader->get_one (topic))
        {
          this->topic_counter_++;
          PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : read #" << this->topic_counter_ << std::endl;
          this->check_datum (topic);
        }
        else
        {
          PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : no topic" << std::endl;
        }
      }

      if (this->count () > this->topic_counter_)
      {
        PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : scheduling next reader tick" << std::endl;

        IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
        if (tt_s)
        {
          this->tm_ = tt_s->schedule_trigger (
                              CORBA::make_reference<TT_Callback> (IDL::traits<Test::CCM_Receiver>::narrow (this->_lock())),
                              CCM_TT::TT_Duration (
                                  this->interval () / 1000,
                                  (this->interval () % 1000) * 1000000));
        }
      }
      else
      {
        PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : finished reading" << std::endl;
      }
    }
    catch (const ::CCM_PSDD::InternalError &ex)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
        << "caught CCM_PSDD::InternalError: "
        << ex << std::endl;
    }
    catch (const std::exception &ex)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
        << "caught std::exception: "
        << ex << std::endl;
    }
    catch (...)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
        << "ERROR caught unexpected exception"
        << std::endl;
    }
  }

  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  void Receiver_exec_i::check_datum (const ::Test::Topic& datum)
  {
    this->check_standard_types (datum);

    /// Check b_10 [Test::B10 (std::vector< Test::B02 >)]
    if (datum.b_10 ().size () != 5)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_10.size: expected<5> - got <" << datum.b_10 ().size ()
        << "> - details <" << datum.b_10 () << ">"
        << std::endl;
    }
    uint16_t c = 0;
    for (const Test::B02 &b02 : datum.b_10 ())
    {
      int32_t expected = ++c*datum.count ();
      if (expected != b02.B02_1 ())
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_10[" << c-1 << "]: expected <" << expected << "> - got <"
          << b02.B02_1 () << ">" << std::endl;
      }
    }


    /// Check b_11 [Test::B11 ( IDL::bounded_vector < B02, 15> )]
    if (datum.b_11 ().size () != 15)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_11.size: expected<15> - got <" << datum.b_11 ().size ()
        << "> - details <" << datum.b_11 () << ">"
        << std::endl;
    }
    c = 0;
    for (const Test::B02 &b02 : datum.b_11 ())
    {
      int32_t expected = (++c+1)*datum.count ();
      if (expected != b02.B02_1 ())
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_11[" << c-1 << "]: expected <" << expected << "> - got <"
          << b02.B02_1 () << ">" << std::endl;
      }
    }


    /// Check b_12 [Test::B12 (std::vector< uint8_t >)]
    if (datum.b_12 ().size () != 15)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_12.size: expected<15> - got <" << datum.b_12 ().size ()
        << "> - details <" << datum.b_12 () << ">"
        << std::endl;
    }


    /// Check b_13 [Test::B13 (IDL::bounded_vector < uint8_t, 15>)]
    if (datum.b_13 ().size () != 15)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_13.size: expected<15> - got <" << datum.b_13 ().size ()
        << "> - details <" << datum.b_13 () << ">"
        << std::endl;
    }


    /// Check b_14 [Test::B12 (std::vector< uint8_t >)]
    if (datum.b_14 ().size () != 15)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "b_14.size: expected<15> - got <" << datum.b_14 ().size ()
        << "> - details <" << datum.b_14 () << ">"
        << std::endl;
    }


    c = 0;
    /// Check b_15 [Test::B15 (std::vector< int32_t>)]
    for (int32_t val : datum.b_15 ())
    {
      int32_t expected = c * datum.count ();
      if (val != expected)
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
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
        double expected = x*y*datum.count ();
        if (datum.b_16 ()[x][y] != expected)
        {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_16[" << x*y << "]: expected <" << expected << "> - got <"
            << datum.b_16 ()[x][y] << ">" << std::endl;
        }
      }
    }

    /// Check b_32 [Test::B32 (std::array< B31, 2 >)]
    this->check_b31_array (datum.b_32 (), datum.count ());

    /// Check b_33 [Test::B33 (std::array< std::array< B31, 5 >, 4 >)]
    x = 0;
    y = 0;
    for (const std::array< Test::B31, 5 > &arr : datum.b_33 ())
    {
      y = 0;
      for (const Test::B31 &val : arr)
      {
        int32_t expected = x*y*datum.count ();
        if (val.B31_1 () != expected)
        {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_33[" << x*y << "]: expected <" << expected << "> - got <"
            << val.B31_1 () << ">" << std::endl;
        }
        ++y;
      }
      ++x;
    }

    /// Check b_34 [Test::B34 (std::array< std::array< std::array< B31, 8 >, 7 >, 6 >)]
    x = 0;
    y = 0;
    uint32_t z = 0;
    for (const std::array< std::array< Test::B31, 8 >, 7 > &arr_1 : datum.b_34 ())
    {
      y = 0;
      for (const std::array< Test::B31, 8 > &arr_2 : arr_1)
      {
        z = 0;
        for (const Test::B31 &val : arr_2)
        {
          int32_t expected = x*y*z*datum.count ();
          if (val.B31_1 () != expected)
          {
            PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
              << "datum.b_34[" << x*y*z << "]: expected <" << expected << "> - got <"
              << val.B31_1 () << ">" << std::endl;
          }
          ++z;
        }
        ++y;
      }
      ++x;
    }


    /// Check b_40 [Test::B40 (std::array< int32_t, 2 >)]
    c = 0;
    for (int32_t val : datum.b_40 ())
    {
      int32_t expected = (c++ + 2)*datum.count ();
      if (val != expected)
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_40[" << c-1 << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
    }


    /// Check b_41 [Test::B41 (std::array< int32_t, 3 >, 2 >)]
    x = 0;
    y = 0;
    for (const std::array< int32_t, 3 > &arr : datum.b_41 ())
    {
      y = 0;
      for (int32_t val : arr)
      {
        int32_t expected = (x+1)*(y+2)*datum.count ();
        if (val != expected)
        {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_41[" << x*y << "]: expected <" << expected << "> - got <"
            << val << ">" << std::endl;
        }
        ++y;
      }
      ++x;
    }


    /// Check b_42 [Test::B42 (std::array< int32_t, 2 >)]
    if (datum.b_42 () != datum.b_40 ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_42: expected <" << datum.b_40 () << "> - got <"
        << datum.b_42 () << ">" << std::endl;
    }


    /// Check b_43 [Test::B43 (std::array< int32_t, 4 >)]
    const std::array<int32_t, 4> arr {{5,4,3,2}};
    if (datum.b_43 () != arr)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_43: expected <" << arr << "> - got <"
        << datum.b_43 () << ">" << std::endl;
    }

    /// Check b_50 [Test::B_50 (std::string)]
    std::string tmp = datum.key ();
    const std::string expected_4_b50 ("ITERATION_" + tmp.erase (0, 4) +
        "_" + std::to_string (datum.count ()));

    if (datum.b__50 () != expected_4_b50)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b__50: expected <" << expected_4_b50 << "> - got <"
        << datum.b__50 () << ">" << std::endl;
    }

    /// Check b_51 [Test::B51 (IDL::bounded_basic_string<char, 5> B51)]
    if (datum.b_51 ().size () > 5)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected size for "
        << "datum.b_51: expected <5> - got <"
        << datum.b_51 ().size () << ">" << std::endl;
    }
    std::string iter = std::to_string (datum.count ());
    Test::B51 expected_b51 (5-iter.length (), '*');
    expected_b51 += iter;
    if (datum.b_51 () != expected_b51)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_51: expected <" << expected_b51 << "> - got <"
        << datum.b_51 () << ">" << std::endl;
    }

    /// Check b_52 [Test::B52 (double)]
    double expected_4_b52 (datum.count ()^datum.count ());
    if (datum.b_52 () != expected_4_b52)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_52: expected <" << expected_4_b52 << "> - got <"
        << datum.b_52 () << ">" << std::endl;
    }


    /// Check b_53 [Test::B53 (Test::B32)]
    this->check_b31_array (datum.b_53 (), datum.count ());


    /// Check b__54 [Test::B_54 (Test::B_50)]
    if (datum.b__54 () != datum.b__50 ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b__54: expected <" << datum.b__50 () << "> - got <"
        << datum.b__54 () << ">" << std::endl;
    }


    /// Check b_55 [Test::B55 (Test::B51)]
    if (datum.b_55 ().size () > 5)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected size for "
        << "datum.b_55: expected <5> - got <"
        << datum.b_55 ().size () << ">" << std::endl;
    }
    if (datum.b_55 () != datum.b_51 ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_55: expected <" << datum.b_51 () << "> - got <"
        << datum.b_55 () << ">" << std::endl;
    }


    /// Check b_56 [Test::B56 (std::array< std::array< std::string, 5 >, 6 >)]
    for (uint16_t x = 0; x < 6; ++x)
    {
      for (uint16_t y = 0; y < 5; ++y)
      {
        const std::string expected (
          std::to_string (x + y + datum.count ()));
        if (datum.b_56 ()[x][y] != expected)
        {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_56[" << x*y << "]: expected <" << expected << "> - got <"
            << datum.b_56 ()[x][y] << ">" << std::endl;
        }
      }
    }


    /// Check b_57 [Test::B57 (std::vector < std::string>)]
    c = 0;
    for (const std::string &val : datum.b_57 ())
    {
      const std::string expected ("VALUE_"+std::to_string (datum.count () + c));
      if (val != expected)
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_57[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }

    /// Check b_59 [Test::B59 (std::vector < IDL::bounded_basic_string<char, 512> B58>)]
    c = 0;
    for (const Test::B58 &val : datum.b_59 ())
    {
      const std::string expected ("BOUNDED STRING VALUE_"+std::to_string (datum.count () + c));
      if (val != expected)
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_59[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }

    /// Check b_60 [Test::B60 (alias for Test::B59)]
    c = 33;
    for (const Test::B58 &val : datum.b_60 ())
    {
      const std::string expected ("BOUNDED STRING VALUE_"+std::to_string (datum.count () + c));
      if (val != expected)
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_60[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }


    /// Check b_61 [Test::B61 (std::wstring)]
    const std::wstring expected_4_b61 (L"ITERATION_" + std::to_wstring (datum.count () % 5) +
        L"_" + std::to_wstring (datum.count ()));

    if (datum.b_61 () != expected_4_b61)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_61: expected <" << expected_4_b61 << "> - got <"
        << datum.b_61 () << ">" << std::endl;
    }

    /// Check b_62 [Test::B62 (IDL::bounded_basic_wstring<wchar_t, 5> B62)]
    if (datum.b_62 ().size () > 5)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected size for "
        << "datum.b_62: expected <5> - got <"
        << datum.b_62 ().size () << ">" << std::endl;
    }
    std::wstring witer = std::to_wstring (datum.count ());
    Test::B62 expected_b62 (5-witer.length (), '*');
    expected_b62 += witer;
    if (datum.b_62 () != expected_b62)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_62: expected <" << expected_b62 << "> - got <"
        << datum.b_62 () << ">" << std::endl;
    }

    /// Check b_63 [Test::B63 (std::vector < std::wstring>)]
    c = 0;
    for (const std::wstring &val : datum.b_63 ())
    {
      const std::wstring expected (L"VALUE_"+std::to_wstring (datum.count () + c));
      if (val != expected)
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_63[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }

    /// Check b_64 [Test::B64 (std::array< std::array< std::wstring, 5 >, 6 >)]
    for (uint16_t x = 0; x < 6; ++x)
    {
      for (uint16_t y = 0; y < 5; ++y)
      {
        const std::wstring expected (
          std::to_wstring (x + y + datum.count ()));
        if (datum.b_64 ()[x][y] != expected)
        {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_64[" << x*y << "]: expected <" << expected << "> - got <"
            << datum.b_64 ()[x][y] << ">" << std::endl;
        }
      }
    }

    /// Check b_70 [Test::B70 (enum class B70 : uint32_t)]
    Test::B70 expected;
    datum.a_13 () ? expected = Test::B70::B70_1 : expected = Test::B70::B70_2;
    if (datum.b_70 () != expected)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "datum.b_70: expected <" << expected << "> - got <"
        << datum.b_70 () << ">" << std::endl;
    }

    /// Check b_73 [Test::B73 (union B73)]
    Test::B72 expected_b72;
    expected_b72.push_back (Test::B71 (Test::B70::B70_3, Test::B72 ()));
    Test::B71 expected_b71 (Test::B70::B70_2, expected_b72);
    Test::B73 expected_b73;
    if (this->topic_counter_ % 2)
    {
      expected_b73.b_71 (expected_b71);
      if ((datum.b_73 ()._d () != Test::B70::B70_1)
          || (datum.b_73 ().b_71 ().e70 () != Test::B70::B70_2)
          || (datum.b_73 ().b_71 ().sb72 ().size () != 1)
          || (datum.b_73 ().b_71 ().sb72 ()[0].e70 () != Test::B70::B70_3))
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_73: expected <" << expected_b73 << "> - got <"
          << datum.b_73 () << ">" << std::endl;
      }
    }
    else
    {
      expected_b73.b_72 (expected_b72);
      if ((datum.b_73 ()._d () == Test::B70::B70_1)
          || (datum.b_73 ().b_72 ().size () != 1)
          || (datum.b_73 ().b_72 ()[0].e70 () != Test::B70::B70_3))
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_73: expected <" << expected_b73 << "> - got <"
          << datum.b_73 () << ">" << std::endl;
      }
    }

    /// Check b_80 [Test::B80 (class B80)]
    switch (datum.b_80 ()._d ())
    {
      case Test::B70::B70_1:
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected discriminator "
          << "for datum.b_80: expected <Test::B70::B70_2> - got "
          << "<Test::B70::B70_1>." << std::endl;
        break;
      case Test::B70::B70_2:
        if (datum.b_80 ().b_80_2 () != Test::B70::B70_3)
        {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_80 ().b_80_2 (): expected <Test::B70::B70_3> - got <"
            << datum.b_80 ().b_80_2 () << ">" << std::endl;
        }
        break;
      default:
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected discriminator "
          << "for datum.b_80: expected <Test::B70::B70_2> - got "
          << "<default>." << std::endl;
        break;
    }

    c = 0;
    for (const Test::B81 &val : datum.b_83 ().f())
    {
      std::string const expected_b ("B81 STRING B VALUE_"+std::to_string (datum.count () + c));
      std::string const expected_c ("B81 BOUNDED STRING C VALUE_"+std::to_string (datum.count () + c));
      if (val.b () != expected_b)
      {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_83 ().f()[" << c << "]).b(): expected <" << expected_b  << "> - got <"
            << val.b() << ">" << std::endl;
      }
      if (val.c () != expected_c)
      {
          PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
            << "datum.b_83 ().f()[" << c << "]).c(): expected <" << expected_c  << "> - got <"
            << val.c () << ">" << std::endl;
      }
      ++c;
    }
  }
  void Receiver_exec_i::check_standard_types (const ::Test::Topic& datum)
  {
    if (datum.a_01 () != 'A')
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_01: expected <'A'> - got <"
        << datum.a_01 () << ">" << std::endl;
    }
    if (datum.a_02 () != L'A')
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_02: expected <'A'> - got <"
        << datum.a_02 () << ">" << std::endl;
    }

    uint8_t a_03 = 0;
    datum.count () > 255 ? a_03 = 255 : a_03 = datum.a_03 ();
    if (datum.a_03 () != a_03)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_03: expected <" << a_03 << "> - got <"
        << datum.a_03 () << ">" << std::endl;
    }
    if (datum.a_04 () != (int16_t)(-1 * datum.count ()))
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_04: expected <" << -1 * datum.count () << "> - got <"
        << datum.a_04 () << ">" << std::endl;
    }
    if (datum.a_05 () != datum.count ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_05: expected <" << datum.count () << "> - got <"
        << datum.a_05 () << ">" << std::endl;
    }
    if (datum.a_06 () != (int32_t)(-2 * datum.count ()))
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_06: expected <" << -2 * datum.count () << "> - got <"
        << datum.a_06 () << ">" << std::endl;
    }
    uint32_t multiplier = 2;
    if (datum.a_07 () != multiplier * datum.count ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_07: expected <" << 2 * datum.count () << "> - got <"
        << datum.a_07 () << ">" << std::endl;
    }
    if (datum.a_08 () != -200 * datum.count ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_08: expected <" << -200 * datum.count () << "> - got <"
        << datum.a_08 () << ">" << std::endl;
    }
    multiplier = 200;
    if (datum.a_09 () != multiplier * datum.count ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_09: expected <" << 200 * datum.count () << "> - got <"
        << datum.a_09 () << ">" << std::endl;
    }
    if (datum.a_10 () != datum.count ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_10: expected <" << datum.count () << "> - got <"
        << datum.a_10 () << ">" << std::endl;
    }
    if (datum.a_11 () != datum.count ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_11: expected <" << datum.count () << "> - got <"
        << datum.a_11 () << ">" << std::endl;
    }
    if (datum.a_12 () != datum.count ())
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_12: expected <" << datum.count () * 123.456 << "> - got <"
        << datum.a_12 () << ">" << std::endl;
    }
    bool expected = (datum.count () % 2) == 1;
    if (datum.a_13 () != expected)
    {
      PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
        << "a_13: expected <" << expected << "> - got <"
        << datum.a_13 () << ">" << std::endl;
    }
  }
  void Receiver_exec_i::check_b31_array (const std::array< Test::B31, 2 > &to_check, int32_t iter)
  {
    uint32_t c = 0;
    for (const Test::B31 &val : to_check)
    {
      int32_t expected = (c++ + 3)*iter;
      if (val.B31_1 () != expected)
      {
        PSDD4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "a b31_array[" << c-1 << "]: expected <" << expected << "> - got <"
          << val.B31_1 () << ">" << std::endl;
      }
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribing to any topic instance" << std::endl;

    // subscribe to all topic instances
    auto topic_sub = this->context_->get_connection_topic_sub ();
    topic_sub->subscribe_any ();

    PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribed" << std::endl;

    PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : activating reader tick" << std::endl;

    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
    if (!tt_s)
    {
      PSDD4CCM_TEST_ERROR << "Receiver_exec_i::ccm_activate : NO timed trigger scheduler" << std::endl;
    }
    else
    {
      this->tm_ = tt_s->schedule_trigger (
                          CORBA::make_reference<TT_Callback> (IDL::traits<Test::CCM_Receiver>::narrow (this->_lock())),
                          CCM_TT::TT_Duration (
                              this->delay () / 1000,
                              (this->delay () % 1000) * 1000000));

      PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : scheduled reader tick" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->tm_)
    {
      this->tm_->cancel ();
      this->tm_.reset ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    if (this->topic_counter_ > 0)
      PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_remove : received " << this->topic_counter_ << " topic instances" << std::endl;
    else
      PSDD4CCM_TEST_ERROR << "Receiver_exec_i::ccm_remove : NO topic instances received" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }


  uint32_t
  Receiver_exec_i::count ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::count[getter]
    return this->count_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::count[getter]
  }

  void
  Receiver_exec_i::count (
      uint32_t count)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::count[setter]
    this->count_ = count;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::count[setter]
  }

  uint32_t
  Receiver_exec_i::delay ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::delay[getter]
    return this->delay_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::delay[getter]
  }

  void
  Receiver_exec_i::delay (
      uint32_t delay)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::delay[setter]
    this->delay_ = delay;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::delay[setter]
  }

  uint32_t
  Receiver_exec_i::interval ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::interval[getter]
    return this->interval_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::interval[getter]
  }

  void
  Receiver_exec_i::interval (
      uint32_t interval)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::interval[setter]
    this->interval_ = interval;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::interval[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<::Test::CCM_Receiver_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_end_impl]

} // namespace Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[factory]
extern "C" void
create_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
