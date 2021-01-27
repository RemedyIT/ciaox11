// -*- C++ -*-
/**
 * @file    opendds_subscriber.h
 * @author  Johnny Willemsen
 *
 * @brief   Wrapper facade for OpenDDS. Implements the OpenDDS extensions
 *          to the spec compliant IDL
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_OpenDDS_SUBSCRIBER_H_
#define DDSX11_IMPL_OpenDDS_SUBSCRIBER_H_

#include "dds/dds_subscriber.h"
#include "dds/dds_export.h"

namespace DDSX11
{
  namespace OpenDDS_PROXY
  {
    class DDSX11_IMPL_Export OpenDDS_Subscriber_proxy final
      : public virtual DDSX11::DDS_Subscriber_proxy
    {
    public:
      OpenDDS_Subscriber_proxy (
        DDS_Native::DDS::Subscriber * sub);

      virtual ~OpenDDS_Subscriber_proxy () = default;

      /**
       * @name  create_datareader_with_profile
       * @brief OpenDDS extension. Creates a data reader, using
       *        the QOS profile string
       */
      IDL::traits< ::DDS::DataReader>::ref_type
      create_datareader_with_profile (
        IDL::traits< ::DDS::TopicDescription>::ref_type a_topic,
        const std::string &qos_profile,
        IDL::traits< ::DDS::DataReaderListener>::ref_type a_listener,
        ::DDS::StatusMask mask) override;

  private:
      OpenDDS_Subscriber_proxy() = delete;
      OpenDDS_Subscriber_proxy(const OpenDDS_Subscriber_proxy&) = delete;
      OpenDDS_Subscriber_proxy(OpenDDS_Subscriber_proxy&&) = delete;
      OpenDDS_Subscriber_proxy& operator=(const OpenDDS_Subscriber_proxy&) = delete;
      OpenDDS_Subscriber_proxy& operator=(OpenDDS_Subscriber_proxy&&) = delete;
    };
  }
}

#endif /* DDSX11_IMPL_OpenDDS_SUBSCRIBER_H_ */
