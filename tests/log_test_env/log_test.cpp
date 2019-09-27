/**
 * @file    log_test.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   CORBA C++11 logging test with env. var.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "ciaox11/testlib/ciaox11_testlog.h"

void
test_log ()
{
  //Testcase priority 1
  // First use priority mask LP_INFO|LP_WARNING  set via env.var. CIAOX11_LOG_MASK:
  CIAOX11_TEST_INFO << "**************** Use priority mask LP_INFO|LP_WARNING"
              << std::endl;

  CIAOX11_TEST_INFO << " begin priority testcase: 1 " << std::endl;
  CIAOX11_TEST_INFO << "CIAOX11_LOG expected: CIAOX11_LOG_INFO" << std::endl;
  CIAOX11_LOG_INFO ("Test of the macro <CIAOX11_LOG_INFO>");
  CIAOX11_TEST_INFO << "CIAOX11_LOG expected: CIAOX11_LOG_WARNING" << std::endl;
  CIAOX11_LOG_WARNING ("Test of the macro <CIAOX11_LOG_WARNING>");

  CIAOX11_TEST_INFO << "not expected priority testcase: 1 " << std::endl;
  CIAOX11_LOG_DEBUG ("If you see this message from < CIAOX11_LOG_DEBUG>, it is an ERROR.") ;
  CIAOX11_TEST_INFO << "end priority testcase: 1 " << std::endl;

  // Testcase priority 2
  // Overwrite priority mask LP_INFO|LP_WARNING  set via env.var.  with LP_PANIC:
  CIAOX11_TEST_INFO << "**************** Use priority mask LP_PANIC"
               << std::endl;
  CIAOX11_LOGGER::priority_mask (x11_logger::LP_PANIC );
  CIAOX11_TEST_INFO << " begin priority testcase: 2 " << std::endl;
  CIAOX11_TEST_INFO << "CIAOX11_LOG expected: CIAOX11_LOG_PANIC" << std::endl;
  CIAOX11_LOG_PANIC ("Test of the macro <CIAOX11_LOG_PANIC>");
  CIAOX11_TEST_INFO << "not expected priority testcase: 2 " << std::endl;
  CIAOX11_LOG_DEBUG ("If you see this message from < CIAOX11_LOG_DEBUG>, it is an ERROR.") ;
  CIAOX11_LOG_INFO ("If you see this message from < CIAOX11_LOG_INFO>, it is an ERROR.") ;
  CIAOX11_TEST_INFO << "end priority testcase: 2 " << std::endl;

  // Testcase verbose 1
  // Use verbose mask V_CATEGORY|V_PRIO set via env. var. CIAOX11_VERBOSE
  CIAOX11_TEST_INFO << "************* uses priority mask LP_INFO"
              << " and verbose options :"
              << "V_CATEGORY, V_PRIO."
              << std::endl;

  CIAOX11_LOGGER::priority_mask (x11_logger::LP_INFO );
  CIAOX11_TEST_INFO << " begin verbose testcase: 1 " << std::endl;
  CIAOX11_TEST_INFO << "CIAOX11_LOG verbosity expected: V_CATEGORY,V_PRIO" << std::endl;
  CIAOX11_LOG_INFO ("Test of verbosity with the macro <CIAOX11_LOG_INFO>");
  CIAOX11_TEST_INFO << "CIAOX11_LOG verbosity unexpected: V_TIME,V_PROCESS_ID" << std::endl;
  CIAOX11_LOG_INFO ("Test of verbosity with the macro <CIAOX11_LOG_INFO>");
  CIAOX11_TEST_INFO << " end verbose testcase: 1 " << std::endl;

  // Testcase verbose 2
  // Overwrite verbose mask V_CATEGORY|V_PRIO set via env. var. with V_TIME
  CIAOX11_TEST_INFO << "************* uses priority mask LP_INFO"
              << " and verbose options :"
              << "V_TIME."
              << std::endl;

  CIAOX11_LOGGER::priority_mask (x11_logger::LP_INFO );
  CIAOX11_LOGGER::verbosity_mask (x11_logger::V_TIME );
  CIAOX11_TEST_INFO << " begin verbose testcase: 2 " << std::endl;
  CIAOX11_TEST_INFO << "CIAOX11_LOG verbosity expected: V_TIME" << std::endl;
  CIAOX11_LOG_INFO ("Test of verbosity with the macro <CIAOX11_LOG_INFO>");
  CIAOX11_TEST_INFO << "CIAOX11_LOG verbosity unexpected: CATEGORY,V_PRIO,V_PROCESS_ID" << std::endl;
  CIAOX11_LOG_INFO ("Test of verbosity with the macro <CIAOX11_LOG_INFO>");
  CIAOX11_TEST_INFO << " end verbose testcase: 2 " << std::endl;
}


int main(int /*argc*/, char** /*argv[]*/)
{
  try
  {
    // Now test logging macro's
    test_log();

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
