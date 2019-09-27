// -*- C++ -*-
/**
 * @file    publisher_exec.h
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_PUBLISHER_EXEC_H_EABHEJCC_INCLUDED__
#define __RIDL_PUBLISHER_EXEC_H_EABHEJCC_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : publisher_impl.h[Header]

#pragma once

#include "publisherEC.h"

#include /**/ "publisher_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : publisher_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : publisher_impl.h[user_global_decl]

/// Namespace for implementation of publisher_comp component
namespace publisher_comp_Impl
{
  /// Forward declarations
  class publisher_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status_ShapeType facet
  class connector_status_ShapeType_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_ShapeType_exec_i (
        IDL::traits< CCM_publisher_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[ctor]

    /// Destructor
    virtual ~connector_status_ShapeType_exec_i ();

    /** @name Operations from ::CCM_DDS::CCM_ConnectorStatusListener */
    //@{

    virtual
    void
    on_inconsistent_topic (
        IDL::traits< ::DDS::Topic>::ref_type the_topic,
        const ::DDS::InconsistentTopicStatus& status) override;

    virtual
    void
    on_requested_incompatible_qos (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedIncompatibleQosStatus& status) override;

    virtual
    void
    on_sample_rejected (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleRejectedStatus& status) override;

    virtual
    void
    on_offered_deadline_missed (
        IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedDeadlineMissedStatus& status) override;

    virtual
    void
    on_offered_incompatible_qos (
        IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedIncompatibleQosStatus& status) override;

    virtual
    void
    on_unexpected_status (
        IDL::traits< ::DDS::Entity>::ref_type the_entity,
        ::DDS::StatusKind status_kind) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_publisher_comp_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::connector_status_ShapeType_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : publisher_comp_exec_i
  class publisher_comp_exec_i final
    : public virtual IDL::traits< CCM_publisher_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[ctor]
    /// Constructor
    publisher_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[ctor]
    /// Destructor
    virtual ~publisher_comp_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status_ShapeType facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type get_connector_status_ShapeType () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    virtual void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    virtual void configuration_complete () override;

    /// Component state change method to activated state
    virtual void ccm_activate () override;

    /// Component state change method to passivated state
    virtual void ccm_passivate () override;

    /// Component state change method to removed state
    virtual void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[user_public_ops]
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_publisher_comp_Context >::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type connector_status_ShapeType_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[user_members]
    ::DDS::InstanceHandle_t instance_handle_ { ::DDS::HANDLE_NIL };
    ShapeType square_ {"GREEN", 25, 25, 24};
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl::publisher_comp_exec_i[user_private_ops]
    //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl::publisher_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    publisher_comp_exec_i(const publisher_comp_exec_i&) = delete;
    publisher_comp_exec_i(publisher_comp_exec_i&&) = delete;
    publisher_comp_exec_i& operator=(const publisher_comp_exec_i&) = delete;
    publisher_comp_exec_i& operator=(publisher_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[user_namespace_end_decl]

} // namespace publisher_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_comp_Impl[factory]
extern "C" PUBLISHER_EXEC_Export  void
create_publisher_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : publisher_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : publisher_impl.h[Footer]

#endif /* __RIDL_PUBLISHER_EXEC_H_EABHEJCC_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
