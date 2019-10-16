// -*- C++ -*-
/**
 * @file    another_comp_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_ANOTHER_COMP_EXEC_H_CFFIEICF_INCLUDED__
#define __RIDL_ANOTHER_COMP_EXEC_H_CFFIEICF_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : another_comp_impl.h[Header]

#pragma once

#include "another_compEC.h"

#include /**/ "another_comp_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : another_comp_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : another_comp_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : another_comp_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : another_comp_impl.h[user_global_decl]

/// Namespace for implementation of AnotherComp component
namespace AnotherComp_Impl
{
  /// Forward declarations
  class AnotherComp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[user_namespace_decl]


  /// Executor implementation class for run_my_bar_foo_prov facet
  class run_my_bar_foo_prov_exec_i final
    : public IDL::traits< ::Foo::CCM_MyFoo>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    run_my_bar_foo_prov_exec_i (
        IDL::traits< CCM_AnotherComp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[ctor]

    /// Destructor
    virtual ~run_my_bar_foo_prov_exec_i ();

    /** @name Operations from ::Foo::CCM_MyFoo */
    //@{

    virtual
    void
    hello (
        int32_t& answer) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_AnotherComp_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : AnotherComp_exec_i
  class AnotherComp_exec_i final
    : public virtual IDL::traits< CCM_AnotherComp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[ctor]
    /// Constructor
    AnotherComp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[ctor]
    /// Destructor
    virtual ~AnotherComp_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the run_my_bar_foo_prov facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::Foo::CCM_MyFoo >::ref_type get_run_my_bar_foo_prov () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute my_sen_attrib

    virtual
    int32_t
    my_sen_attrib () override;

    virtual
    void
    my_sen_attrib (
        int32_t my_sen_attrib) override;

    /// Attribute TestBar

    virtual
    ::Foo::Bar
    TestBar () override;

    virtual
    void
    TestBar (
        const ::Foo::Bar& TestBar) override;

    /// Attribute my_sen_attrib_2

    virtual
    int32_t
    my_sen_attrib_2 () override;

    /// Attribute my_sen_attrib_3

    virtual
    int32_t
    my_sen_attrib_3 () override;

    virtual
    void
    my_sen_attrib_3 (
        int32_t my_sen_attrib_3) override;

    /// Attribute TestBar_2

    virtual
    ::Foo::Bar
    TestBar_2 () override;

    virtual
    void
    TestBar_2 (
        const ::Foo::Bar& TestBar_2) override;

    /// Attribute TestBarBar

    virtual
    ::Foo::Bar_in_Bar
    TestBarBar () override;

    virtual
    void
    TestBarBar (
        const ::Foo::Bar_in_Bar& TestBarBar) override;

    /// Attribute TestBarNestedBar

    virtual
    ::Foo::Bar_with_nested_bar
    TestBarNestedBar () override;

    virtual
    void
    TestBarNestedBar (
        const ::Foo::Bar_with_nested_bar& TestBarNestedBar) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_AnotherComp_Context >::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of my_sen_attrib attribute
    int32_t my_sen_attrib_ {};
    /// Class member storing value of TestBar attribute
    ::Foo::Bar TestBar_;
    /// Class member storing value of my_sen_attrib_2 attribute
    int32_t my_sen_attrib_2_ {};
    /// Class member storing value of my_sen_attrib_3 attribute
    int32_t my_sen_attrib_3_ {};
    /// Class member storing value of TestBar_2 attribute
    ::Foo::Bar TestBar_2_;
    /// Class member storing value of TestBarBar attribute
    ::Foo::Bar_in_Bar TestBarBar_;
    /// Class member storing value of TestBarNestedBar attribute
    ::Foo::Bar_with_nested_bar TestBarNestedBar_;
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::Foo::CCM_MyFoo >::ref_type run_my_bar_foo_prov_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    AnotherComp_exec_i(const AnotherComp_exec_i&) = delete;
    AnotherComp_exec_i(AnotherComp_exec_i&&) = delete;
    AnotherComp_exec_i& operator=(const AnotherComp_exec_i&) = delete;
    AnotherComp_exec_i& operator=(AnotherComp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[user_namespace_end_decl]

} // namespace AnotherComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[factory]
extern "C" ANOTHER_COMP_EXEC_Export  void
create_AnotherComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : another_comp_impl.h[Footer]

#endif /* __RIDL_ANOTHER_COMP_EXEC_H_CFFIEICF_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
