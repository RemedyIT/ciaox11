// -*- C++ -*-
/**
 * @file    psdd4ccm_context_switch_handlers_t.h
 * @author  Martin Corino
 *
 * @brief   Provides the context switch between PSDD middleware and PSDD4CCM
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_CONTEXT_SWITCH_HANDLERS_T_H_
#define PSDD4CCM_CONTEXT_SWITCH_HANDLERS_T_H_

#include "psdd4ccm/idl/ccm_psddC.h"

#include "ace/Event_Handler.h"

namespace CIAOX11
{
  namespace PSDD4CCM
  {
    template <typename LISTENER, typename HANDLER>
    class DataListenerContextSwitch_T
      : public ACE_Event_Handler
    {
    public:
      explicit DataListenerContextSwitch_T (
        typename IDL::traits<HANDLER>::ref_type dh,
        typename IDL::traits<LISTENER>::weak_ref_type dl);
      virtual ~DataListenerContextSwitch_T () = default;

      int handle_exception (ACE_HANDLE fc = ACE_INVALID_HANDLE) override;

      static void handle_event (
          typename IDL::traits<HANDLER>::ref_type dh,
          typename IDL::traits<LISTENER>::ref_type dl);

    private:
      /// The weak reference to the data reader listener.
      typename IDL::traits<HANDLER>::weak_ref_type dh_;

      typename IDL::traits<LISTENER>::weak_ref_type dl_;

      DataListenerContextSwitch_T() = delete;
      DataListenerContextSwitch_T(const DataListenerContextSwitch_T&) = delete;
      DataListenerContextSwitch_T(DataListenerContextSwitch_T&&) = delete;
      DataListenerContextSwitch_T& operator=(const DataListenerContextSwitch_T&) = delete;
      DataListenerContextSwitch_T& operator=(DataListenerContextSwitch_T&&) = delete;
    };
  }
}

#include "psdd4ccm/impl/psdd4ccm_context_switch_handlers_t.cpp"

#endif /* PSDD4CCM_CONTEXT_SWITCH_HANDLERS_T_H_ */
