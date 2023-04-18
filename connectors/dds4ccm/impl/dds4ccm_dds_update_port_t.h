// -*- C++ -*-
/**
 * @file    dds4ccm_dds_update_port_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM State connector Update port
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_UPDATE_PORT_T_H_
#define DDS4CCM_UPDATE_PORT_T_H_

#include "dds4ccm/impl/dds4ccm_updater_t.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_Update_Port_T
{
public:
  explicit DDS_Update_Port_T (IDL::traits<CORBA::Object>::ref_type component);
  virtual ~DDS_Update_Port_T () = default;

  /**
   * @name DDS_Update
   * DDS_Update operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::data_type>::ref_type get_data ();
  typename IDL::traits<typename CCM_TYPE::dds_entity_type>::ref_type get_dds_entity ();
  //@}

  void
  configuration_complete (
    IDL::traits<::DDS::Topic>::ref_type topic,
    IDL::traits<::DDS::Publisher>::ref_type publisher,
    const std::string &qos_profile);

  void remove (IDL::traits<::DDS::Publisher>::ref_type publisher);

private:
  using DDS4CCM_Updater_type = ::CIAOX11::DDS4CCM::Updater_T<
    typename CCM_TYPE::data_type,
    TOPIC_TYPE,
    TOPIC_SEQ_TYPE>;
  using CCM_DataWriter_type = ::CIAOX11::DDS4CCM::CCM_DataWriter;

  IDL::traits<CORBA::Object>::weak_ref_type component_;

  /**
   * DDS_Update
   */
  //@{
  typename IDL::traits<DDS4CCM_Updater_type>::ref_type dds4ccm_updater_ {};
  typename IDL::traits<CCM_DataWriter_type>::ref_type ccm_data_writer_ {};
  IDL::traits<::DDS::DataWriter>::ref_type data_writer_ {};
  //@}

  DDS_Update_Port_T() = delete;
  DDS_Update_Port_T(const DDS_Update_Port_T&) = delete;
  DDS_Update_Port_T(DDS_Update_Port_T&&) = delete;
  DDS_Update_Port_T& operator=(const DDS_Update_Port_T&) = delete;
  DDS_Update_Port_T& operator=(DDS_Update_Port_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_dds_update_port_t.cpp"

#endif /* DDS4CCM_UPDATE_PORT_T_H_ */
