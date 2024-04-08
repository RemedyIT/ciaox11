// -*- C++ -*-
/**
 * @file    hello_receiver_exec.cpp
 * @author  Marijke Hengstmengel
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
   * Facet Executor Implementation Class : do_my_B_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i[ctor]
  do_my_B_exec_i::do_my_B_exec_i (
    IDL::traits<::Hello::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i[ctor]

  do_my_B_exec_i::~do_my_B_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i[user_private_ops]


  /** Operations and attributes from do_my_B */

  int32_t
  do_my_B_exec_i::op_B (
      int32_t in_l,
      const ::Hello::S1& s_in_l)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::op_B[_in_l_s_in_l]
    return in_l + s_in_l.s_long();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::op_B[_in_l_s_in_l]
  }

  bool
  do_my_B_exec_i::op_C (
      int32_t in_c,
      bool in_b,
      bool& out_b,
      bool& inout_b)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::op_C[_in_c_in_b_out_b_inout_b]
    X11_UNUSED_ARG(in_c);
    X11_UNUSED_ARG(in_b);
    X11_UNUSED_ARG(out_b);
    X11_UNUSED_ARG(inout_b);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::op_C[_in_c_in_b_out_b_inout_b]
  }

  bool
  do_my_B_exec_i::op_D (
      int32_t in_c,
      uint8_t in_b,
      uint8_t& out_b,
      uint8_t& inout_b)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::op_D[_in_c_in_b_out_b_inout_b]
    X11_UNUSED_ARG(in_c);
    X11_UNUSED_ARG(in_b);
    X11_UNUSED_ARG(out_b);
    X11_UNUSED_ARG(inout_b);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::op_D[_in_c_in_b_out_b_inout_b]
  }

  bool
  do_my_B_exec_i::op_E (
      int32_t in_c,
      char in_b,
      char& out_b,
      char& inout_b)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::op_E[_in_c_in_b_out_b_inout_b]
    X11_UNUSED_ARG(in_c);
    X11_UNUSED_ARG(in_b);
    X11_UNUSED_ARG(out_b);
    X11_UNUSED_ARG(inout_b);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::op_E[_in_c_in_b_out_b_inout_b]
  }

  bool
  do_my_B_exec_i::op_F (
      int32_t in_c,
      wchar_t in_b,
      wchar_t& out_b,
      wchar_t& inout_b)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::op_F[_in_c_in_b_out_b_inout_b]
    X11_UNUSED_ARG(in_c);
    X11_UNUSED_ARG(in_b);
    X11_UNUSED_ARG(out_b);
    X11_UNUSED_ARG(inout_b);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::op_F[_in_c_in_b_out_b_inout_b]
  }

  int32_t
  do_my_B_exec_i::op_A (
      int32_t in_l)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::op_A[_in_l]
    return in_l + 100;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::op_A[_in_l]
  }

  bool
  do_my_B_exec_i::at_D ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::at_D[getter]
    return this->at_D_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::at_D[getter]
  }

  void
  do_my_B_exec_i::at_D (
      bool at_D)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::at_D[setter]
    this->at_D_ = at_D;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::at_D[setter]
  }

  int32_t
  do_my_B_exec_i::at_E ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::at_E[getter]
    return this->at_E_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::at_E[getter]
  }

  void
  do_my_B_exec_i::at_E (
      int32_t at_E)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::do_my_B_exec_i::at_E[setter]
    this->at_E_ = at_E;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::do_my_B_exec_i::at_E[setter]
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
    // Your code here
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

  IDL::traits<::Hello::CCM_B>::ref_type
  Receiver_exec_i::get_do_my_B ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[get_do_my_B]
    if (!this->do_my_B_)
    {
      this->do_my_B_ = CORBA::make_reference <do_my_B_exec_i> (this->context_);
    }
    return this->do_my_B_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[get_do_my_B]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<::Hello::CCM_Receiver_Context >::narrow (std::move(ctx));
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
