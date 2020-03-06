// -*- C++ -*-
/**
 * @file    return_args_t_sender_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   sender of ami4ccm test with several return types
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_RETURN_ARGS_T_SENDER_EXEC_H_IDEJHBJA_INCLUDED__
#define __RIDL_RETURN_ARGS_T_SENDER_EXEC_H_IDEJHBJA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : return_args_t_sender_impl.h[Header]

#pragma once

#include "return_args_t_senderEC.h"

#include /**/ "return_args_t_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : return_args_t_sender_impl.h[user_includes]
#include "ace/Task.h"
//@@{__RIDL_REGEN_MARKER__} - END : return_args_t_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : return_args_t_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : return_args_t_sender_impl.h[user_global_decl]

#include "return_args_tAC.h"

/// Namespace for implementation of InterReturnT::Sender component
namespace InterReturnT_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[user_namespace_decl]
  /// Worker thread for asynchronous invocations
  class asynch_foo_generator final : public ACE_Task_Base
  {
    public:
      asynch_foo_generator() = default;
      void set_context(IDL::traits<InterReturnT::CCM_Sender_Context>::ref_type context);
      int svc() override;

    private:
      IDL::traits<InterReturnT::CCM_Sender_Context>::ref_type ciao_context_;
  };

  /// Worker thread for synchronous invocations
  class synch_foo_generator final : public ACE_Task_Base
  {
    public:
      synch_foo_generator () = default;
      void set_context(IDL::traits<InterReturnT::CCM_Sender_Context>::ref_type context);
      int svc () override;

    private:
      IDL::traits<InterReturnT::CCM_Sender_Context>::ref_type ciao_context_;
  };

  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::InterReturnT::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    virtual ~Sender_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::InterReturnT::CCM_Sender_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[user_members]
    asynch_foo_generator asynch_foo_gen_;
    synch_foo_generator synch_foo_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::Sender_exec_i[user_private_ops]
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
  class AMI4CCM_MyFooReplyHandler_run_my_foo_i final
    :public IDL::traits< InterReturnT::AMI4CCM_MyFooReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
    AMI4CCM_MyFooReplyHandler_run_my_foo_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

    virtual ~AMI4CCM_MyFooReplyHandler_run_my_foo_i ();

    void
    ret_void (
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_void_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    ret_long (
        int32_t ami_return_val,
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_long_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    ret_double (
        double ami_return_val,
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_double_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    ret_struct (
        const ::InterReturnT::TestStruct& ami_return_val,
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_struct_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    ret_array (
        const ::InterReturnT::TestArray& ami_return_val,
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_array_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    ret_seq (
        const ::InterReturnT::TestSeq& ami_return_val,
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_seq_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    ret_union (
        const ::InterReturnT::X_Union& ami_return_val,
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_union_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    ret_enum (
        ::InterReturnT::test_enum ami_return_val,
        const std::string& answer,
        int32_t l_cmd) override;

    void
    ret_enum_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[user_namespace_end_decl]

} // namespace InterReturnT_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterReturnT_Sender_Impl[factory]
extern "C" RETURN_ARGS_T_SENDER_EXEC_Export  void
create_InterReturnT_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : InterReturnT_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : return_args_t_sender_impl.h[Footer]

#endif /* __RIDL_RETURN_ARGS_T_SENDER_EXEC_H_IDEJHBJA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
