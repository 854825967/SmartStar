#include "Chessboard.h"
#include "Smart09.h"
USING_NS_CC;
Chessboard * Chessboard::s_pSelf = NULL;

Chessboard * Chessboard::create(const s8 nColor) {
    if (NULL == s_pSelf) {
        const char * pPath = NULL;
        switch (nColor) {
        case COLOR_BLUE:
            pPath = "tablecloth_blue.png";
            break;
        case COLOR_RED:
            pPath = "tablecloth_red.png";
            break;
        case COLOR_YELLOW:
            pPath = "tablecloth_yellow.png";
            break;
        default:
            ASSERT(false);
            break;
        }

        s_pSelf = NEW Chessboard();
        ASSERT(s_pSelf);
        if (s_pSelf && s_pSelf->initWithFile(pPath)) {
            s_pSelf->autorelease();
            return s_pSelf;
        }
        CC_SAFE_DELETE(s_pSelf);
    }

    return s_pSelf;
}

s32 Chessboard::GetTouchIndex() {
    return 0;
}

bool Chessboard::IsTouch(const cocos2d::Point & point) {
    Size size = getContentSize();
    if (fabs(point.x - getPositionX()) > size.width * g_config.m_fScaling/2.0f || fabs(point.y - getPositionY()) > size.height * g_config.m_fScaling/2.0f) {
        return false;
    }

    return true;
}

void Chessboard::slideSwitch(const bool b) {
    m_bCanSlide = b;
}

bool Chessboard::getSwitch() {
    return m_bCanSlide;
}

void Chessboard::TouchEvent(const cocos2d::Point & point, const CTouchEventType nEventType) {
    static Point s_StartPoint;
    static bool s_NewOPT;
    switch (nEventType)     {
    case TOUCH_EVENT_BEGAN:
        s_StartPoint = point;
        s_NewOPT = true;
        break;
    case TOUCH_EVENT_MOVED:
    case TOUCH_EVENT_ENDED:
    case TOUCH_EVENT_CANCELED:
        if (s_NewOPT) {
            s32 width = point.x - s_StartPoint.x;
            s32 height = point.y - s_StartPoint.y;
            if (width * width + height * height > SLIDING_DISTANCE * SLIDING_DISTANCE) {
                if (m_bCanSlide) {
                    s32 angle = atan2(width, height) * 180/3.1415926;
                    if (angle >= -45 && angle < 45) {
                        Smart09::CallEvent(EVENT_ID_CHESSBORD_SLIDE_UP);
                    } else if (angle < -45 && angle >= -135) {
                        Smart09::CallEvent(EVENT_ID_CHESSBORD_SLIDE_LEFT);
                    } else if (angle >= 45 && angle < 135) {
                        Smart09::CallEvent(EVENT_ID_CHESSBORD_SLIDE_RIGHT);
                    } else if (angle >= 135 || angle < -135) {
                        Smart09::CallEvent(EVENT_ID_CHESSBORD_SLIDE_DOWN);
                    }
                }

                s_NewOPT = false;
            }
        }
        break;
    default:
        break;
    }
}
