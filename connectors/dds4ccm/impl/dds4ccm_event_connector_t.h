// -*- C++ -*-
/**
 * @file    dds4ccm_event_connector_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM Event connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_EVENT_CONNECTOR_T_H_
#define DDS4CCM_EVENT_CONNECTOR_T_H_

#include "dds4ccm/impl/dds4ccm_latebinded_connector_t.h"
#include "dds4ccm/impl/dds4ccm_dds_get_port_t.h"
#include "dds4ccm/impl/dds4ccm_dds_write_port_t.h"
#include "dds4ccm/impl/dds4ccm_dds_listen_port_t.h"

/**
 * @name DDS_Event_Connector_T
 *
 * @brief DDS4CCM Event Connector Implementation
 *
 * Template variables:
 * @tparam CCM_TYPE DDS4CCM traits
 * @tparam TOPIC_TYPE => Vendor specific Topic Type.
 * @tparam TOPIC_SEQ_TYPE => Vendor specific sequence of Topic Types.
 *
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_Event_Connector_T
  : public virtual DDS_LateBinded_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
{
public:
  DDS_Event_Connector_T () = default;
  virtual ~DDS_Event_Connector_T () = default;

  /**
   * @name DDS_Write
   * DDS_Write operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::supplier_traits::data_type>::ref_type
  get_supplier_data () override;

  typename IDL::traits<typename CCM_TYPE::supplier_traits::dds_entity_type>::ref_type
  get_supplier_dds_entity () override;
  //@}

  /**
   * @name DDS_Get
   * DDS_Get operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::pull_consumer_traits::data_type>::ref_type
  get_pull_consumer_data () override;

  typename IDL::traits<typename CCM_TYPE::pull_consumer_traits::fresh_data_type>::ref_type
  get_pull_consumer_fresh_data () override;

  IDL::traits< ::DDS::CCM_DataReader>::ref_type
  get_pull_consumer_dds_entity () override;

  IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
  get_pull_consumer_filter_config () override;

  CCM_DDS::QueryFilter
  pull_consumer_filter () override;

  void
  pull_consumer_filter (
    const CCM_DDS::QueryFilter &filter) override;
  //@}

  /**
   * @name DDS_Listen
   * DDS_Listen operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::push_consumer_traits::data_type>::ref_type
  get_push_consumer_data () override;

  IDL::traits< CCM_DDS::CCM_DataListenerControl>::ref_type
  get_push_consumer_data_control () override;

  IDL::traits< ::DDS::CCM_DataReader>::ref_type
  get_push_consumer_dds_entity () override;

  IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::ref_type
  get_push_consumer_filter_config () override;

  ::CCM_DDS::QueryFilter
  push_consumer_filter () override;

  void
  push_consumer_filter (
    const ::CCM_DDS::QueryFilter & filter) override;
  //@}

  /**
   * @name Life cycle methods
   * configuration_complete, ccm_active and ccm_removed are implemented
   * in the DDS_LateBinded_Connector_T class.
   */
  //@{
  void ccm_passivate () override;
  //@}

private:
  /**
   * DDS_Write supplier
   */
  //@{
  typedef DDS_Write_Port_T <
      typename CCM_TYPE::supplier_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE>
    Supplier_type;
  std::unique_ptr<Supplier_type> supplier_ {};
  Supplier_type *supplier ();
  //@}

  /**
   * DDS_Listen push_consumer
   */
  //@{
  typedef DDS_Listen_Port_T <
      typename CCM_TYPE::push_consumer_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE,
      CIAOX11::DDS4CCM::DDS4CCM_TAKE>
    PushConsumer_type;
  std::unique_ptr<PushConsumer_type> push_consumer_ {};
  PushConsumer_type *push_consumer ();
  //@}

  /**
   * DDS_Get pull_consumer
   */
  //@{
  typedef DDS_Get_Port_T <
      typename CCM_TYPE::pull_consumer_traits,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE>
    PullConsumer_type;
  std::unique_ptr<PullConsumer_type> pull_consumer_ {};
  PullConsumer_type *pull_consumer ();
  //@}

  /**
   * @name Life cycle methods
   * Actual implementation of the life cycle methods.
   * Separated from the actual lifecycle methods since
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

  DDS_Event_Connector_T(const DDS_Event_Connector_T&) = delete;
  DDS_Event_Connector_T(DDS_Event_Connector_T&&) = delete;
  DDS_Event_Connector_T& operator=(const DDS_Event_Connector_T&) = delete;
  DDS_Event_Connector_T& operator=(DDS_Event_Connector_T&&) = delete;

};

#include "dds4ccm/impl/dds4ccm_event_connector_t.cpp"

#endif /* DDS4CCM_EVENT_CONNECTOR_T_H_ */
