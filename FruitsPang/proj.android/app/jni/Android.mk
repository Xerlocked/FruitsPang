LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/MenuScene.cpp   \
                   $(LOCAL_PATH)/../../../Classes/DataManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameSettingPopup.cpp \
                   $(LOCAL_PATH)/../../../Classes/ResultPopup.cpp \
                   $(LOCAL_PATH)/../../../Classes/Block.cpp \
                   $(LOCAL_PATH)/../../../Classes/Board.cpp \
                   $(LOCAL_PATH)/../../../Classes/GridCell.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.h \
                   $(LOCAL_PATH)/../../../Classes/MenuScene.h   \
                   $(LOCAL_PATH)/../../../Classes/DataManager.h \
                   $(LOCAL_PATH)/../../../Classes/GameScene.h \
                   $(LOCAL_PATH)/../../../Classes/GameSettingPopup.h \
                   $(LOCAL_PATH)/../../../Classes/ResultPopup.h \
                   $(LOCAL_PATH)/../../../Classes/Block.h \
                   $(LOCAL_PATH)/../../../Classes/Board.h \
                   $(LOCAL_PATH)/../../../Classes/GridCell.h \

LOCAL_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)
$(call import-module, extensions)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
