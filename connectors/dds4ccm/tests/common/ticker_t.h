// -*- C++ -*-
/**
 * @file    ticker_t.h
 * @author  Marcel Smit
 *
 * @brief   Base class for a ticker within the dds4ccm tests.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef TICKER_H_
#define TICKER_H_

#include "ace/Event_Handler.h"
#include "dds4ccm/logger/dds4ccm_testlog.h"

namespace DDS4CCM_TEST_UTILS
{
  /**
   * One-time timer
   */
  template<typename EXECUTOR, typename EXECUTOR_I>
  class ContextSwitch
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit ContextSwitch (EXECUTOR component_executor)
      : component_executor_ (std::move(component_executor))
    {
    }

    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type,
        const ::CCM_TT::TT_Duration&,
        uint32_t) override
    {
      auto cex = IDL::traits<EXECUTOR_I>::narrow (this->component_executor_.lock ());
      if (cex)
      {
        cex->notify ();
      }
      else
      {
        DDS4CCM_TEST_ERROR << "ContextSwitch::on_trigger - "
          "ERROR: failed to lock component executor" << std::endl;
      }
    }

  private:
    EXECUTOR component_executor_;
  };
}

#endif /* TICKER_H_ */
