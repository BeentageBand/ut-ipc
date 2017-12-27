PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make

host_GTEST_PATH=$(PROJ_DIR)/support/gtest_fwk/googletest/googletest
linux_GTEST_PATH=$(PROJ_DIR)/support/gtest_fwk/googletest/googletest

define Project_Make

FLAVOR_LIST=linux host
#Flavor
host_build=linux
linux_build=linux

host_PROJ_INC+=\
$(PROJ_DIR:%=%/include) \
include/linux

linux_PROJ_INC+=\
$(PROJ_DIR:%=%/include) \
include/linux

endef

include $(PROJ_MAK_DIR)/project.mk
