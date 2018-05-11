###############################################################################
################### MOOSE Application Standard Makefile #######################
###############################################################################
#
# Optional Environment variables
# MOOSE_DIR        - Root directory of the MOOSE project 
# HERD_TRUNK_DIR   - Location of the HERD repository (or parent directory)
# FRAMEWORK_DIR    - Location of the MOOSE framework
#
###############################################################################
MOOSE_DIR          ?= $(shell dirname `pwd`)/moose
HERD_TRUNK_DIR     ?= $(shell dirname `pwd`)
FRAMEWORK_DIR      ?= $(MOOSE_DIR)/framework
###############################################################################
CURRENT_DIR        := $(shell pwd)

# framework
include $(FRAMEWORK_DIR)/build.mk
include $(FRAMEWORK_DIR)/moose.mk

################################## MODULES ####################################
####CHEMICAL_REACTIONS   := yes
#HEAT_CONDUCTION      := yes
#MISC                 := yes
#SOLID_MECHANICS      := yes
#TENSOR_MECHANICS     := yes
PHASE_FIELD           := yes
#LEVEL_SET             := yes
include $(MOOSE_DIR)/modules/modules.mk

# modules from bison:
####SOLID_MECHANICS   := yes
####LINEAR_ELASTICITY := yes
####CONTACT           := yes
####HEAT_CONDUCTION   := yes
####WATER_STEAM_EOS   := yes
####MISC              := yes
####include           $(MOOSE_DIR)/modules/modules.mk
###############################################################################

# dep apps
####APPLICATION_DIR	   := $(HERD_TRUNK_DIR)/mamba-dev
####APPLICATION_NAME   := mamba-dev
####include            $(FRAMEWORK_DIR)/app.mk
# adding bison...
####APPLICATION_DIR	   := $(HERD_TRUNK_DIR)/bison
####APPLICATION_NAME   := bison
####include            $(FRAMEWORK_DIR)/app.mk
# ...added bison.
APPLICATION_DIR    := $(CURRENT_DIR)
APPLICATION_NAME   := hognose-dev
BUILD_EXEC         := yes
DEP_APPS           := $(shell $(FRAMEWORK_DIR)/scripts/find_dep_apps.py $(APPLICATION_NAME))
include            $(FRAMEWORK_DIR)/app.mk

###############################################################################
# Additional special case targets should be added here
