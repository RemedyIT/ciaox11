// -*- C++ -*-
/**
 * @file    mdd_state_listener_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component for the max delivered data test for the state listener
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : mdd_state_listener_impl.cpp[Header]

#include "mdd_state_listener_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl[user_global_impl]
constexpr uint16_t max_delivered_data () { return 2; }
//@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl[user_global_impl]

namespace MDD_State_Listener_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_state_listen_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[ctor]
  info_state_listen_data_listener_exec_i::info_state_listen_data_listener_exec_i (
    IDL::traits<MDD_State_Listener_Test::CCM_Receiver_Context>::ref_type context,
    atomic_thread_id &thread_id_on_creation,
    atomic_thread_id &thread_id_on_many_updates,
    std::atomic_ullong &sample_created_received,
    std::atomic_ullong &sample_updates_received)
    : context_ (std::move (context))
    , thread_id_on_creation_ (thread_id_on_creation)
    , thread_id_on_many_updates_ (thread_id_on_many_updates)
    , sample_created_received_ (sample_created_received)
    , sample_updates_received_ (sample_updates_received)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[ctor]

  info_state_listen_data_listener_exec_i::~info_state_listen_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_state_listen_data_listener */

  void
  info_state_listen_data_listener_exec_i::on_creation (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_creation[_datum_info]
    X11_UNUSED_ARG(info);
    this->thread_id_on_creation_ = std::this_thread::get_id ();
    DDS4CCM_TEST_DEBUG << "on_creation - " << datum << std::endl;
    // The first max_delivered_data samples and the reference sample are expected
    // to be received here.
    ++this->sample_created_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_creation[_datum_info]
  }

  void
  info_state_listen_data_listener_exec_i::on_one_update (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_one_update[_datum_info]
    X11_UNUSED_ARG(info);
    DDS4CCM_TEST_ERROR << "ERROR: unexpected on_one_update - " << datum << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_one_update[_datum_info]
  }

  void
  info_state_listen_data_listener_exec_i::on_many_updates (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_many_updates[_data_infos]
    X11_UNUSED_ARG(infos);
    this->thread_id_on_many_updates_ = std::this_thread::get_id ();
    this->sample_updates_received_ += data.size ();

    DDS4CCM_TEST_DEBUG << "on_many_updates - " << data << std::endl;

    if (data.size () > max_delivered_data ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_state_listen_data_listener_exec_i::on_many_updates - "
        << "Unexpected number of samples received. Expected <" << max_delivered_data ()
        << "> - got <" << data.size () << ">." << std::endl;
    }

    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_many_updates[_data_infos]
  }

  void
  info_state_listen_data_listener_exec_i::on_deletion (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_deletion[_datum_info]
    X11_UNUSED_ARG(info);
    DDS4CCM_TEST_ERROR << "ERROR: unexpected on_deletion - " << datum << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_data_listener_exec_i::on_deletion[_datum_info]
  }
  /**
   * Facet Executor Implementation Class : info_state_listen_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[ctor]
  info_state_listen_status_exec_i::info_state_listen_status_exec_i (
    IDL::traits<MDD_State_Listener_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[ctor]

  info_state_listen_status_exec_i::~info_state_listen_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i[user_private_ops]


  /** Operations and attributes from info_state_listen_status */

  void
  info_state_listen_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "ERROR: unexpected on_requested_deadline_missed - " << status << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_state_listen_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "ERROR: unexpected on_sample_lost - " << status << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::info_state_listen_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits< ::CCM_DDS::DataListenerControl >::ref_type lc =
      this->context_->get_connection_info_state_listen_data_control ();
    if (!lc)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener control receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc->mode (::CCM_DDS::ListenerMode::MANY_BY_MANY);
    lc->max_delivered_data (max_delivered_data ());
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    if (this->sample_created_received_ != 0)
    {
      DDS4CCM_TEST_UTILS::check_thread_switch ("on_creation", this->thread_id_on_creation_);
    }
    if (this->sample_updates_received_ != 0)
    {
      DDS4CCM_TEST_UTILS::check_thread_switch ("on_many_updates", this->thread_id_on_many_updates_);
    }

    // Only check the total number of samples since it's not guaranteed that
    // we will receive max_delivered_data in on_creation; it could be one...
    // In total we have to receive 21 since the reference sample counts as well.
    if (this->sample_updates_received_ + this->sample_created_received_ != 21)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_remove - "
        << "Unexpected number of callbacks. Expected <21> - got <"
        << this->sample_updates_received_ + this->sample_created_received_
        << ">." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_remove - "
        << "Received expected number of callbacks, got <"
        << this->sample_updates_received_ + this->sample_created_received_
        << ">." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CommonTestConnector::CCM_StateListener >::ref_type
  Receiver_exec_i::get_info_state_listen_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[get_info_state_listen_data_listener]
  if (!this->info_state_listen_data_listener_)
  {
    this->info_state_listen_data_listener_ =
      CORBA::make_reference <info_state_listen_data_listener_exec_i>
        (this->context_,
         this->thread_id_on_creation_,
         this->thread_id_on_many_updates_,
         this->sample_created_received_,
         this->sample_updates_received_);
  }
  return this->info_state_listen_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[get_info_state_listen_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_info_state_listen_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[get_info_state_listen_status]
  if (!this->info_state_listen_status_)
  {
    this->info_state_listen_status_ = CORBA::make_reference <info_state_listen_status_exec_i> (this->context_);
  }
  return this->info_state_listen_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[get_info_state_listen_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<MDD_State_Listener_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace MDD_State_Listener_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_State_Listener_Test_Receiver_Impl[factory]
extern "C" void
create_MDD_State_Listener_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <MDD_State_Listener_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : MDD_State_Listener_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : mdd_state_listener_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
