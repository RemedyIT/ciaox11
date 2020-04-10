// -*- C++ -*-
/**
 * @file    psdd_receiver_exec.cpp
 * @author  Martin Corino
 *
 * @brief   PSDD Receiver executor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
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
          PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::tick : read \"" << IDL::traits<Test::Topic>::write (topic) << "\"" << std::endl;

          this->topic_counter_++;
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
        << ex.what() << std::endl;
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
  // Your code here
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
    if (this->filter ())
    {
      PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribing to even topics" << std::endl;

      // subscribe to even topic instances
      ::Test::Topic topic {};
      auto topic_sub = this->context_->get_connection_topic_sub ();
      topic = 2;
      topic_sub->subscribe (topic);
    }
    else
    {
      PSDD4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate : subscribing to any topic instance" << std::endl;

      // subscribe to all topic instances
      auto topic_sub = this->context_->get_connection_topic_sub ();
      topic_sub->subscribe_any ();
    }

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


  bool
  Receiver_exec_i::filter ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::filter[getter]
    return this->filter_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::filter[getter]
  }

  void
  Receiver_exec_i::filter (
      bool filter)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i::filter[setter]
    this->filter_ = filter;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i::filter[setter]
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
