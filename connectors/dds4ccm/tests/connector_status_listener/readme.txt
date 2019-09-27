
This test uses the common (generic) base/connector idl and libraries (see
$CIAOX11_ROOT/connectors/dds4ccm/tests/common).

Every callback on the connector status listener has its own deployment plan in
the descriptors directory. The perl script runs these plans one by one.

The DDS4CCM context switch will be tested for each callback.

Explanation per plan:

plan_on_deadline_missed
--------------------------------------------------------------------------------
This is a 'sender only' deployment. The sender writes just two samples. Since DDS
expects that the datawriter writes a sample at least every two seconds
(configured in the QOS profile) it will invoke a callback when this restriction
is not met.


plan_on_incompatible_qos
--------------------------------------------------------------------------------
This plan refers to a qos profile which contains incompatible QOS profiles. The
test checks whether the correct profiles are listed in the given status struct.
Since there's no matching of topics, the publication/subscription matched statuses
should not be received. This is checked.


plan_on_inconsistent_topic
--------------------------------------------------------------------------------
Besides the common (generic) topic and connector there should be another topic and
connector created to test this properly. This topic declaration is different from
the common topic declaration. Since both topics have the same name in the plan, the
on_inconsistent_topic callback should be received in both the sender and receiver
component.
Since there's no matching of topics, the publication/subscription matched statuses
should not be received. This is checked.


plan_on_sample_rejected
--------------------------------------------------------------------------------
This plan refers to a QOS which has a maximum of one instance on the receiver side.
The sender component writes samples for two instances. Therefor the samples of the
second instance are rejected in the receiver. The test checks how many times this
callback is received and produces an error if it is not what was expected.
Since there's a matching of topics, the publication/subscription matched statuses
should have been received as well. This is checked.


plan_on_unexpected_status
--------------------------------------------------------------------------------
The following unexpected statuses are checked:
- on_publication_matched
- on_subscription_matched
- on_liveliness_lost
- on_liveliness_changed
- on_reliable_writer_cache_changed
- on_reliable_reader_activity_changed

The datawriter and datareader are set to 'reliable' in the QOS. The sender starts
writing samples and the receiver reads a limited amount of samples; it then just
stops reading samples. This will trigger an 'on_liveliness_lost', an
'on_reliable_reader_activity_changed', and an 'on_reliable_writer_cache_changed'
callback in the sender. The receiver will receive a 'on_liveliness_changed'
callback at startup.

Both on_publication_matched and on_subscription_matched are tested during all other
deployments.
