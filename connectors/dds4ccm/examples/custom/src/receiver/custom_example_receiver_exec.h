// -*- C++ -*-
/**
 * @file    custom_example_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the IDL example.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_CUSTOM_EXAMPLE_RECEIVER_EXEC_H_IAIGDCCD_INCLUDED__
#define __RIDL_CUSTOM_EXAMPLE_RECEIVER_EXEC_H_IAIGDCCD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : custom_example_receiver_impl.h[Header]

#pragma once

#include "custom_example_receiverEC.h"

#include /**/ "custom_example_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_receiver_impl.h[user_includes]
#include <atomic>
//@@{__RIDL_REGEN_MARKER__} - END : custom_example_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : custom_example_receiver_impl.h[user_global_decl]

/// Namespace for implementation of Example::BasicSubscriber_comp component
namespace Example_BasicSubscriber_comp_Impl
{
  /// Forward declarations
  class BasicSubscriber_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[user_namespace_decl]


  /// Executor implementation class for CA1DataSub_data_listener facet
  class CA1DataSub_data_listener_exec_i final
    : public IDL::traits<::Example::CA1_conn::CCM_Listener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    CA1DataSub_data_listener_exec_i (
        IDL::traits<Example::CCM_BasicSubscriber_comp_Context>::ref_type context,
        std::atomic_ulong &samples_received);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[ctor]

    /// Destructor
    ~CA1DataSub_data_listener_exec_i () override;

    /** @name Operations from ::Example::CA1_conn::CCM_Listener */
    //@{

    void
    on_one_data (
        const ::Example::CA1_msg& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_data (
        const ::Example::CA1_msgSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Example::CCM_BasicSubscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_members]
    std::atomic_ulong &samples_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_private_ops]
    void
    check_sample (const Example::CA1_msg &msg);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for CA1DataSub_status facet
  class CA1DataSub_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    CA1DataSub_status_exec_i (
        IDL::traits<Example::CCM_BasicSubscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[ctor]

    /// Destructor
    ~CA1DataSub_status_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Example::CCM_BasicSubscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : BasicSubscriber_comp_exec_i
  class BasicSubscriber_comp_exec_i final
    : public virtual IDL::traits<::Example::CCM_BasicSubscriber_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ctor]
    /// Constructor
    BasicSubscriber_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ctor]
    /// Destructor
    ~BasicSubscriber_comp_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the CA1DataSub_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::Example::CA1_conn::CCM_Listener>::ref_type get_CA1DataSub_data_listener () override;
    /// Factory method and getter for the CA1DataSub_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_CA1DataSub_status () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute count
    uint32_t count () override;
    void count (uint32_t count) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Example::CCM_BasicSubscriber_comp_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of count attribute
    uint32_t count_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::Example::CA1_conn::CCM_Listener>::ref_type CA1DataSub_data_listener_;
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type CA1DataSub_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_members]
    std::atomic_ulong samples_received_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    BasicSubscriber_comp_exec_i(const BasicSubscriber_comp_exec_i&) = delete;
    BasicSubscriber_comp_exec_i(BasicSubscriber_comp_exec_i&&) = delete;
    BasicSubscriber_comp_exec_i& operator=(const BasicSubscriber_comp_exec_i&) = delete;
    BasicSubscriber_comp_exec_i& operator=(BasicSubscriber_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[user_namespace_end_decl]

} // namespace Example_BasicSubscriber_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[factory]
extern "C" CUSTOM_EXAMPLE_RECEIVER_EXEC_Export  void
create_Example_BasicSubscriber_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_receiver_impl.h[Footer]

#endif /* __RIDL_CUSTOM_EXAMPLE_RECEIVER_EXEC_H_IGHGBAIE_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
