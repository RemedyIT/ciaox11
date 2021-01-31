// -*- C++ -*-
/**
 * @file    opendds_publisher.h
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_OpenDDS_PUBLISHER_H_
#define DDSX11_IMPL_OpenDDS_PUBLISHER_H_

#include "dds/dds_publisher.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    class DDSX11_IMPL_Export OpenDDS_Publisher_proxy final
      : public virtual DDSX11::DDS_Publisher_proxy
    {
    public:
      OpenDDS_Publisher_proxy (
        DDS_Native::DDS::Publisher * p);

      virtual ~OpenDDS_Publisher_proxy () = default;

      /**
       * @name  create_datawriter_with_profile
       * @brief OpenDDS extension. Creates a data writer, using
       *        the QOS profile string
       */
      IDL::traits< ::DDS::DataWriter>::ref_type
      create_datawriter_with_profile (
        IDL::traits< ::DDS::Topic>::ref_type a_topic,
        const std::string &qos_profile,
        IDL::traits< ::DDS::DataWriterListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;

    private:
      OpenDDS_Publisher_proxy() = delete;
      OpenDDS_Publisher_proxy(const OpenDDS_Publisher_proxy&) = delete;
      OpenDDS_Publisher_proxy(OpenDDS_Publisher_proxy&&) = delete;
      OpenDDS_Publisher_proxy& operator=(const OpenDDS_Publisher_proxy&) = delete;
      OpenDDS_Publisher_proxy& operator=(OpenDDS_Publisher_proxy&&) = delete;
    };
  }
}

#endif /* DDSX11_IMPL_OpenDDS_PUBLISHER_H_ */
