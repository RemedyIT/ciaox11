// -*- C++ -*-
/**
 * @file    ndds_subscriber.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_SUBSCRIBER_H_
#define DDSX11_IMPL_NDDS_SUBSCRIBER_H_

#include "dds/dds_subscriber.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    class DDSX11_IMPL_Export NDDS_Subscriber_proxy final
      : public virtual DDSX11::DDS_Subscriber_proxy
    {
    public:
      NDDS_Subscriber_proxy (
        DDS_Native::DDS::Subscriber * sub);

      virtual ~NDDS_Subscriber_proxy () = default;

      /**
       * @name  create_datareader_with_profile
       * @brief NDDS extension. Creates a data reader, using
       *        the QOS profile string
       */
      virtual IDL::traits< ::DDS::DataReader >::ref_type
      create_datareader_with_profile (
        IDL::traits< ::DDS::TopicDescription >::ref_type a_topic,
        const std::string &qos_profile,
        IDL::traits< ::DDS::DataReaderListener >::ref_type a_listener,
        ::DDS::StatusMask mask) override;

  private:
      /**
       * Private helper methods
       */
      //@{
      DDS_Native::DDS::DataReader *
      create_native_datareader_with_profile (
        IDL::traits< ::DDS::Topic >::ref_type topic,
        const std::string &qos_profile,
        DDS_Native::DDS::DataReaderListener * ccm_dds_drl,
        ::DDS::StatusMask mask);

      DDS_Native::DDS::DataReader *
      create_native_datareader_with_profile (
        IDL::traits< ::DDS::ContentFilteredTopic >::ref_type topic,
        const std::string &qos_profile,
        DDS_Native::DDS::DataReaderListener * ccm_dds_drl,
        ::DDS::StatusMask mask);
      //@}

      NDDS_Subscriber_proxy() = delete;
      NDDS_Subscriber_proxy(const NDDS_Subscriber_proxy&) = delete;
      NDDS_Subscriber_proxy(NDDS_Subscriber_proxy&&) = delete;
      NDDS_Subscriber_proxy& operator=(const NDDS_Subscriber_proxy&) = delete;
      NDDS_Subscriber_proxy& operator=(NDDS_Subscriber_proxy&&) = delete;
    };
  }
}

#endif /* DDSX11_IMPL_NDDS_SUBSCRIBER_H_ */
