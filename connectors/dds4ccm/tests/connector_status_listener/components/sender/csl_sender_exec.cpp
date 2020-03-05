// -*- C++ -*-
/**
 * @file    csl_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : csl_sender_impl.cpp[Header]

#include "csl_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
#include "cslSEEC.h"
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[user_global_impl]

namespace CSL_Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[user_namespace_impl]
  class TT_Callback final
         : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::CSL_Test::CCM_Sender>::weak_ref_type component_executor)
             : component_executor_(component_executor)
    {}

    void
    on_trigger (
      IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round) override;

  private:
    IDL::traits< ::CSL_Test::CCM_Sender>::weak_ref_type component_executor_;
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
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_sender_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[ctor]
  connector_status_sender_exec_i::connector_status_sender_exec_i (
    IDL::traits<CSL_Test::CCM_Sender_Context>::ref_type context,
    IDL::traits<CSL_Test::CCM_Sender>::weak_ref_type component_executor,
    atomic_thread_id &on_inconsistent_topic_thread_id,
    atomic_thread_id &on_requested_incompatible_qos_thread_id,
    atomic_thread_id &on_sample_rejected_thread_id,
    atomic_thread_id &on_offered_deadline_missed_thread_id,
    atomic_thread_id &on_offered_incompatible_qos_thread_id,
    atomic_thread_id &on_publication_matched_thread_id,
    atomic_thread_id &on_subscription_matched_thread_id,
    atomic_thread_id &on_liveliness_changed_thread_id,
    atomic_thread_id &on_liveliness_lost_thread_id,
    atomic_thread_id &on_reliable_reader_activity_changed_thread_id,
    atomic_thread_id &on_reliable_writer_cache_changed_thread_id,
    int32_t &offered_incompatible_total_count,
    int32_t &inconsistent_topic_total_count)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
    , on_inconsistent_topic_thread_id_ (on_inconsistent_topic_thread_id)
    , on_requested_incompatible_qos_thread_id_ (on_requested_incompatible_qos_thread_id)
    , on_sample_rejected_thread_id_ (on_sample_rejected_thread_id)
    , on_offered_deadline_missed_thread_id_ (on_offered_deadline_missed_thread_id)
    , on_offered_incompatible_qos_thread_id_ (on_offered_incompatible_qos_thread_id)
    , on_publication_matched_thread_id_ (on_publication_matched_thread_id)
    , on_subscription_matched_thread_id_ (on_subscription_matched_thread_id)
    , on_liveliness_changed_thread_id_ (on_liveliness_changed_thread_id)
    , on_liveliness_lost_thread_id_ (on_liveliness_lost_thread_id)
    , on_reliable_reader_activity_changed_thread_id_ (on_reliable_reader_activity_changed_thread_id)
    , on_reliable_writer_cache_changed_thread_id_ (on_reliable_writer_cache_changed_thread_id)
    , offered_incompatible_total_count_ (offered_incompatible_total_count)
    , inconsistent_topic_total_count_ (inconsistent_topic_total_count)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[ctor]

  connector_status_sender_exec_i::~connector_status_sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_private_ops]


  /** Operations and attributes from connector_status_sender */

  void
  connector_status_sender_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    DDS4CCM_TEST_DEBUG << "connector_status_sender_exec_i::on_inconsistent_topic - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_inconsistent_topic_thread_id_ = std::this_thread::get_id ();
    this->inconsistent_topic_total_count_ = status.total_count ();

    // Both the sender and receiver receive an on_inconsistent_topic callback so
    // there could two.
    if (this->inconsistent_topic_total_count_ > 2)
    {
      DDS4CCM_TEST_ERROR << "ERROR: connector_status_sender_exec_i::on_inconsistent_topic - "
        << "unexpected total_count: expected less than 3 - received <" << this->inconsistent_topic_total_count_
        << ">." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_sender_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_DEBUG << "connector_status_sender_exec_i::on_requested_incompatible_qos - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_requested_incompatible_qos_thread_id_ = std::this_thread::get_id ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_sender_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_DEBUG << "connector_status_sender_exec_i::on_sample_rejected - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_sample_rejected_thread_id_ = std::this_thread::get_id ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_sender_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_DEBUG << "connector_status_sender_exec_i::on_offered_deadline_missed - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_offered_deadline_missed_thread_id_ = std::this_thread::get_id ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_sender_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_DEBUG << "connector_status_sender_exec_i::on_offered_incompatible_qos - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_offered_incompatible_qos_thread_id_ = std::this_thread::get_id ();
    this->offered_incompatible_total_count_ = status.total_count();

    check_incompatible_qos_status< ::DDS::OfferedIncompatibleQosStatus> (status);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_sender_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_sender_exec_i::on_unexpected_status - "
      << "status <" << DDS::dds_write (status_kind) << ">." << std::endl;
    switch (status_kind)
    {
      case ::DDS::LIVELINESS_CHANGED_STATUS:
        // Receiver only
        this->on_liveliness_changed_thread_id_ = std::this_thread::get_id ();
        break;
      case ::DDS::LIVELINESS_LOST_STATUS:
        {
          this->on_liveliness_lost_thread_id_ = std::this_thread::get_id ();

          IDL::traits< ::DDS::DataWriter>::ref_type writer =
            IDL::traits< ::DDS::DataWriter >::narrow (the_entity);
          if (writer)
          {
            DDS::LivelinessLostStatus lls;
            writer->get_liveliness_lost_status (lls);

            DDS4CCM_TEST_DEBUG << "connector_status_sender_exec_i::on_unexpected_status - "
              << "LivelinessLostStatus: " << DDS::dds_write (lls) << std::endl;
          }
          else
          {
            DDS4CCM_TEST_ERROR << "ERROR: connector_status_sender_exec_i::on_unexpected_status - "
              "Unable to cast the given entity to a DDS::DataWriter." << std::endl;
          }
        }
        break;
#if defined DDSX11_NDDS && DDSX11_NDDS == 1
      case ::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS:
        this->on_reliable_writer_cache_changed_thread_id_ = std::this_thread::get_id ();
        // There's (currently) no way to retrieve this status from NDDS
        break;
      case ::DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS:
        this->on_reliable_reader_activity_changed_thread_id_ = std::this_thread::get_id ();
        // There's (currently) no way to retrieve this status from NDDS
        break;
#endif /* DDSX11_NDDS && DDSX11_NDDS == 1 */
      case ::DDS::PUBLICATION_MATCHED_STATUS:
        this->on_publication_matched_thread_id_ = std::this_thread::get_id ();
        break;
      case ::DDS::SUBSCRIPTION_MATCHED_STATUS:
        this->on_subscription_matched_thread_id_ = std::this_thread::get_id ();
        break;
      default:
        break;
    };

    if (!this->started_)
    {
      // If we need to write samples....
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
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::start_publishing ()
  {
    uint32_t interval = 100000000;
    if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS)
    {
       interval = 1000000000;
    }
    if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS ||
      this->assignment_ == ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED)
    {
      IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

      this->tm_ = tt_s->schedule_repeated_trigger (
                         CORBA::make_reference<TT_Callback> (IDL::traits< CSL_Test::CCM_Sender>::narrow (this->_lock())),
                         CCM_TT::TT_Duration (0, interval),
                         CCM_TT::TT_Duration (0, interval),
                         0);
    }
  }

  void
  Sender_exec_i::tick ()
  {
    try
    {
      IDL::traits < CommonTestConnector::Writer>::ref_type writer =
        this->context_->get_connection_info_write_data ();

      if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS ||
        this->assignment_ == ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED)
      {
        if (this->written_ >= this->samples_to_write ())
        {
          DDS4CCM_TEST_DEBUG << "Sender_exec_i::tick - <"
            << this->written_ << "> samples have been written. Stop the timer"
            << std::endl;
          this->stop ();
        }
        else
        {
          for (CommonTestMessage &msg : this->samples_)
          {
            writer->write_one (msg, DDS::HANDLE_NIL);
            msg.iteration (++msg.iteration ());
            ++this->written_;
            DDS4CCM_TEST_DEBUG << "Sender_exec_i::tick - "
              << "Written " << msg << std::endl;
          }
        }
      }
      else if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_DEADLINE_MISSED)
      {
        for (CommonTestMessage &msg : this->samples_)
        {
          // In the QOS profile is configured that the writer should each second
          // write a sample. This test just writes two samples and than nothing more.
          // An offered deadline missed callback should come in after about one
          // second after these two samples are written.
          // No receiver is needed for this test!!
          writer->write_one (msg, DDS::HANDLE_NIL);
        }
      }
    }
    catch (const CORBA::Exception &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick - "
        "caught CORBA exception: " << ex << std::endl;
    }
    catch (const std::exception &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick - "
        "caught std::exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::tick - "
        "caught unexpected exception" << std::endl;
    }
  }

  void
  Sender_exec_i::notify ()
  {
    this->tick ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::check_unexpected_status ()
  {
    if (this->on_publication_matched_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_unexpected_status_assignment - "
        << "no on_publication_matched status has been received."<< std::endl;
    }
    if (this->on_subscription_matched_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_unexpected_status_assignment - "
        << "an on_subscription_matched status has been received."<< std::endl;
    }
    if (this->on_liveliness_lost_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_unexpected_status_assignment - "
        << "no on_liveliness_lost status has been received."<< std::endl;
    }
    if (this->on_liveliness_changed_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_unexpected_status_assignment - "
        << "an on_liveliness_changed status has been received."<< std::endl;
    }
#if defined DDSX11_NDDS && DDSX11_NDDS == 1
    if (this->on_reliable_reader_activity_changed_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "no on_reliable_reader_activity_changed status has been received."<< std::endl;
    }
    if (this->on_reliable_writer_cache_changed_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "no on_reliable_writer_cache_changed status has been received."<< std::endl;
    }
#endif
  }

  void
  Sender_exec_i::check_on_inconsistent_topic ()
  {
    check_unexpected_status_when_no_match ("Sender_exec_i",
      this->on_subscription_matched_thread_id_,
      this->on_publication_matched_thread_id_,
      this->on_reliable_writer_cache_changed_thread_id_,
      this->on_reliable_reader_activity_changed_thread_id_,
      this->on_liveliness_changed_thread_id_,
      this->on_liveliness_lost_thread_id_);

    if (this->inconsistent_topic_total_count_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_on_inconsistent_topic_assignment - "
        << "no on_inconsistent_topic status has been received." << std::endl;
    }
  }

  void
  Sender_exec_i::check_on_sample_rejected ()
  {
    if (this->on_publication_matched_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_on_sample_rejected - "
        << "no on_publication_matched status has been received."<< std::endl;
    }
    if (this->on_subscription_matched_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_on_sample_rejected - "
        << "an on_subscription_matched status has been received."<< std::endl;
    }
    if (this->on_sample_rejected_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_on_sample_rejected_assignment - "
        << "an on_sample_rejected status has been received." << std::endl;
    }
  }

  void
  Sender_exec_i::check_on_incompatible_qos ()
  {
    // There's no matching of topic so these should not have been detected.
    check_unexpected_status_when_no_match ("Sender_exec_i",
      this->on_subscription_matched_thread_id_,
      this->on_publication_matched_thread_id_,
      this->on_reliable_writer_cache_changed_thread_id_,
      this->on_reliable_reader_activity_changed_thread_id_,
      this->on_liveliness_changed_thread_id_,
      this->on_liveliness_lost_thread_id_);

    // Now check whether the incompatible qos callback came in
    // Requested in the receiver; offered in the sender
    if (this->on_requested_incompatible_qos_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_on_incompatible_qos - "
        << "an on_requested_incompatible_qos status has been received." << std::endl;
    }
    if (this->offered_incompatible_total_count_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_on_incompatible_qos - "
        << "no on_offered_incompatible_qos status has been received." << std::endl;
    }
  }

  void
  Sender_exec_i::check_deadline_missed ()
  {
    // This is a sender test only so no publication_matched should have been received.
    // and certainly no subscription matched status should have been received.
    check_unexpected_status_when_no_match ("Sender_exec_i",
      this->on_subscription_matched_thread_id_,
      this->on_publication_matched_thread_id_,
      this->on_reliable_writer_cache_changed_thread_id_,
      this->on_reliable_reader_activity_changed_thread_id_,
      this->on_liveliness_changed_thread_id_,
      this->on_liveliness_lost_thread_id_);

    if (this->on_offered_deadline_missed_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::check_deadline_missed - "
        << "no on_offered_deadline_missed status has been received." << std::endl;
    }
  }

  void
  Sender_exec_i::stop ()
  {
    this->tm_->cancel();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[ccm_activate]

    if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED ||
      this->assignment_ == ASSIGNMENT::ASSIGNMENT_DEADLINE_MISSED ||
      this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS)
    {
      this->samples_.push_back (CommonTestMessage ("ONE", 1));
      this->samples_.push_back (CommonTestMessage ("TWO", 2));
    }
    if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_DEADLINE_MISSED)
    {
      IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
      if (tt_s)
      {
        this->tm_ = tt_s->schedule_trigger (
          CORBA::make_reference<ContextSwitch> (IDL::traits<CSL_Test::CCM_Sender>::narrow (this->_lock())),
                                    CCM_TT::TT_Duration (0, 0));
      }
    }

    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_passivate - begin" << std::endl;

    // It can be that the offered_incompatible_qos event gets in before our listener has been
    // installed so let us check the status directly with DDS when we have not received
    // any status
    if ((this->assignment_ == ASSIGNMENT::ASSIGNMENT_INCOMPATIBLE_QOS) && (this->offered_incompatible_total_count_ == 0))
    {
      IDL::traits< ::DDS::DataWriter>::ref_type writer =
        this->context_->get_connection_info_write_dds_entity ();
      if (writer)
      {
        ::DDS::OfferedIncompatibleQosStatus status {};

        ::DDS::ReturnCode_t const retcode = writer->get_offered_incompatible_qos_status (status);

        if (retcode == ::DDS::RETCODE_OK)
        {
          offered_incompatible_total_count_ = status.total_count ();
        }
        else
        {
          DDS4CCM_TEST_ERROR << "Sender_exec_i::ccm_passivate - "
              << "ERROR: get_offered_incompatible_qos_status returned an error <" << ::DDS::dds_write (retcode)
              << ">." << std::endl;
        }
      }
    }

    if ((this->assignment_ == ASSIGNMENT::ASSIGNMENT_INCONSISTENT_TOPIC) && (this->inconsistent_topic_total_count_ == 0))
    {
      IDL::traits< ::DDS::DataWriter>::ref_type writer =
        this->context_->get_connection_oit_write_dds_entity ();
      if (writer)
      {
        // Get the topic through the subscriber/domain participant by using the
        // topic name of the connector we are connected to
        IDL::traits< ::DDS::Publisher>::ref_type pub = writer->get_publisher ();
        IDL::traits< ::DDS::DomainParticipant>::ref_type dp = pub->get_participant ();
        IDL::traits< ::CORBA::Object>::ref_type cmp = writer->_get_component ();
        IDL::traits< ::OnInconsistentTopicConnector::CCM_DDS_Event>::ref_type conn =
          IDL::traits< ::OnInconsistentTopicConnector::CCM_DDS_Event >::narrow (cmp);

        ::DDS::Duration_t timeout (0, 0);
        IDL::traits< ::DDS::Topic>::ref_type tp = dp->find_topic(conn->topic_name(), timeout);
        ::DDS::InconsistentTopicStatus status {};
        ::DDS::ReturnCode_t const retcode = tp->get_inconsistent_topic_status (status);

        if (retcode == ::DDS::RETCODE_OK)
        {
          inconsistent_topic_total_count_ = status.total_count();
        }
        else
        {
          DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
              << "ERROR: get_inconsistent_topic_status returned an error <" << ::DDS::dds_write (retcode)
              << ">." << std::endl;
        }
      }
    }

    if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED ||
        this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS)
    {
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
    }
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_passivate - end" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[ccm_remove]
    // Always check the thread id if a certain connect status callback has been received
    check_context_switches(
      this->on_inconsistent_topic_thread_id_,
      this->on_requested_incompatible_qos_thread_id_,
      this->on_sample_rejected_thread_id_,
      this->on_offered_deadline_missed_thread_id_,
      this->on_offered_incompatible_qos_thread_id_,
      this->on_publication_matched_thread_id_,
      this->on_subscription_matched_thread_id_,
      this->on_liveliness_changed_thread_id_,
      this->on_liveliness_lost_thread_id_,
      this->on_reliable_reader_activity_changed_thread_id_,
      this->on_reliable_writer_cache_changed_thread_id_);

    // Now check whether the correct callbacks were invoked
    switch (this->assignment_)
    {
      case ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS:
        this->check_unexpected_status ();
        break;
      case ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED:
        this->check_on_sample_rejected ();
        break;
      case ASSIGNMENT::ASSIGNMENT_INCONSISTENT_TOPIC:
        this->check_on_inconsistent_topic ();
        break;
      case ASSIGNMENT::ASSIGNMENT_INCOMPATIBLE_QOS:
        this->check_on_incompatible_qos ();
        break;
      case ASSIGNMENT::ASSIGNMENT_DEADLINE_MISSED:
        this->check_deadline_missed ();
        break;
      default:
        break;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_exec_i::get_connector_status_sender ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[get_connector_status_sender]
  if (!this->connector_status_sender_)
  {
    this->connector_status_sender_ =
      CORBA::make_reference <connector_status_sender_exec_i> (
        this->context_,
        IDL::traits<CSL_Test::CCM_Sender>::narrow (this->_lock ()),
        this->on_inconsistent_topic_thread_id_,
        this->on_requested_incompatible_qos_thread_id_,
        this->on_sample_rejected_thread_id_,
        this->on_offered_deadline_missed_thread_id_,
        this->on_offered_incompatible_qos_thread_id_,
        this->on_publication_matched_thread_id_,
        this->on_subscription_matched_thread_id_,
        this->on_liveliness_changed_thread_id_,
        this->on_liveliness_lost_thread_id_,
        this->on_reliable_reader_activity_changed_thread_id_,
        this->on_reliable_writer_cache_changed_thread_id_,
        this->offered_incompatible_total_count_,
        this->inconsistent_topic_total_count_);
  }
  return this->connector_status_sender_;
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[get_connector_status_sender]
  }


  std::string
  Sender_exec_i::csl_assignment ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i::csl_assignment[getter]
    return this->csl_assignment_;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i::csl_assignment[getter]
  }

  void
  Sender_exec_i::csl_assignment (
      const std::string& csl_assignment)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i::csl_assignment[setter]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::csl_assignment (setter) - "
      << "Setting assignment to <" << csl_assignment << ">." << std::endl;
    this->csl_assignment_ = csl_assignment;
    this->assignment_ = assignment_to_enum (csl_assignment);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i::csl_assignment[setter]
  }

  uint32_t
  Sender_exec_i::samples_to_write ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i::samples_to_write[getter]
    return this->samples_to_write_;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i::samples_to_write[getter]
  }

  void
  Sender_exec_i::samples_to_write (
      uint32_t samples_to_write)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i::samples_to_write[setter]
    this->samples_to_write_ = samples_to_write;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i::samples_to_write[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<CSL_Test::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[user_namespace_end_impl]

} // namespace CSL_Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[factory]
extern "C" void
create_CSL_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <CSL_Test_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
