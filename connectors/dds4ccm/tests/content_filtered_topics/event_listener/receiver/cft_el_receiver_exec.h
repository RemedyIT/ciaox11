// -*- C++ -*-
/**
 * @file    cft_el_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation
 *
 * Receiver implementation for a ContentFiltered topic test. This receiver tests
 * the content filtered topic on a listener.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_CFT_EL_RECEIVER_EXEC_H_BHFGDIGI_INCLUDED__
#define __RIDL_CFT_EL_RECEIVER_EXEC_H_BHFGDIGI_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : cft_el_receiver_impl.h[Header]

#pragma once

#include "cft_el_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : cft_el_receiver_impl.h[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : cft_el_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : cft_el_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : cft_el_receiver_impl.h[user_global_decl]

/// Namespace for implementation of CFT_EL_Test::Receiver component
namespace CFT_EL_Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_listen_data_listener facet
  class info_listen_data_listener_exec_i final
    : public IDL::traits< ::CommonTestConnector::CCM_Listener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_listen_data_listener_exec_i (
      IDL::traits<CFT_EL_Test::CCM_Receiver_Context>::ref_type context,
      std::atomic_ulong &samples_received,
      atomic_thread_id &thread_id);
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_listen_data_listener_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::CFT_EL_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_members]
    std::atomic_ulong &samples_received_;
    atomic_thread_id &thread_id_;
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_listen_status facet
  class info_listen_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_listen_status_exec_i (
      IDL::traits<CFT_EL_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[ctor]

    /// Destructor
    virtual ~info_listen_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::CFT_EL_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::info_listen_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::CFT_EL_Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_listen_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type get_info_listen_data_listener () override;
    /// Factory method and getter for the info_listen_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_listen_status () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute keys

    uint16_t
    keys () override;

    void
    keys (uint16_t keys) override;

    /// Attribute iterations

    uint16_t
    iterations () override;

    void
    iterations (uint16_t iterations) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::CFT_EL_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of keys attribute
    uint16_t keys_{};
    /// Class member storing value of iterations attribute
    uint16_t iterations_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type info_listen_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_listen_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_members]
    uint32_t     samples_expected_ { 10 };
    std::atomic_ulong samples_received_ {};
    atomic_thread_id thread_id_listener_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[user_namespace_end_decl]

} // namespace CFT_EL_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CFT_EL_Test_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_CFT_EL_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : CFT_EL_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : cft_el_receiver_impl.h[Footer]

#endif /* __RIDL_CFT_EL_RECEIVER_EXEC_H_BHFGDIGI_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
