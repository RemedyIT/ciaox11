// -*- C++ -*-
/**
 * @file    dds_log_formatters.h
 * @author  Marcel Smit
 *
 * @brief   Override default logging format of certain artifacts.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_LOG_FORMATTERS_H_
#define DDSX11_IMPL_LOG_FORMATTERS_H_

/// Helper method translating a ::DDS::ReturnCode_t into
/// a readable string
inline std::string translate_retcode (const ::DDS::ReturnCode_t &ret)
{
#define DDS_RETCODE(X) case X: return #X
  switch (ret)
  {
    DDS_RETCODE (::DDS::RETCODE_OK);
    DDS_RETCODE (::DDS::RETCODE_ERROR);
    DDS_RETCODE (::DDS::RETCODE_UNSUPPORTED);
    DDS_RETCODE (::DDS::RETCODE_BAD_PARAMETER);
    DDS_RETCODE (::DDS::RETCODE_PRECONDITION_NOT_MET);
    DDS_RETCODE (::DDS::RETCODE_OUT_OF_RESOURCES);
    DDS_RETCODE (::DDS::RETCODE_NOT_ENABLED);
    DDS_RETCODE (::DDS::RETCODE_IMMUTABLE_POLICY);
    DDS_RETCODE (::DDS::RETCODE_INCONSISTENT_POLICY);
    DDS_RETCODE (::DDS::RETCODE_ALREADY_DELETED);
    DDS_RETCODE (::DDS::RETCODE_TIMEOUT);
    DDS_RETCODE (::DDS::RETCODE_NO_DATA);
    DDS_RETCODE (::DDS::RETCODE_ILLEGAL_OPERATION);
  }
  return "***Unknown enum value for DDS::ReturnCode_t detected***";
#undef DDS_RETCODE
}

/// Helper method translating a ::DDS::StatusKind into
/// a readable string
inline std::string translate_statuskind (const ::DDS::StatusKind &ret)
{
#define DDS_STATUS_KIND(X) case X: return #X
  switch (ret)
  {
    DDS_STATUS_KIND (::DDS::INCONSISTENT_TOPIC_STATUS);
    DDS_STATUS_KIND (::DDS::OFFERED_DEADLINE_MISSED_STATUS);
    DDS_STATUS_KIND (::DDS::REQUESTED_DEADLINE_MISSED_STATUS);
    DDS_STATUS_KIND (::DDS::OFFERED_INCOMPATIBLE_QOS_STATUS);
    DDS_STATUS_KIND (::DDS::REQUESTED_INCOMPATIBLE_QOS_STATUS);
    DDS_STATUS_KIND (::DDS::SAMPLE_LOST_STATUS);
    DDS_STATUS_KIND (::DDS::SAMPLE_REJECTED_STATUS);
    DDS_STATUS_KIND (::DDS::DATA_ON_READERS_STATUS);
    DDS_STATUS_KIND (::DDS::DATA_AVAILABLE_STATUS);
    DDS_STATUS_KIND (::DDS::LIVELINESS_LOST_STATUS);
    DDS_STATUS_KIND (::DDS::LIVELINESS_CHANGED_STATUS);
    DDS_STATUS_KIND (::DDS::PUBLICATION_MATCHED_STATUS);
    DDS_STATUS_KIND (::DDS::SUBSCRIPTION_MATCHED_STATUS);
  }
  // Not found.
  return "***Unknown enum value for DDS::StatusKind detected***";
#undef DDS_STATUS_KIND
}

inline std::string translate_qos_policy_id (const ::DDS::QosPolicyId_t &ret)
{
#define DDS_QOS_POLICY_ID(X) case X: return #X
  switch (ret)
  {
    DDS_QOS_POLICY_ID (::DDS::INVALID_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::USERDATA_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DURABILITY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::PRESENTATION_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DEADLINE_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::LATENCYBUDGET_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::OWNERSHIP_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::OWNERSHIPSTRENGTH_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::LIVELINESS_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TIMEBASEDFILTER_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::PARTITION_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::RELIABILITY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DESTINATIONORDER_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::HISTORY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::RESOURCELIMITS_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::ENTITYFACTORY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::WRITERDATALIFECYCLE_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::READERDATALIFECYCLE_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TOPICDATA_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::GROUPDATA_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TRANSPORTPRIORITY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::LIFESPAN_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DURABILITYSERVICE_QOS_POLICY_ID);
  }
  // Not found.
  return "***Unknown value for DDS::QosPolicyId_t detected***";
#undef DDS_QOS_POLICY_ID
}

inline void translate_listenermask (std::string &ret, ::DDS::StatusMask const &mask)
{
#define DDS_CHECK_MASK(X, Y, Z) \
    if (X & Y) { \
      if (!Z.empty ()) \
          Z += " | "; \
      Z += translate_statuskind (Y); \
    }
  DDS_CHECK_MASK (mask, ::DDS::INCONSISTENT_TOPIC_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::OFFERED_DEADLINE_MISSED_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::REQUESTED_DEADLINE_MISSED_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::OFFERED_INCOMPATIBLE_QOS_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::REQUESTED_INCOMPATIBLE_QOS_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::SAMPLE_LOST_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::SAMPLE_REJECTED_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::DATA_ON_READERS_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::DATA_AVAILABLE_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::LIVELINESS_LOST_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::LIVELINESS_CHANGED_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::PUBLICATION_MATCHED_STATUS, ret);
  DDS_CHECK_MASK (mask, ::DDS::SUBSCRIPTION_MATCHED_STATUS, ret);

#undef DDS_CHECK_MASK
}

#include "idl/dds_vendor_log_formatters.h"
#include "ace/Time_Value.h"
#include "ace/ACE.h"

typedef std::basic_ostream<typename std::ostream::char_type, typename std::ostream::traits_type> ostream_type;

/**
 * Logs the Instance Handle of a DDS entity
 * Since this is vendor specific, the implementation
 * the instance_handle_formatter struct is put in the
 * vendor specific part of the DDS proxy.
 */
