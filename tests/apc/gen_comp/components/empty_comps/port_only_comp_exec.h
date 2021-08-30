// -*- C++ -*-
/**
 * @file    port_only_comp_exec.h
 * @author  Marijke Hengstmengel
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_PORT_ONLY_COMP_EXEC_H_FJCAHFDD_INCLUDED__
#define __RIDL_PORT_ONLY_COMP_EXEC_H_FJCAHFDD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : port_only_comp_impl.h[Header]

#pragma once

#include "port_only_compEC.h"

#include /**/ "port_only_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : port_only_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : port_only_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : port_only_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : port_only_comp_impl.h[user_global_decl]

/// Namespace for implementation of PortComp component
namespace PortComp_Impl
{
  /// Forward declarations
  class PortComp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[user_namespace_decl]


  /// Executor implementation class for run_my_bar_foo_prov facet
  class run_my_bar_foo_prov_exec_i final
    : public IDL::traits< ::Foo::CCM_MyFoo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    run_my_bar_foo_prov_exec_i (
        IDL::traits< CCM_PortComp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[ctor]

    /// Destructor
    ~run_my_bar_foo_prov_exec_i () override;

    /** @name Operations from ::Foo::CCM_MyFoo */
    //@{

    void
    hello (
        int32_t& answer) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_PortComp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : PortComp_exec_i
  class PortComp_exec_i final
    : public virtual IDL::traits< CCM_PortComp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[ctor]
    /// Constructor
    PortComp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[ctor]
    /// Destructor
    ~PortComp_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the run_my_bar_foo_prov facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Foo::CCM_MyFoo>::ref_type get_run_my_bar_foo_prov () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_PortComp_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::Foo::CCM_MyFoo>::ref_type run_my_bar_foo_prov_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl::PortComp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl::PortComp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    PortComp_exec_i(const PortComp_exec_i&) = delete;
    PortComp_exec_i(PortComp_exec_i&&) = delete;
    PortComp_exec_i& operator=(const PortComp_exec_i&) = delete;
    PortComp_exec_i& operator=(PortComp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[user_namespace_end_decl]

} // namespace PortComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PortComp_Impl[factory]
extern "C" PORT_ONLY_COMP_EXEC_Export  void
create_PortComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : PortComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : port_only_comp_impl.h[Footer]

#endif /* __RIDL_PORT_ONLY_COMP_EXEC_H_FJCAHFDD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
