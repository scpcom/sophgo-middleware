SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

SDIR = $(PWD)/src
SRCS := $(wildcard $(SDIR)/*.c)

.PHONY : clean all
all : build_3rdparty_module

$(TRD_LIB_PATH)/libjson-c.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TMP_PATH)/json-c/build
	@mkdir -p $(TRD_TMP_PATH)/json-c/output
	@cd $(TRD_TMP_PATH)/json-c/build ; CMAKE_BUILD_TYPE="release" CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS)" cmake $(TRD_MOD_PATH)/json-c -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/json-c/output
	@cd $(TRD_TMP_PATH)/json-c/build ; CMAKE_BUILD_TYPE="release" CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS)" make install
	@tar -C $(TRD_TMP_PATH)/json-c/output -czf $(TRD_TMP_PATH)/json-c/output/json-c.tar.gz include lib
	@cp -p $(TRD_TMP_PATH)/json-c/output/lib/libjson-c.a $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libjson-c.a

clean:
	@rm -f $(TRD_LIB_PATH)/libjson-c.a
	@rm -rf $(TRD_TMP_PATH)/json-c

-include $(DEPS)
