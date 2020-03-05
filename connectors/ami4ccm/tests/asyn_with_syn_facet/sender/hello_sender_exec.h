// -*- C++ -*-
/**
 * @file    hello_sender_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   Sender component exec
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_HELLO_SENDER_EXEC_H_EJGHDIEC_INCLUDED__
#define __RIDL_HELLO_SENDER_EXEC_H_EJGHDIEC_INCLUDED__

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

#include "helloAC.h"

/// Namespace for implementation of Hello::Sender component
namespace Hello_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_decl]
  /// Common exception handlers
  void HandleException (
      int32_t id,
      const std::string& error_string,
      const std::string& func);

  void HandleException (
      IDL::traits< ::CCM_AMI::ExceptionHolder>::ref_type excep_holder,
      const std::string& func);

  /// Worker thread for asynchronous invocations
  class asynch_foo_generator final : public ACE_Task_Base
  {
    public:
       asynch_foo_generator() = default;
       void set_context(IDL::traits<Hello::CCM_Sender_Context>::ref_type context);
       void set_comp_exec (IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec)
       { this->comp_exec_ = comp_exec; }
       int svc() override;

     private:
       IDL::traits<Hello::CCM_Sender_Context>::ref_type context_;
       IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec_;
  };

  /// Worker thread for synchronous invocations
  class synch_foo_generator final : public ACE_Task_Base
   {
   public:
     synch_foo_generator () = default;
     void set_context(IDL::traits<Hello::CCM_Sender_Context>::ref_type context);
     virtual int svc () override;

   private:
     IDL::traits<Hello::CCM_Sender_Context>::ref_type context_;
   };
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for do_control facet
  class do_control_exec_i final
    : public IDL::traits< ::Hello::CCM_Control>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_control_exec_i (
      IDL::traits<Hello::CCM_Sender_Context>::ref_type context,
      IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[ctor]

    /// Destructor
    virtual ~do_control_exec_i ();

    /** @name Operations from ::Hello::CCM_Control */
    //@{

    void
    start () override;

    void
    shutdown () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[user_members]
    IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for do_my_foo facet
  class do_my_foo_exec_i final
    : public IDL::traits< ::Hello::CCM_MyFoo>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_foo_exec_i (
      IDL::traits<Hello::CCM_Sender_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[ctor]

    /// Destructor
    virtual ~do_my_foo_exec_i ();

    /** @name Operations from ::Hello::CCM_MyFoo */
    //@{

    int32_t
    foo (
        const std::string& in_str,
        std::string& answer) override;

    void
    hello (
        int32_t& answer) override;
    //@}

    /** @name Attributes from ::Hello::CCM_MyFoo */
    //@{

    int16_t
    rw_attrib () override;

    void
    rw_attrib (int16_t rw_attrib) override;

    int16_t
    ro_attrib () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[user_public_ops]
    uint32_t foo_calls () { return this->foo_calls_; }
    uint32_t hello_calls () { return this->hello_calls_; }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Hello::CCM_MyFoo */
    //@{
    /// Class member storing value of rw_attrib attribute
    int16_t rw_attrib_ {};
    /// Class member storing value of ro_attrib attribute
    int16_t ro_attrib_ {};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[user_members]
    uint32_t foo_calls_ {};
    uint32_t hello_calls_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::Hello::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    virtual ~Sender_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_control facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Hello::CCM_Control>::ref_type get_do_control () override;
    /// Factory method and getter for the do_my_foo facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Hello::CCM_MyFoo>::ref_type get_do_my_foo () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
    void start ();
    void stop ();
    void add_asyn_reply () { this->asyn_replies_++; }
    uint32_t asyn_replies () { return this->asyn_replies_; }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::Hello::CCM_Control>::ref_type do_control_;
    IDL::traits< ::Hello::CCM_MyFoo>::ref_type do_my_foo_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_members]
    uint32_t asyn_replies_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
    asynch_foo_generator asynch_foo_gen_;
    synch_foo_generator synch_foo_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
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
    :public IDL::traits< Hello::AMI4CCM_MyFooReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
    AMI4CCM_MyFooReplyHandler_run_my_foo_i (IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

    virtual ~AMI4CCM_MyFooReplyHandler_run_my_foo_i ();

    void
    foo (
        int32_t ami_return_val,
        const std::string& answer) override;

    void
    foo_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void
    hello (
        int32_t answer) override;

    void
    hello_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;


    void
    get_rw_attrib(int16_t _rw_attrib) override;
    void
    get_rw_attrib_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    void
    set_rw_attrib() override;
    void
    set_rw_attrib_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    void
    get_ro_attrib(int16_t _ro_attrib) override;
    void
    get_ro_attrib_excep (
        IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_members]
    IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_decl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" HELLO_SENDER_EXEC_Export  void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[Footer]

#endif /* __RIDL_HELLO_SENDER_EXEC_H_EJGHDIEC_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
