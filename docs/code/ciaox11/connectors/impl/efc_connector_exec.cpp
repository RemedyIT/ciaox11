/**
 * @file    efc_connector_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : efc_connector_impl.cpp[Header]

#include "efc_connector_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[user_global_impl]

namespace EFC_FooConnector_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : request_handler_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[ctor]
  request_handler_exec_i::request_handler_exec_i (
    IDL::traits< ::EFC::CCM_FooConnector_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[ctor]

  request_handler_exec_i::~request_handler_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[user_private_ops]


  /** Operations and attributes from request_handler */

  bool
  request_handler_exec_i::submit (
      const ::EFC::FooRequest& request)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i::submit[_request]
    X11_UNUSED_ARG(request);
    return {};
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i::submit[_request]
  }

  /**
   * Component Executor Implementation Class : FooConnector_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[ctor]
  FooConnector_exec_i::FooConnector_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[ctor]

  FooConnector_exec_i::~FooConnector_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[user_private_ops]

  /** Session component operations */
  void FooConnector_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[configuration_complete]
  }

  void FooConnector_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[ccm_activate]
  }

  void FooConnector_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[ccm_passivate]
  }

  void FooConnector_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[ccm_remove]
  }

  IDL::traits< ::EFC::CCM_FooHandler>::ref_type
  FooConnector_exec_i::get_request_handler ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[get_request_handler]
    if (!this->request_handler_)
    {
      this->request_handler_ = IDL::traits< ::EFC::CCM_FooHandler>::make_reference <request_handler_exec_i> (this->context_);
    }
    return this->request_handler_;
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[get_request_handler]
  }


  std::string
  FooConnector_exec_i::service_specification ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i::service_specification[getter]
    return this->service_specification_;
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i::service_specification[getter]
  }

  void
  FooConnector_exec_i::service_specification (
      const std::string& service_specification)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i::service_specification[setter]
    this->service_specification_ = service_specification;
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i::service_specification[setter]
  }

  /// Operations from Components::SessionComponent
  void
  FooConnector_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[set_session_context]
    this->context_ = IDL::traits< ::EFC::CCM_FooConnector_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[user_namespace_end_impl]

} // namespace EFC_FooConnector_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[factory]
extern "C" void
create_EFC_FooConnector_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = IDL::traits< ::EFC::CCM_FooConnector>::make_reference <EFC_FooConnector_Impl::FooConnector_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : efc_connector_impl.cpp[Footer]
// Your footer (code) here
