// -*- C++ -*-
/**
 * @file    filters_common_el_receiver_checks.h
 * @author  Marcel Smit
 *
 * @brief   Common checks for the event listeners.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef FILTERS_COMMON_EL_RECEIVER_CHECKS_H_
#define FILTERS_COMMON_EL_RECEIVER_CHECKS_H_

#include "dds4ccm/tests/filters/common/qc_common.h"

constexpr uint16_t min_iteration () { return 5; }
constexpr uint16_t max_iteration () { return 10; }


// The following listeners will receive the following iterations:
// - listen_port_1_data_listener : 6,7,8,9
// - listen_port_2_data_listener : 1,2,3,4,11,12,13,14,15
constexpr uint16_t expected_number_of_samples_on_listener_1 ()
{
  return 4 * number_of_loops () * keys ();
}

constexpr uint16_t expected_number_of_samples_on_listener_2 ()
{
  return number_of_loops () * keys () * (iterations () - 6);
}


inline void
check_sample (CommonTestMessage const &msg)
{
  if (msg.iteration () <= min_iteration ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: listen_port_2_data_listener_exec_i::check_samples - "
      << "Unexpected sample <" << msg << "> received. The receiver does not expect samples "
      << "with an iteration <= <" << min_iteration () << ">."
      << std::endl;
  }
  if (msg.iteration () > max_iteration ())
  {
    DDS4CCM_TEST_ERROR << "ERROR: listen_port_2_data_listener_exec_i::check_samples - "
      << "Unexpected sample <" << msg << "> received. The receiver does not expect samples "
      << "with an iteration > <" << max_iteration () << ">."
      << std::endl;
  }
}

inline void
check_samples (CommonTestMessageSeq const &messages)
{
  for (CommonTestMessage const & msg : messages)
  {
    if (msg.iteration () > min_iteration () &&
      msg.iteration () < max_iteration ())
    {
      DDS4CCM_TEST_ERROR << "ERROR: listen_port_1_data_listener_exec_i::check_sample - "
        << "Unexpected sample <" << msg << "> received. The receiver does not expect samples "
        << "with an iteration between <" << min_iteration () << "> and <"
        << max_iteration () << ">." << std::endl;
    }
  }
}


#endif /* FILTERS_COMMON_EL_RECEIVER_CHECKS_H_ */
