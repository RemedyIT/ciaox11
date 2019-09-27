Like the CIAOX11 extended hello example, this example also follows the filosophy
of AXCIOMA.
The four 'parts':

1. AXCIOMA concept: 'DATA IDL' (directory 'base' in this example)
   Same concepts as the CIAOX11 extended hello example.
2. AXIOMA concept: 'Interaction patterns' (directory 'patterns' in this example)
   Will compile the IDL from the base directory, generating
   all files needed for certain interaction patterns which are needed by the
   user defined component(s), like the asynchronous request/reply pattern.
   This directory contains two MPC files, one for the synchronous request/reply
   pattern (*_srr.mpc) and one for the asynchronous request/reply pattern
   (*_arr.mpc). The *_srr.mpc makes sure that the lem IDL is generated and that the
   lem stub library is compiled; the *_arr.mpc makes sure that the AMI IDL (*A.idl)
   is generated and that the stub library of this IDL will be compiled. Both
   libraries are used by the sender component while the receiver component only
   needs the lem stub library since the receiver does not use the asynchronous
   request/reply interaction pattern.
   This directory does *not* contain any implementation specific IDL/code.
3. AXIOMA concept: 'Implementation of Interaction Patterns' (directory 'connectors' in this example)
   This directory contains the implementation of the interaction patterns. Besides a
   synchronous request/reply, this example also needs an implementation of the
   asynchronous request/reply pattern.
   Therefor this directory contains two mpc files; one for each pattern. A third
   MPC file is responsible for generating and compiling the (CORBA)skeleton
   library since both implementations need it.
4. AXCIOMA concept: 'User defined components' (directory 'components' in this example)
   User defined component. These component may only use libraries
   from the 'patterns' directory. User defined components should not be
   linked to an implementation of an interaction pattern in any way! Both sender and
   receiver will link against the lem stub library while the sender also links
   against the AMI4CCM stub library.

All this makes sure that the implementation of a certain pattern can be developed
separately from the user defined components.
The decision which implementation of an interaction pattern is used is a
deployment decision and *not* a development decision.

The directory structure in this example in somewhat different from the rest
of the AMI4CCM examples/tests. Therefor the MPC files will be a bit different
from the rest. Please have a look at the 'simple' hello example as well.
