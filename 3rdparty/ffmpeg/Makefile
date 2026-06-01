SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

ifeq ($(SDK_VER), 32bit)
FFMPEG_ARCH = arm
FFMPEG_ARM_CPU_HAS_VFPV2 = y
FFMPEG_ARM_CPU_HAS_NEON = y
GCC_TARGET_CPU = cortex-a53
else ifeq ($(SDK_VER), 64bit)
FFMPEG_ARCH = aarch64
GCC_TARGET_CPU = cortex-a53
else ifeq ($(SDK_VER), glibc_riscv64)
FFMPEG_ARCH = riscv64
ifeq ($(findstring thead-c906,$(OPT_LEVEL)),thead-c906)
GCC_TARGET_CPU = thead-c906
else
GCC_TARGET_CPU = c906fdv
endif
else ifeq ($(SDK_VER), musl_riscv64)
FFMPEG_ARCH = riscv64
ifeq ($(findstring thead-c906,$(OPT_LEVEL)),thead-c906)
GCC_TARGET_CPU = thead-c906
else
GCC_TARGET_CPU = c906fdv
endif
else
$(error $(red)SDK_VER is invalid$(reset))
endif

FFMPEG_CFLAGS = $(filter-out -std=gnu11, $(CFLAGS)) -g0 -I$(TRD_INCLUDE_PATH) -L$(TRD_LIB_PATH)
FFMPEG_CXXFLAGS = $(filter-out -std=gnu++11, $(CXXFLAGS)) -g0 -I$(TRD_INCLUDE_PATH) -L$(TRD_LIB_PATH)

FFMPEG_CMAKE_ENV = \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(FFMPEG_CFLAGS)" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(FFMPEG_CXXFLAGS)" \
	LDFLAGS="$(FFMPEG_CFLAGS)"

FFMPEG_CONF_OPTS = \
	--enable-cross-compile \
	--cross-prefix=$(CROSS_COMPILE) \
	--sysroot=$(SYSROOT) \
	--arch="$(FFMPEG_ARCH)" \
	--target-os="linux" \
	--disable-stripping \
	--enable-debug=0 \
	--enable-static \
	--enable-shared \
	--prefix=/usr/local \
	--disable-avfilter \
	--disable-version3 \
	--enable-logging \
	--enable-optimizations \
	--disable-extra-warnings \
	--disable-avdevice \
	--enable-avcodec \
	--enable-avformat \
	--enable-network \
	--disable-gray \
	--enable-swscale-alpha \
	--disable-small \
	--enable-dct \
	--enable-fft \
	--enable-mdct \
	--enable-rdft \
	--disable-crystalhd \
	--disable-dxva2 \
	--enable-runtime-cpudetect \
	--disable-hardcoded-tables \
	--disable-mipsdsp \
	--disable-mipsdspr2 \
	--disable-msa \
	--enable-hwaccels \
	--disable-cuda \
	--disable-cuvid \
	--disable-nvenc \
	--disable-avisynth \
	--disable-frei0r \
	--disable-libopencore-amrnb \
	--disable-libopencore-amrwb \
	--disable-libdc1394 \
	--disable-libgsm \
	--disable-libilbc \
	--disable-libvo-amrwbenc \
	--disable-symver \
	--enable-doc \
	--enable-manpages \
	--disable-htmlpages \
	--disable-podpages \
	--disable-txtpages \
	--enable-gpl \
	--enable-nonfree \
	--enable-ffmpeg \
	--disable-ffplay \
	--disable-libv4l2 \
	--disable-avresample \
	--enable-ffprobe \
	--disable-libxcb \
	--disable-postproc \
	--enable-swscale \
	--enable-indevs \
	--disable-alsa \
	--enable-outdevs \
	--enable-pthreads \
	--enable-zlib \
	--disable-bzlib \
	--disable-libfdk-aac \
	--disable-libcdio \
	--disable-gnutls \
	--enable-openssl \
	--disable-libdrm \
	--disable-libopenh264 \
	--disable-vaapi \
	--disable-vdpau \
	--disable-mmal \
	--disable-omx \
	--disable-omx-rpi \
	--enable-libopencv \
	--disable-libopus \
	--disable-libvpx \
	--disable-libass \
	--disable-libbluray \
	--disable-libmfx \
	--disable-librtmp \
	--disable-libmp3lame \
	--disable-libmodplug \
	--disable-libspeex \
	--disable-libtheora \
	--disable-libwavpack \
	--disable-iconv \
	--disable-libfreetype \
	--disable-fontconfig \
	--disable-libopenjpeg \
	--disable-libx264 \
	--disable-libx265 \
	--disable-libdav1d \
	--disable-x86asm \
	--disable-mmx \
	--disable-sse \
	--disable-sse2 \
	--disable-sse3 \
	--disable-ssse3 \
	--disable-sse4 \
	--disable-sse42 \
	--disable-avx \
	--disable-avx2 \
	--disable-armv6 \
	--disable-armv6t2

