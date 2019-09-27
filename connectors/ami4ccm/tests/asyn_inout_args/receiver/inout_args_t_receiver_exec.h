// -*- C++ -*-
/**
 * @file    inout_args_t_receiver_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   receiver compomnent
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#ifndef __RIDL_INOUT_ARGS_T_RECEIVER_EXEC_H_BDBEBDBA_INCLUDED__
#define __RIDL_INOUT_ARGS_T_RECEIVER_EXEC_H_BDBEBDBA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : inout_args_t_receiver_impl.h[Header]

#pragma once

#include "inout_args_t_receiverEC.h"

#include /**/ "inout_args_t_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : inout_args_t_receiver_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : inout_args_t_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : inout_args_t_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : inout_args_t_receiver_impl.h[user_global_decl]

/// Namespace for implementation of InterInOutT::Receiver component
namespace InterInOutT_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for do_my_foo facet
  class do_my_foo_exec_i final
    : public IDL::traits< ::InterInOutT::CCM_MyFoo>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::do_my_foo_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_foo_exec_i (
        IDL::traits< InterInOutT::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::do_my_foo_exec_i[ctor]

    /// Destructor
    virtual ~do_my_foo_exec_i ();

    /** @name Operations from ::InterInOutT::CCM_MyFoo */
    //@{

    virtual
    int32_t
    foo (
        const std::string& in_str,
        int32_t& cmd,
        std::string& answer) override;

    virtual
    void
    var_ins (
        const std::string& in_str,
        std::string& answer,
        double& cmd) override;

    virtual
    void
    var_div_ins (
        ::InterInOutT::TestTopic& test_topic,
        ::InterInOutT::TopicString& topic_str,
        ::InterInOutT::TestArray& topic_arr,
        std::string& answer) override;

    virtual
    void
    var_div2_ins (
        ::InterInOutT::X_Union& topic_union,
        ::InterInOutT::test_seq& seq,
        std::string& answer) override;

    virtual
    void
    enum_in (
        std::string& answer,
        ::InterInOutT::test_enum& in_test) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::InterInOutT::CCM_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::do_my_foo_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::do_my_foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::InterInOutT::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_my_foo facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::InterInOutT::CCM_MyFoo >::ref_type get_do_my_foo () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::InterInOutT::CCM_Receiver_Context >::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::InterInOutT::CCM_MyFoo >::ref_type do_my_foo_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::Receiver_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl[user_namespace_end_decl]

} // namespace InterInOutT_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : InterInOutT_Receiver_Impl[factory]
extern "C" INOUT_ARGS_T_RECEIVER_EXEC_Export  void
create_InterInOutT_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : InterInOutT_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : inout_args_t_receiver_impl.h[Footer]

#endif /* __RIDL_INOUT_ARGS_T_RECEIVER_EXEC_H_BDBEBDBA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
