// -*- C++ -*-
/**
 * @file    non_changeable_component_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : non_changeable_component_impl.cpp[Header]

#include "non_changeable_component_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[user_global_impl]

namespace NonChangeableComponent_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<CCM_NonChangeableComponent_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : NonChangeableComponent_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ctor]
  NonChangeableComponent_exec_i::NonChangeableComponent_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ctor]

  NonChangeableComponent_exec_i::~NonChangeableComponent_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_private_ops]
  bool
  NonChangeableComponent_exec_i::test_topic_name (
    IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn)
  {
    try
    {
      if (conn->topic_name () != "NonChangeable")
      {
        DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_topic_name - "
          << "Unexpected topic_name found. Expected <NonChangeable> - found <"
          << conn->topic_name () << ">." << std::endl;
      }

      conn->topic_name ("nonchangeable_test");
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::test_topic_name - "
        << "Able to reset topic name without an exception." << std::endl;
      return true;
    }
    catch (::CCM_DDS::NonChangeable const &)
    {
      DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_topic_name - "
        << "Unable to reset topic name." << std::endl;
    }
    catch_dds4ccm_test_ex (ex, "NonChangeableComponent_exec_i::test_topic_name")
    return false;
  }

  bool
  NonChangeableComponent_exec_i::test_domain_id (
    IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn)
  {
    try
    {
      // First retrieve the domain_id
      DDS::DomainId_t domain_id = -1;
      const char * domain = std::getenv ("DDS4CCM_DEFAULT_DOMAIN_ID");
      if (domain)
      {
        domain_id = std::atoi (domain);
      }
      if (domain_id != -1)
      {
        if (domain_id != conn->domain_id ())
        {
          DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_domain_id - "
            << "Unexpected domain_id found. Expected <" << domain_id << "> - found <"
            << conn->domain_id () << ">." << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_domain_id - "
          << "Unable to retrieve domain_id." << std::endl;
      }

      conn->domain_id (254);
      DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_domain_id - "
        << "Able to set domain id without an exception." << std::endl;
    }
    catch (::CCM_DDS::NonChangeable const &)
    {
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::test_domain_id - "
        << "Caught expected NonChangeable exception." << std::endl;
      return true;
    }
    catch_dds4ccm_test_ex (ex, "NonChangeableComponent_exec_i::test_domain_id")
    return false;
  }

  bool
  NonChangeableComponent_exec_i::test_qos_profile (
    IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn)
  {
    try
    {
      if (conn->qos_profile () != "nonchangeablelibrary#NonChangeableProfile")
      {
        DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_qos_profile - "
          << "Unexpected qos_profile found. Expected "
          << "<nonchangeablelibrary#NonChangeableProfile> - found <"
          << conn->qos_profile () << ">." << std::endl;
      }

      conn->qos_profile ("non_changeable_profile");
      DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_qos_profile - "
        << "Able to set qos profile without an exception." << std::endl;
    }
    catch (::CCM_DDS::NonChangeable const &)
    {
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::test_qos_profile - "
        << "Caught expected NonChangeable exception." << std::endl;
      return true;
    }
    catch_dds4ccm_test_ex (ex, "NonChangeableComponent_exec_i::test_qos_profile")
    return false;
  }

  bool
  NonChangeableComponent_exec_i::test_filter (
    IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn)
  {
    try
    {
      // Retrieving the filter is tested in the filters tests..
      ::CCM_DDS::QueryFilter filter;
      filter.expression ("na");
      conn->pull_consumer_filter (filter);
      DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::test_filter - "
        << "Able to set qos profile without an exception." << std::endl;
    }
    catch (::CCM_DDS::NonChangeable const &)
    {
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::test_filter - "
        << "Caught expected NonChangeable exception." << std::endl;
      return true;
    }
    catch_dds4ccm_test_ex (ex, "NonChangeableComponent_exec_i::test_filter")
    return false;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[user_private_ops]

  /** Session component operations */
  void NonChangeableComponent_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[configuration_complete]
  }

  void NonChangeableComponent_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ccm_activate]
    IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn;
    try
    {
      IDL::traits< ::CommonTestConnector::Reader >::ref_type getter =
        this->context_->get_connection_info_get_data ();
      IDL::traits< ::CORBA::Object >::ref_type cmp = getter->_get_component ();
      conn = IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
      if (!conn)
      {
        DDS4CCM_TEST_ERROR << "ERROR: NonChangeableComponent_exec_i::ccm_activate - "
          "Unable to get component interface of the Getter"
          << std::endl;
        return;
      }
    }
    catch_dds4ccm_test_ex (ex, "non_changeable_component_exec_i::ccm_activate")

    if (this->test_topic_name (conn))
    {
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::ccm_activate - "
        << "Set topic_name test passed." << std::endl;
    }
    if (this->test_domain_id (conn))
    {
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::ccm_activate - "
        << "Set domain_id test passed." << std::endl;
    }
    if (this->test_qos_profile (conn))
    {
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::ccm_activate - "
        << "Set qos_profile test passed." << std::endl;
    }
    if (this->test_filter (conn))
    {
      DDS4CCM_TEST_DEBUG << "NonChangeableComponent_exec_i::ccm_activate - "
        << "Set filter test passed." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ccm_activate]
  }

  void NonChangeableComponent_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ccm_passivate]
  }

  void NonChangeableComponent_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  NonChangeableComponent_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[get_info_get_status]
  }

  /// Operations from Components::SessionComponent
  void
  NonChangeableComponent_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_NonChangeableComponent_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl::NonChangeableComponent_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[user_namespace_end_impl]

} // namespace NonChangeableComponent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : NonChangeableComponent_Impl[factory]
extern "C" void
create_NonChangeableComponent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <NonChangeableComponent_Impl::NonChangeableComponent_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : NonChangeableComponent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : non_changeable_component_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
