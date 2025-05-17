SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif

SDIR = $(PWD)/src
SRCS := $(wildcard $(SDIR)/*.c)

# 3rdparty lib
TRD_MOD_PATH = $(PWD)
TRD_INCLUDE_PATH = $(PWD)/prebuilt/include
TRD_LIB_PATH = $(PWD)/prebuilt/$(SDK_VER)
TRD_TAR_PATH = $(realpath $(PWD)/../..)/3rdparty/oss/oss_release_tarball/$(SDK_VER)
TRD_TMP_PATH = $(PWD)/tmp_3rd/$(SDK_VER)

ifneq ($(findstring $(CHIP_ARCH), MARS PHOBOS CV181X CV180X),)
ISP_BIN_DIR = $(MW_PATH)/modules/isp/$(shell echo $(CHIP_ARCH) | tr A-Z a-z)/isp_bin/inc
else
$(error UNKNOWN chip architecture - $(CHIP_ARCH))
endif

SRCS_ASM = $(wildcard $(SDIR)/*.S)
INCS = -I$(MW_INC) -I$(KERNEL_INC) -I$(SYS_INC) -I$(VPSS_INC) -I$(ISP_INC) -Iinclude
INCS += -I$(SYS_INC) -I$(TRD_INCLUDE_PATH)/cvi_json-c -I$(ISP_BIN_DIR) -I$(TRD_INCLUDE_PATH)/cvi_miniz
OBJS = $(SRCS:.c=.o)
OBJS_ASM = $(SRCS_ASM:.S=.o)
DEPS = $(SRCS:.c=.d)

TARGET_A = $(MW_LIB)/libcvi_bin.a
TARGET_SO = $(MW_LIB)/libcvi_bin.so

EXTRA_CFLAGS = $(INCS) -fpack-struct=8
EXTRA_CFLAGS += -DMMF_VERSION=\"$(shell git describe --always)\"
EXTRA_CFLAGS += -DSDK_VER=\"$(SDK_VER)\"
EXTRA_CFLAGS += -DISP_COMMIT=\"$(shell git rev-parse --short HEAD)\"
EXTRA_CFLAGS += -DISP_GERRIT=\"$(shell git log -n1 | grep Reviewed-on | tail -n1 | sed "s/.*\///g")\"
ifeq ($(MULTI_PROCESS_SUPPORT), 1)
EXTRA_CFLAGS += -DRPC_MULTI_PROCESS
endif

.PHONY : clean all
all : build_3rdparty_module $(TARGET_A) $(TARGET_SO)

$(TRD_LIB_PATH)/libcvi_json-c.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/cvi_json-c/build
	@mkdir -p $(TRD_TMP_PATH)/cvi_json-c/output
	@cd $(TRD_TMP_PATH)/cvi_json-c/build ; CMAKE_BUILD_TYPE="release" CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS)" cmake $(TRD_MOD_PATH)/json-c -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/cvi_json-c/output
	@cd $(TRD_TMP_PATH)/cvi_json-c/build ; CMAKE_BUILD_TYPE="release" CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS)" make install
	@tar -C $(TRD_TMP_PATH)/cvi_json-c/output -czf $(TRD_TAR_PATH)/cvi-json-c.tar.gz include lib
	@cp -p $(TRD_TMP_PATH)/cvi_json-c/output/lib/libcvi_json-c.a $(TRD_LIB_PATH)/

$(TRD_LIB_PATH)/libcvi_miniz.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/cvi_miniz/build
	@mkdir -p $(TRD_TMP_PATH)/cvi_miniz/output
	@cd $(TRD_TMP_PATH)/cvi_miniz/build ; CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS)" cmake $(TRD_MOD_PATH)/miniz -G"Unix Makefiles" -DAMALGAMATE_SOURCES=ON -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/cvi_miniz/output
	@cd $(TRD_TMP_PATH)/cvi_miniz/build ; CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS)" make install
	@tar -C $(TRD_TMP_PATH)/cvi_miniz/output -czf $(TRD_TAR_PATH)/cvi-miniz.tar.gz include lib share
	@cp -p $(TRD_TMP_PATH)/cvi_miniz/output/lib/libcvi_miniz.a $(TRD_LIB_PATH)/
	@rm -f $(TRD_MOD_PATH)/miniz/bin/example*

build_3rdparty_module: $(TRD_LIB_PATH)/libcvi_json-c.a $(TRD_LIB_PATH)/libcvi_miniz.a

$(SDIR)/%.o: $(SDIR)/%.c
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(EXTRA_CFLAGS) -o $@ -c $<
	@echo [$(notdir $(CC))] $(notdir $@)

$(SDIR)/%.o: $(SDIR)/%.S
	$(CC) $(DEPFLAGS) $(CFLAGS) $(EXTRA_CFLAGS) -o $@ -c $<
	@echo [$(notdir $(CC))] $(notdir $@)

$(TARGET_A): $(OBJS) $(OBJS_ASM)
	@$(AR) $(ARFLAGS) $(TARGET_A) $(OBJS) $(OBJS_ASM)
	@echo -e $(YELLOW)[LINK]$(END)[$(notdir $(AR))] $(notdir $(TARGET_A))
	@echo "$$AR_MRI" | $(AR) -M

$(TARGET_SO): $(OBJS) $(OBJS_ASM)
	@$(LD) $(LDFLAGS) $(EXTRA_LDFLAGS) -o $(TARGET_SO) --start-group $(OBJS) $(OBJS_ASM) $(LIBS) --end-group
	@echo -e $(GREEN)[LINK]$(END)[$(notdir $(LD))] $(notdir $(TARGET_SO))
	@$(STRIP) $(TARGET_SO)

clean:
	@rm -f $(OBJS) $(OBJS_ASM) $(DEPS) $(TARGET_A) $(TARGET_SO)
	@rm -f $(TRD_LIB_PATH)/libcvi_json-c.a $(TRD_LIB_PATH)/libcvi_miniz.a
	@rm -f $(TRD_TAR_PATH)/cvi-json-c.tar.gz $(TRD_TAR_PATH)/cvi-miniz.tar.gz
	@rm -rf $(TRD_TMP_PATH)

-include $(DEPS)
