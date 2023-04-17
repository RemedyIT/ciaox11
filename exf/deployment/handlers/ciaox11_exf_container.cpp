/**
 * @file    ciaox11_exf_container.cpp
 * @author  Martin Corino
 *
 * @brief Implementation file for CIAOX11 ExF container implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/handlers/ciaox11_exf_container.h"

#include "ccm/session/ccm_sessioncomponentC.h"
#include "ciaox11/logger/log.h"
#include "ace/Thread_Mutex.h"
#include "ace/Condition_Thread_Mutex.h"
#include "ace/Guard_T.h"

namespace CIAOX11
{
  namespace ExF
  {
    struct LifecycleSemaphore
    {
      LifecycleSemaphore ()
        : condition_ (mutex_) {}

      ACE_Thread_Mutex mutex_ {};
      ACE_Condition_Thread_Mutex condition_;
      bool cancelled_ {};
      bool completed_ {};

      void signal_completion (bool cancelled) noexcept(true);

      void wait_for_completion () noexcept(true);
    };

    class LifecycleExecutor
      : public Executor
    {
    public:
      LifecycleExecutor (std::shared_ptr<LifecycleSemaphore> sem)
       : sem_ (std::move(sem)) {}
      LifecycleExecutor (std::shared_ptr<LifecycleSemaphore> sem, ExF::Settings settings)
       : Executor (std::move(settings)), sem_ (std::move(sem)) {}
      ~LifecycleExecutor () override = default;

      void execute () noexcept(true) override;

      void finish () noexcept(true) override
      { this->signal_completion (); }

      void cancel (CancellationType) noexcept(true) override
      { this->signal_completion (true); }

    protected:
      void signal_completion (bool cancelled = false) noexcept(true)
      { this->sem_->signal_completion (cancelled); }

      virtual void do_lifecycle_call () = 0;

    private:
      std::shared_ptr<LifecycleSemaphore> sem_;
    };

    void
    LifecycleSemaphore::signal_completion (bool cancelled) noexcept(true)
    {
      // no need to lock if already done
      // (in case of cancellation before execution finished)
      if (this->completed_)
        return;

      try
      {
        // make sure the mutex is locked before entering wait()
        ACE_GUARD (ACE_Thread_Mutex, __guard, this->mutex_);

        // check again if we're already done
        if (this->completed_)
          return;

        CIAOX11_LOG_DEBUG ("LifecycleSemaphore::signal_complete - " <<
                           "signaling completion");

        this->cancelled_ = cancelled;
        this->completed_ = true;

        // wait for completion signal
        this->condition_.signal ();
      }
      catch (...)
      {
        CIAOX11_LOG_CRITICAL ("ExF::LifecycleSemaphore::signal_complete - " <<
                              "Unexpected exception while signalling completion");
      }
    }

    void
    LifecycleSemaphore::wait_for_completion () noexcept(true)
    {
      // no need to lock if already done
      if (this->completed_)
        return;

      try
      {
        // make sure the mutex is locked before entering wait()
        ACE_GUARD (ACE_Thread_Mutex, __guard, this->mutex_);

        // check again if we're already done
        if (this->completed_)
          return;

        CIAOX11_LOG_DEBUG ("LifecycleSemaphore::wait_for_completion - " <<
                           "waiting for signal");

        // wait for completion signal
        this->condition_.wait ();
      }
      catch (...)
      {
        CIAOX11_LOG_CRITICAL ("ExF::LifecycleSemaphore::wait_for_completion - " <<
                              "Unexpected exception while waiting");
      }
    }

    void
    LifecycleExecutor::execute () noexcept(true)
    {
      try
      {
        this->do_lifecycle_call ();
      }
      catch (const CORBA::Exception& ex)
      {
        CIAOX11_LOG_CRITICAL ("ExF::UninstallExecutor::execute - "\
                              "Unexpected CORBA::Exception executing "
                              << this->event_id () << ": " << ex);
      }
      catch (const std::exception& ex)
      {
        CIAOX11_LOG_CRITICAL ("ExF::UninstallExecutor::execute - "\
                              "Unexpected c++ exception executing "
                              << this->event_id () << ": " << ex.what ());
      }
      catch (...)
      {
        CIAOX11_LOG_CRITICAL ("ExF::UninstallExecutor::execute - "\
                              "Unexpected exception executing "
                              << this->event_id ());
      }
      this->signal_completion ();
    }

    class UninstallExecutor
      : public LifecycleExecutor
    {
    public:
      UninstallExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se)
        : LifecycleExecutor (std::move(sem)), session_exec_ (std::move(se)) {}
      UninstallExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se,
          ExF::Settings settings)
        : LifecycleExecutor (std::move(sem), std::move(settings)),
          session_exec_ (std::move(se)) {}

      const std::string& event_id () const noexcept(true) override
      { return event_id_; }

    protected:
      void do_lifecycle_call () override
      { this->session_exec_->ccm_remove (); }

    private:
      IDL::traits<Components::SessionComponent>::ref_type session_exec_;

      static const std::string event_id_;
    };

    const std::string UninstallExecutor::event_id_ = "ccm_remove";

    class ActivationExecutor
      : public LifecycleExecutor
    {
    public:
      ActivationExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se)
        : LifecycleExecutor (sem), session_exec_ (se) {}
      ActivationExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se,
          ExF::Settings settings)
        : LifecycleExecutor (std::move(sem), std::move(settings)),
          session_exec_ (std::move(se)) {}

      const std::string& event_id () const noexcept(true) override
      { return event_id_; }

    protected:
      void do_lifecycle_call () override
      { this->session_exec_->ccm_activate (); }

    private:
      IDL::traits<Components::SessionComponent>::ref_type session_exec_;

      static const std::string event_id_;
    };

    const std::string ActivationExecutor::event_id_ = "ccm_activate";

    class PassivationExecutor
      : public LifecycleExecutor
    {
    public:
      PassivationExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se)
        : LifecycleExecutor (std::move(sem)), session_exec_ (std::move(se)) {}
      PassivationExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se,
          ExF::Settings settings)
        : LifecycleExecutor (std::move(sem), std::move(settings)),
          session_exec_ (std::move(se)) {}

      const std::string& event_id () const noexcept(true) override
      { return event_id_; }

    protected:
      void do_lifecycle_call () override
      { this->session_exec_->ccm_passivate (); }

    private:
      IDL::traits<Components::SessionComponent>::ref_type session_exec_;

      static const std::string event_id_;
    };

    const std::string PassivationExecutor::event_id_ = "ccm_passivate";

    class ConfiguredExecutor
      : public LifecycleExecutor
    {
    public:
      ConfiguredExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se)
        : LifecycleExecutor (std::move(sem)), session_exec_ (std::move(se)) {}
      ConfiguredExecutor (
          std::shared_ptr<LifecycleSemaphore> sem,
          IDL::traits<Components::SessionComponent>::ref_type se,
          ExF::Settings settings)
        : LifecycleExecutor (std::move(sem), std::move(settings)),
          session_exec_ (std::move(se)) {}

      const std::string& event_id () const noexcept(true) override
      { return event_id_; }

    protected:
      void do_lifecycle_call () override
      { this->session_exec_->configuration_complete (); }

    private:
      IDL::traits<Components::SessionComponent>::ref_type session_exec_;

      static const std::string event_id_;
    };

    const std::string ConfiguredExecutor::event_id_ = "configuration_complete";

    Container::Container (
      std::string name,
      IDL::traits<CORBA::ORB>::ref_type orb,
      ExF::Scheduler::ref_type sched)
      : CIAOX11::Container_i (name, orb),
        scheduler_ (sched)
    {
    }

    void
    Container::fini ()
    {
      this->CIAOX11::Container_i::fini ();
      if (this->scheduler_)
      {
        this->scheduler_->close ();
        this->scheduler_.reset ();
      }
    }

    IDL::traits<ExF::SchedulingLane>::ref_type
    Container::find_lane (const std::string& id)
    {
      if (this->scheduler_)
      {
        IDL::traits<ExF::SchedulingLane>::ref_type lane;
        if (ExF::SchedulerResult::SOK ==
              this->scheduler_->find_scheduling_lane (id, lane))
        {
          return lane;
        }
      }
      return {};
    }

    bool
    Container::uninstall_component (
        const std::string& name)
    {
      CIAOX11_LOG_DEBUG ("ExF::Container::uninstall_component - ");

      // check if component instance has scheduling lane
      IDL::traits<ExF::SchedulingLane>::ref_type lane =
          this->find_lane (name);
      if (lane)
      {
        CIAOX11_LOG_DEBUG ("ExF::Container::uninstall_component - " <<
                           "scheduling execution through lane");

        IDL::traits<CIAOX11::ExecutorLocator>::ref_type comp = this->get_component (name);
        if (comp)
        {
          IDL::traits<CORBA::Object>::ref_type executor = comp->obtain_executor();
          IDL::traits<Components::SessionComponent>::ref_type session_executor =
                IDL::traits<Components::SessionComponent>::narrow (executor);

          if (session_executor)
          {
            try
            {
              // create semaphore
              std::shared_ptr<LifecycleSemaphore> sem =
                  std::make_shared<LifecycleSemaphore> ();
              // create executor
              ExF::Executor::ref_type exec =
                  std::make_unique<ExF::UninstallExecutor> (sem, session_executor);

              CIAOX11_LOG_DEBUG ("ExF::Container::uninstall_component - " <<
                                 "submitting executor");

              // submit to scheduling lane
              lane->submit (std::move (exec));

              CIAOX11_LOG_DEBUG ("ExF::Container::uninstall_component - " <<
                                 "waiting for completion");

              // wait till completed
              sem->wait_for_completion ();

              return !sem->cancelled_;
            }
            catch (const std::bad_alloc&)
            {
              CIAOX11_LOG_ERROR ("ExF::Container::uninstall_component - "\
                                 "Unable to create ExF executor "\
                                 "for <" + name + ">");
            }
          }
          else
          {
            CIAOX11_LOG_ERROR ("ExF::Container::uninstall_component - "\
                               "Unable to retrieve component executor "\
                               "reference for <" + name + ">");
          }
        }
        else
        {
          CIAOX11_LOG_ERROR ("ExF::Container::uninstall_component - "\
                             "Unable to retrieve executor locator "\
                             "reference for <" + name + ">");
        }
      }
      else
      {
        // handle request without scheduler
        return this->CIAOX11::Container_i::uninstall_component (name);
      }
      return false;
    }

    bool
    Container::activate_component (
        const std::string& name)
    {
      CIAOX11_LOG_DEBUG ("ExF::Container::activate_component - ");

      // check if component instance has scheduling lane
      IDL::traits<ExF::SchedulingLane>::ref_type lane =
          this->find_lane (name);
      if (lane)
      {
        CIAOX11_LOG_DEBUG ("ExF::Container::activate_component - " <<
                           "scheduling execution through lane");

        IDL::traits<CIAOX11::ExecutorLocator>::ref_type comp = this->get_component (name);
        if (comp)
        {
          IDL::traits<CORBA::Object>::ref_type executor = comp->obtain_executor();
          IDL::traits<Components::SessionComponent>::ref_type session_executor =
                IDL::traits<Components::SessionComponent>::narrow (executor);

          if (session_executor)
          {
            try
            {
              // create semaphore
              std::shared_ptr<LifecycleSemaphore> sem =
                  std::make_shared<LifecycleSemaphore> ();
              // create executor
              ExF::Executor::ref_type exec =
                  std::make_unique<ExF::ActivationExecutor> (sem, session_executor);

              CIAOX11_LOG_DEBUG ("ExF::Container::activate_component - " <<
                                 "submitting executor");

              // submit to scheduling lane
              lane->submit (std::move (exec));

              CIAOX11_LOG_DEBUG ("ExF::Container::activate_component - " <<
                                 "waiting for completion");

              // wait till completed
              sem->wait_for_completion ();

              return !sem->cancelled_;
            }
            catch (const std::bad_alloc&)
            {
              CIAOX11_LOG_ERROR ("ExF::Container::activate_component - "\
                                 "Unable to create ExF executor "\
                                 "for <" + name + ">");
            }
          }
          else
          {
            CIAOX11_LOG_ERROR ("ExF::Container::activate_component - "\
                               "Unable to retrieve component executor "\
                               "reference for <" + name + ">");
          }
        }
        else
        {
          CIAOX11_LOG_ERROR ("ExF::Container::activate_component - "\
                             "Unable to retrieve executor locator "\
                             "reference for <" + name + ">");
        }
      }
      else
      {
        // handle request without scheduler
        return this->CIAOX11::Container_i::activate_component (name);
      }
      return false;
    }

    bool
    Container::passivate_component (
        const std::string& name)
    {
      CIAOX11_LOG_DEBUG ("ExF::Container::passivate_component - ");

      // check if component instance has scheduling lane
      IDL::traits<ExF::SchedulingLane>::ref_type lane =
          this->find_lane (name);
      if (lane)
      {
        CIAOX11_LOG_DEBUG ("ExF::Container::passivate_component - " <<
                           "scheduling execution through lane");

        IDL::traits<CIAOX11::ExecutorLocator>::ref_type comp = this->get_component (name);
        if (comp)
        {
          IDL::traits<CORBA::Object>::ref_type executor = comp->obtain_executor();
          IDL::traits<Components::SessionComponent>::ref_type session_executor =
                IDL::traits<Components::SessionComponent>::narrow (executor);

          if (session_executor)
          {
            try
            {
              // create semaphore
              std::shared_ptr<LifecycleSemaphore> sem =
                  std::make_shared<LifecycleSemaphore> ();
              // create executor
              ExF::Executor::ref_type exec =
                  std::make_unique<ExF::PassivationExecutor> (sem, session_executor);

              CIAOX11_LOG_DEBUG ("ExF::Container::passivate_component - " <<
                                 "submitting executor");

              // submit to scheduling lane
              lane->submit (std::move (exec));

              CIAOX11_LOG_DEBUG ("ExF::Container::passivate_component - " <<
                                 "waiting for completion");

              // wait till completed
              sem->wait_for_completion ();

              return !sem->cancelled_;
            }
            catch (const std::bad_alloc&)
            {
              CIAOX11_LOG_ERROR ("ExF::Container::passivate_component - "\
                                 "Unable to create ExF executor "\
                                 "for <" + name + ">");
            }
          }
          else
          {
            CIAOX11_LOG_ERROR ("ExF::Container::passivate_component - "\
                               "Unable to retrieve component executor "\
                               "reference for <" + name + ">");
          }
        }
        else
        {
          CIAOX11_LOG_ERROR ("ExF::Container::passivate_component - "\
                             "Unable to retrieve executor locator "\
                             "reference for <" + name + ">");
        }
      }
      else
      {
        // handle request without scheduler
        return this->CIAOX11::Container_i::passivate_component (name);
      }
      return false;
    }

    bool
    Container::configured_component (
        const std::string& name)
    {
      CIAOX11_LOG_DEBUG ("ExF::Container::configured_component - ");

      // check if component instance has scheduling lane
      IDL::traits<ExF::SchedulingLane>::ref_type lane =
          this->find_lane (name);
      if (lane)
      {
        CIAOX11_LOG_DEBUG ("ExF::Container::configured_component - " <<
                           "scheduling execution through lane");

        IDL::traits<CIAOX11::ExecutorLocator>::ref_type comp = this->get_component (name);
        if (comp)
        {
          IDL::traits<CORBA::Object>::ref_type executor = comp->obtain_executor();
          IDL::traits<Components::SessionComponent>::ref_type session_executor =
                IDL::traits<Components::SessionComponent>::narrow (executor);

          if (session_executor)
          {
            try
            {
              // create semaphore
              std::shared_ptr<LifecycleSemaphore> sem =
                  std::make_shared<LifecycleSemaphore> ();
              // create executor
              ExF::Executor::ref_type exec =
                  std::make_unique<ExF::ConfiguredExecutor> (sem, session_executor);

              CIAOX11_LOG_DEBUG ("ExF::Container::configured_component - " <<
                                 "submitting executor");

              // submit to scheduling lane
              lane->submit (std::move (exec));

              CIAOX11_LOG_DEBUG ("ExF::Container::configured_component - " <<
                                 "waiting for completion");

              // wait till completed
              sem->wait_for_completion ();

              return !sem->cancelled_;
            }
            catch (const std::bad_alloc&)
            {
              CIAOX11_LOG_ERROR ("ExF::Container::configured_component - "\
                                 "Unable to create ExF executor "\
                                 "for <" + name + ">");
            }
          }
          else
          {
            CIAOX11_LOG_ERROR ("ExF::Container::configured_component - "\
                               "Unable to retrieve component executor "\
                               "reference for <" + name + ">");
          }
        }
        else
        {
          CIAOX11_LOG_ERROR ("ExF::Container::configured_component - "\
                             "Unable to retrieve executor locator "\
                             "reference for <" + name + ">");
        }
      }
      else
      {
        // handle request without scheduler
        return this->CIAOX11::Container_i::configured_component (name);
      }
      return false;
    }
  }
}
