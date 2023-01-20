/**
 * @file    getter_test_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the Getter test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : getter_test_receiver_impl.cpp[Header]

#include "getter_test_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
#include <chrono>
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[user_global_impl]

namespace Getter_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[user_namespace_impl]
  /**
   * GetOneHandler
   */
  GetOneHandler::GetOneHandler (IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor,
                                const std::string &key,
                                int32_t iteration)
    : component_executor_ (std::move(component_executor))
    , key_ (key)
    , iteration_ (iteration)
  {
    DDS4CCM_TEST_DEBUG << "ReceiverGetOneHandler::GetOneHandler" << std::endl;
  }

  void
  GetOneHandler::on_trigger (
    IDL::traits<::CCM_TT::TT_Timer>::ref_type,
    const ::CCM_TT::TT_Duration&,
    uint32_t)
  {
    auto cex = IDL::traits<Receiver_exec_i>::narrow (
      this->component_executor_.lock ());
    if (cex)
    {
      cex->get_one (this->key_, this->iteration_);
    }
    else
    {
      DDS4CCM_TEST_ERROR << "GetOneHandler::on_trigger - "
        "ERROR: failed to lock component executor" << std::endl;
    }
  }

  /**
   * GetManyHandler
   */
  GetManyHandler::GetManyHandler (IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor,
                                  int16_t keys,
                                  int32_t iterations)
    : component_executor_ (std::move(component_executor)),
      keys_ (keys),
      iterations_ (iterations)
  {
    DDS4CCM_TEST_DEBUG << " GetManyHandler::GetManyHandler" << std::endl;
  }

  void
  GetManyHandler::on_trigger (
    IDL::traits<::CCM_TT::TT_Timer>::ref_type,
    const ::CCM_TT::TT_Duration&,
    uint32_t)
  {
    auto cex = IDL::traits<Receiver_exec_i>::narrow (
      this->component_executor_.lock ());
    if (cex)
    {
      cex->get_many (this->keys_, this->iterations_);
    }
    else
    {
      DDS4CCM_TEST_ERROR << "GetManyHandler::on_trigger - "
        "ERROR: failed to lock component executor" << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<Getter_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    DDS4CCM_TEST_DEBUG << "Receiver_ info_get_status_exec_i::on_requested_deadline_missed" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    DDS4CCM_TEST_DEBUG << "Receiver info_get_status_exec_i::on_sample_lost" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : getter_invoke_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[ctor]
  getter_invoke_exec_i::getter_invoke_exec_i (
    IDL::traits<Getter_Test::CCM_Receiver_Context>::ref_type context,
    IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
    DDS4CCM_TEST_DEBUG << "Receivergetter_invoke_exec_i::getter_invoke_exec_i" << std::endl;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[ctor]

  getter_invoke_exec_i::~getter_invoke_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[dtor]
    // Your code here
    DDS4CCM_TEST_DEBUG << "Receiver getter_invoke_exec_i::~getter_invoke_exec_i" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_private_ops]


  /** Operations and attributes from getter_invoke */

  void
  getter_invoke_exec_i::start_timeout_get_one ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_timeout_get_one[void]
    DDS4CCM_TEST_DEBUG << "Receiver getter_invoke_exec_i::start_timeout_get_one" << std::endl;
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->timeout_get_one ();
    else
    {
      DDS4CCM_TEST_ERROR << "Receiver:\tgetter_invoke_exec_i::start_timeout_get_one - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_timeout_get_one[void]
  }

  void
  getter_invoke_exec_i::start_timeout_get_many ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_timeout_get_many[void]
    DDS4CCM_TEST_DEBUG << "Receiver: getter_invoke_exec_i::start_timeout_get_many" << std::endl;
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->timeout_get_many ();
    else
    {
      DDS4CCM_TEST_ERROR << "Receiver:\tgetter_invoke_exec_i::timeout_get_many - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_timeout_get_many[void]
  }

  void
  getter_invoke_exec_i::start_get_one (
      const std::string& key,
      int32_t iteration)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_get_one[_key_iteration]
    DDS4CCM_TEST_DEBUG << "Receiver getter_invoke_exec_i::start_get_one" << std::endl;
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->start_get_one (key, iteration);
    else
    {
      DDS4CCM_TEST_ERROR << "Receiver:\tgetter_invoke_exec_i::start_timeout_get_one - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_get_one[_key_iteration]
  }

  void
  getter_invoke_exec_i::start_get_many (
      int16_t keys,
      int32_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_get_many[_keys_iterations]
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->start_get_many (keys, iterations);
    else
    {
      DDS4CCM_TEST_ERROR << "Receiver:\tgetter_invoke_exec_i::start_get_many - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i::start_get_many[_keys_iterations]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  void
  Receiver_exec_i::start_get_one (
    const std::string &key,
    int32_t iteration)
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::start_get_one" << std::endl;
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
    if (tt_s)
    {
      this->tm_ = tt_s->schedule_trigger (
        CORBA::make_reference<GetOneHandler> (IDL::traits<Getter_Test::CCM_Receiver>::narrow (this->_lock()), key, iteration),
                                  CCM_TT::TT_Duration (0, 0));
    }
  }

  void
  Receiver_exec_i::start_get_many (
    int16_t keys,
    int32_t iterations)
  {
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
    if (tt_s)
    {
      this->tm_ = tt_s->schedule_trigger (
        CORBA::make_reference<GetManyHandler> (IDL::traits<Getter_Test::CCM_Receiver>::narrow (this->_lock()), keys, iterations),
                                  CCM_TT::TT_Duration (0, 0));
    }
  }

  void
  Receiver_exec_i::get_many (int16_t keys , int32_t iterations)
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::get_many" << std::endl;
    // this is very hard to test in a controlled environment.
    // When data arrives in DDS, the waiting ends and the
    // Getter starts to read the data. In this test we expected
    // therefor al least one, and less then but not exactly max_delivered_data.
    // On the other hand, when the user want to have all the
    // samples in DDS, one shouldn't use the wait method.
    // Since the spec is not clear about this, the test will
    // pass when at least one sample is returned.
    IDL::traits < CommonTestConnector::Getter>::ref_type getter =
      this->context_->get_connection_info_get_fresh_data ();

    DDS::Duration_t to (20, 0);
    getter->time_out (to);
    getter->max_delivered_data (40);
    DDS4CCM_TEST_DEBUG <<"Receiver_exec_i::get_many - "
      << "Start getting data from DDS: #keys <"
      << keys << "> - #iterations <" << iterations
      << "> with timeout: "
      << ::DDS::dds_write (getter->time_out ()) << " s."
      << std::endl;

    CommonTestMessageSeq gettertest_seq;
    ::CCM_DDS::ReadInfoSeq readinfo;
    bool const result = getter->get_many (gettertest_seq, readinfo);
    if (result)
    {
      if (gettertest_seq.empty ())
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::get_many - "
          "No data returned. number of samples: expected at "
          "least one - received <0>" << std::endl;
      }
      if (gettertest_seq.size () > 40)
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::get_many - "
          << "To much data returned. number of samples: "
          << "expected not more then 40 - received <"
          << gettertest_seq.size () << ">" << std::endl;
       }
      for (const CommonTestMessage &msg : gettertest_seq)
      {
        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::get_many - "
          "Returned data : " << msg << std::endl;
      }
    }
    else
    {
      DDS4CCM_TEST_ERROR << "ERROR: GET MANY: Time out occurred" << std::endl;
    }
    // Wait a while before reading.
    std::this_thread::sleep_for (std::chrono::seconds (3));
    this->read_many (keys, iterations, gettertest_seq);
  }

  void
  Receiver_exec_i::read_many (int16_t keys ,
                              int32_t iterations,
                              const CommonTestMessageSeq& gettertest_seq)
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::read_many" << std::endl;
    IDL::traits<CommonTestConnector::Reader>::ref_type reader =
      this->context_->get_connection_info_get_data ();

    CommonTestMessageSeq read_seq;
    ::CCM_DDS::ReadInfoSeq readinfos;
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::read_many - "
      "Start checking samples in DDS." << std::endl;
    reader->read_all (read_seq, readinfos);
    // we expect all samples written during the test for get one (KEY_1)
    // AND all samples written during the test for get many (number of keys)
    uint32_t expected = iterations * (keys + 1);
    if (read_seq.size () != expected)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::read_many - "
        << "Unexpected number of samples received: expected <"
        << expected << "> - received <" << read_seq.size () << ">."
        << std::endl;
    }
    for (const CommonTestMessage &msg : read_seq)
    {
      DDS4CCM_TEST_DEBUG << "READ ALL : Receiver_exec_i::read_many - "
        "Sample received: " << msg << std::endl;
    }

    for (int16_t key = 0; key < keys; ++key)
    {
      int32_t iter = 0;
      const std::string str_key ("KEY_" + std::to_string (key+1));
      for (const CommonTestMessage &msg : read_seq)
      {
        if (msg.key () == str_key)
          ++iter;
        if (iter > iterations)
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::read_many - "
            << "Unexpected number of iterations received for key <"
            << str_key << ": <" << iter << ">." << std::endl;
        }
      }
    }
    // check which sample states should be ALREADY_SEEN/FRESH_INFO
    for (CommonTestMessageSeq::size_type readed = 0; readed < read_seq.size (); ++readed)
    {
      CCM_DDS::AccessStatus received_access_status =
        readinfos[readed].access_status ();
      bool found = false;

      for (const CommonTestMessage &got : gettertest_seq)
      {
        if (read_seq[readed].key () == got.key () &&
            read_seq[readed].iteration () == got.iteration ())
        {
          if (received_access_status != CCM_DDS::AccessStatus::ALREADY_SEEN)
          {
            DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::read_many - "
              << "Unexpected access state received: "
              << "expected <CCM_DDS::AccessStatus::ALREADY_SEEN> - received <"
              << ::DDS::dds_write (received_access_status)
              << ">." << std::endl;
          }
          else
          {
            DDS4CCM_TEST_DEBUG << "Receiver_exec_i::read_many - "
              << "Access state received as expected <"
              << ::DDS::dds_write (received_access_status)
              << ">." << std::endl;
          }
          found = true;
          break;
        }
      }
      // Samples which are not read by get_many or get_one (the samples belonging to
      // KEY_1), should have FRESH_INFO as access status.
      if (!found && read_seq[readed].key () != "KEY_1")
      {
        if (received_access_status != CCM_DDS::AccessStatus::FRESH_INFO)
        {
          DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::read_many - "
            << "Unexpected access state received for sample "
            << read_seq[readed] << "expected <CCM_DDS::AccessStatus::FRESH_INFO> "
            << "- received <"
            << ::DDS::dds_write (received_access_status)
            << ">." << std::endl;
        }
      }
    }
  }


  void
  Receiver_exec_i::get_one (const std::string &key, int32_t iteration)
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::get_one" << std::endl;
    IDL::traits<CommonTestConnector::Getter>::ref_type getter =
      this->context_->get_connection_info_get_fresh_data ();

    DDS::Duration_t to (5, 0);
    getter->time_out (to);
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::get_one - "
      << "Start getting data from DDS: key <" << key << "> - iteration <"
      << iteration << "> with timeout: "
      << ::DDS::dds_write (getter->time_out ()) << " s."
      << std::endl;
    CommonTestMessage gettertest_info;
    ::CCM_DDS::ReadInfo readinfo;

    std::chrono::time_point<std::chrono::system_clock> start (
      std::chrono::system_clock::now ());

    if (getter->get_one (gettertest_info, readinfo))
    {
      if (this->instance_handle_ == ::DDS::HANDLE_NIL)
      {
        this->instance_handle_ = readinfo.instance_handle ();
      }
      std::chrono::milliseconds const elapsed_milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now () - start);
      DDS4CCM_TEST_DEBUG <<"Receiver_exec_i::get_one - "
        << "get_one took " << elapsed_milliseconds.count () << " ms."
        << std::endl;
      if (gettertest_info.key () !=  key)
      {
        DDS4CCM_TEST_ERROR << "ERROR: GET ONE: Expected key does "
          << "not match received key: expected <" << key
          << "> - received <" << gettertest_info.key ()
          << ">." << std::endl;
      }
      if (gettertest_info.iteration () != iteration)
      {
        DDS4CCM_TEST_ERROR << "ERROR: GET ONE: Expected iteration does "
          << "not match received iteration: expected <" << iteration
          << "> - received <" << gettertest_info.iteration ()
          << ">." << std::endl;
      }
      if (readinfo.source_timestamp ().sec () == 0 &&
          readinfo.source_timestamp ().nanosec () == 0)
      {
        DDS4CCM_TEST_ERROR << "ERROR: READ ONE LAST: "
          << "source timestamp seems to be invalid (nil) for "
          << gettertest_info << " - ReadInfo : "
          << ::DDS::dds_write (readinfo)
          << std::endl;
      }
      DDS4CCM_TEST_DEBUG <<"Receiver_exec_i::get_one - "
        << "Returned data : " << gettertest_info << " - ReadInfo : "
        << DDS::dds_write (readinfo) << std::endl;
    }
    else
    {
      DDS4CCM_TEST_ERROR << "ERROR: GET ONE: Time out while waiting for "
        << "key <" << key << "> - iteration <" << iteration << ">." << std::endl;
    }
  }

  void
  Receiver_exec_i::timeout_get_one ()
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::timeout_get_one" << std::endl;
    try
    {
      IDL::traits<CommonTestConnector::Getter>::ref_type getter =
        this->context_->get_connection_info_get_fresh_data ();

      DDS::Duration_t to (1, 0);
      getter->time_out (to);
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::timeout_get_one: "
        << "Start getting data from DDS: timeout: "
        << ::DDS::dds_write (getter->time_out ()) << " s."
        << std::endl;
      CommonTestMessage gettertest_info;
      CCM_DDS::ReadInfo readinfo;
      if (getter->get_one (gettertest_info, readinfo))
      {
        DDS4CCM_TEST_ERROR << "ERROR: TIMEOUT GET ONE: "
          "Returning true when get no data." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::timeout_get_one - "
          << "Expected to return no data." << std::endl;
      }
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: TIMEOUT GET ONE: Caught unexcepted "
        " InternalError exception: " << ex << std::endl;
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::timeout_get_one - "
        << "Exception caught : " << ex << std::endl;
    }
  }

  void
  Receiver_exec_i::timeout_get_many ()
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::timeout_get_many" << std::endl;
    try
    {
      IDL::traits<CommonTestConnector::Getter>::ref_type getter =
        this->context_->get_connection_info_get_fresh_data ();

      DDS::Duration_t to (3, 0);
      getter->time_out (to);
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::timeout_get_many - "
        << "Start getting data from DDS: timeout: "
        << ::DDS::dds_write (getter->time_out ()) << " s."
        << std::endl;
      CommonTestMessageSeq gettertest_seq;
      ::CCM_DDS::ReadInfoSeq readinfo;
      if (getter->get_many (gettertest_seq, readinfo))
      {
        DDS4CCM_TEST_ERROR << "ERROR: TIMEOUT GET MANY: "
          "Returning true when get no data." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Receiver_exec_i::timeout_get_many - "
          "Expected to return no data." << std::endl;
      }
    }
    catch (const CCM_DDS::InternalError &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: TIMEOUT GET MANY: Caught unexcepted "
        " InternalError exception: " << ex << std::endl;
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::timeout_get_many - "
        << "Exception caught : " << ex << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_activate" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->tm_)
    {
      this->tm_->cancel ();
      this->tm_.reset ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[get_info_get_status]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i:get_info_get_status " << std::endl;
    if (!this->info_get_status_)
      {
        this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
      }
    return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  }

  IDL::traits< CCM_GetInvoker>::ref_type
  Receiver_exec_i::get_getter_invoke ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[get_getter_invoke]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::get_getter_invoke" << std::endl;
    if (!this->getter_invoke_)
      {
        this->getter_invoke_ =
          CORBA::make_reference <getter_invoke_exec_i> (
              this->context_, IDL::traits<Getter_Test::CCM_Receiver>::narrow (this->_lock()));
      }
    return this->getter_invoke_;
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[get_getter_invoke]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::set_session_context" << std::endl;
    this->context_ = IDL::traits<Getter_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace Getter_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[factory]
extern "C" void
create_Getter_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Getter_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : getter_test_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
