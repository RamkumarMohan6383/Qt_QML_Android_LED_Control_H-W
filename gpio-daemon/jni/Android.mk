LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := gpiod
LOCAL_SRC_FILES := gpio_daemon.c gpio_mmio.c
LOCAL_LDLIBS    := -llog
include $(BUILD_EXECUTABLE)
