// -*- C++ -*-
/**
 * @file    dds_vendor_log_formatters.h
 * @author  Marcel Smit
 *
 * @brief   NDDS specific overrides for logging formats
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DDS_VENDOR_LOG_FORMATTERS_H_
#define DDSX11_IMPL_DDS_VENDOR_LOG_FORMATTERS_H_

inline std::string translate_vendor_statuskind (const ::DDS::StatusKind &ret)
{
#define DDS_VENDOR_STATUSKIND(X) case X: return #X
  switch (ret)
  {
    DDS_VENDOR_STATUSKIND (::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS);
    DDS_VENDOR_STATUSKIND (::DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS);
  }
#undef DDS_VENDOR_STATUSKIND
  return translate_statuskind (ret);
}

inline void translate_vendor_statusmask (std::string &ret, ::DDS::StatusMask const &mask)
{
#define DDS_VENDOR_STATUS_MASK_1(X) if (mask == X) ret += #X; return
  DDS_VENDOR_STATUS_MASK_1 (::DDS::STATUS_MASK_NONE);
  DDS_VENDOR_STATUS_MASK_1 (::DDS::STATUS_MASK_ALL);
#undef DDS_VENDOR_STATUS_MASK_1
#define DDS_VENDOR_CHECK_MASK(Y) \
    if (mask & Y) { \
      if (!ret.empty ()) \
          ret += " | "; \
      ret += translate_vendor_statuskind (Y); \
    }
  DDS_VENDOR_CHECK_MASK (::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS);
  DDS_VENDOR_CHECK_MASK (::DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS);
#undef DDS_VENDOR_CHECK_MASK
  translate_statusmask(ret, mask);
}

inline std::string translate_vendor_qos_policy_id (const ::DDS::QosPolicyId_t &ret)
{
#define DDS_QOS_POLICY_ID(X) case X: return #X
  switch (ret)
  {
    DDS_QOS_POLICY_ID (::DDS::TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::WIREPROTOCOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DISCOVERY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DATAREADERRESOURCELIMITS_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DATAWRITERRESOURCELIMITS_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DATAREADERPROTOCOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DATAWRITERPROTOCOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DOMAINPARTICIPANTRESOURCELIMITS_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::EVENT_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DATABASE_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::RECEIVERPOOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DISCOVERYCONFIG_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::EXCLUSIVEAREA_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::USEROBJECT_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::SYSTEMRESOURCELIMITS_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TRANSPORTSELECTION_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TRANSPORTUNICAST_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TRANSPORTMULTICAST_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TRANSPORTBUILTIN_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TYPESUPPORT_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::PROPERTY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::PUBLISHMODE_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::ASYNCHRONOUSPUBLISHER_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::ENTITYNAME_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::SERVICE_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::BATCH_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::PROFILE_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::LOCATORFILTER_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::MULTICHANNEL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TRANSPORTENCAPSULATION_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::PUBLISHERPROTOCOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::SUBSCRIBERPROTOCOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TOPICPROTOCOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::DOMAINPARTICIPANTPROTOCOL_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::AVAILABILITY_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::TRANSPORTMULTICASTMAPPING_QOS_POLICY_ID);
    DDS_QOS_POLICY_ID (::DDS::LOGGING_QOS_POLICY_ID);
  }
#undef DDS_QOS_POLICY_ID
  return translate_qos_policy_id (ret);
}


/**
 * Translates NDDS specific DDS::InstanceHandle_t from its value to a string.
 */
template <typename OS>
struct instance_handle_formatter
{
  inline OS& operator ()(
      OS& os_,
      ::DDS::InstanceHandle_t const &val_)
  {
    os_ << "DDS::InstanceHandle_t{";
    for (uint32_t i = 0; i < 4; ++i)
    {
      uint32_t idx = i*4;
      int32_t val = ntohl(val_.value ()[idx] | (val_.value ()[idx+1] << 8) | (val_.value ()[idx+2] << 16) | val_.value ()[idx+3] << 24);
      os_ << "0X"<< std::uppercase << std::hex << val << std::dec << std::nouppercase;
      if (i != 3) os_ << ",";
    }
    os_ << "}";
    return os_;
  }
};

/**
 * Translates the vendor specific DDS::StatusKind from an integer value to a string.
 * CORE usage
 */
struct status_kind_formatter
{
  status_kind_formatter () {}

  inline std::ostream& operator ()(
      std::ostream& os_,
      const ::DDS::StatusKind& val_)
  {
    os_ << translate_vendor_statuskind (val_);
    return os_;
  }
};

/**
 * Translates the vendor specific DDS::QosPolicyId_t from an integer value to a string.
 * CORE usage
 */
struct qos_policy_id_formatter
{
  qos_policy_id_formatter () {}

  inline std::ostream& operator ()(
      std::ostream& os_,
      const ::DDS::QosPolicyId_t& val_)
  {
    os_ << translate_vendor_qos_policy_id (val_);
    return os_;
  }
};

/**
 * Translates the DDS::StatusMask from an integer value to a string.
 */
struct status_mask_formatter
{
  inline std::ostream&
  operator ()(
    std::ostream& os_,
    ::DDS::StatusMask const &val_)
  {
    std::string mask;
    translate_vendor_statusmask (mask, val_);
    os_ << mask;
    return os_;
  }
};

#endif /* DDSX11_IMPL_DDS_VENDOR_LOG_FORMATTERS_H_ */
