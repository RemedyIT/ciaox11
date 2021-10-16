// -*- C++ -*-
/**
 * @file    dds4ccm_data_listener_control_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_DATA_LISTENER_CONTROL_T_H_
#define DDS4CCM_DATA_LISTENER_CONTROL_T_H_

#include "dds4ccm/idl/dds4ccm_data_listener_controlC.h"
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"

#include <atomic>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

template <typename BASE_TYPE>
class CCM_DDS_DataListenerControl_T
  : public virtual CIAOX11::DDS4CCM::FacetBase<BASE_TYPE>
{
public:
  /// Constructor
  explicit CCM_DDS_DataListenerControl_T (
    IDL::traits<CORBA::Object>::weak_ref_type component);

  /// Destructor
  ~CCM_DDS_DataListenerControl_T () override = default;

  /// Get the listener mode
  ::CCM_DDS::ListenerMode mode () override;

  /// Set the listener mode
  void mode (::CCM_DDS::ListenerMode mode) override;

  /// Get the max_delivered_data
  ::CCM_DDS::DataNumber_t max_delivered_data () override;

  /// Set the max_delivered_data
  void max_delivered_data (::CCM_DDS::DataNumber_t max_delivered_data) override;

private:
  std::atomic< ::CCM_DDS::ListenerMode > mode_ {::CCM_DDS::ListenerMode::NOT_ENABLED};
  std::atomic< ::CCM_DDS::DataNumber_t > max_delivered_data_ {0};

  CCM_DDS_DataListenerControl_T() = delete;
  CCM_DDS_DataListenerControl_T(const CCM_DDS_DataListenerControl_T&) = delete;
  CCM_DDS_DataListenerControl_T(CCM_DDS_DataListenerControl_T&&) = delete;
  CCM_DDS_DataListenerControl_T& operator=(const CCM_DDS_DataListenerControl_T&) = delete;
  CCM_DDS_DataListenerControl_T& operator=(CCM_DDS_DataListenerControl_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_data_listener_control_t.cpp"

#endif /* DDS4CCM_DATA_LISTENER_CONTROL_T_H_ */