struct entity_formatter
{
  inline std::ostream&
  operator ()(
    std::ostream& os_,
    IDL::traits< ::DDS::Entity>::ref_type val_)
  {
    os_ <<
      IDL::traits< ::DDS::InstanceHandle_t>::write<instance_handle_formatter<std::ostream>>(
        val_->get_instance_handle ());
    return os_;
  }
};

/**
 * Translates the DDS::ReturnCode_t from an integer value to a string.
 */
struct retcode_formatter
{
  inline std::ostream&
  operator ()(
    std::ostream& os_,
    ::DDS::ReturnCode_t const &val_)
  {
    os_ << translate_retcode (val_);
    return os_;
  }
};

/**
 * Translates the DDS::Duration_t to a string.
 */
struct duration_formatter
{
  inline std::ostream&
  operator ()(
    std::ostream& os_,
    ::DDS::Duration_t const &val_)
  {
    os_ << ACE_Time_Value (val_.sec (), val_.nanosec () / 1000);
    return os_;
  }
};

/**
 * Translates the DDS::Time_t to a string.
 */
struct time_t_formatter
{
  inline std::ostream&
  operator ()(
    std::ostream& os_,
    ::DDS::Time_t const &val_)
  {
    ACE_TCHAR day_and_time[27];
    const ACE_TCHAR *s = 0;
    ACE_Time_Value const tv (val_.sec (), val_.nanosec () / 1000);
    ACE::timestamp (tv, day_and_time, sizeof (day_and_time) / sizeof (ACE_TCHAR));
    s = day_and_time;
    os_ << ACE_TEXT_ALWAYS_CHAR (s);
    return os_;
  }
};

/**
 * Special writer methods for usage in user space.
 * Since the StatusKind is vendor specific, the
 * implementation of the status_kind_formatter is
 * put in the vendor specific part of the DDS proxy
 */
template <typename OS>
struct status_kind_formatter_os
{
  status_kind_formatter_os () {}

  inline OS& operator ()(
      OS& os_,
      const ::DDS::StatusKind& val_)
  {
    os_ <<
      IDL::traits< ::DDS::StatusKind>::write<status_kind_formatter>(val_);
    return os_;
  }
};

template <typename OS>
struct duration_formatter_os
{
  inline OS& operator ()(
    OS& os_,
    ::DDS::Duration_t const &val_)
  {
    os_ <<
      IDL::traits< ::DDS::Duration_t>::write<duration_formatter>(val_);
    return os_;
  }
};

template <typename OS>
struct time_t_formatter_os
{
  inline OS& operator ()(
    OS& os_,
    ::DDS::Time_t const &val_)
  {
    os_ <<
      IDL::traits< ::DDS::Time_t>::write<time_t_formatter>(val_);
    return os_;
  }
};

template <typename OS>
struct qos_policy_count_formatter_os
{
  inline OS& operator ()(
    OS& os_,
    ::DDS::QosPolicyCount const &val_)
  {
    os_ << "DDS::QosPolicyCount{policy_id="
      << IDL::traits< ::DDS::QosPolicyId_t>::write<qos_policy_id_formatter>(val_.policy_id ())
      << ",count=" << val_.count () << "}";
    return os_;
  }
};


