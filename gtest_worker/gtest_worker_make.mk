define $(_flavor_)_$(_feat_)_MAKE

$(_flavor_)_$(_feat_)_inc=gtest_worker.h gtest_worker_ext.h

$(_flavor_)_$(_feat_)_lib_objs=gtest_worker

$(_flavor_)_$(_feat_)_lib=gtest_worker

endef

include $(PROJ_MAK_DIR)/epilog.mk
