#ifndef BUTTON_H
#define BUTTON_H

#include "Header.h"
#include "Interface/ITouchHandle.h"

class Button : public ITouchHandle, public cocos2d::Node{
public:
    static Button * create(const s32 nEventID);
    virtual void setOpacity(GLubyte opacity);
    virtual void setScale(float scale);
    virtual bool init(const char * text, const s8 nColor = COLOR_COUNT, const char * pPic = NULL);
    virtual void changePic(const char * fileName);
    virtual s32 GetTouchIndex();
    virtual bool IsTouch(const cocos2d::Point & point);
    virtual void TouchEvent(const cocos2d::Point & point, const CTouchEventType nEventType);

private:
    Button(const s32 nEventID) {
        m_nEventID = nEventID;
        m_fScale = 1;
    }

private:
    cocos2d::Sprite * m_pSprite;
    cocos2d::Label * m_pLabel;
    s32 m_nEventID;
    float m_fScale;
};

#endif //BUTTON_H
