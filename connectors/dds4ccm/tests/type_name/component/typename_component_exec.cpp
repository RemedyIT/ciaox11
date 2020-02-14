// -*- C++ -*-
/**
 * @file    typename_component_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : typename_component_impl.cpp[Header]

#include "typename_component_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[user_global_impl]

namespace TypeNameComponent_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : TypeNameComponent_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[ctor]
  TypeNameComponent_exec_i::TypeNameComponent_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[ctor]

  TypeNameComponent_exec_i::~TypeNameComponent_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_public_ops]
  void TypeNameComponent_exec_i::check_typename_global ()
  {
    try
    {
      IDL::traits< ::TypeNameConnector::Writer>::ref_type writer =
        this->context_->get_connection_type_name_writer_data ();
      IDL::traits< ::CORBA::Object>::ref_type cmp = writer->_get_component ();
      if (!cmp)
      {
        DDS4CCM_TEST_ERROR << "TypeNameComponent_exec_i::check_typename_global - "
          "ERROR: Unable to get component interface." << std::endl;
        return;
      }
      IDL::traits< ::TypeNameConnector::CCM_DDS_Event>::ref_type conn =
        IDL::traits< ::TypeNameConnector::CCM_DDS_Event >::narrow (cmp);
      if (!conn)
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_global - "
          "Unable to narrow connector interface." << std::endl;
        return;
      }

      std::string const type_name = conn->type_name ();

      if (type_name != "TypeNameMessage")
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_global - "
          << "Unexpected type_name found: expected <TypeNameMessage> - found <"
          << type_name << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "OK: TypeNameComponent_exec_i::check_typename_global - "
          << "Expected type_name found: <TypeNameMessage>" << std::endl;
      }
    }
    catch_dds4ccm_test_ex(ex, "TypeNameComponent_exec_i::check_typename_global")
  }

  void TypeNameComponent_exec_i::check_typename_of_module ()
  {
    try
    {
      IDL::traits< ::TypeNameModule::TypeNameModuleConnector::Writer>::ref_type writer =
        this->context_->get_connection_type_name_module_writer_data ();
      IDL::traits< ::CORBA::Object>::ref_type cmp = writer->_get_component ();
      if (!cmp)
      {
        DDS4CCM_TEST_ERROR << "TypeNameComponent_exec_i::check_typename_of_module - "
          "ERROR: Unable to get component interface." << std::endl;
        return;
      }
      IDL::traits< ::TypeNameModule::TypeNameModuleConnector::CCM_DDS_Event>::ref_type conn =
        IDL::traits< ::TypeNameModule::TypeNameModuleConnector::CCM_DDS_Event >::narrow (cmp);
      if (!conn)
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_of_module - "
          "Unable to narrow connector interface." << std::endl;
        return;
      }

      std::string const type_name = conn->type_name ();

      if (type_name != "TypeNameModule::TypeNameMessage")
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_of_module - "
          << "Unexpected type_name found: expected <TypeNameModule::TypeNameMessage> - found <"
          << type_name << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "OK: TypeNameComponent_exec_i::check_typename_of_module - "
          << "Expected type_name found: <TypeNameModule::TypeNameMessage>" << std::endl;
      }
    }
    catch_dds4ccm_test_ex(ex, "TypeNameComponent_exec_i::check_typename_of_module")
  }

  void TypeNameComponent_exec_i::check_typename_of_module_in_module ()
  {
    try
    {
      IDL::traits< ::TypeNameModule::TypeNameModuleModule::TypeNameModuleModuleConnector::Writer>::ref_type writer =
        this->context_->get_connection_type_name_module_module_writer_data ();
      IDL::traits< ::CORBA::Object>::ref_type cmp = writer->_get_component ();
      if (!cmp)
      {
        DDS4CCM_TEST_ERROR << "TypeNameComponent_exec_i::check_typename_of_module_in_module - "
          "ERROR: Unable to get component interface." << std::endl;
        return;
      }
      IDL::traits< ::TypeNameModule::TypeNameModuleModule::TypeNameModuleModuleConnector::CCM_DDS_Event>::ref_type conn =
        IDL::traits< ::TypeNameModule::TypeNameModuleModule::TypeNameModuleModuleConnector::CCM_DDS_Event >::narrow (cmp);
      if (!conn)
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_of_module_in_module - "
          "Unable to narrow connector interface." << std::endl;
        return;
      }

      std::string const type_name = conn->type_name ();

      if (type_name != "TypeNameModule::TypeNameModuleModule::TypeNameMessage")
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_of_module_in_module - "
          << "Unexpected type_name found: expected <TypeNameModule::TypeNameModuleModule::TypeNameMessage> - found <"
          << type_name << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "OK: TypeNameComponent_exec_i::check_typename_of_module_in_module - "
          << "Expected type_name found: <TypeNameModule::TypeNameModuleModule::TypeNameMessage>" << std::endl;
      }
    }
    catch_dds4ccm_test_ex(ex, "TypeNameComponent_exec_i::check_typename_of_module_in_module")
  }

  void TypeNameComponent_exec_i::check_typename_of_module_in_module_2 ()
  {
    try
    {
      IDL::traits< ::TypeNameModule::TypeNameModuleModule2::TypeNameModuleModule2Connector::Writer>::ref_type writer =
        this->context_->get_connection_type_name_module_module_2_writer_data ();
      IDL::traits< ::CORBA::Object>::ref_type cmp = writer->_get_component ();
      if (!cmp)
      {
        DDS4CCM_TEST_ERROR << "TypeNameComponent_exec_i::check_typename_of_module_in_module_2 - "
          "ERROR: Unable to get component interface." << std::endl;
        return;
      }
      IDL::traits< ::TypeNameModule::TypeNameModuleModule2::TypeNameModuleModule2Connector::CCM_DDS_Event>::ref_type conn =
        IDL::traits< ::TypeNameModule::TypeNameModuleModule2::TypeNameModuleModule2Connector::CCM_DDS_Event >::narrow (cmp);
      if (!conn)
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_of_module_in_module_2 - "
          "Unable to narrow connector interface." << std::endl;
        return;
      }

      std::string const type_name = conn->type_name ();

      if (type_name != "TypeNameModule::TypeNameModuleModule2::TypeNameMsg")
      {
        DDS4CCM_TEST_ERROR << "ERROR: TypeNameComponent_exec_i::check_typename_of_module_in_module_2 - "
          << "Unexpected type_name found: expected <TypeNameModule::TypeNameModuleModule2::TypeNameMsg> - found <"
          << type_name << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "OK: TypeNameComponent_exec_i::check_typename_of_module_in_module_2 - "
          << "Expected type_name found: <TypeNameModule::TypeNameModuleModule2::TypeNameMsg>" << std::endl;
      }
    }
    catch_dds4ccm_test_ex(ex, "TypeNameComponent_exec_i::check_typename_of_module_in_module_2")
  }
  //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[user_private_ops]

  /** Session component operations */
  void TypeNameComponent_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[configuration_complete]
  }

  void TypeNameComponent_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[ccm_activate]
    this->check_typename_global ();
    this->check_typename_of_module ();
    this->check_typename_of_module_in_module ();
    this->check_typename_of_module_in_module_2 ();
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[ccm_activate]
  }

  void TypeNameComponent_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[ccm_passivate]
  }

  void TypeNameComponent_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  TypeNameComponent_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl::TypeNameComponent_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_TypeNameComponent_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl::TypeNameComponent_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[user_namespace_end_impl]

} // namespace TypeNameComponent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : TypeNameComponent_Impl[factory]
extern "C" void
create_TypeNameComponent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <TypeNameComponent_Impl::TypeNameComponent_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : TypeNameComponent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : typename_component_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
