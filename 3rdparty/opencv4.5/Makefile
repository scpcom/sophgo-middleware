SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../../Makefile.param
     include $(PARAM_FILE)
endif
include ../3rdparty.mk

ifeq ($(SDK_VER), 32bit)
CMAKE_SYSTEM_PROCESSOR = arm
OPENCV4_5_SYSTEM_PROCESSOR = ARM
else ifeq ($(SDK_VER), 64bit)
CMAKE_SYSTEM_PROCESSOR = aarch64
OPENCV4_5_SYSTEM_PROCESSOR = AARCH64
else ifeq ($(SDK_VER), glibc_riscv64)
CMAKE_SYSTEM_PROCESSOR = riscv64
OPENCV4_5_SYSTEM_PROCESSOR = RISCV
else ifeq ($(SDK_VER), musl_riscv64)
CMAKE_SYSTEM_PROCESSOR = riscv64
OPENCV4_5_SYSTEM_PROCESSOR = RISCV
else
$(error $(red)SDK_VER is invalid$(reset))
endif

OPENCV4_5_CMAKE_ENV = CMAKE_BUILD_TYPE="Release" \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CC=$(CROSS_COMPILE)gcc CFLAGS="$(CFLAGS) -g0" \
	CXX=$(CROSS_COMPILE)g++ CXXFLAGS="$(CXXFLAGS) -g0 -Wno-class-memaccess -Wno-deprecated-copy"

OPENCV4_5_CMAKE_OPTS = -DCMAKE_SYSTEM_PROCESSOR=$(CMAKE_SYSTEM_PROCESSOR)
OPENCV4_5_CMAKE_OPTS += -DOPENCV_SKIP_SYSTEM_PROCESSOR_DETECTION=ON -D$(OPENCV4_5_SYSTEM_PROCESSOR)=1
OPENCV4_5_CMAKE_OPTS += -DCPU_BASELINE_DETECT=OFF

