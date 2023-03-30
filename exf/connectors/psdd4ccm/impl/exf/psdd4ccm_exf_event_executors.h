// -*- C++ -*-
/**
 * @file    psdd4ccm_exf_event_executors.h
 * @author  Martin Corino
 *
 * @brief   Implements the event handling strategies for ExF for PSDD4CCM
 *
 *          The class members (listener) are passed
 *          as weak references. We don't want to influence the life cycle of
 *          entities here.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_EXF_EVENT_EXECUTORS_H_
#define PSDD4CCM_EXF_EVENT_EXECUTORS_H_

#include "exf/deployment/core/ciaox11_schedule.h"
#include "psdd4ccm/logger/psdd4ccm_log.h"
#include "psdd4ccm/idl/ccm_psddC.h"

namespace CIAOX11
{
  namespace PSDD4CCM
  {
    namespace ExF
    {
      using namespace CIAOX11::ExF;

      template <typename LISTENER, typename HANDLER>
      class PSDDDataListenerExecutor
        : public ExF::Executor
      {
      public:
        PSDDDataListenerExecutor (
            ExF::Priority prio,
            ExF::Deadline dltm,
            typename IDL::traits<HANDLER>::ref_type dh,
            typename IDL::traits<LISTENER>::weak_ref_type dl)
          : Executor (prio, dltm)
          , dh_ (dh.weak_reference ())
          , dl_ (std::move (dl))
        {}
        ~PSDDDataListenerExecutor () override = default;

        void execute () noexcept(true) override
        {
          try
          {
            this->execute_i (this->dh_.lock (), this->dl_.lock ());
          }
          catch (const std::exception& ex)
          {
            PSDD4CCM_LOG_ERROR (
                "ExF::PSDDDataListenerExecutor<LISTENER, HANDLER>::execute " <<
                "caught exception [" << ex << "] for event_id: " <<
                this->event_id ());
          }
          catch (...)
          {
            PSDD4CCM_LOG_ERROR (
                "ExF::PSDDDataListenerExecutor<LISTENER, HANDLER>::execute " <<
                "caught unknown C++ exception for event_id: " <<
                this->event_id ());
          }
        }

        void finish () noexcept(true) override {}

        void cancel (ExF::CancellationType ctyp) noexcept(true) override
        {
          if (ctyp == CIAOX11::ExF::CancellationType::CT_SHUTDOWN)
            PSDD4CCM_LOG_INFO (
                "ExF::PSDDDataListenerExecutor<LISTENER, HANDLER>::cancel received " <<
                "CT_SHUTDOWN" << " for event_id: " << this->event_id ());
          else
            PSDD4CCM_LOG_INFO (
                "ExF::PSDDDataListenerExecutor<LISTENER, HANDLER>::cancel received " <<
                "CT_TIMEOUT" << " for event_id: " << this->event_id ());
        }

        const std::string& event_id () const noexcept(true) override
        {
          static std::string __event_id { "data_available" };
          return __event_id;
        }

      protected:
        void execute_i (typename IDL::traits<HANDLER>::ref_type dh, typename IDL::traits<LISTENER>::ref_type dl)
        {
          if (dh && dl)
          {
            dh->dispatch_data_available (std::move(dl));
          }
          else
          {
            PSDD4CCM_LOG_WARNING (
                "ExF::PSDDDataListenerExecutor<LISTENER, HANDLER>::execute_i - "
                "No PSDD Listener or CCM Listener implementation found (dh=" <<
                (dh ? "true" : "false") << " dl=" << (dl ? "true" : "false") << ").");
          }
        }

      private:
        /// The weak reference to the data reader listener.
        typename IDL::traits<HANDLER>::weak_ref_type dh_;
        typename IDL::traits<LISTENER>::weak_ref_type dl_ {};
      };
    }
  }
}


#endif /* PSDD4CCM_EXF_EVENT_EXECUTORS_H_ */
