// -*- C++ -*-
/**
 * @file    unkeyed_writer_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the unkeyed Writer test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : unkeyed_writer_receiver_impl.cpp[Header]

#include "unkeyed_writer_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl[user_global_impl]

namespace UnkeyedWriterTest_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits<UnkeyedWriterTest::CCM_Receiver_Context>::ref_type context,
    uint16_t iterations,
    std::atomic<uint32_t> &samples_received)
    : context_ (std::move (context))
    , iterations_ (iterations)
    , samples_received_ (samples_received)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::UnkeyedWriterTest::UnkeyedWriterMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(info);
    if (datum.sample_index () != this->samples_received_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: received sample <" << datum.sample_index ()
        << "> but we expected sample <"
        << this->samples_received_ << ">" << std::endl;
    }
    ++this->samples_received_;
    DDS4CCM_TEST_DEBUG << "info_out_data_listener_exec_i::on_one_data received writer "
      << "info : " << datum << std::endl;
    if (datum.iteration () > this->iterations_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: received iteration greater than expected : "
        << "expected <" << this->iterations_ << "> - received <"
        << datum.iteration () << ">" << std::endl;
    }
    if (datum.iteration () == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: received iteration is zero" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::UnkeyedWriterTest::UnkeyedWriterMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits<UnkeyedWriterTest::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits<::CCM_DDS::DataListenerControl>::ref_type lc =
      this->context_->get_connection_info_out_data_control ();

    if (!lc)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener control receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    uint32_t const expected = (2 * this->keys_ * this->iterations_) - this->keys_;
    bool qos_used = true;

    try
    {
      IDL::traits<UnkeyedWriterTest::UnkeyedWriterMessageConnector::Reader>::ref_type reader =
        this->context_->get_connection_info_out_data ();
      IDL::traits<UnkeyedWriterTest::UnkeyedWriterMessageConnector::CCM_DDS_Event>::ref_type conn =
        IDL::traits<UnkeyedWriterTest::UnkeyedWriterMessageConnector::CCM_DDS_Event >::narrow (
          reader->_get_component ());
      qos_used = !conn->qos_profile ().empty ();
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::ccm_passivate")

    if (qos_used)
    {
      if (this->samples_received_ != expected)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
          << "Did not receive the expected number of samples: "
          << "expected <" << expected << "> - received <"
          << this->samples_received_ << ">" << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_passivate - "
                  << "Did receive the expected number of samples: "
                  << "expected <" << expected << "> - received <"
                  << this->samples_received_ << ">" << std::endl;
      }
    }
    else
    {
      if (this->samples_received_ < expected * 0.1)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
          << "Did not receive the expected number of samples: "
          << "expected at least ten percent of <" << expected << "> - received <"
          << this->samples_received_ << ">" << std::endl;
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::UnkeyedWriterTest::UnkeyedWriterMessageConnector::CCM_Listener>::ref_type
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
    if (!this->info_out_data_listener_)
      {
        this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (this->context_,
          this->iterations_, this->samples_received_);
      }
    return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[get_info_out_status]
    if (!this->info_out_status_)
      {
        this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (this->context_);
      }
    return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  }


  uint16_t
  Receiver_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::iterations[getter]
  }

  void
  Receiver_exec_i::iterations (
      uint16_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::iterations[setter]
  }

  uint16_t
  Receiver_exec_i::keys ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::keys[getter]
    return this->keys_;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::keys[getter]
  }

  void
  Receiver_exec_i::keys (
      uint16_t keys)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::keys[setter]
    this->keys_ = keys;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i::keys[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<UnkeyedWriterTest::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl[user_namespace_end_impl]

} // namespace UnkeyedWriterTest_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Receiver_Impl[factory]
extern "C" void
create_UnkeyedWriterTest_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UnkeyedWriterTest_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : unkeyed_writer_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