OPENCV4_5_CMAKE_OPTS += \
	-DBUILD_DOCS=OFF \
	-DBUILD_PERF_TESTS=OFF \
	-DBUILD_TESTS=OFF \
	-DBUILD_WITH_DEBUG_INFO=OFF \
	-DDOWNLOAD_EXTERNAL_TEST_DATA=OFF \
	-DOPENCV_ENABLE_PKG_CONFIG=OFF \
	-DINSTALL_TEST=OFF \
	-DBUILD_WITH_STATIC_CRT=OFF \
	-DENABLE_CCACHE=OFF \
	-DENABLE_COVERAGE=OFF \
	-DENABLE_FAST_MATH=ON \
	-DENABLE_IMPL_COLLECTION=OFF \
	-DENABLE_NOISY_WARNINGS=OFF \
	-DENABLE_OMIT_FRAME_POINTER=ON \
	-DENABLE_PRECOMPILED_HEADERS=OFF \
	-DENABLE_PROFILING=OFF \
	-DOPENCV_WARNINGS_ARE_ERRORS=OFF \
	-DCMAKE_INSTALL_RPATH_USE_LINK_PATH=OFF \
	-DCMAKE_SKIP_RPATH=OFF \
	-DCMAKE_USE_RELATIVE_PATHS=OFF \
	-DBUILD_PACKAGE=OFF \
	-DENABLE_SOLUTION_FOLDERS=OFF \
	-DINSTALL_CREATE_DISTRIB=OFF \
	-DBUILD_opencv_androidcamera=OFF \
	-DBUILD_opencv_apps=OFF \
	-DBUILD_opencv_calib3d=OFF \
	-DBUILD_opencv_core=ON \
	-DBUILD_opencv_dnn=ON \
	-DBUILD_opencv_features2d=OFF \
	-DBUILD_opencv_flann=OFF \
	-DBUILD_opencv_highgui=OFF \
	-DBUILD_opencv_imgcodecs=ON \
	-DBUILD_opencv_imgproc=ON \
	-DBUILD_opencv_java=OFF \
	-DBUILD_opencv_ml=OFF \
	-DBUILD_opencv_objdetect=OFF \
	-DBUILD_opencv_photo=OFF \
	-DBUILD_opencv_shape=OFF \
	-DBUILD_opencv_stitching=OFF \
	-DBUILD_opencv_superres=OFF \
	-DBUILD_opencv_ts=OFF \
	-DBUILD_opencv_video=OFF \
	-DBUILD_opencv_videoio=OFF \
	-DBUILD_opencv_videostab=OFF \
	-DBUILD_opencv_viz=OFF \
	-DBUILD_opencv_world=OFF \
	-DENABLE_POWERPC=OFF \
	-DENABLE_NEON=OFF \
	-DENABLE_VFPV3=OFF \
	-DBUILD_CUDA_STUBS=OFF \
	-DBUILD_opencv_cudaarithm=OFF \
	-DBUILD_opencv_cudabgsegm=OFF \
	-DBUILD_opencv_cudacodec=OFF \
	-DBUILD_opencv_cudafeatures2d=OFF \
	-DBUILD_opencv_cudafilters=OFF \
	-DBUILD_opencv_cudaimgproc=OFF \
	-DBUILD_opencv_cudalegacy=OFF \
	-DBUILD_opencv_cudaobjdetect=OFF \
	-DBUILD_opencv_cudaoptflow=OFF \
	-DBUILD_opencv_cudastereo=OFF \
	-DBUILD_opencv_cudawarping=OFF \
	-DBUILD_opencv_cudev=OFF \
	-DWITH_CUBLAS=OFF \
	-DWITH_CUDA=OFF \
	-DWITH_CUFFT=OFF \
	-DWITH_NVCUVID=OFF \
	-DWITH_OPENCLAMDBLAS=OFF \
	-DWITH_OPENCLAMDFFT=OFF \
	-DBUILD_WITH_DYNAMIC_IPP=OFF \
	-DWITH_INTELPERC=OFF \
	-DWITH_IPP=OFF \
	-DWITH_IPP_A=OFF \
	-DWITH_TBB=OFF \
	-DWITH_GIGEAPI=OFF \
	-DWITH_PVAPI=OFF \
	-DWITH_XIMEA=OFF \
	-DANDROID=OFF \
	-DBUILD_ANDROID_CAMERA_WRAPPER=OFF \
	-DBUILD_ANDROID_EXAMPLES=OFF \
	-DBUILD_ANDROID_SERVICE=OFF \
	-DBUILD_FAT_JAVA_LIB=OFF \
	-DINSTALL_ANDROID_EXAMPLES=OFF \
	-DWITH_ANDROID_CAMERA=OFF \
	-DWITH_AVFOUNDATION=OFF \
	-DWITH_CARBON=OFF \
	-DWITH_QUICKTIME=OFF \
	-DWITH_CSTRIPES=OFF \
	-DWITH_DSHOW=OFF \
	-DWITH_MSMF=OFF \
	-DWITH_VFW=OFF \
	-DWITH_VIDEOINPUT=OFF \
	-DWITH_WIN32UI=OFF \
	-DBUILD_EXAMPLES=OFF \
	-DBUILD_JASPER=ON \
	-DBUILD_JPEG=ON \
	-DBUILD_OPENEXR=ON \
	-DBUILD_PNG=ON \
	-DBUILD_PROTOBUF=ON \
	-DBUILD_TIFF=ON \
	-DBUILD_WEBP=ON \
	-DBUILD_ZLIB=ON \
	-DINSTALL_C_EXAMPLES=OFF \
	-DINSTALL_PYTHON_EXAMPLES=OFF \
	-DINSTALL_TO_MANGLED_PATHS=OFF \
	-DWITH_1394=OFF \
	-DWITH_CLP=OFF \
	-DWITH_EIGEN=OFF \
	-DWITH_GDAL=OFF \
	-DWITH_GPHOTO2=OFF \
	-DWITH_GSTREAMER_0_10=OFF \
	-DWITH_LAPACK=OFF \
	-DWITH_MATLAB=OFF \
	-DWITH_OPENCL=OFF \
	-DWITH_OPENCL_SVM=OFF \
	-DWITH_OPENEXR=OFF \
	-DWITH_OPENNI2=OFF \
	-DWITH_OPENNI=OFF \
	-DWITH_UNICAP=OFF \
	-DWITH_VA=OFF \
	-DWITH_VA_INTEL=OFF \
	-DWITH_VTK=OFF \
	-DWITH_XINE=OFF \
	-DWITH_FFMPEG=OFF \
	-DWITH_GSTREAMER=OFF \
	-DWITH_GTK=OFF \
	-DWITH_GTK_2_X=OFF \
	-DWITH_JASPER=ON \
	-DWITH_JPEG=ON \
	-DWITH_OPENGL=OFF \
	-DWITH_OPENMP=ON \
	-DWITH_PNG=ON \
	-DWITH_PROTOBUF=ON \
	-DWITH_QT=OFF \
	-DWITH_TIFF=ON \
	-DWITH_LIBV4L=OFF \
	-DWITH_V4L=ON \
	-DWITH_WEBP=ON \
	-DBUILD_opencv_python2=OFF \
	-DBUILD_opencv_python3=OFF

