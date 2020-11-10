// -*- C++ -*-
/**
 * @file    dds4ccm_dds_context_switch_handlers_t.h
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_CONTEXT_SWITCH_HANDLERS_T_H_
#define DDS4CCM_CONTEXT_SWITCH_HANDLERS_T_H_

#include "dds4ccm/idl/dds_rtf2_dcpsC.h"
#include "ace/Event_Handler.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename LISTENER, typename DATA_LISTENER>
    class DataReaderContextSwitch_T
      : public ACE_Event_Handler
    {
    public:
      explicit DataReaderContextSwitch_T (
        typename IDL::traits<LISTENER>::ref_type drl,
        IDL::traits< ::DDS::DataReader>::ref_type dr,
        typename IDL::traits<DATA_LISTENER>::weak_ref_type dl);
      virtual ~DataReaderContextSwitch_T () = default;

      int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE) override;

      static void handle_event (
        typename IDL::traits<LISTENER>::ref_type drl,
        IDL::traits< ::DDS::DataReader>::ref_type dr,
        typename IDL::traits<DATA_LISTENER>::ref_type dl);

    private:
      /// The weak reference to the data reader listener.
      typename IDL::traits<LISTENER>::weak_ref_type drl_;
      /// All strong references are managed in the DDS proxy. We therefor need
      /// to use a weak_ref_type here otherwise we would extend the lifecycle
      /// of the DataReader here
      IDL::traits< ::DDS::DataReader>::weak_ref_type dr_;

      typename IDL::traits<DATA_LISTENER>::weak_ref_type dl_;

      DataReaderContextSwitch_T() = delete;
      DataReaderContextSwitch_T(const DataReaderContextSwitch_T&) = delete;
      DataReaderContextSwitch_T(DataReaderContextSwitch_T&&) = delete;
      DataReaderContextSwitch_T& operator=(const DataReaderContextSwitch_T&) = delete;
      DataReaderContextSwitch_T& operator=(DataReaderContextSwitch_T&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_dds_context_switch_handlers_t.cpp"

#endif /* DDS4CCM_CONTEXT_SWITCH_HANDLERS_T_H_ */
