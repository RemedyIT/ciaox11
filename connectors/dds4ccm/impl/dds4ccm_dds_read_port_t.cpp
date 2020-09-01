// -*- C++ -*-
/**
 * @file    dds4ccm_dds_read_port_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM Read port
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
DDS_Read_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::DDS_Read_Port_T (
  IDL::traits<CORBA::Object>::ref_type component)
  : DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (std::move(component))
{
  DDS4CCM_LOG_TRACE ("DDS_Read_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::DDS_Read_Port_T");
}

