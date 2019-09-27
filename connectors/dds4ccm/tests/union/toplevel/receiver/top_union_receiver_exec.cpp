// -*- C++ -*-
/**
 * @file    top_union_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : top_union_receiver_impl.cpp[Header]

#include "top_union_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_global_impl]
#define SAMPLES_EXPECTED 2*3+1
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_global_impl]

namespace Uni_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits< ::Uni::CCM_Receiver_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    if (this->samples_received_ != SAMPLES_EXPECTED)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::~info_out_data_listener_exec_i - "
        << "Unexpected number of samples received. Expected <" << SAMPLES_EXPECTED
        << "> - got <" << this->samples_received_ << ">." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "info_out_data_listener_exec_i::~info_out_data_listener_exec_i - "
        << "Received expected <" << SAMPLES_EXPECTED
        << "> samples." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::Uni::TopUnionMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::Uni::TopUnionMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(infos);

    this->samples_received_ += ACE_Utils::truncate_cast<uint16_t> (data.size ());

    for (const Uni::TopUnionMessage& msg : data)
    {
      if (msg._d () == 4)
      {
        if (msg.x () != 5)
        {
          DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::on_many_data - "
            << "Unexpected value for x found. Expected <5> - "
            << "got <" << msg.x () << ">." << std::endl;
        }
      }
      else if (msg._d () == 5)
      {
        if (msg.y () < 0 || msg.y () > 2)
        {
          DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::on_many_data - "
            << "Unexpected value for y found. Expected values between 0 and 2 - "
            << "got <" << msg.y () << ">." << std::endl;
        }
      }
      else if (msg._d () == 6)
      {
        if (msg.y () < 3 || msg.y () > 5)
        {
          DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::on_many_data - "
            << "Unexpected value for y found. Expected values between 3 and 5 - "
            << "got <" << msg.y () << ">." << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::on_many_data - "
          << "Unexpected value for the discriminator found. Expected <4 or 5> - "
          << "got <" << msg._d () << ">." << std::endl;
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits< ::Uni::CCM_Receiver_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits< ::CCM_DDS::DataListenerControl >::ref_type lc =
      this->context_->get_connection_info_out_data_control ();
    lc->mode (::CCM_DDS::ListenerMode::MANY_BY_MANY);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::Uni::TopUnionConnector::CCM_Listener >::ref_type
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
    if (!this->info_out_data_listener_)
    {
      this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (this->context_);
    }
    return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_status]
    if (!this->info_out_status_)
    {
      this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (this->context_);
    }
    return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Uni::CCM_Receiver_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_namespace_end_impl]

} // namespace Uni_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[factory]
extern "C" void
create_Uni_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Uni_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : top_union_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
