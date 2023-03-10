// -*- C++ -*-
/**
 * @file    foo_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 attribute keywords test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_FOO_EXEC_H_BCHJJJGJ_INCLUDED__
#define __RIDL_FOO_EXEC_H_BCHJJJGJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : foo_impl.h[Header]

#pragma once

#include "fooEC.h"

#include /**/ "foo_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : foo_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : foo_impl.h[user_global_decl]

/// Namespace for implementation of Foo component
namespace Foo_Impl
{
  /// Forward declarations
  class Foo_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_decl]


  /// Executor implementation class for my_foo_prov facet
  class my_foo_prov_exec_i final
    : public IDL::traits<CCM_MyFoo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    my_foo_prov_exec_i (
        IDL::traits< CCM_Foo_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[ctor]

    /// Destructor
    ~my_foo_prov_exec_i () override;


    /** @name Attributes from CCM_MyFoo */
    //@{
    int16_t _cxx_short () override;
    void _cxx_short (int16_t _cxx_short) override;
    int16_t _cxx_while () override;
    void _cxx_while (int16_t _cxx_while) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<CCM_Foo_Context>::ref_type context_;

    /** @name Members to store attribute values from CCM_MyFoo */
    //@{
    /// Class member storing value of short attribute
    int16_t _cxx_short_{};
    /// Class member storing value of while attribute
    int16_t _cxx_while_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::my_foo_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::my_foo_prov_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Foo_exec_i
  class Foo_exec_i final
    : public virtual IDL::traits<CCM_Foo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[ctor]
    /// Constructor
    Foo_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[ctor]
    /// Destructor
    ~Foo_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the my_foo_prov facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<CCM_MyFoo>::ref_type get_my_foo_prov () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute m_foo_pt_component
    int16_t m_foo_pt_component () override;
    void m_foo_pt_component (int16_t m_foo_pt_component) override;

    /// Attribute m_foo_pt_virtual
    int16_t m_foo_pt_virtual () override;
    void m_foo_pt_virtual (int16_t m_foo_pt_virtual) override;

    /// Attribute _cxx_and
    int16_t _cxx_and () override;
    void _cxx_and (int16_t _cxx_and) override;

    /// Attribute _cxx_auto
    int16_t _cxx_auto () override;
    void _cxx_auto (int16_t _cxx_auto) override;

    /// Attribute _cxx_int16_t
    int16_t _cxx_int16_t () override;
    void _cxx_int16_t (int16_t _cxx_int16_t) override;

    /// Attribute port
    int16_t port () override;
    void port (int16_t port) override;

    /// Attribute mirrorport
    int16_t mirrorport () override;
    void mirrorport (int16_t mirrorport) override;

    /// Attribute interface
    int16_t interface () override;
    void interface (int16_t interface) override;

    /// Attribute abstract
    int16_t abstract () override;
    void abstract (int16_t abstract) override;

    /// Attribute override
    ::Bar override () override;
    void override (const ::Bar& override) override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<CCM_Foo_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of m_foo_pt_component attribute
    int16_t m_foo_pt_component_{};
    /// Class member storing value of m_foo_pt_virtual attribute
    int16_t m_foo_pt_virtual_{};
    /// Class member storing value of and attribute
    int16_t _cxx_and_{};
    /// Class member storing value of auto attribute
    int16_t _cxx_auto_{};
    /// Class member storing value of int16_t attribute
    int16_t _cxx_int16_t_{};
    /// Class member storing value of port attribute
    int16_t port_{};
    /// Class member storing value of mirrorport attribute
    int16_t mirrorport_{};
    /// Class member storing value of interface attribute
    int16_t interface_{};
    /// Class member storing value of abstract attribute
    int16_t abstract_{};
    /// Class member storing value of override attribute
    ::Bar override_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<CCM_MyFoo>::ref_type my_foo_prov_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_members]
    bool and_attribute_success_ {};
    bool auto_attribute_success_ {};
    bool int16_t_attribute_success_ {};
    bool port_attribute_success_ {};
    bool mirrorport_attribute_success_ {};
    bool interface_attribute_success_ {};
    bool abstract_attribute_success_ {};
    bool override_attribute_success_ {};
    bool m_foo_pt_component_success_ {};
    bool m_foo_pt_virtual_success_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl::Foo_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl::Foo_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Foo_exec_i(const Foo_exec_i&) = delete;
    Foo_exec_i(Foo_exec_i&&) = delete;
    Foo_exec_i& operator=(const Foo_exec_i&) = delete;
    Foo_exec_i& operator=(Foo_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[user_namespace_end_decl]

} // namespace Foo_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Foo_Impl[factory]
extern "C" FOO_EXEC_Export  void
create_Foo_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Foo_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : foo_impl.h[Footer]

#endif /* __RIDL_FOO_EXEC_H_BCHJJJGJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
