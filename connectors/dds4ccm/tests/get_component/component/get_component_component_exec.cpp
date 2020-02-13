// -*- C++ -*-
/**
 * @file    get_component_component_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Component implementation.
 *
 * Testing the _get_component method.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : get_component_component_impl.cpp[Header]

#include "get_component_component_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[user_global_impl]

namespace GetComponentComponent_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_listen_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[ctor]
  info_listen_data_listener_exec_i::info_listen_data_listener_exec_i (
    IDL::traits<CCM_GetComponentComponent_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[ctor]

  info_listen_data_listener_exec_i::~info_listen_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_listen_data_listener */

  void
  info_listen_data_listener_exec_i::on_one_data (
      const ::CommonTestMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_listen_data_listener_exec_i::on_many_data (
      const ::CommonTestMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_listen_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[ctor]
  info_listen_status_exec_i::info_listen_status_exec_i (
    IDL::traits<CCM_GetComponentComponent_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[ctor]

  info_listen_status_exec_i::~info_listen_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i[user_private_ops]


  /** Operations and attributes from info_listen_status */

  void
  info_listen_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_listen_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_listen_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_listen_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<CCM_GetComponentComponent_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : GetComponentComponent_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[ctor]
  GetComponentComponent_exec_i::GetComponentComponent_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[ctor]

  GetComponentComponent_exec_i::~GetComponentComponent_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_private_ops]
  void
  GetComponentComponent_exec_i::test_writer ()
  {
    try
    {
      IDL::traits< ::CommonTestConnector::Writer >::ref_type writer_data =
        this->context_->get_connection_info_write_data ();
      if (writer_data)
      {
        IDL::traits< ::CORBA::Object >::ref_type cmp = writer_data->_get_component ();
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
        if (!conn)
        {
          DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
            "Unable to get component interface of writer_data"
            << std::endl;
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "OK: GetComponentComponent_exec_i::test_writer - "
            "Writer on DDS_Write port returned a reference on "
            "_get_component." << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
          "writer_data is NIL." << std::endl;
      }
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
        << "CORBA exception caught while testing writer_data: "
        << ex << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
        << "Unknown exception caught while testing writer_data"
        << std::endl;
    }

    try
    {
      IDL::traits< ::DDS::DataWriter >::ref_type writer_dds_entity =
        this->context_->get_connection_info_write_dds_entity ();
      if (writer_dds_entity)
      {
        IDL::traits< ::CORBA::Object >::ref_type cmp = writer_dds_entity->_get_component ();
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
        if (!conn)
        {
          DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
            << "Unable to get component interface of writer_dds_entity"
            << std::endl;
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "OK: GetComponentComponent_exec_i::test_writer - "
            << "dds_entity on DDS_Write port returned a reference on _get_component."
            << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
          "writer_dds_entity is NIL." << std::endl;
      }
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
        << "CORBA exception caught while testing write_dds_entity: "
        << ex << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_writer - "
        "Unknown exception caught while testing writer_data" << std::endl;
    }
  }

  void
  GetComponentComponent_exec_i::test_getter ()
  {
    //Reader on DDS_Get
    try
    {
      IDL::traits< ::CommonTestConnector::Reader >::ref_type getter_data =
        this->context_->get_connection_info_get_data ();
      if (getter_data)
        {
          IDL::traits< ::CORBA::Object >::ref_type cmp = getter_data->_get_component ();
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
            IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
          if (!conn)
          {
            DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
              "Unable to get component interface of getter_data" << std::endl;
          }
          else
          {
            DDS4CCM_TEST_DEBUG << "OK: GetComponentComponent_exec_i::test_getter - "
              << "Reader on DDS_Get port returned a reference on _get_component."
              << std::endl;
          }
        }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
          "getter_data is NIL." << std::endl;
      }
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
        << "CORBA exception caught while testing getter_data: "
        << ex << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
        "Unknown exception caught while testing getter_data" << std::endl;
    }

    //Getter on DDS_Get
    try
    {
      IDL::traits< ::CommonTestConnector::Getter >::ref_type getter_fresh_data =
        this->context_->get_connection_info_get_fresh_data ();
      if (getter_fresh_data)
      {
        IDL::traits< ::CORBA::Object >::ref_type cmp = getter_fresh_data->_get_component ();
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
        if (!conn)
        {
          DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
            "Unable to get component interface of getter_fresh_data" << std::endl;
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "OK: GetComponentComponent_exec_i::test_getter - "
            << "Getter on DDS_Get port returned a reference on _get_component."
            << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
          "getter_fresh_data is NIL." << std::endl;
      }
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
        << "CORBA exception caught while testing getter_fresh_data: "
        << ex << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
        << "Unknown exception caught while testing getter_fresh_data"
        << std::endl;
    }

    //Getter on DDS_Get
    try
    {
      IDL::traits< ::DDS::DataReader >::ref_type getter_dds_entity =
        this->context_->get_connection_info_get_dds_entity ();
      if (getter_dds_entity)
      {
        IDL::traits< ::CORBA::Object >::ref_type cmp = getter_dds_entity->_get_component ();
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
        if (!conn)
        {
          DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
            "Unable to get component interface of getter_dds_entity" << std::endl;
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "OK: GetComponentComponent_exec_i::test_getter - "
            << "dds_entity on DDS_Get port returned a reference on _get_component."
            << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
          "getter_dds_entity is NIL." << std::endl;
      }
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
        << "CORBA exception caught while testing get_dds_entity: "
        << ex << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_getter - "
        "Unknown exception caught while testing get_dds_entity" << std::endl;
    }
  }

  void
  GetComponentComponent_exec_i::test_listener ()
  {
    try
    {
        //DDS_Listen
      IDL::traits< ::CommonTestConnector::Reader >::ref_type listen_data =
        this->context_->get_connection_info_listen_data ();
      if (listen_data)
      {
        IDL::traits< ::CORBA::Object >::ref_type cmp = listen_data->_get_component ();
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
        if (!conn)
        {
          DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
            "Unable to get component interface of listen_data" << std::endl;
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "OK: GetComponentComponent_exec_i::test_listener - "
            << "Reader on DDS_Listen port returned a reference on _get_component."
            << std::endl;
        }
      }
      else
        {
          DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
            "listen_data is NIL." << std::endl;
        }
    }
    catch (const ::CORBA::Exception& ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
        "CORBA exception caught while testing listen_data: " << ex << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
        "Unknown exception caught while testing listen_data" << std::endl;
    }

    try
    {
      IDL::traits< ::CCM_DDS::DataListenerControl >::ref_type  listen_data_control =
        this->context_->get_connection_info_listen_data_control ();
      if (listen_data_control)
      {
        IDL::traits< ::CORBA::Object >::ref_type cmp = listen_data_control->_get_component ();
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
          IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
        if (!conn)
        {
          DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
            "Unable to get component interface of listen_data_control" << std::endl;
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "OK: GetComponentComponent_exec_i::test_listener - "
            << "DataControl on DDS_Listen port returned a reference on _get_component."
            << std::endl;
        }
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
          "listen_data_control is NIL." << std::endl;
      }
    }
    catch (const ::CORBA::Exception& ex)
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
          << "CORBA exception caught while testing listen_data_control: "
          << ex << std::endl;
      }
    catch (...)
      {
        DDS4CCM_TEST_ERROR << "ERROR: GetComponentComponent_exec_i::test_listener - "
          "Unknown exception caught while testing listen_data_control" << std::endl;
      }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[user_private_ops]

  /** Session component operations */
  void GetComponentComponent_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "GetComponentComponent_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[configuration_complete]
  }

  void GetComponentComponent_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[ccm_activate]
    if (this->act_as_sender_)
    {
      this->test_writer ();
    }
    else
    {
      this->test_getter ();
      this->test_listener ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[ccm_activate]
  }

  void GetComponentComponent_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[ccm_passivate]
  }

  void GetComponentComponent_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[ccm_remove]
  }

  IDL::traits< ::CommonTestConnector::CCM_Listener>::ref_type
  GetComponentComponent_exec_i::get_info_listen_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[get_info_listen_data_listener]
  return nullptr;
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[get_info_listen_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  GetComponentComponent_exec_i::get_info_listen_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[get_info_listen_status]
  return nullptr;
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[get_info_listen_status]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  GetComponentComponent_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[get_info_get_status]
  }


  bool
  GetComponentComponent_exec_i::act_as_sender ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i::act_as_sender[getter]
    return this->act_as_sender_;
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i::act_as_sender[getter]
  }

  void
  GetComponentComponent_exec_i::act_as_sender (
      bool act_as_sender)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i::act_as_sender[setter]
    this->act_as_sender_ = act_as_sender;
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i::act_as_sender[setter]
  }

  /// Operations from Components::SessionComponent
  void
  GetComponentComponent_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl::GetComponentComponent_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_GetComponentComponent_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl::GetComponentComponent_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[user_namespace_end_impl]

} // namespace GetComponentComponent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : GetComponentComponent_Impl[factory]
extern "C" void
create_GetComponentComponent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <GetComponentComponent_Impl::GetComponentComponent_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : GetComponentComponent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : get_component_component_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
