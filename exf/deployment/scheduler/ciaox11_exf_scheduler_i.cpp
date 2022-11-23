/**
 * @file   ciaox11_exf_scheduler_i.cpp
 * @author Martin Corino
 *
 * @brief AXCIOMA execution scheduler implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/scheduler/ciaox11_exf_scheduler_i.h"

#include "exf/deployment/logger/log.h"

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class SchedulingLane
        : public ExF::SchedulingLane
      {
      public:
        SchedulingLane (ExF::Impl::Dispatcher::gate_ref gate)
          : gate_ (gate) {}
        virtual ~SchedulingLane ();

        virtual ExF::Count trafic_count ()
        { return this->gate_->queued_count (); }

        virtual bool closed ()
        { return this->gate_->closed (); }

        virtual void close ()
        { this->gate_->close (); }

        virtual ExF::SchedulerResult submit (
            ExF::Executor::ref_type&& exec);

      private:
        ExF::Impl::Dispatcher::gate_ref gate_;
      };

      SchedulingLane::~SchedulingLane ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::SchedulingLane::~SchedulingLane -");

        this->close ();
      }

      ExF::SchedulerResult SchedulingLane::submit (
          ExF::Executor::ref_type&& exec)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::SchedulingLane::submit -");

        if (!this->gate_)
        {
          CIAOX11_EXF_LOG_PANIC ("ExF::Impl::SchedulingLane::submit -" <<
                             "scheduling gate NULL");
        }

        if (!this->closed ())
        {
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::SchedulingLane::submit -" <<
                             "entering scheduling gate");

          return this->gate_->enter (std::move (exec));
        }
        return SchedulerResult::SINTERRUPT;
      }

      /*===========================================================*/

      bool Scheduler::get_thread_policy (
          const Components::ConfigValue& cval,
          ExF::Impl::DispatchThreadPolicy& pol)
      {
        std::string val;
        if (!(cval.value () >>= val))
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Scheduler::get_thread_policy - "
                             "failed to extract value for "
                             << cval.name ());
          return false;
        }
        else
        {
          if (val == ExF::SCHEDULER_THREAD_SINGLE)
            pol = DispatchThreadPolicy::DTP_SINGLE;
          else if (val == ExF::SCHEDULER_THREAD_MULTI)
            pol = DispatchThreadPolicy::DTP_MULTI;
          else if (val == ExF::SCHEDULER_THREAD_DYNAMIC)
            pol = DispatchThreadPolicy::DTP_POOL;
          else
          {
            CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Scheduler::get_thread_policy - "
                               "invalid value [" << val << "] for "
                               << cval.name ());
            return false;
          }
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::get_thread_policy - "
                             << cval.name () << " policy = "
                             << ExF::Impl::thread_policy_id (pol));
        }
        return true;
      }

      bool Scheduler::get_queue_policy (
          const Components::ConfigValue& cval,
          ExF::Impl::DispatchQueuePolicy& pol)
      {
        std::string val;
        if (!(cval.value () >>= val))
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Scheduler::get_queue_policy - "
                             "failed to extract value for "
                             << cval.name ());
          return false;
        }
        else
        {
          if (val == ExF::SCHEDULER_QUEUE_FIFO)
            pol = DispatchQueuePolicy::DQP_FIFO;
          else if (val == ExF::SCHEDULER_QUEUE_LIFO)
            pol = DispatchQueuePolicy::DQP_LIFO;
          else
          {
            CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Scheduler::get_queue_policy - "
                               "invalid value [" << val << "] for "
                               << cval.name ());
            return false;
          }
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::get_queue_policy - "
                             << cval.name () << " policy = "
                             << ExF::Impl::queue_policy_id (pol));
        }
        return true;
      }

      bool Scheduler::get_count (
          const Components::ConfigValue& cval,
          uint16_t& count)
      {
        uint16_t val;
        if (!(cval.value () >>= val))
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Scheduler::get_count - "
                             "failed to extract value for "
                             << cval.name ());
          return false;
        }
        else
        {
          count = val;
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::get_count - "
                             << cval.name () << " count = " << count);
        }
        return true;
      }

      bool Scheduler::get_group (
          const Components::ConfigValue& cval,
          std::string& group)
      {
        std::string val;
        if (!(cval.value () >>= val))
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Scheduler::get_group - "
                             "failed to extract value for "
                             << cval.name ());
          return false;
        }
        else
        {
          group = val;
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::get_group - "
                             << cval.name () << " group = " << group);
        }
        return true;
      }

      bool Scheduler::get_dispatch_policy (
          const Components::ConfigValue& cval,
          DispatchPolicyType& type)
      {
        std::string val;
        if (!(cval.value () >>= val))
        {
          CIAOX11_EXF_LOG_ERROR ("ExF::Impl::Scheduler::get_dispatch_policy - "
                             "failed to extract value for "
                             << cval.name ());
          return false;
        }
        else
        {
          if (val == ExF::SCHEDULING_LANE_EXCLUSIVE_DISPATCH)
            type = DispatchPolicyType::EXCLUSIVE;
          else if (val == ExF::SCHEDULING_LANE_GROUPED_DISPATCH)
            type = DispatchPolicyType::GROUPED;
          else
            type = DispatchPolicyType::DEFAULT;

          CIAOX11_EXF_LOG_INFO ("ExF::Impl::Scheduler::get_dispatch_policy - "
                            "value [" << val << "] for "
                            << cval.name ());
        }
        return true;
      }

      Scheduler::Scheduler (
          const Components::ConfigValues& cfg)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::Scheduler -");

        bool lane_queue_pol_set {};
        for (const Components::ConfigValue& cval : cfg)
        {
          if (cval.name () == ExF::SCHEDULER_THREAD_POLICY)
          {
            this->get_thread_policy (cval, this->thread_policy_);
          }
          else if (cval.name () == ExF::SCHEDULER_THREAD_COUNT)
          {
            this->get_count (cval, this->min_threads_);
          }
          else if (cval.name () == ExF::SCHEDULER_THREAD_MAXCOUNT)
          {
            this->get_count (cval, this->max_threads_);
          }
          else if (cval.name () == ExF::SCHEDULER_QUEUE_POLICY)
          {
            this->get_queue_policy (cval, this->queue_policy_);
          }
          else if (cval.name () == ExF::SCHEDULING_LANE_QUEUE_POLICY)
          {
            lane_queue_pol_set =
                this->get_queue_policy (cval, this->lane_queue_policy_);
          }
          else if (cval.name () == ExF::SCHEDULING_LANE_THREAD_POLICY)
          {
            this->get_thread_policy (cval, this->lane_thread_policy_);
          }
          else if (cval.name () == ExF::SCHEDULING_LANE_THREAD_COUNT)
          {
            this->get_count (cval, this->lane_min_threads_);
          }
          else if (cval.name () == ExF::SCHEDULING_LANE_THREAD_MAXCOUNT)
          {
            this->get_count (cval, this->lane_max_threads_);
          }
          if (!lane_queue_pol_set)
          {
            this->lane_queue_policy_ = this->queue_policy_;
          }
        }

        this->monitor_ = ExF::DeadlineMonitor::create_instance (cfg);
      }

      Scheduler::~Scheduler ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::~Scheduler");

        this->close ();
      }

      ExF::SchedulerResult
      Scheduler::open_scheduling_lane (
          std::string instance_id,
          const Components::ConfigValues& cfg,
          ::IDL::traits<ExF::SchedulingLane>::ref_type& lane)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane -");

        // lane settings
        DispatchPolicyType lane_dispatch { DispatchPolicyType::DEFAULT };
        DispatchQueuePolicy lane_pol {this->lane_queue_policy_};
        std::string lane_group {};

        // analyze provided configuration
        for (const Components::ConfigValue& cval : cfg)
        {
          if (cval.name () == ExF::SCHEDULING_LANE_DISPATCH_POLICY)
          {
            if (!this->get_dispatch_policy (cval, lane_dispatch))
            {
              return SchedulerResult::SFAILED;
            }
          }
          else if (cval.name () == ExF::SCHEDULING_LANE_QUEUE_POLICY)
          {
            if (!this->get_queue_policy (cval, lane_pol))
            {
              return SchedulerResult::SFAILED;
            }
          }
          else if (cval.name () == ExF::SCHEDULING_LANE_GROUP_ID)
          {
            if (!this->get_group (cval, lane_group))
            {
              return SchedulerResult::SFAILED;
            }
          }
        }

        // reset the lane ref
        lane.reset ();

        LANE_ENTRY lane_entry {};

        // enter lock scope
        {
          std::lock_guard<std::mutex> __guard (this->lock_);

          // do we need an exclusive lane or a shared lane
          if (lane_dispatch == DispatchPolicyType::EXCLUSIVE)
          {
            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                               "creating dispatcher for " << instance_id);

            // create an exclusive single threaded dispatcher
            ExF::Impl::Dispatcher::ref_type dispatcher =
                ExF::Impl::Dispatcher::create_instance (
                    this->monitor_,
                    DispatchThreadPolicy::DTP_SINGLE,
                    lane_pol);
            if (!dispatcher)
            {
              CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                    "failed to create exclusive dispatcher for "
                                    << instance_id);

              return SchedulerResult::SFAILED;
            }

            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                               "opening dispatcher for " << instance_id);

            if (!dispatcher->open ())
            {
              CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                    "failed to open dispatcher for "
                                    << instance_id);

              return SchedulerResult::SFAILED;
            }

            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                               "opening dispatch gate for " << instance_id);

            // open a gate on the dispatcher
            ExF::Impl::Dispatcher::gate_ref gate =
                dispatcher->open_dispatch_gate (instance_id);
            if (gate)
            {
              // create the exclusive scheduling lane
              lane_entry.lane_ = ::CORBA::make_reference<ExF::Impl::SchedulingLane> (gate);
            }
          }
          else if (lane_dispatch == DispatchPolicyType::GROUPED)
          {
            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                               "setting up sheduling lane for " << instance_id);

            // check for existing group lane
            GROUP_MAP::iterator it = this->groups_.find (lane_group);
            if (it == this->groups_.end ())
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                 "creating group dispatcher for " << lane_group);

              // get scheduler threading and queue settings
              ExF::Impl::DispatchThreadPolicy thread_policy
                  {this->lane_thread_policy_};
              uint16_t min_threads {this->lane_min_threads_};
              uint16_t max_threads {this->lane_max_threads_};

              for (const Components::ConfigValue& cval : cfg)
              {
                if (cval.name () == ExF::SCHEDULING_LANE_THREAD_POLICY)
                {
                  this->get_thread_policy (cval, thread_policy);
                }
                else if (cval.name () == ExF::SCHEDULING_LANE_THREAD_COUNT)
                {
                  this->get_count (cval, min_threads);
                }
                else if (cval.name () == ExF::SCHEDULING_LANE_THREAD_MAXCOUNT)
                {
                  this->get_count (cval, max_threads);
                }
              }

              // create the default (shared) dispatcher
              ExF::Impl::Dispatcher::ref_type dispatcher =
                  ExF::Impl::Dispatcher::create_instance (
                      this->monitor_,
                      thread_policy,
                      lane_pol,
                      min_threads,
                      max_threads);
              if (!dispatcher)
              {
                CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                      "failed to create group dispatcher for "
                                      << lane_group);

                return SchedulerResult::SFAILED;
              }

              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                 "opening group dispatcher for " << lane_group);

              if (!dispatcher->open ())
              {
                CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                      "failed to open group dispatcher for "
                                      << lane_group);

                return SchedulerResult::SFAILED;
              }

              // register group dispatcher
              this->groups_.insert (GROUP_PAIR (lane_group, GROUP_ENTRY {dispatcher}));

              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                 "opening dispatch gate for " << instance_id);

              // open a gate on the dispatcher
              ExF::Impl::Dispatcher::gate_ref gate =
                  dispatcher->open_dispatch_gate (instance_id);
              if (gate)
              {
                // create the exclusive scheduling lane
                lane_entry.lane_ = ::CORBA::make_reference<ExF::Impl::SchedulingLane> (gate);
              }
            }
            else
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                 "opening dispatch gate for " << instance_id);

              // open a gate on the dispatcher
              ExF::Impl::Dispatcher::gate_ref gate =
                  it->second.dispatcher_->open_dispatch_gate (instance_id);
              if (gate)
              {
                // create the exclusive scheduling lane
                lane_entry.lane_ = ::CORBA::make_reference<ExF::Impl::SchedulingLane> (gate);
              }
            }
            if (lane_entry.lane_)
            {
              // register another instance as having a lane referencing this group dispatcher
              this->groups_[lane_group].lane_count_++;
              lane_entry.group_ = lane_group;
            }
          }
          else
          {
            // has the default dispatcher already been created
            if (!this->default_dispatcher_)
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                 "creating default dispatcher");

              // create the default (shared) dispatcher
              this->default_dispatcher_ =
                  ExF::Impl::Dispatcher::create_instance (
                      this->monitor_,
                      this->thread_policy_,
                      this->queue_policy_,
                      this->min_threads_,
                      this->max_threads_);
              if (!this->default_dispatcher_)
              {
                CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                      "failed to create default dispatcher");

                return SchedulerResult::SFAILED;
              }
            }

            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                               "opening default dispatcher");

            if (!this->default_dispatcher_->open ())
            {
              CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                    "failed to open default dispatcher");

              return SchedulerResult::SFAILED;
            }

            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                               "opening dispatch gate for " << instance_id);

            // open a gate on the default dispatcher
            ExF::Impl::Dispatcher::gate_ref gate =
                this->default_dispatcher_->open_dispatch_gate (instance_id);
            if (gate)
            {
              // create the non-exclusive scheduling lane
              lane_entry.lane_ = ::CORBA::make_reference<ExF::Impl::SchedulingLane> (gate);
            }
          }

          if (lane_entry.lane_)
          {
            CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                               "registering scheduling lane for " << instance_id);
            // register lane
            this->lanes_.insert (LANE_PAIR (instance_id, lane_entry));
            std::swap (lane, lane_entry.lane_);
          }

        } // leave lock scope

        if (!lane)
        {
          CIAOX11_EXF_LOG_CRITICAL ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                                "failed to open scheduling lane for " << instance_id);
        }
        else
        {
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::open_scheduling_lane - "\
                             "opened scheduling lane for " << instance_id);
        }

        return lane ? SchedulerResult::SOK : SchedulerResult::SFAILED;
      }

      ExF::SchedulerResult
      Scheduler::find_scheduling_lane (
          std::string instance_id,
          IDL::traits<ExF::SchedulingLane>::ref_type& lane)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::find_scheduling_lane -");

        std::lock_guard<std::mutex> __guard (this->lock_);

        LANE_MAP::iterator it = this->lanes_.find (instance_id);
        if (it == this->lanes_.end ())
        {
          CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::find_scheduling_lane - "\
                             "unable to find scheduling lane for " << instance_id);

          return SchedulerResult::SFAILED;
        }

        lane = it->second.lane_;
        return SchedulerResult::SOK;
      }

      ExF::SchedulerResult
      Scheduler::close_scheduling_lane (
          std::string instance_id)
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::close_scheduling_lane -");

        LANE_ENTRY lane_copy {};
        {
          std::lock_guard<std::mutex> __guard (this->lock_);

          LANE_MAP::iterator itl = this->lanes_.find (instance_id);
          if (itl == this->lanes_.end ())
          {
            CIAOX11_EXF_LOG_INFO ("ExF::Impl::Scheduler::close_scheduling_lane - "\
                              "no scheduling lane for " << instance_id);

            return SchedulerResult::SFAILED;
          }

          std::swap (lane_copy, itl->second);
          this->lanes_.erase (itl);

          GROUP_MAP::iterator itg = this->groups_.find (lane_copy.group_);
          if ( itg != this->groups_.end ())
          {
            itg->second.lane_count_--;
            if (itg->second.lane_count_ == 0)
            {
              this->groups_.erase (itg);
            }
          }
        }

        lane_copy.lane_->close ();
        return SchedulerResult::SOK;
      }

      void Scheduler::close ()
      {
        CIAOX11_EXF_LOG_DEBUG ("ExF::Impl::Scheduler::close -");

        LANE_MAP lanes_copy {};
        GROUP_MAP groups_copy {};
        ExF::Impl::Dispatcher::ref_type dispatcher_copy {};
        {
          std::lock_guard<std::mutex> __guard (this->lock_);

          std::swap (this->lanes_, lanes_copy);
          std::swap (this->groups_, groups_copy);
          std::swap (this->default_dispatcher_, dispatcher_copy);
        }

        groups_copy.clear ();
        LANE_MAP::iterator it = lanes_copy.begin ();
        for (; it != lanes_copy.end (); ++it)
        {
          it->second.lane_->close ();
        }
        lanes_copy.clear ();
        if (dispatcher_copy)
        {
          dispatcher_copy->close ();
          dispatcher_copy.reset ();
        }
      }
    }
  }
}
