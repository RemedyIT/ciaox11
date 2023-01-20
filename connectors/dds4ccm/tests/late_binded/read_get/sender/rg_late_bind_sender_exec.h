// -*- C++ -*-
/**
 * @file    rg_late_bind_sender_exec.h
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the late binded topic test.
 *
 * Writes samples to DDS and notifies the receiver via the ReaderStarter interface
 * that the samples were written.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_RG_LATE_BIND_SENDER_EXEC_H_BGHFFCFJ_INCLUDED__
#define __RIDL_RG_LATE_BIND_SENDER_EXEC_H_BGHFFCFJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : rg_late_bind_sender_impl.h[Header]

#pragma once

#include "rg_late_bind_senderEC.h"

#include /**/ "sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_sender_impl.h[user_includes]
#include "dds4ccm/tests/common/ticker_t.h"
#include "commonSEEC.h"
//@@{__RIDL_REGEN_MARKER__} - END : rg_late_bind_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : rg_late_bind_sender_impl.h[user_global_decl]

/// Namespace for implementation of RG_LateBinding::Sender component
namespace RG_LateBinding_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[user_namespace_decl]
  typedef DDS4CCM_TEST_UTILS::ContextSwitch<
    IDL::traits<RG_LateBinding::CCM_Sender>::weak_ref_type,
    Sender_exec_i > ContextSwitch;
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for start_writing facet
  class start_writing_exec_i final
    : public IDL::traits< CCM_WriterStarter>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    start_writing_exec_i (
      IDL::traits<RG_LateBinding::CCM_Sender_Context>::ref_type context,
      IDL::traits<RG_LateBinding::CCM_Sender>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[ctor]

    /// Destructor
    ~start_writing_exec_i () override;

    /** @name Operations from CCM_WriterStarter */
    //@{

    void
    start_write () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::RG_LateBinding::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_members]
    IDL::traits<RG_LateBinding::CCM_Sender>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits<::RG_LateBinding::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the start_writing facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< CCM_WriterStarter>::ref_type get_start_writing () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute iterations
    uint16_t iterations () override;
    void iterations (uint16_t iterations) override;

    /// Attribute keys
    uint16_t keys () override;
    void keys (uint16_t keys) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[user_public_ops]
    void notify ();
    void switch_context ();
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::RG_LateBinding::CCM_Sender_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of iterations attribute
    uint16_t iterations_{};
    /// Class member storing value of keys attribute
    uint16_t keys_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< CCM_WriterStarter>::ref_type start_writing_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    bool first_run_ { true };
    // Cached version of the topic_name for logging purposes
    std::string topic_name_;
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[user_private_ops]
    void reset_topic_name (std::string const &topic_name);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[user_namespace_end_decl]

} // namespace RG_LateBinding_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[factory]
extern "C" SENDER_EXEC_Export  void
create_RG_LateBinding_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_sender_impl.h[Footer]

#endif /* __RIDL_RG_LATE_BIND_SENDER_EXEC_H_BGHFFCFJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
