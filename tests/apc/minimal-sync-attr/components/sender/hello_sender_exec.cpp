// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_includes]
#include <thread>
#include "ciaox11/testlib/ciaox11_testlog.h"
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

    CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo" << std::endl;

    IDL::traits<Hello::MyFoo>::ref_type my_foo =
      this->ciao_context_->get_connection_run_my_foo();

    if (!my_foo)
    {
      CIAOX11_TEST_ERROR << "ERROR Sender:\t->get_connection_run_my_foo "
                        << "returns null" << std::endl;
      return 1;
    }

    try
    {
      int32_t answer;
      for (uint16_t i = 0; i < 11; ++i)
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
   * Facet Executor Implementation Class : foo_port_s_foo_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[ctor]
  foo_port_s_foo_prov_exec_i::foo_port_s_foo_prov_exec_i (
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[ctor]

  foo_port_s_foo_prov_exec_i::~foo_port_s_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i[user_private_ops]


  /** Operations and attributes from foo_port_s_foo_prov */

  int32_t
  foo_port_s_foo_prov_exec_i::hello (
      int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i::hello[_answer]
    X11_UNUSED_ARG(answer);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::foo_port_s_foo_prov_exec_i::hello[_answer]
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
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    this->synch_foo_gen_.wait();
    if (my_attrib2() != 11 || my_attrib4().foo_long_struct() != 32 ||
        my_attribute()[0] != 123)
    {
      CIAOX11_TEST_ERROR << " ERROR Sender: expexted attribute values 11, 32 and 123, but received "
                         <<  my_attrib2() << "," << my_attrib4().foo_long_struct() << "," << my_attribute()
                         << std::endl;
    }
    else  CIAOX11_TEST_INFO << " Sender: attribute values : "
                         <<  my_attrib2() << "," << my_attrib4().foo_long_struct() << "," << my_attribute()
                         << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::Hello::CCM_PortFooS>::ref_type
  Sender_exec_i::get_foo_port_s_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[get_foo_port_s_foo_prov]
    if (!this->foo_port_s_foo_prov_)
    {
      this->foo_port_s_foo_prov_ = CORBA::make_reference <foo_port_s_foo_prov_exec_i> (this->context_);
    }
    return this->foo_port_s_foo_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[get_foo_port_s_foo_prov]
  }


  ::Hello::foo_seq
  Sender_exec_i::my_attribute ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attribute[getter]
    return this->my_attribute_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attribute[getter]
  }

  void
  Sender_exec_i::my_attribute (
      const ::Hello::foo_seq& my_attribute)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attribute[setter]
    this->my_attribute_ = my_attribute;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attribute[setter]
  }

  ::Hello::foo_long
  Sender_exec_i::my_attrib2 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib2[getter]
    return this->my_attrib2_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib2[getter]
  }

  void
  Sender_exec_i::my_attrib2 (
      ::Hello::foo_long my_attrib2)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib2[setter]
    this->my_attrib2_ = my_attrib2;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib2[setter]
  }

  ::Hello::bar_seq
  Sender_exec_i::my_attrib3 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib3[getter]
    return this->my_attrib3_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib3[getter]
  }

  void
  Sender_exec_i::my_attrib3 (
      const ::Hello::bar_seq& my_attrib3)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib3[setter]
    this->my_attrib3_ = my_attrib3;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib3[setter]
  }

  ::Hello::foo_struct
  Sender_exec_i::my_attrib4 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib4[getter]
    Hello::foo_struct test {32,"Hi",33};
    return test;
    //return this->my_attrib4_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib4[getter]
  }

  void
  Sender_exec_i::my_attrib4 (
      const ::Hello::foo_struct& my_attrib4)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib4[setter]
    this->my_attrib4_ = my_attrib4;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib4[setter]
  }

  int32_t
  Sender_exec_i::my_attrib5 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib5[getter]
    return this->my_attrib5_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib5[getter]
  }

  void
  Sender_exec_i::my_attrib5 (
      int32_t my_attrib5)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib5[setter]
    this->my_attrib5_ = my_attrib5;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib5[setter]
  }

  ::Hello::out_seq
  Sender_exec_i::my_attrib6 ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib6[getter]
    return this->my_attrib6_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib6[getter]
  }

  void
  Sender_exec_i::my_attrib6 (
      const ::Hello::out_seq& my_attrib6)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i::my_attrib6[setter]
    this->my_attrib6_ = my_attrib6;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i::my_attrib6[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Hello::CCM_Sender_Context >::narrow (std::move(ctx));
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
