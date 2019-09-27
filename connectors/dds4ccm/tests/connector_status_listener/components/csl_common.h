// -*- C++ -*-
/**
 * @file    csl_common.h
 * @author  Marcel Smit
 *
 * @brief   Checks which are valid for both the sender and receiver
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CSL_COMMON_H_
#define CSL_COMMON_H_

#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"

/**
 * Check of the incompatible status. Both the sender
 * and the receiver receive the same data; in the sender
 * the type of the status is 'OfferedIncompatibleQosStatus' while
 * in the receiver the type of status is 'RequestedIncompatibleQosStatus'.
 * The fields in both statuses are the same.
 */
template<typename INCOMPATIBLE_STATUS>
inline void check_incompatible_qos_status (
  const INCOMPATIBLE_STATUS &status)
{
  DDS4CCM_TEST_DEBUG << "check_incompatible_qos_status - checking status" << std::endl;

  // Check the status. Should be received just once, listing two incompatibilities:
  // 1. liveliness
  // 2. Reliability
  // The last one is about the liveliness
  if (status.last_policy_id () != ::DDS::LIVELINESS_QOS_POLICY_ID)
  {
    DDS4CCM_TEST_ERROR << "ERROR: check_incompatible_qos_status - "
      << "unexpected last_policy_id: expected <::DDS::LIVELINESS_QOS_POLICY_ID> - received <"
      << DDS::dds_write (status.last_policy_id ()) << ">." << std::endl;
  }
  if (status.policies ().size () != 2)
  {
    DDS4CCM_TEST_ERROR << "ERROR: check_incompatible_qos_status - "
      << "unexpected last_policy_id: expected <::DDS::LIVELINESS_QOS_POLICY_ID> - received <"
      << DDS::dds_write (status.last_policy_id ()) << ">." << std::endl;
  }
  for (::DDS::QosPolicyCount const &pc : status.policies ())
  {
    if (!(pc.policy_id () == ::DDS::RELIABILITY_QOS_POLICY_ID ||
      pc.policy_id () == ::DDS::LIVELINESS_QOS_POLICY_ID))
    {
      DDS4CCM_TEST_ERROR << "ERROR: check_incompatible_qos_status - "
        << "unexpected policy ID detected. expected <DDS::RELIABILITY_QOS_POLICY_ID or "
        << "DDS::LIVELINESS_QOS_POLICY_ID> - detected <"
        << DDS::dds_write (pc.policy_id ()) << ">." << std::endl;
    }
  }
}

/**
 * Checks needed in both the sender and receiver.
 *
 */
inline void
check_unexpected_status_when_no_match (std::string const &component_executor,
  atomic_thread_id const &on_subscription_matched_thread_id,
  atomic_thread_id const &on_publication_matched_thread_id,
  atomic_thread_id const &on_reliable_writer_cache_changed_thread_id,
  atomic_thread_id const &on_reliable_reader_activity_changed_thread_id,
  atomic_thread_id const &on_liveliness_changed_thread_id,
  atomic_thread_id const &on_liveliness_lost_thread_id)
{
  if (on_subscription_matched_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << component_executor
      << "::check_unexpected_status_when_no_match - "
      << "an on_subscription_matched status has been received."<< std::endl;
  }
  if (on_publication_matched_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << component_executor
      << "::check_unexpected_status_when_no_match - "
      << "an on_publication_matched status has been received."<< std::endl;
  }

#if defined DDSX11_NDDS && DDSX11_NDDS == 1
  if (on_reliable_writer_cache_changed_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << component_executor
      << "::check_unexpected_status_when_no_match - "
      << "an on_reliable_writer_cache_changed status has been received."<< std::endl;
  }
  if (on_reliable_reader_activity_changed_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << component_executor
      << "::check_unexpected_status_when_no_match - "
      << "an on_reliable_reader_activity_changed status has been received."<< std::endl;
  }
#else
  X11_UNUSED_ARG (on_reliable_writer_cache_changed_thread_id);
  X11_UNUSED_ARG (on_reliable_reader_activity_changed_thread_id);
#endif /* DDSX11_NDDS && DDSX11_NDDS == 1 */

  if (on_liveliness_changed_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << component_executor
      << "::check_unexpected_status_when_no_match - "
      << "an on_liveliness_changed status has been received."<< std::endl;
  }
  if (on_liveliness_lost_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << component_executor
      << "::check_unexpected_status_when_no_match - "
      << "an on_liveliness_lost status has been received."<< std::endl;
  }
}

