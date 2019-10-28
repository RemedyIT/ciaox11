// -*- C++ -*-
/**
 * @file    dds4ccm_dds_get_port_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_GET_PORT_T_H_
#define DDS4CCM_GET_PORT_T_H_

#include "dds4ccm/impl/dds4ccm_subscriber_base_t.h"
#include "dds4ccm/impl/dds4ccm_getter_t.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_Get_Port_T final
  : public virtual DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
{
public:
  explicit DDS_Get_Port_T (IDL::traits<CORBA::Object >::ref_type component);
  virtual ~DDS_Get_Port_T () = default;

  /**
   * @name DDS_Get
   * DDS_Get operations
   */
  //@{
  typename IDL::traits< typename CCM_TYPE::fresh_data_type >::ref_type
  get_fresh_data ();
  //@}

  virtual void
  configuration_complete (
    IDL::traits< ::DDS::Topic >::ref_type topic,
    IDL::traits< ::DDS::Subscriber >::ref_type subscriber,
    const std::string &qos_profile) override;

private:
  typedef DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    SubscriberBase_type;

  typedef ::CIAOX11::DDS4CCM::Getter_T<
      typename CCM_TYPE::fresh_data_type,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE>
    DDS4CCM_Getter_type;

  /**
   * DDS_Get
   */
  //@{
  typename IDL::traits< DDS4CCM_Getter_type >::ref_type dds4ccm_getter_ {};
  //@}

  DDS_Get_Port_T() = delete;
  DDS_Get_Port_T(const DDS_Get_Port_T&) = delete;
  DDS_Get_Port_T(DDS_Get_Port_T&&) = delete;
  DDS_Get_Port_T& operator=(const DDS_Get_Port_T&) = delete;
  DDS_Get_Port_T& operator=(DDS_Get_Port_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_dds_get_port_t.cpp"

#endif /* DDS4CCM_GET_PORT_T_H_ */
