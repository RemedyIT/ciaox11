// -*- C++ -*-
/**
 * @file    getter_test_receiver_exec.h
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the Getter test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_GETTER_TEST_RECEIVER_EXEC_H_BICFFBFG_INCLUDED__
#define __RIDL_GETTER_TEST_RECEIVER_EXEC_H_BICFFBFG_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : getter_test_receiver_impl.h[Header]

#pragma once

#include "getter_test_receiverEC.h"

#include /**/ "receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : getter_test_receiver_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : getter_test_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : getter_test_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : getter_test_receiver_impl.h[user_global_decl]

/// Namespace for implementation of Getter_Test::Receiver component
namespace Getter_Test_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[user_namespace_decl]
  /**
   * GetOneHandler
   */
  class GetOneHandler final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    GetOneHandler (IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor,
                   const std::string &key,
                   int32_t iteration);
    virtual ~GetOneHandler () = default;

    virtual void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type,
        const ::CCM_TT::TT_Duration&,
        uint32_t) override;

  private:
    IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor_;
    std::string key_;
    int32_t iteration_;
  };

  /**
   * GetManyHandler
   */
  class GetManyHandler final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    GetManyHandler (IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor,
                   int16_t keys,
                   int32_t iterations);
    virtual ~GetManyHandler () = default;

    virtual void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type,
        const ::CCM_TT::TT_Duration&,
        uint32_t) override;

  private:
    IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor_;
    int16_t keys_;
    int32_t iterations_;
  };
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for info_get_status facet
  class info_get_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    info_get_status_exec_i (
      IDL::traits<Getter_Test::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[ctor]

    /// Destructor
    virtual ~info_get_status_exec_i ();

    /** @name Operations from ::CCM_DDS::CCM_PortStatusListener */
    //@{

    virtual
    void
    on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus& status) override;

    virtual
    void
    on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus& status) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]

    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Getter_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_members]


    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for getter_invoke facet
  class getter_invoke_exec_i final
    : public IDL::traits< CCM_GetInvoker>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    getter_invoke_exec_i (
      IDL::traits<Getter_Test::CCM_Receiver_Context>::ref_type context,
      IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[ctor]

    /// Destructor
    virtual ~getter_invoke_exec_i ();

    /** @name Operations from CCM_GetInvoker */
    //@{

    virtual
    void
    start_timeout_get_one () override;

    virtual
    void
    start_timeout_get_many () override;

    virtual
    void
    start_get_one (
        const std::string& key,
        int32_t iteration) override;

    virtual
    void
    start_get_many (
        int16_t keys,
        int32_t iterations) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Getter_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_members]
     IDL::traits<Getter_Test::CCM_Receiver>::weak_ref_type component_executor_;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::getter_invoke_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::Getter_Test::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    virtual ~Receiver_exec_i ();

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the info_get_status facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type get_info_get_status () override;
    /// Factory method and getter for the getter_invoke facet
    /// @return existing instance of facet if one exists, else creates one
    virtual IDL::traits< CCM_GetInvoker>::ref_type get_getter_invoke () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    virtual void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    virtual void configuration_complete () override;

    /// Component state change method to activated state
    virtual void ccm_activate () override;

    /// Component state change method to passivated state
    virtual void ccm_passivate () override;

    /// Component state change method to removed state
    virtual void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    void
    start_get_one (const std::string &key,
      int32_t iteration);

    void
    timeout_get_one ();

    void
    timeout_get_many ();

    void
    get_one (const std::string &key,
      int32_t iteration);

    void
    start_get_many (
      int16_t keys,
      int32_t iterations);

    void
    get_many (
      int16_t keys,
      int32_t iterations);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Getter_Test::CCM_Receiver_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type info_get_status_;
    IDL::traits< CCM_GetInvoker>::ref_type getter_invoke_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[user_members]
    DDS::InstanceHandle_t instance_handle_ { ::DDS::HANDLE_NIL };
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
    void
    read_many (int16_t keys ,
      int32_t iterations,
      const CommonTestMessageSeq& gettertest_seq);
    //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[user_namespace_end_decl]

} // namespace Getter_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Getter_Test_Receiver_Impl[factory]
extern "C" RECEIVER_EXEC_Export  void
create_Getter_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Getter_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : getter_test_receiver_impl.h[Footer]

#endif /* __RIDL_GETTER_TEST_RECEIVER_EXEC_H_BICFFBFG_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
