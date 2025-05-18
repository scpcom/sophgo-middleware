SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

MINIZ_CMAKE_ENV = \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

.PHONY : clean all
all : build_3rdparty_module

$(TRD_LIB_PATH)/libminiz.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/miniz/build
	@mkdir -p $(TRD_TMP_PATH)/miniz/output
	@cd $(TRD_TMP_PATH)/miniz/build ; $(MINIZ_CMAKE_ENV) cmake $(TRD_MOD_PATH)/miniz -G"Unix Makefiles" -DAMALGAMATE_SOURCES=ON -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/miniz/output
	@cd $(TRD_TMP_PATH)/miniz/build ; $(MINIZ_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/miniz/output -czf $(TRD_TAR_PATH)/miniz.tar.gz include lib share
	@cp -p $(TRD_TMP_PATH)/miniz/output/lib/libminiz.a $(TRD_LIB_PATH)/
	@rm -f $(TRD_MOD_PATH)/miniz/bin/example*

build_3rdparty_module: $(TRD_LIB_PATH)/libminiz.a

clean:
	@rm -f $(TRD_LIB_PATH)/libminiz.a
	@rm -f $(TRD_TAR_PATH)/miniz.tar.gz
	@rm -rf $(TRD_TMP_PATH)/miniz

-include $(DEPS)
