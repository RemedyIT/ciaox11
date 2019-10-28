/**
 * @file    corba4ccm_conn_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation file of the CORBA4CCM connector implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "connectors/corba4ccm/corba4ccm/corba4ccm_conn_t.h"
#include "connectors/corba4ccm/corba4ccm/corba4ccm.h"

std::string const sync_request_reply_facet ("srr_facet");

namespace CCM_CORBA
{
  template <typename BASE, typename CONTEXT, typename INTERFACE_TYPE, typename FACET, typename SVNT, typename SVNT_IMPL>
  void
  CORBA_Connector_T<BASE, CONTEXT, INTERFACE_TYPE, FACET, SVNT, SVNT_IMPL>::configuration_complete ()
  {
  }

  template <typename BASE, typename CONTEXT, typename INTERFACE_TYPE, typename FACET, typename SVNT, typename SVNT_IMPL>
  void
  CORBA_Connector_T<BASE, CONTEXT, INTERFACE_TYPE, FACET, SVNT, SVNT_IMPL>::ccm_activate ()
  {
  }

  template <typename BASE, typename CONTEXT, typename INTERFACE_TYPE, typename FACET, typename SVNT, typename SVNT_IMPL>
  void
  CORBA_Connector_T<BASE, CONTEXT, INTERFACE_TYPE, FACET, SVNT, SVNT_IMPL>::ccm_passivate ()
  {
  }

  template <typename BASE, typename CONTEXT, typename INTERFACE_TYPE, typename FACET, typename SVNT, typename SVNT_IMPL>
  void
  CORBA_Connector_T<BASE, CONTEXT, INTERFACE_TYPE, FACET, SVNT, SVNT_IMPL>::ccm_remove ()
  {
    IDL::traits<PortableServer::POA>::ref_type poa = CCM_CORBA::get_corba4ccm_POA (this->context_);

    // Deactivate the corba4ccm support for facet srr_facet
    CCM_CORBA::deactivate_corba4ccm_facet (poa, this->context_->instance_id (), sync_request_reply_facet);

    // Deactivate the corba4ccm support for the component
    CCM_CORBA::deactivate_corba4ccm_component (poa, this->context_->instance_id ());
  }

  template <typename BASE, typename CONTEXT, typename INTERFACE_TYPE, typename FACET, typename SVNT, typename SVNT_IMPL>
  typename IDL::traits< INTERFACE_TYPE >::ref_type
  CORBA_Connector_T<BASE, CONTEXT, INTERFACE_TYPE, FACET, SVNT, SVNT_IMPL>::get_srr_facet ()
  {
    if (!this->srr_facet_)
    {
      this->srr_facet_ = CORBA::make_reference < FACET > (this->context_);
    }
    return this->srr_facet_;
  }

  template <typename BASE, typename CONTEXT, typename INTERFACE_TYPE, typename FACET, typename SVNT, typename SVNT_IMPL>
  void
  CORBA_Connector_T<BASE, CONTEXT, INTERFACE_TYPE, FACET, SVNT, SVNT_IMPL>::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    this->context_ = IDL::traits< CONTEXT >::narrow (std::move(ctx));

    IDL::traits<PortableServer::POA>::ref_type poa = CCM_CORBA::get_corba4ccm_POA (this->context_);

    // Create the CORBA servant for the SRR facet
    typename CORBA::servant_traits< SVNT >::ref_type facet_servant_reference =
      CORBA::make_reference < SVNT_IMPL > (this->get_srr_facet ());

    CCM_CORBA::activate_corba4ccm_facet (poa, std::move(facet_servant_reference), this->context_->instance_id (), sync_request_reply_facet);

    CCM_CORBA::activate_corba4ccm_component (poa, this->context_->instance_id ());
  }
};
