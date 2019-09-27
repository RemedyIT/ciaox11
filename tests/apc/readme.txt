This directory contains tests for several combinations of recipes, recipe-files and settings in recipes.
If there are not used source- or header files or empty directories, this is on purpose!

ext-sync-complex:
test with a lot of data idl files, dependent and independent of each other, in different directories

ext-sync-explicit:
test with explicit base recipes (in data1 dir), combined with implicit base recipes (in data2 dir)

ext-sync-multiple-recipe:
test with 2 component recipes in 2 recipe files in 1 directory and
2 base recipes in 2 recipe files in 1 directory

ext-sync-extra:
test where in receiver component recipe extra sources, headers and include paths are added
components and connector are not using recipe defaults

extended-sync:
test with different dependent and not dependent base idl files in different dirs
Also test of duplicate recipe name

extra-libs-comp:
test for setting extra libpaths, libs and includes in component recipe

extra-libs-project:
test for setting extra libpaths, libs and includes for all components in a project in the projectrecipe

extra-projects:
test with 4 components each setting extra mpc projects or disabling  mpc projects via their recipes

minimal-sync-attr:
test with complex attributes, to check if anytypecode is inserted in the right mpc projects

minimal-sync-data:
idl of receiver component contains also data, so extra stub, must be generated

sync-all-in-one:
In one directory the project recipe file and a recipe file with all the recipes for 2 components, a connector and a explicit base recipe

gen_comp:
test generating component idl files out of component recipes  In the component recipes the ports and attributes are defined in two different ways, one way
as block and one in a condensed way.

