// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_global_impl]

namespace Hello_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_impl]
  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
    IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(context));
  }

  int
  synch_foo_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));

    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo_uses " << std::endl;

    IDL::traits<Hello::MyFoo>::ref_type my_foo =
      this->ciao_context_->get_connection_run_my_foo_uses();

    if (!my_foo)
    {
      CIAOX11_TEST_ERROR << "ERROR Sender:\t->get_connection_run_my_foo_uses "
                        << "returns null" << std::endl;
      return 1;
    }

    try
    {
      int32_t answer;
      for (uint16_t i = 0; i < 3; ++i)
      {
        my_foo->hello (answer);
        CIAOX11_TEST_INFO << "Sender:\tsynch hello " << answer << std::endl;
      }
    }
    catch (const Hello::InternalError& )
    {
      CIAOX11_TEST_INFO << "Sender:\tsynch hello get expected exception."
        << std::endl;
    }
    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : run_my_foo_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[ctor]
  run_my_foo_prov_exec_i::run_my_foo_prov_exec_i (
    IDL::traits<::Hello::CCM_Sender_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[ctor]

  run_my_foo_prov_exec_i::~run_my_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i[user_private_ops]


  /** Operations and attributes from run_my_foo_prov */

  int32_t
  run_my_foo_prov_exec_i::foo (
      const std::string& in_str,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i::foo[_in_str_answer]
    X11_UNUSED_ARG(in_str);
    X11_UNUSED_ARG(answer);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i::foo[_in_str_answer]
  }

  void
  run_my_foo_prov_exec_i::hello (
      int32_t& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i::hello[_answer]
    X11_UNUSED_ARG(answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i::hello[_answer]
  }

  int16_t
  run_my_foo_prov_exec_i::rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i::rw_attrib[getter]
    return this->rw_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i::rw_attrib[getter]
  }

  void
  run_my_foo_prov_exec_i::rw_attrib (
      int16_t rw_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i::rw_attrib[setter]
    this->rw_attrib_ = rw_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i::rw_attrib[setter]
  }

  int16_t
  run_my_foo_prov_exec_i::ro_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_foo_prov_exec_i::ro_attrib[getter]
    return this->ro_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_foo_prov_exec_i::ro_attrib[getter]
  }
  /**
   * Facet Executor Implementation Class : run_my_bar_foo_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[ctor]
  run_my_bar_foo_prov_exec_i::run_my_bar_foo_prov_exec_i (
    IDL::traits<::Hello::CCM_Sender_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[ctor]

  run_my_bar_foo_prov_exec_i::~run_my_bar_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i[user_private_ops]


  /** Operations and attributes from run_my_bar_foo_prov */

  void
  run_my_bar_foo_prov_exec_i::hello (
      int32_t& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i::hello[_answer]
    X11_UNUSED_ARG(answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::run_my_bar_foo_prov_exec_i::hello[_answer]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "Sender ACTIVATE" << std::endl;
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    this->synch_foo_gen_.wait();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits<::Hello::CCM_MyFoo>::ref_type
  Sender_exec_i::get_run_my_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[get_run_my_foo_prov]
    if (!this->run_my_foo_prov_)
    {
      this->run_my_foo_prov_ = CORBA::make_reference <run_my_foo_prov_exec_i> (this->context_);
    }
    return this->run_my_foo_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[get_run_my_foo_prov]
  }

  IDL::traits<::Foo::CCM_MyFoo>::ref_type
  Sender_exec_i::get_run_my_bar_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[get_run_my_bar_foo_prov]
    if (!this->run_my_bar_foo_prov_)
    {
      this->run_my_bar_foo_prov_ = CORBA::make_reference <run_my_bar_foo_prov_exec_i> (this->context_);
    }
    return this->run_my_bar_foo_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[get_run_my_bar_foo_prov]
  }


  int32_t
  Sender_exec_i::my_sen_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_sen_attrib[getter]
    return this->my_sen_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_sen_attrib[getter]
  }

  void
  Sender_exec_i::my_sen_attrib (
      int32_t my_sen_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_sen_attrib[setter]
    this->my_sen_attrib_ = my_sen_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_sen_attrib[setter]
  }

  int16_t
  Sender_exec_i::my_sen_attrib2 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_sen_attrib2[getter]
    return this->my_sen_attrib2_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_sen_attrib2[getter]
  }

  ::Bar
  Sender_exec_i::Test ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::Test[getter]
    return this->Test_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::Test[getter]
  }

  void
  Sender_exec_i::Test (
      const ::Bar& Test)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::Test[setter]
    this->Test_ = Test;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::Test[setter]
  }

  ::Foo::Bar
  Sender_exec_i::TestBar ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::TestBar[getter]
    return this->TestBar_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::TestBar[getter]
  }

  void
  Sender_exec_i::TestBar (
      const ::Foo::Bar& TestBar)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::TestBar[setter]
    this->TestBar_ = TestBar;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::TestBar[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<::Hello::CCM_Sender_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_impl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
