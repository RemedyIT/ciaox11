// -*- C++ -*-
/**
 * @file    dds4ccm_dds_listen_port_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_data_listener_control_t.h"
#include "dds4ccm/logger/dds4ccm_log.h"


template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE, CIAOX11::DDS4CCM::DDS4CCM_LISTENER_READ_TAKE LRT>
DDS_Listen_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, LRT>::DDS_Listen_Port_T (IDL::traits<CORBA::Object>::ref_type component)
  : DDS_Subscriber_Base_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> (component)
{
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE, CIAOX11::DDS4CCM::DDS4CCM_LISTENER_READ_TAKE LRT>
void
DDS_Listen_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, LRT>::activate (
  const typename CCM_TYPE::event_strategy_type &evs,
  typename IDL::traits<typename CCM_TYPE::data_listener_type >::ref_type listener,
  IDL::traits< CCM_DDS::PortStatusListener >::ref_type status)
{
  DDS4CCM_LOG_TRACE ("DDS_Listen_Port_T::activate");

  ::DDS::StatusMask const mask =
    DataReaderListener_type::get_mask (listener, status);

  if (mask != 0)
  {
    if (!this->listener_)
    {
      this->listener_ =
        CORBA::make_reference<DataReaderListener_type>(
          evs,
          this->data_control_,
          this->condition_manager_);
    }
    IDL::traits< ::DDS::DataReader >::ref_type dr =
      this->dds4ccm_reader_->get_dds_reader ();
    if (dr)
    {
      ::DDS::ReturnCode_t const retcode = dr->set_listener (
        this->listener_, mask);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("DDS_Listen_Port_T::activate - "
          << "Error while setting the listener on the listen - <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CORBA::INTERNAL ();
      }
    }
    else
    {
      DDS4CCM_LOG_ERROR ("DDS_Listen_Port_T::activate - "
        "Error while retrieving the DataReader.");
      throw ::CORBA::INTERNAL ();
    }
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE, CIAOX11::DDS4CCM::DDS4CCM_LISTENER_READ_TAKE LRT>
IDL::traits< CCM_DDS::CCM_DataListenerControl >::ref_type
DDS_Listen_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE, LRT>::get_data_control ()
{
  DDS4CCM_LOG_TRACE ("DDS_Listen_Port_T::get_data_control");

  if (!this->data_control_)
  {
    this->data_control_ = CORBA::make_reference<DataListenerControl_type> (this->component_);
  }

  return this->data_control_;
}
