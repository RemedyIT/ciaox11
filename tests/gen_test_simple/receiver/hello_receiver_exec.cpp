// -*- C++ -*-
 /**
 * @file    hello_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   Receiver component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_receiver_impl.cpp[Header]

#include "hello_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_global_impl]

namespace Hello_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : rec_listen_port_foo_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[ctor]
  rec_listen_port_foo_prov_exec_i::rec_listen_port_foo_prov_exec_i (
    IDL::traits<Hello::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[ctor]

  rec_listen_port_foo_prov_exec_i::~rec_listen_port_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_private_ops]


  /** Operations and attributes from rec_listen_port_foo_prov */

  int32_t
  rec_listen_port_foo_prov_exec_i::hello (
      int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::hello[_answer]
    CIAOX11_TEST_INFO << "OK: receiver: rec_listen_port_foo_prov_exec_i::hello answer: " << answer << std::endl;
    return answer;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::hello[_answer]
  }

  int16_t
  rec_listen_port_foo_prov_exec_i::interface_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::interface_attrib[getter]
    return this->interface_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::interface_attrib[getter]
  }

  void
  rec_listen_port_foo_prov_exec_i::interface_attrib (
      int16_t interface_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::interface_attrib[setter]
    this->interface_attrib_ = interface_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::interface_attrib[setter]
  }
  /**
   * Facet Executor Implementation Class : rec_listen_port_bar_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[ctor]
  rec_listen_port_bar_prov_exec_i::rec_listen_port_bar_prov_exec_i (
    IDL::traits<Hello::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[ctor]

  rec_listen_port_bar_prov_exec_i::~rec_listen_port_bar_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_private_ops]


  /** Operations and attributes from rec_listen_port_bar_prov */

  void
  rec_listen_port_bar_prov_exec_i::bye (
      int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i::bye[_answer]
    X11_UNUSED_ARG(answer);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i::bye[_answer]
  }

  int16_t
  rec_listen_port_bar_prov_exec_i::bar_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i::bar_attrib[getter]
    return this->bar_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i::bar_attrib[getter]
  }

  void
  rec_listen_port_bar_prov_exec_i::bar_attrib (
      int16_t bar_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i::bar_attrib[setter]
    this->bar_attrib_ = bar_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i::bar_attrib[setter]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "OK: Receiver_exec_i::ccm_activate." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::Hello::CCM_MyFoo >::ref_type
  Receiver_exec_i::get_rec_listen_port_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[get_rec_listen_port_foo_prov]
    if (!this->rec_listen_port_foo_prov_)
    {
      this->rec_listen_port_foo_prov_ = CORBA::make_reference <rec_listen_port_foo_prov_exec_i> (this->context_);
      }
  return this->rec_listen_port_foo_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[get_rec_listen_port_foo_prov]
  }

  IDL::traits< ::Hello::CCM_MyBar >::ref_type
  Receiver_exec_i::get_rec_listen_port_bar_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[get_rec_listen_port_bar_prov]
    CIAOX11_TEST_INFO << "OK: get_rec_listen_port_bar_prov." << std::endl;
    return nullptr;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[get_rec_listen_port_bar_prov]
  }


  ::Hello::TestTopic
  Receiver_exec_i::test_topic ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i::test_topic[getter]
    return this->test_topic_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i::test_topic[getter]
  }

  void
  Receiver_exec_i::test_topic (
      const ::Hello::TestTopic& test_topic)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i::test_topic[setter]
    this->test_topic_ = test_topic;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i::test_topic[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<Hello::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_namespace_end_impl]

} // namespace Hello_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[factory]
extern "C" void
create_Hello_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
