// -*- C++ -*-
/**
 * @file    updater_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the updater test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : updater_receiver_impl.cpp[Header]

#include "updater_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[user_global_impl]
constexpr uint16_t on_creation_expected () { return 5; }
constexpr uint16_t on_one_update_expected () { return 4; }
constexpr uint16_t on_many_updates_expected_min () { return 2; }
constexpr uint16_t on_many_updates_expected_max () { return 4; }
constexpr uint16_t on_deletion_expected () { return 5; }
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[user_global_impl]

namespace UpdaterModule_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[user_namespace_impl]
  uint16_t check_created_samples (
    const ::CommonTestMessage& datum,
    const ::CCM_DDS::ReadInfo& info,
    const std::string &listener)
  {
    uint16_t errors = 0;

    //special case.
    if (datum.key () == "ONE_3")
    {
      if (datum.iteration () != 8)
      {
        DDS4CCM_TEST_ERROR << "check_created_samples (" << listener << ") - ERROR: "
          << "Unexpected value for x found for key ONE_3. expected <8> - got <"
          << datum.iteration () << ">." << std::endl;
        ++errors;
      }
    }
    else
    {
      std::string const many ("MANY_" + std::to_string (datum.iteration ()));
      std::string const one ("ONE_" + std::to_string (datum.iteration ()));
      if (datum.key () != many && datum.key () != one)
      {
        DDS4CCM_TEST_ERROR << "check_created_samples (" << listener << ") - ERROR: "
          << "Unexpected key value found. expected <" << one << " or " << many
          << "> - got <" << datum.key () << ">." << std::endl;
        ++errors;
      }
    }


    if (info.access_status () != CCM_DDS::AccessStatus::FRESH_INFO)
    {
      DDS4CCM_TEST_ERROR << "check_created_samples (" << listener << ") - ERROR: "
        << "Unexpected AccessStatus found. expected <"
        << "CCM_DDS::AccessStatus::FRESH_INFO> - got <"
        << DDS::dds_write (info.access_status ())
        << ">." << std::endl;
      ++errors;
    }

    if (info.instance_status () != CCM_DDS::InstanceStatus::INSTANCE_CREATED)
    {
      DDS4CCM_TEST_ERROR << "check_created_samples (" << listener << ") - ERROR: "
        << "Unexpected InstanceStatus found. expected <"
        << "CCM_DDS::InstanceStatus::INSTANCE_CREATED> - got <"
        << DDS::dds_write (info.instance_status ())
        << ">." << std::endl;
      ++errors;
    }
    return errors;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_one_by_one_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[ctor]
  info_out_one_by_one_data_listener_exec_i::info_out_one_by_one_data_listener_exec_i (
    IDL::traits<UpdaterModule::CCM_Receiver_Context>::ref_type context,
    std::atomic_ushort &errors_found,
    std::atomic_ushort &obo_on_creation_received,
    std::atomic_ushort &obo_on_one_update_received,
    std::atomic_ushort &obo_on_many_updates_received,
    std::atomic_ushort &obo_on_deletion_received,
    atomic_thread_id &obo_thread_id)
    : context_ (std::move (context))
    , errors_found_ (errors_found)
    , obo_on_creation_received_ (obo_on_creation_received)
    , obo_on_one_update_received_ (obo_on_one_update_received)
    , obo_on_many_updates_received_ (obo_on_many_updates_received)
    , obo_on_deletion_received_ (obo_on_deletion_received)
    , obo_thread_id_ (obo_thread_id)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[ctor]

  info_out_one_by_one_data_listener_exec_i::~info_out_one_by_one_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_one_by_one_data_listener */

  void
  info_out_one_by_one_data_listener_exec_i::on_creation (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_creation[_datum_info]
    this->obo_thread_id_ = std::this_thread::get_id ();
    ++this->obo_on_creation_received_;

    this->errors_found_ += check_created_samples (datum, info, "obo");

    this->context_->get_connection_next_assignment ()->state_event_received (
      STATE_EVENT::OBO_ON_CREATION_RECEIVED);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_creation[_datum_info]
  }

  void
  info_out_one_by_one_data_listener_exec_i::on_one_update (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_one_update[_datum_info]
    this->obo_thread_id_ = std::this_thread::get_id ();
    ++this->obo_on_one_update_received_;

      std::string const many ("MANY_" + std::to_string (datum.iteration () - 5));
      std::string const one ("ONE_" + std::to_string (datum.iteration () - 5));
      if (datum.key () != many && datum.key () != one)
      {
        DDS4CCM_TEST_ERROR << "on_one_update (obo) - ERROR: "
            << "Unexpected key value found. expected <" << one << " or " << many
            << "> - got <" << datum.key () << ">." << std::endl;
        ++this->errors_found_;
      }

    if (info.instance_status () != CCM_DDS::InstanceStatus::INSTANCE_UPDATED)
    {
      DDS4CCM_TEST_ERROR << "on_one_update (obo) - ERROR: "
        << "Unexpected InstanceStatus found. expected <"
        << "CCM_DDS::InstanceStatus::INSTANCE_UPDATED> - got <"
        << DDS::dds_write (info.instance_status ())
        << ">." << std::endl;
      ++this->errors_found_;
    }
    this->context_->get_connection_next_assignment ()->state_event_received (
      STATE_EVENT::OBO_ON_UPDATE_RECEIVED);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_one_update[_datum_info]
  }

  void
  info_out_one_by_one_data_listener_exec_i::on_many_updates (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_many_updates[_data_infos]
    this->obo_thread_id_ = std::this_thread::get_id ();
    ++this->obo_on_many_updates_received_;

    DDS4CCM_TEST_ERROR << "on_many_updates (mbm) - ERROR: "
      << "Unexpected invocation in a ONE_BY_ONE listener. data<"
      << data << "> - info <" << DDS::dds_write (infos) << ">."
      << std::endl;
    ++this->errors_found_;
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_many_updates[_data_infos]
  }

  void
  info_out_one_by_one_data_listener_exec_i::on_deletion (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_deletion[_datum_info]
    X11_UNUSED_ARG(datum);

    this->obo_thread_id_ = std::this_thread::get_id ();
    ++this->obo_on_deletion_received_;

    if (info.instance_status () != CCM_DDS::InstanceStatus::INSTANCE_DELETED)
    {
      DDS4CCM_TEST_ERROR << "on_deletion (obo) - ERROR: "
        << "Unexpected InstanceStatus found. expected <"
        << "CCM_DDS::InstanceStatus::INSTANCE_DELETED> - got <"
        << DDS::dds_write (info.instance_status ())
        << ">." << std::endl;
      ++this->errors_found_;
    }
    this->context_->get_connection_next_assignment ()->state_event_received (
      STATE_EVENT::OBO_ON_DELETION_RECEIVED);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i::on_deletion[_datum_info]
  }
  /**
   * Facet Executor Implementation Class : info_out_one_by_one_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[ctor]
  info_out_one_by_one_status_exec_i::info_out_one_by_one_status_exec_i (
    IDL::traits<UpdaterModule::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[ctor]

  info_out_one_by_one_status_exec_i::~info_out_one_by_one_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_one_by_one_status */

  void
  info_out_one_by_one_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_one_by_one_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_out_many_by_many_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[ctor]
  info_out_many_by_many_data_listener_exec_i::info_out_many_by_many_data_listener_exec_i (
    IDL::traits<UpdaterModule::CCM_Receiver_Context>::ref_type context,
    std::atomic_ushort &errors_found,
    std::atomic_ushort &mbm_on_creation_received,
    std::atomic_ushort &mbm_on_one_update_received,
    std::atomic_ushort &mbm_on_many_updates_received,
    std::atomic_ushort &mbm_on_deletion_received,
    atomic_thread_id &mbm_thread_id)
    : context_ (std::move (context))
    , errors_found_ (errors_found)
    , mbm_on_creation_received_ (mbm_on_creation_received)
    , mbm_on_one_update_received_ (mbm_on_one_update_received)
    , mbm_on_many_updates_received_ (mbm_on_many_updates_received)
    , mbm_on_deletion_received_ (mbm_on_deletion_received)
    , mbm_thread_id_ (mbm_thread_id)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[ctor]

  info_out_many_by_many_data_listener_exec_i::~info_out_many_by_many_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_many_by_many_data_listener */

  void
  info_out_many_by_many_data_listener_exec_i::on_creation (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_creation[_datum_info]
    this->mbm_thread_id_ = std::this_thread::get_id ();
    ++this->mbm_on_creation_received_;

    this->errors_found_ += check_created_samples (datum, info, "mbm");

    this->context_->get_connection_next_assignment ()->state_event_received (
      STATE_EVENT::MBM_ON_CREATION_RECEIVED);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_creation[_datum_info]
  }

  void
  info_out_many_by_many_data_listener_exec_i::on_one_update (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_one_update[_datum_info]
    this->mbm_thread_id_ = std::this_thread::get_id ();
    ++this->mbm_on_one_update_received_;

    DDS4CCM_TEST_ERROR << "info_out_many_by_many_data_listener_exec_i::on_one_update - "
      << "Unexpected invocation of on_one_update in a MANY_BY_MANY listener. Received data : "
      << "data <" << datum << "> - info <"
      << DDS::dds_write (info) << ">." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_one_update[_datum_info]
  }

  void
  info_out_many_by_many_data_listener_exec_i::on_many_updates (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_many_updates[_data_infos]
    this->mbm_thread_id_ = std::this_thread::get_id ();
    ++this->mbm_on_many_updates_received_;

    for (CommonTestMessage const &ut : data)
    {
      std::string const many ("MANY_" + std::to_string (ut.iteration () - 5));
      std::string const one ("ONE_" + std::to_string (ut.iteration () - 5));
      if (ut.key () != many && ut.key () != one)
      {
        DDS4CCM_TEST_ERROR << "on_many_updates (mbm) - ERROR: "
          << "Unexpected key value found. expected <" << one << " or " << many
          << "> - got <" << ut.key () << ">." << std::endl;
        ++this->errors_found_;
      }
    }

    for (CCM_DDS::ReadInfo const &ri : infos)
    {
      if (ri.instance_status () != CCM_DDS::InstanceStatus::INSTANCE_UPDATED)
      {
      DDS4CCM_TEST_ERROR << "on_many_updates (mbm) - ERROR: "
          << "Unexpected InstanceStatus found. expected <"
          << "CCM_DDS::InstanceStatus::INSTANCE_UPDATED> - got <"
          << DDS::dds_write (ri.instance_status ())
          << ">." << std::endl;
        ++this->errors_found_;
      }
    }

    this->context_->get_connection_next_assignment ()->state_event_received (
      STATE_EVENT::MBM_ON_UPDATE_RECEIVED);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_many_updates[_data_infos]
  }

  void
  info_out_many_by_many_data_listener_exec_i::on_deletion (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_deletion[_datum_info]
    X11_UNUSED_ARG (datum);
    this->mbm_thread_id_ = std::this_thread::get_id ();
    ++this->mbm_on_deletion_received_;

    if (info.instance_status () != CCM_DDS::InstanceStatus::INSTANCE_DELETED)
    {
      DDS4CCM_TEST_ERROR << "on_deletion (mbm) - ERROR: "
        << "Unexpected InstanceStatus found. expected <"
        << "CCM_DDS::InstanceStatus::INSTANCE_DELETED> - got <"
        << DDS::dds_write (info.instance_status ())
        << ">." << std::endl;
      ++this->errors_found_;
    }
    this->context_->get_connection_next_assignment ()->state_event_received (
      STATE_EVENT::MBM_ON_DELETION_RECEIVED);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i::on_deletion[_datum_info]
  }
  /**
   * Facet Executor Implementation Class : info_out_many_by_many_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[ctor]
  info_out_many_by_many_status_exec_i::info_out_many_by_many_status_exec_i (
    IDL::traits<UpdaterModule::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[ctor]

  info_out_many_by_many_status_exec_i::~info_out_many_by_many_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_many_by_many_status */

  void
  info_out_many_by_many_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_many_by_many_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    IDL::traits< ::CCM_DDS::StateListenerControl>::ref_type lc =
      this->context_->get_connection_info_out_one_by_one_data_control ();

    if (!lc)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener control for one_by_one receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);

    lc = this->context_->get_connection_info_out_many_by_many_data_control ();

    if (!lc)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener control for many_by_many receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc->mode (::CCM_DDS::ListenerMode::MANY_BY_MANY);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[ccm_activate]
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Check context switches
    DDS4CCM_TEST_DEBUG << std::endl << "-----------------------------" << std::endl;
    DDS4CCM_TEST_UTILS::check_thread_switch ("ONE_BY_ONE Status listener", this->obo_thread_id_);
    DDS4CCM_TEST_UTILS::check_thread_switch ("MANY_BY_MANY Status listener", this->mbm_thread_id_);

    // Check number of received samples
    DDS4CCM_TEST_DEBUG << std::endl << "-----------------------------" << std::endl;

    if (this->obo_on_creation_received_ != on_creation_expected () ||
      this->mbm_on_creation_received_ != on_creation_expected ())
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_remove - ERROR: unexpected number of "
        << "on_creation invocations received. expected <" << on_creation_expected ()
        << "> - received in obo <" << this->obo_on_creation_received_ << "> - "
        << "received in mbm <" << this->mbm_on_creation_received_ << ">."
        << std::endl;
    }

    if (this->obo_on_one_update_received_ != on_one_update_expected ())
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_remove - ERROR: unexpected number of "
        << "on_one_update invocations received in the obo-listener. "
        << "expected <" << on_one_update_expected ()
        << "> - received <" << this->obo_on_one_update_received_ << ">."
        << std::endl;
    }

    if (this->mbm_on_many_updates_received_ < on_many_updates_expected_min () ||
        this->mbm_on_many_updates_received_ > on_many_updates_expected_max ())
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_remove - ERROR: unexpected number of "
        << "on_many_updates invocations received in the mbm-listener. "
        << "expected <" << on_many_updates_expected_min () << "-" << on_many_updates_expected_max ()
        << "> - received <" << this->mbm_on_many_updates_received_ << ">."
        << std::endl;
    }

    if (this->obo_on_many_updates_received_ != 0)
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_remove - ERROR: unexpected number of "
        << "on_many_updates invocations received in the obo-listener. expected <0> - "
        << "received <" << this->obo_on_many_updates_received_ << ">."
        << std::endl;
    }

    if (this->mbm_on_one_update_received_ != 0)
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_remove - ERROR: unexpected number of "
        << "on_one_update invocations received in the mbm-listener. expected <0>"
        << "> - received <" << this->mbm_on_one_update_received_ << ">."
        << std::endl;
    }

    if (this->obo_on_deletion_received_ != on_deletion_expected () ||
      this->mbm_on_deletion_received_ != on_deletion_expected ())
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_remove - ERROR: unexpected number of "
        << "on_deletion invocations received. expected <" << on_deletion_expected ()
        << "> - received in obo <" << this->obo_on_deletion_received_ << "> - "
        << "received in mbm <" << this->mbm_on_deletion_received_ << ">."
        << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CommonTestConnector::CCM_StateListener>::ref_type
  Receiver_exec_i::get_info_out_one_by_one_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_one_by_one_data_listener]
  if (!this->info_out_one_by_one_data_listener_)
  {
    this->info_out_one_by_one_data_listener_ = CORBA::make_reference <info_out_one_by_one_data_listener_exec_i> (
      this->context_,
      this->errors_found_,
      this->obo_on_creation_received_,
      this->obo_on_one_update_received_,
      this->obo_on_many_updates_received_,
      this->obo_on_deletion_received_,
      this->obo_thread_id_);
  }
  return this->info_out_one_by_one_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_one_by_one_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_one_by_one_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_one_by_one_status]
  if (!this->info_out_one_by_one_status_)
  {
    this->info_out_one_by_one_status_ = CORBA::make_reference <info_out_one_by_one_status_exec_i> (this->context_);
  }
  return this->info_out_one_by_one_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_one_by_one_status]
  }

  IDL::traits< ::CommonTestConnector::CCM_StateListener>::ref_type
  Receiver_exec_i::get_info_out_many_by_many_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_many_by_many_data_listener]
  if (!this->info_out_many_by_many_data_listener_)
  {
    this->info_out_many_by_many_data_listener_ = CORBA::make_reference <info_out_many_by_many_data_listener_exec_i> (
      this->context_,
      this->errors_found_,
      this->mbm_on_creation_received_,
      this->mbm_on_one_update_received_,
      this->mbm_on_many_updates_received_,
      this->mbm_on_deletion_received_,
      this->mbm_thread_id_);
  }
  return this->info_out_many_by_many_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_many_by_many_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_many_by_many_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_many_by_many_status]
  if (!this->info_out_many_by_many_status_)
  {
    this->info_out_many_by_many_status_ = CORBA::make_reference <info_out_many_by_many_status_exec_i> (this->context_);
  }
  return this->info_out_many_by_many_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[get_info_out_many_by_many_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<UpdaterModule::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[user_namespace_end_impl]

} // namespace UpdaterModule_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[factory]
extern "C" void
create_UpdaterModule_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <UpdaterModule_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
