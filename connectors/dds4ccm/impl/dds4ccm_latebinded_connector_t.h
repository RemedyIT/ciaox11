// -*- C++ -*-
/**
 * @file    dds4ccm_latebinded_connector_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of late binded connectors.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_LATEBINDED_CONNECTOR_T_H_
#define DDS4CCM_LATEBINDED_CONNECTOR_T_H_

#include "dds4ccm/impl/dds4ccm_topicbase_connector_t.h"

/**
 * @name DDS_LateBinded_Connector_T
 *
 * @brief LateBinded DDS4CCM Connector Implementation
 *
 * Template variables:
 * @tparam CCM_TYPE DDS4CCM traits
 * @tparam TOPIC_TYPE => Vendor specific Topic Type.
 * @tparam TOPIC_SEQ_TYPE => Vendor specific sequence of Topic Types.
 *
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_LateBinded_Connector_T
  : public virtual DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
{
public:
  DDS_LateBinded_Connector_T ();
  virtual ~DDS_LateBinded_Connector_T ();

  /**
   * @name topic_name attribute
   * Setter for the topic_name attribute
   */
  void topic_name (const std::string &topic_name) override;

  /**
   * @name Life cycle methods
   * Life cycle methods of the DDS4CCM connector
   */
  //@{
  void configuration_complete () override;
  void ccm_activate () override;
  void ccm_remove () override;
  //@}

  virtual void do_configuration_complete () = 0;
  virtual void do_ccm_activate () = 0;
  virtual void do_ccm_remove () = 0;

private:
  typedef DDS_TopicBase_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    TopicBaseConnector;

  DDS_LateBinded_Connector_T(const DDS_LateBinded_Connector_T&) = delete;
  DDS_LateBinded_Connector_T(DDS_LateBinded_Connector_T&&) = delete;
  DDS_LateBinded_Connector_T& operator=(const DDS_LateBinded_Connector_T&) = delete;
  DDS_LateBinded_Connector_T& operator=(DDS_LateBinded_Connector_T&&) = delete;

};

#include "dds4ccm/impl/dds4ccm_latebinded_connector_t.cpp"

#endif /* DDS4CCM_LATEBINDED_CONNECTOR_T_H_ */
