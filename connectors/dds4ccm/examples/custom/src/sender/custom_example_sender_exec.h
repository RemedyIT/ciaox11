// -*- C++ -*-
/**
 * @file    custom_example_sender_exec.h
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the IDL example.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_CUSTOM_EXAMPLE_SENDER_EXEC_H_JAFCCHAE_INCLUDED__
#define __RIDL_CUSTOM_EXAMPLE_SENDER_EXEC_H_JAFCCHAE_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : custom_example_sender_impl.h[Header]

#pragma once

#include "custom_example_senderEC.h"

#include /**/ "custom_example_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_sender_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : custom_example_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : custom_example_sender_impl.h[user_global_decl]

/// Namespace for implementation of Example::BasicPublisher_comp component
namespace Example_BasicPublisher_comp_Impl
{
  /// Forward declarations
  class BasicPublisher_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[user_namespace_decl]


  /// Executor implementation class for CA1DataPub_CSL facet
  class CA1DataPub_CSL_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    CA1DataPub_CSL_exec_i (
        IDL::traits< Example::CCM_BasicPublisher_comp_Context>::ref_type context,
        IDL::traits< Example::CCM_BasicPublisher_comp>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[ctor]

    /// Destructor
    virtual ~CA1DataPub_CSL_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Example::CCM_BasicPublisher_comp_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_members]
    IDL::traits< ::Example::CCM_BasicPublisher_comp>::weak_ref_type component_executor_;
    bool started_ { false };
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : BasicPublisher_comp_exec_i
  class BasicPublisher_comp_exec_i final
    : public virtual IDL::traits< ::Example::CCM_BasicPublisher_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ctor]
    /// Constructor
    BasicPublisher_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ctor]
    /// Destructor
    virtual ~BasicPublisher_comp_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the CA1DataPub_CSL facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type get_CA1DataPub_CSL () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute count

    virtual
    uint32_t
    count () override;

    virtual
    void
    count (
        uint32_t count) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_public_ops]
    void start_publishing ();
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Example::CCM_BasicPublisher_comp_Context >::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of count attribute
    uint32_t count_ {};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type CA1DataPub_CSL_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    uint32_t counter_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_private_ops]
    void stop_publishing ();
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    BasicPublisher_comp_exec_i(const BasicPublisher_comp_exec_i&) = delete;
    BasicPublisher_comp_exec_i(BasicPublisher_comp_exec_i&&) = delete;
    BasicPublisher_comp_exec_i& operator=(const BasicPublisher_comp_exec_i&) = delete;
    BasicPublisher_comp_exec_i& operator=(BasicPublisher_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[user_namespace_end_decl]

} // namespace Example_BasicPublisher_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[factory]
extern "C" CUSTOM_EXAMPLE_SENDER_EXEC_Export  void
create_Example_BasicPublisher_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_sender_impl.h[Footer]

#endif /* __RIDL_CUSTOM_EXAMPLE_SENDER_EXEC_H_IFGHHCAH_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
