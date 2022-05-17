// -*- C++ -*-
/**
 * @file    psdd_receiver_exec.h
 * @author  Martin Corino
 *
 * @brief   PSDD Receiver executor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_PSDD_RECEIVER_EXEC_H_IHIIFJGA_INCLUDED__
#define __RIDL_PSDD_RECEIVER_EXEC_H_IHIIFJGA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psdd_receiver_impl.h[Header]

#pragma once

#include "psdd_receiverEC.h"

#include /**/ "psdd_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_receiver_impl.h[user_includes]
#include <atomic>
//@@{__RIDL_REGEN_MARKER__} - END : psdd_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : psdd_receiver_impl.h[user_global_decl]

/// Namespace for implementation of Test::Receiver component
namespace Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute filter
    bool filter () override;
    void filter (bool filter) override;

    /// Attribute count
    uint32_t count () override;
    void count (uint32_t count) override;

    /// Attribute delay
    uint32_t delay () override;
    void delay (uint32_t delay) override;

    /// Attribute interval
    uint32_t interval () override;
    void interval (uint32_t interval) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of filter attribute
    bool filter_{};
    /// Class member storing value of count attribute
    uint32_t count_{};
    /// Class member storing value of delay attribute
    uint32_t delay_{};
    /// Class member storing value of interval attribute
    uint32_t interval_{};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    std::atomic<uint32_t> topic_counter_ {0};
    std::atomic<bool> read_multiple_ {false};
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_end_decl]

} // namespace Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[factory]
extern "C" PSDD_RECEIVER_EXEC_Export  void
create_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_receiver_impl.h[Footer]

#endif /* __RIDL_PSDD_RECEIVER_EXEC_H_IHIIFJGA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
