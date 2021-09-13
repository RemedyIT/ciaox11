// -*- C++ -*-
/**
 * @file    dds4ccm_test_utils.h
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM4CIAOX11 test utilities
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_TEST_UTILS_H_
#define DDS4CCM_TEST_UTILS_H_


#include "dds4ccm/idl/ccm_ddsC.h"

#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

#include <atomic>
#include <chrono>
#include <thread>

typedef std::atomic<std::thread::id> atomic_thread_id;

#define catch_dds4ccm_test_ex(ex, L) \
  catch (const CORBA::Exception &ex) \
  { \
    DDS4CCM_TEST_ERROR << "ERROR: " << L << " - " \
      << "caught unexpected CORBA exception: " \
      << ex << std::endl; \
  } \
  catch (const std::exception &ex) \
  { \
    DDS4CCM_TEST_ERROR << "ERROR: " << L << " - " \
      << "caught std::exception: " \
      << ex << std::endl; \
  } \
  catch (...) \
  { \
    DDS4CCM_TEST_ERROR << "ERROR: " << L << " - " \
      << "ERROR caught unexpected exception" \
      << std::endl; \
  }

namespace DDS4CCM_TEST_UTILS
{
  inline bool check_publication_matched_status (
    IDL::traits< ::DDS::Entity>::ref_type the_entity,
    ::DDS::StatusKind status_kind,
    uint16_t expected_reader_count)
  {
    bool ret = false;

    DDS4CCM_TEST_DEBUG << "unexpected_status_checker::check_publication_matched_status."
                      << std::endl;

    if (status_kind == ::DDS::PUBLICATION_MATCHED_STATUS)
    {
      ::DDS::PublicationMatchedStatus current_pub_status {};
      IDL::traits< ::DDS::DataWriter>::ref_type writer =
        IDL::traits< ::DDS::DataWriter>::narrow (the_entity);
      ::DDS::ReturnCode_t const retcode = writer->get_publication_matched_status (current_pub_status);

      DDS4CCM_TEST_DEBUG << "unexpected_status_checker::check_publication_matched_status - "
          << "PublicationMatchedStatus: " << DDS::dds_write (current_pub_status)
          << std::endl;

      if (retcode == ::DDS::RETCODE_OK)
      {
        // The current number of connected data readers (current_count) should
        // be equal to the given number data readers. Most of the tests expect
        // one data reader.
        if (current_pub_status.current_count () == expected_reader_count)
        {
          DDS4CCM_TEST_DEBUG << "unexpected_status_checker::check_publication_matched_status - "
                            << "All datareaders are connected." << std::endl;
          ret = true;
        }
        else if (current_pub_status.current_count () != 0)
        {
          // A publication matches status is also be received upon exit?
          DDS4CCM_TEST_DEBUG << "unexpected_status_checker::check_publication_matched_status - "
              << "Expected number of Datareaders are not (all) connected yet: connected <"
              << current_pub_status.current_count () << "> - expected <"
              << expected_reader_count << ">." << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "unexpected_status_checker::check_publication_matched_status - "
            << "ERROR: get_publication_matched_status returned an error <" << ::DDS::dds_write (retcode)
            << ">." << std::endl;
      }
    }

    return ret;
  }

  inline void
  check_thread_switch (std::string const & test, std::thread::id const &id)
  {
      std::thread::id const current_thread = std::this_thread::get_id ();

#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1)
      if (id == current_thread)
      {
        DDS4CCM_TEST_DEBUG << "OK : "
          << "Thread switch for " << test << " seems OK; "
          << "DDS4CCM uses the CCM thread for its callbacks. listener <"
          << id << "> - component <"
          << current_thread << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: "
          << "Thread switch for " << test << " doesn't seem to work! listener <"
          << id << "> - component <"
          << current_thread << ">." << std::endl;
      }
#else
      if (id == current_thread)
      {
        DDS4CCM_TEST_ERROR << "ERROR: " << test << ": "
          << "DDS4CCM seems to use a CCM thread for its callbacks: "
          << "listener <" << id << "> - component <"
          << current_thread << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "OK : " << test << ": "
          << "DDS4CCM seems to use the DDS thread for its callbacks: "
          << "listener <" << id << "> - component <"
          << current_thread << ">." << std::endl;
      }
#endif
  }
}

#endif /* DDS4CCM_TEST_UTILS_H_ */
