SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
	PARAM_FILE:=../../../../Makefile.param
	include $(PARAM_FILE)
endif

# 3rdparty lib
TRD_MOD_PATH = $(MW_PATH)/modules/bin
TRD_LIB_INCLUDE_PATH = $(MW_PATH)/modules/bin/prebuilt/include
TRD_LIB_PATH = $(MW_PATH)/modules/bin/prebuilt/$(SDK_VER)

INCS = -I$(MW_INC) -I$(KERNEL_INC) -I$(ISP_INC) -Iinc -Isrc
INCS += -I$(TRD_LIB_INCLUDE_PATH)/cvi_json-c -I../../algo

TMP_FOLDER = $(PWD)/tmp
SDIR = $(PWD)/src
SRCS = $(shell find $(SDIR) -type f -name "*.c")
OBJS = $(addsuffix .o,$(basename $(addprefix $(TMP_FOLDER)/,$(notdir $(SRCS)))))
DEPS = $(addsuffix .d,$(basename $(addprefix $(TMP_FOLDER)/,$(notdir $(SRCS)))))

TMP_FOLDER_LIB = $(PWD)/tmp_lib
ARFLAGS_x = x

TARGET_A = $(MW_LIB)/libcvi_bin_isp.a
TARGET_SO = $(MW_LIB)/libcvi_bin_isp.so

EXTRA_CFLAGS = $(INCS)
EXTRA_LDFLAGS =

EXTRA_CFLAGS += -DISP_BIN_COMMIT=\"$(shell git rev-parse --short HEAD)\"
gerrit_id=$(shell git log -n1 | grep Reviewed-on | tail -n1 | sed "s/.*\///g")
ifneq ($(gerrit_id), )
	EXTRA_CFLAGS += -DISP_BIN_GERRIT=\"$(gerrit_id)\"
endif

result=$(shell ./CalPqBinMD5.sh)
ifeq ($(result),-1)
abort:
	$(error "md5 error: please check CalPqBinMD5.sh")
else
	EXTRA_CFLAGS += -DISP_BIN_MD5=\"$(result)\"
endif

.PHONY: clean all cleanall sdk_release prepare_3rdparty_module

ifeq ($(ISP_SRC_RELEASE),1)
all: prepare_3rdparty_module $(TARGET_A) $(TARGET_SO) sdk_release
else
all: prepare_3rdparty_module $(TARGET_A) $(TARGET_SO)
endif

$(TRD_LIB_PATH)/libcvi_json-c.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_MOD_PATH)/json-c-build
	@mkdir -p $(TRD_MOD_PATH)/json-c-inst
	@cd $(TRD_MOD_PATH)/json-c-build ; CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc cmake $(TRD_MOD_PATH)/json-c -DCMAKE_INSTALL_PREFIX=$(TRD_MOD_PATH)/json-c-inst
	@cd $(TRD_MOD_PATH)/json-c-build ; CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc make install
	@tar -C $(TRD_MOD_PATH)/json-c-inst -czf $(TRD_MOD_PATH)/json-c-inst/cvi-json-c.tar.gz include lib
	@cp -p $(TRD_MOD_PATH)/json-c-inst/lib/libcvi_json-c.a $(TRD_LIB_PATH)/

$(TRD_LIB_PATH)/libcvi_miniz.a:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_MOD_PATH)/miniz-build
	@mkdir -p $(TRD_MOD_PATH)/miniz-inst
	@cd $(TRD_MOD_PATH)/miniz-build ; CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc cmake $(TRD_MOD_PATH)/miniz -G"Unix Makefiles" -DAMALGAMATE_SOURCES=ON -DCMAKE_INSTALL_PREFIX=$(TRD_MOD_PATH)/miniz-inst
	@cd $(TRD_MOD_PATH)/miniz-build ; CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CROSS_COMPILE)gcc make install
	@tar -C $(TRD_MOD_PATH)/miniz-inst -czf $(TRD_MOD_PATH)/miniz-inst/cvi-miniz.tar.gz include lib share
	@cp -p $(TRD_MOD_PATH)/miniz-inst/lib/libcvi_miniz.a $(TRD_LIB_PATH)/
	@rm -f $(TRD_MOD_PATH)/miniz/bin/example*

prepare_3rdparty_module: $(TRD_LIB_PATH)/libcvi_json-c.a $(TRD_LIB_PATH)/libcvi_miniz.a
	@mkdir -p $(TMP_FOLDER_LIB);cd $(TMP_FOLDER_LIB);\
	cp $(TRD_LIB_PATH)/libcvi_miniz.a .;cp $(TRD_LIB_PATH)/libcvi_json-c.a .;\
	$(AR) $(ARFLAGS_x) libcvi_miniz.a;$(AR) $(ARFLAGS_x) libcvi_json-c.a

$(TMP_FOLDER)/%.o: $(SDIR)/%.c | $(TMP_FOLDER)
	@$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@
	@echo [$(notdir $(CC))] $(notdir $@)

$(TARGET_A): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $(OBJS) $(TMP_FOLDER_LIB)/*.o
	@echo -e $(YELLOW)[LINK]$(END)[$(notdir $(AR))] $(notdir $(TARGET_A))

$(TARGET_SO): $(OBJS)
	@$(LD) $(LDFLAGS) $(EXTRA_LDFLAGS) -o $@ --start-group $(OBJS) $(TMP_FOLDER_LIB)/*.o --end-group
	@echo -e $(GREEN)[LINK]$(END)[$(notdir $(LD))] $(notdir $(TARGET_SO))
	@$(STRIP) $(TARGET_SO)

$(TMP_FOLDER):
	@echo "Create $(TMP_FOLDER) for object file"
	-@mkdir -p $(TMP_FOLDER)

sdk_release:
	-@rm -rf $(TMP_FOLDER)
	-@rm -rf $(TMP_FOLDER_LIB)
	-@mv Makefile.sdk_release Makefile

clean:
	@rm -f $(OBJS) $(DEPS) $(TARGET_A) $(TARGET_SO)
	@rm -rf $(TMP_FOLDER_LIB)
	@rm -f $(TRD_LIB_PATH)/libcvi_json-c.a $(TRD_LIB_PATH)/libcvi_miniz.a
	@rm -rf $(TRD_MOD_PATH)/json-c-build $(TRD_MOD_PATH)/json-c-inst
	@rm -rf $(TRD_MOD_PATH)/miniz-build $(TRD_MOD_PATH)/miniz-inst

cleanall: clean
	@rm -rf $(TMP_FOLDER)

-include $(DEPS)
