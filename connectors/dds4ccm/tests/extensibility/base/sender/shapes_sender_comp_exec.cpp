// -*- C++ -*-
/**
 * @file    shapes_sender_comp_exec.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Shapes sender executor
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : shapes_sender_comp_impl.cpp[Header]

#include "shapes_sender_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_global_impl]
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_global_impl]

namespace Shapes_Sender_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits<Shapes::CCM_Sender_comp_Context>::ref_type context,
    IDL::traits<Shapes::CCM_Sender_comp>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[dtor]
  // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind <" << DDS::dds_write(status_kind) << ">" << std::endl;
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // started_ flag.
    if (!this->started_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 1))
      {
        auto cex = IDL::traits<Sender_comp_exec_i>::narrow (this->component_executor_.lock ());
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
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]
  Sender_comp_exec_i::Sender_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]

  Sender_comp_exec_i::~Sender_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
  void
  Sender_comp_exec_i::start_publishing ()
  {
    if (!this->already_publishing_)
    {
      this->already_publishing_ = true;

      if (this->instance_handle_ != ::DDS::HANDLE_NIL)
        {
          IDL::traits< ::ShapeTypeInterface::Writer>::ref_type writer =
            this->context_->get_connection_info_write_data ();

          writer->write_one (square_, this->instance_handle_);

          CIAOX11_TEST_DEBUG
            << "Updated "
            << IDL::traits<ShapeType>::write (square_)
            << std::endl;
        }
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[configuration_complete]
  }

  void Sender_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_activate]
    try
      {
        IDL::traits < ::ShapeTypeInterface::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        this->instance_handle_ = writer->register_instance (this->square_);

        CIAOX11_TEST_DEBUG
          << "Registered shape " << IDL::traits<ShapeType>::write (this->square_) << std::endl;
      }
    catch (const CCM_DDS::AlreadyCreated& )
      {
        CIAOX11_TEST_ERROR
          << "AlreadyCreated Error while creating "
          << IDL::traits<ShapeType>::write (this->square_) << std::endl;
      }
    catch (const CCM_DDS::InternalError& ex)
      {
        CIAOX11_TEST_ERROR
          << "Internal Error while creating "
          << IDL::traits<ShapeType>::write (this->square_)
          << ": " << ex << std::endl;
      }
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_activate]
  }

  void Sender_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_passivate]
    try
      {
        IDL::traits<ShapeTypeInterface::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        writer->unregister_instance (this->square_,
                                     this->instance_handle_);

        this->instance_handle_ = ::DDS::HANDLE_NIL;

        CIAOX11_TEST_DEBUG
          << "Unregistered shape " << IDL::traits<ShapeType>::write (this->square_) << std::endl;
      }
    catch (const CCM_DDS::NonExistent& )
      {
        CIAOX11_TEST_ERROR <<
         IDL::traits<ShapeType>::write (this->square_)  << " not deleted." << std::endl;
      }
    catch (const CCM_DDS::InternalError& ex)
      {
        CIAOX11_TEST_ERROR
          << "Internal Error while deleting "
          << IDL::traits<ShapeType>::write (this->square_)
          << ": " << ex << std::endl;
      }
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_passivate]
  }

  void Sender_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_comp_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[get_connector_status]
    if (!this->connector_status_)
    {
      this->connector_status_ = IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::make_reference <connector_status_exec_i> (
        this->context_, IDL::traits<Shapes::CCM_Sender_comp>::narrow (this->_lock()));
    }
    return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[get_connector_status]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<Shapes::CCM_Sender_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_end_impl]

} // namespace Shapes_Sender_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[factory]
extern "C" void
create_Shapes_Sender_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Shapes_Sender_comp_Impl::Sender_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
