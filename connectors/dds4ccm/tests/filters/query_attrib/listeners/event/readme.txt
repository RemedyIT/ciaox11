Tests the query attribute on the Reader interface of the DDS4CCM DDS_Listen
                           basic port
--------------------------------------------------------------------------------

The sender uses the DDS_Write port, the receiver uses two DDS_Listen ports
Sender and receiver are using the DDS4CCM Event connector.

This test uses the defines, defined in ../qc_common.h. Both the sender and receiver
know exactly how many samples will be written and how much samples the receiver
should receive.

The listener have the following queries defined:
- listener I : ( (iteration > %0) AND (iteration < %1) )
- listener II: ( (iteration < %0) OR (iteration > %1) )

The parameters %0 and %1 are respectively 5 and 10 in this test.

Listener I will receive samples ONE_BY_ONE.
Listener II will receive samples MANY_BY_MANY.

The sender starts writing samples at a certain rate.

Listener I will receive samples with iteration 6,7,8, and 9. Only the "on_one_data"
callback should be invoked on Listener I.

Listener II will receive samples with iteration 1,2,3,4,11,12,13,14 and 15. Only
the "on_many_data" callback should be invoked on Listener II.

The receiver will check each sample whether the correct iteration was
received on the listener. The receiver also checks the total number of
samples received.

The internal error exception will not be tested here since this is already tested
in the query_attrib/read_get test.

