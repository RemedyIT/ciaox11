/**
 * @file    ciaox11_exf_container.h
 * @author  Martin Corino
 *
 * @brief   Header file for CIAOX11 ExF container implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_EXF_CONTAINER_H
#define CIAOX11_EXF_CONTAINER_H

#pragma once

#include "exf/deployment/core/ciaox11_schedule.h"
#include "ciaox11/deployment/handlers/ciaox11_container_i.h"
#include "exf/deployment/handlers/ciaox11_exf_handler_export.h"

namespace CIAOX11
{
  namespace ExF
  {
    class CIAOX11_EXF_HANDLER_Export Container final
      : public CIAOX11::Container_i
    {
    public:
      Container (std::string name,
                 IDL::traits<CORBA::ORB>::ref_type orb,
                 ExF::Scheduler::ref_type sched);
      ~Container () override;

      void fini () override;

      ExF::Scheduler::ref_type
      the_scheduler () {  return this->scheduler_; }

      /// @copydoc CIAOX11::Container::uninstall_component
      bool uninstall_component (const std::string& name) override;

      /// @copydoc CIAOX11::Container::activate_component
      bool activate_component (const std::string& name) override;

      /// @copydoc CIAOX11::Container::passivate_component
      bool passivate_component (const std::string& name) override;

      /// @copydoc CIAOX11::Container::configured_component
      bool configured_component (const std::string& name) override;

    private:

      IDL::traits<ExF::SchedulingLane>::ref_type find_lane (const std::string&);

      /// excution scheduler
      ExF::Scheduler::ref_type scheduler_;

      Container () = delete;
      Container (const Container&) = delete;
      Container (Container&&) = delete;
      Container& operator= (const Container&) = delete;
      Container& operator= (Container&&) = delete;
    };
  }
}

#endif /* CIAOX11_EXF_CONTAINER_I_H */
