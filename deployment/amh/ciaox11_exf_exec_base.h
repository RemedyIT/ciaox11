/**
 * @file   ciaox11_exf_exec_base.h
 * @author Martin Corino
 *
 * @brief Base class for ExF based AMH specific executors.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef CIAOX11_EXF_AMH_EXEC_BASE_H
#define CIAOX11_EXF_AMH_EXEC_BASE_H

#include "exf/deployment/amh/ciaox11_exf_amh_base.h"
#include "exf/deployment/core/ciaox11_schedule.h"

// X11_FUZZ: disable check_taox11_namespaces

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class CIAOX11_EXF_AMH_Export AMH_Executor
        : public ExF::Executor
      {
      public:
        AMH_Executor (ExF::Priority prio, ExF::Deadline dltm)
          : Executor (prio, dltm) {}
        virtual ~AMH_Executor () = default;

        void execute () noexcept(true) override;

        void finish () noexcept(true) override;

        void cancel (CIAOX11::ExF::CancellationType ctyp) noexcept(true) override;

      protected:
        virtual void execute_i () = 0;

        virtual void finish_i () = 0;

        virtual void send_exception_i (const CORBA::Exception& ex) = 0;

      private:
        bool finished_ {};
      };
    }
  }
}

// X11_FUZZ: enable check_taox11_namespaces

#endif
