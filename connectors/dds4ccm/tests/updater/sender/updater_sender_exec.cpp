// -*- C++ -*-
/**
 * @file    updater_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the updater test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : updater_sender_impl.cpp[Header]

#include "updater_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[user_global_impl]
constexpr uint16_t nr_instances { 3 };
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[user_global_impl]

namespace UpdaterModule_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<UpdaterModule::CCM_Sender_Context>::ref_type context,
    IDL::traits<UpdaterModule::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    // The receiver in this test has two datareaders connected to DDS. Therefor
    // we expect two 'on_publication_matched' status events during startup;
    // one with a current_count of one and one with a current_count of two (see
    // the check_publication_matched_status method).
    // These two status events are received by the DDS4CCM core but since this
    // status is not directly propagated to this callback method, we are forced to
    // invoke 'get_publication_matched_status' on the given DDS entity (see again
    // the check_publication_matched_status method) in order to check how many data readers
    // are connected.
    // It appears that due to the context switch in the DDS4CCM core the second
    // 'on_publication_matched' status event is received in the core before the
    // first one has been processed by this business code. That means that when this
    // callback is invoked by the DDS4CCM core, the current_count is already two
    // in DDS. When this method is invoked a second time, the test has already
    // been started and will start again if we don't prevent this.
    // The started flag has been introduced to prevent this.
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
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }
  /**
   * Facet Executor Implementation Class : next_assignment_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[ctor]
  next_assignment_exec_i::next_assignment_exec_i (
    IDL::traits<UpdaterModule::CCM_Sender_Context>::ref_type context,
    IDL::traits<UpdaterModule::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[ctor]

  next_assignment_exec_i::~next_assignment_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_private_ops]


  /** Operations and attributes from next_assignment */

  void
  next_assignment_exec_i::state_event_received (
      ::STATE_EVENT event)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i::state_event_received[_event]
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->start_next_assignment (event);
    }
    else
    {
      DDS4CCM_TEST_ERROR << "next_assignment_exec_i::state_event_received - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i::state_event_received[_event]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::start_publishing ()
  {
    this->create_instances ();
    this->notify ();
  }

  void
  Sender_exec_i::start_next_assignment (STATE_EVENT event)
  {
    bool start_new = false;

    switch (event)
    {
      case STATE_EVENT::MBM_ON_CREATION_RECEIVED:
        ++this->create_one_event_mbm_received_;
        break;
      case STATE_EVENT::OBO_ON_CREATION_RECEIVED:
        ++this->create_one_event_obo_received_;
        break;
      case STATE_EVENT::MBM_ON_UPDATE_RECEIVED:
        ++this->update_event_mbm_received_;
        break;
      case STATE_EVENT::OBO_ON_UPDATE_RECEIVED:
        ++this->update_event_obo_received_;
        break;
      case STATE_EVENT::MBM_ON_DELETION_RECEIVED:
        ++this->delete_one_event_mbm_received_;
        break;
      case STATE_EVENT::OBO_ON_DELETION_RECEIVED:
        ++this->delete_one_event_obo_received_;
        break;
    }

    switch (this->assignment_)
    {
      case UPDATER_ASSIGNMENT::CREATE_ONE:
        if (this->create_one_event_mbm_received_ == 1 &&
          this->create_one_event_obo_received_ == 1)
        {
          start_new = true;
          this->create_one_event_mbm_received_ = 0;
          this->create_one_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::CREATE_ONE_ALREADY_EXIST;
        }
        break;
      case UPDATER_ASSIGNMENT::UPDATE_DELETE_REGISTER:
        if (this->create_one_event_mbm_received_ == 1 &&
          this->create_one_event_obo_received_ == 1)
        {
          start_new = true;
          this->create_one_event_mbm_received_ = 0;
          this->create_one_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::UPDATE_DELETE_REGISTER_2;
        }
        break;
      case UPDATER_ASSIGNMENT::CREATE_MANY:
        if (this->create_one_event_mbm_received_ == 3 &&
          this->create_one_event_obo_received_ == 3)
        {
          start_new = true;
          this->create_one_event_mbm_received_ = 0;
          this->create_one_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::UPDATE_MANY;
        }
        break;
      case UPDATER_ASSIGNMENT::UPDATE_ONE:
        if (this->update_event_mbm_received_ == 1 &&
          this->update_event_obo_received_ == 1)
        {
          start_new = true;
          this->update_event_mbm_received_ = 0;
          this->update_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::UPDATE_ONE_NOT_REGISTERED;
        }
        break;
      case UPDATER_ASSIGNMENT::UPDATE_MANY:
        // It could be that the receiver doesn't receive all samples in one go. Therefor check for a range.
        if ((this->update_event_mbm_received_ >= 1 && this->update_event_mbm_received_ <= 3) &&
          this->update_event_obo_received_ == 3)
        {
          start_new = true;
          this->update_event_mbm_received_ = 0;
          this->update_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::DELETE_MANY;
        }
        break;
      case UPDATER_ASSIGNMENT::DELETE_ONE:
        if (this->delete_one_event_mbm_received_ == 1 &&
          this->delete_one_event_obo_received_ == 1)
        {
          start_new = true;
          this->delete_one_event_mbm_received_ = 0;
          this->delete_one_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::DELETE_ONE_NOT_REGISTERED;
        }
        break;
      case UPDATER_ASSIGNMENT::UPDATE_DELETE_REGISTER_2:
        if (this->delete_one_event_mbm_received_ == 1 &&
          this->delete_one_event_obo_received_ == 1)
        {
          start_new = true;
          this->delete_one_event_mbm_received_ = 0;
          this->delete_one_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::CREATE_MANY;
        }
        break;
      case UPDATER_ASSIGNMENT::DELETE_MANY:
        if (this->delete_one_event_mbm_received_ == 3 &&
          this->delete_one_event_obo_received_ == 3)
        {
          this->delete_one_event_mbm_received_ = 0;
          this->delete_one_event_obo_received_ = 0;
          this->assignment_ = UPDATER_ASSIGNMENT::END_TEST;
        }
        break;
      default:
        break;
    }

    if (start_new)
    {
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::start_next_assignment - "
        "Starting next assignment." << std::endl;
      IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
      if (tt_s)
      {
        this->thread_switch_ = tt_s->schedule_trigger (
          CORBA::make_reference<ContextSwitch> (IDL::traits<UpdaterModule::CCM_Sender>::narrow (this->_lock())),
                                    CCM_TT::TT_Duration (0, 0));
      }
    }
  }

  void
  Sender_exec_i::notify ()
  {
    try
    {
      this->started_ = true;
      if (this->assignment_ != UPDATER_ASSIGNMENT::END_TEST)
      {
        DDS4CCM_TEST_DEBUG << std::endl << "-----------------------------" << std::endl;
      }
      if (this->test_errors_ == 0)
      {
        switch (this->assignment_)
        {
          case UPDATER_ASSIGNMENT::CREATE_ONE:
            this->test_errors_ += this->create_one ();
            break;
          case UPDATER_ASSIGNMENT::CREATE_ONE_ALREADY_EXIST:
            this->assignment_ = UPDATER_ASSIGNMENT::UPDATE_ONE;
            this->test_errors_ += this->create_one_already_exist ();
            break;
          case UPDATER_ASSIGNMENT::UPDATE_ONE:
            this->test_errors_ += this->update_one ();
            break;
          case UPDATER_ASSIGNMENT::UPDATE_ONE_NOT_REGISTERED:
            this->assignment_ = UPDATER_ASSIGNMENT::DELETE_ONE;
            this->test_errors_ += this->update_one_not_registered ();
            break;
          case UPDATER_ASSIGNMENT::DELETE_ONE:
            this->test_errors_ += this->delete_one ();
            break;
          case UPDATER_ASSIGNMENT::DELETE_ONE_NOT_REGISTERED:
            this->assignment_ = UPDATER_ASSIGNMENT::UPDATE_DELETE_REGISTER;
            this->test_errors_ += this->delete_one_not_registered ();
            break;
          case UPDATER_ASSIGNMENT::UPDATE_DELETE_REGISTER:
            this->test_errors_ += this->update_and_delete_one_after_register ();
            break;
          case UPDATER_ASSIGNMENT::UPDATE_DELETE_REGISTER_2:
            this->test_errors_ += this->update_and_delete_one_after_register_2 ();
            break;
          case UPDATER_ASSIGNMENT::CREATE_MANY:
            this->test_errors_ += this->create_many ();
            break;
          case UPDATER_ASSIGNMENT::UPDATE_MANY:
            this->test_errors_ = this->update_many ();
            break;
          case UPDATER_ASSIGNMENT::DELETE_MANY:
            this->test_errors_ = this->delete_many ();
            break;
          default:
            break;
        }
      }
    }
    catch (const CORBA::Exception &ex)
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::tick - ERROR - caught unexpected exception : "
        << ex << std::endl;
      ++this->test_errors_;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::check_status ()
  {
    if (!this->started_)
    {
      IDL::traits< ::DDS::DataWriter >::ref_type writer_dds_entity =
        this->context_->get_connection_test_topic_update_dds_entity ();
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

          if (status.current_count() == 2)
          {
            DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched received" << std::endl;
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

  void
  Sender_exec_i::create_instances ()
  {
    //sequence for tests with .._one
    for (uint16_t i = 1; i < (nr_instances + 1); ++i)
    {
      this->topic_seq_one_.push_back (
        CommonTestMessage ("ONE_" + std::to_string (i), i));
    }
    for (uint16_t i = 1; i < (nr_instances + 1); ++i)
    {
      this->topic_seq_many_.push_back (
        CommonTestMessage ("MANY_" + std::to_string (i), i));
    }
  }

  uint16_t
  Sender_exec_i::create_one ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();
    CommonTestMessage const i = this->topic_seq_one_[0];

    try
    {
      updater->create_one(i);
      DDS4CCM_TEST_DEBUG << "create_one - OK: "
        "Created instance <" << i << ">." << std::endl;
    }
    catch (const CCM_DDS::AlreadyCreated &ex)
    {
      DDS4CCM_TEST_ERROR << "create_one - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "create_one - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    return errors;
  }

  uint16_t
  Sender_exec_i::create_one_already_exist ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();
    CommonTestMessage const i = this->topic_seq_one_[0];

    //try to create same instance again, this should erase an AlreadyCreated exception
    try
    {
      updater->create_one (i);
      DDS4CCM_TEST_ERROR << "create_one_already_exist - ERROR: No exception thrown when "
        "registring the same instance again: instance: <" << i << ">." << std::endl;
    }
    catch (const CCM_DDS::AlreadyCreated &ex)
    {
      DDS4CCM_TEST_DEBUG << "create_one_already_exist - OK: Correct exception caught "
        << "when creating the same instance again. Exception info: <"
        << ex << ">." << std::endl;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "create_one_already_exist - ERROR: Unexpected exception thrown when "
        "registring the same instance again: instance <" << i << "> - exception <"
        << ex << ">." << std::endl;
      ++errors;
    }
    this->notify ();
    return errors;
  }

  uint16_t
  Sender_exec_i::update_one ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();
    CommonTestMessage i = this->topic_seq_one_[0];
    i.iteration (i.iteration () + 5);

    try
    {
      updater->update_one (i, DDS::HANDLE_NIL);
      DDS4CCM_TEST_DEBUG << "update_one - OK: "
        "Updated instance <" << i << ">." << std::endl;
    }
    catch (const CCM_DDS::NonExistent &ex)
    {
      DDS4CCM_TEST_ERROR << "update_one - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "update_one - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    return errors;
  }

  uint16_t
  Sender_exec_i::update_one_not_registered ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();

    // update a not yet registered instance, expect a NonExistent exception
    // use second instance of table
    CommonTestMessage const i = this->topic_seq_one_[1];

    try
    {
      updater->update_one (i, DDS::HANDLE_NIL);
      DDS4CCM_TEST_ERROR << "update_one_not_registered - ERROR: No exception thrown when "
        "updating a non-existent instance: instance: <" << i << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::NonExistent &ex)
    {
      DDS4CCM_TEST_DEBUG << "update_one_not_registered - OK: Correct exception caught "
        << "when updating an unknown instance. Exception info: <"
        << ex << ">." << std::endl;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "update_one_not_registered - ERROR: Unexpected exception thrown when "
        "registring the same instance again: instance <" << i << "> - exception <"
        << ex << ">." << std::endl;
      ++errors;
    }
    this->notify ();
    return errors;
  }

  uint16_t
  Sender_exec_i::delete_one ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();

    // update a not yet registered instance, expect a NonExistent exception
    CommonTestMessage const i = this->topic_seq_one_[0];

    try
    {
      updater->delete_one (i, DDS::HANDLE_NIL);
      DDS4CCM_TEST_DEBUG << "delete_one - OK: "
        "Deleted instance <" << i << ">." << std::endl;
    }
    catch (const CCM_DDS::NonExistent &ex)
    {
      DDS4CCM_TEST_ERROR << "delete_one - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "delete_one - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    return errors;
  }

  uint16_t
  Sender_exec_i::delete_one_not_registered ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();

    // Delete non-existing instance, expect NonExistent exception
    CommonTestMessage const i = this->topic_seq_one_[1];

    try
    {
      updater->delete_one(i, DDS::HANDLE_NIL);
      DDS4CCM_TEST_ERROR << "delete_one_not_registered - ERROR: No exception thrown when "
        "deleting a non-existent instance: instance: <" << i << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::NonExistent &ex)
    {
      DDS4CCM_TEST_DEBUG << "delete_one_not_registered - OK: "
        "Expected exception caught: <" << ex << ">." << std::endl;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "delete_one_not_registered - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    this->notify ();
    return errors;

  }

  uint16_t
  Sender_exec_i::update_and_delete_one_after_register ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();
    // Update an instance after registering first, using a handle
    CommonTestMessage i = this->topic_seq_one_[2];

    DDS4CCM_TEST_DEBUG << "register instance " << i << std::endl;

    ::DDS::InstanceHandle_t const hnd = updater->register_instance (i);

    i.iteration (i.iteration () + 5);

    if (hnd != ::DDS::HANDLE_NIL)
    {
      //update an instance with an instance handle belonging to an other instance
      try
      {
        CommonTestMessage const y = this->topic_seq_one_[1];
        updater->update_one (y, hnd);
        DDS4CCM_TEST_ERROR << "update_and_delete_one_after_register - ERROR: "
          "No exception caught while updating an instance with a wrong instance "
          "handle" << std::endl;
        ++errors;
      }
      catch (const CCM_DDS::NonExistent &ex)
      {
        DDS4CCM_TEST_ERROR << "update_and_delete_one_after_register - ERROR: "
          << "Unexpected exception caught whilst updating a wrong instance: <"
          << ex << ">." << std::endl;
        ++errors;
      }
      catch (const CCM_DDS::InternalError &)
      {
        DDS4CCM_TEST_DEBUG << "update_and_delete_one_after_register - OK: "
          "Expected exception caught while updating a instance with a wrong "
          "instance handle. exception <CCM_DDS::InternalErr>." << std::endl;
      }

      try
      {
        DDS4CCM_TEST_DEBUG << "update_and_delete_one_after_register - Update an "
          "instance after registration. instance <" << i << ">." << std::endl;
        updater->update_one (i, hnd);
      }
      catch (const CCM_DDS::NonExistent &ex)
      {
        DDS4CCM_TEST_ERROR << "update_and_delete_one_after_register - ERROR: "
          "Unexpected exception caught: <" << ex << ">." << std::endl;
        ++errors;
      }
      catch (const CCM_DDS::InternalError &ex)
      {
        DDS4CCM_TEST_ERROR << "update_and_delete_one_after_register - ERROR: "
          "Unexpected exception caught: <" << ex << ">." << std::endl;
        ++errors;
      }
    }
    else
    {
      DDS4CCM_TEST_ERROR << "update_and_delete_one_after_register - ERROR: "
        "Failed to register instance <" << i << ">." << std::endl;
      ++errors;
    }
    return errors;
  }

  uint16_t
  Sender_exec_i::update_and_delete_one_after_register_2 ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();
    // Update an instance after registering first, using a handle
    CommonTestMessage i = this->topic_seq_one_[2];

    DDS4CCM_TEST_DEBUG << "register instance " << i << std::endl;

    ::DDS::InstanceHandle_t const hnd = updater->register_instance (i);

    try
    {
      DDS4CCM_TEST_DEBUG << "update_and_delete_one_after_register_2 - "
        << "delete a registered instance with a correct handle. instance <"
        << i << ">." << std::endl;
      updater->delete_one (i, hnd);
    }
    catch (const CCM_DDS::NonExistent &ex)
    {
      DDS4CCM_TEST_ERROR << "update_and_delete_one_after_register_2 - ERROR: "
        << "Unexpected exception caught whilst deleting the instance: <"
        << ex << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "update_and_delete_one_after_register_2 - ERROR: "
        << "Unexpected exception caught while deleting the instance: <"
        << ex << ">." << std::endl;
      ++errors;
    }
    return errors;
  }

  uint16_t
  Sender_exec_i::create_many ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();

    //create many with no exception
    try
    {
      updater->create_many (this->topic_seq_many_);
      DDS4CCM_TEST_DEBUG << "create_many : "
        << "created <" << this->topic_seq_many_.size ()
        << "> samples." << std::endl;
    }
    catch (const CCM_DDS::AlreadyCreated &ex)
    {
      DDS4CCM_TEST_ERROR << "create_many - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "create_many - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }

    //test create_many with AlreadyCreated exception
    CommonTestMessageSeq tmp;
    tmp.push_back (this->topic_seq_many_[0]);
    tmp.push_back (CommonTestMessage ("ZZZ_1", 1));
    tmp.push_back (this->topic_seq_many_[2]);
    try
    {
      updater->create_many (tmp);
      DDS4CCM_TEST_ERROR << "create_many - ERROR: No AlreadyCreated exception "
        "thrown while creating duplicated samples." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::AlreadyCreated &ex)
    {
      DDS4CCM_TEST_DEBUG << "create_many - OK: "
        "Expected exception caught while creating duplicate samples. "
        "exception <" << ex << ">." << std::endl;

      if (ex.indexes ().size () != 2)
      {
        DDS4CCM_TEST_ERROR << "create_many - ERROR: NonExistent exception contains "
          << "unexpected number of indexes. expected <2> - got <" << ex.indexes ().size () << ">."
          << std::endl;
        ++errors;
      }
      else
      {
        if (std::find (ex.indexes ().begin (), ex.indexes ().end (), 0) == ex.indexes ().end () ||
          std::find (ex.indexes ().begin (), ex.indexes ().end (), 2) == ex.indexes ().end ())
        {
          DDS4CCM_TEST_ERROR << "create_many - ERROR: NonExistent exception contains "
            << "unexpected indexes found. expected <0,2> - got <" << ex.indexes () << ">."
            << std::endl;
          ++errors;
        }
      }
    }
    catch (const CCM_DDS::InternalError& ex)
    {
      DDS4CCM_TEST_ERROR << "create_many - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    return errors;
  }

  uint16_t
  Sender_exec_i::update_many ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();

    try
    {
      for (CommonTestMessage &tp : this->topic_seq_many_)
      {
        tp.iteration (tp.iteration () + 5);
      }
      updater->update_many (this->topic_seq_many_);
      DDS4CCM_TEST_DEBUG << "update_many : "
        << "updated <" << this->topic_seq_many_.size ()
        << "> samples." << std::endl;
    }
    catch (const CCM_DDS::NonExistent &ex)
    {
      DDS4CCM_TEST_ERROR << "update_many - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "update_many - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }

    // update with exception
    // make from the second and third instances a unregistered instance, see above
    this->topic_seq_many_[1] = CommonTestMessage ("XXX_1", 1);
    this->topic_seq_many_[2] = CommonTestMessage ("XXX_2", 2);
    try
    {
      updater->update_many (this->topic_seq_many_);
      DDS4CCM_TEST_ERROR << "update_many - ERROR: No NonExistent exception "
        "thrown while updating unregistered samples." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::NonExistent & ex)
    {
      DDS4CCM_TEST_DEBUG << "update_many - OK: "
        "Expected exception caught while creating duplicate samples. "
        "exception <" << ex << ">." << std::endl;

      if (ex.indexes ().size () != 2)
      {
        DDS4CCM_TEST_ERROR << "update_many - ERROR: NonExistent exception contains "
          << "unexpected number of indexes. expected <2> - got <" << ex.indexes ().size () << ">."
          << std::endl;
        ++errors;
      }
      else
      {
        if (std::find (ex.indexes ().begin (), ex.indexes ().end (), 1) == ex.indexes ().end () ||
          std::find (ex.indexes ().begin (), ex.indexes ().end (), 2) == ex.indexes ().end ())
        {
          DDS4CCM_TEST_ERROR << "update_many - ERROR: NonExistent exception contains "
            << "unexpected indexes found. expected <1,2> - got <" << ex.indexes () << ">."
            << std::endl;
          ++errors;
        }
      }
    }
    catch (const CCM_DDS::InternalError& ex)
    {
      DDS4CCM_TEST_ERROR << "create_many - ERROR: "
        "Unexpected exception caught: <" << ex << ">." << std::endl;
      ++errors;
    }
    return errors;
  }

  uint16_t
  Sender_exec_i::delete_many ()
  {
    uint16_t errors = 0;
    IDL::traits< ::CommonTestConnector::Updater >::ref_type updater =
      this->context_->get_connection_test_topic_update_data ();

    // delete_many with exception (the second and third instances are unknown to DDS)
    try
    {
      updater->delete_many (this->topic_seq_many_);
      DDS4CCM_TEST_ERROR << "delete_many - ERROR: No NonExistent exception "
        "thrown while deleting unregistered samples." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::NonExistent & ex)
    {
      DDS4CCM_TEST_DEBUG << "delete_many - OK: "
        "Expected exception caught while creating duplicate samples. "
        "exception <" << ex << ">." << std::endl;

      if (ex.indexes ().size () != 2)
      {
        DDS4CCM_TEST_ERROR << "delete_many - ERROR: NonExistent exception contains "
          << "unexpected number of indexes. expected <2> - got <" << ex.indexes ().size () << ">."
          << std::endl;
        ++errors;
      }
      else
      {
        if (std::find (ex.indexes ().begin (), ex.indexes ().end (), 1) == ex.indexes ().end () ||
          std::find (ex.indexes ().begin (), ex.indexes ().end (), 2) == ex.indexes ().end ())
        {
          DDS4CCM_TEST_ERROR << "delete_many - ERROR: NonExistent exception contains "
            << "unexpected indexes found. expected <1,2> - got <" << ex.indexes () << ">."
            << std::endl;
          ++errors;
        }
      }
    }
    catch (const CCM_DDS::InternalError& ex)
    {
      DDS4CCM_TEST_ERROR << "delete_many - ERROR: "
        << "Unexpected exception caught while deleting the instance: <"
        << ex << ">." << std::endl;
      ++errors;
    }

    // Delete many with no exception; reset instances to original values
    this->topic_seq_many_[1] = CommonTestMessage ("MANY_2", 2);
    this->topic_seq_many_[2] = CommonTestMessage ("MANY_3", 3);

    try
    {
      updater->delete_many (this->topic_seq_many_);
      DDS4CCM_TEST_DEBUG << "delete_many : "
        << "deleted <" << this->topic_seq_many_.size ()
        << "> samples." << std::endl;
    }
    catch (const CCM_DDS::NonExistent &ex)
    {
      DDS4CCM_TEST_ERROR << "delete_many - ERROR: "
        << "Unexpected exception caught whilst deleting the instance: <"
        << ex << ">." << std::endl;
      ++errors;
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "delete_many - ERROR: "
        << "Unexpected exception caught while deleting the instance: <"
        << ex << ">." << std::endl;
      ++errors;
    }
    return errors;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[ccm_activate]
    this->check_status ();
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (!this->started_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
        "Test did not start." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[ccm_remove]
    if (this->assignment_ != UPDATER_ASSIGNMENT::END_TEST)
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::ccm_remove - ERROR: "
        << "Not all assignments have been fulfilled."
        << std::endl;
    }
    else
    {
      if (this->test_errors_ != 0)
      {
        DDS4CCM_TEST_ERROR << "Sender_exec_i::ccm_remove - ERROR: <"
          << this->test_errors_ << "> errors found in test."
          << std::endl;
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[get_connector_status]
  if (!this->connector_status_)
  {
    this->connector_status_ =
      CORBA::make_reference <connector_status_exec_i> (
        this->context_, IDL::traits<UpdaterModule::CCM_Sender>::narrow (this->_lock()));
  }
  return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[get_connector_status]
  }

  IDL::traits< CCM_NextAssignment >::ref_type
  Sender_exec_i::get_next_assignment ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[get_next_assignment]
  if (!this->next_assignment_)
  {
    this->next_assignment_ =
      CORBA::make_reference <next_assignment_exec_i> (
        this->context_, IDL::traits<UpdaterModule::CCM_Sender>::narrow (this->_lock()));
  }
  return this->next_assignment_;
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[get_next_assignment]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<UpdaterModule::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[user_namespace_end_impl]

} // namespace UpdaterModule_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[factory]
extern "C" void
create_UpdaterModule_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UpdaterModule_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
