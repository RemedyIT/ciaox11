// -*- C++ -*-
/**
 * @file    dds4ccm_dds_state_listen_port_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_STATE_LISTEN_PORT_T_H_
#define DDS4CCM_STATE_LISTEN_PORT_T_H_

#include "dds4ccm/impl/dds4ccm_subscriber_base_t.h"
#include "dds4ccm/impl/dds4ccm_state_listener_t.h"
#include "dds4ccm/impl/dds4ccm_state_listener_control_t.h"
#include "dds4ccm/impl/dds4ccm_utils.h"

/**
  * Template implementing the DDS4CCM Listen basic port
  * @tparam CCM_TYPE Set of type traits for this basic port
  * @tparam TOPIC_TYPE The DDS vendor data type
  * @tparam TOPIC_SEQ_TYPE The type of sequence
  * @tparam LRT An enum indicating the read or take semantics of this port
  */
template <typename CCM_TYPE,
          typename TOPIC_TYPE,
          typename TOPIC_SEQ_TYPE,
          CIAOX11::DDS4CCM::DDS4CCM_LISTENER_READ_TAKE LRT>
class DDS_State_Listen_Port_T final
  : public virtual DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
{
public:
  explicit DDS_State_Listen_Port_T (IDL::traits< CORBA::Object >::ref_type component);
  virtual ~DDS_State_Listen_Port_T () = default;

  /**
   * @name DDS_StateListen
   * DDS_StateListen operations
   */
  //@{
  IDL::traits< CCM_DDS::CCM_StateListenerControl >::ref_type
  get_data_control ();
  //@}

  void
  activate (
    const typename CCM_TYPE::event_strategy_type &evs,
    typename IDL::traits< typename CCM_TYPE::data_listener_type >::ref_type listener,
    IDL::traits< CCM_DDS::PortStatusListener >::ref_type status);

private:
  typedef ::CIAOX11::DDS4CCM::ListenerBase_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    ListenerBase_type;
  typedef ::CIAOX11::DDS4CCM::DataReaderStateListener_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, LRT>
    DataReaderStateListener_type;
  typedef CCM_DDS_StateListenerControl_T< ::CCM_DDS::CCM_StateListenerControl >
    StateListenerControl_type;
  typedef DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    SubscriberBase_type;

  /**
   * DDS_Listen
   */
  //@{
  typename IDL::traits< StateListenerControl_type >::ref_type data_control_;
  //@}

  DDS_State_Listen_Port_T() = delete;
  DDS_State_Listen_Port_T(const DDS_State_Listen_Port_T&) = delete;
  DDS_State_Listen_Port_T(DDS_State_Listen_Port_T&&) = delete;
  DDS_State_Listen_Port_T& operator=(const DDS_State_Listen_Port_T&) = delete;
  DDS_State_Listen_Port_T& operator=(DDS_State_Listen_Port_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_dds_state_listen_port_t.cpp"

#endif /* DDS4CCM_STATE_LISTEN_PORT_T_H_ */
