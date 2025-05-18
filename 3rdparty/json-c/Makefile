SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

JSON_C_CMAKE_ENV = CMAKE_BUILD_TYPE="release" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

.PHONY : clean all
all : build_3rdparty_module

$(TRD_LIB_PATH)/libjson-c.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/json-c/build
	@mkdir -p $(TRD_TMP_PATH)/json-c/output
	@cd $(TRD_TMP_PATH)/json-c/build ; $(JSON_C_CMAKE_ENV) cmake $(TRD_MOD_PATH)/json-c -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/json-c/output
	@cd $(TRD_TMP_PATH)/json-c/build ; $(JSON_C_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/json-c/output -czf $(TRD_TAR_PATH)/json-c.tar.gz include lib
	@cp -p $(TRD_TMP_PATH)/json-c/output/lib/libjson-c.a $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libjson-c.a

clean:
	@rm -f $(TRD_LIB_PATH)/libjson-c.a
	@rm -f $(TRD_TAR_PATH)/json-c.tar.gz
	@rm -rf $(TRD_TMP_PATH)/json-c

-include $(DEPS)
