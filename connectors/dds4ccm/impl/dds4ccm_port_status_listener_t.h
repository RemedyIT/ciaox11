// -*- C++ -*-
/**
 * @file    dds4ccm_port_status_listener_t.h
 * @author  Marcel Smit, Martin Corino
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_PORT_STATUS_LISTENER_T_H_
#define DDS4CCM_PORT_STATUS_LISTENER_T_H_

#include "dds4ccm/idl/dds4ccm_port_status_listenerC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename EVT_STRATEGY>
    class PortStatusListener_T
      : public IDL::traits< ::DDS::DataReaderListener>::base_type
    {
    public:
      /// Constructor
      explicit PortStatusListener_T (
        const EVT_STRATEGY& evs);

      /// Destructor
      virtual ~PortStatusListener_T () = default;

      virtual void
      on_requested_deadline_missed (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedDeadlineMissedStatus & status) override;

      virtual void on_sample_lost (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleLostStatus & status)  override;

      virtual void
      on_requested_incompatible_qos (
        IDL::traits< ::DDS::DataReader>::ref_type ,
        const ::DDS::RequestedIncompatibleQosStatus & ) override;

      virtual void
      on_sample_rejected (
        IDL::traits< ::DDS::DataReader>::ref_type ,
        const ::DDS::SampleRejectedStatus & ) override;

      virtual void
      on_liveliness_changed (
        IDL::traits< ::DDS::DataReader>::ref_type ,
        const ::DDS::LivelinessChangedStatus & ) override;

      virtual void
      on_data_available (
        IDL::traits< ::DDS::DataReader>::ref_type ) override;

      virtual void
      on_subscription_matched (
        IDL::traits< ::DDS::DataReader>::ref_type ,
        const ::DDS::SubscriptionMatchedStatus & ) override;

      static ::DDS::StatusMask get_mask (
        IDL::traits< CCM_DDS::PortStatusListener>::ref_type psl);

    private:
      PortStatusListener_T() = delete;
      PortStatusListener_T(const PortStatusListener_T&) = delete;
      PortStatusListener_T(PortStatusListener_T&&) = delete;
      PortStatusListener_T& operator=(const PortStatusListener_T&) = delete;
      PortStatusListener_T& operator=(PortStatusListener_T&&) = delete;

    protected:
      EVT_STRATEGY evs_;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_port_status_listener_t.cpp"

#endif /* DDS4CCM_PORT_STATUS_LISTENER_T_H_ */
