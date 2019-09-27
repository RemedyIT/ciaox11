// -*- C++ -*-
/**
 * @file    filters_common_receiver_rg_runner_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Runs one iteration (run) for a receiver component.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "dds4ccm/tests/filters/common/read_get/receiver/filters_common_receiver_rg_runner_t.h"
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::ReadGetReceiverRunner_T (
    typename IDL::traits<CONTEXT_TYPE>::ref_type ctx)
  : context_ (ctx)
{
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::ReadGetReceiverRunner_T (
    typename IDL::traits<CONTEXT_TYPE>::ref_type ctx,
    uint16_t run)
  : context_ (ctx)
  , run_ (run)
{
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
uint16_t
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::run ()
{
  this->test_all ();
  ++this->run_;
  if (this->run_ < 5)
  {
    // Reset the parameters.
    this->set_filters ();
    this->check_filters ();

    IDL::traits< WriterStarter >::ref_type starter =
      this->context_->get_connection_writer_start ();
    starter->start_write ();
  }
  return this->run_;
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::pre_start_checks ()
{
  this->test_exception ();
  this->set_filters ();
  this->check_filters ();
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::get_received (
  uint32_t &received_4_getter,
  uint32_t &received_4_reader)
{
  received_4_getter += this->received_4_getter_;
  received_4_reader += this->received_4_reader_;
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_query_attributes ()
{
  ::DDS::StringSeq params (2);
  get_query_parameters (params, this->run_);

  IDL::traits< ::CommonTestConnector::Reader >::ref_type get_reader =
    this->context_->get_connection_get_port_data ();

  IDL::traits< ::CommonTestConnector::Reader >::ref_type read_reader =
    this->context_->get_connection_listen_port_data ();

  if (this->run_ == 4)
  {
    CCM_DDS::QueryFilter const empty_filter ("", DDS::StringSeq ());
    get_reader->query (empty_filter);
    read_reader->query (empty_filter);
  }
  else
  {
    CCM_DDS::QueryFilter const get_filter (QUERY_GETTER, params);
    get_reader->query (get_filter);
    DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_query_attributes - "
      << "Query set for the getter" << std::endl;

    CCM_DDS::QueryFilter const read_filter (QUERY_READER, params);
    read_reader->query (read_filter);
    DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_query_attributes - "
      << "Query set for the reader" << std::endl;
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_filter_attributes ()
{
  IDL::traits< ::CCM_DDS::ContentFilterSetting >::ref_type get_filter_config =
    this->context_->get_connection_get_port_filter_config ();

  IDL::traits< ::CCM_DDS::ContentFilterSetting >::ref_type read_filter_config =
    this->context_->get_connection_listen_port_filter_config ();

  ::DDS::StringSeq params (2);
  get_query_parameters (params, this->run_);

  get_filter_config->set_filter_parameters (params);
  DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_filter_attributes - "
    << "Filter parameters set for the getter <" << params << ">." << std::endl;

  read_filter_config->set_filter_parameters (params);
  DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_filter_attributes - "
    << "Filter parameters set for the reader <" << params << ">." << std::endl;
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_filters ()
{
  try
  {
    if (QUERY_ATTRIB)
    {
      this->set_query_attributes ();
    }
    else
    {
      this->set_filter_attributes ();
    }
  }
  catch (const CCM_DDS::NonChangeable &)
  {
    DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_filters - "
      "NonChangeable exception caught." << std::endl;
  }
  catch (const CCM_DDS::InternalError &)
  {
    DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_filters - "
      "Internal exception caught." << std::endl;
  }
  catch_dds4ccm_test_ex (ex, "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::set_filters")
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter (
  IDL::traits< CommonTestConnector::Reader >::ref_type reader,
  bool check_getter)
{
  bool error = false;
  std::string query, port;

  if (check_getter)
  {
    query = QUERY_GETTER;
    port = "GETTER";
  }
  else
  {
    query = QUERY_READER;
    port = "READER";
  }

  try
  {
    CCM_DDS::QueryFilter const filter = reader->query ();

    if (this->run_ == 4)
    {
      if (!filter.expression ().empty ())
      {
        DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter <"
          << port << "> - Unexpected query when retrieving filter: expected an "
          << "empty query - received <" << filter.expression () << ">."
          << std::endl;
        error = true;
      }
      if (filter.parameters ().size () != 0)
      {
        DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter <"
          << port << "> - Unexpected parameter list: expected an "
          << "empty parameter list - received <" << filter.parameters ()
          << ">." << std::endl;
        error = true;
      }
    }
    else
    {
      if (filter.expression () != query)
      {
        DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter <"
          << port << "> - Unexpected query when retrieving filter: expected <"
          << query << "> - received <" << filter.expression () << ">."
          << std::endl;
        error = true;
      }

      ::DDS::StringSeq param_check (2);
      get_query_parameters (param_check, this->run_);

      if (param_check != filter.parameters ())
      {
        DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter <"
          << port << "> - Unexpected parameter list: expected <"
          << param_check << "> - received <" << filter.parameters ()
          << ">." << std::endl;
        error = true;
      }
    }
  }
  catch (const CCM_DDS::InternalError &)
  {
    DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter <"
      << this->run_ << "> - "
      "Internal exception caught." << std::endl;
    error = true;
  }
  catch_dds4ccm_test_ex (ex,
    "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter <"+std::to_string (this->run_)+">")

  if (!error)
  {
    DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filter <"
      << this->run_ << "> - "
      << "Filter test past for the " << port << std::endl;
  }

}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_filters ()
{
  if (QUERY_ATTRIB)
  {
    IDL::traits< CommonTestConnector::Reader >::ref_type get_reader =
      this->context_->get_connection_get_port_data ();
    this->check_filter (get_reader, true);


    IDL::traits< CommonTestConnector::Reader >::ref_type read_reader =
      this->context_->get_connection_listen_port_data ();
    this->check_filter (read_reader, false);
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_non_changeable_filter (
  IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn,
  bool getter)
{
  std::string test;
  getter
    ? test = "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_non_changeable_filter (getter)"
    : test = "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_non_changeable_filter (reader)";
  try
  {
    if (getter)
    {
      // First check the current filter.
      CCM_DDS::QueryFilter filter =
        conn->pull_consumer_filter ();
      if (filter.expression () != QUERY_GETTER)
      {
        DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
          << "Retrieved an unexpected query: expected <" << QUERY_GETTER
          << "> - retrieved <" << filter.expression () << ">"
          << std::endl;
      }

      // Now be sure that the NonChangeable exception is thrown.
      filter.expression (QUERY_READER);
      conn->pull_consumer_filter (filter);
    }
    else
    {
      // First check the current filter.
      CCM_DDS::QueryFilter filter =
        conn->push_consumer_filter ();
      if (filter.expression () != QUERY_READER)
      {
        DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
          << "Retrieved an unexpected query: expected <" << QUERY_READER
          << "> - retrieved <" << filter.expression () << ">"
          << std::endl;
      }

      // Now be sure that the NonChangeable exception is thrown.
      filter.expression (QUERY_GETTER);
      conn->push_consumer_filter (filter);
    }
    DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
      << "No NonChangeable exception caught while changing the filter expression."
      << std::endl;
  }
  catch (CCM_DDS::NonChangeable const &)
  {
    DDS4CCM_TEST_DEBUG << "OK: " << test << " - "
      << "OK, caught a NonChangeable exception when trying the change the query."
      << std::endl;
  }
  catch_dds4ccm_test_ex (ex, test)

}


template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_non_changeable_filter ()
{
  std::string const test ("ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_non_changeable_filter");
  // Just need a connection in order to be able to get a reference to the
  // DDS4CCM connector itself.
  IDL::traits< ::CommonTestConnector::Reader >::ref_type reader =
    this->context_->get_connection_listen_port_data ();
  IDL::traits< ::CORBA::Object >::ref_type cmp = reader->_get_component ();
  if (!cmp)
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
      << "ERROR: Unable to get component interface." << std::endl;
    return;
  }
  IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
    IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
  if (!conn)
  {
    DDS4CCM_TEST_ERROR << "ERROR: " << test << " - "
      << "Unable to narrow connector interface." << std::endl;
    return;
  }

  this->test_non_changeable_filter (conn, true);
  this->test_non_changeable_filter (conn, false);
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_internal_error_filter (
  IDL::traits< CCM_DDS::ContentFilterSetting >::ref_type cft,
  bool getter)
{
  std::string test;
  getter
    ? test = "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_internal_error_filter (getter)"
    : test = "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_internal_error_filter (reader)";

  DDS::StringSeq params(1);
  params[0] = "3";
  try
  {
    cft->set_filter_parameters (params);

    DDS4CCM_TEST_ERROR << test << " - "
      << "ERROR: Did not caught a InternalError exception when trying to "
      << "set a wrong number of parameters." << std::endl;
  }
  catch (CCM_DDS::InternalError const &)
  {
    DDS4CCM_TEST_DEBUG << test << " - "
      << "OK, caught a InternalErr exception when trying to set a wrong number "
      << "of parameters." << std::endl;
  }
  catch_dds4ccm_test_ex (ex, test)
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_internal_error_filter ()
{
  this->test_internal_error_filter (
    this->context_->get_connection_listen_port_filter_config (),
    false);
  this->test_internal_error_filter (
    this->context_->get_connection_get_port_filter_config (),
    true);
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_exception ()
{
  if (QUERY_ATTRIB)
  {
    try
    {
      IDL::traits< ::CommonTestConnector::Reader >::ref_type get_reader =
        this->context_->get_connection_get_port_data ();
      DDS::StringSeq params (1);
      params[0] = "4";
      CCM_DDS::QueryFilter filter (QUERY_GETTER, params);
      get_reader->query (filter);
    }
    catch (const CCM_DDS::InternalError&)
    {
      DDS4CCM_TEST_DEBUG << "OK: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_exception - "
        << "Caught expected InternalErr. exception." << std::endl;
    }
    catch_dds4ccm_test_ex(ex, "test_exception")
  }
  else
  {
    this->test_non_changeable_filter ();
    this->test_internal_error_filter ();
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_iter_reader (
  CommonTestMessage const &sample,
  QueryParameters const &params)
{
  // The query parameters are set for the read at that moment.
  // The read returns all samples which meet the parameters.
  // This means that all samples are read again (reading more each run),
  // and the query is applied.
  ++this->received_4_reader_;

  if (sample.iteration () > params[0] &&
      sample.iteration () < params[1])
  {
    DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_iter_reader - "
      << "Unexpected sample with iteration <" << sample.iteration() << "> received. The receiver does not expect samples "
      << "with an iteration between <" << params[0] << "> and <"
      << params[1] << "> during run "
      << this->run_ << "." << std::endl;
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_iters_reader (
  CommonTestMessageSeq const &samples)
{
  // A content filtered topic is applied on a set. The samples received
  // during the first run are read again during the second (and every consecutive)
  // run, each set having it's own parameters still applied.

  // Samples contains all samples for a key

  CommonTestMessageSeq::size_type it = 0;

  for (uint16_t r = 1; r <= this->run_; ++r)
  {
    QueryParameters params (2);
    get_query_parameters (params, r);

    for (CommonTestMessageSeq::size_type s = it; s < samples.size (); ++s)
    {
      CommonTestMessage const msg = samples[s];
      DDS4CCM_TEST_DEBUG << "\tread: <" << msg << ">." << std::endl;
      this->check_iter_reader (msg, params);
      if (msg.iteration () == iterations ())
      {
        // A run is checked. Check the next.
        it = ++s;
        break;
      }
    }
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_iter_getter (
  CommonTestMessage const &sample,
  QueryParameters const &params)
{
  ++this->received_4_getter_;

  if (sample.iteration () <= params[0])
  {
    DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_iter_getter - "
      << "Unexpected sample received. The receiver does not expect samples "
      << "with an iteration <= <" << params[0] << "> during run "
      << this->run_ << "." << std::endl;
  }
  if (sample.iteration () > params[1])
  {
    DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::check_iter_getter - "
      << "Unexpected sample received. The receiver does not expect samples "
      << "with an iteration > <" << params[1] << "> during run "
      << this->run_ << "." << std::endl;
  }
}


template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all ()
{
  IDL::traits< ::CommonTestConnector::Reader >::ref_type reader =
    this->context_->get_connection_listen_port_data ();

  QueryParameters params (2);
  get_query_parameters (params, this->run_);

  switch (this->run_)
  {
    case 1:
      {
        CommonTestMessageSeq samples;
        CCM_DDS::ReadInfoSeq readinfo_seq;
        reader->read_all (samples, readinfo_seq);
        if (samples.size () == 0)
        {
          DDS4CCM_TEST_ERROR << "ERROR : ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all : "
            << "No samples available in Reader!" << std::endl;
        }
        DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all - about <"
          << samples.size () << "> to receive for run <" << this->run_ << ">." << std::endl;
        for (CommonTestMessage const &msg : samples)
        {
          DDS4CCM_TEST_DEBUG << "\tread: <" << msg << ">." << std::endl;
          this->check_iter_reader (msg, params);
        }
      }
      break;
    case 2:
      {
        DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all for run <"
                           << this->run_ << ">." << std::endl;
        // Use read_one_all during the second run
        for (uint16_t key = 0; key < keys (); ++key)
        {
          std::string const key_str ("KEY_"+std::to_string (key+1));

          CommonTestMessageSeq samples;
          CCM_DDS::ReadInfoSeq readinfo;
          reader->read_one_all (CommonTestMessage (key_str, 1),
            samples, readinfo, DDS::HANDLE_NIL);

          DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all - about <"
            << samples.size () << "> to receive for key <" << key_str << ">." << std::endl;
          if (QUERY_ATTRIB)
          {
            for (CommonTestMessage const &msg : samples)
            {
              DDS4CCM_TEST_DEBUG << "\tread: <" << msg << ">." << std::endl;
              this->check_iter_reader (msg, params);
            }
          }
          else
          {
            this->check_iters_reader (samples);
          }
        }
      }
      break;
    case 3:
      {
        DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all (read_one_last) - "
                              "for run <" << this->run_ << ">." <<  std::endl;
        for (uint16_t key = 0; key < keys (); ++key)
        {
          CommonTestMessage sample ("KEY_"+std::to_string (key+1), 1);
          CCM_DDS::ReadInfo readinfo;
          reader->read_one_last (sample, readinfo, DDS::HANDLE_NIL);
          DDS4CCM_TEST_DEBUG << "\tread: <" << sample << ">." << std::endl;
          this->check_iter_reader (sample, params);
        }
        DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all (read_last) - "
          << std::endl;
        CommonTestMessageSeq samples;
        CCM_DDS::ReadInfoSeq readinfos;
        reader->read_last (samples, readinfos);

        for (CommonTestMessage const &msg : samples)
        {
          DDS4CCM_TEST_DEBUG << "\tread: <" << msg << ">." << std::endl;
          this->check_iter_reader (msg, params);
        }
      }
      break;
    case 4:
      {
        DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all (read_all) - "
                               "for run <" << this->run_ << ">." <<  std::endl;
        CommonTestMessageSeq samples;
        CCM_DDS::ReadInfoSeq readinfo_seq;
        reader->read_all (samples, readinfo_seq);
        if (samples.size () == 0)
        {
          DDS4CCM_TEST_ERROR << "ERROR : ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all : "
            << "No samples available in Reader!" << std::endl;
        }
        DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::read_all - about <"
          << samples.size () << "> to receive." << std::endl;
        this->received_4_reader_ += ACE_Utils::truncate_cast<uint32_t> (samples.size ());
        for (CommonTestMessage const &msg : samples)
        {
          DDS4CCM_TEST_DEBUG << "\tread: <" << msg << ">." << std::endl;
        }
      }
      break;
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::get_all ()
{
  IDL::traits< ::CommonTestConnector::Getter >::ref_type getter =
    this->context_->get_connection_get_port_fresh_data ();

  QueryParameters params (2);
  get_query_parameters (params, this->run_);

  switch (this->run_)
  {
    case 1:
      {
        CommonTestMessage msg;
        CCM_DDS::ReadInfo readinfo;
        bool result = getter->get_one (msg, readinfo);
        DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::get_all - " << std::endl;
        if (result)
        {
          DDS4CCM_TEST_DEBUG << "\tgot: <" << msg << ">." << std::endl;
          this->check_iter_getter (msg, params);
        }
        else
        {
          DDS4CCM_TEST_ERROR << "ERROR : ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::get_all : "
            << "time out when retrieving first sample." << std::endl;
        }
        while (result)
        {
          result = getter->get_one (msg, readinfo);
          if (result)
          {
            DDS4CCM_TEST_DEBUG << "\tgot: <" << msg << ">." << std::endl;
            this->check_iter_getter (msg, params);
          }
        }
      }
      break;
    case 2:
      {
        // Use get_many during the second run.
        // this is very hard to test in a controlled environment.
        // When data arrives in DDS, the waiting ends and the
        // Getter starts to read the data. So we read until a timeout
        // occurs. We assume then that all samples were received.
        CommonTestMessageSeq samples;
        CCM_DDS::ReadInfoSeq readinfo;
        while (getter->get_many (samples, readinfo))
        {
          DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::get_all - about <"
            << samples.size () << "> samples to receive." << std::endl;
          for (CommonTestMessage const &msg : samples)
          {
            DDS4CCM_TEST_DEBUG << "\tgot: <" << msg << ">." << std::endl;
            if (msg.key() != "KEY_6")
            {
              this->check_iter_getter (msg, params);
            }

          }
          samples.clear ();
          readinfo.clear ();
        }

      }
      break;
    case 4:
      {
        // all should be received
        CommonTestMessageSeq samples;
        CCM_DDS::ReadInfoSeq readinfo;
        while (getter->get_many (samples, readinfo))
        {
          DDS4CCM_TEST_DEBUG << "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::get_all - about <"
            << samples.size () << "> samples to receive." << std::endl;
          for (CommonTestMessage const &msg : samples)
          {
            DDS4CCM_TEST_DEBUG << "\tgot: <" << msg << ">." << std::endl;
            this->check_iter_getter (msg, params);
          }
          samples.clear ();
          readinfo.clear ();
        }
      }
      break;
    default:
      // Nothing to do for the third run
      break;
  }
}

template<typename CONTEXT_TYPE, bool QUERY_ATTRIB>
void
ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_all ()
{
  std::string test ("GET ALL");
  try
  {
    if (this->run_ != 3)
      this->get_all ();
    test = "READ ALL";
    this->read_all ();
  }
  catch (CCM_DDS::InternalError const &ex)
  {
    DDS4CCM_TEST_ERROR << "ERROR: ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_all (" << test << ") - "
      "caught InternalError exception: " << ex << std::endl;
  }
  catch_dds4ccm_test_ex(ex, "ReadGetReceiverRunner_T<CONTEXT_TYPE, QUERY_ATTRIB>::test_all (" + test + ")")
}
