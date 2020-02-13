// -*- C++ -*-
/**
 * @file    dds4ccm_getter_t.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM getter
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_GETTER_T_H_
#define DDS4CCM_GETTER_T_H_

#include "dds4ccm/impl/dds4ccm_conf.h"
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    /**
    * @class Getter_Base_T<GETTER_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>
    *
    * @brief Templated base class for the Getter port.
    *
    *        Spec:  Get operations are performed with the following parameters
    *                . SampleStateMask: NO_READ,
    *                . ViewStateMask: NEW or NOT_NEW,
    *                . InstanceStateMask: ALIVE or NOT_ALIVE,
    *                . Through the query (if any) of the Reader associated to the port,
    *                . Within the time limit specified in time_out.
    *
    *               All methods return a boolean as result indicating whether actual data
    *               is provided (TRUE) or if the time-out occurred (FALSE).
    */
    template <typename GETTER_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
    class Getter_T
      : public virtual FacetBase< GETTER_TYPE >
    {
    public:
      /// Constructor
      explicit Getter_T (IDL::traits<CORBA::Object>::weak_ref_type component);

      /// Destructor
      virtual ~Getter_T () = default;

      /**
        *  Spec : get_many returns all the available samples
        *         in the limits set by the attribute max_delivered_data.
        *         In case there are more available samples, the first
        *         max_delivered_data are returned. The default value for
        *         that attribute is UNLIMITED (0)
        */
      virtual bool
      get_many (
        TOPIC_SEQ_TYPE& instances,
        ::CCM_DDS::ReadInfoSeq& infos) override;

      /**
      *
      * @brief  get_one implementation.
      *
      *         Spec : get_one returns the next sample to be gotten.
      *
      * @retval false When 'wait' times out or when no valid data could be read
      * from DDS.
      * @retval true When 'wait' is triggered.
      */
      virtual bool
      get_one (
        TOPIC_TYPE &an_instance,
        ::CCM_DDS::ReadInfo &info) override;

      /**
        * @name time_out
        * Accessors for time_out
        */
      //@{
      virtual ::DDS::Duration_t time_out () override;
      virtual void time_out (const ::DDS::Duration_t & time_out) override;
      //@}

      /**
        * @name max_delivered_data
        * Accessors for max_delivered_data
        */
      //@{
      virtual ::CCM_DDS::DataNumber_t
      max_delivered_data () override;

      virtual void
      max_delivered_data (
        ::CCM_DDS::DataNumber_t max_delivered_data) override;
      //@}

      /**
        * Set the actual ref_type of the DDS Datareader
        */
      void
      set_dds_reader (
        IDL::traits< ::DDS::DataReader>::ref_type reader,
        SharedConditionManager condition_manager);

      IDL::traits< ::DDS::DataReader>::ref_type
      get_dds_reader ();

    private:
      typename ::DDS::traits<TOPIC_TYPE>::typed_datareader_ref_type dds_reader_ {};

      SharedConditionManager condition_manager_ {};

      ::DDS::Duration_t time_out_ {};
      ::CCM_DDS::DataNumber_t max_delivered_data_ {};

      /**
        * @name get
        *
        * Generic helper methods which perform the actual
        * DDS reading.
        */
      //@{
      ::DDS::ReturnCode_t
      get (
        TOPIC_SEQ_TYPE& data,
        ::DDS::SampleInfoSeq & sample_info,
        uint32_t max_samples);

      ::DDS::ReturnCode_t
      get (
        TOPIC_SEQ_TYPE& data,
        ::DDS::SampleInfoSeq & sample_info,
        uint32_t max_samples,
        IDL::traits< ::DDS::QueryCondition>::ref_type qc);

      ::DDS::ReturnCode_t
      get (
        TOPIC_SEQ_TYPE & data,
        ::DDS::SampleInfoSeq & sample_info,
        uint32_t max_samples,
        IDL::traits< ::DDS::ReadCondition>::ref_type rd);
      //@}

      Getter_T() = delete;
      Getter_T(const Getter_T&) = delete;
      Getter_T(Getter_T&&) = delete;
      Getter_T& operator=(const Getter_T&) = delete;
      Getter_T& operator=(Getter_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_getter_t.cpp"

#endif /* DDS4CCM_GETTER_T_H_ */
