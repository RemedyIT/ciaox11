// -*- C++ -*-
/**
 * @file    typename_component_exec.h
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_TYPENAME_COMPONENT_EXEC_H_GDHGHCAE_INCLUDED__
#define __RIDL_TYPENAME_COMPONENT_EXEC_H_GDHGHCAE_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : typename_component_impl.h[Header]

#pragma once

#include "typename_componentEC.h"

#include /**/ "typename_component_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : typename_component_impl.h[user_includes]
#include "typename_baseSEEC.h"
#include "typenamemodule_typenamemessageSEEC.h"
#include "typenamemodulemodule_typenamemessageSEEC.h"
#include "typenamemodulemodule2_typenamemessageSEEC.h"
//@@{__RIDL_REGEN_MARKER__} - END : typename_component_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : typename_component_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : typename_component_impl.h[user_global_decl]

/// Namespace for implementation of TypeNameComponent component
namespace TypeNameComponent_Impl
{
  /// Forward declarations
  class TypeNameComponent_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : TypeNameComponent_exec_i
  class TypeNameComponent_exec_i final
    : public virtual IDL::traits< CCM_TypeNameComponent>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[ctor]
    /// Constructor
    TypeNameComponent_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[ctor]
    /// Destructor
    virtual ~TypeNameComponent_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_TypeNameComponent_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_private_ops]
    void check_typename_global ();
    void check_typename_of_module ();
    void check_typename_of_module_in_module ();
    void check_typename_of_module_in_module_2 ();
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    TypeNameComponent_exec_i(const TypeNameComponent_exec_i&) = delete;
    TypeNameComponent_exec_i(TypeNameComponent_exec_i&&) = delete;
    TypeNameComponent_exec_i& operator=(const TypeNameComponent_exec_i&) = delete;
    TypeNameComponent_exec_i& operator=(TypeNameComponent_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[user_namespace_end_decl]

} // namespace TypeNameComponent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[factory]
extern "C" TYPENAME_COMPONENT_EXEC_Export  void
create_TypeNameComponent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : typename_component_impl.h[Footer]

#endif /* __RIDL_TYPENAME_COMPONENT_EXEC_H_GDHGHCAE_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
