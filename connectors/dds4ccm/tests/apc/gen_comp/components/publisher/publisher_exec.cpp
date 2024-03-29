// -*- C++ -*-
/**
 * @file    publisher_exec.cpp
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : publisher_impl.cpp[Header]

#include "publisher_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[user_includes]
#include "ace/Reactor.h"
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[user_global_impl]
// X11_FUZZ: disable check_cout_cerr
//@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[user_global_impl]

namespace publisher_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[user_namespace_impl]
  class TT_Callback final : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits<CCM_publisher_comp>::weak_ref_type component_executor)
    : component_executor_(component_executor)
    {}

    void
    on_trigger (
       IDL::traits<::CCM_TT::TT_Timer>::ref_type,
       const ::CCM_TT::TT_Duration&,
       uint32_t round) override;

   private:
     IDL::traits<CCM_publisher_comp>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
     IDL::traits<::CCM_TT::TT_Timer>::ref_type,
     const ::CCM_TT::TT_Duration&,
     uint32_t)
  {
    auto cex = IDL::traits<publisher_comp_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick ();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_ShapeType_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[ctor]
  connector_status_ShapeType_exec_i::connector_status_ShapeType_exec_i (
    IDL::traits<CCM_publisher_comp_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[ctor]

  connector_status_ShapeType_exec_i::~connector_status_ShapeType_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_private_ops]


  /** Operations and attributes from connector_status_ShapeType */

  void
  connector_status_ShapeType_exec_i::on_inconsistent_topic (
      IDL::traits<::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_ShapeType_exec_i::on_requested_incompatible_qos (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_ShapeType_exec_i::on_sample_rejected (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_ShapeType_exec_i::on_offered_deadline_missed (
      IDL::traits<::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_ShapeType_exec_i::on_offered_incompatible_qos (
      IDL::traits<::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_ShapeType_exec_i::on_unexpected_status (
      IDL::traits<::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_unexpected_status[_the_entity_status_kind]
    X11_UNUSED_ARG(the_entity);
    X11_UNUSED_ARG(status_kind);
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : publisher_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[ctor]
  publisher_comp_exec_i::publisher_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[ctor]

  publisher_comp_exec_i::~publisher_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[user_private_ops]

  /** Session component operations */
  void publisher_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[configuration_complete]
  }

  void publisher_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "Publisher ACTIVATE" << std::endl;
    try
      {
        IDL::traits < ::ShapeTypeInterface::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        this->instance_handle_ = writer->register_instance (this->square_);

        IDL::traits<CORBA::Object>::ref_type orb_object =
          this->context_->the_service_registry ()->resolve_service (CIAOX11::SVCID_ORB);
        IDL::traits<CORBA::ORB>::ref_type orb =
          IDL::traits<CORBA::ORB>::narrow (orb_object);

        IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
        this->tm_ = tt_s->schedule_repeated_trigger (
                              CORBA::make_reference<TT_Callback> (IDL::traits<CCM_publisher_comp>::narrow (this->_lock())),
                              CCM_TT::TT_Duration (0,500000000),
                              CCM_TT::TT_Duration (0,500000000),
                              0);
      }
    catch (const std::exception& )
      {
      }
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[ccm_activate]
  }

  void publisher_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[ccm_passivate]
    if (this->tm_)
    {
      this->tm_->cancel();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[ccm_passivate]
  }

  void publisher_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[ccm_remove]
  }

  IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  publisher_comp_exec_i::get_connector_status_ShapeType ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[get_connector_status_ShapeType]
    if (!this->connector_status_ShapeType_)
    {
      this->connector_status_ShapeType_ = CORBA::make_reference <connector_status_ShapeType_exec_i> (this->context_);
    }
    return this->connector_status_ShapeType_;
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[get_connector_status_ShapeType]
  }

  /// Operations from Components::SessionComponent
  void
  publisher_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_publisher_comp_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[user_namespace_end_impl]
  void
  publisher_comp_exec_i::tick ()
  {
    try
      {
        IDL::traits<::ShapeTypeInterface::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        writer->write_one (this->square_, this->instance_handle_);

        std::cout << "TICK" << std::endl;
//         DDS4CCM_TEST_DEBUG
//           << "Updated "
//           << this->square_
//           << std::endl;
      }
    catch (const CCM_DDS::NonExistent& )
      {
//         DDS4CCM_TEST_ERROR
//           << "NonExistent Error while writing "
//           << this->square_ << std::endl;
      }
    catch (const CCM_DDS::InternalError& )
      {
//         DDS4CCM_TEST_ERROR
//           << "Internal Error while writing "
//           << this->square_ << std::endl;
      }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[user_namespace_end_impl]

} // namespace publisher_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[factory]
extern "C" void
create_publisher_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <publisher_comp_Impl::publisher_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
