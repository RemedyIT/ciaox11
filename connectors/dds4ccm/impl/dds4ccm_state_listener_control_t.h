// -*- C++ -*-
/**
 * @file    dds4ccm_state_listener_control_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_STATE_LISTENER_CONTROL_T_H_
#define DDS4CCM_STATE_LISTENER_CONTROL_T_H_

#include "dds4ccm/impl/dds4ccm_data_listener_control_t.h"

template <typename BASE_TYPE>
class CCM_DDS_StateListenerControl_T final
  : public virtual CCM_DDS_DataListenerControl_T<BASE_TYPE>
{
public:
  /// Constructor
  CCM_DDS_StateListenerControl_T (
    IDL::traits< CORBA::Object >::weak_ref_type component);

  /// Destructor
  virtual ~CCM_DDS_StateListenerControl_T () = default;

  /// Get the is_filter_interpreted
  virtual bool is_filter_interpreted () override;

  /// Set the is_filter_interpreted
  virtual void is_filter_interpreted (bool is_filter_interpreted) override;

private:
  std::atomic_bool is_filter_interpreted_ { false };
};

#include "dds4ccm/impl/dds4ccm_state_listener_control_t.cpp"

#endif /* DDS4CCM_STATE_LISTENER_CONTROL_T_H_ */

