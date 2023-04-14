/**
 * @file   ciaox11_exf_scheduler_i.h
 * @author Martin Corino
 *
 * @brief AXCIOMA execution scheduler implementation.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_SCHEDULER_IMPL_H
#define CIAOX11_EXF_SCHEDULER_IMPL_H

#pragma once

#include "exf/deployment/core/ciaox11_schedule.h"
#include "exf/deployment/core/ciaox11_monitor.h"
#include "exf/deployment/scheduler/ciaox11_exf_dispatcher.h"
#include "exf/deployment/scheduler/ciaox11_exf_scheduler_export.h"

#include <mutex>
#include <map>
#include <vector>

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class CIAOX11_EXF_SCHEDULER_Export Scheduler
        : public ExF::Scheduler
      {
      public:
        Scheduler (const Components::ConfigValues& cfg);
        ~Scheduler () override;

        ExF::SchedulerResult open_scheduling_lane (
            const std::string& instance_id,
            const Components::ConfigValues& cfg,
            ::IDL::traits<ExF::SchedulingLane>::ref_type& lane) override;

        ExF::SchedulerResult find_scheduling_lane (
            const std::string& instance_id,
            ::IDL::traits<ExF::SchedulingLane>::ref_type& lane) override;

        ExF::SchedulerResult close_scheduling_lane (
            const std::string& instance_id) override;

        void close () override;

      private:
        enum class DispatchPolicyType : uint32_t
        {
          DEFAULT,
          EXCLUSIVE,
          GROUPED
        };

        bool get_thread_policy (
            const Components::ConfigValue&,
            ExF::Impl::DispatchThreadPolicy&);
        bool get_queue_policy (
            const Components::ConfigValue&,
            ExF::Impl::DispatchQueuePolicy&);
        bool get_uint16_t (
            const Components::ConfigValue&,
            uint16_t&);
        bool get_string (
            const Components::ConfigValue&,
            std::string&);
        bool get_dispatch_policy (
            const Components::ConfigValue&,
            DispatchPolicyType&);

        ExF::DeadlineMonitor::ref_type monitor_;

        ExF::Impl::DispatchThreadPolicy thread_policy_ {ExF::Impl::DispatchThreadPolicy::DTP_SINGLE};
        uint16_t min_threads_ {};
        uint16_t max_threads_ {};
        ExF::Impl::DispatchQueuePolicy queue_policy_ {ExF::Impl::DispatchQueuePolicy::DQP_FIFO};

        // defaults for lane groups
        ExF::Impl::DispatchThreadPolicy lane_thread_policy_ {ExF::Impl::DispatchThreadPolicy::DTP_SINGLE};
        uint16_t lane_min_threads_ {};
        uint16_t lane_max_threads_ {};
        ExF::Impl::DispatchQueuePolicy lane_queue_policy_ {};

        std::mutex lock_;

        ExF::Impl::Dispatcher::ref_type default_dispatcher_ {};

        struct LANE_ENTRY
        {
          IDL::traits<ExF::SchedulingLane>::ref_type lane_ {};
          std::string group_ {};
        };

        using LANE_PAIR = std::pair<std::string, LANE_ENTRY>;
        using LANE_MAP = std::map<std::string, LANE_ENTRY>;

        struct GROUP_ENTRY
        {
          GROUP_ENTRY (ExF::Impl::Dispatcher::ref_type d) : dispatcher_ (std::move(d)) {}
          GROUP_ENTRY () = default;
          GROUP_ENTRY (const GROUP_ENTRY&) = default;
          GROUP_ENTRY (GROUP_ENTRY&&) = default;

          ExF::Impl::Dispatcher::ref_type dispatcher_ {};
          uint32_t lane_count_ {};
        };

        using GROUP_PAIR = std::pair<std::string, GROUP_ENTRY>;
        using GROUP_MAP = std::map<std::string, GROUP_ENTRY>;

        LANE_MAP lanes_ {};
        GROUP_MAP groups_ {};
      };
    }
  }
}

#endif /* CIAOX11_EXF_SCHEDULER_IMPL_H */
