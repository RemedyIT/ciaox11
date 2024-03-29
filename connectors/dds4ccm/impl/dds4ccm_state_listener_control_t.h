// -*- C++ -*-
/**
 * @file    dds4ccm_state_listener_control_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_STATE_LISTENER_CONTROL_T_H_
#define DDS4CCM_STATE_LISTENER_CONTROL_T_H_

#include "dds4ccm/impl/dds4ccm_data_listener_control_t.h"

template <typename BASE_TYPE>
class CCM_DDS_StateListenerControl_T
  : public virtual CCM_DDS_DataListenerControl_T<BASE_TYPE>
{
public:
  explicit CCM_DDS_StateListenerControl_T (IDL::traits<CORBA::Object>::weak_ref_type component);
  ~CCM_DDS_StateListenerControl_T () override = default;

  /// Get the is_filter_interpreted
  bool is_filter_interpreted () override;

  /// Set the is_filter_interpreted
  void is_filter_interpreted (bool is_filter_interpreted) override;

private:
  std::atomic_bool is_filter_interpreted_ { false };

  CCM_DDS_StateListenerControl_T() = delete;
  CCM_DDS_StateListenerControl_T(const CCM_DDS_StateListenerControl_T&) = delete;
  CCM_DDS_StateListenerControl_T(CCM_DDS_StateListenerControl_T&&) = delete;
  CCM_DDS_StateListenerControl_T& operator=(const CCM_DDS_StateListenerControl_T&) = delete;
  CCM_DDS_StateListenerControl_T& operator=(CCM_DDS_StateListenerControl_T&&) = delete;
};

#include "dds4ccm/impl/dds4ccm_state_listener_control_t.cpp"

#endif /* DDS4CCM_STATE_LISTENER_CONTROL_T_H_ */

