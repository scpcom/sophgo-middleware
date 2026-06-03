SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

ALSA_LIB_CFLAGS = $(filter-out -std=gnu11, $(CFLAGS)) -g0 -I$(TRD_INCLUDE_PATH) -L$(TRD_LIB_PATH)
ALSA_LIB_CXXFLAGS = $(filter-out -std=gnu++11, $(CXXFLAGS)) -g0 -I$(TRD_INCLUDE_PATH) -L$(TRD_LIB_PATH)

ALSA_LIB_CONF_ENV = \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(ALSA_LIB_CFLAGS)" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(ALSA_LIB_CXXFLAGS)" \
	LDFLAGS="$(ALSA_LIB_CFLAGS) -lm"

ALSA_LIB_PREFIX=/usr

ifeq ($(SDK_VER), 32bit)
ALSA_LIB_TARGET = arm-linux-gnueabihf
else ifeq ($(SDK_VER), 64bit)
ALSA_LIB_TARGET = aarch64-linux-gnu
else ifeq ($(SDK_VER), glibc_riscv64)
ALSA_LIB_TARGET = riscv64-unknown-linux-gnu
else ifeq ($(SDK_VER), musl_riscv64)
ALSA_LIB_TARGET = riscv64-unknown-linux-musl
else
$(error $(red)SDK_VER is invalid$(reset))
endif

ALSA_LIB_CONF_OPTS = \
	--enable-cross-compile \
	--target=$(ALSA_LIB_TARGET) \
	--host=$(ALSA_LIB_TARGET)

ALSA_LIB_CONF_OPTS += \
	--with-alsa-devdir="/dev/snd" \
	--with-pcm-plugins="all" \
	--with-ctl-plugins="all"

ALSA_LIB_CONF_OPTS += --enable-static=no

ALSA_LIB_CONF_OPTS += --disable-python

.PHONY : clean all
all : $(TRD_BUILD_TPUSDK_MODULE)

$(TRD_LIB_PATH)/libasound.so:
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/alsa_lib/output
	@cd $(TRD_MOD_PATH)/alsa_lib ; $(ALSA_LIB_CONF_ENV) autoreconf -fi
	@#cd $(TRD_MOD_PATH)/alsa_lib ; sed -i s/'std=c11'/'std=gnu11'/g ./configure
	@cd $(TRD_MOD_PATH)/alsa_lib ; $(ALSA_LIB_CONF_ENV) DESTDIR=$(TRD_TMP_PATH)/alsa_lib/output ./configure $(ALSA_LIB_CONF_OPTS)
	@cd $(TRD_MOD_PATH)/alsa_lib ; $(ALSA_LIB_CONF_ENV) DESTDIR=$(TRD_TMP_PATH)/alsa_lib/output make ARCH=$(ALSA_LIB_ARCH) install
	@tar -C $(TRD_TMP_PATH)/alsa_lib/output$(ALSA_LIB_PREFIX) -czf $(TRD_TAR_PATH)/alsa_lib.tar.gz include lib share
	@rsync -avpPxH $(TRD_TMP_PATH)/alsa_lib/output$(ALSA_LIB_PREFIX)/include/ $(TRD_INCLUDE_PATH)/
	@#cp -p $(TRD_TMP_PATH)/alsa_lib/output$(ALSA_LIB_PREFIX)/lib/libasound*.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/alsa_lib/output$(ALSA_LIB_PREFIX)/lib/libasound*.so* $(TRD_LIB_PATH)/
	@#cp -p $(TRD_TMP_PATH)/alsa_lib/output$(ALSA_LIB_PREFIX)/lib/libatopology.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/alsa_lib/output$(ALSA_LIB_PREFIX)/lib/libatopology*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libasound.so

clean:
	@#cd $(TRD_MOD_PATH)/alsa_lib && [ ! -e include/config.h ] || $(ALSA_LIB_CONF_ENV) DESTDIR=$(TRD_TMP_PATH)/alsa_lib/output make ARCH=$(ALSA_LIB_ARCH) distclean
	@cd $(TRD_MOD_PATH)/alsa_lib && rm -f */*.o */*.d */*.la */*.lo */*.a */*.so* */*/*.o */*/*.d */*/*.la */*/*.lo include/config.h
	@cd $(TRD_MOD_PATH)/alsa_lib && rm -f */Makefile */Makefile.in */*/Makefile */*/Makefile.in */*/*/Makefile */*/*/Makefile.in Makefile Makefile.in
	@cd $(TRD_MOD_PATH)/alsa_lib && rm -rf */.deps */.libs */*/.deps */*/.libs */*/*/.deps */*/*/.libs
	@rm -f $(TRD_LIB_PATH)/libasound*.a
	@rm -f $(TRD_LIB_PATH)/libasound*.so*
	@rm -f $(TRD_LIB_PATH)/libatopology.a
	@rm -f $(TRD_LIB_PATH)/libatopology*.so*
	@rm -f $(TRD_TAR_PATH)/alsa_lib.tar.gz
	@rm -rf $(TRD_TMP_PATH)/alsa_lib

-include $(DEPS)
