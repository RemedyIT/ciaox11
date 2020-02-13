// -*- C++ -*-
/**
 * @file    exception_t_receiver_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   Receiver component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : exception_t_receiver_impl.cpp[Header]

#include "exception_t_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[user_includes]
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[user_global_impl]

namespace ExceptionT_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[ctor]
  do_my_foo_exec_i::do_my_foo_exec_i (
    IDL::traits<ExceptionT::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[ctor]

  do_my_foo_exec_i::~do_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from do_my_foo */

  int32_t
  do_my_foo_exec_i::foo (
      int32_t foo_in)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::foo[_foo_in]
    if (foo_in == 0)
    {
      ExceptionT::InternalError ex  (42, "Rec.Exc.foo",
                                     "thrown by receiver");
      throw ex;
    }
    else
    {
       std::this_thread::sleep_for (std::chrono::seconds (1));
       return 1;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::foo[_foo_in]
  }

  void
  do_my_foo_exec_i::hello (
      int32_t& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::hello[_answer]
    X11_UNUSED_ARG(answer);
    //always an exception is thrown
    ExceptionT::InternalError ex (42, "Rec.Exc.hello",
                                  "thrown by receiver");
    throw ex;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::hello[_answer]
  }

  int16_t
  do_my_foo_exec_i::rw_attrib_g_s ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g_s[getter]
    ExceptionT::InternalError ex (42, "Rec.Exc.get_rw_attrib_g_s",
                                      "thrown by receiver");
    throw ex;
    return this->rw_attrib_g_s_;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g_s[getter]
  }

  void
  do_my_foo_exec_i::rw_attrib_g_s (
      int16_t rw_attrib_g_s)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g_s[setter]
    if (rw_attrib_g_s == 0)
    {
      //throw internal excep
      ExceptionT::InternalError ex (42, "Rec.Exc.set_rw_attrib_g_s",
                                         "thrown by receiver");
      throw ex;
    }
    else
    {
      this->rw_attrib_g_s_ = rw_attrib_g_s;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g_s[setter]
  }

  int16_t
  do_my_foo_exec_i::rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib[getter]
    ExceptionT::InternalError ex (42, "Rec.Exc.get_rw_attrib",
                                      "thrown by receiver");
    throw ex;
    return this->rw_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib[getter]
  }

  void
  do_my_foo_exec_i::rw_attrib (
      int16_t rw_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib[setter]
    ExceptionT::InternalError ex (42, "Rec.Exc.rw_attrib",
                                      "thrown by receiver");
    throw ex;
    this->rw_attrib_ = rw_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib[setter]
  }

  int16_t
  do_my_foo_exec_i::rw_attrib_g ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g[getter]
    ExceptionT::InternalError ex (42, "Rec.Exc.get_rw_attrib_g",
                                      "thrown by receiver");
    throw ex;
    return this->rw_attrib_g_;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g[getter]
  }

  void
  do_my_foo_exec_i::rw_attrib_g (
      int16_t rw_attrib_g)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g[setter]
    ExceptionT::InternalError ex (42, "Rec.Exc.set_rw_attrib_g",
                                      "thrown by receiver");
    throw ex;
    this->rw_attrib_g_ = rw_attrib_g;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_g[setter]
  }

  int16_t
  do_my_foo_exec_i::rw_attrib_s ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_s[getter]
    ExceptionT::InternalError ex (42, "Rec.Exc.get_rw_attrib_s",
                                      "thrown by receiver");
    throw ex;
    return this->rw_attrib_s_;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_s[getter]
  }

  void
  do_my_foo_exec_i::rw_attrib_s (
      int16_t rw_attrib_s)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_s[setter]
    ExceptionT::InternalError ex (42, "Rec.Exc.set_rw_attrib_s",
                                      "thrown by receiver");
    throw ex;
    this->rw_attrib_s_ = rw_attrib_s;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::rw_attrib_s[setter]
  }

  int16_t
  do_my_foo_exec_i::ro_attrib_r ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::ro_attrib_r[getter]
    ExceptionT::InternalError ex (42, "Rec.Exc.get_ro_attrib_r",
                                      "thrown by receiver");
    throw ex;
    return this->ro_attrib_r_;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::ro_attrib_r[getter]
  }

  int16_t
  do_my_foo_exec_i::ro_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::do_my_foo_exec_i::ro_attrib[getter]
    // this->get_ro_ is always true, so always an exception is thrown.
    ExceptionT::InternalError ex (42, "Rec.Exc.get_ro_attrib",
                                      "thrown by receiver");
    throw ex;
    return this->ro_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::do_my_foo_exec_i::ro_attrib[getter]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::ExceptionT::CCM_MyFoo>::ref_type
  Receiver_exec_i::get_do_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  if (!this->do_my_foo_)
  {
    this->do_my_foo_ = CORBA::make_reference <do_my_foo_exec_i> (this->context_);
  }
  return this->do_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[get_do_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<ExceptionT::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[user_namespace_end_impl]

} // namespace ExceptionT_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : ExceptionT_Receiver_Impl[factory]
extern "C" void
create_ExceptionT_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <ExceptionT_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : ExceptionT_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : exception_t_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
