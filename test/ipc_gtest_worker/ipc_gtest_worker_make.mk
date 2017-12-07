define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=ipc_gtest_worker.h ipc_gtest_worker_evs.h

$(_flavor_)_$(_feat_)_lib_objs=ipc_gtest_worker

$(_flavor_)_$(_feat_)_lib=ipc_gtest_worker
endef

include $(PROJ_MAK_DIR)/epilog.mk
