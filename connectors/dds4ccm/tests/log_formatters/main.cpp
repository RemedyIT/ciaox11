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

int main (int , char **)
{
  std::ostringstream ostr;

  CCM_DDS::AccessStatus const access_status = CCM_DDS::AccessStatus::ALREADY_SEEN;
  DDS4CCM_TEST_DEBUG << "Logging AccessStatus : " << DDS::dds_write (access_status) << std::endl;
  ostr << "Logging AccessStatus : " << DDS::dds_write (access_status) << std::endl;

  CCM_DDS::InstanceStatus const instance_status = CCM_DDS::InstanceStatus::INSTANCE_UPDATED;
  DDS4CCM_TEST_DEBUG << "Logging InstanceStatus : " << DDS::dds_write (instance_status) << std::endl;
  ostr << "Logging InstanceStatus : " << DDS::dds_write (instance_status) << std::endl;

  CCM_DDS::ListenerMode const listener_mode = CCM_DDS::ListenerMode::NOT_ENABLED;
  DDS4CCM_TEST_DEBUG << "Logging ListenerMode : " << DDS::dds_write (listener_mode) << std::endl;
  ostr << "Logging ListenerMode : " << DDS::dds_write (listener_mode) << std::endl;

#if defined DDSX11_NDDS
  DDS::InstanceHandle_t const instance_handle ({{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}}, 16, true);
#else
  DDS::InstanceHandle_t const instance_handle {{1234567}};
#endif /* DDSX11_NDDS */
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

  return 0;
}
