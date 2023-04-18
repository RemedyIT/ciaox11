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
#include "exf/deployment/scheduler/ciaox11_exf_scheduler_export.h"

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

        class CIAOX11_EXF_SCHEDULER_Export Instance
        {
        public:
          explicit Instance (std::string id, uint16_t concurrent)
            : instance_id_ (std::move(id)), concurrent_ (concurrent) {}
          ~Instance () = default;

          /// Return the unique id of this instance
          const std::string& instance_id () const
          { return this->instance_id_; }

          bool closed () const
          { return this->closed_.load (); }

          /// Allocate this instance for executing a next task
          /// @retval true Instance has been allocated for a next task
          /// @retval false Instance was not allocated, already busy with a task
          /// @note This operation must be called from the dispatcher with
          /// its _g_queue lock held, this operation is *NOT* thread safe
          /// in itself
          bool allocate ()
          {
            // When have a concurrent flag greater as zero we can dispatch
            // a task to it
            if (this->concurrent_ > 0)
            {
              --concurrent_;
              return true;
            }
            return false;
          }

          /// A event is ready we release this instance so that it can be
          /// scheduled for another event
          /// @note This operation must be called from the dispatcher with
          /// its _g_queue lock held, this operation is *NOT* thread safe
          /// in itself
          void release ()
          { ++this->concurrent_; }

        private:
          friend class Dispatcher;
          Instance () = delete;
          Instance (const Instance&) = delete;
          Instance (Instance&&) = delete;
          Instance& operator= (const Instance&) = delete;
          Instance& operator= (Instance&&) = delete;

          /// Unique id for this instance
          std::string const instance_id_;
          /// How many concurrent events can we still dispatch to the instance.
          /// This has a default value of 1 (single threaded), but can be configured
          /// to a higher number to allow multiple threads to execute events
          /// on the instance.
          /// A new event can be dispatched when this counter has a value greater
          /// than
          uint16_t concurrent_ {};
          /// A reference to an instance is stored in the tasks that are scheduled.
          /// This flag is to prevent that we execute tasks that are for an instance
          /// that is closed in the time the task is in the queue between scheduling
          /// and execution
          std::atomic_bool closed_ {};
        }; /* class Instance */

        using instance_ref = std::shared_ptr<Instance>;

        /**
         * @class DispatchTask
         *
         * @brief A class implementing support for queued executors.
         *
         */
        class CIAOX11_EXF_SCHEDULER_Export DispatchTask
          : public ExF::ExecutionTask
        {
        public:
          using task_ref = std::shared_ptr<DispatchTask>;

          DispatchTask (ExF::Executor::ref_type&& exec,
                        instance_ref instance);
          ~DispatchTask () override = default;

          const ExF::Deadline& deadline () const noexcept(true) override;

          /**
           * Expire the encapsulated operation.
           * This method should never throw an exception.
           */
          void expire () noexcept(true) override;

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

          const std::string& instance_id () const noexcept(true) override;

          const std::string& event_id () const noexcept(true) override;

        private:
          DispatchTask () = delete;
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
        class CIAOX11_EXF_SCHEDULER_Export DispatchQueue final
        {
        public:
          DispatchQueue (DispatchQueuePolicy dqp);
          ~DispatchQueue () = default;

          /// Enqueue a task to the dispatch queue
          bool enqueu(task_ref data, ExF::Priority prio);

          /// Dequeue a task from the queue. By default only a task
          /// is dequeued for an instance which is not executing already a task.
          /// At the moment @a always is true a task can be dequeued which
          /// is already executing a task
          bool dequeue(task_ref& data, bool always = false);
          bool dequeue(task_ref& data, std::chrono::microseconds timeout);

          /// Activate the queue and notify all worker threads about
          /// this state change
          void activate ();

          /// Shutdown this queue and notify all worker threads about
          /// this state change
          void shutdown ();

          bool is_shutdown () const;
          bool is_active () const;
          bool empty () const;
          uint64_t count ();

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

          bool enqueue_i (task_ref task, ExF::Priority prio);
          bool dequeue_i (task_ref& task, bool always = false);
          QEntry* claim_free ();
          void insert_free (QEntry* free_entry);
          void allocate_block ();

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
          std::atomic_bool          shutdown_ {};

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

          const std::string& instance_id () const;

          ExF::SchedulerResult enter (ExF::Executor::ref_type&& exec);

          bool closed ();

          void close ();

        private:
          friend class Dispatcher;

          DispatchGate (Dispatcher::ref_type disp,
                        Dispatcher::instance_ref instance,
                        Dispatcher::task_queue_ref q);
          DispatchGate () = delete;
          DispatchGate (const DispatchGate&) = delete;
          DispatchGate (DispatchGate&&) = delete;
          DispatchGate& operator= (const DispatchGate&) = delete;
          DispatchGate& operator= (DispatchGate&&) = delete;

          Dispatcher::task_queue_ref task_queue () const { return this->queue_; }

          Dispatcher::instance_ref instance_;
          Dispatcher::task_queue_ref queue_;
          Dispatcher::ref_type dispatcher_;
        }; /* class DispatchGate */

        using gate_ref = std::shared_ptr<DispatchGate>;

        virtual ~Dispatcher ();

        bool open ();

        bool start ();
        bool stop ();

        bool close ();

        std::shared_ptr<DispatchGate> open_dispatch_gate (const std::string& instance_id, uint16_t concurrent);

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

        ExF::DeadlineMonitor::ref_type monitor ();

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
