// -*- C++ -*-
/**
 * @file    hello_sender_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   header sender compomnent
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_HELLO_SENDER_EXEC_H_GIHBFEEE_INCLUDED__
#define __RIDL_HELLO_SENDER_EXEC_H_GIHBFEEE_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.h[Header]

#pragma once

#include "hello_senderEC.h"

#include /**/ "hello_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[user_includes]
#include "ace/Task.h"
//@@{__RIDL_REGEN_MARKER__} - END : hello_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : hello_sender_impl.h[user_global_decl]

#include "usesmultiAC.h"

/// Namespace for implementation of UsesMulti::Sender component
namespace UsesMulti_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[user_namespace_decl]
  /// Worker thread for asynchronous invocations
  class asynch_foo_generator final : public ACE_Task_Base
  {
  public:
      asynch_foo_generator() = default;
      void set_context(IDL::traits<UsesMulti::CCM_Sender_Context>::ref_type context);
      int svc() override;

    private:
      IDL::traits<UsesMulti::CCM_Sender_Context>::ref_type ciao_context_;
  };

  /// Worker thread for synchronous invocations
  class synch_foo_generator final : public ACE_Task_Base
  {
  public:
    synch_foo_generator () = default;
    void set_context(IDL::traits<UsesMulti::CCM_Sender_Context>::ref_type context);
    int svc () override;

  private:
    IDL::traits<UsesMulti::CCM_Sender_Context>::ref_type ciao_context_;
  };

  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits<::UsesMulti::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::UsesMulti::CCM_Sender_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[user_members]
    asynch_foo_generator asynch_foo_gen_;
    synch_foo_generator synch_foo_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::Sender_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Sender_exec_i(const Sender_exec_i&) = delete;
    Sender_exec_i(Sender_exec_i&&) = delete;
    Sender_exec_i& operator=(const Sender_exec_i&) = delete;
    Sender_exec_i& operator=(Sender_exec_i&&) = delete;
    //@}
  };
  /// AMI4CCM reply handler implementation class
  class AMI4CCM_OneReplyHandler_run_my_um_one_i final
    :public IDL::traits< UsesMulti::AMI4CCM_OneReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[ctor]
    AMI4CCM_OneReplyHandler_run_my_um_one_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[ctor]

    virtual ~AMI4CCM_OneReplyHandler_run_my_um_one_i ();

    void foo (
        int32_t ami_return_val,
        const std::string& answer) override;

    void foo_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[user_members]
    uint16_t received_;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_um_one_i[user_private_ops]
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[user_namespace_end_decl]

} // namespace UsesMulti_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesMulti_Sender_Impl[factory]
extern "C" HELLO_SENDER_EXEC_Export  void
create_UsesMulti_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : UsesMulti_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[Footer]

#endif /* __RIDL_HELLO_SENDER_EXEC_H_GIHBFEEE_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
