SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

LIVE_CMAKE_ENV = \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

.PHONY : clean all
all : build_3rdparty_module

$(TRD_LIB_PATH)/libliveMedia.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/live555/output
	@cd $(TRD_MOD_PATH)/live555 ; $(LIVE_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/live555/output ./genMakefiles linux
	@cd $(TRD_MOD_PATH)/live555 ; $(LIVE_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/live555/output make install
	@tar -C $(TRD_TMP_PATH)/live555/output/usr/local -czf $(TRD_TAR_PATH)/live555.tar.gz bin include lib
	@cp -p $(TRD_TMP_PATH)/live555/output/usr/local/lib/lib*.a $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libliveMedia.a

clean:
	@cd $(TRD_MOD_PATH)/live555 ; [ ! -e Makefile ] || $(LIVE_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/live555/output make clean
	@rm -f $(TRD_LIB_PATH)/libBasicUsageEnvironment.a
	@rm -f $(TRD_LIB_PATH)/libgroupsock.a
	@rm -f $(TRD_LIB_PATH)/libliveMedia.a
	@rm -f $(TRD_LIB_PATH)/libUsageEnvironment.a
	@rm -f $(TRD_TAR_PATH)/live555.tar.gz
	@rm -rf $(TRD_TMP_PATH)/live555

-include $(DEPS)
