// -*- C++ -*-
/**
 * @file    qa_sl_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : qa_sl_receiver_impl.cpp[Header]

#include "qa_sl_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl[user_includes]
#include "dds4ccm/tests/filters/common/listeners/state/receiver/filters_common_sl_receiver_checks.h"
//@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl[user_global_impl]
// Your code here
//@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl[user_global_impl]

namespace QA_State_Listen_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : listen_port_1_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[ctor]
  listen_port_1_data_listener_exec_i::listen_port_1_data_listener_exec_i (
    IDL::traits<QA_State_Listen_Test::CCM_Receiver_Context>::ref_type context,
    std::atomic_ullong &created,
    std::atomic_ullong &updated,
    std::atomic_ullong &deleted)
    : context_ (std::move (context))
    , created_ (created)
    , updated_ (updated)
    , deleted_ (deleted)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[ctor]

  listen_port_1_data_listener_exec_i::~listen_port_1_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from listen_port_1_data_listener */

  void
  listen_port_1_data_listener_exec_i::on_creation (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_creation[_datum_info]
    X11_UNUSED_ARG(info);

    ++this->created_;
    check_on_creation_obo (datum);
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_creation[_datum_info]
  }

  void
  listen_port_1_data_listener_exec_i::on_one_update (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_one_update[_datum_info]
    X11_UNUSED_ARG(info);

    ++this->updated_;
    check_on_one_update (
      "listen_port_1_data_listener_exec_i::on_one_update",
      datum);
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_one_update[_datum_info]
  }

  void
  listen_port_1_data_listener_exec_i::on_many_updates (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_many_updates[_data_infos]
    X11_UNUSED_ARG (data);
    X11_UNUSED_ARG (infos);

    DDS4CCM_TEST_ERROR << "ERROR: listen_port_1_data_listener_exec_i::on_many_updates - "
      << "Unexpected invocation." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_many_updates[_data_infos]
  }

  void
  listen_port_1_data_listener_exec_i::on_deletion (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_deletion[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);

    ++this->deleted_;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i::on_deletion[_datum_info]
  }
  /**
   * Facet Executor Implementation Class : listen_port_1_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[ctor]
  listen_port_1_status_exec_i::listen_port_1_status_exec_i (
    IDL::traits<QA_State_Listen_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[ctor]

  listen_port_1_status_exec_i::~listen_port_1_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_private_ops]


  /** Operations and attributes from listen_port_1_status */

  void
  listen_port_1_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_requested_deadline_missed 1 - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  listen_port_1_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_sample_lost 1 - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : listen_port_2_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[ctor]
  listen_port_2_data_listener_exec_i::listen_port_2_data_listener_exec_i (
    IDL::traits<QA_State_Listen_Test::CCM_Receiver_Context>::ref_type context,
    std::atomic_ullong &created,
    std::atomic_ullong &updated,
    std::atomic_ullong &deleted)
    : context_ (std::move (context))
    , created_ (created)
    , updated_ (updated)
    , deleted_ (deleted)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[ctor]

  listen_port_2_data_listener_exec_i::~listen_port_2_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from listen_port_2_data_listener */

  void
  listen_port_2_data_listener_exec_i::on_creation (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_creation[_datum_info]
    X11_UNUSED_ARG(info);

    ++this->created_;

    check_on_creation_mbm (datum);
    if (this->created_ == keys ())
    {
      // sender may continue.
      IDL::traits< WriterStarter >::ref_type starter =
        this->context_->get_connection_writer_start ();
      starter->start_write ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_creation[_datum_info]
  }

  void
  listen_port_2_data_listener_exec_i::on_one_update (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_one_update[_datum_info]
    X11_UNUSED_ARG (datum);
    X11_UNUSED_ARG (info);

    DDS4CCM_TEST_ERROR << "ERROR: listen_port_2_data_listener_exec_i::on_one_updates - "
      << "Unexpected invocation." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_one_update[_datum_info]
  }

  void
  listen_port_2_data_listener_exec_i::on_many_updates (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_many_updates[_data_infos]
    X11_UNUSED_ARG(infos);
    this->updated_ += data.size ();

    check_on_many_updates (
      "listen_port_2_data_listener_exec_i::on_many_updates",
      data);
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_many_updates[_data_infos]
  }

  void
  listen_port_2_data_listener_exec_i::on_deletion (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_deletion[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);

    ++this->deleted_;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i::on_deletion[_datum_info]
  }
  /**
   * Facet Executor Implementation Class : listen_port_2_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[ctor]
  listen_port_2_status_exec_i::listen_port_2_status_exec_i (
    IDL::traits<QA_State_Listen_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[ctor]

  listen_port_2_status_exec_i::~listen_port_2_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_private_ops]


  /** Operations and attributes from listen_port_2_status */

  void
  listen_port_2_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_requested_deadline_missed 2 - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  listen_port_2_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    DDS4CCM_TEST_ERROR << "on_sample_lost 2 - " << DDS::dds_write (status) << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // First set the queries
    IDL::traits< CommonTestConnector::Reader >::ref_type reader_1 =
      this->context_->get_connection_listen_port_1_data ();
    IDL::traits< CommonTestConnector::Reader >::ref_type reader_2 =
      this->context_->get_connection_listen_port_2_data ();

    ::DDS::StringSeq params (2);
    params[0] = std::to_string (min_iteration ());
    params[1] = std::to_string (max_iteration ());

    reader_1->query (CCM_DDS::QueryFilter (QUERY_LISTENER_I, params));
    reader_2->query (CCM_DDS::QueryFilter (QUERY_LISTENER_II, params));

    // Start the listeners
    IDL::traits< ::CCM_DDS::DataListenerControl >::ref_type lc_1 =
      this->context_->get_connection_listen_port_1_data_control ();

    if (!lc_1)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener (1) control receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc_1->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);

    IDL::traits< ::CCM_DDS::DataListenerControl >::ref_type lc_2 =
      this->context_->get_connection_listen_port_2_data_control ();

    if (!lc_2)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener (2) control receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc_2->mode (::CCM_DDS::ListenerMode::MANY_BY_MANY);
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    bool error = false;
    if (this->created_on_listener_1_ != keys ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of keys created on listener I: expected <"
        << keys () << "> - created <" << this->created_on_listener_1_ << ">."
        << std::endl;
      error = true;

    }
    if (this->created_on_listener_2_ != keys ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of keys created on listener II: expected <"
        << keys () << "> - created <" << this->created_on_listener_2_ << ">."
        << std::endl;
      error = true;
    }

    if (this->updated_on_listener_1_ != expected_number_of_samples_on_listener_1 ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of keys updated on listener I: expected <"
        << expected_number_of_samples_on_listener_1 () << "> - updated <"
        << this->updated_on_listener_1_ << ">." << std::endl;
      error = true;
    }
    if (this->updated_on_listener_2_ != expected_number_of_samples_on_listener_2 ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of keys updated on listener II: expected <"
        << expected_number_of_samples_on_listener_2 () << "> - updated <"
        << this->updated_on_listener_2_ << ">." << std::endl;
      error = true;
    }

