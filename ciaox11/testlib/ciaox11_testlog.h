/**
 * @file    ciaox11_testlog.h
 * @author  Marcel Smit
 *
 * @brief   CORBA C++11 Test Logging module
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_TESTLOG_H
#define CIAOX11_TESTLOG_H

#include "ciaox11/logger/log.h"

#if defined(X11_NLOGGING)

#define CIAOX11_TEST_LOGGER   x11_logger::NULL_LogType

#else

#define CIAOX11_TEST_LOGGER \
  CIAOX11::ciaox11_logger::CIAOX11_Test_Log_Msg::log_type

#endif /* !X11_NLOGGING */

#define CIAOX11_TEST_TRACE      X11_TRACE_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_DEBUG      X11_DEBUG_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_INFO       X11_INFO_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_WARNING    X11_WARNING_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_ERROR      X11_ERROR_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_CRITICAL   X11_CRITICAL_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_PANIC      X11_PANIC_LOG(CIAOX11_TEST_LOGGER)

#define CIAOX11_TEST_TRACE_W    X11_TRACE_W_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_DEBUG_W    X11_DEBUG_W_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_INFO_W     X11_INFO_W_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_WARNING_W  X11_WARNING_W_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_ERROR_W    X11_ERROR_W_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_CRITICAL_W X11_CRITICAL_W_LOG(CIAOX11_TEST_LOGGER)
#define CIAOX11_TEST_PANIC_W    X11_PANIC_W_LOG(CIAOX11_TEST_LOGGER)

#endif /* CIAOX11_TESTLOG_H */
