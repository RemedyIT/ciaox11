
= BRIX11 apc make command

== Collection

ciaox11

== Usage

  brix11 apc make [options] [-- make-options]

=== options

  -c, --clean                      Clean project only.
  -r, --rebuild                    Clean and than build project.
      --debug                      Debug mode. Default: Off
      --release                    Release mode. Default: On

  -f, --force                      Force all tasks to run even if their dependencies do not require them to.
                                   Default: off
  -v, --verbose                    Run with increased verbosity level. Repeat to increase more.
                                   Default: 0

  -h, --help                       Show this help message.

=== Environment variables

In order to control the number of cpu's to use with Visual Studio solutions, the environment variable
BRIX11_NUMBER_OF_PROCESSORS can be set to overrule the system variable NUMBER_OF_PROCESSORS.
If BRIX11_NUMBER_OF_PROCESSORS is higher then NUMBER_OF_PROCESSORS, NUMBER_OF_PROCESSORS is used
to set the /maxcpucount.

== Description

For a project generated with axp prepare this command will run the project type specific build (make) tool to build
(make) the project artifacts like IDL generated code, source code compilations and linked library and executable binaries.

== Example

$ brix11 apc make

Runs the project type specific build (make) tool for the entire project from the project's root folder.

$ brix11 apc make -r

Rebuilds the entire project by first running the project type specific build (make) tool in 'cleanup' mode
and than rerun it to build all artifacts again.
