LOCAL_PATH := $(call my-dir)/../../..

include $(CLEAR_VARS)
LOCAL_MODULE := mxnet_predict
LOCAL_SRC_FILES := \
	src/ndarray/ndarray_function.cc \
	src/ndarray/ndarray.cc \
	src/engine/engine.cc \
	src/engine/naive_engine.cc \
	src/symbol/graph_executor.cc \
	src/symbol/graph_memory_allocator.cc \
	src/symbol/static_graph.cc \
	src/symbol/symbol.cc \
	src/operator/operator.cc \
	src/operator/operator_util.cc \
	src/operator/activation.cc \
	src/operator/batch_norm.cc \
	src/operator/block_grad.cc \
	src/operator/concat.cc \
	src/operator/convolution.cc \
	src/operator/dropout.cc \
	src/operator/elementwise_unary_op.cc \
	src/operator/elementwise_binary_op.cc \
	src/operator/elementwise_sum.cc \
	src/operator/fully_connected.cc \
	src/operator/leaky_relu.cc \
	src/operator/lrn.cc \
	src/operator/pooling.cc \
	src/operator/regression_output.cc \
	src/operator/reshape.cc \
	src/operator/slice_channel.cc \
	src/operator/softmax_output.cc \
	src/operator/deconvolution.cc \
	src/operator/elementwise_binary_scalar_op.cc \
	src/operator/embedding.cc \
	src/storage/storage.cc \
	src/resource.cc \
	src/c_api/c_predict_api.cc \
	src/c_api/c_api_error.cc
LOCAL_SRC_FILES += \
	make/android/jni/mnist/untar.cpp \
	make/android/jni/mnist/test.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/dmlc-core/include $(LOCAL_PATH)/mshadow
LOCAL_CPPFLAGS += -fexceptions -frtti \
	-DMSHADOW_USE_CBLAS=0 \
	-DMSHADOW_STAND_ALONE=1 \
	-DMSHADOW_FORCE_STREAM \
	-DMSHADOW_USE_CUDA=0 \
	-DMSHADOW_USE_MKL=0 \
	-DMSHADOW_RABIT_PS=0 \
	-DMSHADOW_DIST_PS=0 \
	-DMSHADOW_USE_SSE=0 \
	-DMXNET_USE_OPENCV=0 \
	-DMXNET_PREDICT_ONLY=1 \
	-DDISABLE_OPENMP=1

include $(BUILD_EXECUTABLE)



include $(CLEAR_VARS)
LOCAL_MODULE := predict
LOCAL_SRC_FILES := \
	src/ndarray/ndarray_function.cc \
	src/ndarray/ndarray.cc \
	src/engine/engine.cc \
	src/engine/naive_engine.cc \
	src/symbol/graph_executor.cc \
	src/symbol/graph_memory_allocator.cc \
	src/symbol/static_graph.cc \
	src/symbol/symbol.cc \
	src/operator/operator.cc \
	src/operator/operator_util.cc \
	src/operator/activation.cc \
	src/operator/batch_norm.cc \
	src/operator/block_grad.cc \
	src/operator/concat.cc \
	src/operator/convolution.cc \
	src/operator/dropout.cc \
	src/operator/elementwise_unary_op.cc \
	src/operator/elementwise_binary_op.cc \
	src/operator/elementwise_sum.cc \
	src/operator/fully_connected.cc \
	src/operator/leaky_relu.cc \
	src/operator/lrn.cc \
	src/operator/pooling.cc \
	src/operator/regression_output.cc \
	src/operator/reshape.cc \
	src/operator/slice_channel.cc \
	src/operator/softmax_output.cc \
	src/operator/deconvolution.cc \
	src/operator/elementwise_binary_scalar_op.cc \
	src/operator/embedding.cc \
	src/storage/storage.cc \
	src/resource.cc \
	src/c_api/c_predict_api.cc \
	src/c_api/c_api_error.cc
LOCAL_SRC_FILES += \
	make/android/jni/java/predictor.cc

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/dmlc-core/include $(LOCAL_PATH)/mshadow
LOCAL_CPPFLAGS += -fexceptions -frtti \
	-DMSHADOW_USE_CBLAS=0 \
	-DMSHADOW_STAND_ALONE=1 \
	-DMSHADOW_FORCE_STREAM \
	-DMSHADOW_USE_CUDA=0 \
	-DMSHADOW_USE_MKL=0 \
	-DMSHADOW_RABIT_PS=0 \
	-DMSHADOW_DIST_PS=0 \
	-DMSHADOW_USE_SSE=0 \
	-DMXNET_USE_OPENCV=0 \
	-DMXNET_PREDICT_ONLY=1 \
	-DDISABLE_OPENMP=1

include $(BUILD_SHARED_LIBRARY)







