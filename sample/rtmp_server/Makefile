SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
	PARAM_FILE:=../../Makefile.param
	include $(PARAM_FILE)
endif
include ../sample.mk

SDIR = $(PWD)
SRCS = $(wildcard $(SDIR)/*.c)
#SRCS += $(SDIR)/../test_mmf/maixcam_lib/src/maix_avc2flv.c
INCS = -I$(MW_INC) -I$(ISP_INC) -I../common/ -I$(KERNEL_INC) -I$(MW_INC)/linux -I$(SDIR) -I$(SENSOR_LIST_INC)

SRCS_CPP += $(wildcard $(SDIR)/*.cpp)

CFLAGS += -I$(SDIR)/../test_mmf/maixcam_lib/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/media-server/libflv/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/media-server/librtmp/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/sdk/include
CPPFLAGS := $(subst -std=gnu11,-std=c++17, $(CFLAGS)) $(INCS) \
-I$(SDIR)/../test_mmf/media_server-1.0.x/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/sdk/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/sdk/libhttp/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/media-server/librtp/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/media-server/libmpeg/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/media-server/libflv/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/media-server/libmkv/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x \
-I$(SDIR)/../test_mmf/media_server-1.0.x/avcodec/avcodec/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/avcodec/avbsf/include \
-I$(SDIR)/../test_mmf/media_server-1.0.x/media-server/libmov/include \
-D__ERROR__=00*10000000+__LINE__*1000


OBJS = $(SRCS:.c=.o)
OBJS += $(SRCS_CPP:.cpp=.o)
DEPS = $(SRCS:.c=.d)

TARGET = rtmp_server
ifeq ($(CONFIG_ENABLE_SDK_ASAN), y)
TARGET = rtmp_server_asan
endif

PKG_CONFIG_PATH = $(MW_PATH)/pkgconfig
REQUIRES = cvi_common cvi_sample cvi_ive

MW_LIBS = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs --define-variable=mw_dir=$(MW_PATH) $(REQUIRES))

LIBS = $(filter-out -lsample, $(filter-out -lsns_full, $(MW_LIBS)))
ifeq ($(MULTI_PROCESS_SUPPORT), 1)
DEFS += -DRPC_MULTI_PROCESS
LIBS += -lnanomsg
endif

EXTRA_CFLAGS = $(INCS) $(DEFS)
EXTRA_LDFLAGS = $(LIBS) -lpthread -lm -lini

MSK_CFLAGS = $(filter-out -Werror, $(CFLAGS)) -Wno-incompatible-pointer-types

MSK_LIBD = ../test_mmf/media_server-1.0.x/release.linux

LIBS += -L$(SDIR)/$(MSK_LIBD) -lvdec -lhttp -lflv -lrtmp -lmov -lmpeg -lsdk -lavcodec -lavbsf

# IVE_SUPPORT = 1
ifeq ($(IVE_SUPPORT), 1)
CFLAGS += -DIVE_SUPPORT

IVE_PATH = $(MW_PATH)/../install/soc_cv1835_wevb_0002a_spinand/tpu_64/cvitek_ive_sdk
EXTRA_CFLAGS += -I$(IVE_PATH)/include/ive
EXTRA_LDFLAGS += -L$(IVE_PATH)/lib -lcvi_ive_tpu-static

TPU_PATH = $(MW_PATH)/../install/soc_cv1835_wevb_0002a_spinand/tpu_64/cvitek_tpu_sdk
EXTRA_CFLAGS += -I$(TPU_PATH)/include
EXTRA_LDFLAGS += -L$(TPU_PATH)/lib -lcviruntime-static -lcvimath-static -lcvikernel-static -lcnpy -lglog -lz
endif

.PHONY : clean all
all: $(TARGET)

mmflibs:
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) CFLAGS="$(MSK_CFLAGS)" PLATFORM=linux RELEASE=1 -C ../test_mmf/media_server-1.0.x/sdk/
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) CFLAGS="$(MSK_CFLAGS)" PLATFORM=linux RELEASE=1 -C ../test_mmf/media_server-1.0.x/avcodec/
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) CFLAGS="$(MSK_CFLAGS)" PLATFORM=linux RELEASE=1 -C ../test_mmf/media_server-1.0.x/media-server/
	@mkdir -p $(MSK_LIBD)
	@cp -p ../test_mmf/media_server-1.0.x/sdk/libhttp/release.linux/libhttp.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/sdk/libsdk/release.linux/libsdk.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/avcodec/avbsf/release.linux/libavbsf.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/avcodec/avcodec/release.linux/libavcodec.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/media-server/libflv/release.linux/libflv.a $(MSK_LIBD)/
	#@cp -p ../test_mmf/media_server-1.0.x/media-server/libmkv/release.linux/libmkv.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/media-server/libmov/release.linux/libmov.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/media-server/libmpeg/release.linux/libmpeg.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/media-server/librtp/release.linux/librtp.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/media-server/librtmp/release.linux/librtmp.a $(MSK_LIBD)/
	@cp -p ../test_mmf/media_server-1.0.x/media-server/librtsp/release.linux/librtsp.a $(MSK_LIBD)/
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) PLATFORM=linux RELEASE=1 -C ../test_mmf/maix_mmf/
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) PLATFORM=linux RELEASE=1 -C ../test_mmf/maixcam_lib/
	@cp -p ../test_mmf/maixcam_lib/release.linux/libmaixcam_lib.so $(MW_LIB)/

clean_mmflibs:
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) PLATFORM=linux RELEASE=1 -C ../test_mmf/media_server-1.0.x/sdk/ clean
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) PLATFORM=linux RELEASE=1 -C ../test_mmf/media_server-1.0.x/avcodec/ clean
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) PLATFORM=linux RELEASE=1 -C ../test_mmf/media_server-1.0.x/media-server/ clean
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) PLATFORM=linux RELEASE=1 -C ../test_mmf/maix_mmf/ clean
	@$(MAKE) AR=$(AR) CC=$(CC) CXX=$(CXX) PLATFORM=linux RELEASE=1 -C ../test_mmf/maixcam_lib/ clean

$(COMMON_DIR)/%.o: $(COMMON_DIR)/%.c
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(EXTRA_CFLAGS) -o $@ -c $<
	@echo [$(notdir $(CC))] $(notdir $@)

$(SDIR)/%.o: $(SDIR)/%.c
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(EXTRA_CFLAGS) -o $@ -c $<
	@echo [$(notdir $(CC))] $(notdir $@)

$(TARGET): mmflibs $(COMM_OBJ) $(OBJS) $(ISP_OBJ) $(MW_LIB)/libvenc.a $(MW_LIB)/libsys.a
	@$(CXX) -o $@ -Wl,-rpath='$$ORIGIN/dl_lib' -Wl,-rpath=/mnt/system/usr/lib -Wl,-rpath=/mnt/system/usr/lib/3rd -Wl,--start-group -lflv -lrtmp $(OBJS) $(COMM_OBJS) -lsys $(MW_LIB)/libsys.a -Wl,--end-group -lmaixcam_lib $(filter-out -static, $(ELFFLAGS)) $(EXTRA_LDFLAGS)
	@echo -e $(BLUE)[LINK]$(END)[$(notdir $(CXX))] $(notdir $@)

clean: clean_mmflibs
	@rm -f $(OBJS) $(DEPS) $(COMM_OBJ) $(COMM_DEPS) $(TARGET)

-include $(DEPS)
