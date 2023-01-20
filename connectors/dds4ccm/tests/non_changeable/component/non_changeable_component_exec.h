// -*- C++ -*-
/**
 * @file    non_changeable_component_exec.h
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_NON_CHANGEABLE_COMPONENT_EXEC_H_EJCEACGJ_INCLUDED__
#define __RIDL_NON_CHANGEABLE_COMPONENT_EXEC_H_EJCEACGJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : non_changeable_component_impl.h[Header]

#pragma once

#include "non_changeable_componentEC.h"

#include /**/ "nonchangeablecomponent_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : non_changeable_component_impl.h[user_includes]
#include "commonSEEC.h"
//@@{__RIDL_REGEN_MARKER__} - END : non_changeable_component_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : non_changeable_component_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : non_changeable_component_impl.h[user_global_decl]

/// Namespace for implementation of NonChangeableComponent component
namespace NonChangeableComponent_Impl
{
  /// Forward declarations
  class NonChangeableComponent_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[user_namespace_decl]


  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
        IDL::traits< CCM_NonChangeableComponent_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[ctor]

    /// Destructor
    ~info_get_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    void
    on_requested_deadline_missed (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_sample_lost (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_NonChangeableComponent_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : NonChangeableComponent_exec_i
  class NonChangeableComponent_exec_i final
    : public virtual IDL::traits< CCM_NonChangeableComponent>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ctor]
    /// Constructor
    NonChangeableComponent_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ctor]
    /// Destructor
    ~NonChangeableComponent_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_status () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_NonChangeableComponent_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_private_ops]
    bool test_qos_profile (IDL::traits<::CommonTestConnector::CCM_DDS_Event>::ref_type conn);
    bool test_filter (IDL::traits<::CommonTestConnector::CCM_DDS_Event>::ref_type conn);
    bool test_domain_id (IDL::traits<::CommonTestConnector::CCM_DDS_Event>::ref_type conn);
    bool test_topic_name (IDL::traits<::CommonTestConnector::CCM_DDS_Event>::ref_type conn);
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    NonChangeableComponent_exec_i(const NonChangeableComponent_exec_i&) = delete;
    NonChangeableComponent_exec_i(NonChangeableComponent_exec_i&&) = delete;
    NonChangeableComponent_exec_i& operator=(const NonChangeableComponent_exec_i&) = delete;
    NonChangeableComponent_exec_i& operator=(NonChangeableComponent_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[user_namespace_end_decl]

} // namespace NonChangeableComponent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[factory]
extern "C" NONCHANGEABLECOMPONENT_EXEC_Export  void
create_NonChangeableComponent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : non_changeable_component_impl.h[Footer]

#endif /* __RIDL_NON_CHANGEABLE_COMPONENT_EXEC_H_EJCEACGJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
