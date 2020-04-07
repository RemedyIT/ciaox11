// -*- C++ -*-
/**
 * @file    psdd_receiver_exec.h
 * @author  Martin Corino
 *
 * @brief   PSDD Receiver executor.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef __RIDL_PSDD_RECEIVER_EXEC_H_IHIIFJGA_INCLUDED__
#define __RIDL_PSDD_RECEIVER_EXEC_H_IHIIFJGA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psdd_receiver_impl.h[Header]

#pragma once

#include "psdd_receiverEC.h"

#include /**/ "psdd_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_receiver_impl.h[user_includes]
#include <atomic>
//@@{__RIDL_REGEN_MARKER__} - END : psdd_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : psdd_receiver_impl.h[user_global_decl]

/// Namespace for implementation of Test::Receiver component
namespace Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for hello_listen facet
  class hello_listen_exec_i final
    : public IDL::traits< ::Test::Hello::CCM_Listener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    hello_listen_exec_i (
        IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor,
        IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[ctor]

    /// Destructor
    virtual ~hello_listen_exec_i ();

    /** @name Operations from ::Test::Hello::CCM_Listener */
    //@{

    void
    on_data (
        ::Test::StringSeq_t& data) override;
    //@}

    /** @name Attributes from ::Test::Hello::CCM_Listener */
    //@{

    ::CCM_PSDD::ListenerMode
    listen_mode () override;

    void
    listen_mode (::CCM_PSDD::ListenerMode listen_mode) override;

    ::CCM_PSDD::DataCount_t
    max_data () override;

    void
    max_data (::CCM_PSDD::DataCount_t max_data) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Test::Hello::CCM_Listener */
    //@{
    /// Class member storing value of listen_mode attribute
    ::CCM_PSDD::ListenerMode listen_mode_ {};
    /// Class member storing value of max_data attribute
    ::CCM_PSDD::DataCount_t max_data_ {};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[user_members]
    IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::hello_listen_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::hello_listen_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for msg_listen facet
  class msg_listen_exec_i final
    : public IDL::traits< ::Test::Msg::CCM_Listener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    msg_listen_exec_i (
        IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor,
        IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[ctor]

    /// Destructor
    virtual ~msg_listen_exec_i ();

    /** @name Operations from ::Test::Msg::CCM_Listener */
    //@{

    void
    on_data (
        ::Test::MessageSeq_t& data) override;
    //@}

    /** @name Attributes from ::Test::Msg::CCM_Listener */
    //@{

    ::CCM_PSDD::ListenerMode
    listen_mode () override;

    void
    listen_mode (::CCM_PSDD::ListenerMode listen_mode) override;

    ::CCM_PSDD::DataCount_t
    max_data () override;

    void
    max_data (::CCM_PSDD::DataCount_t max_data) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Test::Msg::CCM_Listener */
    //@{
    /// Class member storing value of listen_mode attribute
    ::CCM_PSDD::ListenerMode listen_mode_ {};
    /// Class member storing value of max_data attribute
    ::CCM_PSDD::DataCount_t max_data_ {};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[user_members]
    IDL::traits< ::Test::CCM_Receiver>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::msg_listen_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::msg_listen_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the hello_listen facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Test::Hello::CCM_Listener>::ref_type get_hello_listen () override;
    /// Factory method and getter for the msg_listen facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Test::Msg::CCM_Listener>::ref_type get_msg_listen () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute mode

    std::string
    mode () override;

    void
    mode (const std::string& mode) override;

    /// Attribute subscription

    std::string
    subscription () override;

    void
    subscription (const std::string& subscription) override;

    /// Attribute count

    uint32_t
    count () override;

    void
    count (uint32_t count) override;

    /// Attribute delay

    uint32_t
    delay () override;

    void
    delay (uint32_t delay) override;

    /// Attribute interval

    uint32_t
    interval () override;

    void
    interval (uint32_t interval) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void tick ();
    void increment_hello_counter (uint32_t);
    void increment_msg_counter (uint32_t);
    bool hello_subscription () { return this->hello_subscription_; }
    bool msg_subscription () { return this->msg_subscription_; }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of mode attribute
    std::string mode_;
    /// Class member storing value of subscription attribute
    std::string subscription_;
    /// Class member storing value of count attribute
    uint32_t count_ {};
    /// Class member storing value of delay attribute
    uint32_t delay_ {};
    /// Class member storing value of interval attribute
    uint32_t interval_ {};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::Test::Hello::CCM_Listener>::ref_type hello_listen_;
    IDL::traits< ::Test::Msg::CCM_Listener>::ref_type msg_listen_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    std::atomic<uint32_t> hello_counter_ {0};
    std::atomic<uint32_t> msg_counter_ {0};
    bool hello_subscription_ {false};
    bool msg_subscription_ {false};
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[user_namespace_end_decl]

} // namespace Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Receiver_Impl[factory]
extern "C" PSDD_RECEIVER_EXEC_Export  void
create_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psdd_receiver_impl.h[Footer]

#endif /* __RIDL_PSDD_RECEIVER_EXEC_H_IHIIFJGA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
