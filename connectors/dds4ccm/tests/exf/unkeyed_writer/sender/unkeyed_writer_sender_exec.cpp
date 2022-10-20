// -*- C++ -*-
/**
 * @file    unkeyed_writer_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the unkeyed Writer test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : unkeyed_writer_sender_impl.cpp[Header]

#include "unkeyed_writer_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[user_global_impl]

namespace UnkeyedWriterTest_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits< ::UnkeyedWriterTest::CCM_Sender>::weak_ref_type component_executor,
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
    IDL::traits< ::UnkeyedWriterTest::CCM_Sender>::weak_ref_type component_executor_;
    bool const activate_;
  };

  void
  TT_Callback::on_trigger (
    IDL::traits< ::CCM_TT::TT_Timer>::ref_type /*timer*/,
    const ::CCM_TT::TT_Duration& /*time*/,
    uint32_t /*round*/)
  {
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      if (this->activate_)
        cex->check_status();
      else
        cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<UnkeyedWriterTest::CCM_Sender_Context>::ref_type context,
    IDL::traits<UnkeyedWriterTest::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move(context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[dtor]
  // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind: " << DDS::dds_write(status_kind) << std::endl;
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // started_ flag.
    if (!this->started_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 1))
      {
        auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
        if (cex)
        {
          this->started_ = cex->start_publishing ();
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status - "
                            << "WARNING: failed to lock component executor" << std::endl;
        }
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::tick ()
  {
    switch (this->assignment_)
      {
      case WRITER_ASSIGNMENT::WRITE_UNKEYED:
          write_unkeyed ();
          break;
        case WRITER_ASSIGNMENT::WRITE_MULTI:
          write_many ();
          break;
        case WRITER_ASSIGNMENT::TEST_EXCEPTION:
          test_exception ();
          break;
        default:
          break;
      }
  }
  void
  Sender_exec_i::check_status ()
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

  bool
  Sender_exec_i::start_publishing ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::start_publishing " << this->already_publishing_ << std::endl;

    // Don't start publishing before we got our ccm_activate which we can check
    // by checking tts_s_ which we set in the ccm_activate
    if (!this->already_publishing_ && this->tt_s_)
    {
      this->already_publishing_ = true;
      this->tm_activate_->cancel();

      for (uint16_t i = 1; i < this->keys_ + 1; ++i)
      {
        std::string key("KEY_" + std::to_string (i));
        OctetSeq seq (1);
        UnkeyedWriterTest::UnkeyedWriterMessage new_key (
          key, 1, seq);
        this->ktests_[key] = new_key;

        DDS4CCM_TEST_DEBUG << "Created key : " << new_key << std::endl;
      }

      this->last_key_ = this->ktests_.begin ();
      reset_iterations ();
      this->start ();
    }

    return this->already_publishing_;
  }

  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::reset_iterations ()
  {
    for (std::pair<std::string, UnkeyedWriterTest::UnkeyedWriterMessage> i : this->ktests_)
    {
      i.second.iteration (0);
    }
  }

  void
  Sender_exec_i::start_new_assignment (WRITER_ASSIGNMENT assignment)
  {
    this->last_key_ = this->ktests_.begin ();
    this->assignment_ = assignment;
    reset_iterations ();
  }

  void
  Sender_exec_i::write_unkeyed ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::write_unkeyed" << std::endl;

    if (this->last_key_ != this->ktests_.end ())
    {
      try
      {
        IDL::traits < UnkeyedWriterTest::UnkeyedWriterMessageConnector::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        ++this->last_key_->second.iteration ();
        OctetSeq reply_mesg (1);
        this->last_key_->second.data (reply_mesg);
        writer->write_one (this->last_key_->second, ::DDS::HANDLE_NIL);
        DDS4CCM_TEST_DEBUG << "Written " << this->last_key_->second << std::endl;
      }
      catch (const CCM_DDS::InternalError& )
      {
        DDS4CCM_TEST_ERROR << "ERROR: Internal Error while updating writer "
          << "info for <" << this->last_key_->first << ">." << std::endl;
      }
      ++this->last_key_;
    }
    else
    {
      // Onto the next iteration
      this->last_key_ = this->ktests_.begin ();
      while (this->last_key_ != this->ktests_.end ())
      {
        if (this->last_key_->second.iteration () == this->iterations_)
        {
          //next key
          ++this->last_key_;
        }
        else
        {
          break;
        }
      }
      if (this->last_key_ == this->ktests_.end ())
      {
        this->start_new_assignment (WRITER_ASSIGNMENT::WRITE_MULTI);
      }
    }
  }

  void
  Sender_exec_i::write_many ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::write_many" << std::endl;

    uint32_t nr_samples = this->keys_ * this->iterations_;
    UnkeyedWriterTest::UnkeyedWriterMessageSeq write_many_no_excep;
    write_many_no_excep.resize (nr_samples);
    //write with no exception
    for (uint32_t i = 1; i < nr_samples + 1; ++i)
    {
      OctetSeq reply_mesg (1);
      UnkeyedWriterTest::UnkeyedWriterMessage new_key ("KEY_1", 1, reply_mesg);
      write_many_no_excep[i-1] = new_key;
    }
    try
    {
      IDL::traits < UnkeyedWriterTest::UnkeyedWriterMessageConnector::Writer>::ref_type writer =
        this->context_->get_connection_info_write_data ();

      writer->write_many (write_many_no_excep);
      DDS4CCM_TEST_DEBUG << "write_many : written <"
        << write_many_no_excep.size () << "> samples."
        << std::endl;
    }
    catch (const CCM_DDS::InternalError& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Internal Error while write many writer "
        << ex << std::endl;
    }
    start_new_assignment (WRITER_ASSIGNMENT::TEST_EXCEPTION);
  }

  void
  Sender_exec_i::test_exception ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::test_exception" << std::endl;

    if (this->last_key_ != this->ktests_.end ())
    {
#if defined (DDSX11_NDDS)
      try
      {
        IDL::traits < UnkeyedWriterTest::UnkeyedWriterMessageConnector::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        OctetSeq reply_mesg (1000);
        this->last_key_->second.data (reply_mesg);
        writer->write_one (this->last_key_->second, ::DDS::HANDLE_NIL);
        DDS4CCM_TEST_DEBUG << "ERROR: No InternalError caught while "
          << "writing a large amount of data." << std::endl;
      }
      catch (const CCM_DDS::InternalError& )
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::test_exception" <<
          " - OK: Expected InternalErr received." << std::endl;
      }
