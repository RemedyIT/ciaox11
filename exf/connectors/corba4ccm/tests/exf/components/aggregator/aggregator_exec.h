// -*- C++ -*-
/*
 * @file    aggregator_exec.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_AGGREGATOR_EXEC_H_EEIFEBEJ_INCLUDED__
#define __RIDL_AGGREGATOR_EXEC_H_EEIFEBEJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : aggregator_impl.h[Header]

#pragma once

#include "aggregatorEC.h"

#include /**/ "exftest_aggregator_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : aggregator_impl.h[user_includes]
#include <vector>
#include <map>
#include <set>
#include <random>
//@@{__RIDL_REGEN_MARKER__} - END : aggregator_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : aggregator_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : aggregator_impl.h[user_global_decl]

/// Namespace for implementation of App::Aggregator component
namespace App_Aggregator_Impl
{
  /// Forward declarations
  class Aggregator_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[user_namespace_decl]
  typedef std::set<std::string> TLocationSet;
  typedef std::vector< ::Data::Environment> TEnvironmenList;
  typedef std::map<std::string, TEnvironmenList> TEnvironmentMap;
  typedef std::vector< ::Data::Record> TRecordList;
  typedef std::map<std::string, TRecordList> TRecordMap;
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[user_namespace_decl]


  /// Executor implementation class for do_recorder facet
  class do_recorder_exec_i final
    : public IDL::traits<::API::CCM_Recorder>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_recorder_exec_i (
        IDL::traits<::App::CCM_Aggregator_Context>::ref_type context,
        TLocationSet& locations,
        TEnvironmentMap& env_hist,
        TRecordMap& record_hist,
        uint32_t delay);
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[ctor]

    /// Destructor
    ~do_recorder_exec_i () override;

    /** @name Operations from ::API::CCM_Recorder */
    //@{

    void
    submit_environment_data (
        const ::Data::Environment& envdata) override;

    void
    submit_record_data (
        const ::Data::Record& recdata) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[user_public_ops]
    uint64_t environment_count () { return this->env_count_; }
    uint64_t record_count () { return this->record_count_; }
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::App::CCM_Aggregator_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[user_members]
    TLocationSet& locations_;
    TEnvironmentMap& env_history_;
    TRecordMap& record_history_;
    uint64_t env_count_ {};
    uint64_t record_count_ {};
    uint32_t delay_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for do_collector facet
  class do_collector_exec_i final
    : public IDL::traits<::API::CCM_Collector>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_collector_exec_i (
        IDL::traits<::App::CCM_Aggregator_Context>::ref_type context,
        TLocationSet& locations,
        TEnvironmentMap& env_hist,
        TRecordMap& record_hist,
        uint32_t delay);
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[ctor]

    /// Destructor
    ~do_collector_exec_i () override;

    /** @name Operations from ::API::CCM_Collector */
    //@{

    void
    get_result (
        ::Data::ResultList& result_data) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::App::CCM_Aggregator_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[user_members]
    TLocationSet &locations_;
    TEnvironmentMap& env_history_;
    TRecordMap& record_history_;
    bool delay_ {};
    std::default_random_engine dre_;
    std::uniform_int_distribution<uint32_t> uniform_dist_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Aggregator_exec_i
  class Aggregator_exec_i final
    : public virtual IDL::traits<::App::CCM_Aggregator>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[ctor]
    /// Constructor
    Aggregator_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[ctor]
    /// Destructor
    ~Aggregator_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_recorder facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::API::CCM_Recorder>::ref_type get_do_recorder () override;
    /// Factory method and getter for the do_collector facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::API::CCM_Collector>::ref_type get_do_collector () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute record_delay
    uint32_t record_delay () override;
    void record_delay (uint32_t record_delay) override;

    /// Attribute collect_delay
    uint32_t collect_delay () override;
    void collect_delay (uint32_t collect_delay) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::App::CCM_Aggregator_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of record_delay attribute
    uint32_t record_delay_{};
    /// Class member storing value of collect_delay attribute
    uint32_t collect_delay_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::API::CCM_Recorder>::ref_type do_recorder_;
    IDL::traits<::API::CCM_Collector>::ref_type do_collector_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[user_members]
    TLocationSet locations_;
    TEnvironmentMap env_history_;
    TRecordMap record_history_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Aggregator_exec_i(const Aggregator_exec_i&) = delete;
    Aggregator_exec_i(Aggregator_exec_i&&) = delete;
    Aggregator_exec_i& operator=(const Aggregator_exec_i&) = delete;
    Aggregator_exec_i& operator=(Aggregator_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[user_namespace_end_decl]

} // namespace App_Aggregator_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[factory]
extern "C" EXFTEST_AGGREGATOR_EXEC_Export  void
create_App_Aggregator_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : aggregator_impl.h[Footer]

#endif /* __RIDL_AGGREGATOR_EXEC_H_EEIFEBEJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
