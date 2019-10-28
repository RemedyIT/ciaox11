// -*- C++ -*-
/**
 * @file    coherent_writer_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : coherent_writer_sender_impl.cpp[Header]

#include "coherent_writer_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl[user_global_impl]

namespace CoherentWriter_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<CoherentWriter::CCM_Sender_Context>::ref_type context,
    IDL::traits<CoherentWriter::CCM_Sender>::weak_ref_type component_executor,
    bool &publication_matched)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
    , publication_matched_ (publication_matched)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind: " << DDS::dds_write(status_kind) << std::endl;
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // publication_matched_ flag.
    if (!this->publication_matched_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 1))
      {
        auto cex = IDL::traits< Sender_exec_i>::narrow (this->component_executor_.lock ());
        if (cex)
        {
          this->publication_matched_ = true;
          cex->start_publishing ();
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status - "
                            << "WARNING: failed to lock component executor" << std::endl;
        }
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }
  /**
   * Facet Executor Implementation Class : start_writing_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::start_writing_exec_i[ctor]
  start_writing_exec_i::start_writing_exec_i (
    IDL::traits<CoherentWriter::CCM_Sender_Context>::ref_type context,
    IDL::traits<CoherentWriter::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::start_writing_exec_i[ctor]

  start_writing_exec_i::~start_writing_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::start_writing_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::start_writing_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::start_writing_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::start_writing_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::start_writing_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::start_writing_exec_i[user_private_ops]


  /** Operations and attributes from start_writing */

  void
  start_writing_exec_i::start_write ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::start_writing_exec_i::start_write[void]
    auto cex = IDL::traits< Sender_exec_i >::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->restart ();
    }
    else
    {
      DDS4CCM_TEST_ERROR << "start_writing_exec_i::start_write - "
        << "ERROR: failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::start_writing_exec_i::start_write[void]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::check_status ()
  {
    if (!this->publication_matched_)
    {
      IDL::traits< ::DDS::DataWriter >::ref_type writer_dds_entity =
        this->context_->get_connection_info_write_dds_entity ();
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
          DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched current_count: "
                          << status.current_count() << std::endl;

          if (status.current_count() == 1)
          {
            DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched received" << std::endl;
            this->publication_matched_ = true;
            this->start_publishing();
          }
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "Sender_exec_i::check_status - "
                          << "No dds_entity port connected" << std::endl;
      }
    }
  }

  void Sender_exec_i::notify ()
  {
    try
    {
      ++this->run_;
      IDL::traits < ReaderStarter >::ref_type starter =
        this->context_->get_connection_reader_start ();

      starter->set_reader_properties (1, this->iterations ());

      CommonTestMessageSeq messages;
      for (int i = 1; i < this->iterations () + 1; ++i)
      {
        messages.push_back (CommonTestMessage ("KEY_1", ++this->total_iter_));
      }
      // Reference sample
      messages.push_back (CommonTestMessage ("KEY_2", this->run_));

      if (this->act_as_updater ())
      {
        IDL::traits < CommonTestConnector::Updater >::ref_type updater =
          this->context_->get_connection_info_update_data ();
        updater->is_coherent_write (true);
        updater->update_many (messages);
      }
      else
      {
        IDL::traits < ::CommonTestConnector::Writer >::ref_type writer =
          this->context_->get_connection_info_write_data ();
        writer->is_coherent_write (true);
        writer->write_many (messages);
      }

      DDS4CCM_TEST_DEBUG << "Sender_exec_i::notify - " << "<" << this->total_iter_
        << "> samples written up til now." << std::endl;
      starter->start_new_run (this->run_);
    }
    catch_dds4ccm_test_ex(ex, "Sender_exec_i::notify")
  }

  void Sender_exec_i::restart ()
  {
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
    if (tt_s)
    {
      this->tm_ = tt_s->schedule_trigger (
        CORBA::make_reference<ContextSwitch> (IDL::traits<CoherentWriter::CCM_Sender>::narrow (this->_lock())),
                                  CCM_TT::TT_Duration (0, 0));
    }
  }

  void Sender_exec_i::start_publishing ()
  {
    this->started_ = true;

    if (this->act_as_updater ())
    {
      IDL::traits< CommonTestConnector::Updater >::ref_type updater =
        this->context_->get_connection_info_update_data ();
      updater->is_coherent_write (true);

      updater->create_one (CommonTestMessage ("KEY_1", 1));
    }
    this->restart ();
  }

  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[ccm_activate]
    this->check_status ();
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (this->tm_)
    {
      this->tm_->cancel ();
      this->tm_.reset ();
    }
    if (!this->started_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
        "Test did not start." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[get_connector_status]
  if (!this->connector_status_)
  {
    this->connector_status_ =
      CORBA::make_reference <connector_status_exec_i>
        (this->context_, IDL::traits<CoherentWriter::CCM_Sender>::narrow (this->_lock()), publication_matched_);
  }
  return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[get_connector_status]
  }

  IDL::traits< CCM_WriterStarter >::ref_type
  Sender_exec_i::get_start_writing ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[get_start_writing]
  if (!this->start_writing_)
  {
    this->start_writing_ =
      CORBA::make_reference <start_writing_exec_i>
        (this->context_, IDL::traits<CoherentWriter::CCM_Sender>::narrow (this->_lock()));
  }
  return this->start_writing_;
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[get_start_writing]
  }


  bool
  Sender_exec_i::act_as_updater ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i::act_as_updater[getter]
    return this->act_as_updater_;
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i::act_as_updater[getter]
  }

  void
  Sender_exec_i::act_as_updater (
      bool act_as_updater)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i::act_as_updater[setter]
    this->act_as_updater_ = act_as_updater;
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i::act_as_updater[setter]
  }

  uint16_t
  Sender_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i::iterations[getter]
  }

  void
  Sender_exec_i::iterations (
      uint16_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i::iterations[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<CoherentWriter::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl[user_namespace_end_impl]

} // namespace CoherentWriter_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Sender_Impl[factory]
extern "C" void
create_CoherentWriter_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <CoherentWriter_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : coherent_writer_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
