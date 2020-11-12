# -*- Makefile -*-

#----------------------------------------------------------------------------
#       Common Makefile rules for all of CIAOX11
#----------------------------------------------------------------------------

####
#### Required macros for CIAOX11.
####
ifeq ("$(CIAOX11_ROOT)", "")
  $(error CIAOX11_ROOT must be defined!)
endif

####
#### Macro customization.
####

# Turn on symbol versioning. The scheme that we follow is to allow
# applications dependent on libraries, with same version numbers (major,
# minor and beta) to run, but applications with dependencies on libraries
# with different minor or major or beta versions to fail.
#
ifeq (cmd,$(findstring cmd,$(SHELL)))
CIAOX11_MAJOR_VERSION := $(shell awk "/CIAOX11_MAJOR_VERSION/ { print $$3}" ${CIAOX11_ROOT}/ciaox11/versionx11.h)
CIAOX11_MINOR_VERSION := $(shell awk "/CIAOX11_MINOR_VERSION/ { print $$3}" ${CIAOX11_ROOT}/ciaox11/versionx11.h)
CIAOX11_MICRO_VERSION := $(shell awk "/CIAOX11_MICRO_VERSION/ { print $$3}" ${CIAOX11_ROOT}/ciaox11/versionx11.h)
else
CIAOX11_MAJOR_VERSION := $(shell awk '/CIAOX11_MAJOR_VERSION/ { print $$3}' ${CIAOX11_ROOT}/ciaox11/versionx11.h)
CIAOX11_MINOR_VERSION := $(shell awk '/CIAOX11_MINOR_VERSION/ { print $$3}' ${CIAOX11_ROOT}/ciaox11/versionx11.h)
CIAOX11_MICRO_VERSION := $(shell awk '/CIAOX11_MICRO_VERSION/ { print $$3}' ${CIAOX11_ROOT}/ciaox11/versionx11.h)
endif

GNUACE_PROJECT_VERSION = $(CIAOX11_MAJOR_VERSION).$(CIAOX11_MINOR_VERSION).$(CIAOX11_MICRO_VERSION)
