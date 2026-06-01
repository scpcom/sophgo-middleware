SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

WEBSOCKETS_CMAKE_ENV = CMAKE_BUILD_TYPE="RELEASE" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0 -I$(TRD_INCLUDE_PATH) -Wl,-L$(TRD_LIB_PATH) -Wno-unused-parameter -Wno-implicit-fallthrough -Wno-missing-field-initializers -Wno-deprecated-declarations" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0"

WEBSOCKETS_CMAKE_OPTS = -DLWS_IPV6=ON

WEBSOCKETS_CMAKE_OPTS += \
	-DLWS_WITH_SSL=ON \
	-DLWS_OPENSSL_INCLUDE_DIRS=$(TRD_INCLUDE_PATH) \
	-DLWS_OPENSSL_LIBRARIES="$(TRD_LIB_PATH)/libssl.so;$(TRD_LIB_PATH)/libcrypto.so"

WEBSOCKETS_CMAKE_OPTS += \
	-DLWS_WITH_LIBEV=OFF \
	-DLWS_WITH_LIBEVENT=OFF

WEBSOCKETS_CMAKE_OPTS += \
	-DLWS_WITH_LIBUV=ON \
	-DLWS_LIBUV_INCLUDE_DIRS=$(TRD_INCLUDE_PATH) \
	-DLWS_LIBUV_LIBRARIES=$(TRD_LIB_PATH)

.PHONY : clean all
all : $(TRD_BUILD_TPUSDK_MODULE)

$(TRD_LIB_PATH)/libssl.so:
	cd $(TRD_MOD_PATH)/../$(TRD_DEFAULT_OPENSSL) ; make

$(TRD_LIB_PATH)/libuv.so:
	cd $(TRD_MOD_PATH)/../uv ; make

$(TRD_LIB_PATH)/libwebsockets.a: $(TRD_LIB_PATH)/libssl.so $(TRD_LIB_PATH)/libuv.so
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/websockets/build
	@mkdir -p $(TRD_TMP_PATH)/websockets/output
	@cd $(TRD_TMP_PATH)/websockets/build ; $(WEBSOCKETS_CMAKE_ENV) cmake $(TRD_MOD_PATH)/libwebsockets -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/websockets/output $(WEBSOCKETS_CMAKE_OPTS)
	@cd $(TRD_TMP_PATH)/websockets/build ; $(WEBSOCKETS_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/websockets/output -czf $(TRD_TAR_PATH)/libwebsockets.tar.gz bin include lib share
	@rsync -avpPxH $(TRD_TMP_PATH)/websockets/output/include/ $(TRD_INCLUDE_PATH)/
	@cp -p $(TRD_TMP_PATH)/websockets/output/lib/libwebsockets*.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/websockets/output/lib/libwebsockets*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libwebsockets.a

clean:
	@rm -f $(TRD_LIB_PATH)/libwebsockets.a
	@rm -f $(TRD_LIB_PATH)/libwebsockets*.so*
	@rm -f $(TRD_TAR_PATH)/libwebsockets.tar.gz
	@rm -rf $(TRD_TMP_PATH)/websockets

-include $(DEPS)
