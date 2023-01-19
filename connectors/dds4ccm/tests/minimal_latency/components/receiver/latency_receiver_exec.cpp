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
#include "dds4ccm/logger/dds4ccm_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_global_impl]

namespace Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context,
    IDL::traits< ::Test::CCM_Receiver>::ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move (component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  void
  info_out_data_listener_exec_i::shutdown ()
  {
    this->component_executor_.reset ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::Test::LatencyData& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    //DDS4CCM_TEST_DEBUG << "info_out_data_listener_exec_i::on_one_data : " << std::endl <<
    //                      " datum:" << datum << std::endl <<
    //                      " info:" << DDS::dds_write(info) << std::endl;

    if (info.instance_status() == ::CCM_DDS::InstanceStatus::INSTANCE_CREATED
        || info.instance_status() == ::CCM_DDS::InstanceStatus::INSTANCE_UPDATED)
    {
      if (this->component_executor_)
      {
        IDL::traits<Receiver_exec_i>::narrow(this->component_executor_)->echo (const_cast<Test::LatencyData&> (datum));
      }
//      else
//      {
//        DDS4CCM_TEST_WARNING << "info_out_data_listener_exec_i::on_one_data - "
//                             << "WARNING: failed to lock component executor" << std::endl;
//      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::Test::LatencyDataSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
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
    this->writer_->write_one(an_instance, ::DDS::HANDLE_NIL);
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  void
  Receiver_exec_i::start ()
  {
    IDL::traits<::CCM_DDS::DataListenerControl>::ref_type dlc =
      this->context_->get_connection_info_out_data_control ();
    dlc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);
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
      this->writer_ = this->context_->get_connection_info_echo_data ();
      // Enable the datalistener.
      this->start ();
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::ccm_activate")
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->info_out_data_listener_)
    {
      IDL::traits<info_out_data_listener_exec_i>::narrow(this->info_out_data_listener_)->shutdown ();
    }
    if (this->count_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR RECEIVER: No messages sent back." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_INFO << "SUMMARY RECEIVER:" << std::endl <<
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
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
    if (!this->info_out_data_listener_)
    {
      this->info_out_data_listener_ =
          IDL::traits< ::Test::LatencyDataConnector::CCM_Listener>::make_reference <info_out_data_listener_exec_i> (
              this->context_,
              IDL::traits<::Test::CCM_Receiver>::narrow (this->_lock()));
    }
    return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[get_info_out_status]
    if (!this->info_out_status_)
    {
      this->info_out_status_ = IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::make_reference <info_out_status_exec_i> (this->context_);
    }
    return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[get_info_out_status]
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
  component = IDL::traits< ::Test::CCM_Receiver>::make_reference < Test_Receiver_Impl::Receiver_exec_i > ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : latency_receiver_impl.cpp[Footer]
// Your footer (code) here
