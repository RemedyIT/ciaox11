// -*- C++ -*-
/*
 * @file    aggregator_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : aggregator_impl.cpp[Header]

#include "aggregator_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[user_global_impl]

namespace App_Aggregator_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_recorder_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[ctor]
  do_recorder_exec_i::do_recorder_exec_i (
    IDL::traits< ::App::CCM_Aggregator_Context>::ref_type context,
    TLocationSet& locations,
    TEnvironmentMap& env_hist,
    TRecordMap& record_hist,
    uint32_t delay)
    : context_ (std::move(context))
    , locations_ (locations)
    , env_history_ (env_hist)
    , record_history_ (record_hist)
    , delay_ (delay)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[ctor]

  do_recorder_exec_i::~do_recorder_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i[user_private_ops]


  /** Operations and attributes from do_recorder */

  void
  do_recorder_exec_i::submit_environment_data (
      const ::Data::Environment& envdata)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i::submit_environment_data[_envdata]
    CIAOX11_TEST_DEBUG << "do_recorder_exec_i::submit_environment_data" << std::endl;
    this->locations_.insert (envdata.location ());
    this->env_history_[envdata.location ()].push_back (envdata);
    this->env_count_++;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i::submit_environment_data[_envdata]
  }

  void
  do_recorder_exec_i::submit_record_data (
      const ::Data::Record& recdata)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_recorder_exec_i::submit_record_data[_recdata]
    CIAOX11_TEST_DEBUG << "do_recorder_exec_i::submit_record_data" << std::endl;
    this->locations_.insert (recdata.location ());
    this->record_history_[recdata.location ()].push_back (recdata);
    this->record_count_++;

    if (this->delay_)
    {
      CIAOX11_TEST_DEBUG << "do_recorder_exec_i::submit_record_data - delay=" << this->delay_  << std::endl;
      std::this_thread::sleep_for (std::chrono::milliseconds (this->delay_));
    }

    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_recorder_exec_i::submit_record_data[_recdata]
  }
  /**
   * Facet Executor Implementation Class : do_collector_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[ctor]
  do_collector_exec_i::do_collector_exec_i (
      IDL::traits< ::App::CCM_Aggregator_Context>::ref_type context,
      TLocationSet& locations,
      TEnvironmentMap& env_hist,
      TRecordMap& record_hist,
      uint32_t delay)
      : context_ (std::move(context))
      , locations_ (locations)
      , env_history_ (env_hist)
      , record_history_ (record_hist)
      , delay_ (delay)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[ctor]

  do_collector_exec_i::~do_collector_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i[user_private_ops]


  /** Operations and attributes from do_collector */

  void
  do_collector_exec_i::get_result (
      ::Data::ResultList& result_data)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::do_collector_exec_i::get_result[_result_data]
    CIAOX11_TEST_DEBUG << "do_collector_exec_i::get_result" << std::endl;
    if (this->delay_)
      // simulate more lengthy aggregation
      std::this_thread::sleep_for (std::chrono::milliseconds (this->delay_));

    for (const std::string& loc : this->locations_)
    {
      ::Data::Result result {};
      result.location (loc);
      if (this->env_history_.find (loc) != this->env_history_.end ())
      {
        uint32_t c {};
        for (const ::Data::Environment& envdata : this->env_history_[loc])
        {
          result.avg_temperature () += envdata.temperature ();
          result.avg_pressure () += envdata.pressure ();
          result.avg_humidity () += envdata.humidity ();
          ++c;
        }
        result.avg_temperature () = result.avg_temperature () / c;
        result.avg_pressure () = result.avg_pressure () / c;
        result.avg_humidity () = result.avg_humidity () / c;
      }
      result.record_history (this->record_history_[loc]);

      result_data.push_back (std::move (result));
    }
    this->locations_.clear ();
    this->env_history_.clear ();
    this->record_history_.clear ();
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::do_collector_exec_i::get_result[_result_data]
  }

  /**
   * Component Executor Implementation Class : Aggregator_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[ctor]
  Aggregator_exec_i::Aggregator_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[ctor]

  Aggregator_exec_i::~Aggregator_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[user_private_ops]

  /** Session component operations */
  void Aggregator_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[configuration_complete]
  }

  void Aggregator_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "App::Aggregator(" << this << "): activated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[ccm_activate]
  }

  void Aggregator_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[ccm_passivate]
    if (this->get_do_recorder ())
    {
      IDL::traits<do_recorder_exec_i>::ref_type recorder_exec =
          IDL::traits<do_recorder_exec_i>::narrow (this->do_recorder_);
      CIAOX11_TEST_INFO << "App::Aggregator(" << this << "): "
                        << "captured " << recorder_exec->environment_count () << " Environment messages"
                        << " and " << recorder_exec->record_count () << " Record messages" << std::endl;

    }
    CIAOX11_TEST_INFO << "App::Aggregator(" << this << "): passivated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[ccm_passivate]
  }

  void Aggregator_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[ccm_remove]
  }

  IDL::traits< ::API::CCM_Recorder>::ref_type
  Aggregator_exec_i::get_do_recorder ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[get_do_recorder]
    if (!this->do_recorder_)
    {
      this->do_recorder_ =
          CORBA::make_reference <do_recorder_exec_i> (
              this->context_,
              this->locations_,
              this->env_history_,
              this->record_history_,
              this->record_delay_);
    }
    return this->do_recorder_;
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[get_do_recorder]
  }

  IDL::traits< ::API::CCM_Collector>::ref_type
  Aggregator_exec_i::get_do_collector ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[get_do_collector]
    if (!this->do_collector_)
    {
      this->do_collector_ =
          CORBA::make_reference <do_collector_exec_i> (
              this->context_,
              this->locations_,
              this->env_history_,
              this->record_history_,
              this->collect_delay_);
    }
    return this->do_collector_;
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[get_do_collector]
  }


  uint32_t
  Aggregator_exec_i::record_delay ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i::record_delay[getter]
    return this->record_delay_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i::record_delay[getter]
  }

  void
  Aggregator_exec_i::record_delay (
      uint32_t record_delay)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i::record_delay[setter]
    this->record_delay_ = record_delay;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i::record_delay[setter]
  }

  uint32_t
  Aggregator_exec_i::collect_delay ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i::collect_delay[getter]
    return this->collect_delay_;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i::collect_delay[getter]
  }

  void
  Aggregator_exec_i::collect_delay (
      uint32_t collect_delay)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i::collect_delay[setter]
    this->collect_delay_ = collect_delay;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i::collect_delay[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Aggregator_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl::Aggregator_exec_i[set_session_context]
    this->context_ = IDL::traits< ::App::CCM_Aggregator_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl::Aggregator_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[user_namespace_end_impl]

} // namespace App_Aggregator_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Aggregator_Impl[factory]
extern "C" void
create_App_Aggregator_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <App_Aggregator_Impl::Aggregator_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : App_Aggregator_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : aggregator_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
