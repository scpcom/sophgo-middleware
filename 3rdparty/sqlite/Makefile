SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

ifeq ($(SDK_VER), 32bit)
SQLITE_TARGET_ARCH = arm-linux
else ifeq ($(SDK_VER), 64bit)
SQLITE_TARGET_ARCH = aarch64-linux
else ifeq ($(SDK_VER), glibc_riscv64)
SQLITE_TARGET_ARCH = riscv64-linux
else ifeq ($(SDK_VER), musl_riscv64)
SQLITE_TARGET_ARCH = riscv64-linux
else
$(error $(red)SDK_VER is invalid$(reset))
endif

SQLITE_CMAKE_ENV = \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

.PHONY : clean all
all : $(TRD_BUILD_OPTIONAL_MODULE)

$(TRD_LIB_PATH)/libsqlite3.a:
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/sqlite/output
	@cd $(TRD_MOD_PATH)/sqlite ; $(SQLITE_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/sqlite/output ./configure --host=$(SQLITE_TARGET_ARCH) --disable-tcl
	@cd $(TRD_MOD_PATH)/sqlite ; $(SQLITE_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/sqlite/output make install
	@tar -C $(TRD_TMP_PATH)/sqlite/output/usr/local -czf $(TRD_TAR_PATH)/sqlite3.tar.gz bin include lib
	@rsync -avpPxH $(TRD_TMP_PATH)/sqlite/output/usr/local/include/ $(TRD_INCLUDE_PATH)/
	@cp -p $(TRD_TMP_PATH)/sqlite/output/usr/local/lib/libsqlite3*.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/sqlite/output/usr/local/lib/libsqlite3*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libsqlite3.a

clean:
	@cd $(TRD_MOD_PATH)/sqlite ; [ ! -e Makefile ] || $(SQLITE_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/sqlite/output make distclean
	@rm -f $(TRD_LIB_PATH)/libsqlite3.a
	@rm -f $(TRD_LIB_PATH)/libsqlite3*.so*
	@rm -f $(TRD_TAR_PATH)/sqlite3.tar.gz
	@rm -rf $(TRD_TMP_PATH)/sqlite

-include $(DEPS)
