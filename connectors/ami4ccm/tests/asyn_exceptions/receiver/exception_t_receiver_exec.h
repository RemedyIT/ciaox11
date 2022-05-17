// -*- C++ -*-
/**
 * @file    exception_t_receiver_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   Receiver component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_EXCEPTION_T_RECEIVER_EXEC_H_GJHADAAD_INCLUDED__
#define __RIDL_EXCEPTION_T_RECEIVER_EXEC_H_GJHADAAD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : exception_t_receiver_impl.h[Header]

#pragma once

#include "exception_t_receiverEC.h"

#include /**/ "exception_t_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : exception_t_receiver_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : exception_t_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : exception_t_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : exception_t_receiver_impl.h[user_global_decl]

/// Namespace for implementation of ExceptionT::Receiver component
namespace ExceptionT_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for do_my_foo facet
  class do_my_foo_exec_i final
    : public IDL::traits< ::ExceptionT::CCM_MyFoo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_foo_exec_i (
        IDL::traits< ExceptionT::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[ctor]

    /// Destructor
    ~do_my_foo_exec_i () override;

    /** @name Operations from ::ExceptionT::CCM_MyFoo */
    //@{

    int32_t
    foo (
        int32_t foo_in) override;

    void
    hello (
        int32_t& answer) override;
    //@}

    /** @name Attributes from ::ExceptionT::CCM_MyFoo */
    //@{
    int16_t rw_attrib_g_s () override;
    void rw_attrib_g_s (int16_t rw_attrib_g_s) override;
    int16_t rw_attrib () override;
    void rw_attrib (int16_t rw_attrib) override;
    int16_t rw_attrib_g () override;
    void rw_attrib_g (int16_t rw_attrib_g) override;
    int16_t rw_attrib_s () override;
    void rw_attrib_s (int16_t rw_attrib_s) override;
    int16_t ro_attrib_r () override;
    int16_t ro_attrib () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::ExceptionT::CCM_Receiver_Context>::ref_type context_;

    /** @name Members to store attribute values from ::ExceptionT::CCM_MyFoo */
    //@{
    /// Class member storing value of rw_attrib_g_s attribute
    int16_t rw_attrib_g_s_{};
    /// Class member storing value of rw_attrib attribute
    int16_t rw_attrib_{};
    /// Class member storing value of rw_attrib_g attribute
    int16_t rw_attrib_g_{};
    /// Class member storing value of rw_attrib_s attribute
    int16_t rw_attrib_s_{};
    /// Class member storing value of ro_attrib_r attribute
    int16_t ro_attrib_r_{};
    /// Class member storing value of ro_attrib attribute
    int16_t ro_attrib_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::ExceptionT::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_my_foo facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::ExceptionT::CCM_MyFoo>::ref_type get_do_my_foo () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::ExceptionT::CCM_Receiver_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::ExceptionT::CCM_MyFoo>::ref_type do_my_foo_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Receiver_exec_i(const Receiver_exec_i&) = delete;
    Receiver_exec_i(Receiver_exec_i&&) = delete;
    Receiver_exec_i& operator=(const Receiver_exec_i&) = delete;
    Receiver_exec_i& operator=(Receiver_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[user_namespace_end_decl]

} // namespace ExceptionT_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[factory]
extern "C" EXCEPTION_T_RECEIVER_EXEC_Export  void
create_ExceptionT_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : exception_t_receiver_impl.h[Footer]

#endif /* __RIDL_EXCEPTION_T_RECEIVER_EXEC_H_GJHADAAD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
