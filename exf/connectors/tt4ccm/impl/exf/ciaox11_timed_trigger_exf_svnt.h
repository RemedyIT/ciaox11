// -*- C++ -*-
/**
 * @file    ciaox11_timed_trigger_exf_svnt.h
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 Timed Trigger connector servant using execution framework and timer queue
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_CIAOX11_TIMED_TRIGGER_SVNT_H_GAGHGBBI_INCLUDED__
#define __RIDL_CIAOX11_TIMED_TRIGGER_SVNT_H_GAGHGBBI_INCLUDED__

#include /**/ "ace/pre.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "tt4ccm_exf_conn_export.h"

#include "ciaox11_timed_triggerEC.h"


#include "ccm/ccm_serviceregistryC.h"
#include "ccm/ccm_executorlocatorC.h"

#include "ciaox11/versionx11.h"

// generated from ccmx11/svnt/hdr/component.erb
namespace CIAOX11_TT_TimedTrigger_Impl
{

  /**
   * Context implementation class for the ::CIAOX11_TT::CCM_TimedTrigger
   * component.
   */
  class TimedTrigger_Context final
    : public IDL::traits<::CIAOX11_TT::CCM_TimedTrigger_Context >::base_type
  {
  public:
    /**
     * Constructor for the context.
     * @param svcreg The ServiceRegistry for this component
     * @param ins_name The name of the component instance as mentioned in the deployment plan.
     */
    TimedTrigger_Context (
      IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
      std::string ins_name);

    /// Destructor
    ~TimedTrigger_Context () override;

    /// Retrieve the service registry
    IDL::traits<CIAOX11::Service_Registry>::ref_type
    the_service_registry () override;

    /// readonly attribute which holds the instance name of the
    /// component. This instance name is supplied to the servant factory
    /// method by the deployment tools and represents the name of the
    /// component in the deployment plan.
    std::string
    instance_id () override;

  private:
    /// The ServiceRegistry for this component
    IDL::traits<CIAOX11::Service_Registry>::ref_type service_registry_ {};
    /// The instance name of the component
    std::string const instance_id_ {};

    //@{
    /** Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    TimedTrigger_Context () = delete;
    TimedTrigger_Context (const TimedTrigger_Context&) = delete;
    TimedTrigger_Context (TimedTrigger_Context&&) = delete;
    TimedTrigger_Context& operator= (const TimedTrigger_Context&) = delete;
    TimedTrigger_Context& operator= (TimedTrigger_Context&&) = delete;
    //@}
  };

  /**
   * ExecutorLocator for the TimedTrigger component. This
   * gives access to all middleware generated pieces that are used
   * by the CCM infrastructur
   */
  class TimedTrigger_ExecutorLocator final
    : public IDL::traits<CIAOX11::ExecutorLocator>::base_type
  {
  public:
    /**
    * Constructor
    * @param component_executor The user implemented executor
    * @param component_context The context that is passed to the executor
    */
    TimedTrigger_ExecutorLocator (
      IDL::traits<::CIAOX11_TT::CCM_TimedTrigger>::ref_type component_executor,
      IDL::traits<TimedTrigger_Context>::ref_type component_context);

    /**
     * Configure the component
     */
    void configure (::Components::ConfigValues& config) override;

    /**
     * Connect a component port.
     * @retval true Connecting the port has succeeded
     * @retval false Connecting the port has failed
     */
     bool connect (const ::Components::FeatureName& name,
                   IDL::traits<CORBA::Object>::ref_type connection,
                   const std::string& conn_name,
                   const ::Components::ConfigValues& config) override;

    /**
     * Disconnect a component port.
     * @retval true Disonnecting the port has succeeded
     * @retval false Disconnecting the port has failed
     */
     bool disconnect (const ::Components::FeatureName& name,
                      const std::string& conn_name) override;

    /**
     * Obtain the component executor.
     */
    IDL::traits<CORBA::Object>::ref_type obtain_executor () override;

    /**
     * Obtain a facet executor for the given @a name and the given @a connection using the
     * the given @a config. If there is no facet executor returned by the component
     * executor we just return nullptr. If we have to get an executor for an invalid
     * facet name we throw an InvalidName() exception
     */
    IDL::traits<CORBA::Object>::ref_type obtain_facet_executor (
                          const ::Components::FeatureName& name,
                          ::Components::ConfigValues& config) override;

  private:
    /// Reference to the user implemented executor
    IDL::traits<::CIAOX11_TT::CCM_TimedTrigger>::ref_type component_executor_;

    /// The context for this component
    IDL::traits<TimedTrigger_Context>::ref_type component_context_;

    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    TimedTrigger_ExecutorLocator () = delete;
    TimedTrigger_ExecutorLocator (const TimedTrigger_ExecutorLocator&) = delete;
    TimedTrigger_ExecutorLocator (TimedTrigger_ExecutorLocator&&) = delete;
    TimedTrigger_ExecutorLocator& operator= (const TimedTrigger_ExecutorLocator&) = delete;
    TimedTrigger_ExecutorLocator& operator= (TimedTrigger_ExecutorLocator&&) = delete;
    //@}
  };

  /**
   * Factory method to create an executor locator for a
   * CIAOX11_TT_TimedTrigger_Impl component
   * @param component_executor The user component executor for which we need
   * to create the executor locator
   * @param svcreg The ServiceRegistry for this component
   * @param ins_name The unique name of this component
   * @param executor_locator The created executor locator
   */
  extern "C" TT4CCM_EXF_CONN_Export  void
  create_CIAOX11_TT_TimedTrigger_Servant (
    IDL::traits<Components::EnterpriseComponent>::ref_type component_executor,
    IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
    const std::string& ins_name,
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type& executor_locator);
} // namespace CIAOX11_TT_TimedTrigger_Impl

#include /**/ "ace/post.h"
#endif /* __RIDL_CIAOX11_TIMED_TRIGGER_SVNT_H_GAGHGBBI_INCLUDED__ */

// -*- END -*-
