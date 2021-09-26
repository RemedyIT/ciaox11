// -*- C++ -*-
/**
 * @file    dds4ccm_sample_info.h
 * @author  Marcel Smit
 *
 * @brief   Conversion traits from SampleInfo to ReadInfo
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_SAMPLE_INFO_H_
#define DDS4CCM_SAMPLE_INFO_H_

#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/idl/ccm_ddsC.h"

namespace DDS4CCM
{
  template<typename T>
  struct traits {};

  template<>
  struct traits< ::DDS::SampleInfo >
  {
    struct to_readinfo
    {
      ::CCM_DDS::ReadInfo read_info_;

      to_readinfo (const ::DDS::SampleInfo& sample_info)
      {
        this->read_info_.source_timestamp (sample_info.source_timestamp ());
        if (sample_info.sample_state () == ::DDS::NOT_READ_SAMPLE_STATE)
        {
          this->read_info_.access_status (::CCM_DDS::AccessStatus::FRESH_INFO);
        }
        else if (sample_info.sample_state () == ::DDS::READ_SAMPLE_STATE)
        {
          this->read_info_.access_status (::CCM_DDS::AccessStatus::ALREADY_SEEN);
        }

        this->read_info_.instance_handle (sample_info.instance_handle ());

        if (sample_info.instance_state () == ::DDS::ALIVE_INSTANCE_STATE &&
            sample_info.view_state () == ::DDS::NEW_VIEW_STATE)
        {
          // Instance_status
          this->read_info_.instance_status (::CCM_DDS::InstanceStatus::INSTANCE_CREATED);
        }
        else if (sample_info.instance_state () == ::DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
        {
          // Instance_status deleted
          this->read_info_.instance_status (::CCM_DDS::InstanceStatus::INSTANCE_DELETED);
        }
        else if ((sample_info.instance_state () == ::DDS::ALIVE_INSTANCE_STATE &&
          sample_info.view_state () == ::DDS::NOT_NEW_VIEW_STATE) ||
          sample_info.instance_state () == ::DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE)
          {
            // Instance_status updated
            this->read_info_.instance_status (::CCM_DDS::InstanceStatus::INSTANCE_UPDATED);
          }
      }

      operator ::CCM_DDS::ReadInfo ()
      {
        // Move the read_info_ to the caller, we can only do a conversion once this
        // way but it saves a copy in all cases
        return std::move(this->read_info_);
      }
    };
  };
}

#endif /* DDS4CCM_SAMPLE_INFO_H_ */
