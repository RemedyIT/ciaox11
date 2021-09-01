// -*- C++ -*-
/**
 * @file    psl_deadline_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the deadline missed callback on
 *          the Port Status Listener.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_PSL_DEADLINE_RECEIVER_EXEC_H_CHCAJJBA_INCLUDED__
#define __RIDL_PSL_DEADLINE_RECEIVER_EXEC_H_CHCAJJBA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psl_deadline_receiver_impl.h[Header]

#pragma once

#include "psl_deadline_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_receiver_impl.h[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : psl_deadline_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : psl_deadline_receiver_impl.h[user_global_decl]

/// Namespace for implementation of PSL_DeadlineTest::Receiver component
namespace PSL_DeadlineTest_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
      IDL::traits<PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context,
      std::atomic_ushort &nr_invocations,
      atomic_thread_id &thread_id);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[ctor]

    /// Destructor
    ~info_get_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_members]
    std::atomic_ushort &nr_invocations_;
    atomic_thread_id   &thread_id_;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_data_listener facet
  class info_out_data_listener_exec_i final
    : public IDL::traits< ::CommonTestConnector::CCM_Listener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_data_listener_exec_i (
      IDL::traits<PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[ctor]

    /// Destructor
    ~info_out_data_listener_exec_i () override;

    /** @name Operations from ::CommonTestConnector::CCM_Listener */
    //@{

    void
    on_one_data (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_data (
        const ::CommonTestMessageSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_status facet
  class info_out_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_status_exec_i (
      IDL::traits<PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context,
        std::atomic_ushort &nr_invocations,
        atomic_thread_id &thread_id);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[ctor]

    /// Destructor
    ~info_out_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_members]
    std::atomic_ushort &nr_invocations_;
    atomic_thread_id &thread_id_;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::info_out_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::PSL_DeadlineTest::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_status () override;
    /// Factory method and getter for the info_out_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type get_info_out_data_listener () override;
    /// Factory method and getter for the info_out_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_out_status () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::PSL_DeadlineTest::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_status_;
    IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type info_out_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_out_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    std::atomic_ushort    nr_invocations_get_port_ {};
    atomic_thread_id thread_id_get_port_ {};
    std::atomic_ushort    nr_invocations_listen_port_ {};
    atomic_thread_id thread_id_listen_port_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[user_namespace_end_decl]

} // namespace PSL_DeadlineTest_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_PSL_DeadlineTest_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_receiver_impl.h[Footer]

#endif /* __RIDL_PSL_DEADLINE_RECEIVER_EXEC_H_CHCAJJBA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
