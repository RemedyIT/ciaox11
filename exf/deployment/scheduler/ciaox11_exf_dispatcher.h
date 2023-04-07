/**
 * @file   ciaox11_exf_dispatcher.h
 * @author Martin Corino
 *
 * @brief AXCIOMA execution scheduler dispatcher implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_DISPATCHER_H
#define CIAOX11_EXF_DISPATCHER_H

#pragma once

#include "exf/deployment/core/ciaox11_schedule.h"
#include "exf/deployment/core/ciaox11_monitor.h"

#if defined(ACE_WIN32) || \
    (defined (_POSIX_MONOTONIC_CLOCK) && !defined (ACE_LACKS_MONOTONIC_TIME)) || \
    defined (ACE_HAS_CLOCK_GETTIME_MONOTONIC)
# include "ace/Monotonic_Time_Policy.h"
# define EXF_TIME_POLICY  ACE_Monotonic_Time_Policy
#else
# include "ace/Time_Policy.h"
# define EXF_TIME_POLICY  ACE_System_Time_Policy
#endif

#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>
#include <limits>

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      enum class DispatchThreadPolicy : uint32_t
      {
        DTP_SINGLE,
        DTP_MULTI,
        DTP_POOL
      };

      const std::string& thread_policy_id (DispatchThreadPolicy pol);

      enum class DispatchQueuePolicy : uint32_t
      {
        DQP_FIFO,
        DQP_LIFO
      };

      const std::string& queue_policy_id (DispatchQueuePolicy pol);

      /**
       * @class Dispatcher
       *
       * @brief A class managing executor queue(s) and running
       *        dispatching thread(s) for one or more instances.
       *
       */
      class Dispatcher
      {
      public:
        using ref_type = std::shared_ptr<Dispatcher>;

        class DispatchTask; // fwd

        using task_ref = std::shared_ptr<DispatchTask>;

        class Instance
        {
        public:
          ~Instance () = default;

          /// Return the unique id of this instance
          const std::string& instance_id () const
          { return this->instance_id_; }

          bool closed () const
          { return this->closed_.load (); }

          /// Are we executing a task for this instance?
          bool is_busy () const
          { return this->busy_.load (); }

          /// Allocate this instance for executing a next task
          /// @retval true Instance has been allocated for a next task
          /// @retval false Instance was not allocated, already busy with a task
          bool allocate ()
          { return !this->busy_.exchange(true); }

          /// Tag this instance ready for the next task
          void release ()
          { this->busy_ = false; }

        private:
          friend class Dispatcher;

          Instance (const std::string& id)
            : instance_id_ (id) {}

          std::string const instance_id_;
          std::atomic<bool> busy_ {};
          std::atomic<bool> closed_ {};
        }; /* class Instance */

        using instance_ref = std::shared_ptr<Instance>;

        /**
         * @class DispatchTask
         *
         * @brief A class implementing support for queued executors.
         *
         */
        class DispatchTask
          : public ExF::ExecutionTask
        {
        public:
          using task_ref = std::shared_ptr<DispatchTask>;

          DispatchTask (ExF::Executor::ref_type&& exec,
                        instance_ref instance)
            : executor_ (std::move (exec)), instance_ (instance)
          {
            if (this->executor_->deadline ().deadline_type_ != ExF::DeadlineType::DLT_NONE)
            {
              this->absolute_dead_line_.deadline_time_ =
                  ACE_Time_Value_T<EXF_TIME_POLICY> (
                      this->executor_->deadline ().deadline_time_).to_absolute_time ();
              this->absolute_dead_line_.deadline_type_ =
                      this->executor_->deadline ().deadline_type_;
            }
          }
          ~DispatchTask () override = default;

          virtual const ExF::Deadline& deadline () const noexcept(true);

          /**
           * Expire the encapsulated operation.
           * This method should never throw an exception.
           */
          virtual void expire () noexcept(true);

          /**
           * Cancel the encapsulated operation.
           * This method should never throw an exception.
           */
          void cancel (bool expired = false) noexcept(true);

          /**
           * Execute the encapsulated operation.
           * This method should never throw an exception.
           */
          void execute () noexcept(true);

          const std::string& instance_id () const noexcept(true)
          { return this->instance_->instance_id (); }

          const std::string& event_id () const noexcept(true)
          { return this->executor_->event_id (); }

        private:
          DispatchTask (const DispatchTask&) = delete;
          DispatchTask& operator= (const DispatchTask&) = delete;
          DispatchTask (DispatchTask&&) = delete;
          DispatchTask& operator= (DispatchTask&&) = delete;
          friend class Dispatcher;

          instance_ref instance ()
          { return this->instance_; }

          std::atomic_bool processing_ {};
          std::atomic_bool processed_ {};
          ExF::Executor::ref_type executor_;
          instance_ref instance_;
          ExF::Deadline absolute_dead_line_ {};
        }; /* class DispatchTask */

        /**
         * @class DispatchQueue
         *
         * @brief A priority queue for dispatch tasks with instance allocation
         *        support.
         *
         * This queue is implemented as a doubly linked list.
         * This queue allocates memory for entry elements in contiguous blocks of configured size.
         * Blocks are allocated as needed and added to a free list.
         * Allocated entry blocks are never freed during the life cycle of the queue.
         * Dequeued entries are released to the free list enqueued entries allocated from the free list.
         */
        class DispatchQueue
        {
        public:
          DispatchQueue (DispatchQueuePolicy dqp)
          {
            if (dqp == DispatchQueuePolicy::DQP_FIFO)
              this->cmp_ = DispatchPolicyFIFO();
            else
              this->cmp_ = DispatchPolicyLIFO();
            // initialize free list
            this->allocate_block ();
          }
          ~DispatchQueue () = default;

          /// Enqueue a task to the dispatch queue
          bool enqueu(task_ref data, ExF::Priority prio)
          {
            {
              std::unique_lock<std::mutex> _g_queue (this->mutex_);

              bool const flow_control = (high_water_mark>low_water_mark && high_water_mark==this->count_);

              while (!this->shutdown_ &&
                  ((flow_control && this->count_ > low_water_mark) ||
                      this->seqnr_ == std::numeric_limits<uint64_t>::max ()))
              {
                // in case we've triggered flow control or reached the overrun max
                // (unlikely to happen more than once every several thousand year or so)
                // we wait (block) until dequeue frees us or the queue is shutdown.
                this->condition_.wait (_g_queue);
              }

              if (this->shutdown_)
                return false;

              if (!this->enqueue_i(std::move (data), prio))
                return false;
            }

            this->condition_.notify_all ();

            return true;
          }

          /// Dequeue a task from the queue. By default only a task
          /// is dequeued for an instance which is not executing already a task.
          /// At the moment @a always is true a task can be dequeued which
          /// is already executing a task
          bool dequeue(task_ref& data, bool always = false)
          {
            std::lock_guard<std::mutex> _g_queue (this->mutex_);

            if (always || !this->shutdown_)
            {
              return this->dequeue_i(data, always);
            }
            return false;
          }

          bool dequeue(task_ref& data, std::chrono::microseconds timeout)
          {
            std::unique_lock<std::mutex> _g_queue (this->mutex_);

            if (!this->shutdown_)
            {
              if (this->dequeue_i(data))
                return true;

              this->condition_.wait_for (_g_queue, timeout);

              if (!this->shutdown_ && this->dequeue_i(data))
                return true;
            }

            return false;
          }

          /// Activate the queue and notify all worker threads about
          /// this state change
          void activate ()
          {
            {
              std::lock_guard<std::mutex> _g_queue (this->mutex_);

              this->shutdown_ = false;
            }

            this->condition_.notify_all ();
          }

          /// Shutdown this queue and notify all worker threads about
          /// this state change
          void shutdown ()
          {
            {
              std::lock_guard<std::mutex> _g_queue (this->mutex_);

              this->shutdown_ = true;
            }

            this->condition_.notify_all ();
          }

          bool is_shutdown () const
          {
            return this->shutdown_;
          }

          bool is_active () const
          {
            return !this->is_shutdown ();
          }

          bool empty () const
          {
            return this->count_ == 0;
          }

          uint64_t count ()
          {
            std::lock_guard<std::mutex> _g_queue (this->mutex_);

            return this->count_;
          }

          static uint32_t allocation_block_size; // default 64
          static uint64_t high_water_mark; // default 0 (flow control disabled)
          static uint64_t low_water_mark; // default 16

        private:
          struct QEntry
          {
            task_ref      task_ {};
            ExF::Priority prio_ {};
            uint64_t      seqnr_ {};
            QEntry*       prev_ {};
            QEntry*       next_ {};
          };

          bool enqueue_i (task_ref task, ExF::Priority prio)
          {
            try
            {
              // claim a free entry
              QEntry* new_entry = this->claim_free ();
              new_entry->task_ = std::move (task);
              new_entry->prio_ = prio;
              new_entry->seqnr_ = this->seqnr_++;

              // increment the queue count
              ++this->count_;

              // insert into queue list based on prio and seq
              // start looking from the tail until an entry is found
              // which is 'larger' than the new entry
              for (QEntry* qep=this->tail_ ; qep ; qep=qep->next_)
              {
                // is new entry 'smaller' than queue entry?
                if (this->cmp_ (*new_entry, *qep))
                {
                  // insert before the queue entry
                  new_entry->next_ = qep;
                  if (qep->prev_)
                  {
                    new_entry->prev_ = qep->prev_;
                    qep->prev_->next_ = new_entry;
                  }
                  else
                  {
                    // this must be the tail end itself
                    // replace with new entry
                    this->tail_ = new_entry;
                  }
                  qep->prev_ = new_entry;

                  return true;
                }
              }
              // new entry 'larger' than any (or queue empty) add as new queue head
              new_entry->prev_ = this->head_;
              if (this->head_)
                this->head_->next_ = new_entry;
              this->head_ = new_entry;
              // if the queue was empty also set tail to new_entry
              if (!this->tail_)
                this->tail_ = new_entry;

              return true;
            }
            catch (const std::bad_alloc&)
            {
              return false;
            }
          }

          bool dequeue_i (task_ref& task, bool always = false)
          {
            // start looking from the head for an entry
            // of which the instance is not busy (if any)
            for (QEntry* qep=this->head_; qep ;qep=qep->prev_)
            {
              if (always || qep->task_->instance_->allocate ())
              {
                // remove entry from queue list
                if (qep->next_)
                {
                  qep->next_->prev_ = qep->prev_;
                }
                else
                {
                  // must be head itself
                  this->head_ = qep->prev_;
                  if (this->head_)
                    this->head_->next_ = nullptr;
                }
                if (qep->prev_)
                {
                  qep->prev_->next_ = qep->next_;
                }
                else
                {
                  // must be tail
                  this->tail_ = qep->next_;
                  if (this->tail_)
                    this->tail_->prev_ = nullptr;
                }
                // get task
                task = std::move (qep->task_);
                // cleanup entry
                qep->prev_ = nullptr;
                // insert into free list
                this->insert_free(qep);

                // decrement the queue count
                --this->count_;
                if (this->count_ == 0)
                {
                  // reset sequence number when queue is empty
                  if (this->seqnr_ == std::numeric_limits<uint64_t>::max ())
                  {
                    // notify any overrun waiters that we're resetting
                    this->condition_.notify_all ();
                  }
                  this->seqnr_ = 0;
                }

                return true;
              }
            }
            return false;
          }

          QEntry* claim_free ()
          {
            if (!this->free_head_)
            {
              this->allocate_block();
            }
            QEntry* claimed_block = this->free_head_;
            if (claimed_block->prev_)
            {
              this->free_head_ = claimed_block->prev_;
              this->free_head_->next_ = nullptr;
            }
            else
            {
              // list is empty now
              this->free_tail_ = nullptr;
              this->free_head_ = nullptr;
            }
            claimed_block->prev_ = claimed_block->next_ = nullptr;
            return claimed_block;
          }

          void insert_free (QEntry* free_entry)
          {
            // insert into free list at tail end
            free_entry->next_ = this->free_tail_;
            if (this->free_tail_)
              this->free_tail_->prev_ = free_entry;
            this->free_tail_ = free_entry;
            // if this is the first for an empty list this new entry also becomes the current head
            if (!this->free_head_)
              this->free_head_ = this->free_tail_;
          }

          // allocates a new block of (initially) free entries
          void allocate_block ()
          {
            // allocate block
            this->allocations_.push_back(std::make_unique<QEntry[]> (allocation_block_size));
            // get block pointer
            QEntry* new_block_ = this->allocations_.back ().get ();
            // insert into free list at tail end
            for (uint32_t i=0; i<allocation_block_size ;++i)
            {
              QEntry* new_entry = std::addressof(new_block_[i]);
              this->insert_free(new_entry);
            }
          }

          using alloc_block_type = std::unique_ptr<QEntry[]>;
          using alloc_list_type = std::vector<alloc_block_type>;

          alloc_list_type           allocations_ {};

          // linked lists are linked from tail -> head

          QEntry*                   head_ {};
          QEntry*                   tail_ {};
          std::atomic<uint64_t>     count_ {};

          QEntry*                   free_head_ {};
          QEntry*                   free_tail_ {};

          uint64_t                  seqnr_ {};
          std::mutex                mutex_ {};
          std::condition_variable   condition_ {};
          std::atomic<bool>         shutdown_ {};

          using cmp_type = std::function<bool (const QEntry&, const QEntry&)>;

          cmp_type                  cmp_ {};

          struct DispatchPolicyFIFO
          {
            bool operator ()(const QEntry& e1, const QEntry& e2) const
            {
              return (e1.prio_ < e2.prio_ || (e1.prio_ == e2.prio_ && e1.seqnr_ > e2.seqnr_));
            }
          };

          struct DispatchPolicyLIFO
          {
            bool operator ()(const QEntry& e1, const QEntry& e2) const
            {
              return (e1.prio_ < e2.prio_ || (e1.prio_ == e2.prio_ && e1.seqnr_ < e2.seqnr_));
            }
          };
        }; /* class DispatchQueue */

        using task_queue = DispatchQueue ;
        using task_queue_ref = std::shared_ptr<task_queue>;

        /**
         * @class DispatchGate
         *
         * @brief A class implementing an entrypoint for the dispatcher
         *        queue for executors from a single instance.
         */
        class DispatchGate
        {
        public:
          using ref_type = std::shared_ptr<DispatchGate> ;

          ~DispatchGate ();

          const std::string& instance_id () const { return this->instance_->instance_id (); }

          ExF::Count queued_count ();

          ExF::SchedulerResult enter (ExF::Executor::ref_type&& exec);

          bool closed ()
          { return this->instance_->closed (); }

          void close ()
          { if (!this->closed ()) this->dispatcher_->close_dispatch_gate (*this); }

        private:
          friend class Dispatcher;

          DispatchGate (Dispatcher::ref_type disp,
                        Dispatcher::instance_ref instance,
                        Dispatcher::task_queue_ref q)
            : instance_ (std::move(instance))
            , queue_ (std::move(q))
            , dispatcher_ (std::move(disp)) {}

          Dispatcher::task_queue_ref task_queue () const { return this->queue_; }

          Dispatcher::instance_ref instance_;
          Dispatcher::task_queue_ref queue_;
          std::shared_ptr<Dispatcher> dispatcher_;
        }; /* class DispatchGate */

        using gate_ref = std::shared_ptr<DispatchGate>;

        virtual ~Dispatcher ();

        bool open ();

        bool start ();
        bool stop ();

        bool close ();

        std::shared_ptr<DispatchGate> open_dispatch_gate (
            const std::string& instance_id);

        static std::chrono::microseconds dispatcher_dequeue_timeout;
        static size_t max_idle_pool_threads;

        static ref_type create_instance (
            ExF::DeadlineMonitor::ref_type monitor,
            DispatchThreadPolicy dtp,
            DispatchQueuePolicy dqp,
            uint16_t count=1,
            uint16_t max=0);

      private:
        Dispatcher (ExF::DeadlineMonitor::ref_type monitor,
                    DispatchThreadPolicy dtp,
                    DispatchQueuePolicy dqp,
                    uint16_t count=1,
                    uint16_t max=0);

        friend class DispatchGate;

        bool start_i ();

        void close_dispatch_gate (const DispatchGate& dg);

        ExF::DeadlineMonitor::ref_type monitor () { return this->monitor_; }

        void svc ();

        void execute_task (task_ref dtask, task_queue& taskq);

        /*
         * State
         */

        DispatchThreadPolicy dtp_;
        DispatchQueuePolicy dqp_;
        uint16_t minsize_;
        uint16_t maxsize_;

        std::mutex q_lock_ {};

        task_queue_ref queue_ {};

        std::vector<std::thread> threads_ {};
        std::atomic<size_t> thread_num_ {};

        using INSTANCE_PAIR = std::pair<std::string, instance_ref>;
        using INSTANCE_MAP = std::map<std::string, instance_ref>;

        INSTANCE_MAP instance_map_ {};
        std::atomic<size_t> busy_count_ {};

        ExF::DeadlineMonitor::ref_type monitor_;

        std::weak_ptr<Dispatcher> self_;
      };
    }
  }
}

#endif /* CIAOX11_EXF_SCHEDULER_IMPL_H */
