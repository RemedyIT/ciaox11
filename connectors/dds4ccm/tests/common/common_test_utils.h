// -*- C++ -*-
/**
 * @file    common_test_utils.h
 * @author  Marcel Smit
 *
 * @brief   Utilities related to the CommonTestConnector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef COMMON_TEST_UTILS_H_
#define COMMON_TEST_UTILS_H_


#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "dds4ccm_test_utils.h"

namespace DDS4CCM_TEST_UTILS
{
  inline bool check_last (
    IDL::traits< ::CommonTestConnector::Reader >::ref_type reader,
    uint32_t last_key, int32_t last_iteration)
  {
    std::string const key_str ("KEY_"+std::to_string (last_key));

    ::CCM_DDS::ReadInfo readinfo;
    CommonTestMessage datum (key_str, 0);
    try
    {
      reader->read_one_last (datum, readinfo, ::DDS::HANDLE_NIL);

      DDS4CCM_TEST_DEBUG << "DDS4CCM_TEST_UTILS::check_last <"
        << key_str << "> - last iteration <" << datum.iteration ()
        << "> - <" << last_iteration << ">, access status :" << DDS::dds_write(readinfo.access_status ()) << std::endl;

      return readinfo.access_status () == CCM_DDS::AccessStatus::FRESH_INFO &&
        datum.iteration () >= last_iteration;
    }
    catch (const ::CCM_DDS::NonExistent &)
    {
      DDS4CCM_TEST_DEBUG << "DDS4CCM_TEST_UTILS::check_last - "
        << "Caught a NonExistent exception for key - "
        << datum << std::endl;
    }
    catch_dds4ccm_test_ex(ex, "DDS4CCM_TEST_UTILS::check_last")
    return false;
  }
}

#endif /* COMMON_TEST_UTILS_H_ */
