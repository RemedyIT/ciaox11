// -*- C++ -*-
/**
 * @file    dds4ccm_dds_update_port_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector Update port
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_updater_t.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
DDS_Update_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::DDS_Update_Port_T (
  IDL::traits<CORBA::Object>::ref_type component)
  : component_ (component.weak_reference ())
{
  DDS4CCM_LOG_TRACE ("DDS_Update_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::DDS_Update_Port_T");
}


template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Update_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_complete (
  IDL::traits<::DDS::Topic>::ref_type topic,
  IDL::traits<::DDS::Publisher>::ref_type publisher,
  const std::string &qos_profile)
{
  DDS4CCM_LOG_TRACE ("DDS_Update_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::configuration_complete");

  // Check whether a connection has been made to one of the basic ports.
  // If so, a DataWriter should be created.
  if (!this->data_writer_ && (this->dds4ccm_updater_ || this->ccm_data_writer_))
  {
    if (!qos_profile.empty ())
    {
      this->data_writer_ =
        publisher->create_datawriter_with_profile (
          topic, qos_profile, nullptr, ::DDS::STATUS_MASK_NONE);
    }
    else
    {
      ::DDS::DataWriterQos dwqos;
      ::DDS::ReturnCode_t const retcode = publisher->get_default_datawriter_qos (dwqos);

      if (retcode != DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_ERROR ("DDS_Update_Port_T<"
          << ::DDS::traits<TOPIC_TYPE>::get_type_name()
          << ">::configuration_complete - Error: Unable to retrieve get_default_datawriter_qos: <"
          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
          << ">.");
        throw ::CCM_DDS::InternalError (retcode, 0);
      }

      this->data_writer_ =
        publisher->create_datawriter (topic, dwqos, nullptr, ::DDS::STATUS_MASK_NONE);
    }

    if (this->data_writer_)
    {
      DDS4CCM_LOG_DEBUG ("DDS_Update_Port_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::configuration_complete - Created datawriter <"
        << IDL::traits<DDS::Entity>::write<entity_formatter> (this->data_writer_)
        << "> using publisher <"
        << IDL::traits<DDS::Entity>::write<entity_formatter> (publisher)
        << ">");
    }
    else
    {
      DDS4CCM_LOG_ERROR ("DDS_Update_Port_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::configuration_complete - Error: DDS returned a nil datawriter.");
      throw ::CORBA::INTERNAL ();
    }

    ::DDS::ReturnCode_t const retcode = this->data_writer_->enable ();
    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Update_Port_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::configuration_complete - Error: Unable to enable the datawriter: <" <<
        IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode) << ">.");
      throw ::CORBA::INTERNAL ();
    }

    if (this->dds4ccm_updater_)
    {
      this->dds4ccm_updater_->set_dds_writer (this->data_writer_);
    }
    if (this->ccm_data_writer_)
    {
      this->ccm_data_writer_->set_dds_entity (this->data_writer_);
    }
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_Update_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::remove (
  IDL::traits<::DDS::Publisher>::ref_type publisher)
{
  DDS4CCM_LOG_TRACE ("DDS_Update_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::remove");

  if (this->dds4ccm_updater_)
  {
    this->dds4ccm_updater_->set_dds_writer (nullptr);
  }
  if (this->ccm_data_writer_)
  {
    this->ccm_data_writer_->set_dds_entity (nullptr);
  }

  if (this->data_writer_)
  {
    DDS4CCM_LOG_DEBUG ("DDS_Update_Port_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::remove - About to remove DataWriter "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (this->data_writer_)
      << " from publisher "
      << IDL::traits<DDS::Entity>::write<entity_formatter> (publisher));

    ::DDS::ReturnCode_t const retcode =
      publisher->delete_datawriter (this->data_writer_);

    if (retcode != ::DDS::RETCODE_OK)
    {
      DDS4CCM_LOG_ERROR ("DDS_Update_Port_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::remove - Unable to remove DataWriter: <"
        << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
        << ">.");
      throw ::CORBA::INTERNAL ();
    }
    else
    {
      DDS4CCM_LOG_DEBUG ("DDS_Update_Port_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::remove - deleted DataWriter.");
    }

    this->data_writer_ = nullptr;
  }
}

/**
 * Context methods.
 */
template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename  CCM_TYPE::data_type>::ref_type
DDS_Update_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_data ()
{
  DDS4CCM_LOG_TRACE ("DDS_Update_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_data");

  if (!this->dds4ccm_updater_)
  {
    this->dds4ccm_updater_ = CORBA::make_reference< DDS4CCM_Updater_type> (this->component_);
  }

  return this->dds4ccm_updater_;
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
typename IDL::traits<typename CCM_TYPE::dds_entity_type>::ref_type
DDS_Update_Port_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::get_dds_entity ()
{
  DDS4CCM_LOG_TRACE ("DDS_Update_Port_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::get_dds_entity");

  if (!this->ccm_data_writer_)
  {
    this->ccm_data_writer_ = CORBA::make_reference< CCM_DataWriter_type> (this->component_);
  }

  return this->ccm_data_writer_;
}