#if (DDSX11_NDDS == 1)
    // This test is filtering on non-key fields. Because we are using a non-key
    // filter OpenDDS can't determine whether we want to have the dispose or not
    // so it doesn't propagate these to our listeners.
    if (this->deleted_on_listener_1_ != keys ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of keys deleted on listener I: expected <"
        << keys () << "> - deleted <" << this->deleted_on_listener_1_ << ">."
        << std::endl;
      error = true;
    }
    if (this->deleted_on_listener_2_ != keys ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of keys deleted on listener II: expected <"
        << keys () << "> - deleted <" << this->deleted_on_listener_2_ << ">."
        << std::endl;
      error = true;
    }
#endif /* DDSX11_NDDS == 1 */
    if (!error)
    {
      DDS4CCM_TEST_DEBUG << "OK: Receiver_exec_i::ccm_passivate - "
        << "Expected number of samples received." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CommonTestConnector::CCM_StateListener >::ref_type
  Receiver_exec_i::get_listen_port_1_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_1_data_listener]
  if (!this->listen_port_1_data_listener_)
  {
    this->listen_port_1_data_listener_ =
      CORBA::make_reference <listen_port_1_data_listener_exec_i> (
        this->context_,
        this->created_on_listener_1_,
        this->updated_on_listener_1_,
        this->deleted_on_listener_1_);
  }
  return this->listen_port_1_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_1_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_listen_port_1_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_1_status]
  if (!this->listen_port_1_status_)
  {
    this->listen_port_1_status_ = CORBA::make_reference <listen_port_1_status_exec_i> (this->context_);
  }
  return this->listen_port_1_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_1_status]
  }

  IDL::traits< ::CommonTestConnector::CCM_StateListener >::ref_type
  Receiver_exec_i::get_listen_port_2_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_2_data_listener]
  if (!this->listen_port_2_data_listener_)
  {
    this->listen_port_2_data_listener_ =
      CORBA::make_reference <listen_port_2_data_listener_exec_i> (
        this->context_,
        this->created_on_listener_2_,
        this->updated_on_listener_2_,
        this->deleted_on_listener_2_);
  }
  return this->listen_port_2_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_2_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_listen_port_2_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_2_status]
  if (!this->listen_port_2_status_)
  {
    this->listen_port_2_status_ = CORBA::make_reference <listen_port_2_status_exec_i> (this->context_);
  }
  return this->listen_port_2_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[get_listen_port_2_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<QA_State_Listen_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace QA_State_Listen_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : QA_State_Listen_Test_Receiver_Impl[factory]
extern "C" void
create_QA_State_Listen_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <QA_State_Listen_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : QA_State_Listen_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : qa_sl_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
