/**
 * @file   ciaox11_exf_exec_base.cpp
 * @author Martin Corino
 *
 * @brief Base class for ExF based AMH specific executors.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "exf/deployment/amh/ciaox11_exf_exec_base.h"

// X11_FUZZ: disable check_taox11_namespaces

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      void
      AMH_Executor::execute () noexcept(true)
      {
        try
        {
          this->execute_i ();
        }
        catch (const CORBA::Exception& ex)
        {
          this->finished_ = true;
          this->send_exception_i (ex);
        }
        catch (...)
        {
          this->finished_ = true;
          this->send_exception_i (CORBA::INTERNAL ());
        }
      }

      void
      AMH_Executor::finish () noexcept(true)
      {
        if (!this->finished_)
        {
          this->finished_ = true;
          try
          {
            this->finish_i ();
          }
          catch (const CORBA::Exception& ex)
          {
            this->send_exception_i (ex);
          }
          catch (...)
          {
            this->send_exception_i (CORBA::INTERNAL ());
          }
        }
      }

      void
      AMH_Executor::cancel (CIAOX11::ExF::CancellationType ctyp) noexcept(true)
      {
        if (!this->finished_)
        {
          this->finished_ = true;
          if (ctyp == CIAOX11::ExF::CancellationType::CT_SHUTDOWN)
            this->send_exception_i (CORBA::THREAD_CANCELLED ());
          else
            this->send_exception_i (CORBA::TIMEOUT ());
        }
      }
    }
  }
}

// X11_FUZZ: enable check_taox11_namespaces
