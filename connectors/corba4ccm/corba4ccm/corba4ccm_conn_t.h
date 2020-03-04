// -*- C++ -*-
/**
 * @file    corba4ccm_conn_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation file of the CORBA4CCM connector implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CORBA4CCM_CONN_T_H_
#define CORBA4CCM_CONN_T_H_

#include "ccm/session/ccm_sessioncontextC.h"

namespace CCM_CORBA
{
  template <typename BASE, typename CONTEXT, typename INTERFACE_TYPE, typename FACET, typename SVNT, typename SVNT_IMPL>
  class CORBA_Connector_T
    : public virtual IDL::traits<BASE>::base_type
  {
  public:
    CORBA_Connector_T () = default;
    virtual ~CORBA_Connector_T () = default;

    /** @name Component port operations. */
    //@{
    /// Factory method and getter for the srr_facet facet
    /// @return existing instance of facet if one exists, else creates one
    typename IDL::traits<INTERFACE_TYPE>::ref_type
    get_srr_facet () override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    /// Registers this CORBA connector with the POA, creates the CORBA servant
    /// for the srr_facet_ and registers this servant with the POA.
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    /// Deactivates the srr_facet and this CORBA connector in the POA
    void ccm_remove () override;
    //@}

  protected:
    /// Context for component instance.
    typename IDL::traits<CONTEXT>::ref_type context_ {};

    /** @name Component facets. */
    //@{
    typename IDL::traits<INTERFACE_TYPE>::ref_type srr_facet_ {};
    //@}

  private:
    CORBA_Connector_T(const CORBA_Connector_T&) = delete;
    CORBA_Connector_T(CORBA_Connector_T&&) = delete;
    CORBA_Connector_T& operator=(const CORBA_Connector_T&) = delete;
    CORBA_Connector_T& operator=(CORBA_Connector_T&&) = delete;
  };
}

#include "connectors/corba4ccm/corba4ccm/corba4ccm_conn_t.cpp"

#endif /* CORBA4CCM_CONN_T_H_ */
