// -*- C++ -*-
/**
 * @file    dds4ccm_data_listener_control_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */


template <typename BASE_TYPE>
CCM_DDS_DataListenerControl_T<BASE_TYPE>::CCM_DDS_DataListenerControl_T (
  IDL::traits< CORBA::Object >::weak_ref_type component)
  : CIAOX11::DDS4CCM::FacetBase< BASE_TYPE > (component)
{
}

template <typename BASE_TYPE>
::CCM_DDS::ListenerMode
CCM_DDS_DataListenerControl_T<BASE_TYPE>::mode ()
{
  DDS4CCM_LOG_TRACE ("CCM_DDS_DataListenerControl_T::mode");
  return this->mode_.load ();
}

template <typename BASE_TYPE>
void
CCM_DDS_DataListenerControl_T<BASE_TYPE>::mode (::CCM_DDS::ListenerMode mode)
{
  DDS4CCM_LOG_TRACE ("CCM_DDS_DataListenerControl_T::mode");
  this->mode_ = mode;
}

template <typename BASE_TYPE>
::CCM_DDS::DataNumber_t
CCM_DDS_DataListenerControl_T<BASE_TYPE>::max_delivered_data ()
{
  DDS4CCM_LOG_TRACE ("CCM_DDS_DataListenerControl_T::max_delivered_data");
  return this->max_delivered_data_.load ();
}

template <typename BASE_TYPE>
void
CCM_DDS_DataListenerControl_T<BASE_TYPE>::max_delivered_data (
  ::CCM_DDS::DataNumber_t max_delivered_data)
{
  DDS4CCM_LOG_TRACE ("CCM_DDS_DataListenerControl_T::max_delivered_data");
  this->max_delivered_data_ = max_delivered_data;
}
