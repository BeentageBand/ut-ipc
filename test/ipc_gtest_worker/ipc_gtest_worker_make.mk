define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=
$(_flavor_)_$(_feat_)_bin_objs=\
ipc_gtest_gworker\
ipc_gworker_friends \

$(_flavor_)_$(_feat_)_bin_libs=\
	ccipc \
	ccposix \
	dbg_log \
	gmock_main \
	gmock \
	gtest \
	gworker \

$(_flavor_)_$(_feat_)_bin=ipc_gtest_gworker
endef

include $(PROJ_MAK_DIR)/epilog.mk
