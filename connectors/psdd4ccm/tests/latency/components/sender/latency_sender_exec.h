// -*- C++ -*-
/**
 * @file    latency_sender_exec.h
 * @author  Martin Corino
 *
 * @brief   Sender component implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_LATENCY_SENDER_EXEC_H_HAJHBIAB_INCLUDED__
#define __RIDL_LATENCY_SENDER_EXEC_H_HAJHBIAB_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : latency_sender_impl.h[Header]

#pragma once

#include "latency_senderEC.h"

#include /**/ "latency_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : latency_sender_impl.h[user_includes]
#include <atomic>
//@@{__RIDL_REGEN_MARKER__} - END : latency_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : latency_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : latency_sender_impl.h[user_global_decl]

/// Namespace for implementation of Test::Sender component
namespace Test_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for info_recv facet
  class info_recv_exec_i final
    : public IDL::traits<::Test::LatencyDataConnector::CCM_Listener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_recv_exec_i (
        IDL::traits<::Test::CCM_Sender_Context>::ref_type context,
        IDL::traits<::Test::CCM_Sender>::ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_exec_i[ctor]

    /// Destructor
    ~info_recv_exec_i () override;

    /** @name Operations from ::Test::LatencyDataConnector::CCM_Listener */
    //@{

    void
    on_data (
        ::Test::LatencyDataSeq& data) override;
    //@}

    /** @name Attributes from ::Test::LatencyDataConnector::CCM_Listener */
    //@{
    ::CCM_PSDD::ListenerMode listen_mode () override;
    void listen_mode (::CCM_PSDD::ListenerMode listen_mode) override;
    ::CCM_PSDD::DataCount_t max_data () override;
    void max_data (::CCM_PSDD::DataCount_t max_data) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_exec_i[user_public_ops]
    void shutdown ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Test::CCM_Sender_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Test::LatencyDataConnector::CCM_Listener */
    //@{
    /// Class member storing value of listen_mode attribute
    ::CCM_PSDD::ListenerMode listen_mode_{};
    /// Class member storing value of max_data attribute
    ::CCM_PSDD::DataCount_t max_data_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_exec_i[user_members]
    IDL::traits<::Test::CCM_Sender>::ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::info_recv_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::info_recv_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits<::Test::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_recv facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::Test::LatencyDataConnector::CCM_Listener>::ref_type get_info_recv () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute rate
    uint32_t rate () override;
    void rate (uint32_t rate) override;

    /// Attribute samples
    uint32_t samples () override;
    void samples (uint32_t samples) override;

    /// Attribute sample_size
    uint32_t sample_size () override;
    void sample_size (uint32_t sample_size) override;

    /// Attribute iterations
    uint32_t iterations () override;
    void iterations (uint32_t iterations) override;

    /// Attribute uses_context_switch
    bool uses_context_switch () override;
    void uses_context_switch (bool uses_context_switch) override;

    /// Attribute context_switch_type
    std::string context_switch_type () override;
    void context_switch_type (const std::string& context_switch_type) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_public_ops]
    void check_status ();
    void tick ();
    void start_publishing ();
    void read (Test::LatencyData & instance, uint64_t receive_time);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Test::CCM_Sender_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of rate attribute
    uint32_t rate_{};
    /// Class member storing value of samples attribute
    uint32_t samples_{};
    /// Class member storing value of sample_size attribute
    uint32_t sample_size_{};
    /// Class member storing value of iterations attribute
    uint32_t iterations_{};
    /// Class member storing value of uses_context_switch attribute
    bool uses_context_switch_{};
    /// Class member storing value of context_switch_type attribute
    std::string context_switch_type_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::Test::LatencyDataConnector::CCM_Listener>::ref_type info_recv_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_members]
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_activate_;
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s;
    IDL::traits<CCM_TT::TT_Handler>::ref_type tmh_;
    bool already_publishing_ {};


    IDL::traits<::Test::LatencyDataConnector::Publisher>::ref_type writer_ {};

    uint32_t iteration_nr_ {};
    std::atomic<bool> matched_ {};
    uint64_t tv_total_ {};
    uint64_t tv_max_ {};
    uint64_t tv_min_ {};
    uint16_t count_ {};
    uint16_t number_of_msg_ {};
    std::atomic<bool> received_ {};
    std::atomic<bool> receiving_ {};
    int32_t seq_num_ {};
    double sigma_duration_squared_ {};
    uint64_t start_time_ {};
    uint64_t start_time_test_ {};
    uint64_t end_time_test_ {};

    struct IterationResult
    {
      double tv_avg_ {};
      double sigma_duration_squared_;
      uint64_t tv_max_ {};
      uint64_t tv_min_ {};
      double per50_;
      double per90_;
      double per99_;
      double per9999_;
    };

    Test::LatencyData test_topic_ {};
    std::unique_ptr<uint64_t[]> duration_times_ {};
    std::unique_ptr<IterationResult[]> iteration_results_;
    int32_t _clock_overhead_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_private_ops]
    void start (void);
    void calc_results (void);
    void reset_results (void);
    void init_values (void);
    void calculate_clock_overhead (void);
    void record_time (uint64_t receive_time);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Sender_exec_i(const Sender_exec_i&) = delete;
    Sender_exec_i(Sender_exec_i&&) = delete;
    Sender_exec_i& operator=(const Sender_exec_i&) = delete;
    Sender_exec_i& operator=(Sender_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_end_decl]

} // namespace Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[factory]
extern "C" LATENCY_SENDER_EXEC_Export  void
create_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : latency_sender_impl.h[Footer]

#endif /* __RIDL_LATENCY_SENDER_EXEC_H_HAJHBIAB_INCLUDED__ */

// Your footer (code) here
