// -*- C++ -*-
/**
 * @file    filters_common_rg_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the query condition test which
 *          tests two different queries.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : filters_common_rg_sender_impl.cpp[Header]

#include "filters_common_rg_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
#include "dds4ccm/tests/filters/common/qc_common.h"
//@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl[user_global_impl]

namespace Filters_Common_Read_Get_Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<Filters_Common_Read_Get_Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<Filters_Common_Read_Get_Test::CCM_Sender>::weak_ref_type component_executor,
    bool &publication_matched)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
    , publication_matched_ (publication_matched)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    DDS4CCM_TEST_ERROR << "on_inconsistent_topic - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_requested_incompatible_qos - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_sample_rejected - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_ERROR << "on_offered_deadline_missed - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_ERROR << "on_offered_incompatible_qos - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind <" << DDS::dds_write(status_kind) << ">" << std::endl;
    if (!this->publication_matched_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 2))
      {
        auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
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
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }
  /**
   * Facet Executor Implementation Class : start_writing_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[ctor]
  start_writing_exec_i::start_writing_exec_i (
    IDL::traits<Filters_Common_Read_Get_Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<Filters_Common_Read_Get_Test::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[ctor]

  start_writing_exec_i::~start_writing_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[user_private_ops]
  void
  Sender_exec_i::check_status ()
  {
    if (!this->publication_matched_)
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

          if (status.current_count() == 2)
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
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i[user_private_ops]


  /** Operations and attributes from start_writing */

  void
  start_writing_exec_i::start_write ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i::start_write[void]
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->start_publishing ();
    else
    {
      DDS4CCM_TEST_ERROR << "start_writing_exec_i::start_write - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::start_writing_exec_i::start_write[void]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::start_publishing ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::start_publishing " << std::endl;
    this->started_ = true;
    this->notify();
  }

  void
  Sender_exec_i::notify ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::notify - " << std::endl;
    IDL::traits<CommonTestConnector::Writer>::ref_type writer =
      this->context_->get_connection_info_write_data ();

    CommonTestMessageSeq msgs;
    for (uint16_t key = 0;  key < keys (); ++key)
    {
      std::string const current_key ("KEY_"+std::to_string (key+1));
      for (uint16_t iter = 0; iter < iterations (); ++iter)
      {
        msgs.push_back (CommonTestMessage (current_key, iter+1));
      }
    }
    std::string const current_key ("KEY_"+ std::to_string (keys () + 1));
    msgs.push_back (CommonTestMessage (current_key, 1));

    writer->write_many (msgs);

    DDS4CCM_TEST_DEBUG << "Sender_exec_i::notify - <"
      << msgs.size () << "> samples have been written."
      << std::endl;
    this->written_ += msgs.size ();

    // Let the receiver know that the samples were written
    IDL::traits< ReaderStarter>::ref_type starter =
      this->context_->get_connection_reader_start ();
    starter->start_read ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ccm_activate]
    this->check_status ();
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ccm_passivate]

    if (!this->started_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
        "Test did not start." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_passivate - <"
        << this->written_ << "> samples were written." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[get_connector_status]
  if (!this->connector_status_)
  {
    this->connector_status_ =
      CORBA::make_reference <connector_status_exec_i> (
        this->context_, IDL::traits<Filters_Common_Read_Get_Test::CCM_Sender>::narrow (this->_lock()), publication_matched_);
  }
  return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[get_connector_status]
  }

  IDL::traits< CCM_WriterStarter>::ref_type
  Sender_exec_i::get_start_writing ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[get_start_writing]
  if (!this->start_writing_)
  {
    this->start_writing_ =
      CORBA::make_reference <start_writing_exec_i> (
        this->context_, IDL::traits<Filters_Common_Read_Get_Test::CCM_Sender>::narrow (this->_lock()));
  }
  return this->start_writing_;
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[get_start_writing]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<Filters_Common_Read_Get_Test::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl[user_namespace_end_impl]

} // namespace Filters_Common_Read_Get_Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_Read_Get_Test_Sender_Impl[factory]
extern "C" void
create_Filters_Common_Read_Get_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Filters_Common_Read_Get_Test_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_Read_Get_Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : filters_common_rg_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
