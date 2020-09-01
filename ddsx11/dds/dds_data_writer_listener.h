// -*- C++ -*-
/**
 * @file    dds_data_writer_listener.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DATA_WRITER_LISTENER_H_
#define DDSX11_IMPL_DATA_WRITER_LISTENER_H_

#include "dds/dds_export.h"
#include "dds/dds_common.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_listener_guard_t.h"

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_DataWriterListener_proxy final
    : public DDS_Native::DDS::DataWriterListener
  {
  public:
    /// Constructor
    DDS_DataWriterListener_proxy (
      IDL::traits< ::DDS::DataWriterListener>::ref_type p);

    /// Destructor
    virtual ~DDS_DataWriterListener_proxy () = default;

    void on_offered_deadline_missed (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::OfferedDeadlineMissedStatus & status) override;

    void on_offered_incompatible_qos (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::OfferedIncompatibleQosStatus & status) override;

    void on_liveliness_lost (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::LivelinessLostStatus & status) override;

    void on_publication_matched (
      DDS_Native::DDS::DataWriter *the_writer,
      const DDS_Native::DDS::PublicationMatchedStatus & status) override;

    IDL::traits< ::DDS::DataWriterListener>::ref_type
    get_datawriterlistener ();

  private:
    IDL::traits< ::DDS::DataWriterListener>::ref_type impl_;

    // In order to gain performance, we keep a weak_ref_pointer to the data
    // writer. This pointer will be set the first time a callback from DDS
    // comes in. The pointer will be converted to a strong reference and
    // checked on each callback. This prevents looking up the internal map
    // in the ProxyEntityManager each time a callback is called.
    IDL::traits< ::DDS::DataWriter>::weak_ref_type dw_ {};

    IDL::traits< ::DDS::DataWriter>::ref_type
    get_datawriter (DDS_Native::DDS::DataWriter *the_writer);

    DDS_DataWriterListener_proxy() = delete;
    DDS_DataWriterListener_proxy(const DDS_DataWriterListener_proxy&) = delete;
    DDS_DataWriterListener_proxy(DDS_DataWriterListener_proxy&&) = delete;
    DDS_DataWriterListener_proxy& operator=(const DDS_DataWriterListener_proxy&) = delete;
    DDS_DataWriterListener_proxy& operator=(DDS_DataWriterListener_proxy&&) = delete;
  };

  typedef DDSX11_Listener_Guard_T<
    DDS_Native::DDS::DataWriterListener,
    ::DDS::DataWriterListener> DataWriterListener_Guard;

  typedef entity_traits< ::DDS::DataWriterListener, DDS_DataWriterListener_proxy, DDS_Native::DDS::DataWriterListener>
    datawriterlistener_trait;
}

#endif /* DDSX11_IMPL_DATA_WRITER_LISTENER_H_ */
