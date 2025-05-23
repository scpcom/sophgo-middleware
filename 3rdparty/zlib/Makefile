SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

ZLIB_CMAKE_ENV = \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

.PHONY : clean all
all : build_3rdparty_module

$(TRD_LIB_PATH)/libz.a:
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/zlib/output
	@cd $(TRD_MOD_PATH)/zlib ; $(ZLIB_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/zlib/output ./configure
	@cd $(TRD_MOD_PATH)/zlib ; $(ZLIB_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/zlib/output make install
	@tar -C $(TRD_TMP_PATH)/zlib/output/usr/local -czf $(TRD_TAR_PATH)/zlib.tar.gz include lib share
	@rsync -avpPxH $(TRD_TMP_PATH)/zlib/output/usr/local/include/ $(TRD_INCLUDE_PATH)/
	@cp -p $(TRD_TMP_PATH)/zlib/output/usr/local/lib/lib*.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/zlib/output/usr/local/lib/libz*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libz.a

clean:
	@cd $(TRD_MOD_PATH)/zlib ; $(ZLIB_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/zlib/output make distclean
	@rm -f $(TRD_LIB_PATH)/libz.a
	@rm -f $(TRD_LIB_PATH)/libz*.so*
	@rm -f $(TRD_TAR_PATH)/zlib.tar.gz
	@rm -rf $(TRD_TMP_PATH)/zlib

-include $(DEPS)