namespace DDS
{
  // Template writer for writing
  template <typename DDS_ENTITY>
  struct __DDS_Writer
  {
    __DDS_Writer (DDS_ENTITY const &dds_writer)
      : dds_writer_ (dds_writer) {}
    DDS_ENTITY const &dds_writer_;
  };

  /**
   * Writers for ::DDS::SampleRejectedStatusKind
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::SampleRejectedStatusKind> const &w)
  {
    os << IDL::traits< ::DDS::SampleRejectedStatusKind>::write(w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::SampleRejectedStatusKind> dds_write (::DDS::SampleRejectedStatusKind const &srk)
  {
    return __DDS_Writer< ::DDS::SampleRejectedStatusKind> (srk);
  }

  /**
  * Writer for ::DDS::InstanceHandle
  */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::InstanceHandle_t> const &w)
  {
    IDL::traits< ::DDS::InstanceHandle_t>::write_on<
      ostream_type, instance_handle_formatter<ostream_type>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::InstanceHandle_t> dds_write (::DDS::InstanceHandle_t const &ih)
  {
    return __DDS_Writer< ::DDS::InstanceHandle_t> (ih);
  }

  /**
   * Writers for ::DDS::StatusKind
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::StatusKind> const &w)
  {
    IDL::traits< ::DDS::StatusKind>::write_on<
      ostream_type, status_kind_formatter_os<ostream_type>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::StatusKind> dds_write (::DDS::StatusKind const &sk)
  {
    return __DDS_Writer< ::DDS::StatusKind> (sk);
  }

  /**
   * Writers for ::DDS::PublicationMatchedStatus
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::PublicationMatchedStatus> const &w)
  {
    os << "DDS::PublicationMatchedStatus{total_count=" << w.dds_writer_.total_count ()
      << ",total_count_change=" << w.dds_writer_.total_count_change ()
      << ",current_count=" << w.dds_writer_.current_count ()
      << ",current_count_change=" << w.dds_writer_.current_count_change ()
      << ",last_subscription_handle=" << ::DDS::dds_write (w.dds_writer_.last_subscription_handle ())
      << "}";
    return os;
  }

  inline __DDS_Writer< ::DDS::PublicationMatchedStatus> dds_write (::DDS::PublicationMatchedStatus const &pms)
  {
    return __DDS_Writer< ::DDS::PublicationMatchedStatus> (pms);
  }

  /**
   * Writers for ::DDS::SubscriptionMatchedStatus
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::SubscriptionMatchedStatus> const &w)
  {
    os << "DDS::SubscriptionMatchedStatus{total_count=" << w.dds_writer_.total_count ()
      << ",total_count_change=" << w.dds_writer_.total_count_change ()
      << ",current_count=" << w.dds_writer_.current_count ()
      << ",current_count_change=" << w.dds_writer_.current_count_change ()
      << ",last_publication_handle=" << ::DDS::dds_write (w.dds_writer_.last_publication_handle ())
      << "}";
    return os;
  }

  inline __DDS_Writer< ::DDS::SubscriptionMatchedStatus> dds_write (::DDS::SubscriptionMatchedStatus const &sms)
  {
    return __DDS_Writer< ::DDS::SubscriptionMatchedStatus> (sms);
  }

  /**
   * Writers for ::DDS::LivelinessLostStatus
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::LivelinessLostStatus> const &w)
  {
    IDL::traits< ::DDS::LivelinessLostStatus>::write_on<ostream_type>
      (os, w.dds_writer_);

    return os;
  }

  inline __DDS_Writer< ::DDS::LivelinessLostStatus> dds_write (::DDS::LivelinessLostStatus const &lls)
  {
    return __DDS_Writer< ::DDS::LivelinessLostStatus> (lls);
  }

  /**
   * Writers for ::DDS::LivelinessChangedStatus
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::LivelinessChangedStatus> const &w)
  {
    os << "DDS::LivelinessChangedStatus{alive_count=" << w.dds_writer_.alive_count ()
      << ",not_alive_count=" << w.dds_writer_.not_alive_count ()
      << ",alive_count_change=" << w.dds_writer_.alive_count_change ()
      << ",not_alive_count_change=" << w.dds_writer_.not_alive_count_change ()
      << ",last_publication_handle=" << w.dds_writer_.last_publication_handle ()
      << "}";
    return os;
  }

  inline __DDS_Writer< ::DDS::LivelinessChangedStatus> dds_write (::DDS::LivelinessChangedStatus const &lcs)
  {
    return __DDS_Writer< ::DDS::LivelinessChangedStatus> (lcs);
  }

  /**
   * Writers for ::DDS::Entity
   */
  struct __DDS_EntityWriter
  {
    __DDS_EntityWriter (IDL::traits< ::DDS::Entity>::ref_type e)
      : e_ (e) {}

    IDL::traits< ::DDS::Entity>::ref_type e_;
  };

  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_EntityWriter w)
  {
    IDL::traits< ::DDS::InstanceHandle_t>::write_on<
       ostream_type, instance_handle_formatter<ostream_type>>
         (os, w.e_->get_instance_handle ());
    return os;
  }

  inline __DDS_EntityWriter dds_write (IDL::traits< ::DDS::Entity>::ref_type e)
  {
    return __DDS_EntityWriter (e);
  }

  /**
   * Writers for ::DDS::Duration_t
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::Duration_t> const &w)
  {
    IDL::traits< ::DDS::Duration_t>::write_on<
      ostream_type, duration_formatter_os<ostream_type>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::Duration_t> dds_write (::DDS::Duration_t const &d)
  {
    return __DDS_Writer< ::DDS::Duration_t> (d);
  }

  /**
   * Writer for ::DDS::Time_t
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::Time_t> const &w)
  {
    IDL::traits< ::DDS::Time_t>::write_on<
      ostream_type, time_t_formatter_os<ostream_type>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::Time_t> dds_write (::DDS::Time_t const &t)
  {
    return __DDS_Writer< ::DDS::Time_t> (t);
  }

  /**
   * Writer for ::DDS::QosPolicyCount
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::QosPolicyCount> const &w)
  {
    IDL::traits< ::DDS::QosPolicyCount>::write_on<
      ostream_type, qos_policy_count_formatter_os<ostream_type>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::QosPolicyCount> dds_write (::DDS::QosPolicyCount const &q)
  {
    return __DDS_Writer< ::DDS::QosPolicyCount> (q);
  }

  /**
   * Writer for ::DDS::QosPolicyCountSeq
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer < ::DDS::QosPolicyCountSeq> const &w)
  {
    ::DDS::QosPolicyCountSeq::size_type i = 0;
    os << "DDS::PolicyCountSeq{";
    for (::DDS::QosPolicyCount const &pc : w.dds_writer_)
    {
      IDL::traits< ::DDS::QosPolicyCount>::write_on<
        ostream_type, qos_policy_count_formatter_os<ostream_type>> (os, pc);
      if (++i != w.dds_writer_.size ())
        os << ",";
    }
    os << "}";
    return os;
  }

  inline __DDS_Writer < ::DDS::QosPolicyCountSeq> dds_write (::DDS::QosPolicyCountSeq const &ri_seq)
  {
    return __DDS_Writer < ::DDS::QosPolicyCountSeq> (ri_seq);
  }


  /**
  * Helper struct for ::DDS::SampleLostStatus
  */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::SampleLostStatus> const &w)
  {
    IDL::traits< ::DDS::SampleLostStatus>::write_on<ostream_type>
      (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::SampleLostStatus> dds_write (::DDS::SampleLostStatus const &sl)
  {
    return __DDS_Writer< ::DDS::SampleLostStatus> (sl);
  }

  /**
  * Helper struct for ::DDS::InconsistentTopicStatus
  */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::InconsistentTopicStatus> const &w)
  {
    IDL::traits< ::DDS::InconsistentTopicStatus>::write_on<ostream_type>
      (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::InconsistentTopicStatus> dds_write (::DDS::InconsistentTopicStatus const &its)
  {
    return __DDS_Writer< ::DDS::InconsistentTopicStatus> (its);
  }

  /**
  * Writer for ::DDS::SampleRejectedStatus
  */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::SampleRejectedStatus> const &w)
  {
    os << "DDS::SampleRejectedStatus{total_count=" << w.dds_writer_.total_count ()
      << ",total_count_change=" << w.dds_writer_.total_count_change ()
      << ",last_reason=" << ::DDS::dds_write (w.dds_writer_.last_reason ())
      << ",last_instance_handle=" << ::DDS::dds_write (w.dds_writer_.last_instance_handle ())
      << "}";
    return os;
  }

  inline __DDS_Writer< ::DDS::SampleRejectedStatus> dds_write (::DDS::SampleRejectedStatus const &srs)
  {
    return __DDS_Writer< ::DDS::SampleRejectedStatus> (srs);
  }

#if (DDSX11_NDDS==1)
  /**
   * Writer for ::DDS::QosPolicyId_t
   */
  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::QosPolicyId_t> const &w)
  {
    IDL::traits< ::DDS::QosPolicyId_t>::write_on<
      ostream_type, qos_policy_id_formatter>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::QosPolicyId_t> dds_write (::DDS::QosPolicyId_t const &qpi)
  {
    return __DDS_Writer< ::DDS::QosPolicyId_t> (qpi);
  }
#endif

  /**
   * Writers for ::DDS::OfferedDeadlineMissedStatus and
   *             ::DDS::RequestedDeadlineMissedStatus
   */
  template <typename OS, typename DEADLINE_MISSED_STATUS>
  struct deadline_missed_qos_status_formatter_os
  {
    inline OS& operator ()(
      OS& os_,
      DEADLINE_MISSED_STATUS const &val_)
    {
      os_ << "{total_count=" << val_.total_count()
        << ",total_count_change=" << val_.total_count_change ()
        << ",last_instance_handle=" << ::DDS::dds_write (val_.last_instance_handle ())
        << "}";
      return os_;
    }
  };

  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::OfferedDeadlineMissedStatus> const &w)
  {
    os << "DDS::OfferedDeadlineMissedStatus";
    IDL::traits< ::DDS::OfferedDeadlineMissedStatus>::write_on<
      ostream_type, deadline_missed_qos_status_formatter_os<
        ostream_type, ::DDS::OfferedDeadlineMissedStatus>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::OfferedDeadlineMissedStatus> dds_write (::DDS::OfferedDeadlineMissedStatus const &odms)
  {
    return __DDS_Writer< ::DDS::OfferedDeadlineMissedStatus> (odms);
  }

  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::RequestedDeadlineMissedStatus> const &w)
  {
    os << "DDS::RequestedDeadlineMissedStatus";
    IDL::traits< ::DDS::RequestedDeadlineMissedStatus>::write_on<
      ostream_type, deadline_missed_qos_status_formatter_os<
        ostream_type, ::DDS::RequestedDeadlineMissedStatus>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::RequestedDeadlineMissedStatus> dds_write (::DDS::RequestedDeadlineMissedStatus const &rdms)
  {
    return __DDS_Writer< ::DDS::RequestedDeadlineMissedStatus> (rdms);
  }


  /**
   * Writers for ::DDS::RequestedIncompatibleQosStatus and
   *             ::DDS::OfferedIncompatibleQosStatus
   */
  template <typename OS, typename INCOMPATIBLE_STATUS>
  struct incompatible_qos_status_formatter_os
  {
    inline OS& operator ()(
      OS& os_,
      INCOMPATIBLE_STATUS const &val_)
    {
      os_ << "{total_count="
        << val_.total_count () << ",total_count_change="
        << val_.total_count_change () << ",last_policy_id="
        << IDL::traits< ::DDS::QosPolicyId_t>::write<qos_policy_id_formatter>(val_.last_policy_id ())
        << ",policies=" << ::DDS::dds_write (val_.policies ())
        << "}";
      return os_;
    }
  };

  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::RequestedIncompatibleQosStatus> const &w)
  {
    os << "DDS::RequestedIncompatibleQosStatus";
    IDL::traits< ::DDS::RequestedIncompatibleQosStatus>::write_on<
      ostream_type, incompatible_qos_status_formatter_os<ostream_type, ::DDS::RequestedIncompatibleQosStatus>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::RequestedIncompatibleQosStatus> dds_write (::DDS::RequestedIncompatibleQosStatus const &odms)
  {
    return __DDS_Writer< ::DDS::RequestedIncompatibleQosStatus> (odms);
  }

  template <typename OS>
  inline OS&
  operator << (OS& os, __DDS_Writer< ::DDS::OfferedIncompatibleQosStatus> const &w)
  {
    os << "DDS::OfferedIncompatibleQosStatus";
    IDL::traits< ::DDS::OfferedIncompatibleQosStatus>::write_on<
      ostream_type, incompatible_qos_status_formatter_os<ostream_type, ::DDS::OfferedIncompatibleQosStatus>>
        (os, w.dds_writer_);
    return os;
  }

  inline __DDS_Writer< ::DDS::OfferedIncompatibleQosStatus> dds_write (::DDS::OfferedIncompatibleQosStatus const &odms)
  {
    return __DDS_Writer< ::DDS::OfferedIncompatibleQosStatus> (odms);
  }
}

#endif /* DDSX11_IMPL_LOG_FORMATTERS_H_ */
