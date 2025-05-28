SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

NANOMSG_CMAKE_ENV = CMAKE_BUILD_TYPE="RELEASE" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

.PHONY : clean all
all : $(TRD_BUILD_OPTIONAL_MODULE)

$(TRD_LIB_PATH)/libnanomsg.so:
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/nanomsg/build
	@mkdir -p $(TRD_TMP_PATH)/nanomsg/output
	@cd $(TRD_TMP_PATH)/nanomsg/build ; $(NANOMSG_CMAKE_ENV) cmake $(TRD_MOD_PATH)/nanomsg -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/nanomsg/output $(NANOMSG_CMAKE_OPTS)
	@cd $(TRD_TMP_PATH)/nanomsg/build ; $(NANOMSG_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/nanomsg/output -czf $(TRD_TAR_PATH)/nanomsg.tar.gz bin include lib
	@rsync -avpPxH $(TRD_TMP_PATH)/nanomsg/output/include/ $(TRD_INCLUDE_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/nanomsg/output/lib/libnanomsg*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libnanomsg.so

clean:
	@rm -f $(TRD_LIB_PATH)/libnanomsg*.so*
	@rm -f $(TRD_TAR_PATH)/nanomsg.tar.gz
	@rm -rf $(TRD_TMP_PATH)/nanomsg
