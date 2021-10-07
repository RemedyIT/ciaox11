  /*
   * Your header here.
   */
#ifndef __RIDL_EFC_CONNECTOR_EXEC_H_IDJIDJIF_INCLUDED__
#define __RIDL_EFC_CONNECTOR_EXEC_H_IDJIDJIF_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : efc_connector_impl.h[Header]

#pragma once

#include "efc_connectorEC.h"

#include /**/ "efcc_conn_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : efc_connector_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : efc_connector_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : efc_connector_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : efc_connector_impl.h[user_global_decl]

/// Namespace for implementation of EFC::FooConnector component
namespace EFC_FooConnector_Impl
{
  /// Forward declarations
  class FooConnector_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[user_namespace_decl]


  /// Executor implementation class for request_handler facet
  class request_handler_exec_i final
    : public IDL::traits< ::EFC::CCM_FooHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    request_handler_exec_i (
        IDL::traits< ::EFC::CCM_FooConnector_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[ctor]

    /// Destructor
    ~request_handler_exec_i () override;

    /** @name Operations from ::EFC::CCM_FooHandler */
    //@{

    bool
    submit (
        const ::EFC::FooRequest& request) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::EFC::CCM_FooConnector_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::request_handler_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::request_handler_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : FooConnector_exec_i
  class FooConnector_exec_i final
    : public virtual IDL::traits< ::EFC::CCM_FooConnector>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[ctor]
    /// Constructor
    FooConnector_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[ctor]
    /// Destructor
    ~FooConnector_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the request_handler facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::EFC::CCM_FooHandler>::ref_type get_request_handler () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute service_specification

    std::string
    service_specification () override;

    void
    service_specification (const std::string& service_specification) override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::EFC::CCM_FooConnector_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of service_specification attribute
    std::string service_specification_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::EFC::CCM_FooHandler>::ref_type request_handler_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl::FooConnector_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl::FooConnector_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    FooConnector_exec_i(const FooConnector_exec_i&) = delete;
    FooConnector_exec_i(FooConnector_exec_i&&) = delete;
    FooConnector_exec_i& operator=(const FooConnector_exec_i&) = delete;
    FooConnector_exec_i& operator=(FooConnector_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[user_namespace_end_decl]

} // namespace EFC_FooConnector_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : EFC_FooConnector_Impl[factory]
extern "C" EFCC_CONN_EXEC_Export  void
create_EFC_FooConnector_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : EFC_FooConnector_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : efc_connector_impl.h[Footer]

#endif /* __RIDL_EFC_CONNECTOR_EXEC_H_IDJIDJIF_INCLUDED__ */

// Your footer (code) here
