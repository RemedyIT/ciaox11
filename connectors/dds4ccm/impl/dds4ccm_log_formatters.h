// -*- C++ -*-
/**
 * @file    dds4ccm_log_formatters.h
 * @author  Marcel Smit
 *
 * @brief   Override default logging format of certain artifacts.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_LOG_FORMATTERS_H_
#define DDS4CCM_LOG_FORMATTERS_H_

#include "ccm_ddsC.h"

// Readinfo
/**
 * Special writer methods for usage in user space.
 */
template <typename OS>
struct read_info_formatter_os
{
  read_info_formatter_os () = default;

  inline OS& operator ()(OS& os_, const ::CCM_DDS::ReadInfo& val_)
  {
    os_ << "CCM_DDS::ReadInfo{instance_handle=" << ::DDS::dds_write (val_.instance_handle ())
      << ",source_timestamp="
      << IDL::traits< ::DDS::Time_t>::write<time_t_formatter>(val_.source_timestamp ())
      << ",access_status="
      << IDL::traits< ::CCM_DDS::AccessStatus>::write (val_.access_status ())
      << ",instance_status="
      << IDL::traits< ::CCM_DDS::InstanceStatus>::write (val_.instance_status ())
      << "}";
    return os_;
  }
};

namespace DDS
{
  /**
   * Writer for ::CCM_DDS::ReadInfo
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer < ::CCM_DDS::ReadInfo> const &w)
  {
    IDL::traits< ::CCM_DDS::ReadInfo>::write_on<ostream_type, read_info_formatter_os<ostream_type>> (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer < ::CCM_DDS::ReadInfo> dds_write (::CCM_DDS::ReadInfo const &ri)
  {
    return __DDS_Writer < ::CCM_DDS::ReadInfo> (ri);
  }

  /**
   * Writer for ::CCM_DDS::ReadInfoSeq
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer < ::CCM_DDS::ReadInfoSeq> const &w)
  {
    ::CCM_DDS::ReadInfoSeq::size_type i = 0;
    os << "CCM_DDS::ReadInfoSeq{";
    for (::CCM_DDS::ReadInfo const &ri : w.dds_writer_)
    {
      IDL::traits< ::CCM_DDS::ReadInfo>::write_on<ostream_type, read_info_formatter_os<ostream_type>> (os, ri);
      if (++i != w.dds_writer_.size ())
        os << ",";
    }
    os << "}";
    return os;
  }

  inline __DDS_Writer < ::CCM_DDS::ReadInfoSeq> dds_write (::CCM_DDS::ReadInfoSeq const &ri_seq)
  {
    return __DDS_Writer < ::CCM_DDS::ReadInfoSeq> (ri_seq);
  }

  /**
   * Writer for ::CCM_DDS::AccessStatus
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::CCM_DDS::AccessStatus> const &w)
  {
    IDL::traits< ::CCM_DDS::AccessStatus>::write_on<ostream_type> (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::CCM_DDS::AccessStatus> dds_write (::CCM_DDS::AccessStatus const &as)
  {
    return __DDS_Writer< ::CCM_DDS::AccessStatus> (as);
  }

  /**
   * Writer for ::CCM_DDS::InstanceStatus
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::CCM_DDS::InstanceStatus> const &w)
  {
    IDL::traits< ::CCM_DDS::InstanceStatus>::write_on<ostream_type> (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::CCM_DDS::InstanceStatus> dds_write (::CCM_DDS::InstanceStatus const &as)
  {
    return __DDS_Writer< ::CCM_DDS::InstanceStatus> (as);
  }

  /**
   * Writer for ::CCM_DDS::ListenerMode
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::CCM_DDS::ListenerMode> const &w)
  {
    IDL::traits< ::CCM_DDS::ListenerMode>::write_on<ostream_type> (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::CCM_DDS::ListenerMode> dds_write (::CCM_DDS::ListenerMode const &as)
  {
    return __DDS_Writer< ::CCM_DDS::ListenerMode> (as);
  }
}

#endif /* DDS4CCM_LOG_FORMATTERS_H_ */
