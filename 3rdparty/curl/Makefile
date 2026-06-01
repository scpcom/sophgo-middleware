SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

CURL_CMAKE_ENV = CMAKE_BUILD_TYPE="RELEASE" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0 -I$(TRD_INCLUDE_PATH)" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0 -I$(TRD_INCLUDE_PATH)" \
	LDFLAGS="-L$(TRD_LIB_PATH)"

CURL_PREFIX=/usr/local

ifeq ($(SDK_VER), 32bit)
CURL_TARGET = arm-linux-gnueabihf
else ifeq ($(SDK_VER), 64bit)
CURL_TARGET = aarch64-linux-gnu
else ifeq ($(SDK_VER), glibc_riscv64)
CURL_TARGET = riscv64-unknown-linux-gnu
else ifeq ($(SDK_VER), musl_riscv64)
CURL_TARGET = riscv64-unknown-linux-musl
else
$(error $(red)SDK_VER is invalid$(reset))
endif

CURL_CONF_OPTS = \
	--enable-cross-compile \
	--target=$(CURL_TARGET) \
	--host=$(CURL_TARGET) \
	--without-zstd \
	--with-openssl

.PHONY : clean all
all : $(TRD_BUILD_TPUSDK_MODULE)

$(TRD_LIB_PATH)/libssl.so:
	cd $(TRD_MOD_PATH)/../$(TRD_DEFAULT_OPENSSL) ; make

$(TRD_LIB_PATH)/libcurl.so: $(TRD_LIB_PATH)/libssl.so
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/curl/output
	@cd $(TRD_MOD_PATH)/curl ; $(CURL_CMAKE_ENV) autoreconf -fi
	@cd $(TRD_MOD_PATH)/curl ; $(CURL_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/curl/output ./configure $(CURL_CONF_OPTS)
	@cd $(TRD_MOD_PATH)/curl ; $(CURL_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/curl/output make install
	@tar -C $(TRD_TMP_PATH)/curl/output$(CURL_PREFIX) -czf $(TRD_TAR_PATH)/curl.tar.gz bin include lib share
	@rsync -avpPxH $(TRD_TMP_PATH)/curl/output$(CURL_PREFIX)/include/ $(TRD_INCLUDE_PATH)/
	@cp -p $(TRD_TMP_PATH)/curl/output$(CURL_PREFIX)/lib/libcurl*.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/curl/output$(CURL_PREFIX)/lib/libcurl*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libcurl.so

clean:
	@rm -f $(TRD_LIB_PATH)/libcurl*.a
	@rm -f $(TRD_LIB_PATH)/libcurl*.so*
	@rm -f $(TRD_TAR_PATH)/curl.tar.gz
	@rm -rf $(TRD_TMP_PATH)/curl

-include $(DEPS)
