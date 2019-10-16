// -*- C++ -*-
/**
 * @file    filters_common_sl_receiver_checks.h
 * @author  Marcel Smit
 *
 * @brief   Common checks for the state listeners.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef FILTERS_COMMON_SL_RECEIVER_CHECKS_H_
#define FILTERS_COMMON_SL_RECEIVER_CHECKS_H_

#include "dds4ccm/tests/filters/common/qc_common.h"

constexpr uint16_t min_iteration () { return 10; }
constexpr uint16_t max_iteration () { return 13; }

// The following listeners will receive *updates* of the following iterations:
// - listen_port_1_data_listener : 11,12
// - listen_port_2_data_listener : 1,2,3,4,5,6,7,8,9,14,15
// The first iteration does not count since this will be received upon 'on_creation'
constexpr uint16_t expected_number_of_samples_on_listener_1 ()
{
  return (2 * number_of_loops () * keys ()) - keys ();
}

constexpr uint16_t expected_number_of_samples_on_listener_2 ()
{
  return (number_of_loops () * keys () * (iterations () - 4)) - keys ();
}

inline void
check_on_creation_obo (const ::CommonTestMessage& datum)
{
  // The first sample which will be created for this connector is
  // (MIN_ITERATION+1) since the other samples are not filtered in.
  if (datum.iteration () != min_iteration () + 1)
  {
    DDS4CCM_TEST_ERROR << "ERROR: on_creation (one_by_one) - "
      << "Unexpected sample detected <" << datum << ">. This listener doesn't expect "
      << "samples other than <CommonTestMessage{key=\"KEY_X\",iteration=11}> upon "
      << "creation." << std::endl;
  }
}

inline void
check_on_creation_mbm (const ::CommonTestMessage& datum)
{
  // The first sample is the one that's created in DDS and filtered in in this
  // listener
  if (datum.iteration () != 1)
  {
    DDS4CCM_TEST_ERROR << "ERROR: on_creation (many_to_many) - "
      << "Unexpected sample detected <" << datum << ">. This listener doesn't expect "
      << "samples other than <CommonTestMessage{key=\"KEY_X\",iteration=1}> upon "
      << "creation." << std::endl;
  }
}

inline void
check_on_one_update (const std::string &test, const ::CommonTestMessage& datum)
{
  if (datum.iteration () <= min_iteration ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
      << "Unexpected sample <" << datum << "> received. The receiver "
      << "does not expect samples with an iteration <= <" << min_iteration () << ">."
      << std::endl;
  }
  if (datum.iteration () > max_iteration ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
      << "Unexpected sample <" << datum << "> received. The receiver does not "
      << "expect samples with an iteration > <" << max_iteration () << ">."
      << std::endl;
  }
}

inline void
check_on_many_updates (const std::string &test, const ::CommonTestMessageSeq& data)
{
  for (CommonTestMessage const & datum : data)
  {
    if (datum.iteration () > min_iteration () &&
      datum.iteration () < max_iteration ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
        << "Unexpected sample <" << datum << "> received. The receiver does not "
        << "expect samples with an iteration between <" << min_iteration ()
        << "> and <" << max_iteration () << ">." << std::endl;
    }
  }
}

#endif /* FILTERS_COMMON_SL_RECEIVER_CHECKS_H_ */
