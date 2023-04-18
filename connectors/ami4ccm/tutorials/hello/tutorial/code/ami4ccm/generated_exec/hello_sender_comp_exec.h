// -*- C++ -*-
/**
 * @file    hello_sender_comp_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   generated header file sender component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_HELLO_SENDER_COMP_EXEC_H_FFFEIADG_INCLUDED__
#define __RIDL_HELLO_SENDER_COMP_EXEC_H_FFFEIADG_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_comp_impl.h[Header]

#pragma once

#include "hello_sender_compEC.h"

#include /**/ "hello_sender_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : hello_sender_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : hello_sender_comp_impl.h[user_global_decl]

#include "helloAC.h"

/// Namespace for implementation of Hello::Sender_comp component
namespace Hello_Sender_comp_Impl
{
  /// Forward declarations
  class Sender_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Sender_comp_exec_i
  class Sender_comp_exec_i final
    : public virtual IDL::traits<::Hello::CCM_Sender_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[ctor]
    /// Constructor
    Sender_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[ctor]
    /// Destructor
    virtual ~Sender_comp_exec_i ();

    /** @name Component port operations. */
    //@{

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Hello::CCM_Sender_comp_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
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
  /// AMI4CCM reply handler implementation class
  class AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i final
    :public IDL::traits<Hello::AMI4CCM_MyFoo_objReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[ctor]
    AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[ctor]

    virtual ~AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i ();

    void
    foo (
        int32_t ami_return_val,
        const std::string& answer) override;

    void
    foo_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    hello (
        int32_t answer) override;

    void
    hello_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;


    void
    get_rw_attrib(int16_t _rw_attrib) override;
    void
    get_rw_attrib_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    void
    set_rw_attrib() override;
    void
    set_rw_attrib_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    void
    get_ro_attrib(int16_t _ro_attrib) override;
    void
    get_ro_attrib_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl::AMI4CCM_MyFoo_objReplyHandler_run_my_foo_i[user_private_ops]
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[user_namespace_end_decl]

} // namespace Hello_Sender_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_comp_Impl[factory]
extern "C" HELLO_SENDER_COMP_EXEC_Export  void
create_Hello_Sender_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_comp_impl.h[Footer]

#endif /* __RIDL_HELLO_SENDER_COMP_EXEC_H_FFFEIADG_INCLUDED__ */

// Your footer (code) here
