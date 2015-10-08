#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Header.h"
#include "Interface/ITouchHandle.h"
#include "Chess.h"

class Chessboard : public cocos2d::Sprite, public ITouchHandle {
public:
    static Chessboard * create(const s8 nColor);

    void slideSwitch(const bool b);
    bool getSwitch();
    s32 GetTouchIndex();
    bool IsTouch(const cocos2d::Point & point);
    void TouchEvent(const cocos2d::Point & point, const CTouchEventType nEventType);

    ~Chessboard() {
        s_pSelf = NULL;
    }
private:
    Chessboard() {
        m_bCanSlide = false;
    }

private:
    static Chessboard * s_pSelf;
    bool m_bCanSlide;
};

#endif //CHESSBOARD_H
