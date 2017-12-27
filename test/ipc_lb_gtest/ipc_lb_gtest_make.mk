define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=
$(_flavor_)_$(_feat_)_bin_objs=\
ipc_lb_gtest \
ipc_gtest \
mailbox_gtest \
mail_gtest \
publisher_gtest \
dbg_log_gtest \

$(_flavor_)_$(_feat_)_bin_libs=\
dbg_log \
gtest_task \
ipc_gtest_worker \
gtest \
ipc \
cobject \

$(_flavor_)_$(_feat_)_bin=ipc_gtest
endef

include $(PROJ_MAK_DIR)/epilog.mk
