HEADER_OPTION = ARCH=$(CAVAN_TARGET_ARCH) INSTALL_HDR_PATH=$(SYSROOT_PATH)/usr

all:
	$(Q)+make distclean
	$(Q)+make $(HEADER_OPTION) headers_install
