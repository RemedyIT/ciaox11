// -*- C++ -*-
/*
 * @file    reporter_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : reporter_impl.cpp[Header]

#include "reporter_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[user_global_impl]

namespace App_Reporter_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_presenter_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[ctor]
  do_presenter_exec_i::do_presenter_exec_i (
    IDL::traits< ::App::CCM_Reporter_Context>::ref_type context)
    : context_ (std::move(context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[ctor]

  do_presenter_exec_i::~do_presenter_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i[user_private_ops]


  /** Operations and attributes from do_presenter */

  void
  do_presenter_exec_i::present_info (
      const std::string& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::do_presenter_exec_i::present_info[_info]
    CIAOX11_TEST_INFO << info << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::do_presenter_exec_i::present_info[_info]
  }

  /**
   * Component Executor Implementation Class : Reporter_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[ctor]
  Reporter_exec_i::Reporter_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[ctor]

  Reporter_exec_i::~Reporter_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[user_private_ops]

  /** Session component operations */
  void Reporter_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[configuration_complete]
  }

  void Reporter_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[ccm_activate]
  }

  void Reporter_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[ccm_passivate]
  }

  void Reporter_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[ccm_remove]
  }

  IDL::traits< ::API::CCM_Presenter>::ref_type
  Reporter_exec_i::get_do_presenter ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[get_do_presenter]
    if (!this->do_presenter_)
    {
      this->do_presenter_ = CORBA::make_reference <do_presenter_exec_i> (this->context_);
    }
    return this->do_presenter_;
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[get_do_presenter]
  }

  /// Operations from Components::SessionComponent
  void
  Reporter_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl::Reporter_exec_i[set_session_context]
    this->context_ = IDL::traits< ::App::CCM_Reporter_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl::Reporter_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[user_namespace_end_impl]

} // namespace App_Reporter_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Reporter_Impl[factory]
extern "C" void
create_App_Reporter_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <App_Reporter_Impl::Reporter_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : App_Reporter_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : reporter_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
