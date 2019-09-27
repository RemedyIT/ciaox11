// -*- C++ -*-
/**
 * @file    attr_only_comp_exec.h
 * @author  Marijke Hengstmengel
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_ATTR_ONLY_COMP_EXEC_H_EHCDGHCB_INCLUDED__
#define __RIDL_ATTR_ONLY_COMP_EXEC_H_EHCDGHCB_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : attr_only_comp_impl.h[Header]

#pragma once

#include "attr_only_compEC.h"

#include /**/ "attr_only_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : attr_only_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : attr_only_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : attr_only_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : attr_only_comp_impl.h[user_global_decl]

/// Namespace for implementation of AttrComp component
namespace AttrComp_Impl
{
  /// Forward declarations
  class AttrComp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : AttrComp_exec_i
  class AttrComp_exec_i final
    : public virtual IDL::traits< CCM_AttrComp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[ctor]
    /// Constructor
    AttrComp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[ctor]
    /// Destructor
    virtual ~AttrComp_exec_i ();

    /** @name Supported attributes. */
    //@{

    /// Attribute TestBar

    virtual
    ::Foo::Bar
    TestBar () override;

    virtual
    void
    TestBar (
        const ::Foo::Bar& TestBar) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_AttrComp_Context >::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of TestBar attribute
    ::Foo::Bar TestBar_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl::AttrComp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl::AttrComp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    AttrComp_exec_i(const AttrComp_exec_i&) = delete;
    AttrComp_exec_i(AttrComp_exec_i&&) = delete;
    AttrComp_exec_i& operator=(const AttrComp_exec_i&) = delete;
    AttrComp_exec_i& operator=(AttrComp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[user_namespace_end_decl]

} // namespace AttrComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AttrComp_Impl[factory]
extern "C" ATTR_ONLY_COMP_EXEC_Export  void
create_AttrComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : AttrComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : attr_only_comp_impl.h[Footer]

#endif /* __RIDL_ATTR_ONLY_COMP_EXEC_H_EHCDGHCB_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
