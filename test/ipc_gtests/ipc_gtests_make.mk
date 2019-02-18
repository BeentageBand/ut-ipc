define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=

$(_flavor_)_$(_feat_)_bin_objs=\
	ipc_friends \
	ipc_gtest \
	ipc_mail_gtest \
	ipc_mailbox_gtest \
	ipc_publisher_gtest \
	ipc_thread_gtest \
	ipc_worker_gtest \

$(_flavor_)_$(_feat_)_bin_libs=\
	ccipc \
	dbg_log \
	gtest \
	gmock \
	gmock_main \

$(_flavor_)_$(_feat_)_bin=ipc_gtests

endef

-include $(PROJ_MAK_DIR)/epilog.mk
