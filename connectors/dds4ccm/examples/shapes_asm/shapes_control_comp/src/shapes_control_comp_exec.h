// -*- C++ -*-
/**
 * @file    shapes_control_comp_exec.h
 * @author  Johnny Willemsen
 *
 * @brief   Shapes control component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_SHAPES_CONTROL_COMP_EXEC_H_GBECDHBA_INCLUDED__
#define __RIDL_SHAPES_CONTROL_COMP_EXEC_H_GBECDHBA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : shapes_control_comp_impl.h[Header]

#pragma once

#include "shapes_control_compEC.h"

#include /**/ "shapes_control_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_control_comp_impl.h[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : shapes_control_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_control_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : shapes_control_comp_impl.h[user_global_decl]

/// Namespace for implementation of Shapes::Control_comp component
namespace Shapes_Control_comp_Impl
{
  /// Forward declarations
  class Control_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Control_comp_exec_i
  class Control_comp_exec_i final
    : public virtual IDL::traits<::Shapes::CCM_Control_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[ctor]
    /// Constructor
    Control_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[ctor]
    /// Destructor
    ~Control_comp_exec_i () override;

    /** @name Component port operations. */
    //@{

    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute rate
    uint32_t rate () override;
    void rate (uint32_t rate) override;

    /// Attribute max_x
    uint16_t max_x () override;
    void max_x (uint16_t max_x) override;

    /// Attribute max_y
    uint16_t max_y () override;
    void max_y (uint16_t max_y) override;

    /// Attribute max_size
    uint16_t max_size () override;
    void max_size (uint16_t max_size) override;

    /// Attribute resize_shape
    bool resize_shape () override;
    void resize_shape (bool resize_shape) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[user_public_ops]
    void tick ();
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Shapes::CCM_Control_comp_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of rate attribute
    uint32_t rate_{};
    /// Class member storing value of max_x attribute
    uint16_t max_x_{};
    /// Class member storing value of max_y attribute
    uint16_t max_y_{};
    /// Class member storing value of max_size attribute
    uint16_t max_size_{};
    /// Class member storing value of resize_shape attribute
    bool resize_shape_{};
    //@}

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[user_members]
    bool x_increasing_ { true };
    bool y_increasing_ { true };
    bool size_increasing_ { false };

    uint16_t current_size_ {};
    uint16_t current_x_ {};
    uint16_t current_y_ {};

    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;

    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[user_private_ops]
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Control_comp_exec_i(const Control_comp_exec_i&) = delete;
    Control_comp_exec_i(Control_comp_exec_i&&) = delete;
    Control_comp_exec_i& operator=(const Control_comp_exec_i&) = delete;
    Control_comp_exec_i& operator=(Control_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[user_namespace_end_decl]

} // namespace Shapes_Control_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[factory]
extern "C" SHAPES_CONTROL_COMP_EXEC_Export  void
create_Shapes_Control_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_control_comp_impl.h[Footer]

#endif /* __RIDL_SHAPES_CONTROL_COMP_EXEC_H_GBECDHBA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
