// -*- C++ -*-
/*
 * @file    analyzer_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : analyzer_impl.cpp[Header]

#include "analyzer_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <iomanip>
#include <sstream>
#include <algorithm>
//@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[user_global_impl]

namespace App_Analyzer_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[user_namespace_impl]
  //============================================================
  // Analyzer trigger callback
  //============================================================
  class TT_Analyzer
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Analyzer (IDL::traits< ::App::CCM_Analyzer_Context>::ref_type context)
      : context_ (std::move(context))
    {
    }

    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

    uint64_t result_count () const
    { return this->result_count_; }

    void passivate ()
    { this->passivated_ = true; }

  private:
    IDL::traits< ::App::CCM_Analyzer_Context>::ref_type context_;
    uint64_t result_count_ {};
    bool passivated_ {};
  };

  void
  TT_Analyzer::on_trigger (
      IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    CIAOX11_TEST_DEBUG << "> TT_Analyzer::on_trigger - timer[" << timer->id ()
                       << "] @ " << time.sec () << "."
                       << std::right << std::setfill('0') << std::setw(9)
                       << time.nanosec ()
                       << " #" << round << std::endl;

    if (this->passivated_)
      return;

    ::Data::ResultList result_totals;

    for (const App::CCM_Analyzer::my_collectorsConnection& col :
           this->context_->get_connections_my_collectors())
    {
      try
      {
        ::Data::ResultList results;

        col.objref ()->get_result (results);

        this->result_count_ += results.size ();

        result_totals.reserve(result_totals.size() + results.size ());
        std::move(results.begin(), results.end(), std::inserter(result_totals, result_totals.end()));
      }
      catch (const CORBA::TRANSIENT&)
      {
        // ignore in non-active state when not using ExF
        if (this->passivated_ == false)
        {
          // for now always ignore
          // CIAOX11_TEST_ERROR << "App::Analyzer: caught exception from get_result [" << ex.what () << "]" << std::endl;
        }
      }
      catch (const std::exception& ex)
      {
        CIAOX11_TEST_ERROR << "App::Analyzer: caught exception from get_result [" << ex << "]" << std::endl;
      }
    }

    std::ostringstream report;
    report << "Results for " << result_totals.size () << " locations:" << std::endl;
    for (const ::Data::Result& result : result_totals)
    {
      report << "\t @ " << result.location ()
             << "(temperature=" << result.avg_temperature ()
             << ",pressure=" << result.avg_temperature ()
             << ",humidity=" << result.avg_humidity () << ")" << std::endl;
      if (!result.record_history ().empty ())
      {
        auto minmax_pairA = std::minmax_element (
            result.record_history ().begin (),
            result.record_history ().end (),
            [](const ::Data::Record& a, const ::Data::Record& b) { return a.sensorA () < b.sensorA (); });
        auto minmax_pairB = std::minmax_element (
            result.record_history ().begin (),
            result.record_history ().end (),
            [](const ::Data::Record& a, const ::Data::Record& b) { return a.sensorB () < b.sensorB (); });

        report << "\t\t sensor A = " << minmax_pairA.first->sensorA () << "-" << minmax_pairA.second->sensorA () << std::endl;
        report << "\t\t sensor B = " << minmax_pairB.first->sensorB () << "-" << minmax_pairB.second->sensorB () << std::endl;
      }
    }

    try
    {
      this->context_->get_connection_my_presenter ()->present_info (report.str ());
    }
    catch (const CORBA::TRANSIENT&)
    {
      // ignore in non-active state when not using ExF
      if (this->passivated_ == false)
      {
        // for now always ignore
        // CIAOX11_TEST_ERROR << "App::Analyzer: caught exception [" << ex.what () << "]" << std::endl;
      }
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_ERROR << "App::Analyzer: caught exception from present_info [" << ex << "]" << std::endl;
    }
    CIAOX11_TEST_DEBUG << "< TT_Analyzer::on_trigger - timer[" << timer->id ()
                       << "] @ " << time.sec () << "."
                       << std::right << std::setfill('0') << std::setw(9)
                       << time.nanosec ()
                       << " #" << round << std::endl;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Analyzer_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[ctor]
  Analyzer_exec_i::Analyzer_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[ctor]

  Analyzer_exec_i::~Analyzer_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[user_private_ops]

  /** Session component operations */
  void Analyzer_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[configuration_complete]
  }

  void Analyzer_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[ccm_activate]
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_ana = this->context_->get_connection_tt_analyzer ();
    this->th_ana_ = CORBA::make_reference<TT_Analyzer> (this->context_);
    this->tm_ana_ = tt_ana->schedule_repeated_trigger (
        this->th_ana_,
        CCM_TT::TT_Duration (0, 500000000),  // 500ms
        CCM_TT::TT_Duration (0, 500000000),  // 500ms
        0);

    CIAOX11_TEST_INFO << "App::Analyzer: activated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[ccm_activate]
  }

  void Analyzer_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[ccm_passivate]
    IDL::traits<TT_Analyzer>::narrow (this->th_ana_)->passivate ();
    if (this->tm_ana_)
    {
      this->tm_ana_->cancel ();
    }

    CIAOX11_TEST_INFO << "App::Analyzer: " <<
        IDL::traits<TT_Analyzer>::narrow (this->th_ana_)->result_count () <<
        " results collected" << std::endl;

    CIAOX11_TEST_INFO << "App::Analyzer: passivated component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[ccm_passivate]
  }

  void Analyzer_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "App::Analyzer: removing  component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Analyzer_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl::Analyzer_exec_i[set_session_context]
    this->context_ = IDL::traits< ::App::CCM_Analyzer_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl::Analyzer_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[user_namespace_end_impl]

} // namespace App_Analyzer_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : App_Analyzer_Impl[factory]
extern "C" void
create_App_Analyzer_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <App_Analyzer_Impl::Analyzer_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : App_Analyzer_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : analyzer_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
