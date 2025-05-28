SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

ifeq ($(SDK_VER), 32bit)
CMAKE_SYSTEM_PROCESSOR = arm
else ifeq ($(SDK_VER), 64bit)
CMAKE_SYSTEM_PROCESSOR = aarch64
else ifeq ($(SDK_VER), glibc_riscv64)
CMAKE_SYSTEM_PROCESSOR = riscv64
else ifeq ($(SDK_VER), musl_riscv64)
CMAKE_SYSTEM_PROCESSOR = riscv64
else
$(error $(red)SDK_VER is invalid$(reset))
endif

GLOG_CXXFLAGS = $(filter-out -std=gnu++11, $(CXXFLAGS)) -g0

GLOG_CMAKE_ENV = CMAKE_BUILD_TYPE="RELEASE" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(GLOG_CXXFLAGS)"

GLOG_CMAKE_OPTS += \
	-DCMAKE_SYSTEM_NAME=Linux \
	-DCMAKE_SYSTEM_VERSION=1 \
	-DCMAKE_SYSTEM_PROCESSOR=$(CMAKE_SYSTEM_PROCESSOR) \
	-DWITH_GTEST=OFF \
	-DWITH_GFLAGS=OFF

.PHONY : clean all
all : $(TRD_BUILD_OPTIONAL_MODULE)

$(TRD_LIB_PATH)/libglog.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/glog/build
	@mkdir -p $(TRD_TMP_PATH)/glog/output
	@cd $(TRD_TMP_PATH)/glog/build ; $(GLOG_CMAKE_ENV) cmake $(TRD_MOD_PATH)/glog -G"Unix Makefiles" -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/glog/output $(GLOG_CMAKE_OPTS)
	@cd $(TRD_TMP_PATH)/glog/build ; $(GLOG_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/glog/output -czf $(TRD_TAR_PATH)/glog.tar.gz include lib
	@cp -p $(TRD_TMP_PATH)/glog/output/lib/lib*.a $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libglog.a

clean:
	@rm -f $(TRD_LIB_PATH)/libglog.a
	@rm -f $(TRD_TAR_PATH)/glog.tar.gz
	@rm -rf $(TRD_TMP_PATH)/glog

-include $(DEPS)