.PHONY : clean all
all : $(TRD_BUILD_TPUSDK_MODULE)

$(TRD_LIB_PATH)/libopencv_core.so.4.5:
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TAR_PATH)
	@mkdir -p $(TRD_TMP_PATH)/opencv4.5/build
	@mkdir -p $(TRD_TMP_PATH)/opencv4.5/output
	@cd $(TRD_TMP_PATH)/opencv4.5/build ; $(OPENCV4_5_CMAKE_ENV) cmake $(TRD_MOD_PATH)/opencv -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/opencv4.5/output $(OPENCV4_5_CMAKE_OPTS)
	@cd $(TRD_TMP_PATH)/opencv4.5/build ; $(OPENCV4_5_CMAKE_ENV) make install
	@[ -e $(TRD_TMP_PATH)/opencv4.5/output/include/opencv2 -o ! -e $(TRD_TMP_PATH)/opencv4.5/output/include/opencv4/opencv2 ] || \
		ln -s opencv4/opencv2 $(TRD_TMP_PATH)/opencv4.5/output/include/opencv2
	@[ "$(TRD_DEFAULT_OPENCV)" != "opencv4.5" ] || rsync -avpPxH $(TRD_TMP_PATH)/opencv4.5/output/include/ $(TRD_INCLUDE_PATH)/
	@[ "$(TRD_DEFAULT_OPENCV)" != "opencv4.5" ] || rsync -avpPxH $(TRD_TMP_PATH)/opencv4.5/output/lib/libopencv*.so* $(TRD_LIB_PATH)/
	@rsync -avpPxH $(TRD_TMP_PATH)/opencv4.5/output/lib/libopencv*.so.4.5* $(TRD_LIB_PATH)/

$(TRD_LIB_PATH)/libopencv_core.a.4.5: $(TRD_LIB_PATH)/libopencv_core.so.4.5
	@mkdir -p $(TRD_LIB_PATH)
	@mkdir -p $(TRD_TMP_PATH)/opencv4.5/build_static
	@mkdir -p $(TRD_TMP_PATH)/opencv4.5/output
	@cd $(TRD_TMP_PATH)/opencv4.5/build_static ; $(OPENCV4_5_CMAKE_ENV) cmake $(TRD_MOD_PATH)/opencv -DCMAKE_INSTALL_PREFIX=$(TRD_TMP_PATH)/opencv4.5/output $(OPENCV4_5_CMAKE_OPTS) -DBUILD_SHARED_LIBS=OFF
	@cd $(TRD_TMP_PATH)/opencv4.5/build_static ; $(OPENCV4_5_CMAKE_ENV) make install
	@tar -C $(TRD_TMP_PATH)/opencv4.5/output -czf $(TRD_TAR_PATH)/opencv4.5.tar.gz include lib share
	@[ "$(TRD_DEFAULT_OPENCV)" != "opencv4.5" ] || rsync -avpPxH $(TRD_TMP_PATH)/opencv4.5/output/include/ $(TRD_INCLUDE_PATH)/
	@[ "$(TRD_DEFAULT_OPENCV)" != "opencv4.5" ] || rsync -avpPxH $(TRD_TMP_PATH)/opencv4.5/output/lib/libopencv*.a $(TRD_LIB_PATH)/
	@for f in $(TRD_TMP_PATH)/opencv4.5/output/lib/libopencv*.a ; do \
		rsync -avpPxH $$f $(TRD_LIB_PATH)/$$(basename $$f).4.5 ; \
	done

build_3rdparty_module: $(TRD_LIB_PATH)/libopencv_core.a.4.5

clean:
	@[ "$(TRD_DEFAULT_OPENCV)" != "opencv4.5" ] || rm -f $(TRD_LIB_PATH)/libopencv*.a
	@[ "$(TRD_DEFAULT_OPENCV)" != "opencv4.5" ] || rm -f $(TRD_LIB_PATH)/libopencv*.so
	@rm -f $(TRD_LIB_PATH)/libopencv*.a.4.5*
	@rm -f $(TRD_LIB_PATH)/libopencv*.so.4.5*
	@rm -f $(TRD_TAR_PATH)/opencv4.5*.tar.gz
	@rm -rf $(TRD_TMP_PATH)/opencv4.5

-include $(DEPS)
