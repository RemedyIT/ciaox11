// -*- C++ -*-
/**
 * @file    bst_bst_comp_exec.cpp
 * @author  Johnny Willemsen
 *
 * @brief   CIAOX11 bounded attribute test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : bst_bst_comp_impl.cpp[Header]

#include "bst_bst_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[user_global_impl]

namespace BST_BST_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : BST_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[ctor]
  BST_comp_exec_i::BST_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[ctor]

  BST_comp_exec_i::~BST_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[user_private_ops]

  /** Session component operations */
  void BST_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[configuration_complete]
  }

  void BST_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[ccm_activate]
  }

  void BST_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[ccm_passivate]
  }

  void BST_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[ccm_remove]
    if (!this->MyBoundString_set_)
      CIAOX11_TEST_ERROR << "ERROR: MyBoundString not set" << std::endl;
    else
      CIAOX11_TEST_DEBUG << "OK: MyBoundString set" << std::endl;

    if (!this->MyUnboundedString_set_)
      CIAOX11_TEST_ERROR << "ERROR: MyUnboundedString not set" << std::endl;
    else
      CIAOX11_TEST_DEBUG << "OK: MyUnboundedString set" << std::endl;

    if (!this->MyStruct_set_)
      CIAOX11_TEST_ERROR << "ERROR: MyStruct_set not set" << std::endl;
    else
      CIAOX11_TEST_DEBUG << "OK: MyStruct_set set" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[ccm_remove]
  }


  ::BST::MyBoundedStringType
  BST_comp_exec_i::MyBoundedString ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i::MyBoundedString[getter]
    return this->MyBoundedString_;
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i::MyBoundedString[getter]
  }

  void
  BST_comp_exec_i::MyBoundedString (
      const ::BST::MyBoundedStringType& MyBoundedString)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i::MyBoundedString[setter]
    this->MyBoundString_set_ = true;
    if (MyBoundedString != "bounded string value")
      CIAOX11_TEST_ERROR << "ERROR: received invalid bounded string value" << std::endl;
    else
      CIAOX11_TEST_DEBUG << "OK: correct bounded string value" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i::MyBoundedString[setter]
  }

  ::BST::MyStringTypedef
  BST_comp_exec_i::MyUnboundedString ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i::MyUnboundedString[getter]
    return this->MyUnboundedString_;
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i::MyUnboundedString[getter]
  }

  void
  BST_comp_exec_i::MyUnboundedString (
      const ::BST::MyStringTypedef& MyUnboundedString)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i::MyUnboundedString[setter]
    this->MyUnboundedString_set_ = true;
    if (MyUnboundedString != "unbounded string value")
      CIAOX11_TEST_ERROR << "ERROR: received invalid unbounded string value" << std::endl;
    else
      CIAOX11_TEST_DEBUG << "OK: correct unbounded string value" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i::MyUnboundedString[setter]
  }

  ::BST::MyStructType
  BST_comp_exec_i::MyStruct ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i::MyStruct[getter]
    return this->MyStruct_;
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i::MyStruct[getter]
  }

  void
  BST_comp_exec_i::MyStruct (
      const ::BST::MyStructType& MyStruct)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i::MyStruct[setter]
    this->MyStruct_set_ = true;
    if ((MyStruct.unboundedString () != "struct unbstring") &&
        (MyStruct.boundedString () != "struct bstring"))
      CIAOX11_TEST_ERROR << "ERROR: received invalid struct value" << std::endl;
    else
      CIAOX11_TEST_DEBUG << "OK: correct struct value" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i::MyStruct[setter]
  }

  /// Operations from Components::SessionComponent
  void
  BST_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl::BST_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<BST::CCM_BST_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl::BST_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[user_namespace_end_impl]

} // namespace BST_BST_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : BST_BST_comp_Impl[factory]
extern "C" void
create_BST_BST_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <BST_BST_comp_Impl::BST_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : BST_BST_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : bst_bst_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
