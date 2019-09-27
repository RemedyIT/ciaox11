// -*- C++ -*-
/**
 * @file    dds4ccm_state_listener_control_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "dds4ccm/logger/dds4ccm_log.h"

template <typename BASE_TYPE>
CCM_DDS_StateListenerControl_T<BASE_TYPE>::CCM_DDS_StateListenerControl_T (
    IDL::traits< CORBA::Object >::weak_ref_type component)
  : CIAOX11::DDS4CCM::FacetBase<BASE_TYPE> (component)
  , CCM_DDS_DataListenerControl_T<BASE_TYPE> (component)
{
  DDS4CCM_LOG_TRACE ("CCM_DDS_StateListenerControl_T::CCM_DDS_StateListenerControl_T");
}

template <typename BASE_TYPE>
bool
CCM_DDS_StateListenerControl_T<BASE_TYPE>::is_filter_interpreted ()
{
  DDS4CCM_LOG_TRACE ("CCM_DDS_StateListenerControl_T::is_filter_interpreted");
  return this->is_filter_interpreted_.load ();
}

template <typename BASE_TYPE>
void
CCM_DDS_StateListenerControl_T<BASE_TYPE>::is_filter_interpreted (bool is_filter_interpreted)
{
  this->is_filter_interpreted_ = is_filter_interpreted;
}
