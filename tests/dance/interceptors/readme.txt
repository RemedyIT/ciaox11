DAnCEX11 Locality Manager interception test.

In order to test interception points in the DAnCEX11 locality manager,
we need two components to be deployed. Therefor this test is located
here.

This test deploys two sender components and one receiver component one two nodes
(the 'Sender' and 'Receiver' nodes). This means that two locality managers are
spawned.
Besides a base directory, a 'sender', a 'receiver' and a 'descriptors' directory,
this test also contains a 'interceptor' directory. This directory contains the
interceptor library. This library is loaded twice: once by the 'Sender' locality
manager and once by the 'Receiver' locality manager.
The interceptor test code distinguish between the two.

The following interception points are tested in the interceptor library:

- configure
- preprocess_plan
- pre_install
- post_install
- post_endpoint_reference
- pre_connect
- post_connect
- pre_disconnect
- post_disconnect
- post_configured
- post_activate
- post_passivate
- post_remove
- unexpected_event

The perl script to run the test automatically adds and removes the interceptor
to the locality manager configuration file.

The Sender component executor code is generated and does not contain user-defined code.
