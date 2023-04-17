/**
 * @file    dispatch_queue.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Unit test for ciaox11 exf dispatch queue
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11/testlib/ciaox11_testlog.h"
#include "deployment/scheduler/ciaox11_exf_dispatcher.h"


int main(int /*argc*/, char** /*argv[]*/)
{
  try
  {
    CIAOX11_TEST_INFO << "shutting down...";

    CIAOX11_TEST_INFO << std::endl;
  }
  catch (const std::exception& e)
  {
    // X11_FUZZ: disable check_test_log_macros
    ciaox11_error << "exception caught: " << e.what () << std::endl;
    // X11_FUZZ: enable check_test_log_macros
    return 1;
  }
  return 0;
}
