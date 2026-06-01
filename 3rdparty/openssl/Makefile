SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

SED ?= $(shell which sed || type -p sed) -i -e

ifeq ($(SDK_VER), 32bit)
OPENSSL_TARGET_ARCH = linux-armv4
else ifeq ($(SDK_VER), 64bit)
OPENSSL_TARGET_ARCH = linux-aarch64
else ifeq ($(SDK_VER), glibc_riscv64)
OPENSSL_TARGET_ARCH = linux-generic64 no-asm
else ifeq ($(SDK_VER), musl_riscv64)
OPENSSL_TARGET_ARCH = linux-generic64 no-asm
else
$(error $(red)SDK_VER is invalid$(reset))
endif

OPENSSL_CFLAGS = $(CFLAGS) -g0

ifeq ($(SDK_VER), musl_riscv64)
OPENSSL_CFLAGS += -DOPENSSL_NO_ASYNC
endif

OPENSSL_CFLAGS += -I$(TRD_TMP_PATH)/zlib/output/usr/local/include -L$(TRD_TMP_PATH)/zlib/output/usr/local/lib

OPENSSL_CMAKE_ENV = \
	CROSS_COMPILE=$(CROSS_COMPILE)

OPENSSL_BUILD_DIR = $(TRD_MOD_PATH)/openssl

.PHONY : clean all
all : $(TRD_BUILD_OPTIONAL_MODULE)

$(TRD_LIB_PATH)/libz.a:
	cd $(TRD_MOD_PATH)/../zlib ; make

$(TRD_LIB_PATH)/libssl.so.1.1: $(TRD_LIB_PATH)/libz.a
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/openssl/output
	(cd $(OPENSSL_BUILD_DIR); \
		$(OPENSSL_CMAKE_ENV) \
		DESTDIR=$(TRD_TMP_PATH)/openssl/output \
		./Configure \
			$(OPENSSL_TARGET_ARCH) \
			--prefix=/usr/local \
			--openssldir=/usr/local/ssl \
			-latomic \
			-lpthread threads \
			shared \
			no-rc5 \
			enable-camellia \
			enable-mdc2 \
			no-tests \
			no-fuzz-libfuzzer \
			no-fuzz-afl \
			zlib-dynamic \
	)
	$(SED) "s#-march=[-a-z0-9] ##" -e "s#-mcpu=[-a-z0-9] ##g" $(OPENSSL_BUILD_DIR)/Makefile
	$(SED) "s#-O[0-9sg]#$(OPENSSL_CFLAGS)#" $(OPENSSL_BUILD_DIR)/Makefile
	$(SED) "s# build_tests##" $(OPENSSL_BUILD_DIR)/Makefile
	@cd $(OPENSSL_BUILD_DIR) ; $(OPENSSL_CMAKE_ENV) make DESTDIR=$(TRD_TMP_PATH)/openssl/output install
	@tar -C $(TRD_TMP_PATH)/openssl/output/usr/local -czf $(TRD_TAR_PATH)/openssl.tar.gz bin include lib share ssl
	@[ "$(TRD_DEFAULT_OPENSSL)" != "openssl" ] || rsync -avpPxH $(TRD_TMP_PATH)/openssl/output/usr/local/include/ $(TRD_INCLUDE_PATH)/
	@[ "$(TRD_DEFAULT_OPENSSL)" != "openssl" ] || rsync -avpPxH $(TRD_TMP_PATH)/openssl/output/usr/local/lib/lib*.so* $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/openssl/output/usr/local/lib/lib*.so.1* $(TRD_LIB_PATH)/
	@[ "$(TRD_DEFAULT_OPENSSL)" != "openssl" ] || cp -p $(TRD_TMP_PATH)/openssl/output/usr/local/lib/lib*.a $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libssl.so.1.1

clean:
	@cd $(OPENSSL_BUILD_DIR) && $(OPENSSL_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/openssl/output make clean
	@cd $(OPENSSL_BUILD_DIR) && rm -f */*/*.o */*/*.d */*/*/*.o */*/*/*.d */*/*/*/*.o */*/*/*/*.d */*.a
	@[ "$(TRD_DEFAULT_OPENSSL)" != "openssl" ] || rm -f $(TRD_LIB_PATH)/libcrypto.a
	@[ "$(TRD_DEFAULT_OPENSSL)" != "openssl" ] || rm -f $(TRD_LIB_PATH)/libcrypto*.so*
	@rm -f $(TRD_LIB_PATH)/libcrypto*.so.1*
	@[ "$(TRD_DEFAULT_OPENSSL)" != "openssl" ] || rm -f $(TRD_LIB_PATH)/libssl.a
	@[ "$(TRD_DEFAULT_OPENSSL)" != "openssl" ] || rm -f $(TRD_LIB_PATH)/libssl*.so*
	@rm -f $(TRD_LIB_PATH)/libssl*.so.1*
	@rm -f $(TRD_TAR_PATH)/openssl.tar.gz
	@rm -rf $(TRD_TMP_PATH)/openssl

-include $(DEPS)
