// -*- C++ -*-
/**
 * @file    dds4ccm_state_connector_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM State connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_STATE_CONNECTOR_T_H_
#define DDS4CCM_STATE_CONNECTOR_T_H_

#include "dds4ccm/impl/dds4ccm_latebinded_connector_t.h"
#include "dds4ccm/impl/dds4ccm_dds_update_port_t.h"
#include "dds4ccm/impl/dds4ccm_dds_read_port_t.h"
#include "dds4ccm/impl/dds4ccm_dds_get_port_t.h"
#include "dds4ccm/impl/dds4ccm_dds_listen_port_t.h"
#include "dds4ccm/impl/dds4ccm_dds_state_listen_port_t.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_State_Connector_T
  : public virtual DDS_LateBinded_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
{
public:
  DDS_State_Connector_T () = default;
  ~DDS_State_Connector_T () override;

  /**
   * @name DDS_Update
   * DDS_Update operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::observable_traits::data_type>::ref_type
  get_observable_data () override;

  IDL::traits< ::DDS::CCM_DataWriter>::ref_type
  get_observable_dds_entity () override;
  //@}

  /**
   * @name DDS_Read
   * DDS_Read operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::passive_observer_traits::data_type>::ref_type
  get_passive_observer_data () override;

  IDL::traits< ::DDS::CCM_DataReader>::ref_type
  get_passive_observer_dds_entity () override;

  IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
  get_passive_observer_filter_config () override;

  ::CCM_DDS::QueryFilter passive_observer_filter () override;

  void passive_observer_filter (
    const ::CCM_DDS::QueryFilter &filter) override;
  //@}

  /**
   * @name DDS_Get
   * DDS_Get operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::pull_observer_traits::data_type>::ref_type
  get_pull_observer_data () override;

  typename IDL::traits<typename CCM_TYPE::pull_observer_traits::fresh_data_type>::ref_type
  get_pull_observer_fresh_data () override;

  IDL::traits< ::DDS::CCM_DataReader>::ref_type
  get_pull_observer_dds_entity () override;

  IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
  get_pull_observer_filter_config () override;

  CCM_DDS::QueryFilter
  pull_observer_filter () override;

  void
  pull_observer_filter (
    const CCM_DDS::QueryFilter &filter) override;
  //@}

  /**
   * @name DDS_Listen
   * DDS_Listen operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::push_observer_traits::data_type>::ref_type
  get_push_observer_data () override;

  IDL::traits< CCM_DDS::CCM_DataListenerControl>::ref_type
  get_push_observer_data_control () override;

  IDL::traits< ::DDS::CCM_DataReader>::ref_type
  get_push_observer_dds_entity () override;

  IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
  get_push_observer_filter_config () override;

  ::CCM_DDS::QueryFilter
  push_observer_filter () override;

  void
  push_observer_filter (
    const ::CCM_DDS::QueryFilter & filter) override;
  //@}

  /**
   * @name DDS_StateListen
   * DDS_StateListen operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::push_state_observer_traits::data_type>::ref_type
  get_push_state_observer_data () override;

  IDL::traits< CCM_DDS::CCM_StateListenerControl>::ref_type
  get_push_state_observer_data_control () override;

  IDL::traits< ::DDS::CCM_DataReader>::ref_type
  get_push_state_observer_dds_entity () override;

  IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
  get_push_state_observer_filter_config () override;

  ::CCM_DDS::QueryFilter
  push_state_observer_filter () override;

  void
  push_state_observer_filter (const ::CCM_DDS::QueryFilter & filter) override;
  //@}

  void ccm_passivate () override;

private:
  /**
   * DDS_Update observable
   */
  //@{
  typedef DDS_Update_Port_T <
      typename CCM_TYPE::observable_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE>
    Observable_type;
  std::unique_ptr<Observable_type> observable_ {};
  Observable_type *observable ();
  //@}

  /**
   * DDS_Read passive_observer
   */
  //@{
  typedef DDS_Read_Port_T <
      typename CCM_TYPE::passive_observer_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE>
    PassiveObserver_type;
    std::unique_ptr<PassiveObserver_type> passive_observer_ {};
    PassiveObserver_type *passive_observer ();
  //@}

  /**
   * DDS_Get pull_observer
   */
  //@{
  typedef DDS_Get_Port_T <
      typename CCM_TYPE::pull_observer_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE>
    PullObserver_type;
  std::unique_ptr<PullObserver_type> pull_observer_ {};
  PullObserver_type *pull_observer ();
  //@}

  /**
   * DDS_Listen push_consumer
   */
  //@{
  typedef DDS_Listen_Port_T <
      typename CCM_TYPE::push_observer_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE,
      CIAOX11::DDS4CCM::DDS4CCM_TAKE>
    PushObserver_type;
  std::unique_ptr<PushObserver_type> push_observer_ {};
  PushObserver_type *push_observer ();
  //@}


  /**
   * DDS_StateListen push_state_observer
   */
  //@{
  typedef DDS_State_Listen_Port_T <
      typename CCM_TYPE::push_state_observer_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE,
      CIAOX11::DDS4CCM::DDS4CCM_READ>
    PushStateObserver_type;
  std::unique_ptr<PushStateObserver_type> push_state_observer_ {};
  PushStateObserver_type *push_state_observer ();
  //@}

  /**
   * @name Life cycle methods
   * Actual implementation of the life cycle methods.
   * Separated from the spec defined lifecycle methods since
   * a DDS4CCM connector should be able to change topics.
   */
  //@{
  void do_configuration_complete () override;
  void do_ccm_activate () override;
  void do_ccm_remove () override;
  //@}

  typedef DDS_LateBinded_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    LateBindedConnector;
  typedef DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    TopicBaseConnector;

  DDS_State_Connector_T(const DDS_State_Connector_T&) = delete;
  DDS_State_Connector_T(DDS_State_Connector_T&&) = delete;
  DDS_State_Connector_T& operator=(const DDS_State_Connector_T&) = delete;
  DDS_State_Connector_T& operator=(DDS_State_Connector_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_state_connector_t.cpp"


#endif /* DDS4CCM_STATE_CONNECTOR_T_H_ */
