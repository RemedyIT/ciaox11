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
    , hello_invoked_ (false)
    , set_interface_attrib_invoked_ (false)
    , get_interface_attrib_invoked_ (false)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[ctor]

  rec_listen_port_foo_prov_exec_i::~rec_listen_port_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[dtor]
    this->hello_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~rec_listen_port_foo_prov_exec_i hello was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~rec_listen_port_foo_prov_exec_i hello was NOT invoked" << std::endl;
    this->get_interface_attrib_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~rec_listen_port_foo_prov_exec_i getter interface_attrib was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~rec_listen_port_foo_prov_exec_i getter interface_attrib was NOT invoked" << std::endl;
    this->set_interface_attrib_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~rec_listen_port_foo_prov_exec_i setter interface_attrib was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~rec_listen_port_foo_prov_exec_i setter interface_attrib was NOT invoked" << std::endl;
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
    this->hello_invoked_ = true;
    return answer;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::hello[_answer]
  }

  int16_t
  rec_listen_port_foo_prov_exec_i::interface_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::interface_attrib[getter]
    this->get_interface_attrib_invoked_ = true;
    return this->interface_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::interface_attrib[getter]
  }

  void
  rec_listen_port_foo_prov_exec_i::interface_attrib (
      int16_t interface_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i::interface_attrib[setter]
    this->set_interface_attrib_invoked_ = true;
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
    this->configuration_complete_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Receiver_exec_i configuration_complete was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Receiver_exec_i configuration_complete was NOT invoked" << std::endl;
    this->ccm_activate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Receiver_exec_i ccm_activate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Receiver_exec_i ccm_activate was NOT invoked" << std::endl;
    this->ccm_passivate_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Receiver_exec_i ccm_passivate was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Receiver_exec_i ccm_passivate was NOT invoked" << std::endl;
    this->ccm_remove_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Receiver_exec_i ccm_remove was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Receiver_exec_i ccm_remove was NOT invoked" << std::endl;
    this->set_session_context_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Receiver_exec_i set_session_context was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Receiver_exec_i set_session_context was NOT invoked" << std::endl;
    this->get_rec_listen_port_bar_prov_invoked_
      ? CIAOX11_TEST_ERROR
        << "ERROR: ~Receiver_exec_i get_rec_listen_port_bar_prov was invoked" << std::endl
      : CIAOX11_TEST_INFO
        << "OK: ~Receiver_exec_i get_rec_listen_port_bar_prov was NOT invoked" << std::endl;
    this->get_rec_listen_port_foo_prov_invoked_
      ? CIAOX11_TEST_INFO
        << "OK: ~Receiver_exec_i get_rec_listen_port_foo_prov was invoked" << std::endl
      : CIAOX11_TEST_ERROR
        << "ERROR: ~Receiver_exec_i get_rec_listen_port_foo_prov was NOT invoked" << std::endl;
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
    CIAOX11_TEST_INFO << "OK: Receiver_exec_i::configuration_complete." << std::endl;
    this->configuration_complete_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "OK: Receiver_exec_i::ccm_activate." << std::endl;
    this->ccm_activate_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "OK: Receiver_exec_i::ccm_passivate." << std::endl;
    this->ccm_passivate_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "OK: Receiver_exec_i::ccm_remove." << std::endl;
    this->ccm_remove_invoked_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::Hello::CCM_MyFoo >::ref_type
  Receiver_exec_i::get_rec_listen_port_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[get_rec_listen_port_foo_prov]
     CIAOX11_TEST_INFO << "OK: get_rec_listen_port_foo_prov." << std::endl;
     this->get_rec_listen_port_foo_prov_invoked_ = true;
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
     this->get_rec_listen_port_bar_prov_invoked_ = true;
    if (!this->rec_listen_port_bar_prov_)
    {
      this->rec_listen_port_bar_prov_ = CORBA::make_reference <rec_listen_port_bar_prov_exec_i> (this->context_);
    }
    return this->rec_listen_port_bar_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[get_rec_listen_port_bar_prov]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[set_session_context]
    CIAOX11_TEST_INFO << "OK: Receiver_exec_i::set_session_context." << std::endl;
    this->set_session_context_invoked_ = true;

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