inline void
check_context_switches (
  atomic_thread_id const &on_inconsistent_topic_thread_id,
  atomic_thread_id const &on_requested_incompatible_qos_thread_id,
  atomic_thread_id const &on_sample_rejected_thread_id,
  atomic_thread_id const &on_offered_deadline_missed_thread_id,
  atomic_thread_id const &on_offered_incompatible_qos_thread_id,
  atomic_thread_id const &on_publication_matched_thread_id,
  atomic_thread_id const &on_subscription_matched_thread_id,
  atomic_thread_id const &on_liveliness_changed_thread_id,
  atomic_thread_id const &on_liveliness_lost_thread_id,
  atomic_thread_id const &on_reliable_reader_activity_changed_thread_id,
  atomic_thread_id const &on_reliable_writer_cache_changed_thread_id)
{
  if (on_inconsistent_topic_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_inconsistent_topic",
      on_inconsistent_topic_thread_id);
  }
  if (on_requested_incompatible_qos_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_requested_incompatible_qos",
      on_requested_incompatible_qos_thread_id);
  }
  if (on_sample_rejected_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_sample_rejected",
      on_sample_rejected_thread_id);
  }
  if (on_offered_deadline_missed_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_offered_deadline_missed",
      on_offered_deadline_missed_thread_id);
  }
  if (on_offered_incompatible_qos_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_offered_incompatible_qos",
      on_offered_incompatible_qos_thread_id);
  }

  if (on_liveliness_changed_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_liveliness_changed",
      on_liveliness_changed_thread_id);
  }

  if (on_liveliness_lost_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_liveliness_lost",
      on_liveliness_lost_thread_id);
  }
  if (on_publication_matched_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_publication_matched",
      on_publication_matched_thread_id);
  }
  if (on_subscription_matched_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_subscription_matched",
      on_subscription_matched_thread_id);
  }
  if (on_reliable_reader_activity_changed_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_reliable_reader_activity_changed",
      on_reliable_reader_activity_changed_thread_id);
  }
  if (on_reliable_writer_cache_changed_thread_id != std::thread::id ())
  {
    DDS4CCM_TEST_UTILS::check_thread_switch (
      "on_reliable_writer_cache_changed",
      on_reliable_writer_cache_changed_thread_id);
  }
}

enum class ASSIGNMENT : uint32_t
{
  ASSIGNMENT_UNKNOWN,
  ASSIGNMENT_UNEXPECTED_STATUS,
  ASSIGNMENT_SAMPLE_REJECTED,
  ASSIGNMENT_INCONSISTENT_TOPIC,
  ASSIGNMENT_INCOMPATIBLE_QOS,
  ASSIGNMENT_DEADLINE_MISSED
};// ASSIGNMENT

// Translation from a string (deployment plans) to the internal
// assignment enumeration.
ASSIGNMENT assignment_to_enum (std::string const &csl_assignment)
{
  ASSIGNMENT assignment = ASSIGNMENT::ASSIGNMENT_UNKNOWN;
  if (csl_assignment == "on_unexpected_status")
    assignment = ASSIGNMENT::ASSIGNMENT_UNEXPECTED_STATUS;
  else if (csl_assignment == "on_sample_rejected")
    assignment = ASSIGNMENT::ASSIGNMENT_SAMPLE_REJECTED;
  else if (csl_assignment == "on_inconsistent_topic")
    assignment = ASSIGNMENT::ASSIGNMENT_INCONSISTENT_TOPIC;
  else if (csl_assignment == "on_incompatible_qos")
    assignment = ASSIGNMENT::ASSIGNMENT_INCOMPATIBLE_QOS;
  else if (csl_assignment == "on_deadline_missed")
    assignment = ASSIGNMENT::ASSIGNMENT_DEADLINE_MISSED;
  return assignment;
}


#endif /* CSL_CHECKS_H_ */

