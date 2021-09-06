// -*- C++ -*-
/**
 * @file    shapes_sender_comp_exec.h
 * @author  Johnny Willemsen
 *
 * @brief   Shapes sender executor
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_SHAPES_SENDER_COMP_EXEC_H_IJHJIJGJ_INCLUDED__
#define __RIDL_SHAPES_SENDER_COMP_EXEC_H_IJHJIJGJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : shapes_sender_comp_impl.h[Header]

#pragma once

#include "shapes_sender_compEC.h"

#include /**/ "shapes_sender_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : shapes_sender_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : shapes_sender_comp_impl.h[user_global_decl]

/// Namespace for implementation of Shapes::Sender_comp component
namespace Shapes_Sender_comp_Impl
{
  /// Forward declarations
  class Sender_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_decl]


  /// Executor implementation class for control facet
  class control_exec_i final
    : public IDL::traits< ::Shapes::CCM_Control_obj>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    control_exec_i (
      IDL::traits<Shapes::CCM_Sender_comp_Context>::ref_type context,
      IDL::traits<Shapes::CCM_Sender_comp>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[ctor]

    /// Destructor
    ~control_exec_i () override;

    /** @name Operations from ::Shapes::CCM_Control_obj */
    //@{

    ::Shapes::ReturnStatus
    setSize (
        uint16_t size) override;

    ::Shapes::ReturnStatus
    setLocation (
        uint16_t x,
        uint16_t y) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Shapes::CCM_Sender_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[user_members]
    IDL::traits<Shapes::CCM_Sender_comp>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_comp_exec_i
  class Sender_comp_exec_i final
    : public virtual IDL::traits< ::Shapes::CCM_Sender_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]
    /// Constructor
    Sender_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]
    /// Destructor
    ~Sender_comp_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the control facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Shapes::CCM_Control_obj>::ref_type get_control () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
    ::Shapes::ReturnStatus setSize (uint16_t size);

    ::Shapes::ReturnStatus setLocation (uint16_t x, uint16_t y);
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Shapes::CCM_Sender_comp_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::Shapes::CCM_Control_obj>::ref_type control_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_members]
    ::DDS::InstanceHandle_t instance_handle_ { ::DDS::HANDLE_NIL };
    ShapeType square_ {"GREEN", 10, 10, 1};
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
    ::Shapes::ReturnStatus update_square ();
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Sender_comp_exec_i(const Sender_comp_exec_i&) = delete;
    Sender_comp_exec_i(Sender_comp_exec_i&&) = delete;
    Sender_comp_exec_i& operator=(const Sender_comp_exec_i&) = delete;
    Sender_comp_exec_i& operator=(Sender_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_end_decl]

} // namespace Shapes_Sender_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[factory]
extern "C" SHAPES_SENDER_COMP_EXEC_Export  void
create_Shapes_Sender_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.h[Footer]

#endif /* __RIDL_SHAPES_SENDER_COMP_EXEC_H_IJHJIJGJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
