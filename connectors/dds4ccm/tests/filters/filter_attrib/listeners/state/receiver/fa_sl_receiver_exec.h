// -*- C++ -*-
/**
 * @file    fa_sl_receiver_exec.h
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_FA_SL_RECEIVER_EXEC_H_HFHAJDJA_INCLUDED__
#define __RIDL_FA_SL_RECEIVER_EXEC_H_HFHAJDJA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : fa_sl_receiver_impl.h[Header]

#pragma once

#include "fa_sl_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : fa_sl_receiver_impl.h[user_includes]
#include <atomic>
//@@{__RIDL_REGEN_MARKER__} - END : fa_sl_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : fa_sl_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : fa_sl_receiver_impl.h[user_global_decl]

/// Namespace for implementation of FA_State_Listen_Test::Receiver component
namespace FA_State_Listen_Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for listen_port_1_data_listener facet
  class listen_port_1_data_listener_exec_i final
    : public IDL::traits<::CommonTestConnector::CCM_StateListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    listen_port_1_data_listener_exec_i (
        IDL::traits< FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context,
        std::atomic_ullong &created,
        std::atomic_ullong &updated,
        std::atomic_ullong &deleted);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[ctor]

    /// Destructor
    ~listen_port_1_data_listener_exec_i () override;

    /** @name Operations from ::CommonTestConnector::CCM_StateListener */
    //@{

    void
    on_creation (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_one_update (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_updates (
        const ::CommonTestMessageSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;

    void
    on_deletion (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_members]
    std::atomic_ullong &created_;
    std::atomic_ullong &updated_;
    std::atomic_ullong &deleted_;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_private_ops]
    // Your code here.
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for listen_port_1_status facet
  class listen_port_1_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    listen_port_1_status_exec_i (
        IDL::traits< FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[ctor]

    /// Destructor
    ~listen_port_1_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    void
    on_requested_deadline_missed (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_sample_lost (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_1_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for listen_port_2_data_listener facet
  class listen_port_2_data_listener_exec_i final
    : public IDL::traits<::CommonTestConnector::CCM_StateListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    listen_port_2_data_listener_exec_i (
        IDL::traits< FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context,
        std::atomic_ullong &created_,
        std::atomic_ullong &updated_,
        std::atomic_ullong &deleted_);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[ctor]

    /// Destructor
    ~listen_port_2_data_listener_exec_i () override;

    /** @name Operations from ::CommonTestConnector::CCM_StateListener */
    //@{

    void
    on_creation (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_one_update (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_updates (
        const ::CommonTestMessageSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;

    void
    on_deletion (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_members]
    std::atomic_ullong &created_;
    std::atomic_ullong &updated_;
    std::atomic_ullong &deleted_;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for listen_port_2_status facet
  class listen_port_2_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    listen_port_2_status_exec_i (
        IDL::traits< FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[ctor]

    /// Destructor
    ~listen_port_2_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    void
    on_requested_deadline_missed (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_sample_lost (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::listen_port_2_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits<::FA_State_Listen_Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the listen_port_1_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CommonTestConnector::CCM_StateListener>::ref_type get_listen_port_1_data_listener () override;
    /// Factory method and getter for the listen_port_1_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_listen_port_1_status () override;
    /// Factory method and getter for the listen_port_2_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CommonTestConnector::CCM_StateListener>::ref_type get_listen_port_2_data_listener () override;
    /// Factory method and getter for the listen_port_2_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_listen_port_2_status () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::FA_State_Listen_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::CommonTestConnector::CCM_StateListener>::ref_type listen_port_1_data_listener_;
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type listen_port_1_status_;
    IDL::traits<::CommonTestConnector::CCM_StateListener>::ref_type listen_port_2_data_listener_;
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type listen_port_2_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_members]
    std::atomic_ullong created_on_listener_1_ {};
    std::atomic_ullong created_on_listener_2_ {};

    std::atomic_ullong updated_on_listener_1_ {};
    std::atomic_ullong updated_on_listener_2_ {};

    std::atomic_ullong deleted_on_listener_1_ {};
    std::atomic_ullong deleted_on_listener_2_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    void
    test_internal_error (
      uint16_t listener_port,
      IDL::traits< CCM_DDS::ContentFilterSetting>::ref_type cft);
    void test_internal_errors ();

    void
    test_non_changeable (
      uint16_t listener_port,
      std::string const &current_query,
      std::string const &new_query,
      IDL::traits< CCM_DDS::DataListenerControl>::ref_type ldc);
    void test_non_changeables ();
    //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl[user_namespace_end_decl]

} // namespace FA_State_Listen_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_State_Listen_Test_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_FA_State_Listen_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : FA_State_Listen_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : fa_sl_receiver_impl.h[Footer]

#endif /* __RIDL_FA_SL_RECEIVER_EXEC_H_HFHAJDJA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
