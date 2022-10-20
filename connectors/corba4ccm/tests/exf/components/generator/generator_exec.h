// -*- C++ -*-
/*
 * @file    generator_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_GENERATOR_EXEC_H_HIHBBBCD_INCLUDED__
#define __RIDL_GENERATOR_EXEC_H_HIHBBBCD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : generator_impl.h[Header]

#pragma once

#include "generatorEC.h"

#include /**/ "exftest_generator_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : generator_impl.h[user_includes]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : generator_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : generator_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : generator_impl.h[user_global_decl]

/// Namespace for implementation of App::Generator component
namespace App_Generator_Impl
{
  /// Forward declarations
  class Generator_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Generator_exec_i
  class Generator_exec_i final
    : public virtual IDL::traits< ::App::CCM_Generator>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[ctor]
    /// Constructor
    Generator_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[ctor]
    /// Destructor
    ~Generator_exec_i () override;

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute location
    std::string location () override;
    void location (const std::string& location) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::App::CCM_Generator_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of location attribute
    std::string location_{};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Handler>::ref_type th_gen_;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl::Generator_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl::Generator_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Generator_exec_i(const Generator_exec_i&) = delete;
    Generator_exec_i(Generator_exec_i&&) = delete;
    Generator_exec_i& operator=(const Generator_exec_i&) = delete;
    Generator_exec_i& operator=(Generator_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[user_namespace_end_decl]

} // namespace App_Generator_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Generator_Impl[factory]
extern "C" EXFTEST_GENERATOR_EXEC_Export  void
create_App_Generator_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : App_Generator_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : generator_impl.h[Footer]

#endif /* __RIDL_GENERATOR_EXEC_H_HIHBBBCD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
