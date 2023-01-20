/**
 * @file    tt_test_exec.h
 * @author  Martin Corino
 *
 * @brief   Timed Trigger connector test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_TT_TEST_EXEC_H_FGACFICD_INCLUDED__
#define __RIDL_TT_TEST_EXEC_H_FGACFICD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : tt_test_impl.h[Header]

#pragma once

#include "tt_testEC.h"

#include /**/ "tt_test_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : tt_test_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : tt_test_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : tt_test_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : tt_test_impl.h[user_global_decl]

/// Namespace for implementation of Test::TT_Tester component
namespace Test_TT_Tester_Impl
{
  /// Forward declarations
  class TT_Tester_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : TT_Tester_exec_i
  class TT_Tester_exec_i final
    : public virtual IDL::traits<::Test::CCM_TT_Tester>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[ctor]
    /// Constructor
    TT_Tester_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[ctor]
    /// Destructor
    ~TT_Tester_exec_i () override;

    /** @name Component port operations. */
    //@{

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Test::CCM_TT_Tester_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_1;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_2;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_3;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_4;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_5;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl::TT_Tester_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl::TT_Tester_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    TT_Tester_exec_i(const TT_Tester_exec_i&) = delete;
    TT_Tester_exec_i(TT_Tester_exec_i&&) = delete;
    TT_Tester_exec_i& operator=(const TT_Tester_exec_i&) = delete;
    TT_Tester_exec_i& operator=(TT_Tester_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[user_namespace_end_decl]

} // namespace Test_TT_Tester_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_TT_Tester_Impl[factory]
extern "C" TT_TEST_EXEC_Export  void
create_Test_TT_Tester_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Test_TT_Tester_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : tt_test_impl.h[Footer]

#endif /* __RIDL_TT_TEST_EXEC_H_FGACFICD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
