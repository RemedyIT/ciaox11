// -*- C++ -*-
/**
 * @file    another_comp_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : another_comp_impl.cpp[Header]

#include "another_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[user_global_impl]

namespace AnotherComp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : run_my_bar_foo_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[ctor]
  run_my_bar_foo_prov_exec_i::run_my_bar_foo_prov_exec_i (
    IDL::traits< CCM_AnotherComp_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[ctor]

  run_my_bar_foo_prov_exec_i::~run_my_bar_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]


  /** Operations and attributes from run_my_bar_foo_prov */

  void
  run_my_bar_foo_prov_exec_i::hello (
      int32_t& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::run_my_bar_foo_prov_exec_i::hello[_answer]
    X11_UNUSED_ARG(answer);
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::run_my_bar_foo_prov_exec_i::hello[_answer]
  }

  /**
   * Component Executor Implementation Class : AnotherComp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[ctor]
  AnotherComp_exec_i::AnotherComp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[ctor]

  AnotherComp_exec_i::~AnotherComp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[user_private_ops]

  /** Session component operations */
  void AnotherComp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[configuration_complete]
  }

  void AnotherComp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "AnotherComponent ACTIVATE" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[ccm_activate]
  }

  void AnotherComp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[ccm_passivate]
  }

  void AnotherComp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[ccm_remove]
  }

  IDL::traits<::Foo::CCM_MyFoo>::ref_type
  AnotherComp_exec_i::get_run_my_bar_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[get_run_my_bar_foo_prov]
    if (!this->run_my_bar_foo_prov_)
    {
      this->run_my_bar_foo_prov_ = CORBA::make_reference <run_my_bar_foo_prov_exec_i> (this->context_);
    }
    return this->run_my_bar_foo_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[get_run_my_bar_foo_prov]
  }


  int32_t
  AnotherComp_exec_i::my_sen_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib[getter]
    return this->my_sen_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib[getter]
  }

  void
  AnotherComp_exec_i::my_sen_attrib (
      int32_t my_sen_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib[setter]
    this->my_sen_attrib_ = my_sen_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib[setter]
  }

  ::Foo::Bar
  AnotherComp_exec_i::TestBar ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBar[getter]
    return this->TestBar_;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBar[getter]
  }

  void
  AnotherComp_exec_i::TestBar (
      const ::Foo::Bar& TestBar)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBar[setter]
    this->TestBar_ = TestBar;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBar[setter]
  }

  int32_t
  AnotherComp_exec_i::my_sen_attrib_2 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib_2[getter]
    return this->my_sen_attrib_2_;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib_2[getter]
  }

  int32_t
  AnotherComp_exec_i::my_sen_attrib_3 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib_3[getter]
    return this->my_sen_attrib_3_;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib_3[getter]
  }

  void
  AnotherComp_exec_i::my_sen_attrib_3 (
      int32_t my_sen_attrib_3)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib_3[setter]
    this->my_sen_attrib_3_ = my_sen_attrib_3;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::my_sen_attrib_3[setter]
  }

  ::Foo::Bar
  AnotherComp_exec_i::TestBar_2 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBar_2[getter]
    return this->TestBar_2_;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBar_2[getter]
  }

  void
  AnotherComp_exec_i::TestBar_2 (
      const ::Foo::Bar& TestBar_2)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBar_2[setter]
    this->TestBar_2_ = TestBar_2;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBar_2[setter]
  }

  ::Foo::Bar_in_Bar
  AnotherComp_exec_i::TestBarBar ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBarBar[getter]
    return this->TestBarBar_;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBarBar[getter]
  }

  void
  AnotherComp_exec_i::TestBarBar (
      const ::Foo::Bar_in_Bar& TestBarBar)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBarBar[setter]
    this->TestBarBar_ = TestBarBar;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBarBar[setter]
  }

  ::Foo::Bar_with_nested_bar
  AnotherComp_exec_i::TestBarNestedBar ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBarNestedBar[getter]
    return this->TestBarNestedBar_;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBarNestedBar[getter]
  }

  void
  AnotherComp_exec_i::TestBarNestedBar (
      const ::Foo::Bar_with_nested_bar& TestBarNestedBar)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i::TestBarNestedBar[setter]
    this->TestBarNestedBar_ = TestBarNestedBar;
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i::TestBarNestedBar[setter]
  }

  /// Operations from Components::SessionComponent
  void
  AnotherComp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl::AnotherComp_exec_i[set_session_context]
    this->context_ = IDL::traits< CCM_AnotherComp_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl::AnotherComp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[user_namespace_end_impl]

} // namespace AnotherComp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : AnotherComp_Impl[factory]
extern "C" void
create_AnotherComp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <AnotherComp_Impl::AnotherComp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : AnotherComp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : another_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
