/**
 * @file    main.cpp
 * @author  Marcel Smit
 *
 * @brief   Testing the logging formatters.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "dds4ccm/impl/dds4ccm_log_formatters.h"

class MyEntity
  : public IDL::traits<DDS::Entity>::base_type
{
public:
  virtual DDS::ReturnCode_t enable() override
  {
    return ::DDS::RETCODE_OK;
  }

  virtual IDL::traits<DDS::StatusCondition>::ref_type get_statuscondition() override
  {
    return nullptr;
  }

  virtual DDS::StatusMask get_status_changes() override
  {
    return DDS::LIVELINESS_LOST_STATUS;
  }

  virtual DDS::InstanceHandle_t get_instance_handle() override
  {
#if defined DDSX11_NDDS
    return DDS::InstanceHandle_t {{{15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}}, 16, false};
#else
    return DDS::InstanceHandle_t {{0}};
#endif
  }
};


int main (int , char **)
{
  std::ostringstream ostr;

  ::DDS::QosPolicyCountSeq policy_count_seq;
#if defined DDSX11_NDDS
  ::DDS::QosPolicyCount const policy_count (::DDS::DOMAINPARTICIPANTRESOURCELIMITS_QOS_POLICY_ID, 5);
  DDS4CCM_TEST_DEBUG << "Logging QosPolicyCount : " << DDS::dds_write (policy_count) << std::endl;
  ostr << "Logging QosPolicyCount : " << DDS::dds_write (policy_count) << std::endl;

  policy_count_seq.push_back (policy_count);
  policy_count_seq.push_back (policy_count);
  policy_count_seq.push_back (policy_count);
  DDS4CCM_TEST_DEBUG << "Logging QosPolicyCountSeq : " << DDS::dds_write (policy_count_seq) << std::endl;
  ostr << "Logging QosPolicyCountSeq : " << DDS::dds_write (policy_count_seq) << std::endl;
#endif /* DDSX11_NDDS */

  ::DDS::Time_t const time (15, 0);
  DDS4CCM_TEST_DEBUG << "Logging Time_t : " << DDS::dds_write (time) << std::endl;
  ostr << "Logging Time_t : " << DDS::dds_write (time) << std::endl;

#if defined DDSX11_NDDS
  ::DDS::StatusKind const status_kind (::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS);
  DDS4CCM_TEST_DEBUG << "Logging StatusKind : " << DDS::dds_write (status_kind) << std::endl;
  ostr << "Logging StatusKind : " << DDS::dds_write (status_kind) << std::endl;
#endif /* DDSX11_NDDS */

  CCM_DDS::AccessStatus const access_status = CCM_DDS::AccessStatus::ALREADY_SEEN;
  DDS4CCM_TEST_DEBUG << "Logging AccessStatus : " << DDS::dds_write (access_status) << std::endl;
  ostr << "Logging AccessStatus : " << DDS::dds_write (access_status) << std::endl;

  CCM_DDS::InstanceStatus const instance_status = CCM_DDS::InstanceStatus::INSTANCE_UPDATED;
  DDS4CCM_TEST_DEBUG << "Logging InstanceStatus : " << DDS::dds_write (instance_status) << std::endl;
  ostr << "Logging InstanceStatus : " << DDS::dds_write (instance_status) << std::endl;

#if defined DDSX11_NDDS
  DDS::InstanceHandle_t const instance_handle ({{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}}, 16, true);
#else
  DDS::InstanceHandle_t const instance_handle {{6}};
#endif /* DDSX11_NDDS */
  DDS4CCM_TEST_DEBUG << "Logging InstanceHandle_t : " << DDS::dds_write(instance_handle) << std::endl;
  ostr << "Logging InstanceHandle_t : " << DDS::dds_write(instance_handle) << std::endl;

  CCM_DDS::ReadInfo const ri (instance_handle,
                              ::DDS::Time_t (16,0),
                              CCM_DDS::AccessStatus::FRESH_INFO,
                              CCM_DDS::InstanceStatus::INSTANCE_FILTERED_IN);
  DDS4CCM_TEST_DEBUG << "Logging ReadInfo : " << DDS::dds_write (ri) << std::endl;
  ostr << "Logging ReadInfo : " << DDS::dds_write (ri) << std::endl;

  CCM_DDS::ReadInfoSeq ri_seq;
  ri_seq.push_back (ri);
  ri_seq.push_back (ri);
  ri_seq.push_back (ri);
  DDS4CCM_TEST_DEBUG << "Logging ReadInfoSeq : " << DDS::dds_write (ri_seq) << std::endl;
  ostr << "Logging ReadInfoSeq : " << DDS::dds_write (ri_seq) << std::endl;

  IDL::traits<DDS::Entity>::ref_type entity = CORBA::make_reference<MyEntity>();
  DDS4CCM_TEST_DEBUG << "Logging DDS::Entity : " << DDS::dds_write (entity) << std::endl;
  ostr << "Logging DDS::Entity : " << DDS::dds_write (entity) << std::endl;

#if defined DDSX11_NDDS
  DDS::SampleLostStatus const sample_lost_status (5, 10, ::DDS::SampleLostStatusKind::NOT_LOST);
#else
  DDS::SampleLostStatus const sample_lost_status (5, 10);
