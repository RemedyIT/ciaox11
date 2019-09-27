
= BRIX11 apc prepare command

== Collection

ciaox11

== Usage

  brix11 apc prepare [options] [-- [mwc_options]]

  OR

  brix11 axp prepare [options] [-- [mwc_options]]

=== options

   -m, --mpc                       Don't remove the generated mpc files.
                                   Default: MPC files are removed after the make files are generated

   -f, --force                     Force all tasks to run even if their dependencies do not require them to.
                                   Default: off

   -v, --verbose                   Run with increased verbosity level. Repeat to increase more.
                                   Default: 0

   -h, --help                      Show this help message.

== Description

Generates all project files for an AXCIOMA project starting in the root directory of a project which
should be marked by the root recipe file ('aprc'). The command will look for this file searching from
the directory where the command is executed working it's way 'back' to the root directory.
After finding the project root the first step of this command is using the recipes from the recipe files
(*.aprc), located in the sub directories of this project, to map the dependencies between the different
sub projects and to determine the nature of the different types of recipes (f.i. data, component, connector).
Next, the command will generate all required project build files (makefiles, MSVC solution files or other
depending on the specified project type) and possibly any auto-generated IDL files.
Please see the AXCIOMA Project Control (APC) tool documentation for more information on defining recipes
and project setup.

This command makes use of the MPC project generation tool to generate the required project build files and
generates MPC definition files as intermediate artifacts. By default these files are removed after having
generated the project files using MPC. By adding the '-m|--mpc' this default behavior can be overruled.

== Example

$ brix11 apc prepare

Generate project files for project in the current dir

$ brix11 axp prepare -m

Generate project files for project in the current dir
and don't remove the generated mpc files.

$ brix11 axp prepare -m -- -workers 3

Generate project files for project in the current dir,
don't remove the generated mpc files and
use the MPC option '-workers 3' for the number of child processes
