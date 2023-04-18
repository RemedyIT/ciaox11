/**
 * @file    dispatch_queue.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Unit test for ciaox11 exf dispatch queue
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11/testlib/ciaox11_testlog.h"
#include "deployment/scheduler/ciaox11_exf_dispatcher.h"

class TestExecutor : public CIAOX11::ExF::Executor
{
public:
  TestExecutor (std::string id) : event_id_ (std::move(id)) {}
  ~TestExecutor () override = default;

  const std::string& event_id () const noexcept(true) override
  { return event_id_; }

  void execute () noexcept(true) override {}
  void finish () noexcept(true) override {}
  void cancel (CIAOX11::ExF::CancellationType /*ctyp*/) noexcept(true) override {}

private:
  std::string const event_id_;
};

using instance_ref = std::shared_ptr<CIAOX11::ExF::Impl::Dispatcher::Instance>;
using task_ref = CIAOX11::ExF::Impl::Dispatcher::DispatchTask::task_ref;

int test_concurrent_1 ()
{
  int retval = 0;

  CIAOX11_TEST_INFO << "test_concurrent_1" << std::endl;

  task_ref dequeue_task;

  // Create a dispatch queue
  CIAOX11::ExF::Impl::Dispatcher::DispatchQueue dp (CIAOX11::ExF::Impl::DispatchQueuePolicy::DQP_FIFO);

  // Create 5 possible component instances, each with a unique name and we allow 1 concurrent request
  instance_ref instance_A = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::Instance> ("A", 1);
  instance_ref instance_B = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::Instance> ("B", 1);
  instance_ref instance_C = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::Instance> ("C", 1);
  instance_ref instance_D = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::Instance> ("D", 1);
  instance_ref instance_E = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::Instance> ("E", 1);

  // Create 5 events
  CIAOX11::ExF::Executor::ref_type exec1 = std::make_unique<TestExecutor> ("1");
  CIAOX11::ExF::Executor::ref_type exec2 = std::make_unique<TestExecutor> ("2");
  CIAOX11::ExF::Executor::ref_type exec3 = std::make_unique<TestExecutor> ("3");
  CIAOX11::ExF::Executor::ref_type exec4 = std::make_unique<TestExecutor> ("4");
  CIAOX11::ExF::Executor::ref_type exec5 = std::make_unique<TestExecutor> ("5");

  // Now create a task where we have one event for each instance
  task_ref dtask1 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec1), instance_A);
  task_ref dtask2 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec2), instance_B);
  task_ref dtask3 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec3), instance_C);
  task_ref dtask4 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec4), instance_D);
  task_ref dtask5 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec5), instance_E);

  // Now enqueue the events all at priority 0
  dp.enqueu (dtask1, 0);
  dp.enqueu (dtask2, 0);
  dp.enqueu (dtask3, 0);
  dp.enqueu (dtask4, 0);
  dp.enqueu (dtask5, 0);

  // Now dequeue the tasks, we should get the same order as inserted
  dp.dequeue (dequeue_task);
  if (dequeue_task->instance_id () != instance_A->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_A->instance_id() << std::endl;
    ++retval;
  }
  dp.dequeue (dequeue_task);
  if (dequeue_task->instance_id () != instance_B->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_B->instance_id() << std::endl;
    ++retval;
  }
  dp.dequeue (dequeue_task);
  if (dequeue_task->instance_id () != instance_C->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_C->instance_id() << std::endl;
    ++retval;
  }
  dp.dequeue (dequeue_task);
  if (dequeue_task->instance_id () != instance_D->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_D->instance_id() << std::endl;
    ++retval;
  }
  dp.dequeue (dequeue_task);
  if (dequeue_task->instance_id () != instance_E->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_E->instance_id() << std::endl;
    ++retval;
  }

  return retval;
}

