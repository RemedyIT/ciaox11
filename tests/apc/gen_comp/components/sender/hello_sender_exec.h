// -*- C++ -*-
/**
 * @file    hello_sender_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_HELLO_SENDER_EXEC_H_JEJEJEFD_INCLUDED__
#define __RIDL_HELLO_SENDER_EXEC_H_JEJEJEFD_INCLUDED__

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

/// Namespace for implementation of Hello::Sender component
namespace Hello_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_decl]
  /// Worker thread for synchronous invocations
  class synch_foo_generator final : public ACE_Task_Base
  {
  public:
    synch_foo_generator () = default;
    void set_context(IDL::traits<Hello::CCM_Sender_Context>::ref_type context);
    int svc () override;

  private:
    IDL::traits<Hello::CCM_Sender_Context>::ref_type ciao_context_;
  };
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for run_my_foo_prov facet
  class run_my_foo_prov_exec_i final
    : public IDL::traits< ::Hello::CCM_MyFoo>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    run_my_foo_prov_exec_i (
        IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[ctor]

    /// Destructor
    ~run_my_foo_prov_exec_i () override;

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Hello::CCM_MyFoo */
    //@{
    /// Class member storing value of rw_attrib attribute
    int16_t rw_attrib_{};
    /// Class member storing value of ro_attrib attribute
    int16_t ro_attrib_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for run_my_bar_foo_prov facet
  class run_my_bar_foo_prov_exec_i final
    : public IDL::traits< ::Foo::CCM_MyFoo>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    run_my_bar_foo_prov_exec_i (
        IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[ctor]

    /// Destructor
    ~run_my_bar_foo_prov_exec_i () override;

    /** @name Operations from ::Foo::CCM_MyFoo */
    //@{

    void
    hello (
        int32_t& answer) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
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
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the run_my_foo_prov facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Hello::CCM_MyFoo>::ref_type get_run_my_foo_prov () override;
    /// Factory method and getter for the run_my_bar_foo_prov facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::Foo::CCM_MyFoo>::ref_type get_run_my_bar_foo_prov () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute my_sen_attrib

    int32_t
    my_sen_attrib () override;

    void
    my_sen_attrib (int32_t my_sen_attrib) override;

    /// Attribute my_sen_attrib2

    int16_t
    my_sen_attrib2 () override;

    /// Attribute Test

    ::Bar
    Test () override;

    void
    Test (const ::Bar& Test) override;

    /// Attribute TestBar

    ::Foo::Bar
    TestBar () override;

    void
    TestBar (const ::Foo::Bar& TestBar) override;
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
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of my_sen_attrib attribute
    int32_t my_sen_attrib_{};
    /// Class member storing value of my_sen_attrib2 attribute
    int16_t my_sen_attrib2_{};
    /// Class member storing value of Test attribute
    ::Bar Test_{};
    /// Class member storing value of TestBar attribute
    ::Foo::Bar TestBar_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::Hello::CCM_MyFoo>::ref_type run_my_foo_prov_;
    IDL::traits< ::Foo::CCM_MyFoo>::ref_type run_my_bar_foo_prov_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_members]
    synch_foo_generator synch_foo_gen_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_decl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" HELLO_SENDER_EXEC_Export  void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.h[Footer]

#endif /* __RIDL_HELLO_SENDER_EXEC_H_JEJEJEFD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
