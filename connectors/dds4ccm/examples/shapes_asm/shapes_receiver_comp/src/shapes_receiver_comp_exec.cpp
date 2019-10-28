// -*- C++ -*-
/**
 * @file    shapes_receiver_comp_exec.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Shapes receiver component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : shapes_receiver_comp_impl.cpp[Header]

#include "shapes_receiver_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl[user_global_impl]

namespace Shapes_Receiver_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits<Shapes::CCM_Receiver_comp_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::ShapeType& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(info);
    CIAOX11_TEST_DEBUG << "Receiver, on_one_data " << IDL::traits< ShapeType>::write (datum) << std::endl;

    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::ShapeTypeSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits<Shapes::CCM_Receiver_comp_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ctor]
  Receiver_comp_exec_i::Receiver_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ctor]

  Receiver_comp_exec_i::~Receiver_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[configuration_complete]
  }

  void Receiver_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ccm_activate]
    IDL::traits< ::CCM_DDS::DataListenerControl>::ref_type lc =
      this->context_->get_connection_info_out_data_control ();
    lc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ccm_activate]
  }

  void Receiver_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ccm_passivate]
  }

  void Receiver_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[ccm_remove]
  }

  IDL::traits< ::ShapeTypeInterface::CCM_Listener >::ref_type
  Receiver_comp_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[get_info_out_data_listener]
  if (!this->info_out_data_listener_)
  {
    this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (this->context_);
  }
  return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[get_info_out_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_comp_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[get_info_out_status]
  if (!this->info_out_status_)
  {
    this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (this->context_);
  }
  return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[get_info_out_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<Shapes::CCM_Receiver_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl::Receiver_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl[user_namespace_end_impl]

} // namespace Shapes_Receiver_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Receiver_comp_Impl[factory]
extern "C" void
create_Shapes_Receiver_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Shapes_Receiver_comp_Impl::Receiver_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Receiver_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_receiver_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
