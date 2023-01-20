// -*- C++ -*-
/**
 * @file    idl_conversion_sender_exec.h
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the IDL conversion test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_IDL_CONVERSION_SENDER_EXEC_H_FHJCAGIJ_INCLUDED__
#define __RIDL_IDL_CONVERSION_SENDER_EXEC_H_FHJCAGIJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : idl_conversion_sender_impl.h[Header]

#pragma once

#include "idl_conversion_senderEC.h"

#include /**/ "sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_sender_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : idl_conversion_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : idl_conversion_sender_impl.h[user_global_decl]

/// Namespace for implementation of IDL_Conversion_Test::Sender component
namespace IDL_Conversion_Test_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status facet
  class connector_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_exec_i (
      IDL::traits<IDL_Conversion_Test::CCM_Sender_Context>::ref_type context,
      IDL::traits<IDL_Conversion_Test::CCM_Sender>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[ctor]

    /// Destructor
    ~connector_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_ConnectorStatusListener */
    //@{

    void
    on_inconsistent_topic (
        IDL::traits<::DDS::Topic>::ref_type the_topic,
        const ::DDS::InconsistentTopicStatus& status) override;

    void
    on_requested_incompatible_qos (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedIncompatibleQosStatus& status) override;

    void
    on_sample_rejected (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleRejectedStatus& status) override;

    void
    on_offered_deadline_missed (
        IDL::traits<::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedDeadlineMissedStatus& status) override;

    void
    on_offered_incompatible_qos (
        IDL::traits<::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedIncompatibleQosStatus& status) override;

    void
    on_unexpected_status (
        IDL::traits<::DDS::Entity>::ref_type the_entity,
        ::DDS::StatusKind status_kind) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::IDL_Conversion_Test::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_members]
    IDL::traits<IDL_Conversion_Test::CCM_Sender>::weak_ref_type component_executor_;
    bool started_ { false };
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits<::IDL_Conversion_Test::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type get_connector_status () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute rate
    uint16_t rate () override;
    void rate (uint16_t rate) override;

    /// Attribute iterations
    uint16_t iterations () override;
    void iterations (uint16_t iterations) override;

    /// Attribute data_number
    ::CCM_DDS::DataNumber_t data_number () override;
    void data_number (::CCM_DDS::DataNumber_t data_number) override;

    /// Attribute data_number_seq
    ::CCM_DDS::DataNumberSeq data_number_seq () override;
    void data_number_seq (const ::CCM_DDS::DataNumberSeq& data_number_seq) override;

    /// Attribute listener_mode
    ::CCM_DDS::ListenerMode listener_mode () override;
    void listener_mode (::CCM_DDS::ListenerMode listener_mode) override;

    /// Attribute accesss_status
    ::CCM_DDS::AccessStatus accesss_status () override;
    void accesss_status (::CCM_DDS::AccessStatus accesss_status) override;

    /// Attribute instance_status
    ::CCM_DDS::InstanceStatus instance_status () override;
    void instance_status (::CCM_DDS::InstanceStatus instance_status) override;

    /// Attribute read_info
    ::CCM_DDS::ReadInfo read_info () override;
    void read_info (const ::CCM_DDS::ReadInfo& read_info) override;

    /// Attribute read_info_seq
    ::CCM_DDS::ReadInfoSeq read_info_seq () override;
    void read_info_seq (const ::CCM_DDS::ReadInfoSeq& read_info_seq) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_public_ops]
    void start_publishing ();
    void tick ();
    void check_status ();
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::IDL_Conversion_Test::CCM_Sender_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of rate attribute
    uint16_t rate_{};
    /// Class member storing value of iterations attribute
    uint16_t iterations_{};
    /// Class member storing value of data_number attribute
    ::CCM_DDS::DataNumber_t data_number_{};
    /// Class member storing value of data_number_seq attribute
    ::CCM_DDS::DataNumberSeq data_number_seq_{};
    /// Class member storing value of listener_mode attribute
    ::CCM_DDS::ListenerMode listener_mode_{};
    /// Class member storing value of accesss_status attribute
    ::CCM_DDS::AccessStatus accesss_status_{};
    /// Class member storing value of instance_status attribute
    ::CCM_DDS::InstanceStatus instance_status_{};
    /// Class member storing value of read_info attribute
    ::CCM_DDS::ReadInfo read_info_{};
    /// Class member storing value of read_info_seq attribute
    ::CCM_DDS::ReadInfoSeq read_info_seq_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type connector_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_activate_;
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s;
    bool already_publishing_ {};
    uint16_t last_iteration_ {};
    uint16_t last_key_ { 1 };
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_private_ops]
    void stop ();
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Sender_exec_i(const Sender_exec_i&) = delete;
    Sender_exec_i(Sender_exec_i&&) = delete;
    Sender_exec_i& operator=(const Sender_exec_i&) = delete;
    Sender_exec_i& operator=(Sender_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[user_namespace_end_decl]

} // namespace IDL_Conversion_Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[factory]
extern "C" SENDER_EXEC_Export  void
create_IDL_Conversion_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_sender_impl.h[Footer]

#endif /* __RIDL_IDL_CONVERSION_SENDER_EXEC_H_BIDGFGDJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
