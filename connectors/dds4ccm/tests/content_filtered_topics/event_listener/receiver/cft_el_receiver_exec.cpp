// -*- C++ -*-
/**
 * @file    cft_el_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation
 *
 * Receiver implementation for a ContentFiltered topic test. This receiver tests
 * the content filtered topic on a listener.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : cft_el_receiver_impl.cpp[Header]

#include "cft_el_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[user_global_impl]
constexpr uint16_t min_iteration () { return 2; }
constexpr uint16_t max_iteration () { return 5; }
//@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[user_global_impl]

namespace CFT_EL_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_listen_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[ctor]
  info_listen_data_listener_exec_i::info_listen_data_listener_exec_i (
      IDL::traits<CFT_EL_Test::CCM_Receiver_Context>::ref_type context,
      std::atomic_ulong &samples_received,
      atomic_thread_id &thread_id)
    : context_ (std::move (context))
    , samples_received_ (samples_received)
    , thread_id_ (thread_id)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[ctor]

  info_listen_data_listener_exec_i::~info_listen_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_listen_data_listener */

  void
  info_listen_data_listener_exec_i::on_one_data (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i::on_one_data[_datum_info]
    ++this->samples_received_;
    this->thread_id_ = std::this_thread::get_id ();
    DDS4CCM_TEST_DEBUG << "info_listen_data_listener_exec_i::on_one_data: "
      << datum << std::endl;

    if (info.instance_handle () == ::DDS::HANDLE_NIL)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_listen_data_listener_exec_i::on_one_data: "
        "instance handle seems to be invalid " << datum << std::endl;
    }
    if (info.source_timestamp ().sec () == 0 && info.source_timestamp ().nanosec () == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_listen_data_listener_exec_i::on_one_data: "
        << "source timestamp seems to be invalid (nil) for " << datum << std::endl;
    }
    if (datum.iteration () <= min_iteration () || datum.iteration ()  > max_iteration ())
    {
      DDS4CCM_TEST_ERROR << "info_listen_data_listener_exec_i::on_one_data: "
        << "ERROR: Unexpected iteration received: " << datum << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_listen_data_listener_exec_i::on_many_data (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);

    DDS4CCM_TEST_ERROR << "info_listen_data_listener_exec_i::on_many_data: "
      "ERROR: Unexpected invocation" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_listen_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[ctor]
  info_listen_status_exec_i::info_listen_status_exec_i (
    IDL::traits<CFT_EL_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[ctor]

  info_listen_status_exec_i::~info_listen_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_private_ops]


  /** Operations and attributes from info_listen_status */

  void
  info_listen_status_exec_i::on_requested_deadline_missed (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_listen_status_exec_i::on_sample_lost (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits<::CCM_DDS::DataListenerControl>::ref_type lc =
      this->context_->get_connection_info_listen_data_control ();

    lc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->samples_received_ != this->samples_expected_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: CFT_EVENT: ReaderListener: "
        << "Unexpected number of samples received: expected <"
        << this->samples_expected_ << "> - received <"
        << this->samples_received_ << ">." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "CFT_EVENT: ReaderListener: "
        << "Expected number of samples received: expected <"
        << this->samples_expected_ << "> - received <"
        << this->samples_received_ << ">." << std::endl;
    }
    DDS4CCM_TEST_UTILS::check_thread_switch ("Data Listener", this->thread_id_listener_);
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::CommonTestConnector::CCM_Listener>::ref_type
  Receiver_exec_i::get_info_listen_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[get_info_listen_data_listener]
    if (!this->info_listen_data_listener_)
    {
      this->info_listen_data_listener_ = CORBA::make_reference <info_listen_data_listener_exec_i> (
        this->context_, this->samples_received_, this->thread_id_listener_);
    }
    return this->info_listen_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[get_info_listen_data_listener]
  }

  IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_listen_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[get_info_listen_status]
    if (!this->info_listen_status_)
    {
      this->info_listen_status_ = CORBA::make_reference <info_listen_status_exec_i> (this->context_);
    }
    return this->info_listen_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[get_info_listen_status]
  }


  uint16_t
  Receiver_exec_i::keys ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::keys[getter]
    return this->keys_;
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::keys[getter]
  }

  void
  Receiver_exec_i::keys (
      uint16_t keys)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::keys[setter]
    this->keys_ = keys;
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::keys[setter]
  }

  uint16_t
  Receiver_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::iterations[getter]
  }

  void
  Receiver_exec_i::iterations (
      uint16_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i::iterations[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<CFT_EL_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace CFT_EL_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[factory]
extern "C" void
create_CFT_EL_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <CFT_EL_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : cft_el_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
