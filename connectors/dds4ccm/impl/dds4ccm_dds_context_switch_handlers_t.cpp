// -*- C++ -*-
/**
 * @file    dds4ccm_dds_context_switch_handlers_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Provides the context switch between DDS and DDS4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds4ccm/impl/dds4ccm_utils.h"
#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template <typename LISTENER, typename DATA_LISTENER>
    DataReaderContextSwitch_T<LISTENER, DATA_LISTENER>::DataReaderContextSwitch_T (
      typename IDL::traits< LISTENER>::ref_type drl,
      IDL::traits< ::DDS::DataReader>::ref_type dr,
      typename IDL::traits<DATA_LISTENER>::weak_ref_type dl)
      : drl_ (drl.weak_reference ())
      , dr_ (dr.weak_reference ())
      , dl_ (std::move(dl))
    {
      this->reference_counting_policy ().value (
        ACE_Event_Handler::Reference_Counting_Policy::ENABLED);
    }

    template <typename LISTENER, typename DATA_LISTENER>
    int
    DataReaderContextSwitch_T<LISTENER, DATA_LISTENER>::handle_exception (ACE_HANDLE)
    {
      handle_event (this->drl_.lock (), this->dr_.lock (), this->dl_.lock ());
      return 0;
    }

    template <typename LISTENER, typename DATA_LISTENER>
    void
    DataReaderContextSwitch_T<LISTENER, DATA_LISTENER>::handle_event (
        typename IDL::traits< LISTENER>::ref_type drl,
        IDL::traits< ::DDS::DataReader>::ref_type dr,
        typename IDL::traits<DATA_LISTENER>::ref_type dl)
    {
      try
      {
        if (drl && dl)
        {
          drl->on_data_available_i (std::move(dr), std::move(dl));
        }
        else
        {
          DDS4CCM_LOG_WARNING ("DataReaderContextSwitch_T<LISTENER>::handle_event - "
            "No DataReaderListener or user Listener implementation found.");
        }
      }
      catch_dds4ccm_listener_ex(ex, "DataReaderContextSwitch_T<LISTENER>::handle_event")
    }
  }
}
