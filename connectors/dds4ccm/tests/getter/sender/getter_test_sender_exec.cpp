// -*- C++ -*-
/**
 * @file    getter_test_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the Getter test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : getter_test_sender_impl.cpp[Header]

#include "getter_test_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl[user_global_impl]

namespace Getter_Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl[user_namespace_impl]
  class TT_Callback final
         : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits< ::Getter_Test::CCM_Sender>::weak_ref_type component_executor,
        bool activate)
    : component_executor_(component_executor)
     , activate_(activate)
    {}

    void
    on_trigger (
       IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
       const ::CCM_TT::TT_Duration& time,
       uint32_t round) override;

   private:
     IDL::traits< ::Getter_Test::CCM_Sender>::weak_ref_type component_executor_;
     bool const activate_;
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
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      if (this->activate_)
        cex->check_status();
      else
        cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[ctor]
  info_out_connector_status_exec_i::info_out_connector_status_exec_i (
    IDL::traits<Getter_Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<Getter_Test::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
    DDS4CCM_TEST_DEBUG << "Sender_ info_out_connector_status_exec_i::info_out_connector_status_exec_i" << std::endl;

  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[ctor]

  info_out_connector_status_exec_i::~info_out_connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_connector_status */

  void
  info_out_connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    DDS4CCM_TEST_DEBUG << "Sender_ info_out_connector_status_exec_i::on_inconsistent_topic" << std::endl;

    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  info_out_connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    DDS4CCM_TEST_DEBUG << "Sender_ info_out_connector_status_exec_i::on_requested_incompatible_qos" << std::endl;

    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  info_out_connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_sample_rejected[_the_reader_status]
    DDS4CCM_TEST_DEBUG << "Sender_ info_out_connector_status_exec_i::on_sample_rejected" << std::endl;

    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  info_out_connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    DDS4CCM_TEST_DEBUG << "Sender_ info_out_connector_status_exec_i::on_offered_deadline_missed" << std::endl;

    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  info_out_connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    DDS4CCM_TEST_DEBUG << "Sender_ info_out_connector_status_exec_i::on_offered_incompatible_qos" << std::endl;

    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  info_out_connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "info_out_connector_status_exec_i::on_unexpected_status status_kind <" << DDS::dds_write(status_kind) << ">" << std::endl;
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // started_ flag.
    if (!this->started_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 1))
      {
        auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
        if (cex)
        {
          this->started_ = true;
          cex->start_publishing ();
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status - "
                            << "WARNING: failed to lock component executor" << std::endl;
        }
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::info_out_connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::check_status ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status " << std::endl;
    try
    {
      IDL::traits< ::DDS::DataWriter>::ref_type writer_dds_entity =
        this->context_->get_connection_info_write_dds_entity ();
      if (writer_dds_entity)
      {
        ::DDS::PublicationMatchedStatus status {};
        ::DDS::ReturnCode_t const retcode = writer_dds_entity->get_publication_matched_status (status);

        if (retcode != ::DDS::RETCODE_OK)
        {
          DDS4CCM_TEST_ERROR <<"Sender_exec_i::check_status - "
            << "Error: Unable to get_publication_matched_status: <"
            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
            << ">." << std::endl;
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched current_count: "
                           << status.current_count() << std::endl;

          if (status.current_count() == 1)
          {
            DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched received" << std::endl;
            this->tm_activate_->cancel();
            this->start_publishing();
          }
        }
      }
    }
    catch (const std::exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Internal Error Sender_exec_i::check_status "
                        << ex << std::endl;
    }
  }


  void
  Sender_exec_i::start_publishing ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::start_publishing" << std::endl;
    if (!this->already_publishing_)
    {
      this->already_publishing_ = true;
      this->tm_activate_->cancel();

      // Start can be called more than once...
      start_timeout_tests ();

      this->tm_ = tt_s->schedule_repeated_trigger (
                        CORBA::make_reference<TT_Callback> (IDL::traits< Getter_Test::CCM_Sender>::narrow (this->_lock()),false),
                        CCM_TT::TT_Duration (0, 500000000),
                        CCM_TT::TT_Duration (0, 500000000),
                        0);
    }
  }

  void
  Sender_exec_i::tick ()
  {

    IDL::traits<CommonTestConnector::Writer>::ref_type writer =
      this->context_->get_connection_info_write_data ();
    IDL::traits< GetInvoker>::ref_type invoker =
      this->context_->get_connection_invoke_getter ();

    if (this->last_iter_ <= this->iterations_)
      {
        CommonTestMessage new_key ("KEY_1", this->last_iter_);
        // Inform the receiver that the sender is about to
        // write samples to DDS.
        invoker->start_get_one ("KEY_1", last_iter_);

        std::this_thread::sleep_for (std::chrono::milliseconds (50));

        writer->write_one (new_key, ::DDS::HANDLE_NIL);
        DDS4CCM_TEST_DEBUG << "Written key " << new_key << std::endl;

        ++this->last_iter_;
    }
   else
    {
      // Stop the timer at forehand.
      this->tm_->cancel();
     // Perform the last test.
      this->write_many ();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::start_timeout_tests ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::start_time_out_tests" << std::endl;
    IDL::traits< GetInvoker>::ref_type invoker =
      this->context_->get_connection_invoke_getter ();

    invoker->start_timeout_get_one ();
    invoker->start_timeout_get_many ();
  }

  void
  Sender_exec_i::write_many ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::write_many" << std::endl;
    IDL::traits<CommonTestConnector::Writer>::ref_type writer =
      this->context_->get_connection_info_write_data ();
    IDL::traits< GetInvoker>::ref_type invoker =
      this->context_->get_connection_invoke_getter ();

    // Prepare the samples.
    CommonTestMessageSeq write_many (this->keys_ * this->iterations_);

    // since the test for get_one already writes samples to DDS with
    // key=KEY_1 we start with key = 2 when writing many samples.
    for (uint16_t key = 2; key < this->keys_ + 2; ++key)
    {
      CommonTestMessage new_key;
      new_key.key ("KEY_"+std::to_string (key));

      for (uint16_t iter = 1; iter < this->iterations_ + 1; ++iter)
      {
        new_key.iteration (iter);
        write_many[(iter - 1) + ((key - 2) * 10)] = new_key;
      }
    }
    try
    {
      // Inform the receiver that the sender has written many
      // samples to DDS.
      invoker->start_get_many (this->keys_, this->iterations_);
      // Wait a while before writing the samples.
      std::this_thread::sleep_for (std::chrono::seconds (2));
      // Now start writing.
      writer->write_many (write_many);
      DDS4CCM_TEST_DEBUG << "write_many : written <" << write_many.size ()
        << "> samples" << std::endl;
    }
    catch (const CCM_DDS::InternalError& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Internal Error while write many writer : "
        << ex << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[ccm_activate]
    // Your code here
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_activate" << std::endl;
    this->tt_s = this->context_->get_connection_tt_scheduler ();
    this->tm_activate_ = this->tt_s->schedule_repeated_trigger (
                           CORBA::make_reference<TT_Callback> (IDL::traits< Getter_Test::CCM_Sender>::narrow (this->_lock()),true),
                           CCM_TT::TT_Duration (0, 1000000000),
                           CCM_TT::TT_Duration (0, 1000000000),
                           0);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (!this->tm_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                            "Test did not start, because no DDS::PUBLICATION_MATCHED_STATUS was received."
                         << std::endl;
    }
    else
    {
      if (!this->tm_->is_canceled())
      {
        this->tm_->cancel();
      }
      if (this->tm_->rounds() < 1)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                              "Timer of tests didn't tick." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_passivate - "
                              "Timer ticked " << this->tm_->rounds() << " times." << std::endl;
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_exec_i::get_info_out_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[get_info_out_connector_status]
    if (!this->info_out_connector_status_)
      {
        this->info_out_connector_status_ =
          CORBA::make_reference <info_out_connector_status_exec_i>
            (this->context_, IDL::traits<Getter_Test::CCM_Sender>::narrow (this->_lock()));
      }
    return this->info_out_connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[get_info_out_connector_status]
  }


  uint16_t
  Sender_exec_i::keys ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i::keys[getter]
    return this->keys_;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i::keys[getter]
  }

  void
  Sender_exec_i::keys (
      uint16_t keys)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i::keys[setter]
    this->keys_ = keys;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i::keys[setter]
  }

  uint16_t
  Sender_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i::iterations[getter]
  }

  void
  Sender_exec_i::iterations (
      uint16_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i::iterations[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<Getter_Test::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl[user_namespace_end_impl]

} // namespace Getter_Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Sender_Impl[factory]
extern "C" void
create_Getter_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Getter_Test_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : getter_test_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
