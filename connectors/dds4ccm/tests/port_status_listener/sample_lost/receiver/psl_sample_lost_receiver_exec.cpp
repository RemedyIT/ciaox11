// -*- C++ -*-
/**
 * @file    psl_sample_lost_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psl_sample_lost_receiver_impl.cpp[Header]

#include "psl_sample_lost_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl[user_global_impl]

namespace PSL_SampleLostTest_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::PSL_SampleLostTest::CCM_Receiver>::weak_ref_type component_executor)
    : component_executor_(component_executor)
    {}

   virtual
   void
   on_trigger (
       IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
       const ::CCM_TT::TT_Duration& time,
       uint32_t round) override;

  private:
    IDL::traits< ::PSL_SampleLostTest::CCM_Receiver>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
     IDL::traits< ::CCM_TT::TT_Timer>::ref_type /*timer*/,
     const ::CCM_TT::TT_Duration& /*time*/,
     uint32_t /*round*/)
  {
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<PSL_SampleLostTest::CCM_Receiver_Context>::ref_type context,
    std::atomic_bool &sample_lost, atomic_thread_id &thread_id)
    : context_ (std::move (context))
    , sample_lost_ (sample_lost)
    , thread_id_ (thread_id)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    this->thread_id_ = std::this_thread::get_id ();
    this->sample_lost_ = true;

    DDS4CCM_TEST_DEBUG << "info_get_status_exec_i::on_sample_lost - "
      << DDS::dds_write (the_reader) << " - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits<PSL_SampleLostTest::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits<PSL_SampleLostTest::CCM_Receiver_Context>::ref_type context,
    std::atomic_bool &sample_lost, atomic_thread_id &thread_id)
    : context_ (std::move (context))
    , sample_lost_ (sample_lost)
    , thread_id_ (thread_id)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    this->thread_id_ = std::this_thread::get_id ();
    this->sample_lost_ = true;

    DDS4CCM_TEST_DEBUG << "info_out_status_exec_i::on_sample_lost - "
      << DDS::dds_write (the_reader) << " - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits< ::PSL_SampleLostTest::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_sample_rejected - "
      << DDS::dds_write (the_reader) << " - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    X11_UNUSED_ARG(the_entity);
    X11_UNUSED_ARG(status_kind);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[user_public_ops]
  void Receiver_exec_i::tick ()
  {
    IDL::traits< CommonTestConnector::Reader>::ref_type reader =
      this->context_->get_connection_info_out_data ();
    try
    {
      CommonTestMessageSeq data;
      ::CCM_DDS::ReadInfoSeq readinfo;
      reader->read_all(data, readinfo);
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::tick - <"
        << data.size () << "> samples read." << std::endl;
      for(CommonTestMessage const &msg : data)
      {
        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::tick - "
          << "Sample read : " << msg << std::endl;
      }
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::tick")
  }
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits< CCM_DDS::DataListenerControl>::ref_type lc =
      this->context_->get_connection_info_out_data_control ();
    try
    {
      lc->mode (::CCM_DDS::ListenerMode::NOT_ENABLED);
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::ccm_activate")

    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
            this->tm_ = tt_s->schedule_repeated_trigger (
                               CORBA::make_reference<TT_Callback> (IDL::traits< PSL_SampleLostTest::CCM_Receiver>::narrow (this->_lock())),
                               CCM_TT::TT_Duration (3, 1),
                               CCM_TT::TT_Duration (3, 1),
                               0);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    this->tm_->cancel();
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ccm_remove]
    if (!this->sample_lost_getter_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_remove - "
        << "No sample lost callback received on the Port status listener of "
        << "the getter." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_remove - "
        << "Sample lost callback received on the Port status listener of "
        << "the getter." << std::endl;
      DDS4CCM_TEST_UTILS::check_thread_switch ("Sample lost getter", this->thread_id_getter_);
    }
    if (!this->sample_lost_reader_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_remove - "
        << "No sample lost callback received on the Port status listener of "
        << "the reader." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_remove - "
        << "Sample lost callback received on the Port status listener of "
        << "the reader." << std::endl;
      DDS4CCM_TEST_UTILS::check_thread_switch ("Sample lost reader", this->thread_id_reader_);
    }
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ =
      CORBA::make_reference <info_get_status_exec_i> (
        this->context_, this->sample_lost_getter_, this->thread_id_getter_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  }

  IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  if (!this->info_out_data_listener_)
  {
    this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (this->context_);
  }
  return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  if (!this->info_out_status_)
  {
    this->info_out_status_ =
      CORBA::make_reference <info_out_status_exec_i> (
        this->context_, this->sample_lost_reader_, this->thread_id_reader_);
  }
  return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Receiver_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_connector_status]
    if (!this->connector_status_)
    {
      this->connector_status_ = CORBA::make_reference <connector_status_exec_i> (this->context_);
    }
    return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[get_connector_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<PSL_SampleLostTest::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl[user_namespace_end_impl]

} // namespace PSL_SampleLostTest_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Receiver_Impl[factory]
extern "C" void
create_PSL_SampleLostTest_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <PSL_SampleLostTest_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_sample_lost_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
