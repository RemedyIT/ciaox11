// -*- C++ -*-
/**
 * @file    dds_publisher_listener.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_IMPL_PUBLISHER_LISTENER_H_
#define DDSX11_IMPL_PUBLISHER_LISTENER_H_

#include "dds/dds_common.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_listener_guard_t.h"

namespace DDSX11
{
  class DDS_PublisherListener_proxy
    : public DDS_Native::DDS::PublisherListener
  {
  public:
    /// Constructor
    DDS_PublisherListener_proxy (
      IDL::traits< ::DDS::PublisherListener >::ref_type p);

    /// Destructor
    virtual ~DDS_PublisherListener_proxy () override = default;

    virtual void
    on_offered_deadline_missed (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::OfferedDeadlineMissedStatus & status) override;

    virtual void
    on_offered_incompatible_qos (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::OfferedIncompatibleQosStatus & status) override;

    virtual void
    on_liveliness_lost (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::LivelinessLostStatus & status) override;

    virtual void
    on_publication_matched (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::PublicationMatchedStatus & status) override;

    IDL::traits< ::DDS::PublisherListener >::ref_type
    get_publisher_listener ();

  protected:
    IDL::traits< ::DDS::PublisherListener >::ref_type impl_;

  private:
    DDS_PublisherListener_proxy() = delete;
    DDS_PublisherListener_proxy(const DDS_PublisherListener_proxy&) = delete;
    DDS_PublisherListener_proxy(DDS_PublisherListener_proxy&&) = delete;
    DDS_PublisherListener_proxy& operator=(const DDS_PublisherListener_proxy&) = delete;
    DDS_PublisherListener_proxy& operator=(DDS_PublisherListener_proxy&&) = delete;
  };

  typedef DDSX11_Listener_Guard_T<
    DDS_Native::DDS::PublisherListener,
    ::DDS::PublisherListener> PublisherListener_Guard;

}

#endif /* DDSX11_IMPL_PUBLISHER_LISTENER_H_ */
