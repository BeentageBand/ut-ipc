#=======================================================================================#
# ipc_gtest_worker_make.mk
#=======================================================================================#
#  Created on: Oct 3, 2015
#      Author: puch
#=======================================================================================#

#=======================================================================================#
# DEFINE PACKAGE RULE
#=======================================================================================#
define $(_flavor_)_$(_feat_)_MAKE
#=======================================================================================#
# OBJECTS DIRECTORY
# e.g: 
#     $(_flavor_)_$(_feat_)_src_dir=pk_module_N_code/_src
#     or
#     $(_flavor_)_$(_feat_)_src_dir=_src
#=======================================================================================#
$(_flavor_)_$(_feat_)_inc=ipc_gtest_worker.h ipc_gtest_worker_evs.h

#=======================================================================================#
# BIN REQUISITES
#=======================================================================================#

##
 # Object Requisites
 # e.g: $(_flavor_)_$(_feat_)_lib_objs=$($(_flavor_)_OBJ_DIR)/my_lib_obj$(_obj_ext_) \
 ##
$(_flavor_)_$(_feat_)_lib_objs=ipc_gtest_worker

##
 # Target Binary
 # e.g: $(_flavor_)_$(_feat_)_lib=my_lib
 ##
$(_flavor_)_$(_feat_)_lib=ipc_gtest_worker
#=======================================================================================#
# END PACKAGE RULE
#=======================================================================================#
endef
#=======================================================================================#
# LOCAL VARIABLES
#=======================================================================================#

#=======================================================================================#
# LOCAL DEFINES 
#=======================================================================================#

#=======================================================================================#
# LOCAL DEFINE EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# LOCAL RULES EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# INCLUDE PK PROJECT UTILITY
#=======================================================================================#
include $(PROJ_MAK_DIR)/epilog.mk
#=======================================================================================#
# ipc_gtest_worker_make.mk
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#