#endif /* DDSX11_NDDS */
      ++this->last_key_;
    }
    else
    {
      // Onto the next iteration
      this->last_key_ = this->ktests_.begin ();
      while (this->last_key_ != this->ktests_.end ())
      {
        if (this->last_key_->second.iteration () == this->iterations_)
        {
          ++this->last_key_;
        }
        else
        {
          break;
        }
      }
    }
    if (this->last_key_ == this->ktests_.end ())
    {
      start_new_assignment (WRITER_ASSIGNMENT::WRITE_NONE);
    }
  }

  void
  Sender_exec_i::start ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::start" << std::endl;

    try
    {
      this->tm_ = tt_s_->schedule_repeated_trigger (
                     CORBA::make_reference<TT_Callback> (IDL::traits<UnkeyedWriterTest::CCM_Sender>::narrow (this->_lock()),false),
                  CCM_TT::TT_Duration (0, 1000000000 / this->rate_),
                  CCM_TT::TT_Duration (0, 1000000000 / this->rate_),
                  100);
    }
    catch_dds4ccm_test_ex(ex, "Sender_exec_i::start")
  }

  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ccm_activate]
    //start status checker
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_activate" << std::endl;
    this->tt_s_ = this->context_->get_connection_tt_scheduler ();
    this->tm_activate_ = this->tt_s_->schedule_repeated_trigger (
                              CORBA::make_reference<TT_Callback> (IDL::traits< UnkeyedWriterTest::CCM_Sender>::narrow (this->_lock()),true),
                              CCM_TT::TT_Duration (1, 0),
                              CCM_TT::TT_Duration (1, 0),
                              0);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (!this->tm_)
    {
       DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                          << "Test did not start."
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
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[get_connector_status]
    if (!this->connector_status_)
      {
        this->connector_status_ = CORBA::make_reference <connector_status_exec_i> (
            this->context_, IDL::traits<UnkeyedWriterTest::CCM_Sender>::narrow (this->_lock()));
      }
    return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[get_connector_status]
  }


  uint16_t
  Sender_exec_i::rate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::rate[getter]
    return this->rate_;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::rate[getter]
  }

  void
  Sender_exec_i::rate (
      uint16_t rate)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::rate[setter]
    this->rate_ = rate;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::rate[setter]
  }

  uint16_t
  Sender_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::iterations[getter]
  }

  void
  Sender_exec_i::iterations (
      uint16_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::iterations[setter]
  }

  uint16_t
  Sender_exec_i::keys ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::keys[getter]
    return this->keys_;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::keys[getter]
  }

  void
  Sender_exec_i::keys (
      uint16_t keys)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::keys[setter]
    this->keys_ = keys;
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i::keys[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<UnkeyedWriterTest::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[user_namespace_end_impl]

} // namespace UnkeyedWriterTest_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[factory]
extern "C" void
create_UnkeyedWriterTest_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UnkeyedWriterTest_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : unkeyed_writer_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
