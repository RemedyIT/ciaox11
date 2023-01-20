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

#include <sstream>
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_global_impl]

namespace Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_impl]
  class TT_HelloCallback
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_HelloCallback (IDL::traits<::Test::CCM_Sender>::weak_ref_type component_executor)
    : component_executor_(component_executor)
     {}

    void
    on_trigger (
        IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits<::Test::CCM_Sender>::weak_ref_type component_executor_;
  };

  void
  TT_HelloCallback::on_trigger (
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
      cex->tick_hello();
    }
  }

  class TT_MsgCallback
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_MsgCallback (IDL::traits<::Test::CCM_Sender>::weak_ref_type component_executor)
    : component_executor_(component_executor)
    {}

    void
    on_trigger (
        IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits<::Test::CCM_Sender>::weak_ref_type component_executor_;
  };

  void
  TT_MsgCallback::on_trigger (
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
      cex->tick_message();
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

    if (this->mode_.empty () || this->mode_ == "HELLO")
    {
      this->tm_hello_ = tt_s->schedule_repeated_trigger (
                          CORBA::make_reference<TT_HelloCallback> (IDL::traits<Test::CCM_Sender>::narrow (this->_lock())),
                          CCM_TT::TT_Duration (
                              this->delay_ / 1000,
                              (this->delay_ % 1000) * 1000000),       // delay before starting
                          CCM_TT::TT_Duration (0, 1000000), // 1 tick/msec
                          0);
      PSDD4CCM_TEST_DEBUG << "Sender_exec_i::start_publishing : Hello Timer scheduled." << std::endl;
    }
    if (this->mode_.empty () || this->mode_ == "MSG")
    {
      this->tm_msg_ = tt_s->schedule_repeated_trigger (
                          CORBA::make_reference<TT_MsgCallback> (IDL::traits<Test::CCM_Sender>::narrow (this->_lock())),
                          CCM_TT::TT_Duration (
                              this->delay_ / 1000,
                              (this->delay_ % 1000) * 1000000),       // delay before starting
                          CCM_TT::TT_Duration (0, 1000000), // 1 tick/msec
                          0);
      PSDD4CCM_TEST_DEBUG << "Sender_exec_i::start_publishing : Message Timer scheduled." << std::endl;
    }
  }

  void
  Sender_exec_i::tick_hello ()
  {
    try
    {
      if (this->count () == this->hello_counter_)
      {
        if (this->mode_ == "HELLO" || this->count () == this->msg_counter_)
        {
          this->stop_publishing ();
        }
        return;
      }

      IDL::traits<Test::Hello::Publisher>::ref_type writer =
        this->context_->get_connection_hello_pub ();

      std::ostringstream oss;
      if (++this->hello_counter_ % 2)
      {
        oss << "ODD";
      }
      else
      {
        oss << "EVEN";
      }
      oss << "/" << this->hello_counter_;

      writer->write_one (oss.str ());
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

  void
  Sender_exec_i::tick_message ()
  {
    try
    {
      IDL::traits<Test::Msg::Publisher>::ref_type writer =
        this->context_->get_connection_msg_pub ();

      if (this->count () == this->msg_counter_)
      {
        if (this->mode_ == "MSG" || this->count () == this->hello_counter_)
        {
          this->stop_publishing ();
        }
        return;
      }

      ::Test::Message msg {};
      std::ostringstream oss;
      if (++this->msg_counter_ % 2)
      {
        msg.category ("ODD");
      }
      else
      {
        msg.category ("EVEN");
      }
      oss << "Message #" << this->msg_counter_;
      msg.description (oss.str ());
      msg.value (this->count () - this->msg_counter_);

      writer->write_one (msg);
    }
    catch (const ::CCM_PSDD::InternalError &ex)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick_msg - "
        << "caught CCM_PSDD::InternalError: "
        << ex << std::endl;
    }
    catch (const std::exception &ex)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick_msg - "
        << "caught std::exception: "
        << ex << std::endl;
    }
    catch (...)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick_msg - "
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
    if (this->tm_hello_)
    {
      this->tm_hello_->cancel();
      this->tm_hello_.reset ();
      PSDD4CCM_TEST_DEBUG << "Sender_exec_i::stop_publishing : Hello Timer canceled." << std::endl;
    }
    if (this->tm_msg_)
    {
      this->tm_msg_->cancel();
      this->tm_msg_.reset ();
      PSDD4CCM_TEST_DEBUG << "Sender_exec_i::stop_publishing : Message Timer canceled." << std::endl;
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


  std::string
  Sender_exec_i::mode ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::mode[getter]
    return this->mode_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::mode[getter]
  }

  void
  Sender_exec_i::mode (
      const std::string& mode)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i::mode[setter]
    this->mode_ = mode;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i::mode[setter]
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
