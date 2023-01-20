// -*- C++ -*-
/**
 * @file    latency_receiver_exec.cpp
 * @author  Martin Corino
 *
 * @brief   Receiver component implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : latency_receiver_impl.cpp[Header]

#include "latency_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_includes]
#include "psdd4ccm/logger/psdd4ccm_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_global_impl]

#define catch_psdd4ccm_test_ex(ex, L) \
  catch (const CORBA::Exception &ex) \
  { \
    PSDD4CCM_TEST_ERROR << "ERROR: " << L << " - " \
      << "caught unexpected CORBA exception: " \
      << ex << std::endl; \
  } \
  catch (const std::exception &ex) \
  { \
    PSDD4CCM_TEST_ERROR << "ERROR: " << L << " - " \
      << "caught std::exception: " \
      << ex << std::endl; \
  } \
  catch (...) \
  { \
    PSDD4CCM_TEST_ERROR << "ERROR: " << L << " - " \
      << "ERROR caught unexpected exception" \
      << std::endl; \
  }

//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_global_impl]

namespace Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i[ctor]
  info_out_exec_i::info_out_exec_i (
      IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context,
      IDL::traits< ::Test::CCM_Receiver>::ref_type component_executor)
      : context_ (std::move (context))
      , component_executor_ (std::move (component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i[ctor]

  info_out_exec_i::~info_out_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i[user_public_ops]
  void
  info_out_exec_i::shutdown ()
  {
    this->component_executor_.reset ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i[user_private_ops]


  /** Operations and attributes from info_out */

  void
  info_out_exec_i::on_data (
      ::Test::LatencyDataSeq& data)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i::on_data[_data]
    if (this->component_executor_)
    {
      IDL::traits<Receiver_exec_i>::narrow(this->component_executor_)->echo (const_cast<Test::LatencyData&> (data.front ()));
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i::on_data[_data]
  }

  ::CCM_PSDD::ListenerMode
  info_out_exec_i::listen_mode ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i::listen_mode[getter]
    return this->listen_mode_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i::listen_mode[getter]
  }

  void
  info_out_exec_i::listen_mode (
      ::CCM_PSDD::ListenerMode listen_mode)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i::listen_mode[setter]
    this->listen_mode_ = listen_mode;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i::listen_mode[setter]
  }

  ::CCM_PSDD::DataCount_t
  info_out_exec_i::max_data ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i::max_data[getter]
    return this->max_data_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i::max_data[getter]
  }

  void
  info_out_exec_i::max_data (
      ::CCM_PSDD::DataCount_t max_data)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_exec_i::max_data[setter]
    this->max_data_ = max_data;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_exec_i::max_data[setter]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
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
  Receiver_exec_i::echo (const Test::LatencyData & an_instance)
  {
    ++this->count_;
    this->writer_->write_one(an_instance);
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  void
  Receiver_exec_i::start ()
  {
    this->get_info_out()->listen_mode(::CCM_PSDD::ListenerMode::ONE_BY_ONE);
    auto info_sub = this->context_->get_connection_info_sub ();
    info_sub->subscribe_any ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    try
    {
      this->writer_ = this->context_->get_connection_info_echo();
      // Enable the datalistener.
      this->start ();

      PSDD4CCM_TEST_INFO << "Receiver_exec_i::ccm_activate - started" << std::endl;
    }
    catch_psdd4ccm_test_ex(ex, "Receiver_exec_i::ccm_activate")
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->info_out_)
    {
      IDL::traits<info_out_exec_i>::narrow(this->info_out_)->shutdown ();
    }
    if (this->count_ == 0)
    {
      PSDD4CCM_TEST_ERROR << "ERROR RECEIVER: No messages sent back." << std::endl;
    }
    else
    {
      PSDD4CCM_TEST_INFO << "SUMMARY RECEIVER:" << std::endl <<
                           " Total number of messages sent back: " <<
                            this->count_ << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::Test::LatencyDataConnector::CCM_Listener>::ref_type
  Receiver_exec_i::get_info_out ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[get_info_out]
    if (!this->info_out_)
    {
      this->info_out_ = IDL::traits< ::Test::LatencyDataConnector::CCM_Listener>::make_reference <info_out_exec_i> (
          this->context_,
          IDL::traits<::Test::CCM_Receiver>::narrow (this->_lock()));
    }
    return this->info_out_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[get_info_out]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Test::CCM_Receiver_Context>::narrow (std::move(ctx));
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
  component = IDL::traits< ::Test::CCM_Receiver>::make_reference <Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : latency_receiver_impl.cpp[Footer]
// Your footer (code) here
