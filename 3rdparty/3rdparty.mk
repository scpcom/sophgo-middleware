# 3rdparty lib
TRD_MOD_PATH = $(PWD)
TRD_INCLUDE_PATH = $(realpath $(PWD)/..)/prebuilt/include
TRD_LIB_PATH = $(realpath $(PWD)/..)/prebuilt/$(SDK_VER)
TRD_TAR_PATH = $(realpath $(PWD)/..)/oss/oss_release_tarball/$(SDK_VER)
TRD_TMP_PATH = $(realpath $(PWD)/..)/tmp/$(SDK_VER)
ifeq ($(OSS_TARBALL_REL),1)
TRD_BUILD_TPUSDK_MODULE = build_3rdparty_module
TRD_BUILD_OPTIONAL_MODULE = build_3rdparty_module
else ifeq ($(TPU_REL),1)
TRD_BUILD_TPUSDK_MODULE = build_3rdparty_module
endif
TRD_DEFAULT_OPENCV = opencv4.5
TRD_DEFAULT_OPENSSL = openssl3.0
