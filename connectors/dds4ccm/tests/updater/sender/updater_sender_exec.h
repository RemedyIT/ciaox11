// -*- C++ -*-
/**
 * @file    updater_sender_exec.h
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the updater test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : updater_sender_impl.h[Header]

#pragma once

#include "updater_senderEC.h"

#include /**/ "sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_sender_impl.h[user_includes]
#include "dds4ccm/tests/common/ticker_t.h"
//@@{__RIDL_REGEN_MARKER__} - END : updater_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : updater_sender_impl.h[user_global_decl]

/// Namespace for implementation of UpdaterModule::Sender component
namespace UpdaterModule_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[user_namespace_decl]
  enum class UPDATER_ASSIGNMENT : uint32_t
  {
    CREATE_ONE,
    CREATE_ONE_ALREADY_EXIST,
    UPDATE_ONE,
    UPDATE_ONE_NOT_REGISTERED,
    DELETE_ONE,
    DELETE_ONE_NOT_REGISTERED,
    UPDATE_DELETE_REGISTER,
    UPDATE_DELETE_REGISTER_2,
    CREATE_MANY,
    UPDATE_MANY,
    DELETE_MANY,
    END_TEST
  };

  typedef DDS4CCM_TEST_UTILS::ContextSwitch<
    IDL::traits<UpdaterModule::CCM_Sender>::weak_ref_type,
    Sender_exec_i> ContextSwitch;
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status facet
  class connector_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_exec_i (
        IDL::traits< UpdaterModule::CCM_Sender_Context>::ref_type context,
        IDL::traits< UpdaterModule::CCM_Sender>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[ctor]

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::UpdaterModule::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[user_members]
    IDL::traits<UpdaterModule::CCM_Sender>::weak_ref_type component_executor_;
    bool started_ { false };
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::connector_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::connector_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for next_assignment facet
  class next_assignment_exec_i final
    : public IDL::traits<CCM_NextAssignment>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    next_assignment_exec_i (
        IDL::traits< UpdaterModule::CCM_Sender_Context>::ref_type context,
        IDL::traits< UpdaterModule::CCM_Sender>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[ctor]

    /// Destructor
    ~next_assignment_exec_i () override;

    /** @name Operations from CCM_NextAssignment */
    //@{

    void
    state_event_received (
        ::STATE_EVENT event) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::UpdaterModule::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_members]
    IDL::traits< UpdaterModule::CCM_Sender>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::next_assignment_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits<::UpdaterModule::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type get_connector_status () override;
    /// Factory method and getter for the next_assignment facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<CCM_NextAssignment>::ref_type get_next_assignment () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[user_public_ops]
    void start_publishing ();
    void start_next_assignment (STATE_EVENT event);
    void notify ();
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::UpdaterModule::CCM_Sender_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type connector_status_;
    IDL::traits<CCM_NextAssignment>::ref_type next_assignment_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[user_members]
    CommonTestMessageSeq topic_seq_one_ {};
    CommonTestMessageSeq topic_seq_many_ {};

    bool started_ { false };
    IDL::traits<CCM_TT::TT_Timer>::ref_type thread_switch_ {};

    UPDATER_ASSIGNMENT assignment_ { UPDATER_ASSIGNMENT::CREATE_ONE };
    uint16_t test_errors_ {};

    uint16_t create_one_event_obo_received_ {};
    uint16_t create_one_event_mbm_received_ {};
    uint16_t update_event_obo_received_ {};
    uint16_t update_event_mbm_received_ {};
    uint16_t delete_one_event_obo_received_ {};
    uint16_t delete_one_event_mbm_received_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl::Sender_exec_i[user_private_ops]
    void create_instances ();

    uint16_t create_one ();
    uint16_t create_one_already_exist ();
    uint16_t update_one ();
    uint16_t update_one_not_registered ();
    uint16_t delete_one ();
    uint16_t delete_one_not_registered ();
    uint16_t update_and_delete_one_after_register ();
    uint16_t update_and_delete_one_after_register_2 ();
    uint16_t create_many ();
    uint16_t update_many ();
    uint16_t delete_many ();
    void check_status ();
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl::Sender_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[user_namespace_end_decl]

} // namespace UpdaterModule_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Sender_Impl[factory]
extern "C" SENDER_EXEC_Export  void
create_UpdaterModule_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_sender_impl.h[Footer]
// Your footer (code) here
// -*- END -*-
