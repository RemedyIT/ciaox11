
= BRIX11 run list command

== Collection

taox11

== Usage

  brix11 run list [options] [-- test-options]

=== options

  (any test-options following '--' will be passed on unchecked)

  -l, --list=PATH                  Specifies regression test list to feed auto_run_test.
                                   Default: $TAOX11_ROOT/bin/taox11_tests.lst
  -r, --root=PATH                  Specifies root directory for running the tests.
                                   Default: $TAOX11_BASE_ROOT
      --debug                      Run test using Debug deployment environment (only applicable for msvc/icc builds).
      --release                    Run test using Release deployment environment (only applicable for msvc/icc builds).

  -f, --force                      Force all tasks to run even if their dependencies do not require them to.
                                   Default: off
  -v, --verbose                    Run with increased verbosity level. Repeat to increase more.
                                   Default: 0

  -h, --help                       Show this help message.

_NOTE_

The *--debug* and *--release* switches are only available on Windows platforms and applicable for
build environments utilizing the MSVC or ICC compiler toolsets.


== Description

Executes the 'auto_run_tests' script which will run the tests from the specified list
according to the test-options passed.

== Example

$ brix11 run list

Executes the auto_run_tests script with the default list at the default location.

$ brix11 run list -- -Config ANDROID -s sandbox

Executes the auto_run_tests script with the default list at the default location passing on the
options '-Config ANDROID -s sandbox'.

$ brix11 run list -l mytests.lst -r /home/me/develop

Executes the auto_run_tests script with the list 'mytests.lst' at the location '/home/me/develop'.

$ brix11 run list --debug

Executes the auto_run_tests script with the default list at the default location using the debug
deployment environment.
