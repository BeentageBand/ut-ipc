PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make

host_GTEST_PATH=$(PROJ_DIR)/support/gtest_fwk/googletest
linux_GTEST_PATH=$(PROJ_DIR)/support/gtest_fwk/googletest

define Project_Make


FLAVOR_LIST=host
#Flavor
linux_build=linux

linux_PROJ_INC+=\
include \
include/linux

host_PROJ_INC+=\
include \
include/linux
endef

include $(PROJ_MAK_DIR)/project.mk
