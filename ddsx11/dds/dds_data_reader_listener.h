// -*- C++ -*-
/**
 * @file    dds_data_reader_listener.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DATA_READER_LISTENER_H_
#define DDSX11_IMPL_DATA_READER_LISTENER_H_

#include "dds/dds_export.h"
#include "dds/dds_common.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_listener_guard_t.h"

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_DataReaderListener_proxy final
    : public DDS_Native::DDS::DataReaderListener
  {
  public:
    /// Constructor
    DDS_DataReaderListener_proxy (
      IDL::traits< ::DDS::DataReaderListener>::ref_type p);

    /// Destructor
    virtual ~DDS_DataReaderListener_proxy () = default;

    void
    on_requested_deadline_missed (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::RequestedDeadlineMissedStatus& status) override;

    void
    on_liveliness_changed (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::LivelinessChangedStatus& status) override;

    void
    on_requested_incompatible_qos (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::RequestedIncompatibleQosStatus& status) override;

    void
    on_sample_rejected (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::SampleRejectedStatus& status) override;

    void
    on_data_available (
      DDS_Native::DDS::DataReader* the_reader) override;

    void
    on_sample_lost (
      DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::SampleLostStatus& status) override;

    void
    on_subscription_matched (DDS_Native::DDS::DataReader* the_reader,
      const DDS_Native::DDS::SubscriptionMatchedStatus& status) override;

    IDL::traits< ::DDS::DataReaderListener>::ref_type
    get_datareaderlistener ();

  private:
    IDL::traits< ::DDS::DataReaderListener>::ref_type impl_;

    // In order to gain performance (especially for on_data_available), we keep
    // a weak_ref_pointer to the data reader. This pointer will be set the first
    // time a callback from DDS comes in. The pointer will be converted to a strong
    // reference and checked on each callback.
    // This prevents looking up the internal map in the ProxyEntityManager each
    // time a callback is called.
    IDL::traits< ::DDS::DataReader>::weak_ref_type dr_ {};

    IDL::traits< ::DDS::DataReader>::ref_type
    get_datareader (DDS_Native::DDS::DataReader *the_reader);

    DDS_DataReaderListener_proxy() = delete;
    DDS_DataReaderListener_proxy(const DDS_DataReaderListener_proxy&) = delete;
    DDS_DataReaderListener_proxy(DDS_DataReaderListener_proxy&&) = delete;
    DDS_DataReaderListener_proxy& operator=(const DDS_DataReaderListener_proxy&) = delete;
    DDS_DataReaderListener_proxy& operator=(DDS_DataReaderListener_proxy&&) = delete;
  };

  typedef DDSX11_Listener_Guard_T<
    DDS_Native::DDS::DataReaderListener,
    ::DDS::DataReaderListener> DataReaderListener_Guard;
}

#endif /* DDSX11_IMPL_DATA_READER_LISTENER_H_ */