int test_concurrent_2 ()
{
  int retval = 0;

  CIAOX11_TEST_INFO << "test_concurrent_2" << std::endl;

  task_ref dequeue_task;

  // Create a dispatch queue
  CIAOX11::ExF::Impl::Dispatcher::DispatchQueue dp (CIAOX11::ExF::Impl::DispatchQueuePolicy::DQP_FIFO);

  // Create 2 possible component instances, each with a unique name and we allow 2 concurrent request for each instance
  instance_ref instance_A = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::Instance> ("A", 2);
  instance_ref instance_B = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::Instance> ("B", 2);

  // Create 5 events
  CIAOX11::ExF::Executor::ref_type exec1 = std::make_unique<TestExecutor> ("1");
  CIAOX11::ExF::Executor::ref_type exec2 = std::make_unique<TestExecutor> ("2");
  CIAOX11::ExF::Executor::ref_type exec3 = std::make_unique<TestExecutor> ("3");
  CIAOX11::ExF::Executor::ref_type exec4 = std::make_unique<TestExecutor> ("4");
  CIAOX11::ExF::Executor::ref_type exec5 = std::make_unique<TestExecutor> ("5");

  // Now create a task where we have one event for each instance
  task_ref dtask1 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec1), instance_A);
  task_ref dtask2 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec2), instance_B);
  task_ref dtask3 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec3), instance_A);
  task_ref dtask4 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec4), instance_B);
  task_ref dtask5 = std::make_shared<CIAOX11::ExF::Impl::Dispatcher::DispatchTask> (std::move (exec5), instance_A);

  // Now enqueue the events all at priority 0, first 3 tasks for A, than 2 for B
  dp.enqueu (dtask1, 0);
  dp.enqueu (dtask3, 0);
  dp.enqueu (dtask5, 0);
  dp.enqueu (dtask2, 0);
  dp.enqueu (dtask4, 0);

  // Now dequeue the tasks, we should get first 2 events for A, than 2 events for B, last one event for A (when it is ready with one event)
  if (!dp.dequeue (dequeue_task))
  {
    CIAOX11_TEST_ERROR << "Can't dequeue task" << std::endl;
    ++retval;
  }
  if (dequeue_task->instance_id () != instance_A->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_A->instance_id() << std::endl;
    ++retval;
  }
  if (!dp.dequeue (dequeue_task))
  {
    CIAOX11_TEST_ERROR << "Can't dequeue task" << std::endl;
    ++retval;
  }
  if (dequeue_task->instance_id () != instance_A->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_A->instance_id() << std::endl;
    ++retval;
  }
  if (!dp.dequeue (dequeue_task))
  {
    CIAOX11_TEST_ERROR << "Can't dequeue task" << std::endl;
    ++retval;
  }
  if (dequeue_task->instance_id () != instance_B->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_B->instance_id() << std::endl;
    ++retval;
  }
  if (!dp.dequeue (dequeue_task))
  {
    CIAOX11_TEST_ERROR << "Can't dequeue task" << std::endl;
    ++retval;
  }
  if (dequeue_task->instance_id () != instance_B->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_A->instance_id() << std::endl;
    ++retval;
  }
  // Try to dequeue another task, this should not return true, as all instances are busy
  if (dp.dequeue (dequeue_task))
  {
    CIAOX11_TEST_ERROR << "Dequeue should return false as instances are all busy" << std::endl;
    ++retval;
  }
  // Release instance_A so that it gets another event
  instance_A->release();
  if (!dp.dequeue (dequeue_task))
  {
    CIAOX11_TEST_ERROR << "Can't dequeue task" << std::endl;
    ++retval;
  }
  if (dequeue_task->instance_id () != instance_A->instance_id())
  {
    CIAOX11_TEST_ERROR << "Invalid instance, received " << dequeue_task->instance_id () << " expected " << instance_A->instance_id() << std::endl;
    ++retval;
  }

  return retval;
}

int main(int /*argc*/, char** /*argv[]*/)
{
  int retval = 0;
  try
  {
    retval += test_concurrent_1();

    retval += test_concurrent_2();

    CIAOX11_TEST_INFO << "shutting down..." << std::endl;
  }
  catch (const std::exception& e)
  {
    // X11_FUZZ: disable check_test_log_macros
    CIAOX11_TEST_ERROR << "exception caught: " << e.what () << std::endl;
    // X11_FUZZ: enable check_test_log_macros
    return 1;
  }
  return retval;
}
