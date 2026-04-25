SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

UV_CMAKE_ENV = CMAKE_BUILD_TYPE="RELEASE" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

.PHONY : clean all
all : $(TRD_BUILD_TPUSDK_MODULE)

$(TRD_LIB_PATH)/libuv.so:
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/uv/build
	@mkdir -p $(TRD_TMP_PATH)/uv/output
	@cd $(TRD_TMP_PATH)/uv/build ; $(UV_CMAKE_ENV) cmake $(TRD_MOD_PATH)/uv -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/uv/output $(UV_CMAKE_OPTS)
	@cd $(TRD_TMP_PATH)/uv/build ; $(UV_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/uv/output -czf $(TRD_TAR_PATH)/uv.tar.gz include lib share
	@rsync -avpPxH $(TRD_TMP_PATH)/uv/output/include/ $(TRD_INCLUDE_PATH)/
	@cp -p $(TRD_TMP_PATH)/uv/output/lib/libuv*.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/uv/output/lib/libuv*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libuv.so

clean:
	@rm -f $(TRD_LIB_PATH)/libuv*.a
	@rm -f $(TRD_LIB_PATH)/libuv*.so*
	@rm -f $(TRD_TAR_PATH)/uv.tar.gz
	@rm -rf $(TRD_TMP_PATH)/uv

-include $(DEPS)
