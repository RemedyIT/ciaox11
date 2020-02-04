// -*- C++ -*-
/**
 * @file    dds4ccm_dds_write_port_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector Write port
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_WRITE_PORT_T_H_
#define DDS4CCM_WRITE_PORT_T_H_

#include "dds4ccm/impl/dds4ccm_topicbase_connector_t.h"
#include "dds4ccm/impl/dds4ccm_writer_t.h"
#include "dds4ccm/impl/dds4ccm_ccm_data_writer.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_Write_Port_T
{
public:
  explicit DDS_Write_Port_T (IDL::traits<CORBA::Object >::ref_type component);
  ~DDS_Write_Port_T () = default;

  /**
   * @name DDS_Write
   * DDS_Write operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::data_type >::ref_type get_data ();
  typename IDL::traits<typename CCM_TYPE::dds_entity_type >::ref_type get_dds_entity ();
  //@}

  void
  configuration_complete (
    IDL::traits< ::DDS::Topic >::ref_type topic,
    IDL::traits< ::DDS::Publisher >::ref_type publisher,
    const std::string &qos_profile);

  void remove (IDL::traits< ::DDS::Publisher >::ref_type publisher);

private:
  typedef ::CIAOX11::DDS4CCM::Writer_T<
    typename CCM_TYPE::data_type,
    TOPIC_TYPE,
    TOPIC_SEQ_TYPE>
      DDS4CCM_Writer_type;

  typedef ::CIAOX11::DDS4CCM::CCM_DataWriter CCM_DataWriter_type;

  IDL::traits<CORBA::Object>::weak_ref_type component_;

  /**
   * DDS_Write
   */
  //@{
  typename IDL::traits< DDS4CCM_Writer_type >::ref_type dds4ccm_writer_ {};
  typename IDL::traits< CCM_DataWriter_type >::ref_type ccm_data_writer_ {};
  IDL::traits< ::DDS::DataWriter >::ref_type data_writer_ {};
  //@}

  DDS_Write_Port_T() = delete;
  DDS_Write_Port_T(const DDS_Write_Port_T&) = delete;
  DDS_Write_Port_T(DDS_Write_Port_T&&) = delete;
  DDS_Write_Port_T& operator=(const DDS_Write_Port_T&) = delete;
  DDS_Write_Port_T& operator=(DDS_Write_Port_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_dds_write_port_t.cpp"

#endif /* DDS4CCM_WRITE_PORT_T_H_ */
