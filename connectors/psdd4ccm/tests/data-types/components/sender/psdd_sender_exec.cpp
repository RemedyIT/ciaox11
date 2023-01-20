// -*- C++ -*-
/**
 * @file    psdd_sender_exec.cpp
 * @author  Martin Corino
 *
 * @brief   PSDD Sender executor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psdd_sender_impl.cpp[Header]

#include "psdd_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_includes]
#include "psdd4ccm/logger/psdd4ccm_testlog.h"
#include "ace/Truncate.h"
#include <sstream>
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_global_impl]

namespace Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_impl]
  class TT_TopicCallback
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_TopicCallback (IDL::traits<::Test::CCM_Sender>::weak_ref_type component_executor)
    : component_executor_(component_executor)
     {}
    ~TT_TopicCallback () override = default;

    void
    on_trigger (
        IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits<::Test::CCM_Sender>::weak_ref_type component_executor_;
  };

  void
  TT_TopicCallback::on_trigger (
      IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    X11_UNUSED_ARG(time);
    X11_UNUSED_ARG(round);
    X11_UNUSED_ARG(timer);
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  : delay_ (1000)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::start_publishing ()
  {
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    this->tm_topic_ = tt_s->schedule_repeated_trigger (
                        CORBA::make_reference<TT_TopicCallback> (IDL::traits<Test::CCM_Sender>::narrow (this->_lock())),
                        CCM_TT::TT_Duration (
                            this->delay_ / 1000,
                            (this->delay_ % 1000) * 1000000),       // delay before starting
                        CCM_TT::TT_Duration (0, 1000000), // 1 tick/msec
                        0);
    PSDD4CCM_TEST_DEBUG << "Sender_exec_i::start_publishing : Topic Timer scheduled." << std::endl;
  }

  void
  Sender_exec_i::tick ()
  {
    try
    {
      if (this->count () == this->topic_counter_)
      {
        this->stop_publishing ();
        return;
      }

      IDL::traits<Test::TopicInterface::Publisher>::ref_type writer =
        this->context_->get_connection_topic_pub ();

      ++this->topic_counter_;
      uint16_t last_key = this->topic_counter_ % 5;

      Test::B10 b10;
      b10.reserve (5);
      for (uint16_t i = 1; i < 6; ++i)
      {
        Test::B02 b02 (i*this->topic_counter_);
        b10.push_back (b02);
      }

      Test::B11 b11;
      for (uint16_t i = 1; i < IDL::traits<Test::B11 >::bound () + 1; ++i)
      {
        Test::B02 b02 ((i+1)*this->topic_counter_);
        b11.push_back (b02);
      }

      const Test::B12 b12 (15);
      const Test::B13 b13 (15);
      const Test::B12 b14 (15);

      Test::B15 b15 (10);
      for (uint16_t i = 0; i < 10; ++i)
      {
        b15[i] = i*this->topic_counter_;
      }

      Test::B16 b16;
      for (uint16_t x = 0; x < 4; ++x)
      {
        for (uint16_t y = 0; y < 5; ++y)
        {
          b16[x][y] = x*y*this->topic_counter_;
        }
      }


      Test::B32 b32;
      b32[0] = Test::B31 (3*this->topic_counter_);
      b32[1] = Test::B31 (4*this->topic_counter_);

      Test::B33 b33;
      for (uint16_t x = 0; x < 4; ++x)
      {
        for (uint16_t y = 0; y < 5; ++y)
        {
          b33[x][y] = Test::B31 (x*y*this->topic_counter_);
        }
      }

      Test::B34 b34;
      for (uint16_t x = 0; x < 6; ++x)
      {
        for (uint16_t y = 0; y < 7; ++y)
        {
          for (uint16_t z = 0; z < 8; ++z)
          {
            b34[x][y][z] = Test::B31 (x*y*z*this->topic_counter_);
          }
        }
      }

      Test::B40 b40;
      b40[0] = 2*this->topic_counter_;
      b40[1] = 3*this->topic_counter_;

      Test::B41 b41;
      for (uint16_t x = 0; x < 2; ++x)
      {
        for (uint16_t y = 0; y < 3; ++y)
        {
          b41[x][y] = (x+1)*(y+2)*this->topic_counter_;
        }
      }

      const Test::B42 b42 (b40);

      const std::array<int32_t, 4> arr {{5,4,3,2}};
      Test::B43 b43 (arr);

      const Test::B_50 b50 (
        "ITERATION_" + std::to_string (last_key) +
        "_" + std::to_string (this->topic_counter_));

      std::string iter = std::to_string (this->topic_counter_);
      Test::B51 b51 (5-iter.length (), '*');
      b51 += iter;

      const Test::B52 b52 (this->topic_counter_^this->topic_counter_);

      const Test::B53 b53 (b32);

      const Test::B_54 b54 (b50);

      const Test::B55 b55 (b51);

      Test::B56 b56;
      for (uint16_t x = 0; x < 6; ++x)
      {
        for (uint16_t y = 0; y < 5; ++y)
        {
          b56[x][y] = std::to_string (x+y+this->topic_counter_);
        }
      }

      Test::B57 b57;
      for (uint16_t val = this->topic_counter_; val <  this->topic_counter_ + 100; ++val)
      {
        b57.push_back ("VALUE_"+std::to_string (val));
      }

      Test::B59 b59;
      for (uint16_t val = this->topic_counter_; val <  this->topic_counter_ + 100; ++val)
      {
        b59.push_back ("BOUNDED STRING VALUE_"+std::to_string (val));
      }

      Test::B60 b60;
      for (uint16_t val = this->topic_counter_; val <  this->topic_counter_ + 100; ++val)
      {
        b60.push_back ("BOUNDED STRING VALUE_"+std::to_string (val+33));
      }


      const Test::B61 b61 (
        L"ITERATION_" + std::to_wstring (last_key) +
        L"_" + std::to_wstring (this->topic_counter_));

      std::wstring witer = std::to_wstring (this->topic_counter_);
      Test::B62 b62 (5-witer.length (), '*');
      b62 += witer;

      Test::B63 b63;
      for (uint16_t val = this->topic_counter_; val <  this->topic_counter_ + 100; ++val)
      {
        b63.push_back (L"VALUE_"+std::to_wstring (val));
      }

      Test::B64 b64;
      for (uint16_t x = 0; x < 6; ++x)
      {
        for (uint16_t y = 0; y < 5; ++y)
        {
          b64[x][y] = std::to_wstring (x+y+this->topic_counter_);
        }
      }

      Test::B72 b72;
      b72.push_back (Test::B71 (Test::B70::B70_3, Test::B72 ()));
      Test::B71 b71 (Test::B70::B70_2, b72);
      Test::B73 b73;
      if (this->topic_counter_ % 2)
      {
        b73.b_71 (b71);
      }
      else
      {
        b73.b_72 (b72);
      }

      Test::B80 b80;
      b80.b_80_2 (Test::B70::B70_3);

      Test::B83 b83;
      b83.a ("B83 STRING A");
      b83.c ("B83 STRING C");
      b83.d ("B83 STRING D");
      Test::B81 b81;
      for (uint16_t val = this->topic_counter_; val <  this->topic_counter_ + 100; ++val)
      {
        b81.b("B81 STRING B VALUE_"+std::to_string (val));
        b81.c("B81 BOUNDED STRING C VALUE_"+std::to_string (val));
        b83.f().push_back (b81);
      }

      bool a_13 = (this->topic_counter_%2) == 1;

      std::string const key ("KEY_"+std::to_string (last_key));
      Test::Topic topic (
          'A',                        // char
          L'A',                       // wchar
          this->topic_counter_ > 255 ? 255 : this->topic_counter_,      // octet
          -1*this->topic_counter_,   // short
          this->topic_counter_,      // ushort
          -2*this->topic_counter_,   // long
          2*this->topic_counter_,    // ulong
          -200*this->topic_counter_, // longlong
          200*this->topic_counter_,  // ulonglong
          (float)ACE_Utils::truncate_cast<uint16_t> (this->topic_counter_),      // float
          this->topic_counter_,      // double
          this->topic_counter_,      // long double
          a_13,
          b10,
          b11,
          b12,
          b13,
          b14,
          b15,
          b16,
          b32,
          b33,
          b34,
          b40,
          b41,
          b42,
          b43,
          b50,
          b51,
          b52,
          b53,
          b54,
          b55,
          b56,
          b57,
          b59,
          b60,
          b61,
          b62,
          b63,
          b64,
          a_13 ? Test::B70::B70_1 : Test::B70::B70_2,
          b73,
          b80,
          b83,
          key,
          this->topic_counter_);

      writer->write_one (topic);
    }
    catch (const ::CCM_PSDD::InternalError &ex)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick_hello - "
        << "caught CCM_PSDD::InternalError: "
        << ex << std::endl;
    }
    catch (const std::exception &ex)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick_hello - "
        << "caught std::exception: "
        << ex << std::endl;
    }
    catch (...)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick_hello - "
        << "ERROR caught unexpected exception"
        << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::stop_publishing ()
  {
    if (this->tm_topic_)
    {
      this->tm_topic_->cancel();
      this->tm_topic_.reset ();
      PSDD4CCM_TEST_DEBUG << "Sender_exec_i::stop_publishing : Topic Timer canceled." << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_activate]
    this->start_publishing ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_passivate]
    this->stop_publishing ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }


  uint32_t
  Sender_exec_i::count ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::count[getter]
    return this->count_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::count[getter]
  }

  void
  Sender_exec_i::count (
      uint32_t count)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::count[setter]
    this->count_ = count;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::count[setter]
  }

  uint32_t
  Sender_exec_i::delay ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::delay[getter]
    return this->delay_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::delay[getter]
  }

  void
  Sender_exec_i::delay (
      uint32_t delay)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::delay[setter]
    this->delay_ = delay;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::delay[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<::Test::CCM_Sender_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_end_impl]

} // namespace Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[factory]
extern "C" void
create_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Test_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
