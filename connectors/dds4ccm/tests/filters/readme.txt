Filter tests

There are two way to apply a filter (a query) in DDS4CCM:
1. Via the query attribute on the Reader interface
2. Via the filter attribute on the various DDS4CCM basic ports.

See dds4ccm/idl/ccm_dds.idl for more details.

This directory will test both situations for each basic port.

Since the publishing components (the senders) do need the same functionality for
both the query attribute tests and filter attributes tests, the sender components
are placed in the common directory of this test.
The common directory also contains common checks for some of the receiver components.

This directory contains the following tests. For more details about the test itself,
please see the readme files in each individual directory.



Test for the Query attribute on the Reader interface (query_attrib directory)
-----------------------------------------------------------------------------
** read_get **

**** Event ****
Tests the query attribute on the Reader interface of the DDS_Get basic port
and Reader interface of DDS_Listen basic port. The latter is choosen because
the DDS4CCM Event connector has no DDS_Read basic port.

**** State ****
TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO

** listeners **

**** Event ****
Test the query attribute on the Reader interface of the DDS_Listen basic port.

**** State ****
Test the query attribute on the Reader interface of the DDS_StateListen basic port.



Test for the Filter attribute on the DDS4CCM basic ports (filter_attrib directory)
----------------------------------------------------------------------------------
** read_get **

**** Event ****
Tests the filter attribute on de DDS_Get basic port and Reader interface of
DDS_Listen basic port. The latter is choosen because the DDS4CCM connector
has no DDS_Read basic port.

**** State ****
TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO

** listeners **

**** Event ****
TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
Test the filter attribute on the DDS_Listen basic port.

**** State ****
TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
Test the filter attribute on the DDS_StateListen basic port.
