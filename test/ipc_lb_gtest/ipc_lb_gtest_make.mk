define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=

$(_flavor_)_$(_feat_)_bin_objs=\
dbg_log_gtest \
ipc_gtest \
ipc_lb_gtest \
mail_gtest \
mailbox_gtest \
publisher_gtest \

$(_flavor_)_$(_feat_)_bin_libs=\
cobject \
dbg_log \
gtest_task \
gtest \
ipc \
ipc_gtest_worker \

$(_flavor_)_$(_feat_)_bin=ipc_gtest
endef

include $(PROJ_MAK_DIR)/epilog.mk
