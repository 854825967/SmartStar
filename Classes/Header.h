#ifndef HEADER_H
#define HEADER_H
#include "cocos2d.h"
#include "MultiSys.h"
#include "Tools.h"

#ifdef __ANDROID__
#include "cocos2d/external/curl/include/android/curl/curl.h"
#endif

#ifdef WIN32
#include "curl/include/win32/curl/curl.h"
#endif

struct GameData {
    s8 m_nGravity;

    s32 m_nEliminate;
    s32 m_nSetupCount;
    s32 m_nRedStar;
    s32 m_nBlueStar;
    s32 m_nYellowStar;
    s32 m_nPoint;

    GameData() {
        memset(this, 0, sizeof(*this));
    }
};

struct GameConfig {
    s8 m_nRandom;
    float m_fScaling;
    cocos2d::Size m_ScreenSize;
    cocos2d::Size m_VirtualScrenSize;
    cocos2d::Point m_ScreenCenterPoint;

    GameConfig() {
        memset(this, 0, sizeof(*this));
    }
};

extern GameData g_data;
extern GameConfig g_config;
extern bool g_soundSwitch;

#define BASE_SCREEN_WIDTH 640.0f
#define BASE_SCREEN_HEIGHT 960.0f

typedef enum {
    STATE_GAME_INIT = 0,
    STATE_CREATE_CHESS,
    STATE_SCAN_CHESSBROAD,
    STATE_MOVE_CHESS,
    STATE_ABOUT,

}eState;

typedef enum {
    DIRECTION_UP = 0,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,

    //
    DIRECTION_NULL,
}eDirection;

typedef enum {
    STARTUI_MENU_PLAY = 0,
    STARTUI_MENU_HELP = 1,

    STARTUI_MENU_COUNT
//     STARTUI_MENU_SETTING = 1,
// 
//     //ADD BEFORE THIS
//     STARTUI_MENU_COUNT
}eStartUIMenu;

typedef enum {
    GAMEUI_MENU_POINT = 0,

    //ADD BEFOR THIS
    GAMEUI_MENU_COUNT,
}eGameUIMenu;

typedef enum {
    COLOR_BLUE = 0,
    COLOR_RED,
    COLOR_YELLOW,

    //ADD BEFOR THIS
    COLOR_COUNT
}eColor;

typedef enum {
    EVENT_ID_PLAY = 0,
    EVENT_ID_SETTING,
    EVENT_ID_HELP,
    EVENT_ID_CHESSBORD_SLIDE_UP,
    EVENT_ID_CHESSBORD_SLIDE_DOWN,
    EVENT_ID_CHESSBORD_SLIDE_LEFT,
    EVENT_ID_CHESSBORD_SLIDE_RIGHT,
    EVENT_ID_DEFEAT,
    EVENT_ID_REPLAY,
    EVENT_ID_CLOSE_HELP,
    EVENT_ID_ESC,
    EVENT_ID_GIFT_PACKS,
    EVENT_ID_EXIT_YES,
    EVENT_ID_EXIT_NO,
    EVENT_ID_CLEAR,
    EVENT_ID_SOUND_SWITCH,

}eEventID;

#define STARTUI_MENU_TAG_HEAD 10000
#define CREATE_CHESS_COUNT 6
#define TABLECLOTH_WIDTH 6
#define TABLECLOTH_HEIGHT 6
#define SLIDING_DISTANCE 100
#define ELIMINATE_COUNT 8
#define POINT_BASE 10
#define COMBO_POINT 10

typedef void (* event_fun)();

#ifdef __ANDROID__
#include <jni.h>
#include <jni/JniHelper.h>
#include <android/log.h>
#endif //__ANDROID__

#include <string>

typedef int (*curl_callback)(void *, size_t, size_t, void *);

bool payBilling(const char * pBillIndex);
bool isMusicEnabled();

bool CURL_GET_REQUEST(const char * pUrl, const curl_callback pCallAddress);

enum {
    HTTP_LOG_DEBUG = 0,
    HTTP_LOG_WRAN = 1,
    HTTP_LOG_ERROR = 2,

};

#define HTTP_LOG_URL "http://218.244.149.57/LogServer.php?AppName=SmartStar&LogLevel=%d&LogContext=%s"

int httpLogProc(void *buffer, size_t size, size_t nmemb, void *stream);

#ifdef WIN32
#define HTTP_LOG(format, ...) {\
    char _log[4096] = {0}; \
    memset(_log, 0, sizeof(_log)); \
    SafeSprintf(_log, sizeof(_log), format, ##__VA_ARGS__); \
    char __url[4096] = {0}; \
    SafeSprintf(__url, sizeof(__url), HTTP_LOG_URL, 0, _log); \
    CURL_GET_REQUEST(__url, httpLogProc); \
}
#else
#define HTTP_LOG(format, a...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##a); \
    char __url[4096] = {0}; \
    SafeSprintf(__url, sizeof(__url), HTTP_LOG_URL, 0, log); \
    CURL_GET_REQUEST(__url, httpLogProc); \
}
#endif //WIN32

enum {
    PRODUCT_TYPE_1,
    PRODUCT_TYPE_2,
    PRODUCT_TYPE_5,
    PRODUCT_TYPE_6,
    PRODUCT_TYPE_8,
    PRODUCT_TYPE_10,
};

#define APP_ID "1234"
#define CONSUM_CODE_1 "000000010110"
#define CONSUM_CODE_2 "000000010111"
#define CONSUM_CODE_5 "000000010112"
#define CONSUM_CODE_6 "000000010113"
#define CONSUM_CODE_8 "000000010114"
#define CONSUM_CODE_10 "000000010115"

#define PRODUCT_ID_1 "0000000010365184"
#define PRODUCT_ID_2 "0000000010365185"
#define PRODUCT_ID_5 "0000000010365186"
#define PRODUCT_ID_6 "0000000010365187"
#define PRODUCT_ID_8 "0000000010365188"
#define PRODUCT_ID_10 "0000000010365189"

#define CP_ID "100002"
#define APP_KEY "594ed7dff95a72a3sbe1d1a392525349"
#define SOURCE "11"
#define CHANNEL_ID "12345678"

#define ONLINE_SMS_PAY_URL "http://119.39.227.243:9099//unipay/rest/unipay/prepaid/onlinesmspay/%s/%s?\
channelid=%s&\
consumeCode=%s&\
productid=%s&\
cpOrderId=%s&\
appId=%s&\
myId=%s&\
imsi=%s&\
cpparam=%s&\
timestamp=%s&\
sign=%s&\
keyversion=1"

#endif //HEADER_H
