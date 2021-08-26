// -*- C++ -*-
/**
 * @file    shapes_sender_comp_exec.h
 * @author  Johnny Willemsen
 *
 * @brief   Shapes sender executor
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_SHAPES_SENDER_COMP_EXEC_H_IJHJIJGJ_INCLUDED__
#define __RIDL_SHAPES_SENDER_COMP_EXEC_H_IJHJIJGJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : shapes_sender_comp_impl.h[Header]

#pragma once

#include "shapes_sender_compEC.h"

#include /**/ "shapes_sender_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : shapes_sender_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : shapes_sender_comp_impl.h[user_global_decl]

/// Namespace for implementation of Shapes::Sender_comp component
namespace Shapes_Sender_comp_Impl
{
  /// Forward declarations
  class Sender_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status facet
  class connector_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_exec_i (
        IDL::traits< ::Shapes::CCM_Sender_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[ctor]

    /// Destructor
    ~connector_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_ConnectorStatusListener */
    //@{

    void
    on_inconsistent_topic (
        IDL::traits< ::DDS::Topic>::ref_type the_topic,
        const ::DDS::InconsistentTopicStatus& status) override;

    void
    on_requested_incompatible_qos (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedIncompatibleQosStatus& status) override;

    void
    on_sample_rejected (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleRejectedStatus& status) override;

    void
    on_offered_deadline_missed (
        IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedDeadlineMissedStatus& status) override;

    void
    on_offered_incompatible_qos (
        IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedIncompatibleQosStatus& status) override;

    void
    on_unexpected_status (
        IDL::traits< ::DDS::Entity>::ref_type the_entity,
        ::DDS::StatusKind status_kind) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Shapes::CCM_Sender_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::connector_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::connector_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_comp_exec_i
  class Sender_comp_exec_i final
    : public virtual IDL::traits< ::Shapes::CCM_Sender_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]
    /// Constructor
    Sender_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]
    /// Destructor
    ~Sender_comp_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type get_connector_status () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Shapes::CCM_Sender_comp_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type connector_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_members]
    ::DDS::InstanceHandle_t instance_handle_ { ::DDS::HANDLE_NIL };
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
    void start_publishing ();
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Sender_comp_exec_i(const Sender_comp_exec_i&) = delete;
    Sender_comp_exec_i(Sender_comp_exec_i&&) = delete;
    Sender_comp_exec_i& operator=(const Sender_comp_exec_i&) = delete;
    Sender_comp_exec_i& operator=(Sender_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_end_decl]

} // namespace Shapes_Sender_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[factory]
extern "C" SHAPES_SENDER_COMP_EXEC_Export  void
create_Shapes_Sender_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.h[Footer]

#endif /* __RIDL_SHAPES_SENDER_COMP_EXEC_H_IJHJIJGJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
