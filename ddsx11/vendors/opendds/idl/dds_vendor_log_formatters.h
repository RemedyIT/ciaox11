// -*- C++ -*-
/**
 * @file    dds_vendor_log_formatters.h
 * @author  Johnny Willemsen
 *
 * @brief   OpenDDS specific overrides for logging formats
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DDS_VENDOR_LOG_FORMATTERS_H_
#define DDSX11_IMPL_DDS_VENDOR_LOG_FORMATTERS_H_

inline std::string translate_vendor_statuskind (const ::DDS::StatusKind &ret)
{
#define DDS_VENDOR_STATUSKIND(X) case ::X: return #X
//   switch (ret)
//   {
//     DDS_VENDOR_STATUSKIND (DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS);
//     DDS_VENDOR_STATUSKIND (DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS);
//   }
#undef DDS_VENDOR_STATUSKIND
  return translate_statuskind (ret);
}

inline void translate_vendor_statusmask (std::string &ret, ::DDS::StatusMask const &mask)
{
#define DDS_VENDOR_STATUS_MASK(X) if (mask == ::X) { ret += #X; return; }
  DDS_VENDOR_STATUS_MASK (DDS::STATUS_MASK_NONE)
  DDS_VENDOR_STATUS_MASK (DDS::STATUS_MASK_ALL)
#undef DDS_VENDOR_STATUS_MASK
#define DDS_VENDOR_CHECK_MASK(Y) \
    if (mask & ::Y) { \
      if (ret.length () != 0) \
          ret += " | "; \
      ret += translate_vendor_statuskind (::Y); \
    }
//   DDS_VENDOR_CHECK_MASK (DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS);
//   DDS_VENDOR_CHECK_MASK (DDS::RELIABLE_READER_ACTIVITY_CHANGED_STATUS);
#undef DDS_VENDOR_CHECK_MASK
  translate_statusmask(ret, mask);
}

inline std::string translate_vendor_qos_policy_id (const ::DDS::QosPolicyId_t &ret)
{
  return translate_qos_policy_id (ret);
}

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

/**
 * Translates OpenDDS specific DDS::InstanceHandle_t from its value to a string.
 */
template <typename OS>
struct instance_handle_formatter
{
  inline OS& operator ()(
      OS& os_,
      ::DDS::InstanceHandle_t const &val_)
  {
    os_ << "{" << val_.value () << "}";
    return os_;
  }
};

#endif /* DDSX11_IMPL_DDS_VENDOR_LOG_FORMATTERS_H_ */
