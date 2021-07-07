// -*- C++ -*-
/**
 * @file    psdd_sender_exec.h
 * @author  Martin Corino
 *
 * @brief   PSDD Sender executor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_PSDD_SENDER_EXEC_H_FEIGDFGD_INCLUDED__
#define __RIDL_PSDD_SENDER_EXEC_H_FEIGDFGD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psdd_sender_impl.h[Header]

#pragma once

#include "psdd_senderEC.h"

#include /**/ "psdd_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_sender_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : psdd_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : psdd_sender_impl.h[user_global_decl]

/// Namespace for implementation of Test::Sender component
namespace Test_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::Test::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute count

    uint32_t
    count () override;

    void
    count (uint32_t count) override;

    /// Attribute delay

    uint32_t
    delay () override;

    void
    delay (uint32_t delay) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_public_ops]
    void start_publishing ();
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Test::CCM_Sender_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of count attribute
    uint32_t count_{};
    /// Class member storing value of delay attribute
    uint32_t delay_{};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_topic_;
    uint32_t topic_counter_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_private_ops]
    void stop_publishing ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_end_decl]

} // namespace Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[factory]
extern "C" PSDD_SENDER_EXEC_Export  void
create_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_sender_impl.h[Footer]

#endif /* __RIDL_PSDD_SENDER_EXEC_H_FEIGDFGD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
