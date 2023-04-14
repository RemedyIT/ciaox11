This test is for the nl.remedy.it.Axcioma.ExF.SchedulingLane.Dispatch.Concurrent flag. By default AXCIOMA provides a single threaded model for each component, only one thread will be scheduled for a specific component instance. Using the the Concurrent flag this can be changed to a specific number of threads.

The test has multiple deployment plans where the Concurrent flag is set to a different value. The receiver component keeps a small bookkeeping how many threads
are active and checks that with the amount is may expect, that value is set as attribute on the receiver component.
