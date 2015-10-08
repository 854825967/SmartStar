LOCAL_PATH := $(call my-dir)

#third so begin#
#include $(CLEAR_VARS)
#LOCAL_MODULE := megjb_shared
#LOCAL_SRC_FILES := prebuild/libmegjb.so
#include $(PREBUILT_SHARED_LIBRARY)
##third so end##

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
		   ../../Public/MultiSys.cpp \
		   ../../Public/md5.cpp \
		   ../../Public/json/json_reader.cpp \
		   ../../Public/json/json_value.cpp \
		   ../../Public/json/json_writer.cpp \
           ../../Classes/Header.cpp \
           ../../Classes/AppDelegate.cpp \
           ../../Classes/Button.cpp \
           ../../Classes/Chess.cpp \
           ../../Classes/Chessboard.cpp \
           ../../Classes/CTouchEngine.cpp \
           ../../Classes/DefeatPanel.cpp \
           ../../Classes/GamePanel.cpp \
           ../../Classes/Panel.cpp \
           ../../Classes/Smart09.cpp \
           ../../Classes/HelpPanel.cpp \
           ../../Classes/StartPanel.cpp \
           ../../Classes/ExitPanel.cpp \
           ../../Classes/ShopPanel.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		    $(LOCAL_PATH)/../../Public \
		    $(LOCAL_PATH)/../../Classes/Interface \
		    $(LOCAL_PATH)/../../

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)
