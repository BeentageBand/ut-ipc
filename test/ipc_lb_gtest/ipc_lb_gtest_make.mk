define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=

$(_flavor_)_$(_feat_)_bin_objs=\
mail_gtest \
ipc_lb_gtest \
dbg_log_gtest \
ipc_gtest \
publisher_gtest \
#mailbox_gtest \

$(_flavor_)_$(_feat_)_bin_libs=\
cobject \
dbg_log \
gtest_worker \
gtest \
ipc \
ipc_gtest_worker \

$(_flavor_)_$(_feat_)_bin=ipc_gtest
endef

include $(PROJ_MAK_DIR)/epilog.mk
