// -*- C++ -*-
/**
 * @file    rg_late_bind_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the late binded topic test.
 *
 * The topic name is set when the start_read method on the ReaderStarter facet
 * gets invoked.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_RG_LATE_BIND_RECEIVER_EXEC_H_GIHFHDAA_INCLUDED__
#define __RIDL_RG_LATE_BIND_RECEIVER_EXEC_H_GIHFHDAA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : rg_late_bind_receiver_impl.h[Header]

#pragma once

#include "rg_late_bind_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_receiver_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : rg_late_bind_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : rg_late_bind_receiver_impl.h[user_global_decl]

/// Namespace for implementation of RG_LateBinding::Receiver component
namespace RG_LateBinding_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
      IDL::traits<RG_LateBinding::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[ctor]

    /// Destructor
    ~info_get_status_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::RG_LateBinding::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for start_reading facet
  class start_reading_exec_i final
    : public IDL::traits<CCM_ReaderStarter>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    start_reading_exec_i (
      IDL::traits<RG_LateBinding::CCM_Receiver_Context>::ref_type context,
      IDL::traits<RG_LateBinding::CCM_Receiver>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[ctor]

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::RG_LateBinding::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_members]
    IDL::traits<RG_LateBinding::CCM_Receiver>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits<::RG_LateBinding::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_status () override;
    /// Factory method and getter for the start_reading facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<CCM_ReaderStarter>::ref_type get_start_reading () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void tick ();
    void start ();
    void set_reader_properties (uint16_t keys, uint16_t iterations);

    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::RG_LateBinding::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_status_;
    IDL::traits<CCM_ReaderStarter>::ref_type start_reading_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    uint16_t iterations_ {};
    uint16_t keys_ {};
    bool first_run_ {true};
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_private_ops]

    CommonTestMessageSeq::size_type samples_read_ {};

    void set_topic_name ();

    void start_read ();

    void start_reading ();
    void start_getting ();
    void test_exception ();

    void inform_sender ();

    void check_samples (
      const std::string &test,
      const CommonTestMessageSeq &samples,
      uint16_t expected);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[user_namespace_end_decl]

} // namespace RG_LateBinding_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_RG_LateBinding_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_receiver_impl.h[Footer]

#endif /* __RIDL_RG_LATE_BIND_RECEIVER_EXEC_H_GIHFHDAA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
