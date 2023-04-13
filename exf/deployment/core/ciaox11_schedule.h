/**
 * @file   ciaox11_schedule.h
 * @author Martin Corino
 *
 * @brief Public interfaces for the AXCIOMA execution framework.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_SCHEDULE_H
#define CIAOX11_EXF_SCHEDULE_H

#include "ccm/ccm_configC.h"

#include "tao/x11/object.h"

#include "ace/Time_Value.h"

#include <memory>

#include "exf/deployment/core/ciaox11_exf_core_export.h"

namespace CIAOX11
{
  namespace ExF
  {
    // boolean value; by default assumed to be true when using the ExF container installation handler
    const std::string CREATE_EXECUTION_SCHEDULER = "nl.remedy.it.Axcioma.ExF.Scheduler.CREATE";

    // boolean value; by default assumed to be false in the context of ExF component handler
    // explicitly set to true for connector executor locaters generated with ExF support
    const std::string NO_SCHEDULING_LANE = "nl.remedy.it.Axcioma.ExF.SchedulingLane.DO_NOT_OPEN";
    // config value id for reference value for component instance
    const std::string SCHEDULING_LANE_REF = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Reference";

    // string value; threading policy for non-exclusive component lanes
    const std::string SCHEDULER_THREAD_POLICY = "nl.remedy.it.Axcioma.ExF.Scheduler.Thread.Policy";
    const std::string SCHEDULER_THREAD_SINGLE = "Single"; // default
    const std::string SCHEDULER_THREAD_MULTI = "Multi";   // static thread pool
    const std::string SCHEDULER_THREAD_DYNAMIC = "Dynamic";   // dynamic thread pool
    // uint16_t value; (minimum) size of (dynamic) thread pool
    const std::string SCHEDULER_THREAD_COUNT = "nl.remedy.it.Axcioma.ExF.Scheduler.Thread.Count";
    // uint16_t value; maximum size of dynamic thread pool
    const std::string SCHEDULER_THREAD_MAXCOUNT = "nl.remedy.it.Axcioma.ExF.Scheduler.Thread.MaxCount";

    // string value; default queuing policy for scheduler/scheduling lanes
    const std::string SCHEDULER_QUEUE_POLICY = "nl.remedy.it.Axcioma.ExF.Scheduler.Queue.Policy";
    const std::string SCHEDULER_QUEUE_FIFO = "FIFO";
    const std::string SCHEDULER_QUEUE_LIFO = "LIFO";

    const std::string SCHEDULING_LANE_DISPATCH_POLICY = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Dispatch.Policy";
    const std::string SCHEDULING_LANE_EXCLUSIVE_DISPATCH = "EXCLUSIVE"; // separate (single threaded) dispatcher for executing component executors
    const std::string SCHEDULING_LANE_GROUPED_DISPATCH = "GROUPED"; // shared (single or multi threaded) dispatcher for grouped component executors
    // any other value or missing == non-exclusive (default)

    // string value; number of concurrent events that maybe be dispatched on a component
    const std::string SCHEDULING_LANE_DISPATCH_CONCURRENT = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Dispatch.Concurrent";

    // string value; queuing policy for EXCLUSIVE and GROUPED scheduling lanes
    const std::string SCHEDULING_LANE_QUEUE_POLICY = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Queue.Policy";

    // string value; group ID for GROUPED scheduling lanes
    const std::string SCHEDULING_LANE_GROUP_ID = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Group";

    // these properties can be used to define defaults at a scheduler level or specific settings
    // for a single dispatch group (specified with every member component instance)
    // string value; threading policy for non-exclusive component lanes
    const std::string SCHEDULING_LANE_THREAD_POLICY = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Thread.Policy";
    // uint16_t value; (minimum) size of (dynamic) thread pool
    const std::string SCHEDULING_LANE_THREAD_COUNT = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Thread.Count";
    // uint16_t value; maximum size of dynamic thread pool
    const std::string SCHEDULING_LANE_THREAD_MAXCOUNT = "nl.remedy.it.Axcioma.ExF.SchedulingLane.Thread.MaxCount";

    // uint16_t; 0-255
    const std::string SCHEDULING_PRIORITY = "nl.remedy.it.Axcioma.ExF.Priority";
    // string
    const std::string SCHEDULING_DEADLINE_TYPE = "nl.remedy.it.Axcioma.ExF.Deadline.Type";
    const std::string SCHEDULING_DEADLINE_EXPIRE = "EXPIRE";    // no fault; only cancels executor
    const std::string SCHEDULING_DEADLINE_SOFT = "SOFT";        // reported fault; cancels executor but no attempt to stop running executor
    const std::string SCHEDULING_DEADLINE_HARD = "HARD";        // reported fault; cancels executor and attempts to stop running executor
    // any other value or missing ==  DLT_NONE
    // string; relative time as 999999999tt
    // where '9' is digit; range for number is 0 - std::numeric_limits<uint32_t>::max ()
    // 'tt' is time unit 'ns' == nanosec, 'us' == microsec, 'ms' == millisec 's' == sec, 'm' == minutes or 'h' == hours
    const std::string SCHEDULING_DEADLINE_TIME = "nl.remedy.it.Axcioma.ExF.Deadline.Time";

    /**
     * The priority specifies the scheduling priority to be used for
     * the execution task instantiated for this event by the execution
     * queue's scheduling policy
     */
    using Priority = uint16_t;

    using Count = uint32_t;

    enum class CancellationType : uint32_t
    {
      CT_TIMEOUT,   // deadline expiration
      CT_SHUTDOWN   // scheduler shutdown
    };

    enum class DeadlineType : uint32_t
    {
      DLT_NONE,     // no deadline defined
      DLT_EXPIRE,   // expiration (no fault; dequeued; no interrupt; allowed)
      DLT_SOFT,     // soft deadline (report; dequeued; no interrupt; not intended)
      DLT_HARD      // hard deadline (report; dequeued; interrupt; not allowed)
    };

    /**
     * The deadline specifies the deadline time and type to
     * be applied to the message object. The deadline
     * time is a relative time value (initially; in a dispatch
     * task this has been converted to absolute time) specifying
     * the maximum duration (or latest execution time) of the
     * execution of the executor object (after receiving).
     * The deadline type specifies whether the deadline time
     * should be interpreted/handled as an expiration time or
     * a hard or soft limit.
     * In case of an expiration time deadline violations are not
     * reported as faults and any running execution is allowed to
     * continue.
     * In case of a soft deadline violations should be
     * reported/logged but execution is allowed to continue
     * unaltered. In case of a hard deadline violations should
     * cause cancellation/termination of execution as well as
     * violation reports.
     * In all cases undispatched executors are cancelled.
     */
    struct Deadline
    {
      ACE_Time_Value  deadline_time_ {0};  // relative time
      DeadlineType    deadline_type_ {DeadlineType::DLT_NONE};
    };

    /**
     * The ExF settings for a event
     */
    struct Settings
    {
      Priority priority_ {};
      Deadline deadline_ {};
    };

    enum class SchedulerResult : uint32_t
    {
       SOK,         // operation successfully completed
       STIMEOUT,    // operation timed out
       SINTERRUPT,  // scheduler deactivated or pulsed
       SFAILED      // scheduler operation failed
    };

    /**
     * @class Executor
     *
     * @brief A class implementing an executor for an encapsulated
     *        component event.
     *
     */
    class CIAOX11_EXF_CORE_Export Executor
    {
    public:
      using ref_type = std::unique_ptr<Executor>;

      Executor () = default;
      Executor (ExF::Settings settings)
       : settings_ (std::move(settings)) {}
      virtual ~Executor () = default;

      /**
       * Execute the required operation for the encapsulated event.
       * This method should never throw an exception.
       */
      virtual void execute () noexcept(true) = 0;

      /**
       * Finishes the operation for the encapsulated event after
       * execution (for example sending reply).
       * This is not called if the operation is cancelled before
       * returning from execution.
       * This method should never throw an exception.
       */
      virtual void finish () noexcept(true) = 0;

      /**
       * Cancel the encapsulated event.
       * This does *not* cancel any running operations.
       * This method should never throw an exception.
       */
      virtual void cancel (CancellationType ctyp) noexcept(true) = 0;

      /**
       * Returns the id of the event handled by this executor.
       * This method should never throw an exception.
       */
      virtual const std::string& event_id () const noexcept(true) = 0;

      ExF::Priority priority () const { return this->settings_.priority_; }
      const ExF::Deadline& deadline () const { return this->settings_.deadline_; }

    protected:
      void set_priority_i (ExF::Priority prio) noexcept(true)
      { this->settings_.priority_ = prio; }

      void set_deadline_i (ExF::Deadline dl) noexcept(true)
      { this->settings_.deadline_ = std::move(dl); }

    private:
      Executor (const Executor&) = delete;
      Executor (Executor&&) = delete;
      Executor& operator= (const Executor&) = delete;
      Executor& operator= (Executor&&) = delete;
      ExF::Settings settings_ {};
    };

    /**
     * @class SchedulingLane
     *
     * @brief A class implementing a scheduling lane for one
     *        or more components (depending on configuration).
     *        A scheduling lane incorporates queuing facilities
     *        and dispatching facilities.
     *
     * This class derives from CORBA::LocalObject because we
     * need to be able to insert it's reference into a CORBA::Any
     * to pass it on as part of a connecion configuration.
     */
    class CIAOX11_EXF_CORE_Export SchedulingLane
      : public ::CORBA::LocalObject
    {
    public:
      ~SchedulingLane () override = default;

      virtual ExF::Count trafic_count () = 0;

      virtual bool closed () = 0;

      virtual void close () = 0;

      /**
       * Submit an executor instance in the lane for processing.
       * QOK is returned if the operation succeeded.
       * QTIMEOUT is returned if the message could not be submitted
       *          within the specified timeout period.
       * QINTERRUPT is returned if the lane was closed or pulsed.
       */
      virtual ExF::SchedulerResult submit (
          std::unique_ptr<ExF::Executor>&& exec) = 0;
    };

    /**
     * @class Scheduler
     *
     * @brief A class implementing a component execution scheduler.
     *
     */
    class CIAOX11_EXF_CORE_Export Scheduler
    {
    public:
      using ref_type = std::shared_ptr<Scheduler>;

      virtual ~Scheduler () = default;

      /**
       * Open (allocate) a scheduling lane for the component
       * instance taking the provided option list into account
       * (which could provide settings like scheduling and
       *  dispatching policies, low water mark, high water mark,
       *  initial size, maximum size, etc.).
       * In case a scheduling lane was previously opened for the
       * component the existing lane is returned.
       * QOK is returned when a lane has been opened for the
       *     component instance.
       * QFAILED is returned if opening the lane did not succeed.
       */
      virtual ExF::SchedulerResult open_scheduling_lane (
          const std::string& instance_id,
          const Components::ConfigValues& cfg,
          ::IDL::traits<ExF::SchedulingLane>::ref_type& lane) = 0;

      /**
       * Find an opened scheduling lane for the component instance.
       * QOK is returned when an opened lane has been found.
       * QFAILED is returned if no open lane could be found.
       */
      virtual ExF::SchedulerResult find_scheduling_lane (
          const std::string& instance_id,
          ::IDL::traits<ExF::SchedulingLane>::ref_type& lane) = 0;

      /**
       * Close a scheduling lane for a component instance.
       * QOK is returned when a lane has been closed for the
       *     component instance.
       * QFAILED is returned if no open lane could be found.
       */
      virtual ExF::SchedulerResult close_scheduling_lane (
          const std::string& instance_id) = 0;

      /**
       * Close the scheduler.
       */
      virtual void close () = 0;

      /**
       * Create a scheduler instance.
       */
      static ref_type create_instance (
          const Components::ConfigValues& cfg);

      static const std::string ServiceName;
    };

  } /* ExF */
} /* CIAOX11 */

#endif /* CIAOX11_EXF_SCHEDULE_H */
