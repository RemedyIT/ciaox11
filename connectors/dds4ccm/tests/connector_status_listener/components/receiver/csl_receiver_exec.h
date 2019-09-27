// -*- C++ -*-
/**
 * @file    csl_receiver_exec.h
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef __RIDL_CSL_RECEIVER_EXEC_H_BCBDACIC_INCLUDED__
#define __RIDL_CSL_RECEIVER_EXEC_H_BCBDACIC_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : csl_receiver_impl.h[Header]

#pragma once

#include "csl_receiverEC.h"

#include /**/ "connector_status_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_receiver_impl.h[user_includes]
#include "../csl_common.h"
//#include "dds4ccm/tests/common/ticker_t.h"
//@@{__RIDL_REGEN_MARKER__} - END : csl_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : csl_receiver_impl.h[user_global_decl]

/// Namespace for implementation of CSL_Test::Receiver component
namespace CSL_Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[user_namespace_decl]
//  typedef DDS4CCM_TEST_UTILS::Ticker<
//    IDL::traits<CSL_Test::CCM_Receiver>::weak_ref_type,
//    Receiver_exec_i > Ticker;
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
        IDL::traits< CSL_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[ctor]

    /// Destructor
    virtual ~info_get_status_exec_i ();

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    virtual
    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    virtual
    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::CSL_Test::CCM_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for connector_status_receiver facet
  class connector_status_receiver_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_receiver_exec_i (
        IDL::traits< CSL_Test::CCM_Receiver_Context>::ref_type context,
        std::atomic_ulong &on_sample_rejected_invoked,
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
        int32_t &requested_incompatible_total_count,
        int32_t &inconsistent_topic_total_count,
        int32_t &subscription_matched_total_count);
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[ctor]

    /// Destructor
    virtual ~connector_status_receiver_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::CSL_Test::CCM_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_members]
    std::atomic_ulong &on_sample_rejected_invoked_;
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
    int32_t &requested_incompatible_total_count_;
    int32_t &inconsistent_topic_total_count_;
    int32_t &subscription_matched_total_count_;
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::connector_status_receiver_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::CSL_Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type get_info_get_status () override;
    /// Factory method and getter for the connector_status_receiver facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type get_connector_status_receiver () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute csl_assignment

    virtual
    std::string
    csl_assignment () override;

    virtual
    void
    csl_assignment (
        const std::string& csl_assignment) override;

    /// Attribute samples_to_receive

    virtual
    uint32_t
    samples_to_receive () override;

    virtual
    void
    samples_to_receive (
        uint32_t samples_to_receive) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::CSL_Test::CCM_Receiver_Context >::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of csl_assignment attribute
    std::string csl_assignment_;
    /// Class member storing value of samples_to_receive attribute
    uint32_t samples_to_receive_ {};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type info_get_status_;
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type connector_status_receiver_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[user_members]
    std::atomic_ulong on_sample_rejected_invoked_ {0};
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

    int32_t requested_incompatible_total_count_ {};
    int32_t inconsistent_topic_total_count_ {};
    int32_t subscription_matched_total_count_ {};

    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    std::atomic_size_t received_ {};

    ASSIGNMENT assignment_ { ASSIGNMENT::ASSIGNMENT_UNKNOWN };

    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    void check_unexpected_status ();
    void check_on_sample_rejected ();
    void check_on_inconsistent_topic ();
    void check_on_incompatible_qos ();

    void stop ();
    //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Receiver_exec_i(const Receiver_exec_i&) = delete;
    Receiver_exec_i(Receiver_exec_i&&) = delete;
    Receiver_exec_i& operator=(const Receiver_exec_i&) = delete;
    Receiver_exec_i& operator=(Receiver_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[user_namespace_end_decl]

} // namespace CSL_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CSL_Test_Receiver_Impl[factory]
extern "C" CONNECTOR_STATUS_RECEIVER_EXEC_Export  void
create_CSL_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : CSL_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : csl_receiver_impl.h[Footer]

#endif /* __RIDL_CSL_RECEIVER_EXEC_H_BCBDACIC_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
