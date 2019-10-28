// -*- C++ -*-
/**
 * @file    qc_common.h
 * @author  Marcel Smit
 *
 * @brief   Some common definitions for the query tests.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef QC_COMMON_H_
#define QC_COMMON_H_

#include "dds4ccm/logger/dds4ccm_testlog.h"

constexpr uint16_t keys () { return 5; }
constexpr uint16_t iterations ()  { return 15; }

// Setting for the listener tests. The sender will send
// NUMBER_OF_LOOPS*KEYS*ITERATIONS
// This way the receiver knows how many samples to receive.
constexpr uint16_t number_of_loops () { return 5; }

// Define the queries
std::string const QUERY_LISTENER_I  ("( (iteration > %0) AND (iteration < %1) )");
std::string const QUERY_LISTENER_II ("( (iteration < %0) OR (iteration > %1) )");

std::string const QUERY_GETTER ("( (iteration > %0) AND (iteration < %1) ) OR (key = 'KEY_6')");
std::string const QUERY_READER ("( (iteration < %0) OR (iteration > %1) ) OR (key = 'KEY_6')");

#endif /* QC_COMMON_H_ */
