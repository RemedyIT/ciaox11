// -*- C++ -*-
/**
 * @file    dds4ccm_dds_listen_port_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_LISTEN_PORT_T_H_
#define DDS4CCM_LISTEN_PORT_T_H_

#include "dds4ccm/impl/dds4ccm_subscriber_base_t.h"
#include "dds4ccm/impl/dds4ccm_data_listener_t.h"
#include "dds4ccm/impl/dds4ccm_data_listener_control_t.h"
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
class DDS_Listen_Port_T
  : public virtual DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
{
public:
  explicit DDS_Listen_Port_T (IDL::traits<CORBA::Object>::ref_type component);
  ~DDS_Listen_Port_T () override = default;

  /**
   * @name DDS_Listen
   * DDS_Listen operations
   */
  //@{
  IDL::traits<CCM_DDS::CCM_DataListenerControl>::ref_type get_data_control ();
  //@}

  void
  activate (
    const typename CCM_TYPE::event_strategy_type &evs,
    typename IDL::traits<typename CCM_TYPE::data_listener_type>::ref_type listener,
    IDL::traits<CCM_DDS::PortStatusListener>::ref_type status);

private:
  using DataReaderListener_type = ::CIAOX11::DDS4CCM::DataReaderListener_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, LRT>;
  using DataListenerControl_type = CCM_DDS_DataListenerControl_T< ::CCM_DDS::CCM_DataListenerControl>;
  using SubscriberBase_type = DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>;

  /**
   * DDS_Listen
   */
  //@{
  typename IDL::traits<DataListenerControl_type>::ref_type data_control_;
  //@}

  DDS_Listen_Port_T() = delete;
  DDS_Listen_Port_T(const DDS_Listen_Port_T&) = delete;
  DDS_Listen_Port_T(DDS_Listen_Port_T&&) = delete;
  DDS_Listen_Port_T& operator=(const DDS_Listen_Port_T&) = delete;
  DDS_Listen_Port_T& operator=(DDS_Listen_Port_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_dds_listen_port_t.cpp"

#endif /* DDS4CCM_LISTEN_PORT_T_H_ */
