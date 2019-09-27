Tests the query attribute on the Reader interface of the DDS4CCM DDS_StateListen
                           basic port
--------------------------------------------------------------------------------

The sender uses the DDS_Update port, the receiver uses two DDS_StateListen ports
Sender and receiver are using the DDS4CCM state connector.

This test uses the defines, defined in ../qc_common.h. Both the sender and receiver
know exactly how many samples will be written and how much samples the receiver
should receive.

The listeners have the following queries defined:
- listener I : ( (iteration > %0) AND (iteration < %1) )
- listener II: ( (iteration < %0) OR (iteration > %1) )

The parameters %0 and %1 are respectively 10 and 13 in this test.

Listener I will receive samples ONE_BY_ONE.
Listener II will receive samples MANY_BY_MANY.

The sender starts with the creation of the keys with an iteration of 1.
This means that listener I will instantly receive the "on_creation" callbacks.
Listener II will not receive the "on_creation" callback until iteration 11.

Straight after the creation of the keys, the sender will start updating the keys.

Listener I will receive samples with iteration 11 and 12. Only the "on_one_update"
callback should be invoked on Listener I.

Listener II will receive samples with iteration 1,2,3,4,5,6,7,8,9,14, and 15. Only
the "on_many_updates" callback should be invoked on Listener II.

After all samples were written (determined by the defines in qc_common.h), the
sender will remove the keys by invoking "delete_many". Both listeners should receive
the "on_deletion" callback a number of times (number of keys).

The receiver checks the iterations, the number of invocation of "on_creation",
"on_one_update", and "on_deletion" on Listener I.
Besides the number of invocation of "on_creation" and "on_deletion" on Listener II,
the receiver also checks the number of samples received when an "on_many_updates"
callback gets invoked.

The internal error exception will not be tested here since this is already tested
in the query_attrib/read_get test.
