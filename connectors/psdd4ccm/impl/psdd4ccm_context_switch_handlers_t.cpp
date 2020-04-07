// -*- C++ -*-
/**
 * @file    psdd4ccm_context_switch_handlers_t.cpp
 * @author  Martin Corino
 *
 * @brief   Provides the context switch between PSDD middleware and PSDD4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "psdd4ccm/logger/psdd4ccm_log.h"

namespace CIAOX11
{
  namespace PSDD4CCM
  {
    template <typename LISTENER, typename HANDLER>
    DataListenerContextSwitch_T<LISTENER, HANDLER>::DataListenerContextSwitch_T (
      typename IDL::traits<HANDLER>::ref_type dh,
      typename IDL::traits<LISTENER>::weak_ref_type dl)
      : dh_ (dh.weak_reference ())
      , dl_ (dl)
    {
      this->reference_counting_policy ().value (
        ACE_Event_Handler::Reference_Counting_Policy::ENABLED);
    }

    template <typename LISTENER, typename HANDLER>
    int
    DataListenerContextSwitch_T<LISTENER, HANDLER>::handle_exception (ACE_HANDLE)
    {
      handle_event (this->dh_.lock (), this->dl_.lock ());
      return 0;
    }

    template <typename LISTENER, typename HANDLER>
    void
    DataListenerContextSwitch_T<LISTENER, HANDLER>::handle_event (
        typename IDL::traits<HANDLER>::ref_type dh,
        typename IDL::traits<LISTENER>::ref_type dl)
    {
      try
      {
        if (dh && dl)
        {
          dh->dispatch_data_available (dl);
        }
        else
        {
          PSDD4CCM_LOG_WARNING ("DataListenerContextSwitch_T<LISTENER, HANDLER>::handle_event - "
            "No PSDD Listener or CCM Listener implementation found (dh=" <<
            (dh ? "1" : "0") << " dl=" << (dl ? "1" : "0") << ").");
        }
      }
      catch (const CORBA::Exception &ex)
      {
        PSDD4CCM_LOG_ERROR ("DataListenerContextSwitch_T<LISTENER, HANDLER>::handle_event" << " - "
          << "ERROR: Caught unexpected CORBA exception: " << ex);
      }
      catch (const std::exception &ex)
      {
        PSDD4CCM_LOG_ERROR ("DataListenerContextSwitch_T<LISTENER, HANDLER>::handle_event" << " - "
          << "ERROR: Caught unexpected std exception: " << ex.what ());
      }
      catch (...)
      {
        PSDD4CCM_LOG_ERROR ("DataListenerContextSwitch_T<LISTENER, HANDLER>::handle_event" << " - "
          << "ERROR: Caught unexpected exception");
      }
    }
  }
}
