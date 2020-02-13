// -*- C++ -*-
/**
 * @file    subscriber_exec.cpp
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : subscriber_impl.cpp[Header]

#include "subscriber_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[user_global_impl]
// X11_FUZZ: disable check_cout_cerr
//@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[user_global_impl]

namespace subscriber_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    std::cout << "Received " << IDL::traits<ShapeType>::write (datum) << std::endl;
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::ShapeTypeSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_read_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[ctor]
  info_read_status_exec_i::info_read_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[ctor]

  info_read_status_exec_i::~info_read_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[user_private_ops]


  /** Operations and attributes from info_read_status */

  void
  info_read_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_read_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_state_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[ctor]
  info_state_data_listener_exec_i::info_state_data_listener_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[ctor]

  info_state_data_listener_exec_i::~info_state_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_state_data_listener */

  void
  info_state_data_listener_exec_i::on_creation (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i::on_creation[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i::on_creation[_datum_info]
  }

  void
  info_state_data_listener_exec_i::on_one_update (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i::on_one_update[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i::on_one_update[_datum_info]
  }

  void
  info_state_data_listener_exec_i::on_many_updates (
      const ::ShapeTypeSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i::on_many_updates[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i::on_many_updates[_data_infos]
  }

  void
  info_state_data_listener_exec_i::on_deletion (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i::on_deletion[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i::on_deletion[_datum_info]
  }
  /**
   * Facet Executor Implementation Class : info_state_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[ctor]
  info_state_status_exec_i::info_state_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[ctor]

  info_state_status_exec_i::~info_state_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[user_private_ops]


  /** Operations and attributes from info_state_status */

  void
  info_state_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_state_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_out_2_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[ctor]
  info_out_2_data_listener_exec_i::info_out_2_data_listener_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[ctor]

  info_out_2_data_listener_exec_i::~info_out_2_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_2_data_listener */

  void
  info_out_2_data_listener_exec_i::on_one_data (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_2_data_listener_exec_i::on_many_data (
      const ::ShapeTypeSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_2_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[ctor]
  info_out_2_status_exec_i::info_out_2_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[ctor]

  info_out_2_status_exec_i::~info_out_2_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_2_status */

  void
  info_out_2_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_2_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_read_2_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[ctor]
  info_read_2_status_exec_i::info_read_2_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[ctor]

  info_read_2_status_exec_i::~info_read_2_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[user_private_ops]


  /** Operations and attributes from info_read_2_status */

  void
  info_read_2_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_read_2_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_get_2_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[ctor]
  info_get_2_status_exec_i::info_get_2_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[ctor]

  info_get_2_status_exec_i::~info_get_2_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_2_status */

  void
  info_get_2_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_2_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_state_2_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[ctor]
  info_state_2_data_listener_exec_i::info_state_2_data_listener_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[ctor]

  info_state_2_data_listener_exec_i::~info_state_2_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_state_2_data_listener */

  void
  info_state_2_data_listener_exec_i::on_creation (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_creation[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_creation[_datum_info]
  }

  void
  info_state_2_data_listener_exec_i::on_one_update (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_one_update[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_one_update[_datum_info]
  }

  void
  info_state_2_data_listener_exec_i::on_many_updates (
      const ::ShapeTypeSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_many_updates[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_many_updates[_data_infos]
  }

  void
  info_state_2_data_listener_exec_i::on_deletion (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_deletion[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i::on_deletion[_datum_info]
  }
  /**
   * Facet Executor Implementation Class : info_state_2_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[ctor]
  info_state_2_status_exec_i::info_state_2_status_exec_i (
    IDL::traits< CCM_subscriber_comp_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[ctor]

  info_state_2_status_exec_i::~info_state_2_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[user_private_ops]


  /** Operations and attributes from info_state_2_status */

  void
  info_state_2_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_state_2_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : subscriber_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[ctor]
  subscriber_comp_exec_i::subscriber_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[ctor]

  subscriber_comp_exec_i::~subscriber_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[user_private_ops]

  /** Session component operations */
  void subscriber_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[configuration_complete]
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[configuration_complete]
  }

  void subscriber_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[ccm_activate]
     CIAOX11_TEST_INFO << "Subscriber ACTIVATE" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[ccm_activate]
  }

  void subscriber_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[ccm_passivate]
  }

  void subscriber_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[ccm_remove]
  }

  IDL::traits< ::ShapeTypeInterface::CCM_Listener>::ref_type
  subscriber_comp_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_data_listener]
    if (!this->info_out_data_listener_)
    {
      this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (this->context_);
    }
    return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_status]
    if (!this->info_out_status_)
    {
      this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (this->context_);
    }
    return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_status]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_read_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_read_status]
    if (!this->info_read_status_)
    {
      this->info_read_status_ = CORBA::make_reference <info_read_status_exec_i> (this->context_);
    }
    return this->info_read_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_read_status]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_get_status]
    if (!this->info_get_status_)
    {
      this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
    }
    return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_get_status]
  }

  IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::ref_type
  subscriber_comp_exec_i::get_info_state_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_data_listener]
    if (!this->info_state_data_listener_)
    {
      this->info_state_data_listener_ = CORBA::make_reference <info_state_data_listener_exec_i> (this->context_);
    }
    return this->info_state_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_state_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_status]
    if (!this->info_state_status_)
    {
      this->info_state_status_ = CORBA::make_reference <info_state_status_exec_i> (this->context_);
    }
    return this->info_state_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_status]
  }

  IDL::traits< ::ShapeTypeInterface::CCM_Listener>::ref_type
  subscriber_comp_exec_i::get_info_out_2_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_2_data_listener]
    if (!this->info_out_2_data_listener_)
    {
      this->info_out_2_data_listener_ = CORBA::make_reference <info_out_2_data_listener_exec_i> (this->context_);
    }
    return this->info_out_2_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_2_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_out_2_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_2_status]
    if (!this->info_out_2_status_)
    {
      this->info_out_2_status_ = CORBA::make_reference <info_out_2_status_exec_i> (this->context_);
    }
    return this->info_out_2_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_out_2_status]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_read_2_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_read_2_status]
    if (!this->info_read_2_status_)
    {
      this->info_read_2_status_ = CORBA::make_reference <info_read_2_status_exec_i> (this->context_);
    }
    return this->info_read_2_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_read_2_status]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_get_2_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_get_2_status]
    if (!this->info_get_2_status_)
    {
      this->info_get_2_status_ = CORBA::make_reference <info_get_2_status_exec_i> (this->context_);
    }
    return this->info_get_2_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_get_2_status]
  }

  IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::ref_type
  subscriber_comp_exec_i::get_info_state_2_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_2_data_listener]
    if (!this->info_state_2_data_listener_)
    {
      this->info_state_2_data_listener_ = CORBA::make_reference <info_state_2_data_listener_exec_i> (this->context_);
    }
    return this->info_state_2_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_2_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  subscriber_comp_exec_i::get_info_state_2_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_2_status]
    if (!this->info_state_2_status_)
    {
      this->info_state_2_status_ = CORBA::make_reference <info_state_2_status_exec_i> (this->context_);
    }
    return this->info_state_2_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[get_info_state_2_status]
  }

  /// Operations from Components::SessionComponent
  void
  subscriber_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[set_session_context]
    this->context_ = IDL::traits< CCM_subscriber_comp_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[user_namespace_end_impl]

} // namespace subscriber_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[factory]
extern "C" void
create_subscriber_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <subscriber_comp_Impl::subscriber_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
