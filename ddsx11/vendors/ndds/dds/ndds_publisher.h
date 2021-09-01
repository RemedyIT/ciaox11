// -*- C++ -*-
/**
 * @file    ndds_publisher.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for NDDS. Implements the NDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_NDDS_PUBLISHER_H_
#define DDSX11_IMPL_NDDS_PUBLISHER_H_

#include "dds/dds_publisher.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace NDDS_PROXY
  {
    class DDSX11_IMPL_Export NDDS_Publisher_proxy final
      : public virtual DDSX11::DDS_Publisher_proxy
    {
    public:
      explicit NDDS_Publisher_proxy (DDS_Native::DDS::Publisher * p);

      ~NDDS_Publisher_proxy () override = default;

      /**
       * @name  create_datawriter_with_profile
       * @brief NDDS extension. Creates a data writer, using
       *        the QOS profile string
       */
      IDL::traits< ::DDS::DataWriter>::ref_type
      create_datawriter_with_profile (
        IDL::traits< ::DDS::Topic>::ref_type a_topic,
        const std::string &qos_profile,
        IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;

      IDL::traits< ::DDS::PublisherListener>::ref_type
      get_listener () override;

    private:
      NDDS_Publisher_proxy() = delete;
      NDDS_Publisher_proxy(const NDDS_Publisher_proxy&) = delete;
      NDDS_Publisher_proxy(NDDS_Publisher_proxy&&) = delete;
      NDDS_Publisher_proxy& operator=(const NDDS_Publisher_proxy&) = delete;
      NDDS_Publisher_proxy& operator=(NDDS_Publisher_proxy&&) = delete;
    };
  }
}

#endif /* DDSX11_IMPL_NDDS_PUBLISHER_H_ */
