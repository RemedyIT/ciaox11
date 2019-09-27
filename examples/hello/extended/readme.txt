This example follows the filosophy of AXCIOMA (UCM).
This means that the there are four 'parts' in which an application could be devided:

1. AXCIOMA concept: 'DATA IDL' (directory 'base' in this example)
   User defined IDL. Declaration of data types, interfaces etc.
   Only the stub library of this IDL is created
2. AXCIOMA concept: 'Interaction patterns' (directory 'patterns' in this example)
   Will compile the IDL from the base directory, generating
   all files needed for certain interaction patterns which are needed by the
   user defined component, like the asynchronous request/reply interaction pattern.
   The lem stub is needed here as a base for the different patterns. In this example,
   the user defined components just need the lem stub.
   The libraries created in this directory can be used by the user defined
   components as well as the implementation libraries of the interaction patterns.
   In this example this is just the lem stub.
   This directory does *not* contain any implementation specific IDL/code.
3. AXCIOMA concept: 'Implementation of Interaction Patterns' (directory 'connectors' in this example)
   This directory contains the implementation of the interaction patterns. This
   directory typically only contains MPC file (s); the implementation can be
   created by the RIDL compiler.
4. AXCIOMA concept: 'User defined components' (directory 'components' in this example)
   These components may only use libraries from the 'patterns' directory.
   User defined components should not be linked to an implementation of an
   interaction pattern in any way!

All this makes sure that the implementation of a certain pattern can be developed
separately from the user defined components.
The decision which implementation of an interaction pattern is used is a
deployment decision and *not* a development decision.

Since this example only contains one interaction pattern (synchronous request/reply), it
might be worth taking a look at an example, using at least two interaction patterns.
The connectors/ami4ccm/examples directory contains a simple and an extended example,
using two interaction patterns (synchronous and asynchronous request/reply). See
the readme in this directory for more info.

The directory structure in this example in somewhat different from the rest
of the CIAOX11 examples/tests. Therefor the MPC files will be a bit different
from the rest. Please have a look at the 'basic' hello example.
