// -*- C++ -*-
/**
 * @file    csl_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : csl_receiver_impl.cpp[Header]

#include "csl_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
#include "commonSEEC.h"
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[user_global_impl]

namespace CSL_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::CSL_Test::CCM_Receiver>::weak_ref_type component_executor)
    :  component_executor_(component_executor)
    {}

    virtual
    void
    on_trigger (
         IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
         const ::CCM_TT::TT_Duration& time,
         uint32_t round) override;

    private:
      IDL::traits< ::CSL_Test::CCM_Receiver>::weak_ref_type component_executor_;
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
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<CSL_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : connector_status_receiver_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[ctor]
  connector_status_receiver_exec_i::connector_status_receiver_exec_i (
    IDL::traits< CSL_Test::CCM_Receiver_Context>::ref_type context,
    std::atomic_ulong &on_sample_rejected_invoked,
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
    int32_t &requested_incompatible_total_count,
    int32_t &inconsistent_topic_total_count,
    int32_t &subscription_matched_total_count)
    : context_ (std::move (context))
    , on_sample_rejected_invoked_ (on_sample_rejected_invoked)
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
    , requested_incompatible_total_count_ (requested_incompatible_total_count)
    , inconsistent_topic_total_count_ (inconsistent_topic_total_count)
    , subscription_matched_total_count_ (subscription_matched_total_count)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[ctor]

  connector_status_receiver_exec_i::~connector_status_receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_private_ops]


  /** Operations and attributes from connector_status_receiver */

  void
  connector_status_receiver_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    DDS4CCM_TEST_DEBUG << "connector_status_receiver_exec_i::on_inconsistent_topic - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_inconsistent_topic_thread_id_ = std::this_thread::get_id ();
    this->inconsistent_topic_total_count_ = status.total_count ();

    // Both the sender and receiver receive an on_inconsistent_topic callback so
    // there could two.
    if (this->inconsistent_topic_total_count_ > 2)
    {
      DDS4CCM_TEST_ERROR << "ERROR: connector_status_receiver_exec_i::on_inconsistent_topic - "
        << "unexpected total_count: expected less than 3 - received <" << this->inconsistent_topic_total_count_
        << ">." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_receiver_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_DEBUG << "connector_status_receiver_exec_i::on_requested_incompatible_qos - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_requested_incompatible_qos_thread_id_ = std::this_thread::get_id ();
    this->requested_incompatible_total_count_ = status.total_count();

    check_incompatible_qos_status< ::DDS::RequestedIncompatibleQosStatus > (status);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_receiver_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_DEBUG << "connector_status_receiver_exec_i::on_sample_rejected - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    ++this->on_sample_rejected_invoked_;
    this->on_sample_rejected_thread_id_ = std::this_thread::get_id ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_receiver_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_DEBUG << "connector_status_receiver_exec_i::on_offered_deadline_missed - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_offered_deadline_missed_thread_id_ = std::this_thread::get_id ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_receiver_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    DDS4CCM_TEST_DEBUG << "connector_status_receiver_exec_i::on_offered_incompatible_qos - "
      << "status <" << DDS::dds_write (status) << ">." << std::endl;
    this->on_offered_incompatible_qos_thread_id_ = std::this_thread::get_id ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_receiver_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_receiver_exec_i::on_unexpected_status - "
      << "status <" << DDS::dds_write (status_kind) << ">." << std::endl;
    switch (status_kind)
    {
      case ::DDS::LIVELINESS_CHANGED_STATUS:
        {
          this->on_liveliness_changed_thread_id_ = std::this_thread::get_id ();

          IDL::traits< ::DDS::DataReader>::ref_type reader =
            IDL::traits< ::DDS::DataReader>::narrow (the_entity);
          if (reader)
          {
            ::DDS::LivelinessChangedStatus lcs;
            reader->get_liveliness_changed_status (lcs);

            DDS4CCM_TEST_DEBUG << "connector_status_receiver_exec_i::on_unexpected_status - "
              "LivelinessChangedStatus: " << DDS::dds_write (lcs) << std::endl;
          }
          else
          {
            DDS4CCM_TEST_ERROR << "ERROR: connector_status_receiver_exec_i::on_unexpected_status - "
              "Unable to cast the given entity to a DDS::DataReader." << std::endl;
          }
        }
        break;
      case ::DDS::LIVELINESS_LOST_STATUS:
        // Sender only
        this->on_liveliness_lost_thread_id_ = std::this_thread::get_id ();
        break;
#if defined DDSX11_NDDS && DDSX11_NDDS == 1
      // Sender only; no further checks here
      case ::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS:
        this->on_reliable_writer_cache_changed_thread_id_ = std::this_thread::get_id ();
        break;
      case ::DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS:
        this->on_reliable_reader_activity_changed_thread_id_ = std::this_thread::get_id ();
        break;
#endif /* DDSX11_NDDS && DDSX11_NDDS == 1 */
      case ::DDS::PUBLICATION_MATCHED_STATUS:
        this->on_publication_matched_thread_id_ = std::this_thread::get_id ();
        break;
      case ::DDS::SUBSCRIPTION_MATCHED_STATUS:
        {
          this->on_subscription_matched_thread_id_ = std::this_thread::get_id ();
          // Extra check
          IDL::traits< ::DDS::DataReader>::ref_type reader =
            IDL::traits< ::DDS::DataReader>::narrow (the_entity);
          if (reader)
          {
            DDS::SubscriptionMatchedStatus sms;
            reader->get_subscription_matched_status (sms);
            this->subscription_matched_total_count_ = sms.total_count ();
            if (sms.current_count () != 1 || this->subscription_matched_total_count_ != 1)
            {
              DDS4CCM_TEST_ERROR << "ERROR: connector_status_receiver_exec_i::on_unexpected_status - "
                << "unexpected values in SubscriptionMatchedStatus detected. Expected "
                << "total_count<1> - received <" << this->subscription_matched_total_count_
                << "> and current_count<1> - received <" << sms.current_count ()
                << ">." << std::endl;
            }
          }
          else
          {
            DDS4CCM_TEST_ERROR << "ERROR: connector_status_receiver_exec_i::on_unexpected_status - "
              "Unable to cast the given entity to a DDS::DataReader." << std::endl;
          }
        }
        break;
      default:
        break;
    };
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  void
  Receiver_exec_i::tick ()
  {
    try
    {
      if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS &&
        this->received_ > 20)
      {
        this->stop ();
        // Stop reading after a few samples. This should trigger the liveliness lost/changed
        // callback to occur.
        return;
      }

      IDL::traits < CommonTestConnector::Reader >::ref_type reader =
        this->context_->get_connection_info_get_data ();

      CommonTestMessageSeq samples;
      CCM_DDS::ReadInfoSeq infos;
      reader->read_all (samples, infos);
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::tick - "
        << "<" << samples.size () << "> have been received." << std::endl;
      this->received_ += samples.size ();

      for (CommonTestMessage const &msg : samples)
      {
        if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_DEADLINE_MISSED)
        {
          if (msg.iteration () > static_cast<int32_t>(this->samples_to_receive ()))
          {
            DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
              << "unexpected iteration detected. Expected iteration < <"
              << this->samples_to_receive () << "> - found <"
              << msg.iteration () << ">." << std::endl;
          }
        }
      }
    }
    catch (const CORBA::Exception &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
        "caught CORBA exception: " << ex << std::endl;
    }
    catch (const std::exception &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
        "caught std::exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
        "caught unexpected exception" << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  void
  Receiver_exec_i::check_unexpected_status ()
  {
    if (this->subscription_matched_total_count_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "no on_subscription_matched status has been received."<< std::endl;
    }
    if (this->on_publication_matched_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "an on_publication_matched status has been received."<< std::endl;
    }
    if (this->on_liveliness_lost_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "an on_liveliness_lost status has been received."<< std::endl;
    }
    if (this->on_liveliness_changed_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "no on_liveliness_changed status has been received."<< std::endl;
    }
#if defined DDSX11_NDDS && DDSX11_NDDS == 1
    if (this->on_reliable_reader_activity_changed_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "an on_reliable_reader_activity_changed status has been received."<< std::endl;
    }
    if (this->on_reliable_writer_cache_changed_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_unexpected_status_assignment - "
        << "an on_reliable_writer_cache_changed status has been received."<< std::endl;
    }
#endif
  }

  void
  Receiver_exec_i::check_on_inconsistent_topic ()
  {
    // There's no matching of topic so these should not have been detected.
    check_unexpected_status_when_no_match ("Receiver_exec_i",
      this->on_subscription_matched_thread_id_,
      this->on_publication_matched_thread_id_,
      this->on_reliable_writer_cache_changed_thread_id_,
      this->on_reliable_reader_activity_changed_thread_id_,
      this->on_liveliness_changed_thread_id_,
      this->on_liveliness_lost_thread_id_);

    if (this->inconsistent_topic_total_count_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_on_inconsistent_topic - "
        << "no on_inconsistent_topic status has been received." << std::endl;
    }
  }

  void
  Receiver_exec_i::check_on_sample_rejected ()
  {
    if (this->on_publication_matched_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_on_sample_rejected - "
        << "an on_publication_matched status has been received."<< std::endl;
    }
    if (this->on_subscription_matched_thread_id_ == std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_on_sample_rejected - "
        << "no on_subscription_matched status has been received."<< std::endl;
    }
    if (this->on_sample_rejected_invoked_ < this->samples_to_receive ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_on_sample_rejected - "
        << "unexpected number of on_sample_rejected invocations received: "
        << "expected at least " << this->samples_to_receive () << " - received <"
        << this->on_sample_rejected_invoked_ << ">." << std::endl;
    }
  }

  void
  Receiver_exec_i::check_on_incompatible_qos ()
  {
    // There's no matching of topic so these should not have been detected.
    check_unexpected_status_when_no_match ("Receiver_exec_i",
      this->on_subscription_matched_thread_id_,
      this->on_publication_matched_thread_id_,
      this->on_reliable_writer_cache_changed_thread_id_,
      this->on_reliable_reader_activity_changed_thread_id_,
      this->on_liveliness_changed_thread_id_,
      this->on_liveliness_lost_thread_id_);
    // Now check whether the incompatible qos callback came in
    // Requested in the receiver; offered in the sender
    if (this->requested_incompatible_total_count_ == 0)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_on_incompatible_qos - "
        << "no on_requested_incompatible_qos status has been received." << std::endl;
    }
    if (this->on_offered_incompatible_qos_thread_id_ != std::thread::id ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::check_on_incompatible_qos - "
        << "an on_offered_incompatible_qos status has been received." << std::endl;
    }
  }

  void
  Receiver_exec_i::stop()
  {
    if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS ||
      this->assignment_ == ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED)
    {
      this->tm_->cancel();
    }
  }

  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
    if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS)
    {

      this->tm_ = tt_s->schedule_repeated_trigger (
                         CORBA::make_reference<TT_Callback> (IDL::traits< CSL_Test::CCM_Receiver>::narrow (this->_lock())),
                         CCM_TT::TT_Duration (6, 0),
                         CCM_TT::TT_Duration (3, 0),
                         0);
    }
    else if (this->assignment_ == ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED)
    {
      this->tm_ = tt_s->schedule_repeated_trigger (
                               CORBA::make_reference<TT_Callback> (IDL::traits< CSL_Test::CCM_Receiver>::narrow (this->_lock())),
                               CCM_TT::TT_Duration (1, 0),
                               CCM_TT::TT_Duration (1, 0),
                               0);
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_passivate - begin" << std::endl;

    // It can be that the requested_incompatible_qos event gets in before our listener has been
    // installed so let us check the status directly with DDS when we have not received
    // any status
    if ((this->assignment_ == ASSIGNMENT::ASSIGNMENT_INCOMPATIBLE_QOS) && (this->requested_incompatible_total_count_ == 0))
    {
      IDL::traits< ::DDS::DataReader>::ref_type reader =
        this->context_->get_connection_info_get_dds_entity ();
      if (reader)
      {
        ::DDS::RequestedIncompatibleQosStatus status {};
        ::DDS::ReturnCode_t const retcode = reader->get_requested_incompatible_qos_status (status);

        if (retcode == ::DDS::RETCODE_OK)
        {
          requested_incompatible_total_count_ = status.total_count();
        }
        else
        {
          DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
              << "ERROR: get_requested_incompatible_qos_status returned an error <" << ::DDS::dds_write (retcode)
              << ">." << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
              << "ERROR: get_dds_entity port not connected" << std::endl;
      }
    }

    if ((this->assignment_ == ASSIGNMENT::ASSIGNMENT_INCONSISTENT_TOPIC) && (this->inconsistent_topic_total_count_ == 0))
    {
      IDL::traits< ::DDS::DataReader>::ref_type reader =
        this->context_->get_connection_info_get_dds_entity ();
      if (reader)
      {
        // Get the topic through the subscriber/domain participant by using the
        // topic name of the connector we are connected to
        IDL::traits< ::DDS::Subscriber>::ref_type sub = reader->get_subscriber ();
        IDL::traits< ::DDS::DomainParticipant>::ref_type dp = sub->get_participant ();
        IDL::traits< ::CORBA::Object >::ref_type cmp = reader->_get_component ();
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);

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
      else
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
              << "ERROR: get_dds_entity port not connected" << std::endl;
      }
    }

    if ((this->assignment_ == ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS) && (this->subscription_matched_total_count_ == 0))
    {
      IDL::traits< ::DDS::DataReader>::ref_type reader =
        this->context_->get_connection_info_get_dds_entity ();
      if (reader)
      {
        ::DDS::SubscriptionMatchedStatus status {};
        ::DDS::ReturnCode_t const retcode = reader->get_subscription_matched_status (status);

        if (retcode == ::DDS::RETCODE_OK)
        {
          subscription_matched_total_count_ = status.total_count();
        }
        else
        {
          DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
              << "ERROR: get_subscription_matched_status returned an error <" << ::DDS::dds_write (retcode)
              << ">." << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
              << "ERROR: get_dds_entity port not connected" << std::endl;
      }
    }

    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_passivate - end" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
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
        // The receiver component is not deployed in this case. This callback is
        // sender only; no receiver needed in this case.
        break;
      default:
        break;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Receiver_exec_i::get_connector_status_receiver ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[get_connector_status_receiver]
  if (!this->connector_status_receiver_)
  {
    this->connector_status_receiver_ =
      CORBA::make_reference <connector_status_receiver_exec_i> (
        this->context_,
        this->on_sample_rejected_invoked_,
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
        this->requested_incompatible_total_count_,
        this->inconsistent_topic_total_count_,
        this->subscription_matched_total_count_);
  }
  return this->connector_status_receiver_;
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[get_connector_status_receiver]
  }


  std::string
  Receiver_exec_i::csl_assignment ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i::csl_assignment[getter]
    return this->csl_assignment_;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i::csl_assignment[getter]
  }

  void
  Receiver_exec_i::csl_assignment (
      const std::string& csl_assignment)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i::csl_assignment[setter]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::csl_assignment (setter) - "
      << "Setting assignment to <" << csl_assignment << ">." << std::endl;
    this->csl_assignment_ = csl_assignment;
    this->assignment_ = assignment_to_enum (csl_assignment);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i::csl_assignment[setter]
  }

  uint32_t
  Receiver_exec_i::samples_to_receive ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i::samples_to_receive[getter]
    return this->samples_to_receive_;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i::samples_to_receive[getter]
  }

  void
  Receiver_exec_i::samples_to_receive (
      uint32_t samples_to_receive)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i::samples_to_receive[setter]
    this->samples_to_receive_ = samples_to_receive;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i::samples_to_receive[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<CSL_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace CSL_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[factory]
extern "C" void
create_CSL_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <CSL_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
