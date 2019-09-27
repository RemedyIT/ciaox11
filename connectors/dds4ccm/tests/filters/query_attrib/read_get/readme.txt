Tests the query attribute on the Reader interface of the DDS4CCM DDS_Get and
DDS_Listen basic ports
--------------------------------------------------------------------------------

Using the common filter receiver template class to run the test and checks
(see dds4ccm/tests/filters/common/read_get/receiver)

The receiver uses two interfaces of the DDS4CCM Event connector:
1. the Getter interface of the DDS_Get basic port
2. the Reader interface of the DDS_Listen basic port

The deployment plan contains connections to the Reader of the DDS_Listen port
and to the Reader and Getter of the DDS_Get port. The Reader of the DDS_Get port
is only connected in order to be able to define a QueryFilter.

The query on Reader of the DDS_Get port is different from the Reader on the
DDS_Listen port.

Query on the Reader interface of the DDS_Get basic port
( (iteration > %0) AND (iteration < %1) )

Query on the Reader interface of the DDS_Listen basic port
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
Filter is reset to an empty filter.

During this run, the receiver invokes:
 - get_many on the Getter of the DDS_Get port
 - read_all on the Reader of the DDS_Listen port

Please have a look at the implementation of the receiver to have an insight of how
many samples should be received during each run.

The common receiver template class will also test the InternalError exception.
The internal error exception will be thrown when DDS reports an error whilst
setting the query. DDS4CCM does NOT perform any checks on the query and its
parameters.
