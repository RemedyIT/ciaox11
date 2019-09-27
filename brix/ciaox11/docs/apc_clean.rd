
= BRIX11 apc clean command

== Collection

ciaox11

== Usage

  brix11 apc clean [options]

  OR

  brix11 axp clean [options]

=== options

   -f, --force                     Force all tasks to run even if their dependencies do not require them to.
                                   Default: off

   -v, --verbose                   Run with increased verbosity level. Repeat to increase more.
                                   Default: 0

   -h, --help                      Show this help message.

== Description

For a project generated with axp prepare this command cleans the project
(using the project type specific 'clean' procedure) and then removes the
generated directories, project files (and mpc files if not removed yet) as
well as any auto-generated IDL files.

== Example

$ brix11 axp clean
