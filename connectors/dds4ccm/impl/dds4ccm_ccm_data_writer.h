// -*- C++ -*-
/**
 * @file    dds4ccm_ccm_data_writer.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for the DataWriter
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_CCM_DATA_WRITER_H_
#define DDS4CCM_CCM_DATA_WRITER_H_

#include "dds_dcpsEC.h"
#include "dds4ccm/impl/dds4ccm_impl_export.h"
#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    /**
     * DataWriter implementation which is the proxy to DDSX11 at the moment
     * the user code directly wants to use DDS
     */
    class DDS4CCM_IMPL_Export CCM_DataWriter
      : public virtual FacetBase< ::DDS::CCM_DataWriter>
    {
    public:
      /// Constructor
      explicit CCM_DataWriter (IDL::traits<CORBA::Object>::weak_ref_type component);

      /// Destructor
      ~CCM_DataWriter () override = default;

      ::DDS::ReturnCode_t enable () override;

      IDL::traits<::DDS::StatusCondition>::ref_type get_statuscondition () override;

      ::DDS::StatusMask get_status_changes () override;

      ::DDS::InstanceHandle_t get_instance_handle () override;

      ::DDS::ReturnCode_t set_qos (const ::DDS::DataWriterQos &qos) override;

      ::DDS::ReturnCode_t get_qos (::DDS::DataWriterQos &qos) override;

      ::DDS::ReturnCode_t
      set_listener (
        IDL::traits<::DDS::DataWriterListener>::ref_type listener,
        ::DDS::StatusMask mask) override;

      IDL::traits<::DDS::DataWriterListener>::ref_type get_listener () override;

      IDL::traits<::DDS::Topic>::ref_type get_topic () override;

      IDL::traits<::DDS::Publisher>::ref_type get_publisher () override;

      ::DDS::ReturnCode_t wait_for_acknowledgments (const ::DDS::Duration_t &duration) override;

      ::DDS::ReturnCode_t
      get_liveliness_lost_status (::DDS::LivelinessLostStatus &status) override;

      ::DDS::ReturnCode_t
      get_offered_deadline_missed_status (::DDS::OfferedDeadlineMissedStatus &status) override;

      ::DDS::ReturnCode_t
      get_offered_incompatible_qos_status (::DDS::OfferedIncompatibleQosStatus &status) override;

      ::DDS::ReturnCode_t
      get_publication_matched_status (::DDS::PublicationMatchedStatus &status) override;

      ::DDS::ReturnCode_t assert_liveliness () override;

      ::DDS::ReturnCode_t
      get_matched_subscriptions (::DDS::InstanceHandleSeq &seq) override;

      ::DDS::ReturnCode_t
      get_matched_subscription_data (
        ::DDS::SubscriptionBuiltinTopicData &data,
        const ::DDS::InstanceHandle_t &handle) override;

      void set_dds_entity (IDL::traits<::DDS::DataWriter>::ref_type dw);

      IDL::traits<::DDS::DataWriter>::ref_type get_dds_entity ();

    private:
      IDL::traits<::DDS::DataWriter>::ref_type dds_entity_;

      CCM_DataWriter() = delete;
      CCM_DataWriter(const CCM_DataWriter&) = delete;
      CCM_DataWriter(CCM_DataWriter&&) = delete;
      CCM_DataWriter& operator=(const CCM_DataWriter&) = delete;
      CCM_DataWriter& operator=(CCM_DataWriter&&) = delete;
    };
  }
}

#endif /* DDS4CCM_CCM_DATA_WRITER_H_ */
