// -*- C++ -*-
/**
 * @file    multi_inherit_sender_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   sender of ami4ccm test with multiple inheritance
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef __RIDL_MULTI_INHERIT_SENDER_EXEC_H_IJBEBEBJ_INCLUDED__
#define __RIDL_MULTI_INHERIT_SENDER_EXEC_H_IJBEBEBJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : multi_inherit_sender_impl.h[Header]

#pragma once

#include "multi_inherit_senderEC.h"

#include /**/ "multi_inherit_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : multi_inherit_sender_impl.h[user_includes]
#include "ace/Task.h"
//@@{__RIDL_REGEN_MARKER__} - END : multi_inherit_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : multi_inherit_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : multi_inherit_sender_impl.h[user_global_decl]

#include "multi_inheritAC.h"
#include "baseAC.h"

/// Namespace for implementation of InterMulti::Sender component
namespace InterMulti_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[user_namespace_decl]
  /// Worker threads for asynchronous invocations
  class asynch_one_generator : public ACE_Task_Base
  {
    public:
      asynch_one_generator();
      void set_context(IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context);
      int svc() override;

    private:
      IDL::traits<InterMulti::CCM_Sender_Context>::ref_type ciao_context_;
  };

  class asynch_two_generator : public ACE_Task_Base
  {
    public:
      asynch_two_generator();
      void set_context(IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context);
      int svc() override;

    private:
      IDL::traits<InterMulti::CCM_Sender_Context>::ref_type ciao_context_;
  };

  class asynch_three_generator : public ACE_Task_Base
  {
    public:
      asynch_three_generator();
      void set_context(IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context);
      int svc() override;

    private:
      IDL::traits<InterMulti::CCM_Sender_Context>::ref_type ciao_context_;
  };

  /// Worker threads for synchronous invocations
  class synch_one_generator : public ACE_Task_Base
  {
    public:
      synch_one_generator ();
      void set_context(IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context);
      int svc () override;

    private:
      IDL::traits<InterMulti::CCM_Sender_Context>::ref_type ciao_context_;
  };

  class synch_three_generator : public ACE_Task_Base
   {
     public:
       synch_three_generator ();
       void set_context(IDL::traits<InterMulti::CCM_Sender_Context>::ref_type context);
       int svc () override;

     private:
       IDL::traits<InterMulti::CCM_Sender_Context>::ref_type ciao_context_;
   };
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::InterMulti::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[ctor]
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::InterMulti::CCM_Sender_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[user_members]
    asynch_one_generator asynch_one_gen_;
    synch_one_generator synch_one_gen_;
    asynch_two_generator asynch_two_gen_;
    asynch_three_generator asynch_three_gen_;
    synch_three_generator synch_three_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::Sender_exec_i[user_private_ops]
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
  class AMI4CCM_OneReplyHandler_run_my_one_i final
    :public IDL::traits< InterMulti::AMI4CCM_OneReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[ctor]
    AMI4CCM_OneReplyHandler_run_my_one_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[ctor]

    virtual ~AMI4CCM_OneReplyHandler_run_my_one_i ();

    void
    foo (
        int32_t ami_return_val,
        const std::string& answer) override;

    void
    foo_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_OneReplyHandler_run_my_one_i[user_private_ops]
    //@}
  };
  /// AMI4CCM reply handler implementation class
  class AMI4CCM_TwoReplyHandler_run_my_two_i final
    :public IDL::traits< InterMulti::AMI4CCM_TwoReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[ctor]
    AMI4CCM_TwoReplyHandler_run_my_two_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[ctor]

    virtual ~AMI4CCM_TwoReplyHandler_run_my_two_i ();

    void
    bar (
        const std::string& answer) override;

    void
    bar_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_TwoReplyHandler_run_my_two_i[user_private_ops]
    //@}
  };
  /// AMI4CCM reply handler implementation class
  class AMI4CCM_ThreeReplyHandler_run_my_three_i final
    :public IDL::traits< InterMulti::AMI4CCM_ThreeReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[ctor]
    AMI4CCM_ThreeReplyHandler_run_my_three_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[ctor]

    virtual ~AMI4CCM_ThreeReplyHandler_run_my_three_i ();

    void
    plus (
        const std::string& answer) override;

    void
    plus_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    foo (
        int32_t ami_return_val,
        const std::string& answer) override;

    void
    foo_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    bar (
        const std::string& answer) override;

    void
    bar_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl::AMI4CCM_ThreeReplyHandler_run_my_three_i[user_private_ops]
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[user_namespace_end_decl]

} // namespace InterMulti_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterMulti_Sender_Impl[factory]
extern "C" MULTI_INHERIT_SENDER_EXEC_Export  void
create_InterMulti_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : InterMulti_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : multi_inherit_sender_impl.h[Footer]

#endif /* __RIDL_MULTI_INHERIT_SENDER_EXEC_H_IJBEBEBJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
