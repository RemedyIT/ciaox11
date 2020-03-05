// -*- C++ -*-
/**
 * @file    subscriber_exec.h
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_SUBSCRIBER_EXEC_H_HECEAEGA_INCLUDED__
#define __RIDL_SUBSCRIBER_EXEC_H_HECEAEGA_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : subscriber_impl.h[Header]

#pragma once

#include "subscriberEC.h"

#include /**/ "subscriber_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : subscriber_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : subscriber_impl.h[user_global_decl]

/// Namespace for implementation of subscriber_comp component
namespace subscriber_comp_Impl
{
  /// Forward declarations
  class subscriber_comp_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[user_namespace_decl]


  /// Executor implementation class for info_out_data_listener facet
  class info_out_data_listener_exec_i final
    : public IDL::traits< ::ShapeTypeInterface::CCM_Listener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_data_listener_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_out_data_listener_exec_i ();

    /** @name Operations from ::ShapeTypeInterface::CCM_Listener */
    //@{

    void
    on_one_data (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_data (
        const ::ShapeTypeSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_status facet
  class info_out_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[ctor]

    /// Destructor
    virtual ~info_out_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_read_status facet
  class info_read_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_read_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[ctor]

    /// Destructor
    virtual ~info_read_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[ctor]

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_state_data_listener facet
  class info_state_data_listener_exec_i final
    : public IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_state_data_listener_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_state_data_listener_exec_i ();

    /** @name Operations from ::ShapeTypeInterface::CCM_StateListener */
    //@{

    void
    on_creation (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_one_update (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_updates (
        const ::ShapeTypeSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;

    void
    on_deletion (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_state_status facet
  class info_state_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_state_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[ctor]

    /// Destructor
    virtual ~info_state_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_2_data_listener facet
  class info_out_2_data_listener_exec_i final
    : public IDL::traits< ::ShapeTypeInterface::CCM_Listener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_2_data_listener_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_out_2_data_listener_exec_i ();

    /** @name Operations from ::ShapeTypeInterface::CCM_Listener */
    //@{

    void
    on_one_data (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_data (
        const ::ShapeTypeSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_out_2_status facet
  class info_out_2_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_out_2_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[ctor]

    /// Destructor
    virtual ~info_out_2_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_out_2_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_out_2_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_read_2_status facet
  class info_read_2_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_read_2_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[ctor]

    /// Destructor
    virtual ~info_read_2_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_read_2_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_read_2_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_get_2_status facet
  class info_get_2_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_2_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[ctor]

    /// Destructor
    virtual ~info_get_2_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_get_2_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_get_2_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_state_2_data_listener facet
  class info_state_2_data_listener_exec_i final
    : public IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_state_2_data_listener_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[ctor]

    /// Destructor
    virtual ~info_state_2_data_listener_exec_i ();

    /** @name Operations from ::ShapeTypeInterface::CCM_StateListener */
    //@{

    void
    on_creation (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_one_update (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;

    void
    on_many_updates (
        const ::ShapeTypeSeq& data,
        const ::CCM_DDS::ReadInfoSeq& infos) override;

    void
    on_deletion (
        const ::ShapeType& datum,
        const ::CCM_DDS::ReadInfo& info) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_data_listener_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for info_state_2_status facet
  class info_state_2_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_state_2_status_exec_i (
        IDL::traits< CCM_subscriber_comp_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[ctor]

    /// Destructor
    virtual ~info_state_2_status_exec_i ();

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::info_state_2_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::info_state_2_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : subscriber_comp_exec_i
  class subscriber_comp_exec_i final
    : public virtual IDL::traits< CCM_subscriber_comp>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[ctor]
    /// Constructor
    subscriber_comp_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[ctor]
    /// Destructor
    virtual ~subscriber_comp_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_out_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::ShapeTypeInterface::CCM_Listener>::ref_type get_info_out_data_listener () override;
    /// Factory method and getter for the info_out_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_out_status () override;
    /// Factory method and getter for the info_read_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_read_status () override;
    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_status () override;
    /// Factory method and getter for the info_state_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::ref_type get_info_state_data_listener () override;
    /// Factory method and getter for the info_state_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_state_status () override;
    /// Factory method and getter for the info_out_2_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::ShapeTypeInterface::CCM_Listener>::ref_type get_info_out_2_data_listener () override;
    /// Factory method and getter for the info_out_2_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_out_2_status () override;
    /// Factory method and getter for the info_read_2_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_read_2_status () override;
    /// Factory method and getter for the info_get_2_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_2_status () override;
    /// Factory method and getter for the info_state_2_data_listener facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::ref_type get_info_state_2_data_listener () override;
    /// Factory method and getter for the info_state_2_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_state_2_status () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< CCM_subscriber_comp_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::ShapeTypeInterface::CCM_Listener>::ref_type info_out_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_out_status_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_read_status_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_status_;
    IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::ref_type info_state_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_state_status_;
    IDL::traits< ::ShapeTypeInterface::CCM_Listener>::ref_type info_out_2_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_out_2_status_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_read_2_status_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_2_status_;
    IDL::traits< ::ShapeTypeInterface::CCM_StateListener>::ref_type info_state_2_data_listener_;
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_state_2_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl::subscriber_comp_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl::subscriber_comp_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    subscriber_comp_exec_i(const subscriber_comp_exec_i&) = delete;
    subscriber_comp_exec_i(subscriber_comp_exec_i&&) = delete;
    subscriber_comp_exec_i& operator=(const subscriber_comp_exec_i&) = delete;
    subscriber_comp_exec_i& operator=(subscriber_comp_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[user_namespace_end_decl]

} // namespace subscriber_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_comp_Impl[factory]
extern "C" SUBSCRIBER_EXEC_Export  void
create_subscriber_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : subscriber_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : subscriber_impl.h[Footer]

#endif /* __RIDL_SUBSCRIBER_EXEC_H_HECEAEGA_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
