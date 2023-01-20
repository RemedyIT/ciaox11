// -*- C++ -*-
/**
 * @file    fa_rg_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the query condition test which
 *          tests two different queries.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_FA_RG_RECEIVER_EXEC_H_IDDICFDA_INCLUDED__
#define __RIDL_FA_RG_RECEIVER_EXEC_H_IDDICFDA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : fa_rg_receiver_impl.h[Header]

#pragma once

#include "fa_rg_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : fa_rg_receiver_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : fa_rg_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : fa_rg_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : fa_rg_receiver_impl.h[user_global_decl]

/// Namespace for implementation of FA_Read_Get_Test::Receiver component
namespace FA_Read_Get_Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for get_port_status facet
  class get_port_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    get_port_status_exec_i (
        IDL::traits< FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[ctor]

    /// Destructor
    ~get_port_status_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::get_port_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for listen_port_data_listener facet
  class listen_port_data_listener_exec_i final
    : public IDL::traits<::CommonTestConnector::CCM_Listener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    listen_port_data_listener_exec_i (
        IDL::traits< FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[ctor]

    /// Destructor
    ~listen_port_data_listener_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for listen_port_status facet
  class listen_port_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    listen_port_status_exec_i (
        IDL::traits< FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[ctor]

    /// Destructor
    ~listen_port_status_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::listen_port_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for start_reading facet
  class start_reading_exec_i final
    : public IDL::traits< CCM_ReaderStarter>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    start_reading_exec_i (
        IDL::traits< FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context,
        IDL::traits< FA_Read_Get_Test::CCM_Receiver>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[ctor]

    /// Destructor
    ~start_reading_exec_i () override;

    /** @name Operations from CCM_ReaderStarter */
    //@{

    void
    start_read () override;

    void
    start_new_run (
        uint16_t run) override;

    void
    set_reader_properties (
        uint16_t nr_keys,
        uint16_t nr_iterations) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_members]
    IDL::traits< FA_Read_Get_Test::CCM_Receiver>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::start_reading_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits<::FA_Read_Get_Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the get_port_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_get_port_status () override;
    /// Factory method and getter for the listen_port_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CommonTestConnector::CCM_Listener>::ref_type get_listen_port_data_listener () override;
    /// Factory method and getter for the listen_port_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_listen_port_status () override;
    /// Factory method and getter for the start_reading facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< CCM_ReaderStarter>::ref_type get_start_reading () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void tick ();
    void notify ();
    void run ();
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::FA_Read_Get_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_port_status_;
    IDL::traits<::CommonTestConnector::CCM_Listener>::ref_type listen_port_data_listener_;
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type listen_port_status_;
    IDL::traits< CCM_ReaderStarter>::ref_type start_reading_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    uint16_t run_ { 1 };

    uint32_t received_4_getter_ {};
    uint32_t received_4_reader_ {};
    bool last_get {};
    bool last_listen {};
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[user_namespace_end_decl]

} // namespace FA_Read_Get_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : FA_Read_Get_Test_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_FA_Read_Get_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : FA_Read_Get_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : fa_rg_receiver_impl.h[Footer]

#endif /* __RIDL_FA_RG_RECEIVER_EXEC_H_IDDICFDA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
