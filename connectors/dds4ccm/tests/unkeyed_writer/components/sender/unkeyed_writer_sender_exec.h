// -*- C++ -*-
/**
 * @file    unkeyed_writer_sender_exec.h
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the unkeyed Writer test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef __RIDL_UNKEYED_WRITER_SENDER_EXEC_H_BGEFDHHB_INCLUDED__
#define __RIDL_UNKEYED_WRITER_SENDER_EXEC_H_BGEFDHHB_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : unkeyed_writer_sender_impl.h[Header]

#pragma once

#include "unkeyed_writer_senderEC.h"

#include /**/ "unkeyed_writer_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : unkeyed_writer_sender_impl.h[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
#include <mutex>
#include <map>
//@@{__RIDL_REGEN_MARKER__} - END : unkeyed_writer_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : unkeyed_writer_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : unkeyed_writer_sender_impl.h[user_global_decl]

/// Namespace for implementation of UnkeyedWriterTest::Sender component
namespace UnkeyedWriterTest_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[user_namespace_decl]
  enum class WRITER_ASSIGNMENT : uint32_t
  {
    WRITE_NONE,
    WRITE_UNKEYED,
    WRITE_MULTI,
    TEST_EXCEPTION
  };

  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status facet
  class connector_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_exec_i (
      IDL::traits<UnkeyedWriterTest::CCM_Sender_Context>::ref_type context,
      IDL::traits<UnkeyedWriterTest::CCM_Sender>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[ctor]

    /// Destructor
    virtual ~connector_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::UnkeyedWriterTest::CCM_Sender_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_members]
     IDL::traits<UnkeyedWriterTest::CCM_Sender>::weak_ref_type component_executor_;
     bool started_ { false };
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::connector_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::UnkeyedWriterTest::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    virtual ~Sender_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type get_connector_status () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute rate

    virtual
    uint16_t
    rate () override;

    virtual
    void
    rate (
        uint16_t rate) override;

    /// Attribute iterations

    virtual
    uint16_t
    iterations () override;

    virtual
    void
    iterations (
        uint16_t iterations) override;

    /// Attribute keys

    virtual
    uint16_t
    keys () override;

    virtual
    void
    keys (
        uint16_t keys) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_public_ops]
    void tick ();
    void start_publishing ();
    WRITER_ASSIGNMENT assignment_ { WRITER_ASSIGNMENT::WRITE_UNKEYED };
    void write_unkeyed ();
    void write_many ();
    void test_exception ();
    void check_status ();
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::UnkeyedWriterTest::CCM_Sender_Context >::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of rate attribute
    uint16_t rate_ {};
    /// Class member storing value of iterations attribute
    uint16_t iterations_ {};
    /// Class member storing value of keys attribute
    uint16_t keys_ {};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type connector_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_activate_;
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s;
    bool already_publishing_ {};



    std::mutex mutex_ {};
    typedef std::map<std::string, UnkeyedWriterTest::UnkeyedWriterMessage> Writer_Table;
    Writer_Table ktests_ {};

    Writer_Table::iterator last_key_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_private_ops]
    void start ();

    void reset_iterations ();
    void start_new_assignment (
        WRITER_ASSIGNMENT assignment);

    //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl::Sender_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[user_namespace_end_decl]

} // namespace UnkeyedWriterTest_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UnkeyedWriterTest_Sender_Impl[factory]
extern "C" UNKEYED_WRITER_SENDER_EXEC_Export  void
create_UnkeyedWriterTest_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : UnkeyedWriterTest_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : unkeyed_writer_sender_impl.h[Footer]

#endif // __RIDL_UNKEYED_WRITER_SENDER_EXEC_H_BGEFDHHB_INCLUDED__


// Your comments here.
// -*- END -*-