ifeq ($(FFMPEG_ARM_CPU_HAS_VFPV2),y)
FFMPEG_CONF_OPTS += --enable-vfp
else
FFMPEG_CONF_OPTS += --disable-vfp
endif
ifeq ($(FFMPEG_ARM_CPU_HAS_NEON),y)
FFMPEG_CONF_OPTS += --enable-neon
else ifeq ($(FFMPEG_ARCH),aarch64)
FFMPEG_CONF_OPTS += --enable-neon
else
FFMPEG_CONF_OPTS += --disable-neon
endif

FFMPEG_CONF_OPTS += \
	--disable-altivec \
	--extra-libs=-latomic \
	--enable-pic \
	--cpu="$(GCC_TARGET_CPU)"


.PHONY : clean all
all : $(TRD_BUILD_OPTIONAL_MODULE)

$(TRD_LIB_PATH)/libz.a:
	cd $(TRD_MOD_PATH)/../zlib ; make

$(TRD_LIB_PATH)/libssl.a: $(TRD_LIB_PATH)/libz.a
	cd $(TRD_MOD_PATH)/../$(TRD_DEFAULT_OPENSSL) ; make

$(TRD_LIB_PATH)/libopencv_core.a:
	cd $(TRD_MOD_PATH)/../$(TRD_DEFAULT_OPENCV) ; make

$(TRD_LIB_PATH)/libavcodec.a: $(TRD_LIB_PATH)/libssl.a $(TRD_LIB_PATH)/libopencv_core.a
	@mkdir -p $(TRD_INCLUDE_PATH)
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/ffmpeg/output
	@cd $(TRD_MOD_PATH)/ffmpeg ; sed -i s/'std=c11'/'std=gnu11'/g ./configure
	@cd $(TRD_MOD_PATH)/ffmpeg ; $(FFMPEG_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/ffmpeg/output ./configure $(FFMPEG_CONF_OPTS)
	@cd $(TRD_MOD_PATH)/ffmpeg ; $(FFMPEG_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/ffmpeg/output make ARCH=$(FFMPEG_ARCH) install
	@tar -C $(TRD_TMP_PATH)/ffmpeg/output/usr/local -czf $(TRD_TAR_PATH)/ffmpeg.tar.gz bin include lib share
	@rsync -avpPxH $(TRD_TMP_PATH)/ffmpeg/output/usr/local/include/ $(TRD_INCLUDE_PATH)/
	@cp -p $(TRD_TMP_PATH)/ffmpeg/output/usr/local/lib/libav*.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/ffmpeg/output/usr/local/lib/libav*.so* $(TRD_LIB_PATH)/
	@cp -p $(TRD_TMP_PATH)/ffmpeg/output/usr/local/lib/libswresample.a $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/ffmpeg/output/usr/local/lib/libswresample*.so* $(TRD_LIB_PATH)/

build_3rdparty_module: $(TRD_LIB_PATH)/libavcodec.a

clean:
	@cd $(TRD_MOD_PATH)/ffmpeg && [ ! -e ffbuild/config.mak ] || $(FFMPEG_CMAKE_ENV) DESTDIR=$(TRD_TMP_PATH)/ffmpeg/output make ARCH=$(FFMPEG_ARCH) distclean
	@cd $(TRD_MOD_PATH)/ffmpeg && rm -f */*.o  */*.d */*.a */*.so* */*/*.o  */*/*.d config.h
	@rm -f $(TRD_LIB_PATH)/libav*.a
	@rm -f $(TRD_LIB_PATH)/libav*.so*
	@rm -f $(TRD_LIB_PATH)/libswresample.a
	@rm -f $(TRD_LIB_PATH)/libswresample*.so*
	@rm -f $(TRD_TAR_PATH)/ffmpeg.tar.gz
	@rm -rf $(TRD_TMP_PATH)/ffmpeg

-include $(DEPS)
