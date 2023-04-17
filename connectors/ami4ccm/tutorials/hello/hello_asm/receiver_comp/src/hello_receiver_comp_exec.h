/**
 * @file    hello_receiver_comp_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   header file receiver component implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_HELLO_RECEIVER_COMP_EXEC_H_JIHJFFBD_INCLUDED__
#define __RIDL_HELLO_RECEIVER_COMP_EXEC_H_JIHJFFBD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_receiver_comp_impl.h[Header]

#pragma once

#include "hello_receiver_compEC.h"

#include /**/ "hello_receiver_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : hello_receiver_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : hello_receiver_comp_impl.h[user_global_decl]

/// Namespace for implementation of Hello::Receiver_comp component
namespace Hello_Receiver_comp_Impl
{
  /// Forward declarations
  class Receiver_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl[user_namespace_decl]


  /// Executor implementation class for do_my_foo facet
  class do_my_foo_exec_i final
    : public IDL::traits<::Hello::CCM_MyFoo_obj>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::do_my_foo_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_foo_exec_i (
        IDL::traits<Hello::CCM_Receiver_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::do_my_foo_exec_i[ctor]

    /// Destructor
    ~do_my_foo_exec_i () override;

    /** @name Operations from ::Hello::CCM_MyFoo_obj */
    //@{

    int32_t
    foo (
        const std::string& in_str,
        std::string& answer) override;

    void
    hello (
        int32_t& answer) override;
    //@}

    /** @name Attributes from ::Hello::CCM_MyFoo_obj */
    //@{
    int16_t rw_attrib () override;
    void rw_attrib (int16_t rw_attrib) override;
    int16_t ro_attrib () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::do_my_foo_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::do_my_foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Hello::CCM_Receiver_comp_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Hello::CCM_MyFoo_obj */
    //@{
    /// Class member storing value of rw_attrib attribute
    int16_t rw_attrib_{};
    /// Class member storing value of ro_attrib attribute
    int16_t ro_attrib_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::do_my_foo_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::do_my_foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::do_my_foo_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::do_my_foo_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_comp_exec_i
  class Receiver_comp_exec_i final
    : public virtual IDL::traits<::Hello::CCM_Receiver_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[ctor]
    /// Constructor
    Receiver_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[ctor]
    /// Destructor
    ~Receiver_comp_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_my_foo facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::Hello::CCM_MyFoo_obj>::ref_type get_do_my_foo () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Hello::CCM_Receiver_comp_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits<::Hello::CCM_MyFoo_obj>::ref_type do_my_foo_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl::Receiver_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Receiver_comp_exec_i(const Receiver_comp_exec_i&) = delete;
    Receiver_comp_exec_i(Receiver_comp_exec_i&&) = delete;
    Receiver_comp_exec_i& operator=(const Receiver_comp_exec_i&) = delete;
    Receiver_comp_exec_i& operator=(Receiver_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl[user_namespace_end_decl]

} // namespace Hello_Receiver_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_comp_Impl[factory]
extern "C" HELLO_RECEIVER_COMP_EXEC_Export  void
create_Hello_Receiver_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_comp_impl.h[Footer]

#endif /* __RIDL_HELLO_RECEIVER_COMP_EXEC_H_JIHJFFBD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
