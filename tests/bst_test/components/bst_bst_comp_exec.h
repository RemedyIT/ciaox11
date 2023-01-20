// -*- C++ -*-
/**
 * @file    bst_bst_comp_exec.h
 * @author  Johnny Willemsen
 *
 * @brief   CIAOX11 bounded attribute test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_BST_BST_COMP_EXEC_H_ICBBACDF_INCLUDED__
#define __RIDL_BST_BST_COMP_EXEC_H_ICBBACDF_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : bst_bst_comp_impl.h[Header]

#pragma once

#include "bst_bst_compEC.h"

#include /**/ "bst_bst_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : bst_bst_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : bst_bst_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : bst_bst_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : bst_bst_comp_impl.h[user_global_decl]

/// Namespace for implementation of BST::BST_comp component
namespace BST_BST_comp_Impl
{
  /// Forward declarations
  class BST_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : BST_comp_exec_i
  class BST_comp_exec_i final
    : public virtual IDL::traits<::BST::CCM_BST_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[ctor]
    /// Constructor
    BST_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[ctor]
    /// Destructor
    ~BST_comp_exec_i () override;

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute MyBoundedString
    ::BST::MyBoundedStringType MyBoundedString () override;
    void MyBoundedString (const ::BST::MyBoundedStringType& MyBoundedString) override;

    /// Attribute MyUnboundedString
    ::BST::MyStringTypedef MyUnboundedString () override;
    void MyUnboundedString (const ::BST::MyStringTypedef& MyUnboundedString) override;

    /// Attribute MyStruct
    ::BST::MyStructType MyStruct () override;
    void MyStruct (const ::BST::MyStructType& MyStruct) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::BST::CCM_BST_comp_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of MyBoundedString attribute
    ::BST::MyBoundedStringType MyBoundedString_{};
    /// Class member storing value of MyUnboundedString attribute
    ::BST::MyStringTypedef MyUnboundedString_{};
    /// Class member storing value of MyStruct attribute
    ::BST::MyStructType MyStruct_{};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[user_members]
    bool MyBoundString_set_ {};
    bool MyUnboundedString_set_ {};
    bool MyStruct_set_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    BST_comp_exec_i(const BST_comp_exec_i&) = delete;
    BST_comp_exec_i(BST_comp_exec_i&&) = delete;
    BST_comp_exec_i& operator=(const BST_comp_exec_i&) = delete;
    BST_comp_exec_i& operator=(BST_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[user_namespace_end_decl]

} // namespace BST_BST_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[factory]
extern "C" BST_BST_COMP_EXEC_Export  void
create_BST_BST_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : bst_bst_comp_impl.h[Footer]

#endif /* __RIDL_BST_BST_COMP_EXEC_H_ICBBACDF_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
