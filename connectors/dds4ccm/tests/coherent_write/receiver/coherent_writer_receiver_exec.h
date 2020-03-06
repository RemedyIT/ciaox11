// -*- C++ -*-
/**
 * @file    coherent_writer_receiver_exec.h
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_COHERENT_WRITER_RECEIVER_EXEC_H_IFJGJIFJ_INCLUDED__
#define __RIDL_COHERENT_WRITER_RECEIVER_EXEC_H_IFJGJIFJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : coherent_writer_receiver_impl.h[Header]

#pragma once

#include "coherent_writer_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : coherent_writer_receiver_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : coherent_writer_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : coherent_writer_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : coherent_writer_receiver_impl.h[user_global_decl]

/// Namespace for implementation of CoherentWriter::Receiver component
namespace CoherentWriter_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
        IDL::traits< CoherentWriter::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[ctor]

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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::CoherentWriter::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for start_reading facet
  class start_reading_exec_i final
    : public IDL::traits< CCM_ReaderStarter>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    start_reading_exec_i (
        IDL::traits< CoherentWriter::CCM_Receiver_Context>::ref_type context,
        IDL::traits< CoherentWriter::CCM_Receiver>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[ctor]

    /// Destructor
    virtual ~start_reading_exec_i ();

    /** @name Operations from CCM_ReaderStarter */
    //@{

    void
    start_read () override;

    void
    start_new_run (
        uint16_t run) override;

    void
    set_reader_properties (
        uint16_t nr_keys,
        uint16_t nr_iterations) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::CoherentWriter::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_members]
    IDL::traits< CoherentWriter::CCM_Receiver>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::start_reading_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::CoherentWriter::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_status () override;
    /// Factory method and getter for the start_reading facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< CCM_ReaderStarter>::ref_type get_start_reading () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute nr_runs

    uint16_t
    nr_runs () override;

    void
    nr_runs (uint16_t nr_runs) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void start_read (uint16_t run);
    void tick ();

    void iterations (int32_t iterations);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::CoherentWriter::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of nr_runs attribute
    uint16_t nr_runs_ {};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_status_;
    IDL::traits< CCM_ReaderStarter>::ref_type start_reading_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_members]
 //   long ticker_id_ { -1 };
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    int32_t iterations_ {};
    uint16_t run_ {};
    int32_t last_iter_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_private_ops]
    void get_all ();
    void read_all ();
    void check_iters (std::string const &test,
      CommonTestMessageSeq const &msgs);
    //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[user_namespace_end_decl]

} // namespace CoherentWriter_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : CoherentWriter_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_CoherentWriter_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : CoherentWriter_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : coherent_writer_receiver_impl.h[Footer]

#endif /* __RIDL_COHERENT_WRITER_RECEIVER_EXEC_H_IFJGJIFJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
