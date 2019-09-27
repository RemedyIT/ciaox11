Like the ../hello_extended example, this example also follows the AXCIOMA
filosophy but hasn't devided that into separate directories. The concepts
stay the same only they are grouped together in MPC files.

'base/hello_simple.mpc' contains the generation and the compilation of the stub
('base' in the extended example), the generation and the compilation
of the lem stub ('patterns/hello_extended_srr.mpc' in the extended example),
the generation and compilation of the AMI4CCM stub
('patterns/hello_extended_arr.mpc' in the extended example) and finally the
generation and compilation of the skeleton ('connectors/hello_extended_skel.mpc'
in the extended example).
The implementation of the AMI4CCM connector and CORBA4CCM connector are put in
separate directories in this example (ami_connector, corba_connector respectively).
The two user defined components each have their own directory.
