Tests the filter attribute of the DDS4CCM DDS_Get and DDS_Listen basic ports
----------------------------------------------------------------------------

Using the common filter receiver template class to run the test and checks
(see dds4ccm/tests/filters/common/read_get/receiver)

The receiver uses two interface of the DDS4CCM Event connector:
1. the Getter interface of the DDS_Get basic port
2. the Reader interface of the DDS_Listen basic port


Query on the DDS_Get basic port
( (iteration > %0) AND (iteration < %1) )

Query on the DDS_Listen basic port
( (iteration < %0) OR (iteration > %1) )

The maximum number of keys is set to 5 while the maximum number of iterations per
key is set to 15.

The test itself consists of four runs:

Run 1
-----
Parameter %0 is set to 6 and
Parameter %1 is set to 9

During this run, the receiver invokes:
 - get_one on the Getter of the DDS_Get port
 - read_all on the Reader of the DDS_Listen port

Run 2
-----
Parameter %0 is set to 4 and
Parameter %1 is set to 14

During this run, the receiver invokes:
 - get_many on the Getter of the DDS_Get port
 - read_one_all on the Reader of the DDS_Listen port

Run 3
-----
Parameter %0 is set to 4 and
Parameter %1 is set to 15

During this run, the receiver invokes:
 - read_one_last on the Reader of the DDS_Listen port
 - read_all on the Reader of the DDS_Listen port

Run 4
-----
The filter cannot be reset in this case. To receive all samples on the Getter,
the parameters are set to:
Parameter %0 is set to 0 and
Parameter %1 is set to 15

During this run, the receiver invokes:
 - get_many on the Getter of the DDS_Get port
 - read_all on the Reader of the DDS_Listen port

Please have a look at the implementation of the receiver to have an insight of how
many samples should be received during each run.

Both the InternalError and NonChangeable exceptions are tested within the common
receiver template class for this test.
