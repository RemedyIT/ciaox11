// -*- C++ -*-
/*
 * @file    generator_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : generator_impl.cpp[Header]

#include "generator_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <iomanip>
#include <random>
#include <ctime>
//@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[user_global_impl]

namespace App_Generator_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[user_namespace_impl]
  //============================================================
  // Generator trigger callback
  //============================================================
  class TT_Generator
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Generator (std::string loc, IDL::traits< ::App::CCM_Generator_Context>::ref_type context)
      : location_ (loc),
        context_ (std::move(context)),
        dre_ (std::random_device ()()),
        uniform_dist_ (1000, 10000)
    {
    }

    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

    void passivate ()
    { this->passivated_ = true; }

    uint32_t message_count () const
    { return this->message_count_; }

  private:
    std::string location_;
    bool passivated_ {};
    IDL::traits< ::App::CCM_Generator_Context>::ref_type context_;
    std::default_random_engine dre_;
    std::uniform_int_distribution<int> uniform_dist_;
    uint32_t message_count_ {};
  };

  void
  TT_Generator::on_trigger (
      IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    CIAOX11_TEST_TRACE << "TT_Generator::on_trigger - timer[" << timer->id ()
                       << "] @ " << time.sec () << "."
                       << std::right << std::setfill('0') << std::setw(9)
                       << time.nanosec ()
                       << " #" << round
                       << " : " << this->location_ << std::endl;

    if (this->passivated_)
      return;

    // report environment change
    ::Data::Record data {
      this->location_,
      std::time(0),
      0.33 * this->uniform_dist_ (this->dre_),
      this->uniform_dist_ (this->dre_),
      true
    };

    try
    {
      this->context_->get_connection_my_recorder ()->submit_record_data (data);
      this->message_count_++;
    }
    catch (const CORBA::TRANSIENT&)
    {
      // ignore in non-active state when not using ExF
      if (this->passivated_ == false)
      {
        // for now always ignore
        // CIAOX11_TEST_ERROR << "App::Generator(" << this->location_ << "): caught exception [" << ex.what () << "]" << std::endl;
      }
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_ERROR << "App::Generator(" << this->location_ << "): caught exception [" << ex << "]" << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Generator_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[ctor]
  Generator_exec_i::Generator_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[ctor]

  Generator_exec_i::~Generator_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[user_private_ops]

  /** Session component operations */
  void Generator_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[configuration_complete]
  }

  void Generator_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[ccm_activate]
    this->th_gen_ = CORBA::make_reference<TT_Generator> (this->location_, this->context_);
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_gen = this->context_->get_connection_tt_generator ();
    this->tm_gen_ = tt_gen->schedule_repeated_trigger (
        this->th_gen_,
        CCM_TT::TT_Duration (0, 300000000),  // 300ms
        CCM_TT::TT_Duration (0, 300000000),  // 300ms
        0);

    CIAOX11_TEST_INFO << "App::Generator(" << this->location_ << "): activated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[ccm_activate]
  }

  void Generator_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[ccm_passivate]
    IDL::traits<TT_Generator>::narrow (this->th_gen_)->passivate ();
    if (this->tm_gen_)
    {
      this->tm_gen_->cancel ();

      CIAOX11_TEST_INFO << "App::Generator(" << this->location_ << "): "
    		  	  	    << IDL::traits<TT_Generator>::narrow (this->th_gen_)->message_count ()
						<< " messages sent" << std::endl;
    }

    CIAOX11_TEST_INFO << "App::Generator(" << this->location_ << "): passivated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[ccm_passivate]
  }

  void Generator_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[ccm_remove]
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[ccm_remove]
  }


  std::string
  Generator_exec_i::location ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i::location[getter]
    return this->location_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i::location[getter]
  }

  void
  Generator_exec_i::location (
      const std::string& location)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i::location[setter]
    this->location_ = location;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i::location[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Generator_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[set_session_context]
    this->context_ = IDL::traits< ::App::CCM_Generator_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[user_namespace_end_impl]

} // namespace App_Generator_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[factory]
extern "C" void
create_App_Generator_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <App_Generator_Impl::Generator_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : generator_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
