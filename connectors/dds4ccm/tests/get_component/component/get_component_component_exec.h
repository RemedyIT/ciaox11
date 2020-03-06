// -*- C++ -*-
/**
 * @file    get_component_component_exec.h
 * @author  Marcel Smit
 *
 * @brief   Component implementation.
 *
 * Testing the _get_component method.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_GET_COMPONENT_COMPONENT_EXEC_H_HFHIAECF_INCLUDED__
#define __RIDL_GET_COMPONENT_COMPONENT_EXEC_H_HFHIAECF_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : get_component_component_impl.h[Header]

#pragma once

#include "get_component_componentEC.h"

#include /**/ "getcomponentcomponent_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : get_component_component_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : get_component_component_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : get_component_component_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : get_component_component_impl.h[user_global_decl]

/// Namespace for implementation of GetComponentComponent component
namespace GetComponentComponent_Impl
{
  /// Forward declarations
  class GetComponentComponent_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[user_namespace_decl]


  /// Executor implementation class for info_listen_data_listener facet
  class info_listen_data_listener_exec_i final
    : public IDL::traits< ::CommonTestConnector::CCM_Listener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_listen_data_listener_exec_i (
      IDL::traits<CCM_GetComponentComponent_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_listen_data_listener_exec_i ();

    /** @name Operations from ::CommonTestConnector::CCM_Listener */
    //@{

    void
    on_one_data (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_data (
        const ::CommonTestMessageSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_GetComponentComponent_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_listen_status facet
  class info_listen_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_listen_status_exec_i (
      IDL::traits<CCM_GetComponentComponent_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[ctor]

    /// Destructor
    virtual ~info_listen_status_exec_i ();

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_GetComponentComponent_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
      IDL::traits<CCM_GetComponentComponent_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[ctor]

    /// Destructor
    virtual ~info_get_status_exec_i ();

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_GetComponentComponent_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : GetComponentComponent_exec_i
  class GetComponentComponent_exec_i final
    : public virtual IDL::traits< CCM_GetComponentComponent>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[ctor]
    /// Constructor
    GetComponentComponent_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[ctor]
    /// Destructor
    virtual ~GetComponentComponent_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_listen_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type get_info_listen_data_listener () override;
    /// Factory method and getter for the info_listen_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_listen_status () override;
    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_status () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute act_as_sender

    bool
    act_as_sender () override;

    void
    act_as_sender (bool act_as_sender) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_GetComponentComponent_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of act_as_sender attribute
    bool act_as_sender_ {};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type info_listen_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_listen_status_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_private_ops]
    void test_writer ();
    void test_getter ();
    void test_listener ();
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    GetComponentComponent_exec_i(const GetComponentComponent_exec_i&) = delete;
    GetComponentComponent_exec_i(GetComponentComponent_exec_i&&) = delete;
    GetComponentComponent_exec_i& operator=(const GetComponentComponent_exec_i&) = delete;
    GetComponentComponent_exec_i& operator=(GetComponentComponent_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[user_namespace_end_decl]

} // namespace GetComponentComponent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[factory]
extern "C" GETCOMPONENTCOMPONENT_EXEC_Export  void
create_GetComponentComponent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : get_component_component_impl.h[Footer]

#endif /* __RIDL_GET_COMPONENT_COMPONENT_EXEC_H_HFHIAECF_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
