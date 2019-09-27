// -*- C++ -*-
/**
 * @file    updater_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the updater test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : updater_receiver_impl.h[Header]

#pragma once

#include "updater_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_receiver_impl.h[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : updater_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : updater_receiver_impl.h[user_global_decl]

/// Namespace for implementation of UpdaterModule::Receiver component
namespace UpdaterModule_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_out_one_by_one_data_listener facet
  class info_out_one_by_one_data_listener_exec_i final
    : public IDL::traits< ::CommonTestConnector::CCM_StateListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_one_by_one_data_listener_exec_i (
      IDL::traits<UpdaterModule::CCM_Receiver_Context>::ref_type context,
      std::atomic_ushort &errors_found,
      std::atomic_ushort &obo_on_creation_received,
      std::atomic_ushort &obo_on_one_update_received,
      std::atomic_ushort &obo_on_many_updates_received,
      std::atomic_ushort &obo_on_deletion_received,
      atomic_thread_id &obo_thread_id);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_out_one_by_one_data_listener_exec_i ();

    /** @name Operations from ::CommonTestConnector::CCM_StateListener */
    //@{

    virtual
    void
    on_creation (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    virtual
    void
    on_one_update (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    virtual
    void
    on_many_updates (
        const ::CommonTestMessageSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;

    virtual
    void
    on_deletion (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::UpdaterModule::CCM_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_members]
    std::atomic_ushort &errors_found_;
    std::atomic_ushort &obo_on_creation_received_;
    std::atomic_ushort &obo_on_one_update_received_;
    std::atomic_ushort &obo_on_many_updates_received_;
    std::atomic_ushort &obo_on_deletion_received_;

    atomic_thread_id &obo_thread_id_;
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_one_by_one_status facet
  class info_out_one_by_one_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_one_by_one_status_exec_i (
        IDL::traits< UpdaterModule::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[ctor]

    /// Destructor
    virtual ~info_out_one_by_one_status_exec_i ();

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    virtual
    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    virtual
    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::UpdaterModule::CCM_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_one_by_one_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_many_by_many_data_listener facet
  class info_out_many_by_many_data_listener_exec_i final
    : public IDL::traits< ::CommonTestConnector::CCM_StateListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_many_by_many_data_listener_exec_i (
      IDL::traits<UpdaterModule::CCM_Receiver_Context>::ref_type context,
      std::atomic_ushort &errors_found,
      std::atomic_ushort &mbm_on_creation_received,
      std::atomic_ushort &mbm_on_one_update_received,
      std::atomic_ushort &mbm_on_many_updates_received,
      std::atomic_ushort &mbm_on_deletion_received,
      atomic_thread_id &mbm_thread_id);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_out_many_by_many_data_listener_exec_i ();

    /** @name Operations from ::CommonTestConnector::CCM_StateListener */
    //@{

    virtual
    void
    on_creation (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    virtual
    void
    on_one_update (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    virtual
    void
    on_many_updates (
        const ::CommonTestMessageSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;

    virtual
    void
    on_deletion (
        const ::CommonTestMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::UpdaterModule::CCM_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_members]
    std::atomic_ushort &errors_found_;
    std::atomic_ushort &mbm_on_creation_received_;
    std::atomic_ushort &mbm_on_one_update_received_;
    std::atomic_ushort &mbm_on_many_updates_received_;
    std::atomic_ushort &mbm_on_deletion_received_;

    atomic_thread_id &mbm_thread_id_;
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_many_by_many_status facet
  class info_out_many_by_many_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_many_by_many_status_exec_i (
        IDL::traits< UpdaterModule::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[ctor]

    /// Destructor
    virtual ~info_out_many_by_many_status_exec_i ();

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    virtual
    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    virtual
    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::UpdaterModule::CCM_Receiver_Context >::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::info_out_many_by_many_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::UpdaterModule::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_out_one_by_one_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CommonTestConnector::CCM_StateListener >::ref_type get_info_out_one_by_one_data_listener () override;
    /// Factory method and getter for the info_out_one_by_one_status facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type get_info_out_one_by_one_status () override;
    /// Factory method and getter for the info_out_many_by_many_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CommonTestConnector::CCM_StateListener >::ref_type get_info_out_many_by_many_data_listener () override;
    /// Factory method and getter for the info_out_many_by_many_status facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type get_info_out_many_by_many_status () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    virtual void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    virtual void configuration_complete () override;

    /// Component state change method to activated state
    virtual void ccm_activate () override;

    /// Component state change method to passivated state
    virtual void ccm_passivate () override;

    /// Component state change method to removed state
    virtual void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::UpdaterModule::CCM_Receiver_Context >::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CommonTestConnector::CCM_StateListener >::ref_type info_out_one_by_one_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type info_out_one_by_one_status_;
    IDL::traits< ::CommonTestConnector::CCM_StateListener >::ref_type info_out_many_by_many_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type info_out_many_by_many_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_members]
    std::atomic_ushort errors_found_ {};

    std::atomic_ushort obo_on_creation_received_ {};
    std::atomic_ushort obo_on_one_update_received_ {};
    std::atomic_ushort obo_on_many_updates_received_ {};
    std::atomic_ushort obo_on_deletion_received_ {};

    std::atomic_ushort mbm_on_creation_received_ {};
    std::atomic_ushort mbm_on_one_update_received_ {};
    std::atomic_ushort mbm_on_many_updates_received_ {};
    std::atomic_ushort mbm_on_deletion_received_ {};

    // Just one thread id needed this the distinction between on_creation, on_one/many_update(s),
    // and on_deletion comes after the context switch.
    atomic_thread_id obo_thread_id_ {};
    atomic_thread_id mbm_thread_id_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl::Receiver_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Receiver_exec_i(const Receiver_exec_i&) = delete;
    Receiver_exec_i(Receiver_exec_i&&) = delete;
    Receiver_exec_i& operator=(const Receiver_exec_i&) = delete;
    Receiver_exec_i& operator=(Receiver_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[user_namespace_end_decl]

} // namespace UpdaterModule_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UpdaterModule_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_UpdaterModule_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : UpdaterModule_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : updater_receiver_impl.h[Footer]
// Your footer (code) here
// -*- END -*-
