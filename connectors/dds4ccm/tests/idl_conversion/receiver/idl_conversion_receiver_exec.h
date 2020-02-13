// -*- C++ -*-
/**
 * @file    idl_conversion_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the IDL conversion test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_IDL_CONVERSION_RECEIVER_EXEC_H_JFAIJADD_INCLUDED__
#define __RIDL_IDL_CONVERSION_RECEIVER_EXEC_H_JFAIJADD_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : idl_conversion_receiver_impl.h[Header]

#pragma once

#include "idl_conversion_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_receiver_impl.h[user_includes]
#include <atomic>
//@@{__RIDL_REGEN_MARKER__} - END : idl_conversion_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : idl_conversion_receiver_impl.h[user_global_decl]

/// Namespace for implementation of IDL_Conversion_Test::Receiver component
namespace IDL_Conversion_Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_out_data_listener facet
  class info_out_data_listener_exec_i final
    : public IDL::traits< ::Example::IDLConversionTestConnector::CCM_Listener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_data_listener_exec_i (
      IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context,
      std::atomic_ulong &samples_received);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_out_data_listener_exec_i ();

    /** @name Operations from ::Example::IDLConversionTestConnector::CCM_Listener */
    //@{

    virtual
    void
    on_one_data (
        const ::Example::IDLConversionMessage& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    virtual
    void
    on_many_data (
        const ::Example::IDLConversionMessageSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_members]
    std::atomic_ulong &samples_received_;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
    void check_datum (const ::Example::IDLConversionMessage& datum);
    void check_b31_array (const std::array< Example::B31, 2 > &to_check, int32_t iter);
    void check_standard_types (const ::Example::IDLConversionMessage& datum);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_status facet
  class info_out_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_status_exec_i (
      IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[ctor]

    /// Destructor
    virtual ~info_out_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::IDL_Conversion_Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_out_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::Example::IDLConversionTestConnector::CCM_Listener>::ref_type get_info_out_data_listener () override;
    /// Factory method and getter for the info_out_status facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_out_status () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::Example::IDLConversionTestConnector::CCM_Listener>::ref_type info_out_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_out_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_members]
    std::atomic_ulong samples_received_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_namespace_end_decl]

} // namespace IDL_Conversion_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_IDL_Conversion_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_receiver_impl.h[Footer]

#endif /* __RIDL_IDL_CONVERSION_RECEIVER_EXEC_H_HCDHFCJD_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
