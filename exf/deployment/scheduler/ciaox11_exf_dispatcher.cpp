/**
 * @file   ciaox11_exf_dispatcher.cpp
 * @author Martin Corino
 *
 * @brief AXCIOMA execution scheduler dispatcher implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/scheduler/ciaox11_exf_dispatcher.h"

#include <atomic>
#include "exf/deployment/core/ciaox11_task.h"
#include "exf/deployment/logger/log.h"

// X11_FUZZ: disable check_new_delete

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      uint32_t Dispatcher::DispatchQueue::allocation_block_size = 64;
      uint64_t Dispatcher::DispatchQueue::high_water_mark = 0;
      uint64_t Dispatcher::DispatchQueue::low_water_mark = 16;

      std::chrono::microseconds Dispatcher::dispatcher_dequeue_timeout (10 * 1000 * 1000); // 10 sec
      size_t Dispatcher::max_idle_pool_threads = 2;

      const std::string UNKNOWN_POLICY = "UNKNOWN";

      const std::string&
      thread_policy_id (DispatchThreadPolicy pol)
      {
        switch (pol)
        {
          case DispatchThreadPolicy::DTP_SINGLE: return ExF::SCHEDULER_THREAD_SINGLE;
          case DispatchThreadPolicy::DTP_MULTI: return ExF::SCHEDULER_THREAD_MULTI;
          case DispatchThreadPolicy::DTP_POOL: return ExF::SCHEDULER_THREAD_DYNAMIC;
        }
        return UNKNOWN_POLICY;
      }

      const std::string&
      queue_policy_id (DispatchQueuePolicy pol)
      {
        switch (pol)
        {
          case DispatchQueuePolicy::DQP_FIFO: return ExF::SCHEDULER_QUEUE_FIFO;
          case DispatchQueuePolicy::DQP_LIFO: return ExF::SCHEDULER_QUEUE_LIFO;
        }
        return UNKNOWN_POLICY;
      }

      void
      Dispatcher::DispatchTask::expire () noexcept(true)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchTask::expire");

        this->cancel (true);
      }

      const ExF::Deadline&
      Dispatcher::DispatchTask::deadline () const noexcept(true)
      {
        return this->absolute_dead_line_;
      }

      void
      Dispatcher::DispatchTask::cancel (bool expired) noexcept(true)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchTask::cancel");

        // mark the task as being processed
        // (might already be by execution).
        this->processing_.exchange (true);

        // at the moment the executor has already been
        // processed we do nothing
        if (!this->processed_.exchange (true))
        {
          // otherwise we are going to cancel the operation after
          // reporting any deadline expiration

          if (expired)
          {
            switch (this->deadline ().deadline_type_)
            {
              case ExF::DeadlineType::DLT_HARD:
              {
                CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Dispatcher::cancel - " <<
                                   "cancelling expired task " <<
                                   this->instance_id () <<
                                   "::" << this->event_id ());
              }
              break;
              case ExF::DeadlineType::DLT_SOFT:
              {
                CIAOX11_EXF_LOG_WARNING ("ExF::Impl::Dispatcher::cancel - " <<
                                     "cancelling expired task " <<
                                     this->instance_id () <<
                                     "::" << this->event_id ());
              }
              break;
              case ExF::DeadlineType::DLT_EXPIRE:
              {
                CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::cancel - " <<
                                  "cancelling expired task " <<
                                  this->instance_id () <<
                                  "::" << this->event_id ());
              }
              break;
              default:
              {
                CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Dispatcher::cancel - " <<
                                   "cancelling expired NON-DEADLINED task " <<
                                   this->instance_id () <<
                                   "::" << this->event_id ());
              }
              break;
            }
          }
          else
          {
            CIAOX11_EXF_LOG_INFO ("ExF::Impl::DispatchTask::cancel - " <<
                               "cancelling task " << this->instance_id () <<
                               "::" << this->event_id ());
          }

          // cancel executor
          this->executor_->cancel (
              expired ?
                  ExF::CancellationType::CT_TIMEOUT :
                  ExF::CancellationType::CT_SHUTDOWN);
        }
      }

      void
      Dispatcher::DispatchTask::execute () noexcept(true)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchTask::execute");

        // at the moment the executor is already being
        // processed we do nothing
        if (!this->processing_.exchange (true))
        {
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchTask::execute - " <<
                                 "executing task " << this->instance_id () <<
                                 "::" << this->event_id ());

          // execute
          this->executor_->execute ();

          // if the task has been processed (probably expired) before
          // us getting here we do not finish the executor anymore
          if (!this->processed_.exchange (true))
          {
            // finish
            this->executor_->finish ();
          }
        }
      }

      /*===========================================================*/

      Dispatcher::DispatchGate::~DispatchGate ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchGate::~DispatchGate");

        this->close ();
      }

      ExF::Count
      Dispatcher::DispatchGate::queued_count ()
      {
        return ACE_Utils::truncate_cast<ExF::Count> (this->queue_->count ());
      }

      ExF::SchedulerResult
      Dispatcher::DispatchGate::enter (
          ExF::Executor::ref_type&& exec)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchGate::enter - " <<
                               "Scheduling executor for " << this->instance_id ()
                            << " in dispatcher queue.");

        // encapsulate executor as a dispatch task

        try
        {
          // create a dispatch task for the task reference
          // ***NOTE*** moves the exec reference so 'exec' is not valid
          //            anymore after this -> so cache priority here
          ExF::Priority const exec_prio = exec->priority ();
          DispatchTask::task_ref dtask =
              std::make_shared<DispatchTask> (std::move (exec), this->instance_);

          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchGate::enter - " <<
                             "Created task " << dtask.get ()
                             << "::" << dtask->event_id ()
                             << " for " << this->instance_id ()
                             << " with priority " << exec_prio);

          // register task with deadline monitor if required
          if (dtask->deadline ().deadline_type_ != ExF::DeadlineType::DLT_NONE)
          {
            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchGate::enter - " <<
                               "Starting deadline monitoring for task"
                               << this->instance_id () <<
                               "::" << dtask->event_id ());

            this->dispatcher_->monitor ()->start_monitoring (dtask);
          }

          // enqueue task
          if (this->queue_->enqueu (std::move (dtask), exec_prio))
          {
            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::DispatchGate::enter - " <<
                               "Inserted executor task in dispatcher queue.");
          }
          else if (this->queue_->is_shutdown ())
          {
            CIAOX11_EXF_LOG_ERROR ("ExF::Impl::DispatchGate::enter - " <<
                             "Returning SINTERRUPT");
            return ExF::SchedulerResult::SINTERRUPT;
          }
          else
          {
            CIAOX11_EXF_LOG_ERROR ("ExF::Impl::DispatchGate::enter - " <<
                               "Returning SFAILED");
            return ExF::SchedulerResult::SFAILED;
          }
        }
        catch (const std::bad_alloc&)
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::DispatchGate::enter - " <<
                           "Error creating dispatch task. " \
                           "Returning SFAILED");
          return ExF::SchedulerResult::SFAILED;
        }

        return ExF::SchedulerResult::SOK;
      }

      /*===========================================================*/

      Dispatcher::ref_type Dispatcher::create_instance (
          ExF::DeadlineMonitor::ref_type monitor,
          DispatchThreadPolicy dtp,
          DispatchQueuePolicy dqp,
          uint16_t count,
          uint16_t max)
      {
        ref_type disp = ref_type (new Dispatcher (monitor, dtp, dqp, count, max));
        disp->self_ = std::weak_ptr<Dispatcher> (disp);
        return disp;
      }

      Dispatcher::Dispatcher (
          ExF::DeadlineMonitor::ref_type monitor,
          DispatchThreadPolicy dtp,
          DispatchQueuePolicy dqp,
          uint16_t count,
          uint16_t max)
        : dtp_ (dtp)
        , dqp_ (dqp)
        , minsize_ (count > 0 ? count : 1)
        , maxsize_ (max)
        , monitor_ (monitor)
      {
        this->maxsize_ = std::max (this->minsize_, this->maxsize_);
      }

      Dispatcher::~Dispatcher ()
      {
        CIAOX11_EXF_LOG_DEBUG ("Dispatcher::~Dispatcher - ");

        this->close ();
      }

      bool
      Dispatcher::open ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::open");

        std::lock_guard<std::mutex> _q_guard (this->q_lock_);

        CIAOX11_EXF_LOG_INFO("Exf::Impl::Dispatcher::open" <<
                             " - DispatchQueuePolicy=" << ExF::Impl::queue_policy_id (this->dqp_) <<
                             " DispatchThreadPolicy=" << ExF::Impl::thread_policy_id(this->dtp_) <<
                             "  (min threads=" << this->minsize_ << ", max threads=" << this->maxsize_ << ")");

        if (!this->queue_)
        {
          try
          {
            this->queue_ = std::make_shared<task_queue> (this->dqp_);
          }
          catch (const std::bad_alloc&)
          {
            CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Dispatcher::open" <<
                                   " - failed to create queue");
            return false;
          }

          return this->start_i ();
        }

        return true;
      }

      bool
      Dispatcher::close ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::close - ");

        task_queue_ref tmp_taskq;
        std::vector<std::thread> tmp_threads;
        INSTANCE_MAP tmp_instance_map;
        {
          std::lock_guard<std::mutex> _q_ulock (this->q_lock_);

          if (!this->queue_)
            return true;

          if (!this->queue_->is_shutdown ())
            this->queue_->shutdown ();

          tmp_taskq = this->queue_;
          this->queue_.reset ();
          tmp_threads = std::move (this->threads_);
          this->thread_num_ = 0;
          tmp_instance_map = std::move (this->instance_map_);
          this->busy_count_ = 0;
        }

        CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::close - " <<
                            "closing dispatcher");

        CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::stop_i - " \
                           "waiting for " << tmp_threads.size ()
                           << " dispatcher thread(s) to stop");

        for (std::thread& t : tmp_threads)
        {
          t.join ();
        }

        // cleanup and cancel any remaining queued tasks
        task_ref dtask;
        while (!tmp_taskq->empty ())
        {
          if (tmp_taskq->dequeue(dtask, true))
          {
            // cancel this task
            dtask->cancel ();
            dtask.reset();
          }
        }

        return true;
      }

      bool
      Dispatcher::start ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::start");

        std::lock_guard<std::mutex> _q_guard (this->q_lock_);

        if (!this->queue_)
          return false;

        return this->start_i ();
      }

      bool
      Dispatcher::start_i ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::start_i");

        this->queue_->activate ();

        int const start_count = this->dtp_ == DispatchThreadPolicy::DTP_SINGLE ? 1 : this->minsize_;

        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::start_i - " \
                           "starting " << start_count << " dispatcher thread(s)");

        for (int i=0; i<start_count ;++i)
        {
          this->threads_.push_back(std::thread(&Dispatcher::svc, this));
          this->thread_num_++;
        }

        CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::start_i - " <<
                           "started dispatcher (" << start_count << " thread(s))");
        return true;
      }


      bool
      Dispatcher::stop ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::stop");

        std::vector<std::thread> tmp_threads;
        {
          std::lock_guard<std::mutex> _q_ulock (this->q_lock_);

          if (!this->queue_ || this->queue_->is_shutdown ())
            return false;

          this->queue_->shutdown ();
          tmp_threads = std::move (this->threads_);
          this->thread_num_ = 0;
        }

        CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::stop_i - " \
                           "waiting for " << tmp_threads.size ()
                           << " dispatcher thread(s) to stop");

        for (std::thread& t : tmp_threads)
        {
          t.join ();
        }

        return true;
      }

      Dispatcher::gate_ref
      Dispatcher::open_dispatch_gate (
          const std::string& instance_id)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::open_dispatch_gate");

        std::lock_guard<std::mutex> _q_guard (this->q_lock_);

        if (this->queue_)
        {
          CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::open_dispatch_gate - "\
                             "opening dispatcher gate for " << instance_id);


          instance_ref inst {};
          INSTANCE_MAP::iterator it = this->instance_map_.find (instance_id);
          if (it != this->instance_map_.end ())
          {
            if (it->second->closed_)
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::open_dispatch_gate - "\
                                 "reopening dispatcher gate for " << instance_id);
              it->second->closed_ = false;
            }
            else
            {
              // this should not happen
              CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Dispatcher::open_dispatch_gate - "\
                                 "instance " << instance_id << " already registered for gate");
              return {};
            }
            inst = it->second;
          }
          else
          {
            inst = instance_ref (new Instance (instance_id));
            this->instance_map_.insert (INSTANCE_PAIR (instance_id, inst));
          }

          Dispatcher::ref_type self_ref = this->self_.lock ();

          if (self_ref)
          {
            return DispatchGate::ref_type (new DispatchGate (
                      self_ref,
                      inst,
                      this->queue_));
          }

          CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Dispatcher::open_dispatch_gate - "\
                                "failed to lock dispatcher reference for "
                                << instance_id);
        }

        return {};
      }

      void Dispatcher::close_dispatch_gate (
          const DispatchGate& dg)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::close_dispatch_gate");

        std::lock_guard<std::mutex> _q_guard (this->q_lock_);

        CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::close_dispatch_gate - "\
                           "closing dispatcher gate for " << dg.instance_id ());

        INSTANCE_MAP::iterator it = this->instance_map_.find (dg.instance_id ());
        if (it == this->instance_map_.end ())
        {
          // this should not happen
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Dispatcher::close_dispatch_gate - "\
                             "gate for instance " << dg.instance_id () << " already closed");
        }
        else
        {
          // mark as closed
          it->second->closed_ = true;
          // remove instance
          this->instance_map_.erase (it);
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::close_dispatch_gate - "\
                            "gate for " << dg.instance_id () << " closed and removed");
        }
      }

      void Dispatcher::svc ()
      {
        CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::svc - enter");

        task_queue_ref local_thread_taskq_;
        {
          std::lock_guard<std::mutex> _q_guard (this->q_lock_);

          local_thread_taskq_ = this->queue_; // get shared_ptr reference to queue
        }

        bool running = (bool)local_thread_taskq_;

        while (running)
        {
          task_ref dtask;
          if (local_thread_taskq_->dequeue(dtask, dispatcher_dequeue_timeout))
          {
            this->execute_task (dtask, *local_thread_taskq_);
          }
          else
          {
            if (local_thread_taskq_->is_active ())
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::svc - " <<
                                 "idling");

              // nothing to do
              if (this->dtp_ == DispatchThreadPolicy::DTP_POOL)
              {

                // check capacity dynamic thread pool
                CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::svc - " <<
                                   "analyzing dynamic thread pool capacity");

                // if we have at least 2 idle threads and we have more threads running
                // than the pool minimum -> close this one down
                if ((this->busy_count_+max_idle_pool_threads) <= this->thread_num_ &&
                    this->thread_num_ > this->minsize_)
                {
                  std::lock_guard<std::mutex> _q_guard (this->q_lock_);

                  if (local_thread_taskq_->is_active ())
                  {
                    if ((this->busy_count_+max_idle_pool_threads) <= this->thread_num_ &&
                        this->thread_num_ > this->minsize_)
                    {
                      CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::svc - " <<
                                         "shutting down idle pool thread [min="
                                         << this->minsize_ << " max="
                                         << this->maxsize_ << " running="
                                         << this->thread_num_.load () << "busy="
                                         << this->busy_count_.load () << "]");
                      // removed this thread from the list
                      std::vector<std::thread>::iterator trd_it = this->threads_.begin();
                      for (; trd_it != this->threads_.end (); ++trd_it)
                      {
                        if (std::this_thread::get_id() == trd_it->get_id())
                        {
                          this->threads_.erase(trd_it);
                          this->thread_num_--;
                          break;
                        }
                      }
                      running = false; // stop and leave
                    }
                  }
                }
              }
            }
          }

          running &= local_thread_taskq_->is_active ();
        } // while(running)

        CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::svc - leave");
      }

      void Dispatcher::execute_task (task_ref dtask, task_queue& local_thread_taskq)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task -");

        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                           "checking instance state for " <<
                           dtask->instance_id ());

        if (dtask->instance_->closed ())
        {
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                                 "instance " << dtask->instance_id () <<
                                 "was closed; canceling task " << dtask->event_id ());

          dtask->cancel ();

          {
            std::lock_guard<std::mutex> _q_guard (this->q_lock_);

            if (dtask->instance ()->closed_) // not reopened in the meantime?
            {
              CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::execute_task - " \
                                 "cleaning up closed instance");

              // check if this instance still can be removed
              INSTANCE_MAP::iterator it = this->instance_map_.find (dtask->instance_id ());
              if (it == this->instance_map_.end ())
              {
                CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - "\
                                  "closed instance entry already removed: "
                                  << dtask->instance_id ());
              }
              else
              {
                CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - "\
                                  "removing closed instance entry: "
                                  << dtask->instance_id ());
                this->instance_map_.erase (it);
              }
            }
          }
        }
        else
        {
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                                 "calling execute for task " << dtask->instance_id () <<
                                 "::" << dtask->event_id ());

          /* We do not need to check anything here anymore.
           * The monitor was responsible for calling expire () on deadline expiration
           * and when the task has already been handled (expired or cancelled otherwise)
           * execute () won't do anything.
           */
          dtask->execute ();

          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                             "finished task " << dtask->instance_id () <<
                             "::" << dtask->event_id ());

          if (dtask->deadline ().deadline_type_ != ExF::DeadlineType::DLT_NONE)
          {
            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                               "stopping deadline monitoring for task");

            this->monitor_->stop_monitoring (dtask);
          }

          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                             "running post execution checks");

          if (local_thread_taskq.is_active ())
          {
            // before releasing check if this is a dynamic thread pool
            if (this->dtp_ == DispatchThreadPolicy::DTP_POOL)
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                                 "analyzing dynamic thread pool capacity");

              // do we need/can we expand capacity?
              if (this->busy_count_ == this->thread_num_ &&
                  this->thread_num_ < this->maxsize_)
              {
                std::lock_guard<std::mutex> _q_guard (this->q_lock_);

                if (this->busy_count_ == this->thread_num_ &&
                    this->thread_num_ < this->maxsize_)
                {
                  // add a new thread to the pool
                  this->threads_.push_back (std::thread (&Dispatcher::svc, this));
                  this->thread_num_++;
                  CIAOX11_EXF_LOG_INFO ("ExF::Impl::Dispatcher::execute_task - "\
                                     "added extra pool thread [min="
                                     << this->minsize_ << " max="
                                     << this->maxsize_ << " running="
                                     << this->thread_num_.load () << "busy="
                                     << this->busy_count_.load () << "]");
                }
              }
            }

            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                               "releasing instance");

            // release
            --this->busy_count_;
            dtask->instance ()->release ();
          }

          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Dispatcher::execute_task - " \
                             "leaving");
        }
      }

    } /* namespace Impl */
  } /* namespace ExF */
} /* namespace CIAOX11 */
