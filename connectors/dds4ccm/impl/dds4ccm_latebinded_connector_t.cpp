// -*- C++ -*-
/**
 * @file    dds4ccm_latebinded_connector_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of late binded connectors.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_utils.h"

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_LateBinded_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::topic_name (
  const std::string &topic_name)
{
  DDS4CCM_LOG_TRACE ("DDS_LateBinded_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::topic_name (set)");

  if (this->stop_dds (topic_name))
  {
    DDS4CCM_LOG_DEBUG ("DDS_LateBinded_Connector_T<"
      << ::DDS::traits<TOPIC_TYPE>::get_type_name()
      << ">::topic_name - Stopping DDS => switching to topic <" << topic_name << ">.");

    this->ccm_passivate ();
    this->do_ccm_remove ();

    if (!topic_name.empty ())
    {
      DDS4CCM_LOG_DEBUG ("DDS_LateBinded_Connector_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::topic_name - DDS is down. Setting topic to <" << topic_name << ">.");

      TopicBaseConnector::topic_name (topic_name);

      DDS4CCM_LOG_DEBUG ("DDS_LateBinded_Connector_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::topic_name - Initialize DDS again for topic <" << topic_name << ">.");

      this->do_configuration_complete ();
      this->do_ccm_activate ();

      DDS4CCM_LOG_DEBUG ("DDS_LateBinded_Connector_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::topic_name - DDS up and running for topic <" << topic_name << ">.");
    }
    else
    {
      DDS4CCM_LOG_DEBUG ("DDS_LateBinded_Connector_T<"
        << ::DDS::traits<TOPIC_TYPE>::get_type_name()
        << ">::topic_name - DDS is down.");
      TopicBaseConnector::topic_name (topic_name);
    }
  }
  else if (this->late_binded (topic_name))
  {
    this->do_configuration_complete ();
    this->do_ccm_activate ();
  }
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_LateBinded_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::configuration_complete ()
{
  DDS4CCM_LOG_TRACE ("DDS_LateBinded_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::configuration_complete");

  try
  {
    if (!this->late_binding ())
    {
      this->do_configuration_complete ();
    }
  }
  catch_dds4ccm_lifecycle_ex(ex, "DDS_LateBinded_Connector_T::configuration_complete")
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_LateBinded_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_activate ()
{
  DDS4CCM_LOG_TRACE ("DDS_LateBinded_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ccm_activate");

  try
  {
    if (!this->late_binding ())
    {
      this->do_ccm_activate ();
    }
  }
  catch_dds4ccm_lifecycle_ex(ex, "DDS_LateBinded_Connector_T::ccm_activate")
}

template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
void
DDS_LateBinded_Connector_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>::ccm_remove ()
{
  DDS4CCM_LOG_TRACE ("DDS_LateBinded_Connector_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::ccm_remove");

  this->do_ccm_remove ();
}
