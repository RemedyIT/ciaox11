// -*- C++ -*-
/**
 * @file    dds4ccm_subscriber_base_t.h
 * @author  Marcel Smit
 *
 * @brief   Base class for the subscribing side of the DDS4CCM connector.
 *          Manages the type specific DataReader
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_SUBSCRIBER_BASE_T_H_
#define DDS4CCM_SUBSCRIBER_BASE_T_H_

#include "dds4ccm/idl/dds4ccm_baseC.h"
#include "dds4ccm/impl/dds4ccm_reader_t.h"
#include "dds4ccm/impl/dds4ccm_content_filter.h"
#include "dds4ccm/impl/dds4ccm_condition_manager.h"
#include "dds4ccm/impl/dds4ccm_ccm_data_reader.h"
#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm_port_status_listener_t.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
class DDS_Subscriber_Base_T
{
public:
  explicit DDS_Subscriber_Base_T (IDL::traits<CORBA::Object>::ref_type component);
  virtual ~DDS_Subscriber_Base_T () = default;

  /**
   * @name DDS_Read
   * DDS_Subscriber_Base_T operations
   */
  //@{
  typename IDL::traits<typename CCM_TYPE::data_type >::ref_type
  get_data ();

  typename IDL::traits<typename CCM_TYPE::dds_entity_type >::ref_type
  get_dds_entity ();

  typename IDL::traits<typename CCM_TYPE::filter_config_type >::ref_type
  get_filter_config ();

  CCM_DDS::QueryFilter filter ();

  /**
   * @name  filter
   * @brief setter for the QueryFilter
   * @throw NonChangeable is setter is invoked after configuration_complete
   */
  void filter (const CCM_DDS::QueryFilter &filter);
  //@}


  /**
   * @name  Life cycle methods
   * @brief Life cycle methods for the subscribing side of the dds4ccm connector
   */
  //@{
  virtual void
  configuration_complete (
    IDL::traits< ::DDS::Topic >::ref_type topic,
    IDL::traits< ::DDS::Subscriber >::ref_type subscriber,
    const std::string &qos_profile);

  virtual void
  activate (
    const typename CCM_TYPE::event_strategy_type &evs,
    IDL::traits< CCM_DDS::PortStatusListener >::ref_type status);

  virtual void passivate ();

  virtual void remove (
    IDL::traits< ::DDS::Subscriber >::ref_type subscriber);
  //@}


protected:
  typedef ::CIAOX11::DDS4CCM::Reader_T<
      typename CCM_TYPE::data_type,
      TOPIC_TYPE,
      TOPIC_SEQ_TYPE>
    DDS4CCM_Reader_type;
  typedef CIAOX11::DDS4CCM::CCM_DataReader CCM_DataReader_type;

  /**
   * DDS_Subscriber_Base_T protected members
   */
  //@{
  IDL::traits< ::DDS::DataReaderListener >::ref_type listener_ {};

  /**
   * @name configuration_complete_
   * Indicates whether configuration_complete has been invoked. Once invoked,
   * changing a connector attribute is not allowed anymore. If the user still
   * wants to set an attribute, a NonChangeable exception is thrown.
    */
  bool configuration_complete_ { false };

  typename IDL::traits<DDS4CCM_Reader_type >::ref_type dds4ccm_reader_ {};
  typename IDL::traits<CCM_DataReader_type >::ref_type ccm_data_reader_ {};
  typename IDL::traits<CIAOX11::DDS4CCM::CCM_DDS_ContentFilterSetting_i>::ref_type cft_setting_ {};

  IDL::traits<CORBA::Object>::weak_ref_type component_ {};

  SharedConditionManager condition_manager_ {};
  //@}

private:


  /**
   * @name Private Helper methods
   * Helper methods for the ContentFilterSetting
   */
  //@{
  /// Get the implementation class of the ContentFilterSetting. Creates
  /// a CFT setting instances if it does not exist.
  IDL::traits<CIAOX11::DDS4CCM::CCM_DDS_ContentFilterSetting_i>::ref_type
  create_cft_setting_impl ();
  //@}

  DDS_Subscriber_Base_T() = delete;
  DDS_Subscriber_Base_T(const DDS_Subscriber_Base_T&) = delete;
  DDS_Subscriber_Base_T(DDS_Subscriber_Base_T&&) = delete;
  DDS_Subscriber_Base_T& operator=(const DDS_Subscriber_Base_T&) = delete;
  DDS_Subscriber_Base_T& operator=(DDS_Subscriber_Base_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_subscriber_base_t.cpp"

#endif /* DDS_SUBSCRIBER_BASE_T_H_ */
