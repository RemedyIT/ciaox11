// -*- C++ -*-
/**
 * @file    filters_common_sl_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : filters_common_sl_sender_impl.cpp[Header]

#include "filters_common_sl_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
#include "dds4ccm/tests/filters/common/qc_common.h"
//@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl[user_global_impl]

namespace Filters_Common_State_Listen_Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits<::Filters_Common_State_Listen_Test::CCM_Sender>::weak_ref_type component_executor,
                 bool activate)
      : component_executor_(component_executor)
      , activate_(activate)
    {
    }

    void
    on_trigger (
             IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
             const ::CCM_TT::TT_Duration& time,
             uint32_t round) override;

  private:
    IDL::traits<::Filters_Common_State_Listen_Test::CCM_Sender>::weak_ref_type component_executor_;
    bool const activate_;
  };

  void
  TT_Callback::on_trigger (
           IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
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
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<Filters_Common_State_Listen_Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<Filters_Common_State_Listen_Test::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits<::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    DDS4CCM_TEST_ERROR << "on_inconsistent_topic - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_requested_incompatible_qos - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_sample_rejected - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits<::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_ERROR << "on_offered_deadline_missed - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits<::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_ERROR << "on_offered_incompatible_qos - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits<::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // started_ flag.
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind <" << DDS::dds_write(status_kind) << ">" << std::endl;
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
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }
  /**
   * Facet Executor Implementation Class : start_writing_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[ctor]
  start_writing_exec_i::start_writing_exec_i (
    IDL::traits<Filters_Common_State_Listen_Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<Filters_Common_State_Listen_Test::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[ctor]

  start_writing_exec_i::~start_writing_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i[user_private_ops]


  /** Operations and attributes from start_writing */

  void
  start_writing_exec_i::start_write ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i::start_write[void]
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      DDS4CCM_TEST_DEBUG << "start_writing_exec_i::start_write - "
        << "Continue publishing samples." << std::endl;
      cex->continue_publishing ();
    }
    else
    {
      DDS4CCM_TEST_ERROR << "ERROR: start_writing_exec_i::start_write - "
        "failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::start_writing_exec_i::start_write[void]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::check_status ()
  {
    IDL::traits<::DDS::DataWriter>::ref_type writer_dds_entity =
      this->context_->get_connection_info_update_dds_entity ();
    if (writer_dds_entity)
    {
      ::DDS::PublicationMatchedStatus status {};
      ::DDS::ReturnCode_t const retcode = writer_dds_entity->get_publication_matched_status (status);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_TEST_ERROR <<"Sender_exec_i::check_status - "
          << "Error: Unable to get_publication_matched_status: <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched current_count: "
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
      DDS4CCM_TEST_ERROR << "Sender_exec_i::check_status - "
                         << "No dds_entity port connected" << std::endl;
    }
  }

  void
  Sender_exec_i::start_publishing ()
  {
    if (!this->already_publishing_)
    {
      this->already_publishing_ = true;
      this->tm_activate_->cancel();
      try
      {
        // First create the samples in DDS.
        IDL::traits<CommonTestConnector::Updater>::ref_type updater =
          this->context_->get_connection_info_update_data ();
        updater->create_many (this->samples_);
        DDS4CCM_TEST_DEBUG << "start_writing_exec_i::start_publishing - "
          << "Created <" << this->samples_.size () << "> in DDS. Now wait "
          << "for the receiver before continuing."<< std::endl;
        // Now we wait for the receiver to receive all on_creation callback
        // If receiver has received the expected number of callbacks, it'll
        // invoke start_write.
      }
      catch (CCM_DDS::InternalError const &ex)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::start_publishing - "
          << "InternalError exception caught : " << ex << std::endl;
      }
      catch (CCM_DDS::AlreadyCreated const &ex)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::start_publishing - "
          << "AlreadyCreated exception caught : " << ex << std::endl;
      }
      catch_dds4ccm_test_ex (ex, "Sender_exec_i::start_publishing")
    }
  }

  void
  Sender_exec_i::tick ()
  {
    IDL::traits<CommonTestConnector::Updater>::ref_type updater =
      this->context_->get_connection_info_update_data ();
    try
    {
      // First iteration will be added by create_many.
      if (++this->last_loop_ > (number_of_loops () * iterations ()) - 1)
      {
        this->stop ();
        return;
      }
      if (this->last_iteration_ >= iterations ())
      {
        this->last_iteration_ = 0;
      }
      ++this->last_iteration_;

      for (CommonTestMessage &sample : this->samples_)
        sample.iteration (this->last_iteration_);

      updater->update_many (this->samples_);
    }
    catch (CCM_DDS::InternalError const &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick - "
        << "InternalError exception caught : " << ex << std::endl;
    }
    catch (CCM_DDS::NonExistent const &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick - "
        << "NonExistent exception caught : " << ex << std::endl;
    }
    catch_dds4ccm_test_ex (ex, "Sender_exec_i::tick")
  }

  void
  Sender_exec_i::continue_publishing ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::continue_publishing - "
      << "Continue publishing samples." << std::endl;

    this->tm_ = tt_s->schedule_repeated_trigger (
                         CORBA::make_reference<TT_Callback> (IDL::traits< Filters_Common_State_Listen_Test::CCM_Sender>::narrow (this->_lock()),false),
                         CCM_TT::TT_Duration (0,100000000),
                         CCM_TT::TT_Duration (0, 100000000),
                         0);

  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::stop ()
  {
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::stop" << std::endl;

    if (!this->tm_->is_canceled())
    {
      this->tm_->cancel();

      // It could be that stop will be invoked a second time. We don't need
      // to remove the samples a second time.

      // Now remove the samples from DDS
      IDL::traits<CommonTestConnector::Updater>::ref_type updater =
        this->context_->get_connection_info_update_data ();
      try
      {
        updater->delete_many (this->samples_);
      }
      catch (CCM_DDS::InternalError const &ex)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::stop - "
          << "InternalError exception caught : " << ex << std::endl;
      }
      catch (CCM_DDS::NonExistent const &ex)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::stop - "
          << "NonExistent exception caught : " << ex << std::endl;
      }
      catch_dds4ccm_test_ex (ex, "Sender_exec_i::stop")
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    // Create the samples
    for (uint16_t key = 0; key < keys (); ++key)
    {
      this->samples_.push_back (
        CommonTestMessage ("KEY_"+std::to_string (key + 1), 1));
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ccm_activate]
    // Start status checker
    this->tt_s = this->context_->get_connection_tt_scheduler ();
    this->tm_activate_ = this->tt_s->schedule_repeated_trigger (
                           CORBA::make_reference<TT_Callback> (IDL::traits< Filters_Common_State_Listen_Test::CCM_Sender>::narrow (this->_lock()),true),
                           CCM_TT::TT_Duration (0, 1000000000),
                           CCM_TT::TT_Duration (0, 1000000000),
                          0);
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
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
       this->stop();
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
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[get_connector_status]
  if (!this->connector_status_)
  {
    this->connector_status_ =
      CORBA::make_reference <connector_status_exec_i> (
        this->context_, IDL::traits<Filters_Common_State_Listen_Test::CCM_Sender>::narrow (this->_lock ()));
  }
  return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[get_connector_status]
  }

  IDL::traits< CCM_WriterStarter>::ref_type
  Sender_exec_i::get_start_writing ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[get_start_writing]
  if (!this->start_writing_)
  {
    this->start_writing_ = CORBA::make_reference <start_writing_exec_i> (
      this->context_, IDL::traits<Filters_Common_State_Listen_Test::CCM_Sender>::narrow (this->_lock ()));
  }
  return this->start_writing_;
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[get_start_writing]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<Filters_Common_State_Listen_Test::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl[user_namespace_end_impl]

} // namespace Filters_Common_State_Listen_Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Filters_Common_State_Listen_Test_Sender_Impl[factory]
extern "C" void
create_Filters_Common_State_Listen_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Filters_Common_State_Listen_Test_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Filters_Common_State_Listen_Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : filters_common_sl_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
