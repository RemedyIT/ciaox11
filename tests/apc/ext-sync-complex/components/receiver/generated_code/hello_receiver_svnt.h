/**
 * ****  Code generated by the RIDL Compiler ****
 * RIDL has been developed by:
 *        Remedy IT Expertise BV
 *        The Netherlands
 *        https://www.remedy.nl
 */

#ifndef __RIDL_HELLO_RECEIVER_SVNT_H_HCBADFGJ_INCLUDED__
#define __RIDL_HELLO_RECEIVER_SVNT_H_HCBADFGJ_INCLUDED__

#pragma once

#include /**/ "hello_receiver_svnt_export.h"

#include "hello_receiverEC.h"

#include "ccm/ccm_serviceregistryC.h"
#include "ccm/ccm_executorlocatorC.h"

#include /**/ "ciaox11/versionx11.h"

#if CIAOX11_MAJOR_VERSION != 2 || CIAOX11_MINOR_VERSION != 3 || CIAOX11_MICRO_VERSION != 0
#error This file was generated with another RIDL CCMX11 backend version (2.3.0). Please re-generate.
#endif

// generated from ccmx11/templates/svnt/hdr/component
namespace Hello_Receiver_Impl
{

  /**
   * Context implementation class for the ::Hello::CCM_Receiver
   * component.
   */
  class Receiver_Context final
    : public IDL::traits< ::Hello::CCM_Receiver_Context>::base_type
  {
  public:
    /**
     * Constructor for the context.
     * @param svcreg The ServiceRegistry for this component
     * @param ins_name The name of the component instance as mentioned in the deployment plan.
     */
    Receiver_Context (IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg, std::string ins_name);

    /// Destructor
    ~Receiver_Context () override = default;

    /// Retrieve the service registry
    IDL::traits<CIAOX11::Service_Registry>::ref_type the_service_registry () override;

    /// readonly attribute which holds the instance name of the
    /// component. This instance name is supplied to the servant factory
    /// method by the deployment tools and represents the name of the
    /// component in the deployment plan.
    std::string instance_id () override;

  private:
    /// The ServiceRegistry for this component
    IDL::traits<CIAOX11::Service_Registry>::ref_type service_registry_ {};
    /// The instance name of the component
    std::string const instance_id_ {};

    //@{
    /** Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    Receiver_Context () = delete;
    Receiver_Context (const Receiver_Context&) = delete;
    Receiver_Context (Receiver_Context&&) = delete;
    Receiver_Context& operator= (const Receiver_Context&) = delete;
    Receiver_Context& operator= (Receiver_Context&&) = delete;
    //@}
  };

  /**
   * ExecutorLocator for the Receiver component. This
   * gives access to all middleware generated pieces that are used
   * by the CCM infrastructure
   */
  class Receiver_ExecutorLocator final
    : public IDL::traits<CIAOX11::ExecutorLocator>::base_type
  {
  public:
    /**
    * Constructor
    * @param component_executor The user implemented executor
    * @param component_context The context that is passed to the executor
    */
    Receiver_ExecutorLocator (
      IDL::traits<::Hello::CCM_Receiver>::ref_type component_executor,
      IDL::traits<Receiver_Context>::ref_type component_context);

    /// Destructor
    ~Receiver_ExecutorLocator () override = default;

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
     * @retval true Disconnecting the port has succeeded
     * @retval false Disconnecting the port has failed
     */
    bool disconnect (const ::Components::FeatureName& name,
                     const std::string& conn_name) override;

    /**
     * Obtain the component executor.
     */
    IDL::traits<CORBA::Object>::ref_type obtain_executor () override;

    /**
     * Obtain a facet executor for the given @a name using the the given @a config.
     * If there is no facet executor returned by the component executor we just
     * return nullptr. If we have to get an executor for an invalid facet
     * name we throw an InvalidName() exception
     */
    IDL::traits<CORBA::Object>::ref_type obtain_facet_executor (
                          const ::Components::FeatureName& name,
                          ::Components::ConfigValues& config) override;

  private:
    /// Reference to the user implemented executor
    IDL::traits<::Hello::CCM_Receiver>::ref_type component_executor_;

    /// The context for this component
    IDL::traits<Receiver_Context>::ref_type component_context_;

    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Receiver_ExecutorLocator () = delete;
    Receiver_ExecutorLocator (const Receiver_ExecutorLocator&) = delete;
    Receiver_ExecutorLocator (Receiver_ExecutorLocator&&) = delete;
    Receiver_ExecutorLocator& operator= (const Receiver_ExecutorLocator&) = delete;
    Receiver_ExecutorLocator& operator= (Receiver_ExecutorLocator&&) = delete;
    //@}
  };
} // namespace Hello_Receiver_Impl

/**
 * Factory method to create an executor locator for a
 * Hello_Receiver_Impl component
 * @param component_executor The user component executor for which we need
 * to create the executor locator
 * @param svcreg The ServiceRegistry for this component
 * @param ins_name The unique name of this component
 * @param executor_locator The created executor locator
 */
extern "C" HELLO_RECEIVER_SVNT_Export  void
create_Hello_Receiver_Servant (
  IDL::traits<Components::EnterpriseComponent>::ref_type component_executor,
  IDL::traits<CIAOX11::Service_Registry>::ref_type svcreg,
  const std::string& ins_name,
  IDL::traits<CIAOX11::ExecutorLocator>::ref_type& executor_locator);

#endif /* __RIDL_HELLO_RECEIVER_SVNT_H_HCBADFGJ_INCLUDED__ */

// -*- END -*-
