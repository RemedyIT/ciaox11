// -*- C++ -*-
/**
 * @file    dds4ccm_dds_read_port_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM Read port
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_READ_PORT_T_H_
#define DDS4CCM_READ_PORT_T_H_

#include "dds4ccm/impl/dds4ccm_subscriber_base_t.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_Read_Port_T
  : public DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
{
public:
  explicit DDS_Read_Port_T (IDL::traits<CORBA::Object>::ref_type component);
  ~DDS_Read_Port_T () override = default;

private:
  DDS_Read_Port_T() = delete;
  DDS_Read_Port_T(const DDS_Read_Port_T&) = delete;
  DDS_Read_Port_T(DDS_Read_Port_T&&) = delete;
  DDS_Read_Port_T& operator=(const DDS_Read_Port_T&) = delete;
  DDS_Read_Port_T& operator=(DDS_Read_Port_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_dds_read_port_t.cpp"

#endif /* DDS4CCM_READ_PORT_T_H_ */
