// -*- C++ -*-
/**
 * @file    psl_sample_lost_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psl_sample_lost_sender_impl.cpp[Header]

#include "psl_sample_lost_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[user_global_impl]

namespace PSL_SampleLostTest_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::PSL_SampleLostTest::CCM_Sender>::weak_ref_type component_executor,
        bool activate)
    : component_executor_(component_executor)
     , activate_(activate)
    {}

    virtual
    void
    on_trigger (
             IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
             const ::CCM_TT::TT_Duration& time,
             uint32_t round) override;

  private:
    IDL::traits< ::PSL_SampleLostTest::CCM_Sender>::weak_ref_type component_executor_;
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
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<PSL_SampleLostTest::CCM_Sender_Context>::ref_type context,
    IDL::traits<PSL_SampleLostTest::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind: " << DDS::dds_write(status_kind) << std::endl;
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // started_ flag.
    if (!this->started_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 2))
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
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::check_status ()
  {
    IDL::traits< ::DDS::DataWriter >::ref_type writer_dds_entity =
      this->context_->get_connection_writer_dds_entity ();
    if (writer_dds_entity)
    {
      ::DDS::PublicationMatchedStatus status {};
      ::DDS::ReturnCode_t const retcode = writer_dds_entity->get_publication_matched_status (status);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_TEST_ERROR <<"Sender_exec_i::check_status - "
          << "Error: Unable to get_publication_matched_status: <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status - publication_matched current_count:"
                         << status.current_count() << std::endl;

        if (status.current_count() == 2)
        {
          DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched received" << std::endl;
          this->tm_activate_->cancel();
          this->start_publishing();
        }
      }
    }
    else
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::check_status - no writer_dds_entity connected" << std::endl;
    }
  }

  void
  Sender_exec_i::start_publishing ()
  {
    if (!this->already_publishing_)
    {
      this->already_publishing_ = true;

      this->tm_activate_->cancel();
      this->tm_ = tt_s->schedule_repeated_trigger (
                              CORBA::make_reference<TT_Callback> (IDL::traits< PSL_SampleLostTest::CCM_Sender>::narrow (this->_lock()),false),
                              CCM_TT::TT_Duration (1, 0),
                              CCM_TT::TT_Duration (1, 0),
                              0);
    }
  }

  void Sender_exec_i::tick ()
  {
    IDL::traits< CommonTestConnector::Writer >::ref_type writer =
      this->context_->get_connection_writer_data ();
    try
    {
      CommonTestMessage s1 {"ONE", ++this->iteration_};
      CommonTestMessage s2 {"TWO", this->iteration_};
      writer->write_one(s1,::DDS::HANDLE_NIL);
      writer->write_one(s2,::DDS::HANDLE_NIL);
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::tick - "
        << "Written samples <" << s1 << "> and <" << s2 << ">." << std::endl;
    }
    catch_dds4ccm_test_ex(ex, "Sender_exec_i::tick")
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ccm_activate]
    // Start status checker
    this->tt_s = this->context_->get_connection_tt_scheduler ();
    this->tm_activate_ = this->tt_s->schedule_repeated_trigger (
                              CORBA::make_reference<TT_Callback> (IDL::traits< PSL_SampleLostTest::CCM_Sender>::narrow (this->_lock()),true),
                              CCM_TT::TT_Duration (0, 1000000000),
                              CCM_TT::TT_Duration (0, 1000000000),
                              0);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (!this->tm_)
    {
       DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                             "Test did not start, because no DDS::PUBLICATION_MATCHED_STATUS was received "
                             "via info_out_connector_status_exec_i::on_unexpected_status ."  << std::endl;
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
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[get_connector_status]
  if (!this->connector_status_)
  {
    this->connector_status_ =
      CORBA::make_reference <connector_status_exec_i> (
        this->context_, IDL::traits<PSL_SampleLostTest::CCM_Sender>::narrow (this->_lock()));
  }
  return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[get_connector_status]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<PSL_SampleLostTest::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[user_namespace_end_impl]

} // namespace PSL_SampleLostTest_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[factory]
extern "C" void
create_PSL_SampleLostTest_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <PSL_SampleLostTest_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_sample_lost_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
