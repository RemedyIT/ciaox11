// -*- C++ -*-
/**
 * @file    csl_sender_exec.h
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_CSL_SENDER_EXEC_H_JHFFIGDD_INCLUDED__
#define __RIDL_CSL_SENDER_EXEC_H_JHFFIGDD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : csl_sender_impl.h[Header]

#pragma once

#include "csl_senderEC.h"

#include /**/ "connector_status_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_sender_impl.h[user_includes]
#include <map>
#include "dds4ccm/tests/common/ticker_t.h"
#include "../csl_common.h"
//@@{__RIDL_REGEN_MARKER__} - END : csl_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : csl_sender_impl.h[user_global_decl]

/// Namespace for implementation of CSL_Test::Sender component
namespace CSL_Test_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[user_namespace_decl]
  typedef DDS4CCM_TEST_UTILS::ContextSwitch<
    IDL::traits<CSL_Test::CCM_Sender>::weak_ref_type,
    Sender_exec_i > ContextSwitch;

  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status_sender facet
  class connector_status_sender_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_sender_exec_i (
        IDL::traits<CSL_Test::CCM_Sender_Context>::ref_type context,
        IDL::traits<CSL_Test::CCM_Sender>::weak_ref_type component_executor,
        atomic_thread_id &on_inconsistent_topic_thread_id,
        atomic_thread_id &on_requested_incompatible_qos_thread_id,
        atomic_thread_id &on_sample_rejected_thread_id,
        atomic_thread_id &on_offered_deadline_missed_thread_id,
        atomic_thread_id &on_offered_incompatible_qos_thread_id,
        atomic_thread_id &on_publication_matched_thread_id,
        atomic_thread_id &on_subscription_matched_thread_id,
        atomic_thread_id &on_liveliness_changed_thread_id,
        atomic_thread_id &on_liveliness_lost_thread_id,
        atomic_thread_id &on_reliable_reader_activity_changed_thread_id,
        atomic_thread_id &on_reliable_writer_cache_changed_thread_id,
        int32_t &offered_incompatible_total_count_,
        int32_t &inconsistent_topic_total_count_);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[ctor]

    /// Destructor
    ~connector_status_sender_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::CSL_Test::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_members]
    IDL::traits<CSL_Test::CCM_Sender>::weak_ref_type component_executor_;
    bool started_ { false };

    atomic_thread_id &on_inconsistent_topic_thread_id_;
    atomic_thread_id &on_requested_incompatible_qos_thread_id_;
    atomic_thread_id &on_sample_rejected_thread_id_;
    atomic_thread_id &on_offered_deadline_missed_thread_id_;
    atomic_thread_id &on_offered_incompatible_qos_thread_id_;
    atomic_thread_id &on_publication_matched_thread_id_;
    atomic_thread_id &on_subscription_matched_thread_id_;
    atomic_thread_id &on_liveliness_changed_thread_id_;
    atomic_thread_id &on_liveliness_lost_thread_id_;
    atomic_thread_id &on_reliable_reader_activity_changed_thread_id_;
    atomic_thread_id &on_reliable_writer_cache_changed_thread_id_;
    int32_t &offered_incompatible_total_count_;
    int32_t &inconsistent_topic_total_count_;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::connector_status_sender_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits<::CSL_Test::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status_sender facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type get_connector_status_sender () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute csl_assignment
    std::string csl_assignment () override;
    void csl_assignment (const std::string& csl_assignment) override;

    /// Attribute samples_to_write
    uint32_t samples_to_write () override;
    void samples_to_write (uint32_t samples_to_write) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[user_public_ops]
    void start_publishing ();
    void tick ();
    void notify ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::CSL_Test::CCM_Sender_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of csl_assignment attribute
    std::string csl_assignment_{};
    /// Class member storing value of samples_to_write attribute
    uint32_t samples_to_write_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type connector_status_sender_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[user_members]
    atomic_thread_id on_inconsistent_topic_thread_id_ {};
    atomic_thread_id on_requested_incompatible_qos_thread_id_ {};
    atomic_thread_id on_sample_rejected_thread_id_ {};
    atomic_thread_id on_offered_deadline_missed_thread_id_ {};
    atomic_thread_id on_offered_incompatible_qos_thread_id_ {};
    // on_unexpected_status callbacks
    atomic_thread_id on_publication_matched_thread_id_ {};
    atomic_thread_id on_subscription_matched_thread_id_ {};
    atomic_thread_id on_liveliness_changed_thread_id_ {};
    atomic_thread_id on_liveliness_lost_thread_id_ {};
    atomic_thread_id on_reliable_reader_activity_changed_thread_id_ {};
    atomic_thread_id on_reliable_writer_cache_changed_thread_id_ {};

    int32_t offered_incompatible_total_count_ {};
    int32_t inconsistent_topic_total_count_ {};

    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    uint32_t written_ {};

    typedef std::vector<CommonTestMessage> samples_table;
    samples_table samples_;

    ASSIGNMENT assignment_ { ASSIGNMENT::ASSIGNMENT_UNKNOWN };
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl::Sender_exec_i[user_private_ops]
    void check_unexpected_status ();
    void check_on_sample_rejected ();
    void check_on_inconsistent_topic ();
    void check_on_incompatible_qos ();
    void check_deadline_missed ();

    void stop ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl::Sender_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[user_namespace_end_decl]

} // namespace CSL_Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Sender_Impl[factory]
extern "C" CONNECTOR_STATUS_SENDER_EXEC_Export  void
create_CSL_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_sender_impl.h[Footer]

#endif /* __RIDL_CSL_SENDER_EXEC_H_JHFFIGDD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
