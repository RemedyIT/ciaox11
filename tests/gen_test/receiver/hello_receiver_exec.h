// -*- C++ -*-
/**
 * @file    hello_receiver_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   Receiver component header
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_HELLO_RECEIVER_EXEC_H_IIJAAGGI_INCLUDED__
#define __RIDL_HELLO_RECEIVER_EXEC_H_IIJAAGGI_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_receiver_impl.h[Header]

#pragma once

#include "hello_receiverEC.h"

#include /**/ "hello_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : hello_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : hello_receiver_impl.h[user_global_decl]

/// Namespace for implementation of Hello::Receiver component
namespace Hello_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for rec_listen_port_foo_prov facet
  class rec_listen_port_foo_prov_exec_i final
    : public IDL::traits<::Hello::CCM_MyFoo>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    rec_listen_port_foo_prov_exec_i (
      IDL::traits<Hello::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[ctor]

    /// Destructor
    ~rec_listen_port_foo_prov_exec_i () override;

    /** @name Operations from ::Hello::CCM_MyFoo */
    //@{

    int32_t
    hello (
        int32_t answer) override;
    //@}

    /** @name Attributes from ::Hello::CCM_MyFoo */
    //@{
    int16_t interface_attrib () override;
    void interface_attrib (int16_t interface_attrib) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Hello::CCM_Receiver_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Hello::CCM_MyFoo */
    //@{
    /// Class member storing value of interface_attrib attribute
    int16_t interface_attrib_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_foo_prov_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for rec_listen_port_bar_prov facet
  class rec_listen_port_bar_prov_exec_i final
    : public IDL::traits<::Hello::CCM_MyBar>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    rec_listen_port_bar_prov_exec_i (
      IDL::traits<Hello::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[ctor]

    /// Destructor
    ~rec_listen_port_bar_prov_exec_i () override;

    /** @name Operations from ::Hello::CCM_MyBar */
    //@{

    void
    bye (
        int32_t answer) override;
    //@}

    /** @name Attributes from ::Hello::CCM_MyBar */
    //@{
    int16_t bar_attrib () override;
    void bar_attrib (int16_t bar_attrib) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::Hello::CCM_Receiver_Context>::ref_type context_;

    /** @name Members to store attribute values from ::Hello::CCM_MyBar */
    //@{
    /// Class member storing value of bar_attrib attribute
    int16_t bar_attrib_{};
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::rec_listen_port_bar_prov_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits<::Hello::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the rec_listen_port_foo_prov facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::Hello::CCM_MyFoo>::ref_type get_rec_listen_port_foo_prov () override;
    /// Factory method and getter for the rec_listen_port_bar_prov facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::Hello::CCM_MyBar>::ref_type get_rec_listen_port_bar_prov () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute test_topic
    ::Hello::TestTopic test_topic () override;
    void test_topic (const ::Hello::TestTopic& test_topic) override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::Hello::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of test_topic attribute
    ::Hello::TestTopic test_topic_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits<::Hello::CCM_MyFoo>::ref_type rec_listen_port_foo_prov_;
    IDL::traits<::Hello::CCM_MyBar>::ref_type rec_listen_port_bar_prov_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl::Receiver_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Receiver_exec_i(const Receiver_exec_i&) = delete;
    Receiver_exec_i(Receiver_exec_i&&) = delete;
    Receiver_exec_i& operator=(const Receiver_exec_i&) = delete;
    Receiver_exec_i& operator=(Receiver_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[user_namespace_end_decl]

} // namespace Hello_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Receiver_Impl[factory]
extern "C" HELLO_RECEIVER_EXEC_Export  void
create_Hello_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_receiver_impl.h[Footer]

#endif /* __RIDL_HELLO_RECEIVER_EXEC_H_IIJAAGGI_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
