SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

FLATBUFFERS_CMAKE_ENV = CMAKE_BUILD_TYPE="RELEASE" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS)" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS)"

FLATBUFFERS_CMAKE_OPTS += \
	-DCMAKE_CXX_FLAGS="-std=c++11" \
	-DCMAKE_POSITION_INDEPENDENT_CODE=ON \
	-DFLATBUFFERS_BUILD_TESTS=OFF \
	-DFLATBUFFERS_FLATC_EXECUTABLE=$(HOST_DIR)/bin/flatc

FLATBUFFERS_CMAKE_OPTS += -DFLATBUFFERS_BUILD_SHAREDLIB=OFF

.PHONY : clean all
all : $(TRD_BUILD_TPUSDK_MODULE)

$(TRD_LIB_PATH)/libflatbuffers.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/flatbuffers/build
	@mkdir -p $(TRD_TMP_PATH)/flatbuffers/output
	@cd $(TRD_TMP_PATH)/flatbuffers/build ; $(FLATBUFFERS_CMAKE_ENV) cmake $(TRD_MOD_PATH)/flatbuffers -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/flatbuffers/output $(FLATBUFFERS_CMAKE_OPTS)
	@cd $(TRD_TMP_PATH)/flatbuffers/build ; $(FLATBUFFERS_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/flatbuffers/output -czf $(TRD_TAR_PATH)/flatbuffers.tar.gz bin include lib
	@cp -p $(TRD_TMP_PATH)/flatbuffers/output/lib/lib*.a $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libflatbuffers.a

clean:
	@rm -f $(TRD_LIB_PATH)/libflatbuffers.a
	@rm -f $(TRD_TAR_PATH)/flatbuffers.tar.gz
	@rm -rf $(TRD_TMP_PATH)/flatbuffers

-include $(DEPS)
