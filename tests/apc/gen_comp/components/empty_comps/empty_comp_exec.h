// -*- C++ -*-
/**
 * @file    empty_comp_exec.h
 * @author  Marijke Hengstmengel
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_EMPTY_COMP_EXEC_H_JCFHAACI_INCLUDED__
#define __RIDL_EMPTY_COMP_EXEC_H_JCFHAACI_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : empty_comp_impl.h[Header]

#pragma once

#include "empty_compEC.h"

#include /**/ "empty_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : empty_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : empty_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : empty_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : empty_comp_impl.h[user_global_decl]

/// Namespace for implementation of EmptyComp component
namespace EmptyComp_Impl
{
  /// Forward declarations
  class EmptyComp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : EmptyComp_exec_i
  class EmptyComp_exec_i final
    : public virtual IDL::traits< CCM_EmptyComp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[ctor]
    /// Constructor
    EmptyComp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[ctor]
    /// Destructor
    virtual ~EmptyComp_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_EmptyComp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl::EmptyComp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl::EmptyComp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    EmptyComp_exec_i(const EmptyComp_exec_i&) = delete;
    EmptyComp_exec_i(EmptyComp_exec_i&&) = delete;
    EmptyComp_exec_i& operator=(const EmptyComp_exec_i&) = delete;
    EmptyComp_exec_i& operator=(EmptyComp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[user_namespace_end_decl]

} // namespace EmptyComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EmptyComp_Impl[factory]
extern "C" EMPTY_COMP_EXEC_Export  void
create_EmptyComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : EmptyComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : empty_comp_impl.h[Footer]

#endif /* __RIDL_EMPTY_COMP_EXEC_H_JCFHAACI_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
