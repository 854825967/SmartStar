#ifndef ITOUCHHANDLE_H
#define ITOUCHHANDLE_H
#include "Header.h"

typedef enum {
    TOUCH_GRADE_TOP = 0,
    TOUCH_GRADE_ALERT = TOUCH_GRADE_TOP,
    TOUCH_GRADE_UI,
    TOUCH_GRADE_GAME,

    //ADD BEFOR THIS
    TOUCH_GRADE_COUNT
}CTouchGrade;

typedef enum {
    TOUCH_EVENT_BEGAN,
    TOUCH_EVENT_MOVED,
    TOUCH_EVENT_ENDED,
    TOUCH_EVENT_CANCELED,

    TOUCH_EVENT_COUNT
}CTouchEventType;


class ITouchHandle {
public:
    ITouchHandle() {
        m_grade = TOUCH_GRADE_COUNT;
    }
    
    virtual s32 GetTouchIndex() = 0;
    virtual bool IsTouch(const cocos2d::Point & point) = 0;
    virtual void TouchEvent(const cocos2d::Point & point, const CTouchEventType nEventType) = 0;

    CTouchGrade m_grade;
};

#endif //ITOUCHHANDLE_H
