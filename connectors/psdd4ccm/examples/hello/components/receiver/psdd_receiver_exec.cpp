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
    TT_Callback (IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor)
    : component_executor_(component_executor)
     {}

    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
      IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
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
   * Facet Executor Implementation Class : hello_listen_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[ctor]
  hello_listen_exec_i::hello_listen_exec_i (
    IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor,
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
    this->listen_mode_ = ::CCM_PSDD::ListenerMode::ONE_BY_ONE;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[ctor]

  hello_listen_exec_i::~hello_listen_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[user_private_ops]


  /** Operations and attributes from hello_listen */

  void
  hello_listen_exec_i::on_data (
      ::Test::StringSeq_t& data)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i::on_data[_data]
    PSDD4CCM_TEST_DEBUG << "hello_listen_exec_i::on_data : received [" << IDL::traits< ::Test::StringSeq_t>::write (data) << "]" << std::endl;
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->increment_hello_counter ((uint32_t)data.size ());
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i::on_data[_data]
  }

  ::CCM_PSDD::ListenerMode
  hello_listen_exec_i::listen_mode ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i::listen_mode[getter]
    return this->listen_mode_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i::listen_mode[getter]
  }

  void
  hello_listen_exec_i::listen_mode (
      ::CCM_PSDD::ListenerMode listen_mode)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i::listen_mode[setter]
    this->listen_mode_ = listen_mode;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i::listen_mode[setter]
  }

  ::CCM_PSDD::DataCount_t
  hello_listen_exec_i::max_data ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i::max_data[getter]
    return this->max_data_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i::max_data[getter]
  }

  void
  hello_listen_exec_i::max_data (
      ::CCM_PSDD::DataCount_t max_data)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i::max_data[setter]
    this->max_data_ = max_data;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i::max_data[setter]
  }
  /**
   * Facet Executor Implementation Class : msg_listen_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[ctor]
  msg_listen_exec_i::msg_listen_exec_i (
    IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor,
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
    this->listen_mode_ = ::CCM_PSDD::ListenerMode::ONE_BY_ONE;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[ctor]

  msg_listen_exec_i::~msg_listen_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[user_private_ops]


  /** Operations and attributes from msg_listen */

  void
  msg_listen_exec_i::on_data (
      ::Test::MessageSeq_t& data)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i::on_data[_data]
    PSDD4CCM_TEST_DEBUG << "msg_listen_exec_i::on_data : received [" << IDL::traits< ::Test::MessageSeq_t>::write (data) << "]" << std::endl;
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->increment_msg_counter ((uint32_t)data.size ());
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i::on_data[_data]
  }

  ::CCM_PSDD::ListenerMode
  msg_listen_exec_i::listen_mode ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i::listen_mode[getter]
    return this->listen_mode_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i::listen_mode[getter]
  }

  void
  msg_listen_exec_i::listen_mode (
      ::CCM_PSDD::ListenerMode listen_mode)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i::listen_mode[setter]
    this->listen_mode_ = listen_mode;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i::listen_mode[setter]
  }

  ::CCM_PSDD::DataCount_t
  msg_listen_exec_i::max_data ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i::max_data[getter]
    return this->max_data_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i::max_data[getter]
  }

  void
  msg_listen_exec_i::max_data (
      ::CCM_PSDD::DataCount_t max_data)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i::max_data[setter]
    this->max_data_ = max_data;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i::max_data[setter]
  }

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
      if (this->hello_subscription ()
          && this->count () > this->hello_counter_)
      {
        IDL::traits<Test::Hello::Getter>::ref_type reader =
          this->context_->get_connection_hello_read ();
        std::string topic;
        if (reader->get_one (topic))
        {
          PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : read \"" << topic << "\"" << std::endl;

          this->hello_counter_++;
        }
        else
        {
          PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : no Hello topic" << std::endl;
        }
      }

      if (this->msg_subscription ()
          && this->count () > this->msg_counter_)
      {
        IDL::traits<Test::Msg::Getter>::ref_type reader =
          this->context_->get_connection_msg_read ();
        ::Test::Message topic;
        if (reader->get_one (topic))
        {
          PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : read [" << IDL::traits< ::Test::Message>::write (topic) << "]" << std::endl;

          this->msg_counter_++;
        }
        else
        {
          PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : no Message topic" << std::endl;
        }
      }

      if ((this->hello_subscription() && this->count () > this->hello_counter_)
            || (this->msg_subscription () && this->count () > this->msg_counter_))
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
        << ex.what() << std::endl;
    }
    catch (...)
    {
      PSDD4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
        << "ERROR caught unexpected exception"
        << std::endl;
    }
  }

  void Receiver_exec_i::increment_hello_counter (uint32_t n)
  {
    this->hello_counter_ += n;
  }

  void Receiver_exec_i::increment_msg_counter (uint32_t n)
  {
    this->msg_counter_ += n;
  }

  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    this->hello_subscription_ = (this->mode_.empty ()
                                  || this->mode_.find("HELLO") != std::string::npos
                                  || this->mode_.find("MSG") == std::string::npos);
    this->msg_subscription_ = (this->mode_.empty ()
                                  || this->mode_.find("MSG") != std::string::npos
                                  || this->mode_.find("HELLO") == std::string::npos);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    if (this->subscription_.empty ())
    {
      PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribing to any topic instance" << std::endl;

      // subscribe to all topic instances
      if (this->hello_subscription_)
      {
        auto hello_sub = this->context_->get_connection_hello_sub ();
        hello_sub->subscribe_any ();

        PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribed Hello topics" << std::endl;
      }
      if (this->msg_subscription_)
      {
        auto msg_sub = this->context_->get_connection_msg_sub ();
        msg_sub->subscribe_any ();

        PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribed Message topics" << std::endl;
      }
    }
    else
    {
      PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribing to [" << this->subscription_ << "] topic instances" << std::endl;

      // subscribe to selected topic instances
      if (this->hello_subscription_)
      {
        auto hello_sub = this->context_->get_connection_hello_sub ();
        hello_sub->subscribe (this->subscription_);

        PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribed Hello topics" << std::endl;
      }
      if (this->msg_subscription_)
      {
        auto msg_sub = this->context_->get_connection_msg_sub ();
        ::Test::Message msg {};
        msg.category (this->subscription_);
        msg_sub->subscribe (msg);

        PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribed Message topics" << std::endl;
      }
    }

    if (this->mode_.empty () || this->mode_.find ("READ") != std::string::npos)
    {
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
    }
    else
    {
      PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : activated in listen mode" << std::endl;
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
    PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_remove : received " << this->hello_counter_ << " Hello topic instances" << std::endl;
    PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_remove : received " << this->msg_counter_ << " Message topic instances" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::Test::Hello::CCM_Listener>::ref_type
  Receiver_exec_i::get_hello_listen ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[get_hello_listen]
    if (!this->hello_listen_)
    {
      this->hello_listen_ =
          CORBA::make_reference <hello_listen_exec_i> (
              IDL::traits<Test::CCM_Receiver>::narrow (this->_lock()),
              this->context_);
    }
    return this->hello_listen_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[get_hello_listen]
  }

  IDL::traits< ::Test::Msg::CCM_Listener>::ref_type
  Receiver_exec_i::get_msg_listen ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[get_msg_listen]
    if (!this->msg_listen_)
    {
      this->msg_listen_ =
          CORBA::make_reference <msg_listen_exec_i> (
              IDL::traits<Test::CCM_Receiver>::narrow (this->_lock()),
              this->context_);
    }
    return this->msg_listen_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[get_msg_listen]
  }


  std::string
  Receiver_exec_i::mode ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::mode[getter]
    return this->mode_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::mode[getter]
  }

  void
  Receiver_exec_i::mode (
      const std::string& mode)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::mode[setter]
    this->mode_ = mode;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::mode[setter]
  }

  std::string
  Receiver_exec_i::subscription ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::subscription[getter]
    return this->subscription_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::subscription[getter]
  }

  void
  Receiver_exec_i::subscription (
      const std::string& subscription)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::subscription[setter]
    this->subscription_ = subscription;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::subscription[setter]
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
    this->context_ = IDL::traits< ::Test::CCM_Receiver_Context >::narrow (std::move(ctx));
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
