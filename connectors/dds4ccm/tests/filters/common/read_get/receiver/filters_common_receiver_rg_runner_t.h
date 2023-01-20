// -*- C++ -*-
/**
 * @file    filters_common_receiver_rg_runner_t.h
 * @author  Marcel Smit
 *
 * @brief   Common checks for the filter and query attributes tests
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef FILTERS_COMMON_RECEIVER_RG_RUNNER_T_H_
#define FILTERS_COMMON_RECEIVER_RG_RUNNER_T_H_

#include "dds4ccm/tests/filters/common/qc_common.h"
#include "dds4ccm/logger/dds4ccm_testlog.h"

constexpr uint16_t min_iteration_run_1 () { return 6; }
constexpr uint16_t max_iteration_run_1 () { return 9; }

constexpr uint16_t min_iteration_run_2 () { return 4; }
constexpr uint16_t max_iteration_run_2 () { return 14; }

constexpr uint16_t min_iteration_run_3 () { return 4; }
constexpr uint16_t max_iteration_run_3 () { return iterations (); }

// The filter expression cannot be changed on a filter config.
// Just to make sure we receive all samples on for a content filtered
// topic as well, we just adjust the parameters.
constexpr uint16_t min_iteration_run_4 () { return 0; }
constexpr uint16_t max_iteration_run_4 () { return iterations () + 1; }

// Helper methods to get the correct parameters
typedef std::vector<uint16_t> QueryParameters;

inline void
get_query_parameters (::DDS::StringSeq &params, uint16_t run)
{
  switch (run)
  {
  case 1:
    params[0] = std::to_string (min_iteration_run_1 ());
    params[1] = std::to_string (max_iteration_run_1 ());
    break;
  case 2:
    params[0] = std::to_string (min_iteration_run_2 ());
    params[1] = std::to_string (max_iteration_run_2 ());
    break;
  case 3:
    params[0] = std::to_string (min_iteration_run_3 ());
    params[1] = std::to_string (max_iteration_run_3 ());
    break;
  case 4:
    params[0] = std::to_string (min_iteration_run_4 ());
    params[1] = std::to_string (max_iteration_run_4 ());
    break;
  default:
    DDS4CCM_TEST_DEBUG << "ERROR: get_query_parameters - "
      << "Unknown run number <" << run << ">." << std::endl;
    break;
  }
}

inline void
get_query_parameters (QueryParameters &params, uint16_t run)
{
  switch (run)
  {
  case 1:
    params[0] = min_iteration_run_1 ();
    params[1] = max_iteration_run_1 ();
    break;
  case 2:
    params[0] = min_iteration_run_2 ();
    params[1] = max_iteration_run_2 ();
    break;
  case 3:
    params[0] = min_iteration_run_3 ();
    params[1] = max_iteration_run_3 ();
    break;
  case 4:
    params[0] = min_iteration_run_4 ();
    params[1] = max_iteration_run_4 ();
    break;
  default:
    DDS4CCM_TEST_DEBUG << "ERROR: get_query_parameters - "
      << "Unknown run number <" << run << ">." << std::endl;
    break;
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
class ReadGetReceiverRunner_T final
{
public:

  explicit ReadGetReceiverRunner_T (
    typename IDL::traits<CONTEXT_TYPE>::ref_type ctx);

  explicit ReadGetReceiverRunner_T (
    typename IDL::traits<CONTEXT_TYPE>::ref_type ctx,
    uint16_t run);
  ~ReadGetReceiverRunner_T () = default;

  uint16_t run ();
  void     pre_start_checks ();

  void
  get_received (
    uint32_t &received_4_getter,
    uint32_t &received_4_reader);

private:
  typename IDL::traits<CONTEXT_TYPE>::ref_type context_;

  uint16_t run_ { 1 };

  uint32_t received_4_getter_ {};
  uint32_t received_4_reader_ {};

  void set_query_attributes ();
  void set_filter_attributes ();
  void set_filters ();

  void
  check_filter (
    IDL::traits<CommonTestConnector::Reader>::ref_type reader,
    bool check_getter);

  void check_filters ();
  void test_exception ();

  void
  test_non_changeable_filter (
    IDL::traits<::CommonTestConnector::CCM_DDS_Event>::ref_type conn,
    bool getter);
  void test_non_changeable_filter ();

  void
  test_internal_error_filter (
    IDL::traits< CCM_DDS::ContentFilterSetting>::ref_type cft,
    bool getter);
  void test_internal_error_filter ();

  void test_all ();
  void get_all ();
  void read_all ();

  void
  check_iter_getter (
    CommonTestMessage const &sample,
    QueryParameters const &params);

  void
  check_iter_reader (
    CommonTestMessage const &sample,
    QueryParameters const &params);

  // Specific to the content filtered topics.
  void check_iters_reader (CommonTestMessageSeq const &samples);


  ReadGetReceiverRunner_T(const ReadGetReceiverRunner_T&) = delete;
  ReadGetReceiverRunner_T(ReadGetReceiverRunner_T&&) = delete;
  ReadGetReceiverRunner_T& operator=(const ReadGetReceiverRunner_T&) = delete;
  ReadGetReceiverRunner_T& operator=(ReadGetReceiverRunner_T&&) = delete;
};

#include "dds4ccm/tests/filters/common/read_get/receiver/filters_common_receiver_rg_runner_t.cpp"

#endif /* FILTERS_COMMON_RECEIVER_RG_RUNNER_T_H_ */