#endif
  DDS4CCM_TEST_DEBUG << "Logging DDS::SampleLostStatus : " << DDS::dds_write (sample_lost_status) << std::endl;
  ostr << "Logging DDS::SampleLostStatus : " << DDS::dds_write (sample_lost_status) << std::endl;

  DDS::RequestedDeadlineMissedStatus const requested_deadline_missed_status (6, 11, instance_handle);
  DDS4CCM_TEST_DEBUG << "Logging DDS::RequestedDeadlineMissedStatus : "
    << DDS::dds_write (requested_deadline_missed_status) << std::endl;
  ostr << "Logging DDS::RequestedDeadlineMissedStatus : "
    << DDS::dds_write (requested_deadline_missed_status) << std::endl;

  DDS::InconsistentTopicStatus const inconsistent_topic_status (10, 15);
  DDS4CCM_TEST_DEBUG << "Logging DDS::InconsistentTopicStatus : "
    << DDS::dds_write (inconsistent_topic_status) << std::endl;
  ostr << "Logging DDS::InconsistentTopicStatus : "
    << DDS::dds_write (inconsistent_topic_status) << std::endl;

  DDS::RequestedIncompatibleQosStatus const requested_incompatible_qos_status (
    11, 16, ::DDS::ENTITYFACTORY_QOS_POLICY_ID, policy_count_seq);
  DDS4CCM_TEST_DEBUG << "Logging DDS::RequestedIncompatibleQosStatus : "
    << DDS::dds_write (requested_incompatible_qos_status) << std::endl;
  ostr << "Logging DDS::RequestedIncompatibleQosStatus : "
    << DDS::dds_write (requested_incompatible_qos_status) << std::endl;

  DDS::SampleRejectedStatus const sample_rejected_status (15, 20,
    DDS::SampleRejectedStatusKind::REJECTED_BY_SAMPLES_LIMIT,
    instance_handle);
  DDS4CCM_TEST_DEBUG << "Logging DDS::SampleRejectedStatus : "
    << DDS::dds_write (sample_rejected_status) << std::endl;
  ostr << "Logging DDS::SampleRejectedStatus : "
    << DDS::dds_write (sample_rejected_status) << std::endl;

  DDS::OfferedDeadlineMissedStatus const offered_deadline_missed_status (7, 12, instance_handle);
  DDS4CCM_TEST_DEBUG << "Logging DDS::OfferedDeadlineMissedStatus : "
    << DDS::dds_write (offered_deadline_missed_status) << std::endl;
  ostr << "Logging DDS::OfferedDeadlineMissedStatus : "
    << DDS::dds_write (offered_deadline_missed_status) << std::endl;

#if defined DDSX11_NDDS
  DDS::OfferedIncompatibleQosStatus const offered_incompatible_qos_status (
    12, 17, ::DDS::DATAWRITERRESOURCELIMITS_QOS_POLICY_ID, policy_count_seq);
  DDS4CCM_TEST_DEBUG << "Logging DDS::OfferedIncompatibleQosStatus : "
    << DDS::dds_write (offered_incompatible_qos_status) << std::endl;
  ostr << "Logging DDS::OfferedIncompatibleQosStatus : "
    << DDS::dds_write (offered_incompatible_qos_status) << std::endl;
#endif /* DDSX11_NDDS */

  DDS::PublicationMatchedStatus const publication_matched_status (
    20, 15, 12, 7, instance_handle);
  DDS4CCM_TEST_DEBUG << "Logging DDS::PublicationMatchedStatus : "
    << DDS::dds_write (publication_matched_status) << std::endl;
  ostr << "Logging DDS::PublicationMatchedStatus : "
    << DDS::dds_write (publication_matched_status) << std::endl;

  DDS::SubscriptionMatchedStatus const subscription_matched_status (
    7, 12, 15, 20, instance_handle);
  DDS4CCM_TEST_DEBUG << "Logging DDS::SubscriptionMatchedStatus : "
    << DDS::dds_write (subscription_matched_status) << std::endl;
  ostr << "Logging DDS::SubscriptionMatchedStatus : "
    << DDS::dds_write (subscription_matched_status) << std::endl;

  DDS::LivelinessLostStatus const liveliness_lost_status (8, 13);
  DDS4CCM_TEST_DEBUG << "Logging DDS::LivelinessLostStatus : "
    << DDS::dds_write (liveliness_lost_status) << std::endl;
  ostr << "Logging DDS::LivelinessLostStatus : "
    << DDS::dds_write (liveliness_lost_status) << std::endl;

  DDS::LivelinessChangedStatus const liveliness_changed_status (
    9, 14, 16, 21, instance_handle);
  DDS4CCM_TEST_DEBUG << "Logging DDS::LivelinessChangedStatus : "
    << DDS::dds_write (liveliness_changed_status) << std::endl;
  ostr << "Logging DDS::LivelinessChangedStatus : "
    << DDS::dds_write (liveliness_changed_status) << std::endl;

  DDS::Duration_t const duration (134, 31145112);
  DDS4CCM_TEST_DEBUG << "Logging DDS::Duration_t : "
    << DDS::dds_write (duration) << std::endl;
  ostr << "Logging DDS::Duration_t : "
    << DDS::dds_write (duration) << std::endl;

#if defined DDSX11_NDDS
  DDS::QosPolicyId_t const policy_id (DDS::DOMAINPARTICIPANTRESOURCELIMITS_QOS_POLICY_ID);
  DDS4CCM_TEST_DEBUG << "Logging DDS::QosPolicyId_t : "
    << DDS::dds_write (policy_id) << std::endl;
  ostr << "Logging DDS::QosPolicyId_t : "
    << DDS::dds_write (policy_id) << std::endl;
#endif /* DDSX11_NDDS */

  return 0;
}
