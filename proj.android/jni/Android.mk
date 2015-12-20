LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared
LOCAL+MODULE += gesture_static

LOCAL_MODULE_FILENAME := libcocos2dcpp
LOCAL+MODULE_FILENAME += libGesture

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/StartScene.cpp\
				   ../../Classes/MenuScene.cpp\
				   ../../Classes/BattleScene.cpp\
				   ../../Classes/WinScene.cpp\
				   ../../Classes/LoseScene.cpp\
				   ../../Classes/MapLayer.cpp\
				   ../../Classes/Monster.cpp\
				   ../../Classes/GeometricRecognizer.cpp\
				   ../../Classes/GestureLayer.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
