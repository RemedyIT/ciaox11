// -*- C++ -*-
/**
 * @file    psl_deadline_sender_exec.h
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the deadline missed callback on
 *          the Port Status Listener.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef __RIDL_PSL_DEADLINE_SENDER_EXEC_H_BIIJHGEJ_INCLUDED__
#define __RIDL_PSL_DEADLINE_SENDER_EXEC_H_BIIJHGEJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psl_deadline_sender_impl.h[Header]

#pragma once

#include "psl_deadline_senderEC.h"

#include /**/ "sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_sender_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : psl_deadline_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : psl_deadline_sender_impl.h[user_global_decl]

/// Namespace for implementation of PSL_DeadlineTest::Sender component
namespace PSL_DeadlineTest_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[user_namespace_decl]
//  typedef DDS4CCM_TEST_UTILS::Ticker<
//    IDL::traits<PSL_DeadlineTest::CCM_Sender>::weak_ref_type,
//    Sender_exec_i > Ticker;
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::PSL_DeadlineTest::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    virtual ~Sender_exec_i ();

    /** @name Component port operations. */
    //@{

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_public_ops]
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::PSL_DeadlineTest::CCM_Sender_Context >::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_private_ops]
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl::Sender_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[user_namespace_end_decl]

} // namespace PSL_DeadlineTest_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_DeadlineTest_Sender_Impl[factory]
extern "C" SENDER_EXEC_Export  void
create_PSL_DeadlineTest_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : PSL_DeadlineTest_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_deadline_sender_impl.h[Footer]

#endif /* __RIDL_PSL_DEADLINE_SENDER_EXEC_H_BIIJHGEJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
