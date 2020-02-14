// -*- C++ -*-
/**
 * @file    foo_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 attribute keywords test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_impl.cpp[Header]

#include "foo_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_global_impl]

namespace Foo_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_impl]
  void check_error (bool success, std::string const &test)
  {
    if (!success)
    {
      CIAOX11_TEST_ERROR << "ERROR: Found errors in the " << test
                        << " attribute keywords test." << std::endl;
    }
    else
    {
      CIAOX11_TEST_INFO << "OK: No errors found in the " << test
                        << " attribute keywords test." << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : my_foo_prov_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[ctor]
  my_foo_prov_exec_i::my_foo_prov_exec_i (
    IDL::traits<CCM_Foo_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[ctor]

  my_foo_prov_exec_i::~my_foo_prov_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[user_private_ops]


  /** Operations and attributes from my_foo_prov */

  int16_t
  my_foo_prov_exec_i::_cxx_short ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i::_cxx_short[getter]
    return this->_cxx_short_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i::_cxx_short[getter]
  }

  void
  my_foo_prov_exec_i::_cxx_short (
      int16_t _cxx_short)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i::_cxx_short[setter]
    this->_cxx_short_ = _cxx_short;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i::_cxx_short[setter]
  }

  int16_t
  my_foo_prov_exec_i::_cxx_while ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i::_cxx_while[getter]
    return this->_cxx_while_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i::_cxx_while[getter]
  }

  void
  my_foo_prov_exec_i::_cxx_while (
      int16_t _cxx_while)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i::_cxx_while[setter]
    this->_cxx_while_ = _cxx_while;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i::_cxx_while[setter]
  }

  /**
   * Component Executor Implementation Class : Foo_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ctor]
  Foo_exec_i::Foo_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ctor]

  Foo_exec_i::~Foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_private_ops]

  /** Session component operations */
  void Foo_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[configuration_complete]
  }

  void Foo_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_activate]
    check_error (this->and_attribute_success_,"attr_and");
    check_error (this->auto_attribute_success_,"attr_auto");
    check_error (this->int16_t_attribute_success_,"attr_int16_t");
    check_error (this->port_attribute_success_,"attr_port");
    check_error (this->mirrorport_attribute_success_,"attr_mirrorport");
    check_error (this->interface_attribute_success_,"attr_interface");
    check_error (this->abstract_attribute_success_,"attr_abstract");
    check_error (this->override_attribute_success_,"attr_override");
    check_error (this->m_foo_pt_component_success_, "attr_component");
    check_error (this->m_foo_pt_virtual_success_, "attr_virtual");
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_activate]
  }

  void Foo_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_passivate]
  }

  void Foo_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ccm_remove]
  }

  IDL::traits< CCM_MyFoo>::ref_type
  Foo_exec_i::get_my_foo_prov ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[get_my_foo_prov]
  if (!this->my_foo_prov_)
  {
    this->my_foo_prov_ = CORBA::make_reference <my_foo_prov_exec_i> (this->context_);
  }
  return this->my_foo_prov_;
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[get_my_foo_prov]
  }


  int16_t
  Foo_exec_i::m_foo_pt_component ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_foo_pt_component[getter]
    return this->m_foo_pt_component_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_foo_pt_component[getter]
  }

  void
  Foo_exec_i::m_foo_pt_component (
      int16_t m_foo_pt_component)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_foo_pt_component[setter]
    if (m_foo_pt_component != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: m_foo_pt_component != 22, it is "
                         << m_foo_pt_component << std::endl;
    }
    else this->m_foo_pt_component_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_foo_pt_component[setter]
  }

  int16_t
  Foo_exec_i::m_foo_pt_virtual ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_foo_pt_virtual[getter]
    return this->m_foo_pt_virtual_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_foo_pt_virtual[getter]
  }

  void
  Foo_exec_i::m_foo_pt_virtual (
      int16_t m_foo_pt_virtual)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::m_foo_pt_virtual[setter]
    if (m_foo_pt_virtual != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: m_foo_pt_virtual != 22, it is "
                         << m_foo_pt_virtual << std::endl;
    }
    else this->m_foo_pt_virtual_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::m_foo_pt_virtual[setter]
  }

  int16_t
  Foo_exec_i::_cxx_and ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::_cxx_and[getter]
    return this->_cxx_and_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::_cxx_and[getter]
  }

  void
  Foo_exec_i::_cxx_and (
      int16_t _cxx_and)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::_cxx_and[setter]
    if (_cxx_and != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_and != 22, it is "
                         << _cxx_and << std::endl;
    }
    else this->and_attribute_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::_cxx_and[setter]
  }

  int16_t
  Foo_exec_i::_cxx_auto ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::_cxx_auto[getter]
    return this->_cxx_auto_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::_cxx_auto[getter]
  }

  void
  Foo_exec_i::_cxx_auto (
      int16_t _cxx_auto)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::_cxx_auto[setter]
    if (_cxx_auto != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_auto != 22, it is "
                         << _cxx_auto << std::endl;
    }
    else this->auto_attribute_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::_cxx_auto[setter]
  }

  int16_t
  Foo_exec_i::_cxx_int16_t ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::_cxx_int16_t[getter]
    return this->_cxx_int16_t_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::_cxx_int16_t[getter]
  }

  void
  Foo_exec_i::_cxx_int16_t (
      int16_t _cxx_int16_t)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::_cxx_int16_t[setter]
    if (_cxx_int16_t != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_int16_t != 22, it is "
                         << _cxx_int16_t << std::endl;
    }
    else this->int16_t_attribute_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::_cxx_int16_t[setter]
  }

  int16_t
  Foo_exec_i::port ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::port[getter]
    return this->port_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::port[getter]
  }

  void
  Foo_exec_i::port (
      int16_t port)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::port[setter]
    if (port != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_port != 22, it is "
                         << port<< std::endl;
    }
    else this->port_attribute_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::port[setter]
  }

  int16_t
  Foo_exec_i::mirrorport ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::mirrorport[getter]
    return this->mirrorport_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::mirrorport[getter]
  }

  void
  Foo_exec_i::mirrorport (
      int16_t mirrorport)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::mirrorport[setter]
    if (mirrorport != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: my__mirrorport != 22, it is "
                         << mirrorport<< std::endl;
    }
    else this->mirrorport_attribute_success_= true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::mirrorport[setter]
  }

  int16_t
  Foo_exec_i::interface ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::interface[getter]
    return this->interface_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::interface[getter]
  }

  void
  Foo_exec_i::interface (
      int16_t interface)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::interface[setter]
    if (interface != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_interface != 22, it is "
                         << interface<< std::endl;
    }
    else this->interface_attribute_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::interface[setter]
  }

  int16_t
  Foo_exec_i::abstract ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::abstract[getter]
    return this->abstract_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::abstract[getter]
  }

  void
  Foo_exec_i::abstract (
      int16_t abstract)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::abstract[setter]
    if (abstract != 22)
    {
      CIAOX11_TEST_ERROR << "ERROR: my_abstract != 22, it is "
                         << abstract << std::endl;
    }
    else this->abstract_attribute_success_ = true;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::abstract[setter]
  }

  ::Bar
  Foo_exec_i::override ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::override[getter]
    return this->override_;
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::override[getter]
  }

  void
  Foo_exec_i::override (
      const ::Bar& override)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i::override[setter]
    this->override_attribute_success_ = true;

    if (override._cxx_char() != 3)
    {
      this->override_attribute_success_ = false;
      CIAOX11_TEST_ERROR << "ERROR: override char value != 3, it is "
                           <<  override._cxx_char() << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i::override[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Foo_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[set_session_context]
    this->context_ = IDL::traits<CCM_Foo_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_end_impl]

} // namespace Foo_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[factory]
extern "C" void
create_Foo_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Foo_Impl::Foo_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
