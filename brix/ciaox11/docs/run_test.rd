
= BRIX11 run test command

== Collection

ciaox11

== Usage

  brix11 run test [options] [TEST [test-options]]|[-- test-options]

=== options

  TEST := Path to project folder or test script (extension guessed if not supplied).
          Default script name = 'run_test.pl'
  (any test-options will be passed unchecked to the script)

      --program=TOOL               Use TOOL to execute test script.
                                   Default: guessed from extension (supported: .pl .sh .rb .py).
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

Executes a test runner script.

== Example

$ brix11 run test

Executes the runner script 'run_test.pl' in the current directory using it's default runner tool
(perl) without arguments.

$ brix11 run test -- -debug

Executes the runner script 'run_test.pl' in the current directory  using it's default runner tool
(perl) with argument '-debug'.

$ brix11 run test --program sandbox my_test.pl -debug

Executes the runner script 'my_test.pl' in the current directory using the tool 'sandbox' with
argument '-debug'.

$ brix11 run test --debug

Executes the runner script 'run_test.pl' in the current directory using the debug deployment
environment.

$ brix11 run test --debug -- -debug

Executes the runner script 'run_test.pl' in the current directory using the debug deployment
environment with argument '-debug' passed to the runner script 'run_test.pl'.
