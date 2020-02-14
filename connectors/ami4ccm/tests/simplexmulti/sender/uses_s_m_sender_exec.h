// -*- C++ -*-
/**
 * @file    uses_s_m_sender_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   sender of ami4ccm test with combination of uses multiple and simplex
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_USES_S_M_SENDER_EXEC_H_FGBAJEHH_INCLUDED__
#define __RIDL_USES_S_M_SENDER_EXEC_H_FGBAJEHH_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : uses_s_m_sender_impl.h[Header]

#pragma once

#include "uses_s_m_senderEC.h"

#include /**/ "uses_s_m_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_sender_impl.h[user_includes]
#include "ace/Task.h"
//@@{__RIDL_REGEN_MARKER__} - END : uses_s_m_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : uses_s_m_sender_impl.h[user_global_decl]

#include "uses_s_mAC.h"

/// Namespace for implementation of UsesSM::Sender component
namespace UsesSM_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[user_namespace_decl]
  /// Worker thread for asynchronous invocations
   class asynch_foo_generator final : public ACE_Task_Base
   {
     public:
       asynch_foo_generator() = default;
       void set_context(IDL::traits<UsesSM::CCM_Sender_Context>::ref_type context);
       virtual int svc() override;

     private:
       IDL::traits<UsesSM::CCM_Sender_Context>::ref_type ciao_context_;
   };

   /// Worker thread for synchronous invocations
   class synch_foo_generator final : public ACE_Task_Base
   {
     public:
       synch_foo_generator () = default;
       void set_context(IDL::traits<UsesSM::CCM_Sender_Context>::ref_type context);
       virtual int svc () override;

     private:
       IDL::traits<UsesSM::CCM_Sender_Context>::ref_type ciao_context_;
   };

  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[user_namespace_decl]


  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::UsesSM::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    virtual ~Sender_exec_i ();

    /** @name Component port operations. */
    //@{

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::UsesSM::CCM_Sender_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[user_members]
    asynch_foo_generator asynch_foo_gen_;
    synch_foo_generator synch_foo_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::Sender_exec_i[user_private_ops]
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
  class AMI4CCM_OneReplyHandler_m_run_my_one_i final
    :public IDL::traits< UsesSM::AMI4CCM_OneReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[ctor]
    AMI4CCM_OneReplyHandler_m_run_my_one_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[ctor]

    virtual ~AMI4CCM_OneReplyHandler_m_run_my_one_i ();

    virtual
    void
    foo (
        int32_t ami_return_val,
        const std::string& answer) override;

    virtual
    void
    foo_excep (
        IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_members]
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_OneReplyHandler_m_run_my_one_i[user_private_ops]
    //@}
  };
  /// AMI4CCM reply handler implementation class
  class AMI4CCM_TwoReplyHandler_s_run_my_two_i final
    :public IDL::traits< UsesSM::AMI4CCM_TwoReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[ctor]
    AMI4CCM_TwoReplyHandler_s_run_my_two_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[ctor]

    virtual ~AMI4CCM_TwoReplyHandler_s_run_my_two_i ();

    virtual
    void
    bar (
        const std::string& answer) override;

    virtual
    void
    bar_excep (
        IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl::AMI4CCM_TwoReplyHandler_s_run_my_two_i[user_private_ops]
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[user_namespace_end_decl]

} // namespace UsesSM_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Sender_Impl[factory]
extern "C" USES_S_M_SENDER_EXEC_Export  void
create_UsesSM_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_sender_impl.h[Footer]

#endif /* __RIDL_USES_S_M_SENDER_EXEC_H_FGBAJEHH_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
