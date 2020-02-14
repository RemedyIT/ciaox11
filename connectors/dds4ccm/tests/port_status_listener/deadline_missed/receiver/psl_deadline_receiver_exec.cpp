// -*- C++ -*-
/**
 * @file    psl_deadline_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the deadline missed callback on
 *          the Port Status Listener.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psl_deadline_receiver_impl.cpp[Header]

#include "psl_deadline_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[user_global_impl]

namespace PSL_DeadlineTest_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::PSL_DeadlineTest::CCM_Receiver>::weak_ref_type component_executor)
              : component_executor_(component_executor)
    {}

    virtual
    void
    on_trigger (
         IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
         const ::CCM_TT::TT_Duration& time,
         uint32_t round) override;

   private:
     IDL::traits< ::PSL_DeadlineTest::CCM_Receiver>::weak_ref_type component_executor_;
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
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
      IDL::traits<PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context,
      std::atomic_ushort &nr_invocations,
      atomic_thread_id &thread_id)
    : context_ (std::move (context))
    , nr_invocations_ (nr_invocations)
    , thread_id_ (thread_id)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    DDS4CCM_TEST_DEBUG << "info_get_status_exec_i::on_requested_deadline_missed - "
      << "on_requested_deadline_missed for DataReader <" << ::DDS::dds_write (the_reader)
      << "> received in PSL of the Getter. Status info : " << ::DDS::dds_write (status)
      << std::endl;
    if (the_reader && status.total_count () != 0)
    {
      ++this->nr_invocations_;
      this->thread_id_ =  std::this_thread::get_id();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits<PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG (info);
    DDS4CCM_TEST_ERROR << "info_out_data_listener_exec_i::on_one_data - "
      "ERROR: invocation of on_one_data : " << datum << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    DDS4CCM_TEST_ERROR << "info_out_data_listener_exec_i::on_many_data - "
      "ERROR: invocation of on_many_data." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
      IDL::traits<PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context,
      std::atomic_ushort &nr_invocations,
      atomic_thread_id &thread_id)
    : context_ (std::move (context))
    , nr_invocations_ (nr_invocations)
    , thread_id_ (thread_id)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    if (the_reader && status.total_count () != 0)
    {
      DDS4CCM_TEST_DEBUG << "info_get_status_exec_i::on_requested_deadline_missed - "
        << "on_requested_deadline_missed for DataReader <" << ::DDS::dds_write (the_reader)
        << "> received in PSL of the Listener. Status info : " << ::DDS::dds_write (status)
        << std::endl;

      ++this->nr_invocations_;
      this->thread_id_ =  std::this_thread::get_id();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_public_ops]
  void
  Receiver_exec_i::tick ()
  {
    IDL::traits< ::CommonTestConnector::Reader>::ref_type reader =
      this->context_->get_connection_info_out_data ();
    if (!reader)
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::tick - "
                         << "ERROR: reader is nil" << std::endl;
    }
    CommonTestMessageSeq messages;
    ::CCM_DDS::ReadInfoSeq readinfoseq;
    try
    {
      reader->read_all(messages, readinfoseq);
      for (CommonTestMessageSeq::size_type i = 0; i < messages.size (); ++i)
      {

        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::tick - "
          << "Timestamp for sample <" << messages[i] << ">: "
          << ::DDS::dds_write (readinfoseq[i].source_timestamp ())
          << std::endl;
        if (messages[i].key () != "ONE" && messages[i].key () != "TWO")
        {
          DDS4CCM_TEST_ERROR << "Receiver_exec_i::tick - "
            << "ERROR: Unexpected data received: " << messages[i] << std::endl;
        }
      }
    }
    catch (const CCM_DDS::InternalError& ex)
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::tick - "
        "ERROR: Internal Error caught <" << ex << ">" << std::endl;
    }

  }

  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
    this->tm_ = tt_s->schedule_repeated_trigger (
                           CORBA::make_reference<TT_Callback> (IDL::traits< PSL_DeadlineTest::CCM_Receiver>::narrow (this->_lock())),
                           CCM_TT::TT_Duration (1, 0),
                           CCM_TT::TT_Duration (1, 300000000),
                           0);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (!this->tm_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver did not tick " << std::endl;
    }
    else
    {
      this->tm_->cancel();
      DDS4CCM_TEST_DEBUG << "Receiver ticked <" << this->tm_->rounds() << "> times." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ccm_remove]
    if (this->nr_invocations_get_port_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: did not receive the expected "
        << "error 'on_requested_deadline_missed' on PortStatusListener Get "
        << "in Receiver" << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "OK : Have received the expected "
        << "'on_requested_deadline_missed' <" << this->nr_invocations_get_port_
        << "> times in PortStatusListener Get in Receiver."
        << std::endl;
      DDS4CCM_TEST_UTILS::check_thread_switch ("PortStatusListener Get", this->thread_id_get_port_);
    }
    if (this->nr_invocations_listen_port_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: did not receive the expected error "
        << "'on_requested_deadline_missed' on PortStatusListener Listener "
        << "in Receiver." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "OK : Have received the expected "
        << "'on_requested_deadline_missed' <" << this->nr_invocations_listen_port_
        << "> times in PortStatusListener Listener in Receiver"
        << std::endl;
      DDS4CCM_TEST_UTILS::check_thread_switch ("PortStatusListener Listener", this->thread_id_listen_port_);
    }

    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (
      this->context_, this->nr_invocations_get_port_, this->thread_id_get_port_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  }

  IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  if (!this->info_out_data_listener_)
  {
    this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (this->context_);
  }
  return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  if (!this->info_out_status_)
  {
    this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (
      this->context_, this->nr_invocations_listen_port_, this->thread_id_listen_port_);
  }
  return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<PSL_DeadlineTest::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[user_namespace_end_impl]

} // namespace PSL_DeadlineTest_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[factory]
extern "C" void
create_PSL_DeadlineTest_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
